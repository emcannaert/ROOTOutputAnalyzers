#! /usr/bin/env python

import ROOT
from ROOT import TFile, TTree, gROOT, addressof
import sys
import numpy as np
import os
import correctionlib
from math import floor, isnan
from array import array

def splitArgs(arg):
	argvSplit = []
	for par in arg:
		par = par.split(",")
		argvSplit.extend(par)
	return argvSplit
def calcEventWeights(year, dataset): 

	if year == "2015":
		pathString = "2016preVFP"
	elif year == "2016":
		pathString == "2016postVFP"
	else:
		pathString = year
	inFileName = "QCD_%s_SKIMMED_TEST_%s.root"%(dataset,year)
	inFile = ROOT.TFile.Open ( inFileName , "READ" )
	tree = inFile.Get( "skimmedTree" )


	h_SFs = ROOT.TH1D("h_SFs","b-tagging SFs", 100, 0.5 ,1.25)
	h_SFs_trueb = ROOT.TH1D("h_SFs_trueb","b-tagging SFs for true b jets", 100, 0.5 ,1.5)
	h_SFs_truec = ROOT.TH1D("h_SFs_truec","b-tagging SFs for true c jets", 100, 0.5 ,1.5)
	h_SFs_truelight = ROOT.TH1D("h_SFs_truelight","b-tagging SFs for true light", 100, 0.5 ,1.5)

	btvjson = correctionlib.CorrectionSet.from_file("btagging/scaleFactors/%s_UL/btagging.json.gz"%pathString)

	f = TFile( 'bTag_eventWeight_%s.root'%year, 'RECREATE' )
	#outText = Open("bTagSFs")
	nMax = 30
	_eventNum     	 = array( 'i', [ 0 ] )
	_eventWeightBTag = array( 'd', [ 0 ] )
	_eventWeightUpBTag = array( 'd', [ 0 ] )
	_eventWeightDownBTag = array( 'd', [ 0 ] )
	_nAK4        	 = array( 'i', [ 0 ] )
	_AK4_pt      	 = array( 'd', nMax*[ 0 ] )

	treeOut = TTree( 'weightsBTagging', 'event weight and some AK4 jet pt for each event' )
	treeOut.Branch( '_eventNum',    _eventNum ,     '_eventNum/I' )
	treeOut.Branch( '_nAK4',        _nAK4 ,         '_nAK4/I' )
	treeOut.Branch( '_eventWeightBTag', _eventWeightBTag ,  '_eventWeightBTag/D' )
	treeOut.Branch( '_eventWeightUpBTag', _eventWeightUpBTag ,  '_eventWeightUpBTag/D' )
	treeOut.Branch( '_eventWeightDownBTag', _eventWeightDownBTag ,  '_eventWeightDownBTag/D' )

	treeOut.Branch( '_AK4_pt',      _AK4_pt ,       '_AK4_pt[_nAK4]t/D' )



	#dataHisto = histFile . Get ( " data " )
	eventNum = 0
	looseDeepJet = 0.0490;
	medDeepJet   = 0.2783;
	tightDeepJet = 0.7100;
	for entryNum in range (0 , tree.GetEntries()):
		"""if eventNum > 0:
			return
		"""
		tree.GetEntry( entryNum )

		AK4_pt = getattr ( tree , "lab_AK4_pt" )
		AK4_eta = getattr ( tree , "AK4_eta" )
		nfatjets = getattr ( tree , "nfatjets" )
		dijetMassOne = getattr ( tree , "dijetMassOne" )
		dijetMassTwo = getattr ( tree , "dijetMassTwo" )
		nAK4 = getattr ( tree , "nAK4" )
		totHT = getattr ( tree , "totHT" )
		nfatjet_pre = getattr ( tree , "nfatjet_pre" )
		AK4_DeepJet_disc = getattr ( tree , "AK4_DeepJet_disc" )
		AK4_hadronFlavour = getattr ( tree , "AK4_hadronFlavour" )


		if (nfatjets < 3) or (totHT < 1500):
			continue
		if (nfatjet_pre < 2) and ( ( dijetMassOne < 1000. ) or ( dijetMassTwo < 1000.)):
			continue 

		###### turn distributions from tree into np arrays ######
		AK4_DeepJet_disc_np = np.array(AK4_DeepJet_disc)
		AK4_pt_np  = np.array(AK4_pt)
		AK4_eta_np = abs(np.array(AK4_eta))
		AK4_hadronFlavour_np = np.array(AK4_hadronFlavour)

		isCharmInEvent = False
		isBottomInEvent = False
		if 5 in AK4_hadronFlavour:
			isBottomInEvent = True
		if 4 in AK4_hadronFlavour:
			isCharmInEvent = True

 		#### indices of light and bc jets based off hadronFlavour
		jet_flav   = np.array(AK4_hadronFlavour)
		light_jets = np.where(jet_flav == 0)
		bc_jets    = np.where(jet_flav != 0)

		#### calculate the efficiencies

		effMapFileName = "QCD_%s_efficiencyMap_%s.root"%(dataset,year)
		inFileEffMap = ROOT.TFile.Open ( effMapFileName , "READ" )
		effMap_light = inFileEffMap.Get ("h_effLightJets")
		effMap_c     = inFileEffMap.Get("h_effcJets")
		effMap_b     = inFileEffMap.Get("h_effbJets")
		jetEfficiency = []
		for iii in range(0,nAK4):
			binx = floor(AK4_pt_np[iii]/50.)   #pt
			biny = floor(5.0*(AK4_eta_np[iii]+2.4))  #eta
			tempFlavour = AK4_hadronFlavour_np[iii]
			if tempFlavour == 0:
				jetEfficiency.append(effMap_light.GetBinContent(binx,biny))
			elif tempFlavour == 4:
				jetEfficiency.append(effMap_c.GetBinContent(binx,biny))
			elif tempFlavour == 5:
				jetEfficiency.append(effMap_b.GetBinContent(binx,biny))
			else:
				print("invalid flavour!:", tempFlavour)
				return -999

		#### split efficiencies up into bc and light jets
		jetEfficiency_np = np.array(jetEfficiency)
		jetEfficiency_bc_jets    = jetEfficiency_np[bc_jets]
		jetEfficiency_light_jets = jetEfficiency_np[light_jets]

		#### bdisc values for light and bc jets
		light_jets_bdisc = AK4_DeepJet_disc_np[light_jets]
		bc_jets_bdisc    = AK4_DeepJet_disc_np[bc_jets]

		#### indices of light, bc jets that are tagged, not tagged
		light_jets_btagged     =   [iii for iii,bdisc in enumerate(light_jets_bdisc) if bdisc > tightDeepJet]
		light_jets_non_btagged =   [iii for iii,bdisc in enumerate(light_jets_bdisc) if bdisc <= tightDeepJet]

		bc_jets_btagged     =   [iii for iii,bdisc in enumerate(bc_jets_bdisc) if bdisc > tightDeepJet]
		bc_jets_non_btagged =   [iii for iii,bdisc in enumerate(bc_jets_bdisc) if bdisc <= tightDeepJet]

		"""  stuff not needed anymore probably
		#### variables for calculations
		bc_jets_pt       = AK4_pt_np[bc_jets]
		bc_jets_eta      = AK4_eta_np[bc_jets]
		bc_jets_flavour  = jet_flav[bc_jets]

		light_jets_pt       = AK4_pt_np[light_jets]
		light_jets_eta      = AK4_eta_np[light_jets]
		light_jets_flavour  = jet_flav[light_jets]

		print("Event looks like this - ")
		print("----------------------------------------------")
		print("AK4_pt:", AK4_pt_np)
		print("AK4_eta:" )
		###### separate out tight b-tagged jets from non-btagged jets #######
		jets_btagged =   [iii for iii,bdisc in enumerate(AK4_DeepJet_disc) if bdisc > tightDeepJet]
		jets_not_btagged =  [iii for iii,bdisc in enumerate(AK4_DeepJet_disc) if bdisc <= tightDeepJet]

		#################### stuff for doing the calculation ###############################
		###### separate light jets that were b-tagged from bc jets that were b-tagged ######
		btagged_light_jets = np.where(btagged_flavour == 0)
		btagged_bc_jets = np.where(btagged_flavour != 0)

		##### separate light jets that were not b-tagged from light jets that were b-tagged #####
		non_btagged_light_jets = np.where(non_btagged_flavour == 0)
		non_btagged_bc_jets = np.where(non_btagged_flavour != 0)

		
		##### get variables for b-tagged jets ######
		btagged_pt = AK4_pt_np[jets_btagged]
		btagged_eta = AK4_eta_np[jets_btagged]
		btagged_flavour = AK4_hadronFlavour_np[jets_btagged]
		btagged_bdisc     = AK4_DeepJet_disc_np[jets_btagged]

		##### get variables for non-b-tagged jets #####
		non_btagged_pt = AK4_pt_np[jets_not_btagged]
		non_btagged_eta = AK4_eta_np[jets_not_btagged]
		non_btagged_flavour = AK4_hadronFlavour_np[jets_not_btagged]
		non_btagged_bdisc = AK4_DeepJet_disc_np[jets_not_btagged] 
		
		"""
		PMC = 1.
		PDATA = 1.
		"""
		if( len(non_btagged_flavour)> 0  ):
			jet_sf_non_tagged_bc  = btvjson["deepJet_mujets"].evaluate("central","T", non_btagged_flavour[non_btagged_bc_jets], non_btagged_eta[non_btagged_bc_jets], non_btagged_pt[non_btagged_bc_jets]) #,non_btagged_bdisc)
			jet_sf_non_tagged_light = btvjson["deepJet_incl"].evaluate("central","T", non_btagged_flavour[non_btagged_light_jets], non_btagged_eta[non_btagged_light_jets], non_btagged_pt[non_btagged_light_jets]) #,non_btagged_bdisc)
		else:
			jet_sf_non_tagged_bc = []
			jet_sf_non_tagged_light = []

		if (len(btagged_flavour)> 0  ):
			jet_sf_tagged_bc      = btvjson["deepJet_mujets"].evaluate("central","T", btagged_flavour[btagged_bc_jets], btagged_eta[btagged_bc_jets], btagged_pt[btagged_bc_jets]) #,btagged_bdisc )
			jet_sf_tagged_light     = btvjson["deepJet_incl"].evaluate("central","T", btagged_flavour[btagged_light_jets], btagged_eta[btagged_light_jets], btagged_pt[btagged_light_jets]) #,btagged_bdisc )
		else:
			jet_sf_tagged_bc = []
			jet_sf_tagged_light = []
		"""

		jet_sf_bc    = btvjson["deepJet_mujets"].evaluate("central","T", jet_flav[bc_jets],    AK4_eta_np[bc_jets],     AK4_pt_np[bc_jets]) 
		jet_sf_light = btvjson["deepJet_incl"].evaluate(  "central","T", jet_flav[light_jets], AK4_eta_np[light_jets],  AK4_pt_np[light_jets])
		
		jet_sf_bc_btagged       = jet_sf_bc[bc_jets_btagged]
		jet_sf_bc_non_tagged    = jet_sf_bc[bc_jets_non_btagged]
		jet_sf_light_btagged    = jet_sf_light[light_jets_btagged]
		jet_sf_light_non_tagged = jet_sf_light[light_jets_non_btagged]

		btagged_eff     = []
		non_btagged_eff = []

		""" indices here 
		light_jets_btagged
		light_jets_non_btagged
		bc_jets_btagged
		bc_jets_non_btagged
		"""

	#### btagged bc jets 
		for iii in range(0,len(jet_sf_bc_btagged)):
			#PDATA *= jet_sf_bc_btagged[iii]*jetEfficiency_bc_jets[bc_jets_btagged][iii]
			PDATA *= jet_sf_bc_btagged[iii] #*jetEfficiency_bc_jets[bc_jets_btagged][iii]

			#PMC *= jetEfficiency_bc_jets[bc_jets_btagged][iii]

	#### btagged light jets
		for iii in range(0,len(jet_sf_light_btagged)):
			#PDATA *= jet_sf_light_btagged[iii]*jetEfficiency_light_jets[light_jets_btagged][iii]
			PDATA *= jet_sf_light_btagged[iii]
			#PMC *= jetEfficiency_light_jets[light_jets_btagged][iii]
	#### non b-tagged bc jets
		for iii in range(0,len(jet_sf_bc_non_tagged)):
			PMC *= (1-jetEfficiency_bc_jets[bc_jets_non_btagged][iii])
			PDATA *= (1 - jet_sf_bc_non_tagged[iii]*jetEfficiency_bc_jets[bc_jets_non_btagged][iii])
	#### non b-tagged light jets
		for iii in range(0,len(jet_sf_light_non_tagged)):
			PMC *= (1-jetEfficiency_light_jets[light_jets_non_btagged][iii])
			PDATA *= (1 - jet_sf_light_non_tagged[iii]*jetEfficiency_light_jets[light_jets_non_btagged][iii])

		eventWeight = PDATA/PMC
		#_eventWeightBTag[0] = 1.0
		if isnan(eventWeight):
			eventWeight = 1.0

		h_SFs.Fill(eventWeight)
		if isBottomInEvent:
			h_SFs_trueb.Fill(eventWeight)
		if isCharmInEvent:
			h_SFs_truec.Fill(eventWeight)
		if (not isBottomInEvent) and (not isCharmInEvent):
			h_SFs_truelight.Fill(eventWeight)


		_eventWeightBTag[0] = eventWeight


		######### set tree variables ##########
		_nAK4[0] = nAK4
		_eventNum[0] = eventNum
		for iii in range(0, nAK4):
			_AK4_pt[iii] = AK4_pt[iii]
		
		#######################################
		#print(_eventNum[0])
		eventNum+=1
		treeOut.Fill()

		#print(eventWeight)
	canvas = ROOT.TCanvas("canvas")
	canvas.SetLogy( True )
	#canvas.Draw ()
	h_SFs.Draw()
	canvas.Print ( "h_SFs.png" )

	h_SFs_trueb.Draw()
	canvas.Print ( "h_SFs_trueb.png" )

	h_SFs_truec.Draw()
	canvas.Print ( "h_SFs_truec.png" )

	h_SFs_truelight.Draw()
	canvas.Print ( "h_SFs_truelight.png" )

	f.Write("",TFile.kOverwrite)
	f.Close()


##############################################################################
#MAIN
##############################################################################
def main(argv):
	argvSplit = splitArgs(argv)

	yearRef = ['2015','2016','2017','2018'] 
	datasetRef = ['HT1000to1500','HT1500to2000','HT2000toInf']
	if '--help' in argv or '-h' in argv or '--h' in argv:
		print("--------------------------------------------------------------------------------------------")
		print("-- Formatting for input: python calcBTaggingWeights.py 2016,2017 HT2000toInf,HT1500to2000 --")
		print("--                         Other options: allYears, allDatasets                           --")
		print("--                         2016 = 2016postVFP, 2016 = 2016preVFP                          --")
	if 'allYears' in argv:
		years = yearRef
	else:
		years = [ year for year in yearRef if year in argvSplit]
	if 'allDatasets' in argv:
		datasets = datasetRef
	else:
		datasets = [dataset for dataset in datasetRef if dataset in argvSplit]

	if (( len(years) + len(datasets) ) < 1):
		print("wrong inputs: enter the data years you want (separated by a comma, allYears for all) and datasets you want (allDatasets for all)")
		return
	for year in years:
		for dataset in datasets:
			print("Calculating btagging event weights for %s %s."%(year,dataset))
			calcEventWeights(year,dataset)
			print("Finished with %s %s."%(year,dataset))
#how do we calculate the up/down event weight thing??
if __name__ == "__main__":
    main(sys.argv[1:])
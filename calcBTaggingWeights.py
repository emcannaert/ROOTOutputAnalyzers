#! /usr/bin/env python

import ROOT
import sys
import numpy as np
import os
import correctionlib

'''
def getEffMapValue(pt,eta,flavour):
	binx = floor(pt/50.)   #pt
	biny = floor(5.0*(eta+2.4))  #eta
	if flavour == 0:
		return effMap_light.GetBinContent(binx,biny)
	elif flavour == 4:
		return effMap_c.GetBinContent(binx,biny)
	elif flavour == 5:
		return effMap_b.GetBinContent(binx,biny)
	else:
		print("invalid flavour!:", flavour)
		return -999

'''
##############################################################################
#MAIN
##############################################################################
def main(argv): 

	print("hello world")
	'''
	print("0")


	effMapFileName = "QCD_HT2000toInf_efficiencyMap_2018.root"
	inFileEffMap = ROOT.TFile.Open ( effMapFileName , "READ" )
	effMap_light = inFileEffMap.Get ("h_effLightJets")
	effMap_c = inFileEffMap.Get ("h_effcJets")
	effMap_b = inFileEffMap.Get ("h_effbJets")


	inFileName = "QCD_HT2000toInf_2018.root"
	inFile = ROOT.TFile.Open ( inFileName , "READ" )
	tree = inFile.Get( "clusteringAnalyzerBR/tree" )
	#dataHisto = histFile . Get ( " data " )
	
	looseDeepJet = 0.0490;
	medDeepJet   = 0.2783;
	tightDeepJet = 0.7100;
	print("0.5")
	for entryNum in range (0 , tree.GetEntries()):
		tree.GetEntry( entryNum )
		#if getattr(tree , " lep_n " ) != 2:
		#	continue
		lepton0 = ROOT . TLorentzVector ()
		lepton1 = ROOT . TLorentzVector ()
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
		print("1")
		jets_btagged = np.where(AK4_DeepJet_disc > tightDeepJet)
		jets_not_btagged = np.where(AK4_DeepJet_disc <= tightDeepJet)

		btagged_pt = AK4_pt[jets_btagged]
		btagged_eta = AK4_eta[jets_btagged]
		btagged_flavour = AK4_hadronFlavour[jets_btagged]

		non_btagged_pt = AK4_pt[jets_not_btagged]
		non_btagged_eta = AK4_eta[jets_not_btagged]
		non_btagged_flavour = AK4_hadronFlavour[jets_not_btagged]

		print("2")

		"""########### another level of this shit .###############
		jets_light_btagged = np.where(btagged_flavour == 0 )
		light_btagged_pt = btagged_pt[jets_light_btagged]
		light_btagged_eta = btagged_eta[jets_light_btagged]

		jets_c_btagged = np.where(btagged_flavour == 4 )
		c_btagged_pt = btagged_pt[jets_c_btagged]
		c_btagged_eta = btagged_eta[jets_c_btagged]

		jets_b_btagged = np.where(btagged_flavour == 5 )
		b_btagged_pt = btagged_pt[jets_b_btagged]
		b_btagged_eta = btagged_eta[jets_b_btagged]
		#######################################################

		jets_light_non_btagged = np.where(non_btagged_flavour == 0 )
		light_non_btagged_pt = btagged_pt[jets_light_non_btagged]
		light_btagged_eta = btagged_eta[jets_light_non_btagged]

		jets_c_non_btagged = np.where(non_btagged_flavour == 4 )
		c_non_btagged_pt = btagged_pt[jets_c_non_btagged]
		c_non_btagged_eta = btagged_eta[jets_c_non_btagged]

		jets_b_non_btagged = np.where(non_btagged_flavour == 5 )
		b_non_btagged_pt = btagged_pt[jets_b_non_btagged]
		b_non_btagged_eta = btagged_eta[jets_b_non_btagged]



		light_jet_sf_tagged = btvjson["deepJet_incl"].evaluate("central","T", jets_light_btagged, light_btagged_eta, light_btagged_pt)
		c_jets_sf_tagged = btvjson["deepJet_comb"].evaluate("central","T",jets_c_btagged, c_btagged_eta, c_btagged_pt)
		b_jets_sf_tagged = btvjson["deepJet_comb"].evaluate("central","T",jets_b_btagged, b_btagged_eta, b_btagged_pt)

		light_jet_sf_nontagged = btvjson["deepJet_incl"].evaluate("central","T", jets_light_non_btagged, light_btagged_eta, light_non_btagged_pt)
		c_jets_sf_nontagged = btvjson["deepJet_comb"].evaluate("central","T",jets_c_non_btagged, c_non_btagged_eta, c_non_btagged_pt)
		b_jets_sf_nontagged = btvjson["deepJet_comb"].evaluate("central","T",jets_b_non_btagged, b_non_btagged_eta, b_non_btagged_pt)

		"""

		PMC = 1.
		PDATA = 1.

		jet_sf_tagged     = btvjson["deepJet_incl"].evaluate("central","T", btagged_flavour, btagged_eta, non_btagged_pt)
		jet_sf_non_tagged = btvjson["deepJet_incl"].evaluate("central","T", non_btagged_flavour, non_btagged_eta, non_btagged_pt)
		print("3")

		btagged_eff     = []
		non_btagged_eff = []

		for iii in range(0,len(jets_btagged)):
			btagged_eff.append(getEffMapValue(btagged_pt[iii],btagged_eta[iii],btagged_flavour[iii]))
			PDATA *= jet_sf_tagged[iii]*btagged_eff[iii]
			PMC *= btagged_eff[iii]
		for iii in range(0,len(jets_non_btagged)):
			non_btagged_eff.append(getEffMapValue(non_btagged_pt[iii],non_btagged_eta[iii], non_btagged_flavour[iii]))
			PMC *= (1-non_btagged_eff[iii])
			PDATA *= (1 - jet_sf_non_tagged[iii]*non_btagged_eff[iii])
		print("4")

		eventWeight = PMC/PDATA
		print(eventWeight)
		'''

if __name__ == "__main__":
    main(sys.argv[1:])	
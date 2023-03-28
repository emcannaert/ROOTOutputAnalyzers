#! /usr/bin/env python

import ROOT
from ROOT import TFile, TTree, gROOT, addressof
import sys
import numpy as np
import os
import correctionlib
from correctionlib import _core
from math import floor, isnan
from array import array

def splitArgs(arg):
	argvSplit = []
	for par in arg:
		par = par.split(",")
		argvSplit.extend(par)
	return argvSplit
def calcEventWeights(year,dataset): 

	if year == "2015":
		pathString = "2016preVFP"
	elif year == "2016":
		pathString == "2016postVFP"
	else:
		pathString = year

	lumiTag = { "2015":"Collisions16_UltraLegacy_goldenJSON", "2016":"Collisions16_UltraLegacy_goldenJSON", "2017":"Collisions17_UltraLegacy_goldenJSON", "2018":"Collisions18_UltraLegacy_goldenJSON"}

	inFileName = "QCD_%s_SKIMMED_TEST_%s.root"%(dataset,year)
	inFile = ROOT.TFile.Open ( inFileName , "READ" )
	tree = inFile.Get( "skimmedTree" )

	h_SFs = ROOT.TH1D("h_SFs","PU reweighting SFs", 100, 0.5 ,1.25)
	PUjson = correctionlib.CorrectionSet.from_file("pileup/LUM/%s_UL/puWeights.json.gz"%pathString)

	f = TFile( 'bTag_eventWeight_%s.root'%year, 'RECREATE' )

	_eventNum      = array( 'i', [ 0 ] )
	_eventWeightPU = array( 'd', [ 0 ] )
	_puWeightDown  = array( 'd', [ 0 ] )
	_puWeightUp    = array( 'd', [ 0 ] )

	treeOut = TTree( 'weightsPU', 'event weight and some AK4 jet pt for each event' )
	treeOut.Branch( '_eventNum',    _eventNum ,     '_eventNum/I' )
	treeOut.Branch( '_eventWeightPU', _eventWeightPU ,  '_eventWeightPU/D' )
	treeOut.Branch( '_puWeightDown', _puWeightDown ,  '_puWeightDown/D' )
	treeOut.Branch( '_puWeightUp', _puWeightUp ,  '_puWeightUp/D' )


	eventNum = 0
	for entryNum in range (0 , tree.GetEntries()):
		tree.GetEntry( entryNum )

		nfatjets     = getattr ( tree , "nfatjets" )
		dijetMassOne = getattr ( tree , "dijetMassOne" )
		dijetMassTwo = getattr ( tree , "dijetMassTwo" )
		totHT        = getattr ( tree , "totHT" )
		nfatjet_pre  = getattr ( tree , "nfatjet_pre" )
		nfatjet_pre  = getattr ( tree , "nfatjet_pre" )
		ntrueInt = getattr ( tree , "ntrueInt" )
		if (nfatjets < 3) or (totHT < 1500):
			continue
		if (nfatjet_pre < 2) and ( ( dijetMassOne < 1000. ) or ( dijetMassTwo < 1000.)):
			continue 
		######### set tree variables ##########
		_eventNum[0] = eventNum
		_puWeightDown       = PUjson[lumiTag[year]].evaluate(ntrueInt,"down") 
		_eventWeightPU      = PUjson[lumiTag[year]].evaluate(ntrueInt,"nominal") 
		_puWeightUp         = PUjson[lumiTag[year]].evaluate(ntrueInt,"up") 
		#######################################
		eventNum+=1
		treeOut.Fill()

	canvas = ROOT.TCanvas("canvas")
	canvas.SetLogy( True )
	h_SFs.Draw()
	canvas.Print ( "h_SFs_%s.png"%year )

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
		print("-- Formatting for input: python calcPileupWeights.py 2016,2017 HT2000toInf,HT1500to2000 --")
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
if __name__ == "__main__":
    main(sys.argv[1:])
if __name__ == "__main__":
    main(sys.argv[1:])
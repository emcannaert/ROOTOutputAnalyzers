#! /usr/bin/env python

import ROOT
from ROOT import TFile, TTree, gROOT, addressof
import sys
import numpy as np
import os
from math import floor, isnan
from array import array

def splitArgs(arg):
	argvSplit = []
	for par in arg:
		par = par.split(",")
		argvSplit.extend(par)
	return argvSplit
def calcEventWeights(year,dataset): 




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



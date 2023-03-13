#!/bin/python

############### Written by Ethan Cannaert, April 23, 2021 #####################
#####             	   SCurve_Threshold_dump.py                          ######
#####             Takes in a run number, plots TProfile                  ######
#####			  of average 1D threshold values for ROC                 ######
#####			  pairs (0+15, 1+14, etc.) and saves plots               ######
#####                   to Plots/SCurve_Threshold                        ######
#####                           Options -  								 ######
#####         REQUIRED: --runnum <run num> = desired run number 		 ######
#####                             to analyze							 ######
#####         OPTIONAL: --plotdisks = Make SCurve threshold plots for 	 ######
#####                          each disk individually					 ######
#####         OPTIONAL: --modulenames <FULL path to .txt file> 			 ######
#####              with desired ROCs listed in format below				 ######
##### 				FPix_<cylinder>_D#_BLD#_PNL#_RNG#_ROC#  			 ######  
#####           Example:												 ######
#####                   FPix_BpO_D3_BLD4_PNL2_RNG2_ROC9					 ######
#####  example usage: python SCurve_Threshold_dump.py --runnum 736 /     ######
#####  --plotdisks --modulenames /home/tif/calibrations/modulenames.txt  ######
###############################################################################
import sys, os
import argparse
import glob
import  ROOT
from ROOT import *

class dumpSCurveThreshold:
	#class definition to access variables
	def __init__(self, runnum, plotdisks, modulenames):
		self.runnum = runnum
		self.plotdisks =plotdisks
		self.modulenames =modulenames
	cylinders = ["BmO","BmI", "BpO","BpI"]
	rfile_path = "/FPix/FPix_" 
	rfile_base = "FPix_"
	nbadfiles = 0
	nhistsfound = 0
	selectedROCs = []
	#Define TProfile 
	c1 = canvas = ROOT.TCanvas("c1","ROC Pair Threshold values",200,10,1600,1600);
	hprofROC  = ROOT.TProfile("hprofROC","ROC Pair Threshold values (All ROCs)",8,0,8,0,120);
	hprofROC_D1  = ROOT.TProfile("hprofROC_D1","ROC Pair Threshold values (Disk 1)",8,0,8,0,120);
	hprofROC_D2  = ROOT.TProfile("hprofROC_D2","ROC Pair Threshold values (Disk 2)",8,0,8,0,120);
	hprofROC_D3  = ROOT.TProfile("hprofROC_D3","ROC Pair Threshold values (Disk 3)",8,0,8,0,120);
	hprofROC_cust  = ROOT.TProfile("hprofROC_cust","ROC Pair Threshold values (Designated ROCs)",8,0,8,0,120);

def _getThresholdValue(self,histo):     
	
	#returns the center value of the given Threshold1D plot - tries to use gaussian unless there are too few entries (<500) or gaussian gives negative value
	if (histo.GetEntries() < 500):
		binmax = histo.GetMaximumBin()
		max_x = histo.GetXaxis().GetBinCenter(binmax);
		return max_x
	else:
		gaussFit = ROOT.TF1("gaussfit","gaus" ,0 ,100)
		histo.Fit(gaussFit ,"MQ")
		if gaussFit.GetParameter(1)  < 0:
			binmax = histo.GetMaximumBin()
			max_x = histo.GetXaxis().GetBinCenter(binmax);
			return max_x
		return gaussFit.GetParameter(1)    #returns the gaussian mean value
	
def _fillHist(self,readFile):
	#creates all possible ROC name combinations to find all histograms in root file
	for cylinder in self.cylinders:
		for disk in range(1,4):
			for BLD in range(1,19):
				for PNL in range(1,3):
					for RNG in range(1,3):
						for ROC in range(0,16):
							fold3 = self.rfile_base+ cylinder + "_D"+str(disk)
							fold4 = fold3 + "_BLD" + str(BLD)
							fold5 = fold4 + "_PNL" + str(PNL)
							fold6 = fold5 + "_RNG" + str(RNG)
							fold7 = fold6 + "_ROC" + str(ROC)
							histname = self.rfile_path + cylinder + "/" +fold3 + "/" + fold4 + "/"+ fold5 + "/" + fold6 + "/" + fold7 + "_Threshold1D"
							try:
								thresholdHist = readFile.Get(histname)
								if thresholdHist.GetEntries()< 1:
									continue
							except:
								#print("ERROR: Couldn't find histogram: %s"%histname)
								continue
							self.nhistsfound+=1
							thresholdValue = self.getThresholdValue(thresholdHist)
							lowROC  = 0
							highROC = 15
							#if thresholdHist.GetEntries()< 100:
							#	print("WARNING: Fewer than 100 entries in histogram %s"%(fold7+"_Threshold1D"))
							for _bin in range(0,9):
								if((ROC == lowROC) or (ROC == highROC)):
									self.hprofROC.Fill(_bin, thresholdValue)   #fill bin content
									if disk == 1:
										self.hprofROC_D1.Fill(_bin, thresholdValue)   #fill bin content
									elif disk == 2:
										self.hprofROC_D2.Fill(_bin, thresholdValue)   #fill bin content
									elif disk == 3:
										self.hprofROC_D3.Fill(_bin, thresholdValue) 
									if fold7 in self.selectedROCs:
										self.hprofROC_cust.Fill(_bin, thresholdValue)
								lowROC +=1
								highROC-=1

	return

def _openFiles(self,filelist):
	#Open up the root files in the given run directory and fills histogram with mean threshold value
	os.getcwd()
	for filename in filelist:
		try:
			readFile = ROOT.TFile.Open(filename ,"READ")
			self.fillHist(readFile)
		except:
			self.nbadfiles+=1
			print("ERROR: Couldn't open ROOT file: %s"%filename)

	return
def _drawhist(self):
	#draws and formats the TProfile of the ROC pair (0&15,1&14, etc.) threshold values       
	self.hprofROC.GetYaxis().SetTitle("Average ROC Threshold [VCal]")
	self.hprofROC.GetXaxis().SetTitle("ROC Pairing")
	lowROC  = 0
	highROC = 15
	for _bin in range(0,8):
		self.hprofROC.GetXaxis().SetBinLabel(_bin+1,"ROC %s+%s"%(str(lowROC),str(highROC)))
		self.hprofROC_D1.GetXaxis().SetBinLabel(_bin+1,"ROC %s+%s"%(str(lowROC),str(highROC)))
		self.hprofROC_D2.GetXaxis().SetBinLabel(_bin+1,"ROC %s+%s"%(str(lowROC),str(highROC)))
		self.hprofROC_D3.GetXaxis().SetBinLabel(_bin+1,"ROC %s+%s"%(str(lowROC),str(highROC)))
		self.hprofROC_cust.GetXaxis().SetBinLabel(_bin+1,"ROC %s+%s"%(str(lowROC),str(highROC)))
		lowROC +=1
		highROC-=1
	gStyle.SetOptStat("e")
	self.hprofROC.GetYaxis().SetTitleOffset(1.5);
	self.hprofROC.GetXaxis().SetLabelSize(0.025);
	self.hprofROC.Draw()

	if not os.path.exists("Plots/SCurve_Threshold/SCurve_%s/"%self.runnum):
		os.makedirs("Plots/SCurve_Threshold/SCurve_%s/"%self.runnum)
	self.c1.Print("Plots/SCurve_Threshold/SCurve_%s/SCurve%s_Threshold.png"%(self.runnum,self.runnum))
	if self.plotdisks:
		self.hprofROC_D1.GetYaxis().SetTitle("Average ROC Threshold [VCal]")
		self.hprofROC_D1.GetXaxis().SetTitle("ROC Pairing")
		self.hprofROC_D1.GetYaxis().SetTitleOffset(1.5);
		self.hprofROC_D1.GetXaxis().SetLabelSize(0.025);
		self.hprofROC_D1.Draw()
		self.c1.Print("Plots/SCurve_Threshold/%s/SCurve%s_Threshold_D1.png"%(self.runnum,self.runnum))

		self.hprofROC_D2.GetYaxis().SetTitle("Average ROC Threshold [VCal]")
		self.hprofROC_D2.GetXaxis().SetTitle("ROC Pairing")
		self.hprofROC_D2.GetYaxis().SetTitleOffset(1.5);
		self.hprofROC_D2.GetXaxis().SetLabelSize(0.025);
		self.hprofROC_D2.Draw()
		self.c1.Print("Plots/SCurve_Threshold/%s/SCurve%s_Threshold_D2.png"%(self.runnum,self.runnum))

		self.hprofROC_D3.GetYaxis().SetTitle("Average ROC Threshold [VCal]")
		self.hprofROC_D3.GetXaxis().SetTitle("ROC Pairing")
		self.hprofROC_D3.GetYaxis().SetTitleOffset(1.5);
		self.hprofROC_D3.GetXaxis().SetLabelSize(0.025);
		self.hprofROC_D3.Draw()
		self.c1.Print("Plots/SCurve_Threshold/%s/SCurve%s_Threshold_D3.png"%(self.runnum,self.runnum))
	if self.modulenames:
		self.hprofROC_cust.GetYaxis().SetTitle("Average ROC Threshold [VCal]")
		self.hprofROC_cust.GetXaxis().SetTitle("ROC Pairing")
		self.hprofROC_cust.GetYaxis().SetTitleOffset(1.5);
		self.hprofROC_cust.GetXaxis().SetLabelSize(0.025);
		self.hprofROC_cust.Draw()
		self.c1.Print("Plots/SCurve_Threshold/%s/SCurve%s_Threshold_cust.png"%(self.runnum,self.runnum))

	return
def _getCustomROCs(self):
	try:
		_ROCfile = open(self.modulenames, "r")
	except:
		print("Couldn't find or open .txt file with desired ROCs. Make sure the FULL path is included after --modulenames")
		return
	for line in _ROCfile:
		_data = line.split()
		if len(_data) > 1:
			print("Something wrong with provided .txt formatting. List ROCs in following format - FPix_<cylinder>_D#_BLD#_PNL#_RNG#_ROC#")
			return
		self.selectedROCs.append(_data[0])
	return
dumpSCurveThreshold.fillHist  = _fillHist
dumpSCurveThreshold.openFiles = _openFiles
dumpSCurveThreshold.getThresholdValue = _getThresholdValue
dumpSCurveThreshold.drawhist = _drawhist
dumpSCurveThreshold.getCustomROCs = _getCustomROCs

def main():
    
	parser = argparse.ArgumentParser(description='Create SCurve for a given run number.')
	parser.add_argument('--runnum', metavar='runnum', type=int, help='the run number to create Plot of SCurve Threshold Values')
	parser.add_argument('--plotdisks', action="store_true", help='Option to plot the SCurve Threshold for each disk individually', default=False)
	parser.add_argument('--modulenames', metavar='runnum', help='List of modules to plot SCurve Threshold for - requires FULL path to text file with desired modules in format\n FPix_<cylinder>_D#_BLD#_PNL#_RNG#_ROC#  \n Example: \n FPix_BpO_D3_BLD4_PNL2_RNG2_ROC9', default=False)

	args = parser.parse_args()

	run_num = -999
	run_num = args.runnum
	plotdisks = args.plotdisks
	modulenames = args.modulenames

	if run_num < 0:
		print("ERROR: Valid run number required: python SCurveThreshold_dump.py --runnum <run number>")
		return 

	filepath = "/home/tif/calibrations/Runs/SCurve_" + str(run_num)
	try:
		os.chdir(filepath)
	except:
		print("Not a valid run number (i.e. path %s does not exist to draw histograms from."%filepath)
		return
	_rootfiles = glob.glob("*.root")
	if not _rootfiles:
		print("ERROR: No ROOT files in directory %s"%filepath)
		return
	print("Processing ROOT Files at %s"%filepath)
	startSCurve = dumpSCurveThreshold(run_num,plotdisks, modulenames)
	if modulenames:
		#try:
		startSCurve.getCustomROCs()
		if(len(startSCurve.selectedROCs) == 0):
			print("Failed to get list of ROCs from .txt")
			return
		#except:
			#print("Couldn't find or open %s"%modulenames)
	startSCurve.openFiles(_rootfiles)
	if startSCurve.nbadfiles == len(_rootfiles):
		print("ERROR: Couldn't open any of the ROOT files")
		return
	os.chdir("/home/tif/calibrations/")
	startSCurve.drawhist()
	print("Found %i (non-empty) histograms"%startSCurve.nhistsfound)
	print("SCurve%s_Threshold.png Successfully saved to Plots/SCurve_Threshold"%run_num)
	return 


if __name__ == "__main__":
    main()

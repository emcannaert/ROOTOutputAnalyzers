import ROOT
import sys, os
from math import sqrt, exp
import random
from random import uniform, shuffle
import pdb
import time

### histInfo.py - contains a class that carries information from multiple histograms 
### for calculating statistal uncertainties
### Written by Ethan Cannaert, September 2023

class histInfo:    # this needs to be initialized for every new region + year, use when looping over the superbin_indices and filling out the uncertainties
	n_bins_x = 22
	n_bins_y = 20
	def __init__(self, year, region):
		self.region = region
		self.year   = year
		self.hist_1000to1500 = self.load_hist("HT1000to1500")
		self.hist_1500to2000 = self.load_hist("HT1500to2000")
		self.hist_2000toInf  = self.load_hist("HT2000toInf")
		self.hist_TTToHadronic = self.load_hist("TTTohadronic")
		self.hist_TTToSemiLeptonic = self.load_hist("TTToSemiLeptonic")
		self.hist_TTToLeptonic = self.load_hist("TTToLeptonic")

		#print("##############################################")
		#print("Printing the original contribution histograms ")
		#print("##############################################")
		self.list_1000to1500   = self.convert_TH2(self.hist_1000to1500)
		#print('\n'.join(' '.join(str(x) for x in row) for row in self.list_1000to1500))
		self.list_1500to2000   = self.convert_TH2(self.hist_1500to2000)
		#print('\n'.join(' '.join(str(x) for x in row) for row in self.list_1500to2000))
		self.list_2000toInf    = self.convert_TH2(self.hist_2000toInf)
		"""
		for iii in range(0, 22):
			for jjj in range(0,20):
				if self.list_2000toInf[iii][jjj] > 0:
					print("2000toInf bin value from histInfo is %s"%self.list_2000toInf[iii][jjj])
		"""
		self.list_TTToHadronic = self.convert_TH2(self.hist_TTToHadronic)
		self.list_TTToSemiLeptonic = self.convert_TH2(self.hist_TTToSemiLeptonic)
		self.list_TTToLeptonic = self.convert_TH2(self.hist_TTToLeptonic)

	def get_contribution_count(self, contribution, iii,jjj):
		if contribution == "HT1000to1500":
			return self.list_1000to1500[iii][jjj]
		elif contribution == "HT1500to2000":
			return self.list_1500to2000[iii][jjj]
		elif contribution == "HT2000toInf":
			return self.list_2000toInf[iii][jjj]
		elif contribution == "TTTohadronic":
			return self.list_TTToHadronic[iii][jjj]
		elif contribution == "TTToSemiLeptonic":
			return self.list_TTToSemiLeptonic[iii][jjj]
		elif contribution == "TTToLeptonic":
			return self.list_TTToLeptonic[iii][jjj]
		else:
			print("ERROR: wrong contribution type")
		return

	def get_contribution_uncert(self, contribution, iii,jjj):
		if contribution == "HT1000to1500":
			return sqrt(self.hist_1000to1500[iii][jjj])
		elif contribution == "HT1500to2000":
			return sqrt(self.hist_1500to2000[iii][jjj])
		elif contribution == "HT2000toInf":
			return sqrt(self.hist_2000toInf[iii][jjj])
		elif contribution == "TTToSemiLeptonic":
			return sqrt(self.hist_TTToSemiLeptonic[iii][jjj])
		elif contribution == "TTToLeptonic":
			return sqrt(self.hist_TTToLeptonic[iii][jjj])

	def get_bin_total_uncert(self, superbin):   # give a list of tuples that represent all the bins in your superbin
		start_time = time.time()

		total_1000to1500 = 0
		total_1500to2000 = 0
		total_2000toInf = 0
		total_TTToHadronic = 0
		total_TTToSemiLeptonic = 0
		total_TTToLeptonic = 0

		#print("The superbin looks like %s"%superbin )
		for _bin in superbin:

			total_1000to1500+= self.get_contribution_count("HT1000to1500", _bin[0],_bin[1])
			total_1500to2000+= self.get_contribution_count("HT1500to2000", _bin[0],_bin[1])
			total_2000toInf+= self.get_contribution_count("HT2000toInf", _bin[0],_bin[1])
			total_TTToHadronic+= self.get_contribution_count("TTTohadronic", _bin[0],_bin[1])
			total_TTToSemiLeptonic+= self.get_contribution_count("TTToSemiLeptonic", _bin[0],_bin[1])
			total_TTToLeptonic+= self.get_contribution_count("TTToLeptonic", _bin[0],_bin[1])

		# once all bins are looped over, square each contribution and add them in quadrature
		total_counts_in_superbin = total_1000to1500 + total_1500to2000 + total_2000toInf + total_TTToHadronic + total_TTToSemiLeptonic + total_TTToLeptonic
		if total_counts_in_superbin == 0:
			return 0.0

		#### do the scale factors need to be included here somewhere?
		frac_1000to1500 = total_1000to1500 / total_counts_in_superbin
		frac_1500to2000 = total_1500to2000 / total_counts_in_superbin
		frac_2000toInf = total_2000toInf / total_counts_in_superbin
		frac_TTToHadronic = total_TTToHadronic / total_counts_in_superbin
		frac_TTToSemiLeptonic = total_TTToSemiLeptonic / total_counts_in_superbin
		frac_TTToLeptonic = total_TTToLeptonic / total_counts_in_superbin

		stat_uncert_1000to1500 = 0
		stat_uncert_1500to2000 = 0
		stat_uncert_2000toInf = 0
		stat_uncert_TTToHadronic = 0
		stat_uncert_TTToSemiLeptonic = 0
		stat_uncert_TTToLeptonic = 0

		if total_1000to1500 > 0:
			stat_uncert_1000to1500   = 1.0/sqrt(total_1000to1500)
		if total_1500to2000 > 0:
			stat_uncert_1500to2000   = 1.0/sqrt(total_1500to2000)
		if total_2000toInf > 0:
			stat_uncert_2000toInf    = 1.0/sqrt(total_2000toInf)
		if total_TTToHadronic > 0:
			stat_uncert_TTToHadronic = 1.0/sqrt(total_TTToHadronic)
		if total_TTToSemiLeptonic > 0:
			stat_uncert_TTToSemiLeptonic = 1.0/sqrt(total_TTToSemiLeptonic)
		if total_TTToLeptonic > 0:
			stat_uncert_TTToLeptonic = 1.0/sqrt(total_TTToLeptonic)
		#print("stat_uncert_1000to1500: %s"%stat_uncert_1000to1500)
		#print("stat_uncert_1500to2000: %s"%stat_uncert_1500to2000)
		#print("stat_uncert_2000toInf: %s"%stat_uncert_2000toInf)
		#print("stat_uncert_TTToHadronic: %s"%stat_uncert_TTToHadronic)

		total_stat_uncert = sqrt(pow(frac_1000to1500*stat_uncert_1000to1500,2) + pow(frac_1500to2000*stat_uncert_1500to2000,2)+pow(frac_2000toInf*stat_uncert_2000toInf,2)+pow(frac_TTToHadronic*stat_uncert_TTToHadronic,2)+ pow(frac_TTToSemiLeptonic*stat_uncert_TTToSemiLeptonic,2)+pow(frac_TTToLeptonic*stat_uncert_TTToLeptonic,2))
		
		#print("Total counts in superbin %s. (%s/%s/%s/%s)"%(total_counts_in_superbin,total_1000to1500,total_1500to2000,total_2000toInf,total_TTToHadronic) ) 
		#print("total stat uncertainty: %s"%total_stat_uncert)


		#print(total_stat_uncert)
		#print("get_bin_total_uncert took %s to run"%(time.time() - start_time))

		return total_stat_uncert


	def load_hist(self,dataset_type):
		if "TTTohadronic" in dataset_type:
			hist_path = "/Users/ethan/Documents/rootFiles/processedRootFilesAlt/%s_%s_processed.root"%(dataset_type,self.year)
		elif "TTToSemiLeptonic" in dataset_type:
			hist_path = "/Users/ethan/Documents/rootFiles/processedRootFilesAlt/%s_%s_processed.root"%(dataset_type,self.year)
		elif "TTToLeptonic" in dataset_type:
			hist_path = "/Users/ethan/Documents/rootFiles/processedRootFilesAlt/%s_%s_processed.root"%(dataset_type,self.year)
		else:
			hist_path = "/Users/ethan/Documents/rootFiles/processedRootFilesAlt/QCDMC_%s_%s_processed.root"%(dataset_type,self.year)

		hist_name = "h_MSJ_mass_vs_MdSJ_%s"%self.region   # need to find what the name of this histogram
		TH2_file = ROOT.TFile.Open(hist_path,"READ")
		TH2_hist = TH2_file.Get(hist_name) 
		TH2_hist.SetDirectory(0)   # histograms lose their references when the file destructor is called
		ROOT.TH1.AddDirectory(False)
		return TH2_hist

	def convert_TH2(self,hist_):
		converted_hist = [ [0]*histInfo.n_bins_y for i in range(histInfo.n_bins_x)]
		for iii in range(0,histInfo.n_bins_x):
			for jjj in range(0,histInfo.n_bins_y):
				converted_hist[iii][jjj] = hist_.GetBinContent(iii,jjj)
		return converted_hist

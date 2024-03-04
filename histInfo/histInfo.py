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
		self.hist_1000to1500 = self.load_hist("QCDMC1000to1500")
		self.hist_1500to2000 = self.load_hist("QCDMC1500to2000")
		self.hist_2000toInf  = self.load_hist("QCDMC2000toInf")
		self.hist_TTToHadronicMC = self.load_hist("TTToHadronicMC")
		self.hist_TTToSemiLeptonicMC = self.load_hist("TTToSemiLeptonicMC")
		self.hist_TTToLeptonicMC = self.load_hist("TTToLeptonicMC")

		self.hist_data       = self.load_data_hists()


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
		self.list_TTToHadronicMC = self.convert_TH2(self.hist_TTToHadronicMC)
		self.list_TTToSemiLeptonicMC = self.convert_TH2(self.hist_TTToSemiLeptonicMC)
		self.list_TTToLeptonicMC = self.convert_TH2(self.hist_TTToLeptonicMC)

	def get_contribution_count(self, contribution, iii,jjj):
		if contribution == "QCDMC1000to1500":
			return self.list_1000to1500[iii][jjj]
		elif contribution == "QCDMC1500to2000":
			return self.list_1500to2000[iii][jjj]
		elif contribution == "QCDMC2000toInf":
			return self.list_2000toInf[iii][jjj]
		elif contribution == "TTToHadronicMC":
			return self.list_TTToHadronicMC[iii][jjj]
		elif contribution == "TTToSemiLeptonicMC":
			return self.list_TTToSemiLeptonicMC[iii][jjj]
		elif contribution == "TTToLeptonicMC":
			return self.list_TTToLeptonicMC[iii][jjj]
		else:
			print("ERROR: wrong contribution type")
		return

	def get_contribution_uncert(self, contribution, iii,jjj):
		if contribution == "QCDMC1000to1500":
			return sqrt(self.hist_1000to1500[iii][jjj])
		elif contribution == "QCDMC1500to2000":
			return sqrt(self.hist_1500to2000[iii][jjj])
		elif contribution == "QCDMC2000toInf":
			return sqrt(self.hist_2000toInf[iii][jjj])
		elif contribution == "TTToHadronicMC":
			return sqrt(self.hist_TTToHadronicMC[iii][jjj])
		elif contribution == "TTToSemiLeptonicMC":
			return sqrt(self.hist_TTToSemiLeptonicMC[iii][jjj])
		elif contribution == "TTToLeptonicMC":
			return sqrt(self.hist_TTToLeptonicMC[iii][jjj])

	def get_bin_total_uncert(self, superbin):   # give a list of tuples that represent all the bins in your superbin
		start_time = time.time()

		total_1000to1500 = 0
		total_1500to2000 = 0
		total_2000toInf = 0
		total_TTToHadronicMC = 0
		total_TTToSemiLeptonicMC = 0
		total_TTToLeptonicMC = 0

		#print("The superbin looks like %s"%superbin )
		for _bin in superbin:

			total_1000to1500+= self.get_contribution_count("QCDMC1000to1500", _bin[0],_bin[1])
			total_1500to2000+= self.get_contribution_count("QCDMC1500to2000", _bin[0],_bin[1])
			total_2000toInf+= self.get_contribution_count("QCDMC2000toInf", _bin[0],_bin[1])
			total_TTToHadronicMC+= self.get_contribution_count("TTToHadronicMC", _bin[0],_bin[1])
			total_TTToSemiLeptonicMC+= self.get_contribution_count("TTToSemiLeptonicMC", _bin[0],_bin[1])
			total_TTToLeptonicMC+= self.get_contribution_count("TTToLeptonicMC", _bin[0],_bin[1])

		# once all bins are looped over, square each contribution and add them in quadrature
		total_counts_in_superbin = total_1000to1500 + total_1500to2000 + total_2000toInf + total_TTToHadronicMC + total_TTToSemiLeptonicMC + total_TTToLeptonicMC
		if total_counts_in_superbin == 0:
			return 0.0

		#### do the scale factors need to be included here somewhere?
		frac_1000to1500 = total_1000to1500 / total_counts_in_superbin
		frac_1500to2000 = total_1500to2000 / total_counts_in_superbin
		frac_2000toInf = total_2000toInf / total_counts_in_superbin
		frac_TTToHadronicMC = total_TTToHadronicMC / total_counts_in_superbin
		frac_TTToSemiLeptonicMC = total_TTToSemiLeptonicMC / total_counts_in_superbin
		frac_TTToLeptonicMC = total_TTToLeptonicMC / total_counts_in_superbin

		stat_uncert_1000to1500 = 0
		stat_uncert_1500to2000 = 0
		stat_uncert_2000toInf = 0
		stat_uncert_TTToHadronicMC = 0
		stat_uncert_TTToSemiLeptonicMC = 0
		stat_uncert_TTToLeptonicMC = 0

		if total_1000to1500 > 0:
			stat_uncert_1000to1500   = 1.0/sqrt(total_1000to1500)
		if total_1500to2000 > 0:
			stat_uncert_1500to2000   = 1.0/sqrt(total_1500to2000)
		if total_2000toInf > 0:
			stat_uncert_2000toInf    = 1.0/sqrt(total_2000toInf)
		if total_TTToHadronicMC > 0:
			stat_uncert_TTToHadronicMC = 1.0/sqrt(total_TTToHadronicMC)
		if total_TTToSemiLeptonicMC > 0:
			stat_uncert_TTToSemiLeptonicMC = 1.0/sqrt(total_TTToSemiLeptonicMC)
		if total_TTToLeptonicMC > 0:
			stat_uncert_TTToLeptonicMC = 1.0/sqrt(total_TTToLeptonicMC)
		#print("stat_uncert_1000to1500: %s"%stat_uncert_1000to1500)
		#print("stat_uncert_1500to2000: %s"%stat_uncert_1500to2000)
		#print("stat_uncert_2000toInf: %s"%stat_uncert_2000toInf)
		#print("stat_uncert_TTToHadronicMC: %s"%stat_uncert_TTToHadronicMC)

		total_stat_uncert = sqrt(pow(frac_1000to1500*stat_uncert_1000to1500,2) + pow(frac_1500to2000*stat_uncert_1500to2000,2)+pow(frac_2000toInf*stat_uncert_2000toInf,2)+pow(frac_TTToHadronicMC*stat_uncert_TTToHadronicMC,2)+ pow(frac_TTToSemiLeptonicMC*stat_uncert_TTToSemiLeptonicMC,2)+pow(frac_TTToLeptonicMC*stat_uncert_TTToLeptonicMC,2))
		
		#print("Total counts in superbin %s. (%s/%s/%s/%s)"%(total_counts_in_superbin,total_1000to1500,total_1500to2000,total_2000toInf,total_TTToHadronicMC) ) 
		#print("total stat uncertainty: %s"%total_stat_uncert)


		#print(total_stat_uncert)
		#print("get_bin_total_uncert took %s to run"%(time.time() - start_time))

		return total_stat_uncert


	def load_hist(self,dataset_type):
		if "TTToHadronicMC" in dataset_type:
			hist_path = "/Users/ethan/Documents/rootFiles/processedRootFiles/%s_%s_nom_processed.root"%(dataset_type,self.year)
		elif "TTToSemiLeptonicMC" in dataset_type:
			hist_path = "/Users/ethan/Documents/rootFiles/processedRootFiles/%s_%s_nom_processed.root"%(dataset_type,self.year)
		elif "TTToLeptonicMC" in dataset_type:
			hist_path = "/Users/ethan/Documents/rootFiles/processedRootFiles/%s_%s_nom_processed.root"%(dataset_type,self.year)
		else:
			hist_path = "/Users/ethan/Documents/rootFiles/processedRootFiles/%s_%s_nom_processed.root"%(dataset_type,self.year)
		hist_name = "h_MSJ_mass_vs_MdSJ_%s"%self.region   # need to find what the name of this histogram
		TH2_file = ROOT.TFile.Open(hist_path,"READ")
		TH2_hist = TH2_file.Get("nom_/"+hist_name) 
		TH2_hist.SetDirectory(0)   # histograms lose their references when the file destructor is called
		ROOT.TH1.AddDirectory(False)
		return TH2_hist

	def load_data_hists(self):
		data_strings = []

		"""
["dataB-ver1","dataB-ver2","dataC-HIPM","dataD-HIPM","dataE-HIPM","dataF-HIPM"]
		elif self.year == "2016":
			data_blocks = ["dataF", "dataG", "dataH"]
		elif self.year == "2017":
			data_blocks = ["dataB","dataC","dataD","dataE", "dataF"]
		elif self.year == "2018":
			data_blocks = ["dataA","dataB","dataC","dataD"]



		"""
		combined_data = ROOT.TH2F("data_combined_%s"%(self.region),"Double Tagged Superjet mass vs diSuperjet mass (%s) (data combined) (%s); diSuperjet mass [GeV];superjet mass"%(self.region, self.year), 22,1250., 9500, 20, 500, 3500) #375 * 125
		hist_name = "h_MSJ_mass_vs_MdSJ_%s"%self.region   # need to find what the name of this histogram
		if self.year == "2015":
			data_strings = ["dataB-ver1","dataB-ver2","dataC-HIPM","dataD-HIPM","dataE-HIPM","dataF-HIPM"] ## will have to remove dataB-ver1
		elif self.year == "2016":
			data_strings = ["dataF","dataG","dataH"]
		elif self.year == "2017":
			data_strings = ["dataB","dataC","dataD","dataE","dataF"]
		elif self.year == "2018":
			data_strings = ["dataA","dataB","dataC","dataD"]
		for prefix in data_strings:
			hist_path = "/Users/ethan/Documents/rootFiles/processedRootFiles/%s_%s_nom_processed.root"%(prefix,self.year)
			TH2_file = ROOT.TFile.Open(hist_path,"READ")
			TH2_hist = TH2_file.Get("nom_/"+hist_name) 
			combined_data.Add(TH2_hist)

		combined_data.SetDirectory(0)   # histograms lose their references when the file destructor is called
		ROOT.TH1.AddDirectory(False)
		return combined_data

	def convert_TH2(self,hist_):
		converted_hist = [ [0]*histInfo.n_bins_y for i in range(histInfo.n_bins_x)]
		for iii in range(0,histInfo.n_bins_x):
			for jjj in range(0,histInfo.n_bins_y):
				converted_hist[iii][jjj] = hist_.GetBinContent(iii,jjj)
		return converted_hist

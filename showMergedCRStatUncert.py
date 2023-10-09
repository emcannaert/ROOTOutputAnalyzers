import ROOT
import sys, os
from math import sqrt, exp
import random
from random import uniform, shuffle
import pdb
import time
import ast
from histInfo import histInfo

### showMergedCRStatUncert.py
### written by Ethan Cannaert, October 2023
### imports the superbin indices from the signal region and applies them to CR histograms 
### and calculates their associated statistical uncertainty histograms 
### imports the histInfo class 


class applyCRBinMerge:

	n_bins_x = 22
	n_bins_y = 20
	def __init__(self,year):

		self.root_file_home      = "/Users/ethan/Documents/rootFiles/processedRootFilesAlt/"
		self.index_file_home     = "/Users/ethan/Documents/rootFiles/statisticalUncertaintyStudyAlt/txtfiles"
		self.merged_CR_plot_home    = "/Users/ethan/Documents/plots/CR_stat_uncert_SR_binning/"

		print("Doing merging process for CR for %s"%year)
		self.year = year
		self.TH2_hist = self.load_hist()
		self.hist_values = self.convert_TH2() #histogram filled with counts in each bin (from alt datasets)     # self.fill_random_values() self.test_hist() self.test_hist2()   # 

		self.all_hists = histInfo. histInfo(self.year, "CR")   ### this holds all the histogram info
		self.superbin_indices = self.load_superbin_indices()
		self.print_merged_CR_hist = self.print_histogram()
		
		self.non_empty_bins = [superbin for superbin_number, superbin in enumerate(self.superbin_indices) if self.counts_in_superbin(superbin_number)>0] 
		print("Merged and printed CR hist for %s. For this year, there were %s bins with counts"%(year,len(self.non_empty_bins)) )

	def load_superbin_indices(self):    # load in the superbin indices (located in a text file )
		_superbin_indices = []
		open_file = open(self.index_file_home+"/superbin_indices.txt","r")
		for line in open_file:
			columns = line.split('/')
			if columns[0] == self.year and columns[1] == "SR":   #### want the signal region superbin indices
				_superbin_indices = columns[2]
		return ast.literal_eval(_superbin_indices)

	def print_histogram(self):  
		c = ROOT.TCanvas("c", "canvas", 1000, 1050)
		ROOT.gStyle.SetOptStat(0)
		merged_CR_hist = ROOT.TH2F("merged_CR_hist", "Statistical Uncertainty of Control Region with SR Binning for %s; diSuperjet mass (GeV); avg superjet mass (GeV)"%(year), 22,1250., 9500, 20, 500, 3500)  # 375 * 125
		for superbin_number,superbin in enumerate(self.superbin_indices):
			for _tuple in superbin:
				merged_CR_hist.SetBinContent(_tuple[0],_tuple[1], self.all_hists.get_bin_total_uncert(superbin))
		merged_CR_hist.Draw("colz")
		c.SaveAs(self.merged_CR_plot_home+"/merged_%s_%s.png"%(self.year,"CR"))
		return
	def counts_in_superbin(self, superbin_number):
		_sum = 0
		for _tuple in self.superbin_indices[superbin_number]:
			_sum+= self.hist_values[_tuple[0]][_tuple[1]]
		return _sum
	def convert_TH2(self):
		converted_hist = [ [0]*applyCRBinMerge.n_bins_y for i in range(applyCRBinMerge.n_bins_x)]
		for iii in range(0,applyCRBinMerge.n_bins_x):
			for jjj in range(0,applyCRBinMerge.n_bins_y):
				converted_hist[iii][jjj] = self.TH2_hist.GetBinContent(iii,jjj) 
		return converted_hist

	def load_hist(self):
		hist_path = "/Users/ethan/Documents/rootFiles/statisticalUncertaintyStudyAlt/allBR_expectedCounts_%s_%s.root"%("CR",year)
		hist_name = "h_MSJ_mass_vs_MdSJ_CR"
		TH2_file = ROOT.TFile.Open(hist_path,"READ")
		TH2_hist = TH2_file.Get(hist_name) 
		TH2_hist.SetDirectory(0)   # histograms lose their references when the file destructor is called
		ROOT.TH1.AddDirectory(False)
		return TH2_hist

if __name__=="__main__":
	years = ["2015","2016", "2017","2018"]
	for year in years:
		CR_stat_uncert = applyCRBinMerge(year)
	##do stuff
import ROOT
import os, sys
import glob

### plotSystematicUncertiantyComparisons.py
### Written by Ethan Cannaert, October 2023

# get a list of all files in current folder
# look for combined files that have a systematic name, try to find the nom version 
# if both are found, open both files, extract the superjet and disuperjet plots, and plot them all together

def get_file_info(file_name):
	sample_str = ""
	year_str =  ""
	syst_str =  ""
	samples = ["QCDMC2000toInf","QCDMC1500to2000","QCDMC1000to1500","TTToHadronic"]
	years = ["2015","2016","2017","2018"]
	systematics = ["JEC","JER"]
	for sample in samples:
		if sample in file_name:
			sample_str = sample
	for year in years:
		if year in file_name:
			year_str = year
	for systematic in systematics:
		if systematic in file_name:
			syst_str = systematic

	#%s_%s_%s_combined.root"%(sample, year, sys_str)
	return year_str,sample_str,syst_str
if __name__=="__main__":

	#create canvas 
	plot_home = "/home/ethan/Documents/plots/systematicPlots"

	systematics = ["JEC", "JER"]
	root_files = glob.glob("*.root")   # get list of all root files in this directory
	for file_name in root_files:
		for systematic in systematics:
			nom_file_name = ile_name.replace(systematic,"nom")
			if systematic in file_name and nom_file_name in root_files:
				# try and find nominal version of 
				print("Looking at %s, found %s"%(file_name,file_name.replace(systematic,"nom")))
				#try to open these files, get the histograms from each, and then plot them together with nice formatting
				#try to work into the root file path
				year_str,sample_str,syst_str = get_file_info(file_name)
				hist_name_syst = ""
				hist_name_nom  = ""
				hist_path_up = ""
				hist_path_down = ""
				hist_path_nom  = ""


				# do all the fancy formatting 
				#draw histograms together 

				#save histogram as png
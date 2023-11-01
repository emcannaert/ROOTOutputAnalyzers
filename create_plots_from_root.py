import ROOT
import sys, os
import time
from print_nice_hist import print_nice_hist
from get_file_info import get_file_info
#import importlib
#importlib.reload(get_file_info)
##############################################################################################################
## create_plots_from_root.py
## written by Ethan Cannaert, October 2023
## USAGE: python3 create_plots_from_root.py <input file>.txt
## input file format: pathToPlot	hist_name	title/for/hist/separated/by/slashes	x/title/separated/by/slashes y/title/separated/by/slashes xlow xhigh ylow yhigh drawOption outputDir plotLogBool canvasx canvasy
## if you don't want to include an option, put a dash - instead
##############################################################################################################

def make_hist(file_path, hist_name,hist_title="-",xtitle = "-", ytitle = "-",xlow="-",xhigh="-",ylow = "-", yhigh = "-", draw_option="-", output_dir="-", logOption = "-", canvasx = "-",canvasy = "-"):
	output_path = output_dir+"/"+hist_name
	if not os.path.exists(output_path):
		os.makedirs(output_path)

	ROOT.gStyle.SetOptStat(0)
	root_file = ROOT.TFile.Open(file_path,"READ")

	hist_ = None

	#root_file.Get(hist_name)
	for key in root_file.GetListOfKeys():
		folder = key.ReadObj()
		folder_name = key.GetName()
		if isinstance(folder, ROOT.TDirectoryFile):
			root_file.cd(folder_name)
			for new_key in folder.GetListOfKeys():
				if not isinstance(new_key.ReadObj(), ROOT.TDirectoryFile) and new_key.GetName() == hist_name:
					hist_ = new_key.ReadObj()
		else:
			th_name = key.GetName()
			if th_name == hist_name:
				hist_ = key.ReadObj()

	if(hist_):
		hist_.SetDirectory(0) 
		ROOT.TH1.AddDirectory(False)
		print_nice_hist.print_nice_hist(hist_, file_path, hist_name,hist_title,xtitle,ytitle, xlow,xhigh,ylow,yhigh,draw_option, output_path, logOption, canvasx, canvasy)
		print("Histogram successfully created at %s."%output_path)
		return
	else:
		print("ERROR: histogram not found.")


def main(args):
	if len(args) != 2 or ".txt" not in args[1]:
		return
	file_lines = []
	with open(args[1] ) as f:
		file_lines = f.readlines()
	for iii,line in enumerate(file_lines):
		if iii < 2:
			continue
		info = line.split()
		if info == []:
			continue
		#print(info)
		make_hist(*info)

if __name__=="__main__":
	main(sys.argv)
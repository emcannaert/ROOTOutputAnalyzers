from create_nice_multiplot import create_nice_multiplot
import os, sys
import ROOT

## need to plot 

def load_hists(file_paths, hist_names):
	hist_list = []
	legend_names = []
	ROOT.TH1.AddDirectory(False)
	for file_path in file_paths:
		root_file = ROOT.TFile.Open(file_path,"READ")
		#root_file.Get(hist_name)
		for key in root_file.GetListOfKeys():
			folder = key.ReadObj()
			folder_name = key.GetName()
			if isinstance(folder, ROOT.TDirectoryFile):
				root_file.cd(folder_name)
				for new_key in folder.GetListOfKeys():
					if not isinstance(new_key.ReadObj(), ROOT.TDirectoryFile) and new_key.GetName() in hist_names:
						hist_list.append(new_key.ReadObj())
			else:
				th_name = key.GetName()
				if th_name in hist_names:
					hist_list.append(key.ReadObj())

		#if(hist_):
		#	hist_.SetDirectory(0) 
		#	ROOT.TH1.AddDirectory(False)
		#	hist_list.append(hist_)
		#else:
		#	print("ERROR: couldn't find histogram")
		#	return

		root_file.Close()
	for hist_ in hist_list:
		hist_name = hist_.GetName()
		legend_names.append(hist_name.split("_")[-1])


	print("Found %s histograms and %s legend name list : %s/%s"%(len(hist_list),len(legend_names), hist_list, legend_names))
	return hist_list, legend_names
def make_hists(file_path, hist_names,hist_title="-",xtitle = "-", ytitle = "-",xlow="-",xhigh="-",ylow = "-", yhigh = "-", draw_option="-", output_dir="-", logOption = "-", canvasx = "-",canvasy = "-"):
	hist_names = hist_names.split("/")
	folder_name = hist_names[0].split("_")[0]
	output_path = output_dir+"/"+folder_name
	if type(file_path) == type("abc"):
		file_path = [file_path]
	#if not os.path.exists(output_path):
	#	os.makedirs(output_path)
	hist_list,legend_list = load_hists(file_path,hist_names)
	#ROOT.gStyle.SetOptStat(0)
	create_nice_multiplot.create_nice_multiplot(file_path,hist_list, legend_list, hist_names ,hist_title,xtitle, ytitle,xlow,xhigh,ylow , yhigh, draw_option, output_dir, logOption, canvasx,canvasy)
	return 
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
		make_hists(*info)

if __name__=="__main__":
	main(sys.argv)
from create_nice_multiplot import create_nice_multiplot
import os, sys
import ROOT

## need to plot 
def get_sys_info(graph_name):
	sys_str = ""
	sys_sigma_str = ""
	sys_sigmas = ["_up","_down","_nom"]
	sys_names = ["PUweight"]
	for sys_sigma in sys_sigmas:
		if sys_sigma in graph_name:
			sys_sigma_str = sys_sigma
	for sys_name in sys_names:
		if sys_name in graph_name:
			sys_str = sys_name
	return sys_str,sys_sigma_str
def load_graphs(file_paths, graph_names):
	graph_list = []
	legend_names = []
	#ROOT.TGraph.AddDirectory(False)
	for file_path in file_paths:
		root_file = ROOT.TFile.Open(file_path,"READ")
		#root_file.Get(graph_name)
		for key in root_file.GetListOfKeys():
			folder = key.ReadObj()
			folder_name = key.GetName()
			if isinstance(folder, ROOT.TDirectoryFile):
				root_file.cd(folder_name)
				for new_key in folder.GetListOfKeys():
					if not isinstance(new_key.ReadObj(), ROOT.TDirectoryFile) and new_key.GetName() in graph_names:
						graph_list.append(new_key.ReadObj())
			else:
				th_name = key.GetName()
				if th_name in graph_names:
					graph_list.append(key.ReadObj())

		#if(hist_):
		#	hist_.SetDirectory(0) 
		#	ROOT.TH1.AddDirectory(False)
		#	graph_list.append(hist_)
		#else:
		#	print("ERROR: couldn't find histogram")
		#	return

		root_file.Close()
	for graph_ in graph_list:
		graph_name = graph_.GetName()
		sys_str,sys_sigma_str = get_sys_info(graph_name)
		print("Graph name is %s%s"%(sys_str,sys_sigma_str))
		legend_names.append("%s%s"%(sys_str,sys_sigma_str))   #### this is where the legend name is being set


	print("Found %s TGraphs and %s legend name list : %s/%s"%(len(graph_list),len(legend_names), graph_list, legend_names))
	return graph_list, legend_names
def make_graphs(file_path, graph_names,graph_titlex="-",xtitle = "-", ytitle = "-",xlow="-",xhigh="-",ylow = "-", yhigh = "-", draw_option="-", output_dir="-", logOption = "-", canvasx = "-",canvasy = "-", marker_options= "-"):
	graph_names = graph_names.split("/")
	folder_name = graph_names[0].split("_")[0]
	output_path = output_dir+"/"+folder_name
	if type(file_path) == type("abc"):
		file_path = [file_path]
	#if not os.path.exists(output_path):
	#	os.makedirs(output_path)
	graph_list,legend_list = load_graphs(file_path,graph_names)
	#ROOT.gStyle.SetOptStat(0)
	create_nice_multiplot.create_nice_multiplot(file_path,graph_list, legend_list, graph_names ,graph_titlex,xtitle, ytitle,xlow,xhigh,ylow , yhigh, draw_option, output_dir, logOption, canvasx,canvasy,marker_options)
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
		make_graphs(*info)

if __name__=="__main__":
	main(sys.argv)
import ROOT
import os, sys
import glob
from print_nice_hist import print_nice_hist

### plotDesiredTreeValue.py
### Written by Ethan Cannaert, October 2023
### Takes in the path to a root file (first arg) followed by the (second arg) name of a histogram and finally the output plot location (arg 3) and then creates a (nicely-formatted) plot of this quantity
###			usage:   python3 plotDesiredTreeValue.py <root file path> <hist name> <output directory>
### NOTE: this assumes there are is only 1 level of folders

def main(argv):
	if len(sys.argv) != 4:
		print("Wrong number of arguments. Must enter a path to a root file followed by a histogram name and then output plot location")
		return
	file_path = argv[1]
	print("Interpreted file path as %s"%file_path)
	hist_name = argv[2]
	print("Interpreted hist name as %s"%hist_name)
	output_path = argv[3]
	print("Interpreted hist plot out path as %s"%output_path)
	if not ".root" in file_path:
		print("first argument must be a root file.")
		return	
	root_file = ROOT.TFile.Open(file_path,"READ")
	if root_file.IsZombie():
		print("File %s not opened correctly. Returning."%file_path)
		return
	print("Successfully opened root file")

	for key in root_file.GetListOfKeys():
		folder = key.ReadObj()
		folder_name = key.GetName()
		if isinstance(folder, ROOT.TDirectoryFile):
			root_file.cd(folder_name)
			for new_key in folder.GetListOfKeys():
				if not isinstance(new_key.ReadObj(), ROOT.TDirectoryFile) and new_key.GetName() == hist_name:
					th2_hist = new_key.ReadObj()
					print("Found histogram!")
		else:
			th2_name = key.GetName()
			if th2_name == hist_name:
				print("Found histogram!")
				th2_hist = key.ReadObj()

	## give TH2 to print_nice_hist to print it with nice formatting
	if('th2_hist' in locals()):
		print_nice_hist.print_nice_hist(th2_hist,output_path,th2_hist.GetName())
		print("Histogram successfully created at %s."%output_path)
		return
	else:
		print("Histogram was NOT successfully created. ")
		return



if __name__=="__main__":
	main(sys.argv)




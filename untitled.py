import ROOT
import os, sys




if __name__=="__main__":
	try:
		eos_path = open(sys.argv, "r")
	except:
		print("Enter in a valid text file with a list of the files you want to copy from EOS (no spaces in between)")
		pass
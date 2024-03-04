import sys,os,time
import numpy as np
import ROOT
import ast
from print_nice_hist import print_nice_hist
from return_signal_SF import return_signal_SF



def estimate(year):

	hist_home = "/Users/ethan/Documents/rootFiles/finalCombineFiles/"
	linearized_file_name = hist_home+"combine_%s_Suu5_chi2.root"%year

	linearized_file = ROOT.TFile(linearized_file_name,  "READ")

	print("Trying to open file: %s"%linearized_file_name)
	SR_data 	= linearized_file.Get("nom/SR/data")
	SR_TTbar 	= linearized_file.Get("nom/SR/TTbar")
	SR_ST 		= linearized_file.Get("nom/SR/ST")
	SR_QCD 		= linearized_file.Get("nom/SR/QCD")
	CR_data 	= linearized_file.Get("nom/CR/data")
	AT1b_data 	= linearized_file.Get("nom/AT1b/data")
	AT1b_QCD    = linearized_file.Get("nom/AT1b/QCD")
	AT1b_TTbar 	= linearized_file.Get("nom/AT1b/TTbar")
	AT1b_ST 	= linearized_file.Get("nom/AT1b/ST")

	c1 = ROOT.TCanvas("","",1000,1000)
	TF = (AT1b_data.Integral()- AT1b_TTbar.Integral() - AT1b_ST.Integral()   )*SR_QCD.Integral()/AT1b_QCD.Integral()

	SR_est = CR_data.Clone()
	SR_est.Scale(TF/(CR_data.Integral()))
	SR_est.Add(SR_TTbar)
	SR_est.Add(SR_ST)

	SR_est.SetLineColor(ROOT.kRed)
	SR_data.SetLineColor(ROOT.kBlue)
	SR_est.Draw("HIST")
	SR_data.Draw("SAME")
	c1.SaveAs("%s/est.png"%hist_home)
	return




if __name__=="__main__":
	start_time = time.time()
	estimate(2018)
	print("Script took %ss to run."%(	np.round(time.time() - start_time,4 )) )

# create one root file for each year containing all the systematics = another level of folders
#   syst_suffix/region/hists
#   JEC_up/SR/QCD




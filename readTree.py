import ROOT
import sys, os
import numpy as np
import glob
import math
#from pathlib import Path  

def create_plots(filename):

	inFile = ROOT.TFile.Open(filename, "READ")

	print("Reading File %s."%filename)

	hist_list = []


	#h_m_SJ1_AT1b = ROOT.TH1F("h_m_SJ1_AT1b", "AT1b SJ mass (%s) (%s); SJ mass [GeV]; Events / 70 GeV"%(sample, year),50,0.0,3500)

	tree_name = "clusteringAnalyzerAll_nom/tree_nom"  # example clusteringAnalyzerAll_JEC_up, clusteringAnalyzerAll_JEC_down, clusteringAnalyzerAll_1
	tree = inFile.Get(tree_name)

	### this means a superjet has AK8 jets with these in them 
	### better way would be to see whether a superjet reclustered CA4 jet w/ E > 300 GeV is more likely to come from 
	### a b,c, light jet 
	tot_b_superjets 	= 0
	tot_c_superjets 	= 0
	tot_light_superjets = 0

	n_b_superjets_tagged 	 = 0
	n_c_superjets_tagged 	 = 0
	n_light_superjets_tagged = 0
	for iii,event in enumerate(tree):
		
		### look at superjets and see whether they are tagged
		### look at AK8 jets and count the hadron flavour of the tagged ones
			### add up the total number of AK8 jets that are associated with each hadron flavour
		
		SJ1_tagged = False
		SJ2_Tagged = False
		if tree.SJ_nAK4_300[0] > 2:
			SJ1_tagged = True
		if tree.SJ_nAK4_300[1] > 2:
			SJ2_tagged = True
		for iii in range(0,tree.nfatjets):
			if (abs(int(tree.AK8_partonFlavour[iii])) < 4 and abs(int(tree.AK8_partonFlavour[iii])) > 0) or tree.AK8_partonFlavour[iii] == 21:
				tot_light_superjets+=1
				if tree.AK8_SJ_assignment[iii] == 0 and SJ1_tagged:
					n_light_superjets_tagged+=1
				if tree.AK8_SJ_assignment[iii] == 1 and SJ2_Tagged:
					n_light_superjets_tagged+=1
			elif abs(int(tree.AK8_partonFlavour[iii])) == 4:
				tot_c_superjets+=1
				if tree.AK8_SJ_assignment[iii] == 0 and SJ1_tagged:
					n_c_superjets_tagged+=1
				if tree.AK8_SJ_assignment[iii] == 1 and SJ2_Tagged:
					n_c_superjets_tagged+=1
			elif abs(int(tree.AK8_partonFlavour[iii])) == 5:
				tot_b_superjets+=1
				if tree.AK8_SJ_assignment[iii] == 0 and SJ1_tagged:
					n_b_superjets_tagged+=1
				if tree.AK8_SJ_assignment[iii] == 1 and SJ2_Tagged:
					n_b_superjets_tagged+=1
			else:
				print("The hadron flavour is different from expected: %i"%tree.AK8_partonFlavour[iii])

	print("The tot number of b/c/light jets was %f/%f/%f, and of that %f/%f/%f superjets were tagged"%(tot_b_superjets,tot_c_superjets,tot_light_superjets,n_b_superjets_tagged,n_c_superjets_tagged,n_light_superjets_tagged))
	print("The b/c/light tagging rates for superjets are %f/%f/%f"%(n_b_superjets_tagged/tot_b_superjets,n_c_superjets_tagged/tot_c_superjets,n_light_superjets_tagged/tot_light_superjets ))
### returns the scale factor for a specific sample and year


if __name__=="__main__":
	filenames = ["/Users/ethan/Documents/rootFiles/randomRootFiles/clusteringAnalyzer_QCDMC2000toInf_2018_nom_output.root"]
	for filename in filenames:
		create_plots(filename)







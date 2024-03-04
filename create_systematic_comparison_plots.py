import numpy as np
import sys, os
import ROOT

from return_BR_SF import return_BR_SF

# create +- ratio plots for a given histogram and systematic

def get_year(inputFile):
	year = ""
	if "2015" in inputFile:
		year = "2015"
	elif "2016" in inputFile:
		year = "2016"
	elif "2017" in inputFile:
		year = "2017"
	elif "2018" in inputFile:
		year = "2018"
	return year

def get_combined_histogram(file_names, hist_name,folder, weights):

	f1 = ROOT.TFile(file_names[0],"r")
	combined_hist = f1.Get(folder+"/"+hist_name)
	combined_hist.Scale(weights[0])
	for iii in range(1,len(file_names)):
		f2 = ROOT.TFile(file_names[iii],"r")
		h2 = f2.Get(folder+"/"+hist_name)
		h2.Scale(weights[iii])
		combined_hist.Add(h2)
	return combined_hist

def create_3_hist_ratio_plot(up_hist,nom_hist,down_hist, hist_type, systematic, year, sample_type):

	up_hist.SetTitle("%s MC %s in the SR for up/nom/down %s Uncertainties (%s)"%(sample_type, hist_type, systematic,year))
	down_hist.SetTitle("%s MC %s in the SR for up/nom/down %s Uncertainties (%s)"%(sample_type, hist_type, systematic,year))

	up_hist.SetLineColor(ROOT.kRed)
	up_hist.SetLineWidth(5)
	nom_hist.SetLineColor(ROOT.kBlack)
	nom_hist.SetLineWidth(3)
	down_hist.SetLineColor(ROOT.kGreen)
	down_hist.SetLineWidth(5)

	ROOT.gStyle.SetOptStat(0)

	# Create a canvas to plot histograms
	canvas.Divide(1, 2)  # Divide canvas into two pads


				   # xlow, ylow, xhigh, yhigh
	canvas.cd(1).SetPad(0.0, 0.3, 1.0, 1.0) 
	#canvas.cd(2).SetPad(0.0, 0.0, 1.0, 0.3) 

	# Upper pad for histogram plots
	canvas.cd(1)
	up_hist.SetLineColor(ROOT.kBlue)
	nom_hist.SetLineColor(ROOT.kRed)
	down_hist.SetLineColor(ROOT.kGreen)
	up_hist.Draw()
	nom_hist.Draw("SAME")
	down_hist.Draw("SAME")
	legend = ROOT.TLegend(0.7, 0.7, 0.9, 0.9)
	legend.AddEntry(up_hist, "up systematic", "l")
	legend.AddEntry(nom_hist, "nom systematic", "l")
	legend.AddEntry(down_hist, "down systematic", "l")
	legend.Draw()

	# Lower pad for ratio plots
	canvas.cd(2)



	ratio1_2 = up_hist.Clone("ratio1_2")
	ratio1_2.SetTitle(hist_type + " up and down systematics / nom systematic")
	#ratio1_2.SetLabelSize(1.0)
	ratio1_2.GetYaxis().SetTitle("Ratio")
	ratio1_2.Divide(nom_hist)
	ratio1_2.SetLineColor(ROOT.kBlue)

	ratio1_2.Draw()

	ratio1_3 = down_hist.Clone("ratio1_3")
	ratio1_3.SetTitle(hist_type + " up and down systematics / nom systematic")
	ratio1_3.GetYaxis().SetTitle("Ratio")
	ratio1_3.Divide(up_hist)
	ratio1_3.SetLineColor(ROOT.kRed)

	ratio1_3.Draw("SAME")

	legend_ratio = ROOT.TLegend(0.7, 0.7, 0.9, 0.9)
	legend_ratio.AddEntry(ratio1_2, "up/nom systematic", "l")
	legend_ratio.AddEntry(ratio1_3, "down/nom systematic", "l")
	legend_ratio.Draw()

	canvas.SaveAs(output_plot_name)

	return


def create_systematic_comparison_plot(hist_name, hist_type,systematic, year,sample_type):

	input_file_dir = "/Users/ethan/Documents/rootFiles/processedRootFiles/"
	output_dir = "/Users/ethan/Documents/plots/ANPlots/"
	output_plot_name = output_dir+"%s_%sSysComparison_RatioPlot_SR_%s.png"%(hist_name,systematic,year)
	canvas = ROOT.TCanvas("canvas", "Histograms", 1200, 1000)

	finput = ROOT.TFile(inputFile)
	year_str = get_year(inputFile)
 	
	

	QCD_samples = ["QCDMC1000to1500_","QCDMC1500to2000_","QCDMC2000toInf_"]
	TTbar_samples = ["TTJetsMCHT1200to2500_", "TTJetsMCHT2500toInf_"]
	ST_samples = ["ST_t-channel-top_inclMC_","ST_t-channel-antitop_inclMC_","ST_s-channel-hadronsMC_","ST_s-channel-leptonsMC_","ST_tW-antiTop_inclMC_","ST_tW-top_inclMC_"]	

	QCD_file_names 	 = [input_file_dir+ ""  + year + "_processed.root" for QCD_sample in QCD_samples]
	TTbar_file_names = [input_file_dir+ ""  + year + "_processed.root" for TTbar_sample in TTbar_samples]
	ST_file_names 	 = [input_file_dir+ ""  + year + "_processed.root" for ST_sample in ST_samples]

	# get QCD histograms

	all_weights = return_BR_SF.return_BR_SF()

	QCD_weights 		= [all_weights["QCDMC1000to1500"][year],all_weights["QCDMC1500to2000"][year],all_weights["QCDMC2000toInf"][year] ]
	TTbar_weights 		= [all_weights["TTJetsMCHT1200to2500"][year],all_weights["TTJetsMCHT2500toInf"][year]]
	ST_weights			= [all_weights["ST_t_channel_top_inclMC"][year],all_weights["ST_t_channel_antitop_incMC"][year],all_weights["ST_s_channel_hadronsMC"][year],all_weights["ST_s_channel_leptonsMC"][year],all_weights["ST_tW_antiTop_inclMC"][year],all_weights["ST_tW_top_inclMC"][year]]

	QCD_combined_down	= get_combined_histogram(QCD_file_names, hist_name, systematic+"_down", QCD_weights)
	QCD_combined_nom	= get_combined_histogram(QCD_file_names, hist_name, 			"nom", QCD_weights)
	QCD_combined_up		= get_combined_histogram(QCD_file_names, hist_name, systematic+"_up", QCD_weights)

	TTbar_combined_down = get_combined_histogram(TTbar_file_names, hist_name, systematic+"_down", TTbar_weights)
	TTbar_combined_nom  = get_combined_histogram(TTbar_file_names, hist_name, 			   "nom", TTbar_weights)
	TTbar_combined_up   = get_combined_histogram(TTbar_file_names, hist_name, systematic+"_up", TTbar_weights)

	ST_combined_up 		= get_combined_histogram(ST_file_names, hist_name, systematic+"_up", ST_weights)
	ST_combined_nom 	= get_combined_histogram(ST_file_names, hist_name, 			  "nom", ST_weights)
	ST_combined_down 	= get_combined_histogram(ST_file_names, hist_name, systematic+"_down", ST_weights)



	allBR_up  = QCD_combined_up
	allBR_up.Add(TTbar_combined_up)
	allBR_up.Add(ST_combined_up)

	allBR_nom = QCD_combined_nom
	allBR_nom.Add(TTbar_combined_nom)
	allBR_nom.Add(ST_combined_nom)	

	allBR_down = QCD_combined_down
	allBR_down = TTbar_combined_down
	allBR_down = ST_combined_down


	### now make histograms


	create_3_hist_ratio_plot(allBR_up,allBR_nom,allBR_down, hist_type, systematic, year, "Combined BR")

	create_3_hist_ratio_plot(QCD_combined_up,QCD_combined_nom,QCD_combined_down, hist_type, systematic, year, "QCD")
	create_3_hist_ratio_plot(TTbar_combined_up,TTbar_combined_nom,TTbar_combined_down, hist_type, systematic, year, "TTbar")
	create_3_hist_ratio_plot(ST_combined_up,ST_combined_nom,ST_combined_down, hist_type, systematic, year, "Single Top")


	"""

	up_hist = ROOT.TH1F("hist1", "Histogram 1", 100, -5, 5)
	nom_hist = ROOT.TH1F("hist2", "Histogram 2", 100, -5, 5)
	down_hist = ROOT.TH1F("hist3", "Histogram 3", 100, -5, 5)

	# Fill histograms with some data
	for _ in range(10000):
	    up_hist.Fill(ROOT.gRandom.Gaus(0, 1))  # Filling with Gaussian distribution
	    nom_hist.Fill(ROOT.gRandom.Gaus(0, 1))  # Filling with Gaussian distribution
	    down_hist.Fill(ROOT.gRandom.Gaus(0, 1))  # Filling with Gaussian distribution
	"""
	return


if __name__== "__main__":

	years 	= ["2015","2016","2017","2018"]
	systematics = ["bTagSF","nom", "PUSF", "JEC", "JER", "topPt", "L1Prefiring", "pdf", "scale"]

	hist_names = ["h_SJ_mass_SR", "h_disuperjet_mass_SR"]  #histogram name for Getting
	hist_types = ["superjet mass", "diSuperjet mass"]   # description of histogram

	#testing 
	years = ["2015"]
	systematics = ["bTagSF"]
	hist_names = ["h_SJ_mass_SR"]
	for year in years:
		for iii,hist_name in enumerate(hist_names):
			for systematic in systematics:
				#try:
				create_systematic_comparison_plot(hist_name, hist_types[iii], systematic, year)
				#except:
					#print("ERROR: Failed for %s, %s %s"%(hist_name,uncertainty,year))








import numpy as np
import sys, os
import ROOT
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

def create_systematic_comparison_plot(inputFile,histname,systematic, ):
	finput = ROOT.TFile(inputFile)

	year = get_year(inputFile)
 	
	c =ROOT.TCanvas("c","",1250,1250)

	up_hist = finput.Get(systematic+"_up/"+region+"/"+histname)
	#up_hist.Sumw2()
	nom_hist = finput.Get("nom/"+region+"/"+histname)
	#nom_hist.Sumw2()
	down_hist = finput.Get(systematic+"_down/"+region+"/"+histname)
	#down_hist.Sumw2()

	up_hist.SetTitle("Linearized %s in the %s for different %s values (%s)"%(histname,region, systematic,year ))
	down_hist.SetTitle("Linearized %s in the %s for different %s values (%s)"%(histname,region, systematic,year ))


	up_hist.SetLineColor(ROOT.kRed)
	up_hist.SetLineWidth(5)
	nom_hist.SetLineColor(ROOT.kBlack)
	nom_hist.SetLineWidth(3)
	down_hist.SetLineColor(ROOT.kGreen)
	down_hist.SetLineWidth(5)

	ROOT.gStyle.SetOptStat(0)

	plot_name_upnom = "/Users/ethan/Documents/plots/final_plot_systematic_ratios/%s_%s_%s_%s_upnom.png"%(histname,region,systematic,year) 
	plot_name_downnom = "/Users/ethan/Documents/plots/final_plot_systematic_ratios/%s_%s_%s_%s_nomdown.png"%(histname,region,systematic,year)

	rp_up = ROOT.TRatioPlot(up_hist,nom_hist)
	rp_up.Draw("HIST,HIST")
	rp_up.GetLowerRefYaxis().SetTitle( "up/nom" );
	rp_up.GetLowerRefGraph().SetMaximum(1.25);
	rp_up.GetLowerRefGraph().SetMinimum(0.75);
	rp_up.GetUpperRefYaxis().SetTitle("Events");

	legend1 = ROOT.TLegend(1.0,0.8,0.48,0.9)
	legend1.AddEntry(up_hist, systematic+ " up", "l")
	legend1.AddEntry(nom_hist, "nom", "l")
	#legend1.AddEntry(down_hist, systematic+ " down", "l")
	legend1.Draw()
	c.SaveAs(plot_name_upnom)

	rp_down = ROOT.TRatioPlot(down_hist,nom_hist)
	rp_down.Draw("SAME,HIST")
	rp_down.GetLowerRefYaxis().SetTitle( "down/nom" );
	rp_down.GetLowerRefGraph().SetMaximum(1.25);
	rp_down.GetLowerRefGraph().SetMinimum(0.75);
	rp_down.GetUpperRefYaxis().SetTitle("Events");
	legend2 = ROOT.TLegend(1.0,0.8,0.48,0.9)
	legend1.AddEntry(nom_hist, "nom", "l")
	legend2.AddEntry(down_hist, systematic+ " down", "l")
	legend2.Draw()

	legend2 = ROOT.TLegend(1.0,0.8,0.48,0.9)
	#legend2.AddEntry(up_hist, systematic+ " up", "l")
	legend2.AddEntry(nom_hist, "nom", "l")
	legend2.AddEntry(down_hist, systematic+ " down", "l")
	legend2.Draw()

	c.SaveAs(plot_name_downnom)

if __name__== "__main__":

	inputFiles = ["/Users/ethan/Documents/rootFiles/finalCombineFiles/combine_2018_Suu5_chi2.root"]
	systematics = ["PUSF"]
	regions = ["SR"]
	histnames = ["QCD"]
	for inputFile in inputFiles:
		for histname in histnames:
			for systematic in systematics:
				for region in regions:
					create_ratio_plot(inputFile,histname,systematic)
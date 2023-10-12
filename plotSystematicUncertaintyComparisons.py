import ROOT
import os, sys
import glob


### plotSystematicUncertiantyComparisons.py
### Written by Ethan Cannaert, October 2023

# get a list of all root files in a given folder
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


	c = ROOT.TCanvas("c", "canvas", 1000, 1050)

	#create canvas 
	plot_home = "/home/ethan/Documents/plots/systematicPlots"
	root_file_home = "/home/ethan/Documents/rootFiles/processedRootFiles/"
	systematics = ["JEC", "JER"]
	print(root_file_home+"*_processed.root")
	root_files = glob.glob(root_file_home+"*_processed.root")   # get list of all root files in this directory
	print("root files are %s"%root_files)
	for file_name in root_files:
		for systematic in systematics:
			nom_file_name = file_name.replace(systematic,"nom")
			if systematic in file_name and nom_file_name in root_files:

				# try and find nominal version of 
				print("Looking at %s, found %s"%(file_name,file_name.replace(systematic,"nom")))
				#try to open these files, get the histograms from each, and then plot them together with nice formatting
				#try to work into the root file path
				year_str,sample_str,syst_str = get_file_info(file_name)

				print(year_str,sample_str,syst_str)
				syst_file = ROOT.TFile.Open(file_name,"READ")
				nom_file = ROOT.TFile.Open(file_name.replace(systematic,"nom"),"READ")

				print("Systematic file: %s"%file_name)
				print("Nom file: %s"%file_name.replace(systematic,"nom"))

				ROOT.gStyle.SetOptStat(0);
				#ROOT.gPad.SetLogy()

				hist_path_up   = syst_str + "_up"
				hist_path_down = syst_str + "_down"
				hist_path_nom  = "nom_"

				#######################################################################
				#SJ plots
				#######################################################################
				SJ_hist_name_syst = "h_SJ_mass_SR"
				SJ_up_hist = syst_file.Get(hist_path_up+"/"+SJ_hist_name_syst) 
				SJ_down_hist = syst_file.Get(hist_path_down+"/"+SJ_hist_name_syst) 
				SJ_nom_hist = nom_file.Get(hist_path_nom+"/"+SJ_hist_name_syst) 

				SJ_up_hist.SetLineColor(ROOT.kRed)
				SJ_down_hist.SetLineColor(ROOT.kBlue)
				SJ_nom_hist.SetLineColor(ROOT.kGreen)

				SJ_up_hist.SetLineWidth(3)
				SJ_down_hist.SetLineWidth(3)
				SJ_nom_hist.SetLineWidth(3)
				
				SJ_up_hist.SetTitle("Effect of %s on %s %s Superjet Mass"%(systematic,year_str,sample_str ))
				SJ_up_hist.GetYaxis().SetTitleOffset(1.72);
				SJ_up_hist.GetXaxis().SetTitle("avg superjet mass [GeV]");
				SJ_up_hist.Draw("HIST")
				SJ_down_hist.Draw("SAME")
				SJ_nom_hist.Draw("SAME")

				legend_SJ = ROOT.TLegend(0.6,0.65,0.85,0.8);
				legend_SJ.SetHeader("Systematic","C")
				legend_SJ.AddEntry(SJ_up_hist,"%s up"%systematic,"f")
				legend_SJ.AddEntry(SJ_nom_hist,"%s nom"%systematic,"f")
				legend_SJ.AddEntry(SJ_down_hist,"%s down"%systematic,"f")

				CMSLabel = ROOT.TText()
				CMSLabel.SetNDC()
				CMSLabel.SetTextFont(1)
				CMSLabel.SetTextColor(1)
				CMSLabel.SetTextSize(0.0385)
				CMSLabel.SetTextAlign(22)
				CMSLabel.SetTextAngle(0)
				CMSLabel.DrawText(0.152, 0.92, "CMS")
				CMSLabel.Draw()

				simLabel = ROOT.TText()
				simLabel.SetNDC()
				simLabel.SetTextFont(52)
				simLabel.SetTextColor(1)
				simLabel.SetTextSize(0.024)
				simLabel.SetTextAlign(22)
				simLabel.SetTextAngle(0)
				simLabel.DrawText(0.31, 0.915, "Simulation Preliminary")
				simLabel.Draw()

				latex = ROOT.TLatex()
				#latex = ROOT.TText
				lumistuff =  "(13 TeV)"
				latex.SetNDC()
				latex.SetTextAngle(0)
				latex.SetTextColor(ROOT.kBlack);  
				latex.SetTextFont(42)
				latex.SetTextAlign(31);
				latex.SetTextSize(0.030);   
				latex.DrawLatex(0.89,0.91,lumistuff)

				legend_SJ.Draw()
				c.SaveAs("%s/systematicComparison_SJ_mass_%s_%s_%s.png"%(plot_home,sample_str,syst_str,year_str))
				################################################################################################

				################################################################################################
				#diSJ plots
				diSJ_hist_name_syst = "h_disuperjet_mass_SR"
				print("Example: trying to find %s in file %s"%(hist_path_up+"/"+diSJ_hist_name_syst,file_name))
				diSJ_up_hist = syst_file.Get(hist_path_up+"/"+diSJ_hist_name_syst) 
				diSJ_down_hist = syst_file.Get(hist_path_down+"/"+diSJ_hist_name_syst) 
				diSJ_nom_hist = nom_file.Get(hist_path_nom+"/"+diSJ_hist_name_syst) 

				diSJ_up_hist.SetLineColor(ROOT.kRed)
				diSJ_down_hist.SetLineColor(ROOT.kBlue)
				diSJ_nom_hist.SetLineColor(ROOT.kGreen)

				diSJ_up_hist.SetLineWidth(3)
				diSJ_down_hist.SetLineWidth(3)
				diSJ_nom_hist.SetLineWidth(3)
				
				diSJ_up_hist.SetTitle("Effect of %s on %s %s diSuperjet Mass"%(systematic,year_str,sample_str ))
				diSJ_up_hist.GetYaxis().SetTitleOffset(1.72);
				diSJ_up_hist.GetXaxis().SetTitle(" diSuperjet mass [GeV]");
				diSJ_up_hist.Draw("HIST")
				diSJ_down_hist.Draw("SAME")
				diSJ_nom_hist.Draw("SAME")

				legend_diSJ = ROOT.TLegend(0.6,0.65,0.85,0.8);
				legend_diSJ.SetHeader("Systematic","C")
				legend_diSJ.AddEntry(SJ_up_hist,"%s up"%systematic,"f")
				legend_diSJ.AddEntry(SJ_nom_hist,"%s nom"%systematic,"f")
				legend_diSJ.AddEntry(SJ_down_hist,"%s down"%systematic,"f")

				CMSLabel.SetNDC()
				CMSLabel.SetTextFont(1)
				CMSLabel.SetTextColor(1)
				CMSLabel.SetTextSize(0.0385)
				CMSLabel.SetTextAlign(22)
				CMSLabel.SetTextAngle(0)
				CMSLabel.DrawText(0.152, 0.92, "CMS")
				CMSLabel.Draw()

				simLabel.SetNDC()
				simLabel.SetTextFont(52)
				simLabel.SetTextColor(1)
				simLabel.SetTextSize(0.024)
				simLabel.SetTextAlign(22)
				simLabel.SetTextAngle(0)
				simLabel.DrawText(0.31, 0.915, "Simulation Preliminary")
				simLabel.Draw()

				lumistuff =  "(13 TeV)"
				latex.SetNDC()
				latex.SetTextAngle(0)
				latex.SetTextColor(ROOT.kBlack);  
				latex.SetTextFont(42)
				latex.SetTextAlign(31);
				latex.SetTextSize(0.030);   
				latex.DrawLatex(0.89,0.91,lumistuff)

				legend_diSJ.Draw()
				c.SaveAs("%s/systematicComparison_diSJ_mass_%s_%s_%s.png"%(plot_home,sample_str,syst_str,year_str))
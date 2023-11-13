import ROOT
import os, sys
import glob
from print_nice_hist import print_nice_hist
from get_file_info import get_file_info
### compare_event_weights.py
### Written by Ethan Cannaert, October 2023
### for a given NOM root file, opens it up and plots the PU and btag event weights for up, down, and nom uncertainties

def main():
	plot_home = "/home/ethan/Documents/plots/scratch_plots"
	file_name = "/home/ethan/Documents/rootFiles/processedRootFiles/QCDMC2000toInf_2018_nom_processed.root"   #QCDMC2000toInf_   TTToHadronic_
	root_file = ROOT.TFile.Open(file_name,"READ")
	c = ROOT.TCanvas("c", "canvas", 1200, 1000)
	year_str,sample_str,syst_str = get_file_info.get_file_info(file_name)
	nom_ = "nom_"
	systematic = "btag_SF"
	btag_up_hist = root_file.Get(nom_+"/"+"h_bTag_eventWeight_up") 
	btag_down_hist = root_file.Get(nom_+"/"+"h_bTag_eventWeight_down") 
	btag_nom_hist = root_file.Get(nom_+"/"+"h_bTag_eventWeight_nom") 


	btag_up_hist.GetXaxis().SetRangeUser(0.4, 1.6);
	btag_down_hist.GetXaxis().SetRangeUser(0.4, 1.6);
	btag_nom_hist.GetXaxis().SetRangeUser(0.4, 1.6);

	btag_up_hist.SetLineColor(ROOT.kRed)
	btag_down_hist.SetLineColor(ROOT.kBlue)
	btag_nom_hist.SetLineColor(ROOT.kGreen)
	ROOT.gStyle.SetOptStat(0);
	btag_up_hist.SetLineWidth(3)
	btag_down_hist.SetLineWidth(3)
	btag_nom_hist.SetLineWidth(3)
	
	btag_up_hist.SetTitle("%a b-tagging Event weight for different SF uncertainty levels (%s)"%(sample_str,year_str ))
	btag_down_hist.SetTitle("%a b-tagging Event weight for different SF uncertainty levels (%s)"%(sample_str,year_str ))
	btag_nom_hist.SetTitle("%a b-tagging Event weight for different SF uncertainty levels (%s)"%(sample_str,year_str ))

	btag_up_hist.GetYaxis().SetTitleOffset(1.58);
	btag_up_hist.GetXaxis().SetTitle("avg superjet mass [GeV]");
	btag_up_hist.Draw("HIST")
	btag_nom_hist.Draw("SAME")
	btag_down_hist.Draw("SAME")

	legend_SJ = ROOT.TLegend(0.6,0.65,0.85,0.8);
	legend_SJ.SetHeader("Systematic","C")
	legend_SJ.AddEntry(btag_up_hist,"%s up"%systematic,"f")
	legend_SJ.AddEntry(btag_nom_hist,"%s nom"%systematic,"f")
	legend_SJ.AddEntry(btag_down_hist,"%s down"%systematic,"f")

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
	c.SaveAs("%s/btag_event_weight_comparison_%s_%s.png"%(plot_home,sample_str,year_str))

    #h_PU_eventWeight_down

	systematic = "PU_SF"
	PU_up_hist = root_file.Get(nom_+"/"+"h_PU_eventWeight_up") 
	PU_down_hist = root_file.Get(nom_+"/"+"h_PU_eventWeight_down") 
	PU_nom_hist = root_file.Get(nom_+"/"+"h_PU_eventWeight_nom") 

	PU_up_hist.SetLineColor(ROOT.kRed)
	PU_down_hist.SetLineColor(ROOT.kBlue)
	PU_nom_hist.SetLineColor(ROOT.kGreen)
	ROOT.gStyle.SetOptStat(0);
	PU_up_hist.SetLineWidth(3)
	PU_down_hist.SetLineWidth(3)
	PU_nom_hist.SetLineWidth(3)
	
	PU_down_hist.SetTitle("%a PU Event weight for different SF uncertainty levels (%s)"%(sample_str,year_str ))
	PU_up_hist.SetTitle("%a PU Event weight for different SF uncertainty levels (%s)"%(sample_str,year_str ))
	PU_nom_hist.SetTitle("%a PU Event weight for different SF uncertainty levels (%s)"%(sample_str,year_str ))

	PU_down_hist.GetYaxis().SetTitleOffset(1.58);
	PU_down_hist.GetXaxis().SetTitle("avg superjet mass [GeV]");
	PU_down_hist.Draw("HIST")
	PU_up_hist.Draw("SAME")
	PU_nom_hist.Draw("SAME")

	legend_SJ = ROOT.TLegend(0.6,0.65,0.85,0.8);
	legend_SJ.SetHeader("Systematic","C")
	legend_SJ.AddEntry(btag_up_hist,"%s up"%systematic,"f")
	legend_SJ.AddEntry(btag_nom_hist,"%s nom"%systematic,"f")
	legend_SJ.AddEntry(btag_down_hist,"%s down"%systematic,"f")

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
	c.SaveAs("%s/PU_event_weight_comparison_%s_%s.png"%(plot_home,sample_str,year_str))

if __name__=="__main__":
	main()




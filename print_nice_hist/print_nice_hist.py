import ROOT
import os, sys
import glob

### print_nice_hist.py
### Written by Ethan Cannaert, October 2023

# takes in a ROOT histogram, plot output filepath, name you want the plot png to be called, and drawing options and prints the histogram with nice formatting

def print_nice_histogram(hist, filepath,hist_name, option=""):
	c = ROOT.TCanvas("c", "canvas", 1000, 1050)
	if option == "":
		hist.Draw()
	else:
		hist.Draw(option)

	# do all the fancy formatting 

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
	lumistuff =  "(13 TeV)"
	latex.SetNDC()
	latex.SetTextAngle(0)
	latex.SetTextColor(ROOT.kBlack);  
	latex.SetTextFont(42)
	latex.SetTextAlign(31);
	latex.SetTextSize(0.030);   
	latex.DrawLatex(0.89,0.91,lumistuff)

	legend_SJ.Draw()
	c.SaveAs("%s/%s.png"%(filepath,hist_name))
	
	"""
	this is here if I ever want to modify this to return a histogram
	TH2_hist.SetDirectory(0)   # histograms lose their references when the file destructor is called
	ROOT.TH1.AddDirectory(False)
	"""

import ROOT
import os, sys
import glob
from get_file_info import get_file_info
### print_nice_hist.py
### Written by Ethan Cannaert, October 2023

# takes in a ROOT histogram, plot output path, name you want the plot png to be called, and drawing options and prints the histogram with nice formatting

def print_nice_hist(hist, hist_file_path, hist_name,hist_title="-",xtitle = "-", ytitle = "-", xlow="-",xhigh="-", ylow = "-", yhigh = "-", draw_option="-", output_dir="-", logOption = "-", canvasx = "-", canvasy = "-", year="-",systematic="-",sample="-", region="-"):
	c = None
	if canvasy != "-" and canvasx != "-":

		c = ROOT.TCanvas("c", "canvas", int(canvasx), int(canvasy))
	else:
		c = ROOT.TCanvas("c", "canvas", 1200, 1000)

	year_str,sample_str,syst_str = get_file_info.get_file_info(hist_file_path)
	region_str = ""
	if region!="-":
		region_str= region
	if year!='-':
		year_str = year
	if systematic!='-':
		syst_str = systematic
	if sample!="-":
		sample_str = sample
	if hist_title != "-":
		strs = [sample_str,region, syst_str,year_str]
		new_title = " ".join(hist_title.split("/"))
		for str_ in strs:
			if str_ != "":
				if str_ == "2015":
					new_title += " (2016preAPV)"
				elif str_ == "2016":
					new_title += " (2016postAPV)"
				else:
					new_title += " (%s)"%str_

		hist.SetTitle(new_title)

	if xtitle != "-":
		new_xtitle = " ".join(xtitle.split("/"))
		hist.GetXaxis().SetTitle(new_xtitle)

	if ytitle != "-":
		new_ytitle = " ".join(ytitle.split("/"))
		hist.GetYaxis().SetTitle(new_ytitle)

	if xlow != "-" and xhigh != "-":
		new_xlow = float(xlow)
		new_xhigh = float(xhigh)
		hist.GetXaxis().SetRangeUser(new_xlow, new_xhigh);
	if ylow != "-" and yhigh != "-":
		new_ylow = float(ylow)
		new_yhigh = float(yhigh)
		hist.GetYaxis().SetRangeUser(new_ylow, new_yhigh);
	if logOption != "-":
		new_logOption = bool(int(logOption))
		if new_logOption:
			c.SetLogy( True )

	if draw_option == "-":
		hist.Draw()
	else:
		hist.Draw(draw_option)
	hist.GetYaxis().SetTitleOffset(1.52);


	# do all the fancy formatting 
	ROOT.gStyle.SetOptStat(0);
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
	simLabel.DrawText(0.295, 0.92, "Simulation Preliminary")
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

	#legend_SJ.Draw()
	plot_name = hist_name
	strs = [sample_str,region, syst_str,year_str]
	for str_ in strs:
		if str_ != "":
			plot_name += "_%s"%str_
	c.SaveAs("%s/%s.png"%(output_dir,plot_name))


	"""
	this is here if I ever want to modify this to return a histogram
	TH2_hist.SetDirectory(0)   # histograms lose their references when the file destructor is called
	ROOT.TH1.AddDirectory(False)
	"""
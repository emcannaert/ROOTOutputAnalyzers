import ROOT
import os, sys
import glob
from get_file_info import get_file_info
### print_nice_hist.py
### Written by Ethan Cannaert, October 2023

# takes in a ROOT histogram, plot output path, name you want the plot png to be called, and drawing options and prints the histogram with nice formatting

def print_nice_hist(hist, hist_file_path, hist_name,hist_title="-",xtitle = "-", ytitle = "-", xlow="-",xhigh="-", ylow = "-", yhigh = "-", draw_option="-", output_dir="-", logOption = "-", canvasx = "-", canvasy = "-", year="-",systematic="-",sample="-", region="-", label_setting = "-", scale_bool = "-"):
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
			if str_ != "" and str_ != '-':
				if str_ == "2015":
					new_title += " (2016preAPV)"
				elif str_ == "2016":
					new_title += " (2016postAPV)"
				elif str_ == "QCDMC_All":
					new_title += " (Combined QCD)"
				elif str_ == "ST_MC_All":
					new_title += " (Single Top)"
				elif str_ == "TTbarMC_All":
					new_title += " (TTbar)"
				else:
					new_title += " (%s)"%str_

		hist.SetTitle(new_title)

	if scale_bool != '-':
		if int(scale_bool) == 1:
			# find the correct scale factor
			if year_str	!= "" and sample_str != "":
				scale_factor = get_scale_factor(year_str,sample_str)
				if scale_factor > 0:
					hist.Scale(get_scale_factor(year_str,sample_str))
				else:
					print("ERROR: Invalid scale factor: %f"%scale_factor)
					return
			else:
				print("You indicated you want to scale the histogram, but the year and sample strings are empty.")
				return
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
		if (new_logOption) and (type(hist) == type(ROOT.TH2F("dummyhist","dummy hist", 1,0,1,1,0,1 ))):
			c.SetLogz( True )
		else:
			c.SetLogy( True )

	if draw_option == "-":
		hist.Draw()
	else:
		hist.Draw(draw_option)
	hist.GetYaxis().SetTitleOffset(1.52);

	CMS_label_pos = 0.152
	SIM_label_pos = 0.295
	if label_setting != "-":
		CMS_label_pos = (1+ 0.1*int(label_setting))*0.152
		SIM_label_pos = (0.295-0.152)+CMS_label_pos

	# do all the fancy formatting 
	ROOT.gStyle.SetOptStat(0);
	CMSLabel = ROOT.TText()
	CMSLabel.SetNDC()
	CMSLabel.SetTextFont(1)
	CMSLabel.SetTextColor(1)
	CMSLabel.SetTextSize(0.0385)
	CMSLabel.SetTextAlign(22)
	CMSLabel.SetTextAngle(0)
	CMSLabel.DrawText(CMS_label_pos, 0.92, "CMS")
	CMSLabel.Draw()

	simLabel = ROOT.TText()
	simLabel.SetNDC()
	simLabel.SetTextFont(52)
	simLabel.SetTextColor(1)
	simLabel.SetTextSize(0.024)
	simLabel.SetTextAlign(22)
	simLabel.SetTextAngle(0)
	simLabel.DrawText(SIM_label_pos, 0.92, "Simulation Preliminary")
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
		if str_ != "" and str_ != "-":
			plot_name += "_%s"%str_
	c.SaveAs("%s/%s.png"%(output_dir,plot_name))


	"""
	this is here if I ever want to modify this to return a histogram
	TH2_hist.SetDirectory(0)   # histograms lose their references when the file destructor is called
	ROOT.TH1.AddDirectory(False)
	"""


### returns the scale factor for a specific sample and year
def get_scale_factor(year,sample):
	scale_factor = -9999
	scale_factors = {
	"QCDMC1000to1500":{"2015":1.578683216,"2016":1.482632755,"2017":3.126481451,"2018":4.289571744},
	"QCDMC1500to2000":{"2015":0.2119142341,"2016":0.195224041,"2017":0.3197450474,"2018":0.4947703875},
	"QCDMC2000toInf":{"2015":0.08568186031,"2016":0.07572795371,"2017":0.14306915,"2018":0.2132134533},
	"TTToHadronicMC":{"2015":0.075592,"2016":0.05808655696,"2017":0.06651018525,"2018":0.06588049107},
	"TTToSemiLeptonicMC":{"2015":0.05395328118,"2016":0.05808655696,"2017":0.04264829286,"2018":0.04563489275},
	"TTToLeptonicMC":{"2015":0.0459517611,"2016":0.03401684391,"2017":0.03431532926,"2018":0.03617828025},

	"TTJetsMCHT1200to2500":{"2015":0.002722324842,"2016":0.002255554525,"2017":0.00267594799,"2018":0.003918532089},
	"TTJetsMCHT2500toInf" :{"2015":0.000056798633,"2016":0.000050253843,"2017":0.00005947217,"2018":0.000084089656},

	"ST_t_channel_top_inclMC":{"2015":0.0409963154,"2016":0.03607115071,"2017":0.03494669125,"2018":0.03859114659},
	"ST_t_channel_antitop_incMC":{"2015":0.05673857623,"2016":0.04102705994,"2017":0.04238814865,"2018":0.03606630944},
	"ST_s_channel_hadronsMC":{"2015":0.04668187234,"2016":0.03564988679,"2017":0.03985938616,"2018":0.04102795437},
	"ST_s_channel_leptonsMC":{"2015":0.01323030083,"2016":0.01149139097,"2017":0.01117527734,"2018":0.01155448784},
	"ST_tW_antiTop_inclMC":{"2015":0.2967888696,"2016":0.2301666797,"2017":0.2556495594,"2018":0.2700032391},
	"ST_tW_top_inclMC":{"2015":0.2962796522,"2016":0.2355829386,"2017":0.2563403788,"2018":0.2625270613}}

	if "QCD" in sample:
		if "1000to1500" in sample:
			scale_factor = scale_factors["QCDMC1000to1500"][year]
		elif "1500to2000" in sample:
			scale_factor = scale_factors["QCDMC1500to2000"][year]
		elif "2000toInf" in sample:
			scale_factor = scale_factors["QCDMC2000toInf"][year]
		elif "QCDMC_combined" in sample:
			scale_factor = 1.0
		else:
			print("ERROR: Sample name not found: %s"%sample)
			return
	elif "TTTo" in sample:
		if "Hadronic" in sample:
			scale_factor = scale_factors["TTToHadronicMC"][year]
		elif "SemiLeptonic" in sample:
			scale_factor = scale_factors["TTToSemiLeptonicMC"][year]
		elif "TTToLeptonic" in sample:
			scale_factor = scale_factors["TTToLeptonicMC"][year]
		elif "TTJetsMCHT1200to2500" in sample:
			scale_factor = scale_factors["TTJetsMCHT1200to2500"][year]
		elif "TTJetsMCHT2500toInf" in sample:
			scale_factor = scale_factors["TTJetsMCHT2500toInf"][year]
		elif "TTbarMC_combined" in sample:
			scale_factor = 1.0
		else: 
			print("ERROR: Sample name not found: %s"%sample)
	elif "ST_" in sample:
		if "t_channel_top_incl" in sample:
			scale_factor = scale_factors["ST_t_channel_top_inclMC"][year]
		elif "t_channel_antitop_inc" in sample:
			scale_factor = scale_factors["ST_t_channel_antitop_incMC"][year]
		elif "s_channel_hadrons" in sample:
			scale_factor = scale_factors["ST_s_channel_hadronsMC"][year]
		elif "s_channel_leptons" in sample:
			scale_factor = scale_factors["ST_s_channel_leptonsMC"][year]
		elif "tW_antiTop_incl" in sample:
			scale_factor = scale_factors["ST_tW_antiTop_inclMC"][year]
		elif "tW_top_incl" in sample:
			scale_factor = scale_factors["ST_tW_top_inclMC"][year]
		elif "STMC_combined" in sample:
			scale_factor = 1.0 
		else:
			print("ERROR: Sample name not found: %s"%sample)
	else:
		print("ERROR: Sample name not found: %s"%sample)
	return scale_factor












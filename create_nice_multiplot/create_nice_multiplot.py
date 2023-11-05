import ROOT
import sys, os
import time
#from print_nice_hist import print_nice_hist
from get_file_info import get_file_info
#import importlib
#importlib.reload(get_file_info)
##############################################################################################################
## create_nice_multiplot.py
## written by Ethan Cannaert, November 2023
## takes in list of histograms and settings, and then plots these histograms together in a multiplot
##############################################################################################################

def create_nice_multiplot(file_path,hist_list, legend_list, hist_names ,hist_title="-",xtitle = "-", ytitle = "-",xlow="-",xhigh="-",ylow = "-", yhigh = "-", draw_option="-", output_dir="-", logOption = "-", canvasx = "-",canvasy = "-", marker_options = "-"):
	folder_name = hist_names[0].split("_")[1]
	output_path = output_dir+"/"+folder_name

	if not os.path.exists(output_path):
		os.makedirs(output_path)

	### find the histogram with the max value so this can be used as the main histogram.
	max_val = -9999
	max_index = -9999
	for iii, hist_ in enumerate(hist_list):
		if hist_.GetMaximum() > max_val:
			max_val = hist_.GetMaximum()
			max_index = iii


	c = None
	if canvasy != "-" and canvasx != "-":
		c = ROOT.TCanvas("c", "canvas", int(canvasx), int(canvasy))
	else:
		c = ROOT.TCanvas("c", "canvas", 1200, 1000)

	hist = hist_list[max_index]
	year_str,sample_str,syst_str = get_file_info.get_file_info(file_path[0])
	if hist_title != "-":
		new_title = " ".join(hist_title.split("/"))
		#if syst_str != "":
		hist.SetTitle("%s (%s) (%s)"%(new_title, sample_str, year_str ))

	#hist.SetTitle("%s (%s) (%s)"%(hist.GetTitle(), sample_str, year_str ))
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
			year_str+="_LOG"

	hist.SetLineColor(ROOT.kGreen)
	hist.SetLineWidth(4)

	marker_styles = len(hist_list)*[1]
	legend_markers = len(hist_list)*["f"]
	print("The marker option is ", marker_options)
	if marker_options != "-":
		marker_styles = marker_options.split("/")
		legend_markers = len(hist_list)*["p"]

	draw_str = len(hist_list)*["SAME"]
	print("The draw option is ", draw_option)
	if (draw_option!='-'):
		draw_str = ["%s,SAME"%substr for substr in draw_option.split("/")]



	# do all the fancy formatting 
	ROOT.gStyle.SetOptStat(0);
	CMSLabel = ROOT.TText()
	CMSLabel.SetNDC()
	CMSLabel.SetTextFont(1)
	CMSLabel.SetTextColor(1)
	CMSLabel.SetTextSize(0.0385)
	CMSLabel.SetTextAlign(22)
	CMSLabel.SetTextAngle(0)
	CMSLabel.DrawText(0.16, 0.92, "CMS")
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

	legend =  ROOT.TLegend(0.60,0.75,0.85,0.85);

	color_counter =0 
	colors = [ROOT.kRed,ROOT.kBlue, ROOT.kOrange, ROOT.kYellow, ROOT.kPink, ROOT.kTeal, ROOT.kViolet, ROOT.kCyan ]

	## need to create a multigraph
	## do two different loops, one for histograms, one for TGraphs
	if(type(hist_list[0]) == type(ROOT.TH1F())) or ( type(hist_list[0]) == type(ROOT.TH1I())):

		legend.AddEntry(hist_list[max_index],"%s"%legend_list[max_index],legend_markers[max_index]);

		if draw_option == "-":
			hist.Draw()
		else:
			hist.Draw(draw_str[max_index])
		hist.GetYaxis().SetTitleOffset(1.52);
		for iii in range(0,len(hist_list)):

			if iii == max_index:
				continue

			hist_list[iii].SetLineColor(colors[color_counter])
			hist_list[iii].SetLineWidth(4);
			hist_list[iii].Draw(draw_str[iii])

			legend.AddEntry(hist_list[iii],"%s"%legend_list[iii],legend_markers[iii]);
			color_counter+=1
	if( type(hist_list[0]) == type(ROOT.TGraph())):

		mg =  ROOT.TMultiGraph()
		
		for iii in range(0,len(hist_list)):
			if marker_options!='-': 
				hist_list[iii].SetMarkerStyle(int(marker_styles[iii]))
				hist_list[iii].SetMarkerSize(1)
				hist_list[iii].SetMarkerColor(colors[color_counter]) 
			#hist_list[iii].Draw(draw_str[iii])
			print("Looking at object %i, name is %s, marker style is %s, legend marker is %s"%(iii,legend_list[iii], marker_styles[iii],legend_markers[iii]))
			mg.Add(hist_list[iii])
			legend.AddEntry(hist_list[iii],"%s"%legend_list[iii],legend_markers[iii]);
			color_counter+=1
		mg.SetTitle(hist_list[0].GetTitle());
		mg.GetXaxis().SetTitle(hist_list[0].GetXaxis().GetTitle());
		mg.GetYaxis().SetTitle(hist_list[0].GetYaxis().GetTitle())
		mg.GetYaxis().SetTitleOffset(1.52);

		mg.Draw("AP")

	legend.Draw()

	c.SaveAs("%s/%s_%s_%s.png"%(output_path,folder_name,sample_str,year_str))


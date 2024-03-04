import sys, os
import ROOT
from return_signal_SF import return_signal_SF
## make plots of (1D) superjet mass, (1D) disuperjet mass, and (2D) average superjet vs diSuperjet mass for some mass points for each yar
"""
4 TeV Suu 1 Tev chi
5 TeV Suu 1.5 TeV chi
6 Tev Suu 2 Tev Chi
7 TeV suu 2.5 TEv chi
8 TEV Suu 3 Tev chi
for all 6 different final states

- do we want these to be scaled to a particular year? probably
"""

##### need to create a means of scaling each of these backgrounds to each year's lumi 
##### and then adding them together to have an expected combined=all had decay set of plots (not split by decay mode)



def make_plots(inFileName, year,decay,mass_point):

	plot_dir   = "/Users/ethan/Documents/plots/ANPlots/signalPlots/"
	c = ROOT.TCanvas("","", 1000,1000)
	sig_file = ROOT.TFile(inFileName,"READ")
	folder_name = "nom_/"
	h_SJ_mass_SR 					= sig_file.Get(folder_name+"h_SJ_mass_SR")
	h_diSJ_mass_SR =				= sig_file.Get(folder_name+"h_disuperjet_mass_SR")
	h_avg_SJ_mass_vs_diSJ_mass_SR 	= sig_file.Get(folder_name+"h_MSJ_mass_vs_MdSJ_SR")

	h_SJ_mass_CR 					= sig_file.Get(folder_name+"h_SJ_mass_CR")
	h_diSJ_mass_CR =				= sig_file.Get(folder_name+"h_disuperjet_mass_CR")
	h_avg_SJ_mass_vs_diSJ_mass_CR 	= sig_file.Get(folder_name+"h_MSJ_mass_vs_MdSJ_CR")

	h_SJ_mass_AT1b 						= sig_file.Get(folder_name+"h_SJ_mass_AT1b")
	h_diSJ_mass_AT1b =					= sig_file.Get(folder_name+"h_disuperjet_mass_AT1b")
	h_avg_SJ_mass_vs_diSJ_mass_AT1b 	= sig_file.Get(folder_name+"h_MSJ_mass_vs_MdSJ_AT1b")

	h_SJ_mass_AT0b 						= sig_file.Get(folder_name+"h_SJ_mass_AT0b")
	h_diSJ_mass_AT0b =					= sig_file.Get(folder_name+"h_disuperjet_mass_AT0b")
	h_avg_SJ_mass_vs_diSJ_mass_AT0b 	= sig_file.Get(folder_name+"h_MSJ_mass_vs_MdSJ_AT0b")

	h_totHT 							= sig_file.Get(folder_name+"h_totHT")

	# scale all histograms 
	sig_SF = return_signal_SF.return_signal_SF(year,mass_point,decay)


	h_SJ_mass_SR.Scale(sig_SF)
	h_diSJ_mass_SR.Scale(sig_SF)
	h_avg_SJ_mass_vs_diSJ_mass_SR.Scale(sig_SF)
	h_SJ_mass_CR.Scale(sig_SF)
	h_diSJ_mass_CR.Scale(sig_SF)
	h_avg_SJ_mass_vs_diSJ_mass_CR.Scale(sig_SF)
	h_SJ_mass_AT1b.Scale(sig_SF)
	h_diSJ_mass_AT1b.Scale(sig_SF)
	h_avg_SJ_mass_vs_diSJ_mass_AT1b.Scale(sig_SF)
	h_SJ_mass_AT0b.Scale(sig_SF)
	h_diSJ_mass_AT0b.Scale(sig_SF)
	h_avg_SJ_mass_vs_diSJ_mass_AT0b.Scale(sig_SF)
	h_totHT.Scale(sig_SF)

	h_SJ_mass_SR.SetTitle("Superjet mass (%s, %s, %s, SR)"%(decay,mass_point,year))
	h_diSJ_mass_SR.SetTitle("diSuperjet mass (%s, %s, %s, SR)"%(decay,mass_point,year))
	h_avg_SJ_mass_vs_diSJ_mass_SR.SetTitle("avg. superjet mass vs diSuperjet mass (%s, %s, %s, SR)"%(decay,mass_point,year))

	h_SJ_mass_CR.SetTitle("Superjet mass (%s, %s, %s, CR)"%(decay,mass_point,year))
	h_diSJ_mass_CR.SetTitle("diSuperjet mass (%s, %s, %s, CR)"%(decay,mass_point,year))
	h_avg_SJ_mass_vs_diSJ_mass_CR.SetTitle("avg. superjet mass vs diSuperjet mass (%s, %s, %s, CR)"%(decay,mass_point,year))

	h_SJ_mass_AT1b.SetTitle("Superjet mass (%s, %s, %s, AT1b)"%(decay,mass_point,year))
	h_diSJ_mass_AT1b.SetTitle("diSuperjet mass (%s, %s, %s, AT1b)"%(decay,mass_point,year))
	h_avg_SJ_mass_vs_diSJ_mass_AT1b.SetTitle("avg. superjet mass vs diSuperjet mass (%s, %s, %s, AT1b)"%(decay,mass_point,year))

	h_SJ_mass_AT0b.SetTitle("Superjet mass (%s, %s, %s, AT0b)"%(decay,mass_point,year))
	h_diSJ_mass_AT0b.SetTitle("diSuperjet mass (%s, %s, %s, AT0b)"%(decay,mass_point,year))
	h_avg_SJ_mass_vs_diSJ_mass_AT0b.SetTitle("avg. superjet mass vs diSuperjet mass (%s, %s, %s, AT0b)"%(decay,mass_point,year))

	h_totHT.SetTitle("Tot HT (%s, %s, %s)"%(decay,mass_point,year))
	h_totHT.Draw("HIST")
	c.SaveAs(plot_dir+"h_totHT_%s_%s_%s.png"%(decay,mass_point,years))

	h_SJ_mass_SR.Draw("HIST")
	c.SaveAs(plot_dir+"h_SJ_mass_%s_%s_%s_SR.png"%(decay,mass_point,years))
	h_diSJ_mass_SR.Draw("HIST")
	c.SaveAs(plot_dir+"h_diSJ_mass_%s_%s_%s_SR.png"%(decay,mass_point,years))
	h_avg_SJ_mass_vs_diSJ_mass_SR.Draw("colz")
	c.SaveAs(plot_dir+"h_SJ_mass_vs_diSJ_mass_%s_%s_%s_SR.png"%(decay,mass_point,years))


	h_SJ_mass_CR.Draw("HIST")
	c.SaveAs(plot_dir+"h_SJ_mass_%s_%s_%s_CR.png"%(decay,mass_point,years))
	h_diSJ_mass_CR.Draw("HIST")
	c.SaveAs(plot_dir+"h_diSJ_mass_%s_%s_%s_CR.png"%(decay,mass_point,years))
	h_avg_SJ_mass_vs_diSJ_mass_CR.Draw("colz")
	c.SaveAs(plot_dir+"h_SJ_mass_vs_diSJ_mass_%s_%s_%s_CR.png"%(decay,mass_point,years))


	h_SJ_mass_AT1b.Draw("HIST")
	c.SaveAs(plot_dir+"h_SJ_mass_%s_%s_%s_AT1b.png"%(decay,mass_point,years))
	h_diSJ_mass_AT1b.Draw("HIST")
	c.SaveAs(plot_dir+"h_diSJ_mass_%s_%s_%s_AT1b.png"%(decay,mass_point,years))
	h_avg_SJ_mass_vs_diSJ_mass_AT1b.Draw("colz")
	c.SaveAs(plot_dir+"h_SJ_mass_vs_diSJ_mass_%s_%s_%s_AT1b.png"%(decay,mass_point,years))

	h_SJ_mass_AT0b.Draw("HIST")
	c.SaveAs(plot_dir+"h_SJ_mass_%s_%s_%s_AT0b.png"%(decay,mass_point,years))
	h_diSJ_mass_AT0b.Draw("HIST")
	c.SaveAs(plot_dir+"h_diSJ_mass_%s_%s_%s_AT0b.png"%(decay,mass_point,years))
	h_avg_SJ_mass_vs_diSJ_mass_AT0b.Draw("colz")
	c.SaveAs(plot_dir+"h_SJ_mass_vs_diSJ_mass_%s_%s_%s_AT0b.png"%(decay,mass_point,years))


	return
if __name__=="__main__":
	years = ["2015","2016","2017","2018"]
	decays = ["WBWB","HTHT","ZTZT","WBHT","WBZT","HTZT"]
	mass_points = ["Suu4_chi1", "Suu4_chi1p5", "Suu5_chi1", "Suu5_chi1p5", "Suu5_chi2", "Suu6_chi1","Suu6_chi1p5", "Suu6_chi2",
	"Suu6_chi2p5", "Suu7_chi1","Suu7_chi1p5","Suu7_chi2", "Suu7_chi2p5", "Suu7_chi3","Suu8_chi1", "Suu8_chi1p5","Suu8_chi2","Suu8_chi2p5","Suu8_chi3" ]   ## copy this from the LPC 
	
	#### need to change this to open up the processed files

	for year in years:
		for mass_point in mass_points:
			# create combined Suu mass decays (all decay modes)
			try:

				## TODO create this function that creates combined plots
				make_combined_plots(inFileName, year, mass_point, )
			except:
				print("ERROR: Failed to create the combined plot for %s + %s"%(mass_point,year))
			for decay in decays:
				inFile_dir = "/Users/ethan/Documents/rootFiles/signalFiles/"
				inFileName = inFile_dir + "%s_%s_%s_processed.root"%(mass_point,decay,year)
				make_plots(inFileName, year,decay,mass_point, )






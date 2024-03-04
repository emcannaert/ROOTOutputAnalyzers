import sys,os,time
import numpy as np
import ROOT
import ast
from print_nice_hist import print_nice_hist
from return_signal_SF import return_signal_SF
### linearize_final_plots.py
### written by Ethan Cannaert, October 2023
### requires locations of input root files for each background/signal contribution (QCD1000to1500, QCD1500to2000, QCD2000toInf, TTbar, sig MC)

### open each file and get the histograms from each
### scale histograms relative to the appropriate luminosity 
### get superbin indices and find "center" of each superbin, sort bin by these centers 
### loop over each superbin and add together the corresponding histogram bins, this becomes an entry in a 1D ( 22x20 = 440 bin) distribution for each contribution that goes to Combine
### in the end there will be a histogram for QCD, TTbar, signal MC, and then data 

### UPDATE: 31 October 2023, this has been updated to run each systematic. For each year, this opens up the QCD,TTbar, and data histograms and 
### writes out a single root file with the up/down/nom for each systematic
### still have to adapt this to run for signal - a separate look would be done that runs over all signal files,years, and systematics, and makes 
### a root file with the linearized histograms 

### update 10 Nov, will create a method that saves plots (and histograms) of the individual and combined 2D distributions in the SR and 



### change the lists to instead be dictionaries?
class linearized_plot:
	n_bins_x = 22
	n_bins_y = 20
	def __init__(self, year,signal_type):
		self.year   = year
		self.MC_root_file_home      = "/Users/ethan/Documents/rootFiles/processedRootFiles/"
		self.data_root_file_home    = "/Users/ethan/Documents/rootFiles/processedRootFilesData/"

		self.index_file_home     = "/Users/ethan/Documents/rootFiles/statisticalUncertaintyStudyAlt/txtfiles"
		self.output_file_home    = "/Users/ethan/Documents/rootFiles/finalCombineFiles"
		self.final_plot_home     = "/Users/ethan/Documents/plots/combinePlots"

		self.superbin_indices        = self.load_superbin_indices()
		self.signal_type = signal_type   # label for the signal mass point

		self.non_data_systematics = ["bTagSF", "PUSF"]
		#self.systematics = ["nom","JER","JEC"] ### NEEDS TO BE CHANGED BACK
		self.systematics = ["nom","bTagSF","PUSF"]
		self.QCD_hist_SR = []
		self.TTbar_hist_SR = []
		self.ST_hist_SR = []
		self.data_hist_SR = []
		self.signal_hist_SR = []

		self.QCD_hist_CR = []
		self.TTbar_hist_CR = []
		self.ST_hist_CR = []
		self.data_hist_CR = []
		self.signal_hist_CR = []

		self.TTbar_hist_antiTagCR = []
		self.ST_hist_antiTagCR = []
		self.QCD_hist_antiTagCR   = []
		self.data_hist_antiTagCR  = []
		self.signal_hist_antiTagCR  = []

		self.TTbar_hist_antiTag_1b = []
		self.ST_hist_antiTag_1b = []
		self.QCD_hist_antiTag_1b   = []
		self.data_hist_antiTag_1b  = []
		self.signal_hist_antiTag_1b  = []


		for systematic in self.systematics:
			self.QCD_hist_SR.extend(self.load_QCD_hists("SR",systematic))
			self.TTbar_hist_SR.extend(self.load_ttbar_hist("SR",systematic))
			self.ST_hist_SR.extend(self.load_ST_hists("SR",systematic))
			self.signal_hist_SR.extend(self.load_signal_hist("SR",systematic))

			self.QCD_hist_CR.extend(self.load_QCD_hists("CR",systematic))
			self.TTbar_hist_CR.extend(self.load_ttbar_hist("CR",systematic))
			self.ST_hist_CR.extend(self.load_ST_hists("CR",systematic))
			self.signal_hist_CR.extend(self.load_signal_hist("CR",systematic))

			self.QCD_hist_antiTagCR.extend(self.load_QCD_hists("antiTagCR",systematic))
			self.TTbar_hist_antiTagCR.extend(self.load_ttbar_hist("antiTagCR",systematic))
			self.ST_hist_antiTagCR.extend(self.load_ST_hists("antiTagCR",systematic))
			self.signal_hist_antiTagCR.extend(self.load_signal_hist("antiTagCR",systematic))

			self.QCD_hist_antiTag_1b.extend(self.load_QCD_hists("antiTag_1b",systematic))
			self.TTbar_hist_antiTag_1b.extend(self.load_ttbar_hist("antiTag_1b",systematic))
			self.ST_hist_antiTag_1b.extend(self.load_ST_hists("antiTag_1b",systematic))
			self.signal_hist_antiTag_1b.extend(self.load_signal_hist("antiTag_1b",systematic))


			if systematic not in self.non_data_systematics:
				self.data_hist_SR.extend(self.load_data_hists("SR",systematic))
				self.data_hist_CR.extend(self.load_data_hists("CR",systematic))
				self.data_hist_antiTagCR.extend(self.load_data_hists("antiTagCR",systematic))
				self.data_hist_antiTag_1b.extend(self.load_data_hists("antiTag_1b",systematic))

		self.write_2D_distribution(self.load_QCD_hists("SR","nom"), "Average Superjet Mass vs diSuperjet Mass", "QCD","SR")
		self.write_2D_distribution(self.load_QCD_hists("CR","nom"),"Average Superjet Mass vs diSuperjet Mass","QCD","CR")
		self.write_2D_distribution(self.load_ttbar_hist("SR","nom"), "Average Superjet Mass vs diSuperjet Mass","TTbar","SR")
		self.write_2D_distribution(self.load_ttbar_hist("CR","nom"), "Average Superjet Mass vs diSuperjet Mass","TTbar","CR")

		self.write_2D_distribution(self.load_ttbar_hist("antiTagCR","nom"), "Average Superjet Mass vs diSuperjet Mass","TTbar","antiTagCR")
		self.write_2D_distribution(self.load_ttbar_hist("antiTag_1b","nom"), "Average Superjet Mass vs diSuperjet Mass","TTbar","antiTag_1b")

		self.write_2D_distribution(self.load_QCD_hists("antiTagCR","nom"), "Average Superjet Mass vs diSuperjet Mass", "QCD","antiTagCR")
		self.write_2D_distribution(self.load_QCD_hists("antiTag_1b","nom"),"Average Superjet Mass vs diSuperjet Mass","QCD","antiTag_1b")

		self.write_2D_distribution(self.load_ST_hists("SR","nom"), "Average Superjet Mass vs diSuperjet Mass","ST","SR")
		self.write_2D_distribution(self.load_ST_hists("CR","nom"), "Average Superjet Mass vs diSuperjet Mass","ST","CR")
		self.write_2D_distribution(self.load_ST_hists("antiTagCR","nom"), "Average Superjet Mass vs diSuperjet Mass", "ST","antiTagCR")
		self.write_2D_distribution(self.load_ST_hists("antiTag_1b","nom"),"Average Superjet Mass vs diSuperjet Mass","ST","antiTag_1b")


		combined_hist_SR = self.load_ttbar_hist("SR","nom")[0]
		combined_hist_SR.Add(self.load_QCD_hists("SR","nom")[0])
		combined_hist_SR.Add(self.load_ST_hists("SR","nom")[0])

		combined_hist_CR =  self.load_ttbar_hist("CR","nom")[0]
		combined_hist_CR.Add(self.load_QCD_hists("CR","nom")[0])
		combined_hist_CR.Add(self.load_ST_hists("CR","nom")[0])

		combined_hist_antiTagCR =  self.load_ttbar_hist("antiTagCR","nom")[0]
		combined_hist_antiTagCR.Add(self.load_QCD_hists("antiTagCR","nom")[0])
		combined_hist_antiTagCR.Add(self.load_ST_hists("antiTagCR","nom")[0])

		combined_hist_antiTag_1b =  self.load_ttbar_hist("antiTag_1b","nom")[0]
		combined_hist_antiTag_1b.Add(self.load_QCD_hists("antiTag_1b","nom")[0])
		combined_hist_antiTag_1b.Add(self.load_ST_hists("antiTag_1b","nom")[0])


		self.write_2D_distribution([combined_hist_SR], "Average Superjet Mass vs diSuperjet Mass", "BR-Combined","SR")
		self.write_2D_distribution([combined_hist_CR], "Average Superjet Mass vs diSuperjet Mass", "BR-Combined","CR")
		self.write_2D_distribution([combined_hist_antiTagCR], "Average Superjet Mass vs diSuperjet Mass", "BR-Combined","antiTagCR")
		self.write_2D_distribution([combined_hist_antiTag_1b], "Average Superjet Mass vs diSuperjet Mass", "BR-Combined","antiTag_1b")

		#now create linear plots that have all systematic plots inside

		self.QCD_linear_SR = []
		self.TTbar_linear_SR = []
		self.ST_linear_SR = []
		self.data_linear_SR = []
		self.signal_linear_SR = []

		self.QCD_linear_CR = []
		self.TTbar_linear_CR = []
		self.ST_linear_CR = []
		self.data_linear_CR = []
		self.signal_linear_CR = []

		self.QCD_linear_antiTagCR = []
		self.TTbar_linear_antiTagCR = []
		self.ST_linear_antiTagCR = []
		self.data_linear_antiTagCR = []
		self.signal_linear_antiTagCR  = []

		self.QCD_linear_antiTag_1b = []
		self.TTbar_linear_antiTag_1b = []
		self.ST_linear_antiTag_1b = []
		self.data_linear_antiTag_1b = []
		self.signal_linear_antiTag_1b = []


		for iii,systematic in enumerate(self.systematics):
			self.QCD_linear_SR.extend(self.linearize_plot(self.QCD_hist_SR[iii],"QCD","SR",systematic))
			self.TTbar_linear_SR.extend(self.linearize_plot(self.TTbar_hist_SR[iii],"TTbar","SR",systematic))
			self.ST_linear_SR.extend(self.linearize_plot(self.ST_hist_SR[iii],"ST","SR",systematic))
			self.signal_linear_SR.extend(self.linearize_plot(self.signal_hist_SR[iii],"signal","SR",systematic))

			self.QCD_linear_CR.extend(self.linearize_plot(self.QCD_hist_CR[iii],"QCD","CR",systematic))
			self.TTbar_linear_CR.extend(self.linearize_plot(self.TTbar_hist_CR[iii],"TTbar","CR",systematic))
			self.ST_linear_CR.extend(self.linearize_plot(self.ST_hist_CR[iii],"ST","CR",systematic))
			self.signal_linear_CR.extend(self.linearize_plot(self.signal_hist_CR[iii],"signal","CR",systematic))


			self.QCD_linear_antiTagCR.extend(self.linearize_plot(self.QCD_hist_antiTagCR[iii],"QCD","antiTagCR",systematic))
			self.TTbar_linear_antiTagCR.extend(self.linearize_plot(self.TTbar_hist_antiTagCR[iii],"TTbar","antiTagCR",systematic))
			self.ST_linear_antiTagCR.extend(self.linearize_plot(self.ST_hist_antiTagCR[iii],"ST","antiTagCR",systematic))
			self.signal_linear_antiTagCR.extend(self.linearize_plot(self.signal_hist_antiTagCR[iii],"signal","antiTagCR",systematic))


			self.QCD_linear_antiTag_1b.extend(self.linearize_plot(self.QCD_hist_antiTag_1b[iii],"QCD","antiTag_1b",systematic))
			self.TTbar_linear_antiTag_1b.extend(self.linearize_plot(self.TTbar_hist_antiTag_1b[iii],"TTbar","antiTag_1b",systematic))
			self.ST_linear_antiTag_1b.extend(self.linearize_plot(self.ST_hist_antiTag_1b[iii],"ST","antiTag_1b",systematic))
			self.signal_linear_antiTag_1b.extend(self.linearize_plot(self.signal_hist_antiTag_1b[iii],"signal","antiTag_1b",systematic))

			if systematic not in self.non_data_systematics:
				self.data_linear_SR.extend(self.linearize_plot(self.data_hist_SR[iii],"data","SR",systematic))
				self.data_linear_CR.extend(self.linearize_plot(self.data_hist_CR[iii],"data","CR",systematic))
				self.data_linear_antiTagCR.extend(self.linearize_plot(self.data_hist_antiTagCR[iii],"data","antiTagCR",systematic))
				self.data_linear_antiTag_1b.extend(self.linearize_plot(self.data_hist_antiTag_1b[iii],"data","antiTag_1b",systematic))

		self.print_dataMC_ratio_plots()

		self.write_histograms()
		self.print_histograms()
		#elf.sorted_superbin_indices = self.sort_superbin_indices()  # have to figure out how to do this ...



	def load_QCD_hists(self,region,systematic):
		"""
  								{ {3.87E+00, 2.89E+00, -99999., -99999., -99999.  },   // MSuu = 4 TeV  // convert this to a dictionary
                                  {1.37E+00, 1.19E+00, 8.67E-01, -99999., -99999. },   // MSuu = 5 Tev
                                  {2.82E-01, 2.58E-01, 2.20E-01, -99999., -99999. },   // MSuu = 6 TeV       
                                  {2.01E-01, 1.89E-01, 1.71E-01, -99999., 1.31E-01},   // MSuu = 7 TeV
                                  {2.17E-02, 2.08E-02, 1.93E-02, -99999., 1.74E-02 }    // MSuu = 8 TeV   
		"""

		#ROOT.TH1.SetDefaultSumw2()
		#ROOT.TH2.SetDefaultSumw2()
		sys_suffix = [""]
		if systematic != "nom":
			sys_updown = ["%s_up"%systematic,"%s_down"%systematic]
		elif systematic == "nom":
			sys_updown = ["nom_"]
		SF_1000to1500 = {'2015':1.578683216 , '2016':1.482632755 , '2017':3.126481451 , '2018':4.289571744  }
		SF_1500to2000 = {'2015': 0.2119142341, '2016':0.195224041 , '2017':0.3197450474 , '2018':0.4947703875  }
		SF_2000toInf  = {'2015':0.08568186031 , '2016':0.07572795371 , '2017': 0.14306915, '2018':0.2132134533  }
		
		### make histogram paths
		hist_path_1000to1500 = self.MC_root_file_home+ "QCDMC1000to1500_%s_processed.root"%(self.year)
		hist_path_1500to2000 = self.MC_root_file_home+ "QCDMC1500to2000_%s_processed.root"%(self.year)
		hist_path_2000toInf  = self.MC_root_file_home+ "QCDMC2000toInf_%s_processed.root"%(self.year)

		all_combined_QCD_hist = []
		for sys_str in sys_updown:

			### get each histogram
			hist_name = "%s/h_MSJ_mass_vs_MdSJ_%s"%(sys_str,region )
			TH2_file_1000to1500 = ROOT.TFile.Open(hist_path_1000to1500,"READ")
			TH2_hist_1000to1500 = TH2_file_1000to1500.Get(hist_name) 

			TH2_file_1500to2000 = ROOT.TFile.Open(hist_path_1500to2000,"READ")
			TH2_hist_1500to2000 = TH2_file_1500to2000.Get(hist_name) 

			TH2_file_2000toInf = ROOT.TFile.Open(hist_path_2000toInf,"READ")
			TH2_hist_2000toInf = TH2_file_2000toInf.Get(hist_name) 

			TH2_hist_1000to1500.SetDirectory(0)   # histograms lose their references when the file destructor is called
			TH2_hist_1500to2000.SetDirectory(0)   # histograms lose their references when the file destructor is called
			TH2_hist_2000toInf.SetDirectory(0)   # histograms lose their references when the file destructor is called

			### scale each histogram
			TH2_hist_1000to1500.Scale(SF_1000to1500[self.year])
			TH2_hist_1500to2000.Scale(SF_1500to2000[self.year])
			TH2_hist_2000toInf.Scale(SF_2000toInf[self.year])

			combined_QCD_hist = ROOT.TH2F("combined_QCD_%s"%sys_str, ("QCD (HT1000-Inf) Events in the %s (%s) (%s)"%(region, year, sys_str)), 22,1250., 9500, 20, 500, 3500)
			combined_QCD_hist.Add(TH2_hist_1000to1500)
			combined_QCD_hist.Add(TH2_hist_1500to2000)
			combined_QCD_hist.Add(TH2_hist_2000toInf)

			combined_QCD_hist.SetDirectory(0)   # histograms lose their references when the file destructor is called
			all_combined_QCD_hist.append(combined_QCD_hist)

		ROOT.TH1.AddDirectory(False)

		return all_combined_QCD_hist   # load in QCD histograms, scale them, add them together, and return their sum
	def load_ttbar_hist(self,region,systematic):


		#ROOT.TH1.SetDefaultSumw2()
		#ROOT.TH2.SetDefaultSumw2()
		SF_TTToHadronic= {'2015':0.075592 , '2016':0.05808655696 , '2017':0.06651018525 , '2018': 0.06588049107 }
		SF_TTToSemiLeptonic= {'2015':0.05395328118 , '2016':0.04236184005 , '2017':0.04264829286 , '2018': 0.04563489275 }
		SF_TTToLeptonic= {'2015':0.0459517611 , '2016':0.03401684391 , '2017':0.03431532926 , '2018': 0.03617828025 }

		hist_path_TTToHadronic = self.MC_root_file_home+ "TTToHadronicMC_%s_processed.root"%(self.year)
		hist_path_TTToSemiLeptonic = self.MC_root_file_home+ "TTToSemiLeptonicMC_%s_processed.root"%(self.year)
		hist_path_TTToLeptonic = self.MC_root_file_home+ "TTToLeptonicMC_%s_processed.root"%(self.year)

		sys_suffix = [""]
		if systematic != "nom":
			sys_updown = ["%s_up"%systematic,"%s_down"%systematic]
		elif systematic == "nom":
			sys_updown = ["nom_"]

		all_combined_TTbar_hist = []
		for sys_str in sys_updown:

			hist_name_TTbar = "%s/h_MSJ_mass_vs_MdSJ_%s"%(sys_str,region )
			TH2_file_TTToHadronic = ROOT.TFile.Open(hist_path_TTToHadronic,"READ")
			TH2_file_TTToSemiLeptonic = ROOT.TFile.Open(hist_path_TTToSemiLeptonic,"READ")
			TH2_file_TTToLeptonic = ROOT.TFile.Open(hist_path_TTToLeptonic,"READ")

			TH2_hist_TTToHadronic = TH2_file_TTToHadronic.Get(hist_name_TTbar) 
			TH2_hist_TTToSemiLeptonic = TH2_file_TTToSemiLeptonic.Get(hist_name_TTbar) 
			TH2_hist_TTToLeptonic = TH2_file_TTToLeptonic.Get(hist_name_TTbar) 

			TH2_hist_TTToHadronic.Scale(SF_TTToHadronic[self.year])
			TH2_hist_TTToHadronic.SetDirectory(0)   # histograms lose their references when the file destructor is called

			TH2_hist_TTToSemiLeptonic.Scale(SF_TTToSemiLeptonic[self.year])
			TH2_hist_TTToSemiLeptonic.SetDirectory(0)   # histograms lose their references when the file destructor is called

			TH2_hist_TTToLeptonic.Scale(SF_TTToLeptonic[self.year])
			TH2_hist_TTToLeptonic.SetDirectory(0)   # histograms lose their references when the file destructor is called
			
			TH2_hist_TTToHadronic.Add(TH2_hist_TTToLeptonic)
			TH2_hist_TTToHadronic.Add(TH2_hist_TTToSemiLeptonic)
			TH2_hist_TTToHadronic.SetTitle("combined TTbar MC (%s) (%s) (%s)"%(self.year,region, sys_str))
			all_combined_TTbar_hist.append(TH2_hist_TTToHadronic)

		return all_combined_TTbar_hist  # load in TTbar historam, scale it, and return this version

	def load_signal_hist(self,region,systematic):

		#ROOT.TH1.SetDefaultSumw2()
		#ROOT.TH2.SetDefaultSumw2()
		# dictionary for signal MC 
		SF_sign = return_signal_SF.return_signal_SF(self.year,self.signal_type)

		hist_path_signal = self.MC_root_file_home+ "%s_%s_%s_processed.root"%(self.signal_type, self.year,systematic)
		print("Loading signal histogram ", hist_path_signal)

		sys_suffix = [""]
		if systematic != "nom":
			sys_updown = ["%s_up"%systematic,"%s_down"%systematic]
		elif systematic == "nom":
			sys_updown = ["nom_"]

		all_combined_signal_hist = []
		for sys_str in sys_updown:
			hist_name_signal = "%s/h_MSJ_mass_vs_MdSJ_%s"%(sys_str,region )
			TH2_file_signal= ROOT.TFile.Open(hist_path_signal,"READ")

			TH2_hist_signal = TH2_file_signal.Get(hist_name_signal) 
			print("Loading histogram ", hist_name_signal)

			TH2_hist_signal.Scale(SF_sign)
			TH2_hist_signal.SetDirectory(0)   # histograms lose their references when the file destructor is called

			TH2_hist_signal.SetTitle("combined TTbar MC (%s) (%s) (%s)"%(self.year,region, sys_str))
			all_combined_signal_hist.append(TH2_hist_signal)
		print("Loaded all signal histograms")
		return all_combined_signal_hist  # load in TTbar historam, scale it, and return this version





	def load_ST_hists(self,region,systematic):

		#ROOT.TH1.SetDefaultSumw2()
		#ROOT.TH2.SetDefaultSumw2()
		linear_plot_size = len(self.superbin_indices)

		ST_t_channel_top_5f_SF= {'2015':0.0409963154 , '2016':0.03607115071 , '2017':0.03494669125 , '2018': 0.03859114659 }
		ST_t_channel_antitop_5f_SF= {'2015':0.05673857623 , '2016':0.04102705994 , '2017':0.04238814865 , '2018': 0.03606630944 }
		ST_s_channel_4f_hadrons_SF= {'2015':0.04668187234 , '2016':0.03564988679 , '2017':0.03985938616 , '2018': 0.04102795437 }
		ST_s_channel_4f_leptons_SF= {'2015':0.01323030083 , '2016':0.01149139097 , '2017':0.01117527734 , '2018': 0.01155448784 }
		ST_tW_antitop_5f_SF= {'2015':0.2967888696 , '2016':0.2301666797, '2017':0.2556495594 , '2018': 0.2700032391 }
		ST_tW_top_5f_SF= {'2015':0.2962796522 , '2016':0.2355829386 , '2017':0.2563403788 , '2018': 0.2625270613 }

		hist_path_ST_t_channel_top_5f 	= self.MC_root_file_home+ "ST_t-channel-top_inclMC_%s_processed.root"%(self.year)
		hist_path_ST_t_channel_antitop_5f = self.MC_root_file_home+ "ST_t-channel-antitop_inclMC_%s_processed.root"%(self.year)
		hist_path_ST_s_channel_4f_hadrons = self.MC_root_file_home+ "ST_s-channel-hadronsMC_%s_processed.root"%(self.year)
		hist_path_ST_s_channel_4f_leptons = self.MC_root_file_home+ "ST_s-channel-leptonsMC_%s_processed.root"%(self.year)
		hist_path_ST_tW_antitop_5f		= self.MC_root_file_home+ "ST_tW-antiTop_inclMC_%s_processed.root"%(self.year)
		hist_path_ST_tW_top_5f 			= self.MC_root_file_home+ "ST_tW-top_inclMC_%s_processed.root"%(self.year)

		sys_suffix = [""]
		if systematic != "nom":
			sys_updown = ["%s_up"%systematic,"%s_down"%systematic]
		elif systematic == "nom":
			sys_updown = ["nom_"]

		all_combined_ST_hist = []
		for sys_str in sys_updown:

			hist_name_ST = "%s/h_MSJ_mass_vs_MdSJ_%s"%(sys_str,region )


			TH2_file_ST_t_channel_top_5f 	 = ROOT.TFile.Open(hist_path_ST_t_channel_top_5f,"READ")
			TH2_file_ST_t_channel_antitop_5f = ROOT.TFile.Open(hist_path_ST_t_channel_antitop_5f,"READ")
			TH2_file_ST_s_channel_4f_hadrons = ROOT.TFile.Open(hist_path_ST_s_channel_4f_hadrons,"READ")
			TH2_file_ST_s_channel_4f_leptons = ROOT.TFile.Open(hist_path_ST_s_channel_4f_leptons,"READ")
			TH2_file_ST_tW_antitop_5f 		 = ROOT.TFile.Open(hist_path_ST_tW_antitop_5f,"READ")
			TH2_file_ST_tW_top_5f			 = ROOT.TFile.Open(hist_path_ST_tW_top_5f,"READ")

			TH2_hist_ST_t_channel_top_5f 	 = TH2_file_ST_t_channel_top_5f.Get(hist_name_ST) 
			TH2_hist_ST_t_channel_antitop_5f = TH2_file_ST_t_channel_antitop_5f.Get(hist_name_ST) 
			TH2_hist_ST_s_channel_4f_hadrons = TH2_file_ST_s_channel_4f_hadrons.Get(hist_name_ST) 
			TH2_hist_ST_s_channel_4f_leptons = TH2_file_ST_s_channel_4f_leptons.Get(hist_name_ST) 
			TH2_hist_ST_tW_antitop_5f 		 = TH2_file_ST_tW_antitop_5f.Get(hist_name_ST) 
			TH2_hist_ST_tW_top_5f			 = TH2_file_ST_tW_top_5f.Get(hist_name_ST) 

			TH2_hist_ST_t_channel_top_5f.Scale(ST_t_channel_top_5f_SF[self.year])
			TH2_hist_ST_t_channel_top_5f.SetDirectory(0)   # histograms lose their references when the file destructor is called

			TH2_hist_ST_t_channel_antitop_5f.Scale(ST_t_channel_antitop_5f_SF[self.year])
			TH2_hist_ST_t_channel_antitop_5f.SetDirectory(0)   # histograms lose their references when the file destructor is called

			TH2_hist_ST_s_channel_4f_hadrons.Scale(ST_s_channel_4f_hadrons_SF[self.year])
			TH2_hist_ST_s_channel_4f_hadrons.SetDirectory(0)   # histograms lose their references when the file destructor is called
			
			TH2_hist_ST_s_channel_4f_leptons.Scale(ST_s_channel_4f_leptons_SF[self.year])
			TH2_hist_ST_s_channel_4f_leptons.SetDirectory(0)   # histograms lose their references when the file destructor is called

			TH2_hist_ST_tW_antitop_5f.Scale(ST_tW_antitop_5f_SF[self.year])
			TH2_hist_ST_tW_antitop_5f.SetDirectory(0)   # histograms lose their references when the file destructor is called

			TH2_hist_ST_tW_top_5f.Scale(ST_tW_top_5f_SF[self.year])
			TH2_hist_ST_tW_top_5f.SetDirectory(0)   # histograms lose their references when the file destructor is called

			combined_ST_hist = ROOT.TH2F("combined_ST_%s"%region,"combined linearized Single Top (%s) (%s) (%s)"%(self.year,region,sys_str),22,1250., 9500, 20, 500, 3500)
			combined_ST_hist.Add(TH2_hist_ST_t_channel_top_5f)
			combined_ST_hist.Add(TH2_hist_ST_t_channel_antitop_5f)
			combined_ST_hist.Add(TH2_hist_ST_s_channel_4f_hadrons)
			combined_ST_hist.Add(TH2_hist_ST_s_channel_4f_leptons)
			combined_ST_hist.Add(TH2_hist_ST_tW_antitop_5f)
			combined_ST_hist.Add(TH2_hist_ST_tW_top_5f)

			all_combined_ST_hist.append(combined_ST_hist)

		return all_combined_ST_hist  # load in TTbar historam, scale it, and return this version

	def load_data_hists(self, region, systematic):
		#ROOT.TH1.SetDefaultSumw2()
		#ROOT.TH2.SetDefaultSumw2()
		data_blocks = []
		if self.year == "2015":
			data_blocks = ["dataB-ver1","dataB-ver2","dataC-HIPM","dataD-HIPM","dataE-HIPM","dataF-HIPM"]
		elif self.year == "2016":
			data_blocks = ["dataF", "dataG", "dataH"]
		elif self.year == "2017":
			data_blocks = ["dataB","dataC","dataD","dataE", "dataF"]
		elif self.year == "2018":
			data_blocks = ["dataA","dataB","dataC","dataD"]

		sys_suffix = [""]
		if systematic != "nom":
			sys_updown = ["%s_up"%systematic,"%s_down"%systematic]
		elif systematic == "nom":
			sys_updown = ["nom_"]

		all_combined_data_hist = []
		for sys_str in sys_updown:
			combined_data_hist = ROOT.TH2F("combined_data%s"%region, ("data events in the %s (%s)"%(year,region)), 22,1250., 9500, 20, 500, 3500)

			#JetHT_"+ *dataBlock+"_"+*year+"_processed.root   -> naming scheme
			for data_block in data_blocks:
				#hist_path = "/Users/ethan/Documents/rootFiles/processedRootFiles/%s_%s_nom_processed.root"%(data_block,self.year)
				hist_path_data = self.MC_root_file_home+ "%s_%s_processed.root"%(data_block,self.year)
				TH2_file_data = ROOT.TFile.Open(hist_path_data,"READ")

				hist_name_data = "h_MSJ_mass_vs_MdSJ_%s"%region 
				TH2_hist_data = TH2_file_data.Get(sys_str+"/"+hist_name_data) 
				combined_data_hist.Add(TH2_hist_data)

			ROOT.TH1.AddDirectory(False)
			combined_data_hist.SetDirectory(0)   # histograms lose their references when the file destructor is called
			all_combined_data_hist.append(combined_data_hist)
		return all_combined_data_hist  # load in TTbar historam, scale it, and return this version


	### now the scale factors are applied, so you'll see few events in bins
	def linearize_plot(self, _hist,BR_type,region,systematic): # take in a histogram and linearize it   TODO: is this working correctly? there are ~350 bins in each year, is the the correct number?
		
		sys_suffix = [""]
		if systematic != "nom":
			sys_updown = ["%s_up"%systematic,"%s_down"%systematic]
		elif systematic == "nom":
			sys_updown = ["nom_"]
		all_linear_plots = []
		for sys_str in sys_updown:
			linear_plot_size = len(self.superbin_indices)  
			linear_plot = ROOT.TH1D("%s"%BR_type,"linearized %s in the %s (%s) (%s)"%(BR_type,region,year,sys_str),linear_plot_size,0,linear_plot_size)
			for superbin_index,superbin in enumerate(self.superbin_indices):
				total_counts = 0
				for _tuple in superbin:
					total_counts+=_hist.GetBinContent(_tuple[0],_tuple[1])
				linear_plot.SetBinContent(superbin_index,total_counts)
			ROOT.TH1.AddDirectory(False)
			linear_plot.SetDirectory(0)   # histograms lose their references when the file destructor is called
			all_linear_plots.append(linear_plot)
		return all_linear_plots

	def write_histograms(self):

		combine_file_name = self.output_file_home + "/combine_%s_%s.root"%(year,signal_type)   
		combine_file = ROOT.TFile(combine_file_name,"RECREATE")
		combine_file.cd()


		for iii,systematic in enumerate(self.systematics):
			sys_suffix = [""]
			if systematic != "nom":
				sys_updown = ["%s_up"%systematic,"%s_down"%systematic]
			elif systematic == "nom":
				sys_updown = ["nom"]
			for jjj,sys_str in enumerate(sys_updown):
				combine_file.cd()
				ROOT.gDirectory.mkdir(sys_str)
				combine_file.cd(sys_str)

				ROOT.gDirectory.mkdir("SR")
				combine_file.cd()
				combine_file.cd("%s/SR"%sys_str)  ## can't seem to find these .... 
				self.QCD_linear_SR[iii+jjj].Write()
				self.TTbar_linear_SR[iii+jjj].Write()
				self.ST_linear_SR[iii+jjj].Write()
				self.signal_linear_SR[iii+jjj].Write()

				combine_file.cd()
				combine_file.cd(sys_str)
				ROOT.gDirectory.mkdir("CR")
				combine_file.cd()
				combine_file.cd("%s/CR"%sys_str)

				self.QCD_linear_CR[iii+jjj].Write()
				self.TTbar_linear_CR[iii+jjj].Write()
				self.ST_linear_CR[iii+jjj].Write()
				self.signal_linear_CR[iii+jjj].Write()

				combine_file.cd()
				combine_file.cd(sys_str)
				ROOT.gDirectory.mkdir("AT0b")
				combine_file.cd()
				combine_file.cd("%s/AT0b"%sys_str)

				self.QCD_linear_antiTagCR[iii+jjj].Write()
				self.TTbar_linear_antiTagCR[iii+jjj].Write()
				self.ST_linear_antiTagCR[iii+jjj].Write()
				self.signal_linear_antiTagCR[iii+jjj].Write()

				combine_file.cd()
				combine_file.cd(sys_str)
				ROOT.gDirectory.mkdir("AT1b")
				combine_file.cd()
				combine_file.cd("%s/AT1b"%sys_str)

				self.QCD_linear_antiTag_1b[iii+jjj].Write()
				self.TTbar_linear_antiTag_1b[iii+jjj].Write()
				self.ST_linear_antiTag_1b[iii+jjj].Write()
				self.signal_linear_antiTag_1b[iii+jjj].Write()

				if systematic not in self.non_data_systematics:
					self.data_linear_SR[iii+jjj].Write()
					self.data_linear_CR[iii+jjj].Write()
					self.data_linear_antiTagCR[iii+jjj].Write()
					self.data_linear_antiTag_1b[iii+jjj].Write()
		return 
	def print_histograms(self):   #TODO: add signal and data olots here 
		c = ROOT.TCanvas("c", "canvas", 1000, 1050)
		for iii,systematic in enumerate(self.systematics):
			sys_suffix = [""]
			if systematic != "nom":
				sys_updown = ["%s_up"%systematic,"%s_down"%systematic]
			elif systematic == "nom":
				sys_updown = ["nom"]
			for jjj,sys_str in enumerate(sys_updown):

				# SR
				self.QCD_linear_SR[iii+jjj].Draw()
				c.SaveAs(self.final_plot_home+"/QCD_linear_%s_%s_SR.png"%(self.year,sys_str))

				self.TTbar_linear_SR[iii+jjj].Draw()
				c.SaveAs(self.final_plot_home+"/TTbar_linear_%s_%s_SR.png"%(self.year,sys_str))
				
				self.ST_linear_SR[iii+jjj].Draw()
				c.SaveAs(self.final_plot_home+"/ST_linear_%s_%s_SR.png"%(self.year,sys_str))


				# CR
				self.QCD_linear_CR[iii+jjj].Draw()
				c.SaveAs(self.final_plot_home+"/QCD_linear_%s_%s_CR.png"%(self.year,sys_str))

				self.TTbar_linear_CR[iii+jjj].Draw()
				c.SaveAs(self.final_plot_home+"/TTbar_linear_%s_%s_CR.png"%(self.year,sys_str))

				self.ST_linear_CR[iii+jjj].Draw()
				c.SaveAs(self.final_plot_home+"/ST_linear_%s_%s_CR.png"%(self.year,sys_str))

				
				# 0b anti-tagged region
				self.QCD_linear_antiTagCR[iii+jjj].Draw()
				c.SaveAs(self.final_plot_home+"/QCD_linear_%s_%s_antiTagCR.png"%(self.year,sys_str))

				self.TTbar_linear_antiTagCR[iii+jjj].Draw()
				c.SaveAs(self.final_plot_home+"/TTbar_linear_%s_%s_antiTagCR.png"%(self.year,sys_str))

				self.ST_linear_antiTagCR[iii+jjj].Draw()
				c.SaveAs(self.final_plot_home+"/ST_linear_%s_%s_antiTagCR.png"%(self.year,sys_str))


				# 1b anti-tagged region
				self.QCD_linear_antiTag_1b[iii+jjj].Draw()
				c.SaveAs(self.final_plot_home+"/QCD_linear_%s_%s_antiTag_1b.png"%(self.year,sys_str))

				self.TTbar_linear_antiTag_1b[iii+jjj].Draw()
				c.SaveAs(self.final_plot_home+"/TTbar_linear_%s_%s_antiTag_1b.png"%(self.year,sys_str))

				self.ST_linear_antiTag_1b[iii+jjj].Draw()
				c.SaveAs(self.final_plot_home+"/ST_linear_%s_%s_antiTag_1b.png"%(self.year,sys_str))

				

				if systematic not in self.non_data_systematics:
					self.data_linear_antiTag_1b[iii+jjj].Draw()
					c.SaveAs(self.final_plot_home+"/data_linear_%s_%s_antiTag_1b.png"%(self.year,sys_str))
					self.data_linear_antiTagCR[iii+jjj].Draw()
					c.SaveAs(self.final_plot_home+"/data_linear_%s_%s_antiTagCR.png"%(self.year,sys_str))
					self.data_linear_CR[iii+jjj].Draw()
					c.SaveAs(self.final_plot_home+"/data_linear_%s_%s_CR.png"%(self.year,sys_str))
					self.data_linear_SR[iii+jjj].Draw()
					c.SaveAs(self.final_plot_home+"/data_linear_%s_%s_SR.png"%(self.year,sys_str))

		return
	def write_2D_distribution(self,hist, title, sample, region):   #TODO: add signal and data olots here 
		c = ROOT.TCanvas("c", "canvas", 1000, 1050)

		outputPath = "/Users/ethan/Documents/plots/randomPlots/2D-Distribution-Plots"
		hist=hist[0]
		print_nice_hist.print_nice_hist(hist= hist, hist_file_path = "" , output_dir=outputPath, hist_name = hist.GetName(), hist_title=title, draw_option="colz", year =self.year,systematic="",sample=sample, region=region,xtitle="diSuperjet Mass [GeV]", ytitle = "Avg Superjet Mass [GeV]")
		
		#c.SaveAs(self.final_plot_home+"/TTbar_linear_%s_%s_CR.png"%(self.year,sys_str))

		return
	def load_superbin_indices(self,region="SR"):    # load in the superbin indices (located in a text file )
		_superbin_indices = []
		open_file = open(self.index_file_home+"/superbin_indices.txt","r")
		for line in open_file:
			columns = line.split('/')
			if columns[0] == self.year and columns[1] == region:
				_superbin_indices = columns[2]
		return ast.literal_eval(_superbin_indices)
	def sorted_superbin_indices(self):
		_sorted_superbin_indices = []
		average_superbin_bin_x     = []
		average_superbin_bin_y     = []
		for superbin_index,superbin in enumerate(self.superbin_indices):
			avg_x = 0
			avg_y = 0
			n_bins = 0
			for _tuple in superbin:
				avg_x += _tuple[0]
				avg_y += _tuple[1]
				n_bins+=1
			avg_x/=n_bins
			avg_y/=n_bins
			average_superbin_bin_x.append(avg_x)
			average_superbin_bin_y.append(avg_y)

			#sort by x bin and then sort by y bin 

		#sort by y and then sort by x? hpw

		return _sorted_superbin_indices


	def print_dataMC_ratio_plots(self):
		"""
			self.QCD_linear_SR.extend(self.linearize_plot(self.QCD_hist_SR[iii],"QCD","SR",systematic))
			self.TTbar_linear_SR.extend(self.linearize_plot(self.TTbar_hist_SR[iii],"TTbar","SR",systematic))

			self.QCD_linear_CR.extend(self.linearize_plot(self.QCD_hist_CR[iii],"QCD","CR",systematic))
			self.TTbar_linear_CR.extend(self.linearize_plot(self.TTbar_hist_CR[iii],"TTbar","CR",systematic))

			self.data_linear_SR.extend(self.linearize_plot(self.data_hist_SR[iii],"data","SR",systematic))
			self.data_linear_CR.extend(self.linearize_plot(self.data_hist_CR[iii],"data","CR",systematic))


		"""


		plot_home = "/Users/ethan/Documents/plots/ratioPlots/"
		c = ROOT.TCanvas("c", "canvas", 1000, 1050)
		linear_plot_size = len(self.superbin_indices) 
		combined_BR_SR = ROOT.TH1D("combined_BR_SR","linearized BR in the SR (%s)"%(year),linear_plot_size,0,linear_plot_size)

		combined_BR_SR.Add(self.QCD_linear_SR[0])
		combined_BR_SR.Add(self.TTbar_linear_SR[0])


		combined_BR_CR = ROOT.TH1D("combined_BR_CR","linearized BR in the CR (%s)"%(year),linear_plot_size,0,linear_plot_size)

		combined_BR_CR.Add(self.QCD_linear_CR[0])
		combined_BR_CR.Add(self.TTbar_linear_CR[0])

		combined_BR_antiTagCR = ROOT.TH1D("combined_BR_antiTagCR","linearized BR in the antiTag (0b) CR (%s)"%(year),linear_plot_size,0,linear_plot_size)

		combined_BR_antiTagCR.Add(self.QCD_linear_antiTagCR[0])
		combined_BR_antiTagCR.Add(self.TTbar_linear_antiTagCR[0])

		combined_BR_antiTag_1b = ROOT.TH1D("combined_BR_antiTag_1b","linearized BR in the antiTag 1b CR (%s)"%(year),linear_plot_size,0,linear_plot_size)

		combined_BR_antiTag_1b.Add(self.QCD_linear_antiTag_1b[0])
		combined_BR_antiTag_1b.Add(self.TTbar_linear_antiTag_1b[0])


		combined_BR_SR.SetLineColor(ROOT.kRed)
		combined_BR_CR.SetLineColor(ROOT.kRed)
		combined_BR_antiTagCR.SetLineColor(ROOT.kRed)
		combined_BR_antiTag_1b.SetLineColor(ROOT.kRed)

		self.data_linear_SR[0].SetLineColor(ROOT.kBlue)
		self.data_linear_CR[0].SetLineColor(ROOT.kBlue)
		self.data_linear_antiTagCR[0].SetLineColor(ROOT.kBlue)
		self.data_linear_antiTag_1b[0].SetLineColor(ROOT.kBlue)

		rp_dataMC_SR = ROOT.TRatioPlot(self.data_linear_SR[0],combined_BR_SR);   ## data , MC
		rp_dataMC_CR = ROOT.TRatioPlot(self.data_linear_CR[0],combined_BR_CR);   ## data , MC

		rp_dataMC_antiTagCR = ROOT.TRatioPlot(self.data_linear_antiTagCR[0],combined_BR_antiTagCR);   ## data , MC
		rp_dataMC_antiTag_1b = ROOT.TRatioPlot(self.data_linear_antiTag_1b[0],combined_BR_antiTag_1b);   ## data , MC

		rp_dataMC_SR.Draw("HIST")
		rp_dataMC_SR.GetLowerRefYaxis().SetTitle("data/MC ratio")
		rp_dataMC_SR.GetLowerRefGraph().SetMaximum(2.)
		rp_dataMC_SR.GetUpperRefYaxis().SetTitle("Events")
		c.SaveAs(plot_home+"rp_dataMC_SR.png")
		rp_dataMC_CR.Draw("HIST")
		rp_dataMC_CR.GetLowerRefYaxis().SetTitle("data/MC ratio")
		rp_dataMC_CR.GetLowerRefGraph().SetMaximum(2.)
		rp_dataMC_CR.GetUpperRefYaxis().SetTitle("Events")
		c.SaveAs(plot_home+"rp_dataMC_CR.png")
		rp_dataMC_antiTagCR.Draw("HIST")
		rp_dataMC_antiTagCR.GetLowerRefYaxis().SetTitle("data/MC ratio")
		rp_dataMC_antiTagCR.GetLowerRefGraph().SetMaximum(2.)
		rp_dataMC_antiTagCR.GetUpperRefYaxis().SetTitle("Events")
		c.SaveAs(plot_home+"rp_dataMC_antiTagCR.png")
		rp_dataMC_antiTag_1b.Draw("HIST")
		rp_dataMC_antiTag_1b.GetLowerRefYaxis().SetTitle("data/MC ratio")
		rp_dataMC_antiTag_1b.GetLowerRefGraph().SetMaximum(2.)
		rp_dataMC_antiTag_1b.GetUpperRefYaxis().SetTitle("Events")
		c.SaveAs(plot_home+"rp_dataMC_antiTag_1b.png")


		# make ratio plots of the comparison of shapes of SR/CR and antiTagCR/antiTag_1b in MC/data


		# normalized data
		data_linear_antiTag_1b_norm = self.data_linear_antiTag_1b[0].Clone()
		data_linear_antiTag_1b_norm.SetTitle("normalized 1b anti-tag to 0b anti-tag comparison")
		data_linear_antiTag_1b_norm.Scale(1/data_linear_antiTag_1b_norm.Integral())

		data_linear_antiTagCR_norm = self.data_linear_antiTagCR[0].Clone()
		data_linear_antiTagCR_norm.SetTitle("normalized 1b anti-tag to 0b anti-tag comparison")
		data_linear_antiTagCR_norm.Scale(1.0/data_linear_antiTagCR_norm.Integral())
		data_linear_antiTagCR_norm.SetLineColor(ROOT.kRed)

		data_linear_CR_norm = self.data_linear_CR[0].Clone()
		data_linear_CR_norm.SetTitle("normalized SR CR comparison")
		data_linear_CR_norm.Scale(1.0/data_linear_CR_norm.Integral())
		data_linear_CR_norm.SetLineColor(ROOT.kRed)

		data_linear_SR_norm = self.data_linear_SR[0].Clone()
		data_linear_SR_norm.SetTitle("normalized SR CR comparison")
		data_linear_SR_norm.Scale(1.0/data_linear_SR_norm.Integral())


		# combined_BR_CR  combined_BR_SR  combined_BR_antiTagCR  combined_BR_antiTag_1b

		#normalized MC
		combined_BR_CR_norm = combined_BR_CR.Clone()
		combined_BR_CR_norm.Scale(1.0/combined_BR_CR_norm.Integral())
		combined_BR_CR_norm.SetLineColor(ROOT.kRed)

		combined_BR_SR_norm= combined_BR_SR.Clone()
		combined_BR_SR_norm.Scale(1.0/combined_BR_SR_norm.Integral())

		combined_BR_antiTagCR_norm = combined_BR_antiTagCR.Clone()
		combined_BR_antiTagCR_norm.Scale(1.0/combined_BR_antiTagCR_norm.Integral())
		combined_BR_antiTagCR_norm.SetLineColor(ROOT.kRed)

		combined_BR_antiTag_1b_norm = combined_BR_antiTag_1b.Clone()
		combined_BR_antiTag_1b_norm.Scale(1.0/combined_BR_antiTag_1b_norm.Integral())

		rp_dataShape_antiTag = ROOT.TRatioPlot(data_linear_antiTag_1b_norm,data_linear_antiTagCR_norm)  
		rp_MCShape_antiTag   = ROOT.TRatioPlot(combined_BR_antiTag_1b_norm,combined_BR_antiTagCR_norm)  

		rp_dataShape_SRCR = ROOT.TRatioPlot(data_linear_SR_norm,data_linear_CR_norm)
		rp_MCShape_SRCR   = ROOT.TRatioPlot(combined_BR_SR_norm,combined_BR_CR_norm)   


		rp_dataShape_antiTag.Draw("HIST")
		rp_dataShape_antiTag.GetLowerRefYaxis().SetTitle("1b region/0b region ratio")
		rp_dataShape_antiTag.GetLowerRefGraph().SetMaximum(2.)
		rp_dataShape_antiTag.GetUpperRefYaxis().SetTitle("Events")
		c.SaveAs(plot_home+"rp_dataShape_antiTag.png")

		rp_MCShape_antiTag.Draw("HIST")
		rp_MCShape_antiTag.GetLowerRefYaxis().SetTitle("1b region MC / 0b region MC")
		rp_MCShape_antiTag.GetLowerRefGraph().SetMaximum(2.)
		rp_MCShape_antiTag.GetUpperRefYaxis().SetTitle("Events")
		c.SaveAs(plot_home+"rp_MCShape_antiTag.png")

		rp_dataShape_SRCR.Draw("HIST")
		rp_dataShape_SRCR.GetLowerRefYaxis().SetTitle("SR/CR")
		rp_dataShape_SRCR.GetLowerRefGraph().SetMaximum(2.)
		rp_dataShape_SRCR.GetUpperRefYaxis().SetTitle("Events")
		c.SaveAs(plot_home+"rp_dataShape_SRCR.png")

		rp_MCShape_SRCR.Draw("HIST")
		rp_MCShape_SRCR.GetLowerRefYaxis().SetTitle("SR MC /CR MC")
		rp_MCShape_SRCR.GetLowerRefGraph().SetMaximum(2.)
		rp_MCShape_SRCR.GetUpperRefYaxis().SetTitle("Events")
		c.SaveAs(plot_home+"rp_MCShape_SRCR.png")
		# modify this to make ratio plots of the shapes of the antiTagCR and antiTag_1b regions
		# do a scaled SR / CR plot ... see how well the shapes match between the regions
		# do a comparison of MC shapes in the SR and CR 

if __name__=="__main__":
	start_time = time.time()
	signal_types = ["Suu5_chi2"]
	#years = ["2015","2016","2017","2018"]
	years = ["2018"]
	regions = ["SR","CR","antiTagCR", "antiTag_1b"]
	for year in years:
		for signal_type in signal_types:
				final_plot = linearized_plot(year, signal_type)
				#print("final_plot value for QCD %s %s : %s"%(year, region,final_plot.QCD_hist.GetBinContent( final_plot.QCD_hist.GetMaximumBin() )) )
				#print("final_plot value for TTbar %s %s : %s"%(year, region,final_plot.TTbar_hist.GetBinContent( final_plot.TTbar_hist.GetMaximumBin() ))   )
				print("The superbin indices have size %s"%len(final_plot.superbin_indices))
	print("Script took %ss to run."%(	np.round(time.time() - start_time,4 )) )

# create one root file for each year containing all the systematics = another level of folders
#   syst_suffix/region/hists
#   JEC_up/SR/QCD




import sys,os,time
import ROOT
import ast
from print_nice_hist import print_nice_hist
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

### update 10 Nov, will create a method that saves plots (and histograms) of the individual and combined 2D distributions in the SR and CR
class linearized_plot:
	n_bins_x = 22
	n_bins_y = 20
	def __init__(self, year):
		self.year   = year
		self.MC_root_file_home      = "/Users/ethan/Documents/rootFiles/processedRootFilesAlt/"
		self.data_root_file_home    = "/Users/ethan/Documents/rootFiles/processedRootFilesData/"

		self.index_file_home     = "/Users/ethan/Documents/rootFiles/statisticalUncertaintyStudyAlt/txtfiles"
		self.output_file_home    = "/Users/ethan/Documents/rootFiles/finalCombineFiles"
		self.final_plot_home    = "/Users/ethan/Documents/plots/combinePlots"

		self.superbin_indices        = self.load_superbin_indices()

		self.systematics = ["nom","JER","JEC"]

		self.QCD_hist_SR = []
		self.TTbar_hist_SR = []
		self.QCD_hist_CR = []
		self.TTbar_hist_CR = []
		self.data_hist_SR = []
		self.data_hist_CR = []

		for systematic in self.systematics:
			self.QCD_hist_SR.extend(self.load_QCD_hists("SR",systematic))
			self.TTbar_hist_SR.extend(self.load_ttbar_hist("SR",systematic))
			#self.data_hist_SR.extend(self.load_data_hists("SR",systematic))

			self.QCD_hist_CR.extend(self.load_QCD_hists("CR",systematic))
			self.TTbar_hist_CR.extend(self.load_ttbar_hist("CR",systematic))
			#self.data_hist_CR.extend(self.load_data_hists("CR",systematic))

		self.write_2D_distribution(self.load_QCD_hists("SR","nom"), "Average Superjet Mass vs diSuperjet Mass", "QCD","SR")
		self.write_2D_distribution(self.load_QCD_hists("CR","nom"),"Average Superjet Mass vs diSuperjet Mass","QCD","CR")
		self.write_2D_distribution(self.load_ttbar_hist("SR","nom"), "Average Superjet Mass vs diSuperjet Mass","TTbar","SR")
		self.write_2D_distribution(self.load_ttbar_hist("CR","nom"), "Average Superjet Mass vs diSuperjet Mass","TTbar","CR")

		combined_hist_SR = self.load_ttbar_hist("SR","nom")[0]
		combined_hist_SR.Add(self.load_QCD_hists("SR","nom")[0])
		combined_hist_CR =  self.load_ttbar_hist("CR","nom")[0]
		combined_hist_CR.Add(self.load_QCD_hists("CR","nom")[0])

		self.write_2D_distribution([combined_hist_SR], "Average Superjet Mass vs diSuperjet Mass", "BR-Combined","SR")
		self.write_2D_distribution([combined_hist_CR], "Average Superjet Mass vs diSuperjet Mass", "BR-Combined","CR")

		#now create linear plots that have all systematic plots inside

		self.QCD_linear_SR = []
		self.TTbar_linear_SR = []
		self.QCD_linear_CR = []
		self.TTbar_linear_CR = []
		self.data_linear_SR = []
		self.data_linear_CR = []
		for iii,systematic in enumerate(self.systematics):
			self.QCD_linear_SR.extend(self.linearize_plot(self.QCD_hist_SR[iii],"QCD","SR",systematic))
			self.TTbar_linear_SR.extend(self.linearize_plot(self.TTbar_hist_SR[iii],"TTbar","SR",systematic))

			self.QCD_linear_CR.extend(self.linearize_plot(self.QCD_hist_CR[iii],"QCD","CR",systematic))
			self.TTbar_linear_CR.extend(self.linearize_plot(self.TTbar_hist_CR[iii],"TTbar","CR",systematic))

			#self.data_linear_SR.extend(self.linearize_plot(self.hist_data,"data","SR",systematic))
			#self.data_linear_CR.extend(self.linearize_plot(self.hist_data,"data","CR",systematic))

		#self.signal_linear       = self.linearize_plot(self.hist_signal,signal)  #TODO
		#self.data_linear         = self.linearize_plot(self.hist_data,"data"")   #TODO



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
		sys_suffix = [""]
		if systematic != "nom":
			sys_updown = ["%s_up"%systematic,"%s_down"%systematic]
		elif systematic == "nom":
			sys_updown = ["nom_"]
		SF_1000to1500 = {'2015':1.578683216 , '2016':1.482632755 , '2017':3.126481451 , '2018':4.289571744  }
		SF_1500to2000 = {'2015': 0.2119142341, '2016':0.195224041 , '2017':0.3197450474 , '2018':0.4947703875  }
		SF_2000toInf  = {'2015':0.08568186031 , '2016':0.07572795371 , '2017': 0.14306915, '2018':0.2132134533  }
		
		### make histogram paths
		hist_path_1000to1500 = self.MC_root_file_home+ "QCDMC_HT1000to1500_%s_%s_processed.root"%(self.year,systematic)
		hist_path_1500to2000 = self.MC_root_file_home+ "QCDMC_HT1500to2000_%s_%s_processed.root"%(self.year,systematic)
		hist_path_2000toInf  = self.MC_root_file_home+ "QCDMC_HT2000toInf_%s_%s_processed.root"%(self.year,systematic)

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

		SF_TTToHadronic= {'2015':0.075592 , '2016':0.05808655696 , '2017':0.06651018525 , '2018': 0.06588049107 }
		SF_TTToSemiLeptonic= {'2015':0.05395328118 , '2016':0.04236184005 , '2017':0.04264829286 , '2018': 0.04563489275 }
		SF_TTToLeptonic= {'2015':0.0459517611 , '2016':0.03401684391 , '2017':0.03431532926 , '2018': 0.03617828025 }

		hist_path_TTToHadronic = self.MC_root_file_home+ "TTTohadronic_%s_%s_processed.root"%(self.year,systematic)
		hist_path_TTToSemiLeptonic = self.MC_root_file_home+ "TTToSemiLeptonic_%s_%s_processed.root"%(self.year,systematic)
		hist_path_TTToLeptonic = self.MC_root_file_home+ "TTToLeptonic_%s_%s_processed.root"%(self.year,systematic)

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

			TH2_hist_TTToHadronic = TH2_file_TTbar.Get(hist_name_TTbar) 
			TH2_hist_TTToHadronic = TH2_file_TTToSemiLeptonic.Get(hist_name_TTbar) 
			TH2_hist_TTToHadronic = TH2_file_TTToLeptonic.Get(hist_name_TTbar) 

			TH2_hist_TTToHadronic.Scale(SF_TTToHadronic[self.year])
			TH2_hist_TTToHadronic.SetDirectory(0)   # histograms lose their references when the file destructor is called

			TH2_hist_TTToSemiLeptonic.Scale(SF_TTToSemiLeptonic[self.year])
			TH2_hist_TTToSemiLeptonic.SetDirectory(0)   # histograms lose their references when the file destructor is called

			TH2_hist_TTToLeptonic.Scale(SF_TTToLeptonic[self.year])
			TH2_hist_TTToLeptonic.SetDirectory(0)   # histograms lose their references when the file destructor is called
			
			TH2_hist_TTToHadronic.add(TH2_hist_TTToLeptonic)
			TH2_hist_TTToHadronic.add(TH2_hist_TTToSemiLeptonic)
			TH2_hist_TTToHadronic.SetTitle("combined TTbar MC (%s) (%s) (%s)"%(self.year,region, systematic))
			all_combined_TTbar_hist.append(TH2_hist_TTToHadronic)

		return all_combined_TTbar_hist  # load in TTbar historam, scale it, and return this version


	def load_data_hists(self):
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
				hist_path_data = self.MC_root_file_home+ "JetHT_%s_%s_processed.root"%(data_block,self.year)
				TH2_file_data = ROOT.TFile.Open(hist_path_TTbar,"READ")

				hist_name_data = "h_MSJ_mass_vs_MdSJ_%s"%region 
				TH2_hist_data = TH2_file_data.Get(hist_name_data) 
				combined_data_hist.add(TH2_hist_data)

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
			linear_plot = ROOT.TH1D("%s"%BR_type,"linearized %s in the %s (%s)"%(BR_type,region,year),linear_plot_size,0,linear_plot_size)
			for superbin_index,superbin in enumerate(self.superbin_indices):
				total_counts = 0
				for _tuple in superbin:
					total_counts+=_hist.GetBinContent(_tuple[0],_tuple[1])
				#print("total counts: %s from %s bins"%(total_counts,len(superbin)))
				linear_plot.SetBinContent(superbin_index,total_counts)
			ROOT.TH1.AddDirectory(False)
			linear_plot.SetDirectory(0)   # histograms lose their references when the file destructor is called
			all_linear_plots.append(linear_plot)
		return all_linear_plots

	def write_histograms(self):

		combine_file_name = self.output_file_home + "/combine_%s.root"%(year)   
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
				#self.data_linear_SR[iii+jjj].Write()

				combine_file.cd()
				combine_file.cd(sys_str)
				ROOT.gDirectory.mkdir("CR")
				combine_file.cd()
				combine_file.cd("%s/CR"%sys_str)

				self.QCD_linear_CR[iii+jjj].Write()
				self.TTbar_linear_CR[iii+jjj].Write()
				#self.data_linear_CR[iii+jjj].Write()

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
				self.QCD_linear_SR[iii+jjj].Draw()
				c.SaveAs(self.final_plot_home+"/QCD_linear_%s_%s_SR.png"%(self.year,sys_str))

				self.TTbar_linear_SR[iii+jjj].Draw()
				c.SaveAs(self.final_plot_home+"/TTbar_linear_%s_%s_SR.png"%(self.year,sys_str))

				self.QCD_linear_CR[iii+jjj].Draw()
				c.SaveAs(self.final_plot_home+"/QCD_linear_%s_%s_CR.png"%(self.year,sys_str))

				self.TTbar_linear_CR[iii+jjj].Draw()
				c.SaveAs(self.final_plot_home+"/TTbar_linear_%s_%s_CR.png"%(self.year,sys_str))

				#self.data_linear_CR[iii+jjj].Draw()
				#c.SaveAs(self.final_plot_home+"/data_linear_%s_%s_CR.png"%(self.year,sys_str))

				#self.data_linear_SR[iii+jjj].Draw()
				#c.SaveAs(self.final_plot_home+"/data_linear_%s_%s_SR.png"%(self.year,sys_str))

		return
	def write_2D_distribution(self,hist, title, sample, region):   #TODO: add signal and data olots here 
		c = ROOT.TCanvas("c", "canvas", 1000, 1050)

		print("The hist is ", hist)
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

if __name__=="__main__":
	start_time = time.time()
	signal_types = ["Suu8TeV_chi3TeV"]
	years = ["2015","2016","2017","2018"]
	regions = ["SR","CR"]
	for year in years:
			final_plot = linearized_plot(year)
			#print("final_plot value for QCD %s %s : %s"%(year, region,final_plot.QCD_hist.GetBinContent( final_plot.QCD_hist.GetMaximumBin() )) )
			#print("final_plot value for TTbar %s %s : %s"%(year, region,final_plot.TTbar_hist.GetBinContent( final_plot.TTbar_hist.GetMaximumBin() ))   )
			print("The superbin indices have size %s"%len(final_plot.superbin_indices))
	print("Script took %ss to run."%(	time.time() - start_time ))

# create one root file for each year containing all the systematics = another level of folders
#   syst_suffix/region/hists
#   JEC_up/SR/QCD




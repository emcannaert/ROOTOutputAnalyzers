import sys,os,time
import ROOT
import ast

### linearize_final_plots.py
### written by Ethan Cannaert, October 2023
### requires locations of input root files for each background/signal contribution (QCD1000to1500, QCD1500to2000, QCD2000toInf, TTbar, sig MC)

### open each file and get the histograms from each
### scale histograms relative to the appropriate luminosity 
### get superbin indices and find "center" of each superbin, sort bin by these centers 
### loop over each superbin and add together the corresponding histogram bins, this becomes an entry in a 1D ( 22x20 = 440 bin) distribution for each contribution that goes to Combine
### in the end there will be a histogram for QCD, TTbar, signal MC, and then data 


class linearized_plot:
	n_bins_x = 22
	n_bins_y = 20
	def __init__(self, year,region,signal):
		self.region = region
		self.year   = year
		self.root_file_home      = "/Users/ethan/Documents/rootFiles/processedRootFilesAlt/"
		self.index_file_home     = "/Users/ethan/Documents/rootFiles/statisticalUncertaintyStudyAlt/txtfiles"
		self.output_file_home    = "/Users/ethan/Documents/rootFiles/finalCombineFiles"
		self.final_plot_home    = "/Users/ethan/Documents/plots/combinePlots"

		self.superbin_indices        = self.load_superbin_indices()

		self.QCD_hist = self.load_QCD_hists()
		self.TTbar_hist = self.load_ttbar_hist()
		#self.hist_signal       = self.load_signal_hist(signal)   #TODO
		#self.hist_data         = self.load_data_hist()           #TODO
 
		self.QCD_linear = self.linearize_plot(self.QCD_hist,"QCD")
		self.TTbar_linear = self.linearize_plot(self.TTbar_hist,"TTbar")
		#self.signal_linear       = self.linearize_plot(self.hist_signal,signal)  #TODO
		#self.data_linear         = self.linearize_plot(self.hist_data,"data"")   #TODO

		self.write_histograms()
		self.print_histograms()
		#elf.sorted_superbin_indices = self.sort_superbin_indices()  # have to figure out how to do this ...



	def load_QCD_hists(self):
		"""
  								{ {3.87E+00, 2.89E+00, -99999., -99999., -99999.  },   // MSuu = 4 TeV  // convert this to a dictionary
                                  {1.37E+00, 1.19E+00, 8.67E-01, -99999., -99999. },   // MSuu = 5 Tev
                                  {2.82E-01, 2.58E-01, 2.20E-01, -99999., -99999. },   // MSuu = 6 TeV       
                                  {2.01E-01, 1.89E-01, 1.71E-01, -99999., 1.31E-01},   // MSuu = 7 TeV
                                  {2.17E-02, 2.08E-02, 1.93E-02, -99999., 1.74E-02 }    // MSuu = 8 TeV   
		"""
		SF_1000to1500 = {'2015':1.578683216 , '2016':1.482632755 , '2017':3.126481451 , '2018':4.289571744  }
		SF_1500to2000 = {'2015': 0.2119142341, '2016':0.195224041 , '2017':0.3197450474 , '2018':0.4947703875  }
		SF_2000toInf  = {'2015':0.08568186031 , '2016':0.07572795371 , '2017': 0.14306915, '2018':0.2132134533  }
		### make histogram paths
		hist_path_1000to1500 = self.root_file_home+ "QCDMC_HT1000to1500_%s_processed.root"%(self.year)
		hist_path_1500to2000 = self.root_file_home+ "QCDMC_HT1500to2000_%s_processed.root"%(self.year)
		hist_path_2000toInf  = self.root_file_home+ "QCDMC_HT2000toInf_%s_processed.root"%(self.year)

		### get each histogram
		hist_name = "h_MSJ_mass_vs_MdSJ_%s"%self.region 
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

		combined_QCD_hist = ROOT.TH2F("combined_QCD", ("QCD (HT1000-Inf) Events in the %s (%s)"%(region, year)), 22,1250., 9500, 20, 500, 3500)
		combined_QCD_hist.Add(TH2_hist_1000to1500)
		combined_QCD_hist.Add(TH2_hist_1500to2000)
		combined_QCD_hist.Add(TH2_hist_2000toInf)

		combined_QCD_hist.SetDirectory(0)   # histograms lose their references when the file destructor is called

		ROOT.TH1.AddDirectory(False)

		return combined_QCD_hist   # load in QCD histograms, scale them, add them together, and return their sum
	def load_ttbar_hist(self):

		SF_TTbar= {'2015':0.075592 , '2016':0.05808655696 , '2017':0.06651018525 , '2018': 0.06588049107 }
		hist_path_TTbar = self.root_file_home+ "TTTohadronic_%s_processed.root"%(self.year)

		hist_name_TTbar = "h_MSJ_mass_vs_MdSJ_%s"%self.region 
		TH2_file_TTbar = ROOT.TFile.Open(hist_path_TTbar,"READ")
		TH2_hist_TTbar = TH2_file_TTbar.Get(hist_name_TTbar) 

		TH2_hist_TTbar.Scale(SF_TTbar[self.year])
		TH2_hist_TTbar.SetDirectory(0)   # histograms lose their references when the file destructor is called

		return TH2_hist_TTbar  # load in TTbar historam, scale it, and return this version

	### now the scale factors are applied, so you'll see few events in bins
	def linearize_plot(self, _hist,BR_type): # take in a histogram and linearize it   TODO: is this working correctly? there are ~350 bins in each year, is the the correct number?
		linear_plot_size = len(self.superbin_indices)  
		linear_plot = ROOT.TH1D("%s"%BR_type,"linearized %s in the %s (%s)"%(BR_type,region,year),linear_plot_size,0,linear_plot_size)
		for superbin_index,superbin in enumerate(self.superbin_indices):
			total_counts = 0
			for _tuple in superbin:
				total_counts+=_hist.GetBinContent(_tuple[0],_tuple[1])
			print("total counts: %s from %s bins"%(total_counts,len(superbin)))
			linear_plot.SetBinContent(superbin_index,total_counts)
		return linear_plot

	def write_histograms(self):

		combine_file_name = self.output_file_home + "/combine_%s_%s.root"%(year,region)     ### TODO: need to change name to match each of the signal mass points, TODO: add signal and data histogram entries
		combine_file = ROOT.TFile(combine_file_name,"RECREATE")
		combine_file.cd()
		ROOT.gDirectory.mkdir("QCD_%s"%region)
		combine_file.cd("QCD_%s"%region)

		self.QCD_linear.Write()

		combine_file.cd()
		ROOT.gDirectory.mkdir("TTbar_%s"%region)
		combine_file.cd("TTbar_%s"%region)

		self.TTbar_linear.Write()

		return 
	def print_histograms(self):   #TODO: add signal and data olots here 
		c = ROOT.TCanvas("c", "canvas", 1000, 1050)

		self.QCD_linear.Draw()
		c.SaveAs(self.final_plot_home+"/QCD_linear_%s_%s.png"%(self.year,self.region))

		self.TTbar_linear.Draw()
		c.SaveAs(self.final_plot_home+"/TTbar_linear_%s_%s.png"%(self.year,self.region))
		return
	def load_superbin_indices(self):    # load in the superbin indices (located in a text file )
		_superbin_indices = []
		open_file = open(self.index_file_home+"/superbin_indices.txt","r")
		for line in open_file:
			columns = line.split('/')
			if columns[0] == self.year and columns[1] == self.region:
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
		for region in regions:
			for signal in signal_types:

				final_plot = linearized_plot(year,region,signal)
				#print("final_plot value for QCD %s %s : %s"%(year, region,final_plot.QCD_hist.GetBinContent( final_plot.QCD_hist.GetMaximumBin() )) )
				#print("final_plot value for TTbar %s %s : %s"%(year, region,final_plot.TTbar_hist.GetBinContent( final_plot.TTbar_hist.GetMaximumBin() ))   )
				print("The superbin indices have size %s"%len(final_plot.superbin_indices))
	print("Script took %ss to run."%(	time.time() - start_time ))



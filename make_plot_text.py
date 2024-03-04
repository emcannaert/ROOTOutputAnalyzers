import os, sys



def make_plot_text(year,sample,hist_name)





if __name__=="__main__":
	years = ["2015","2016","2017","2018"]
	hist_names = ["superjet_mass"]
	file_names = [""]
	for year in years:
		if year == "2015"
			samples = ["dataB-ver1","dataB-ver2","dataC-HIPM","dataD-HIPM","dataE-HIPM" ,"dataF-HIPM","QCDMC1000to1500","QCDMC1500to2000","QCDMC2000toInf","TTToHadronicMC", "TTToSemiLeptonicMC", "TTToLeptonicMC",
		"ST_t-channel-top_inclMC","ST_t-channel-antitop_inclMC","ST_s-channel-hadronsMC","ST_s-channel-leptonsMC","ST_tW-antiTop_inclMC","ST_tW-top_inclMC"]
		elif year == "2016":
			samples = ["dataF","dataG","dataH","QCDMC1000to1500","QCDMC1500to2000","QCDMC2000toInf","TTToHadronicMC","TTToSemiLeptonicMC","TTToLeptonicMC",
      "ST_t-channel-top_inclMC","ST_t-channel-antitop_inclMC","ST_s-channel-hadronsMC","ST_s-channel-leptonsMC","ST_tW-antiTop_inclMC","ST_tW-top_inclMC"]
		elif year == "2017":
			samples = ["dataB","dataC","dataD","dataE","dataF","QCDMC1000to1500","QCDMC1500to2000","QCDMC2000toInf","TTToHadronicMC","TTToSemiLeptonicMC","TTToLeptonicMC",
      "ST_t-channel-top_inclMC","ST_t-channel-antitop_inclMC","ST_s-channel-hadronsMC","ST_s-channel-leptonsMC","ST_tW-antiTop_inclMC","ST_tW-top_inclMC" ]
		elif year == "2018":
			samples = ["dataA","dataB", "dataC", "dataD","QCDMC1000to1500","QCDMC1500to2000","QCDMC2000toInf","TTToHadronicMC","TTToSemiLeptonicMC","TTToLeptonicMC",
   "ST_t-channel-top_inclMC","ST_t-channel-antitop_inclMC","ST_s-channel-hadronsMC","ST_s-channel-leptonsMC","ST_tW-antiTop_inclMC","ST_tW-top_inclMC" ]
   		else:
   			sys.exit("ERROR: year %s not found"%year)
   		for iii,sample in enumerate(samples):
   			for hist_name in hist_names:
   				make_plot_text(year,sample, hist_name, file_names[iii])

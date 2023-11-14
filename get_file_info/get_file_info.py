def get_file_info(file_name):
	sample_str = ""
	year_str =  ""
	syst_str =  ""
	samples = ["QCDMC2000toInf","QCDMC1500to2000","QCDMC1000to1500","TTToHadronic", "TTBar", "TTbar", "QCD2000toInf","QCD1500to2000","QCD1000to1500","QCDMC_HT2000toInf","QCDMC_HT1000to1500","QCDMC_HT1500to2000","TTTohadronic","QCDMCHT2000toInf", "TTToHadronic", "TTToSemiLeptonic", "TTToLeptonic"]
	years = ["2015","2016","2017","2018"]
	systematics = ["JEC","JER"]
	for sample in samples:
		if sample in file_name:
			sample_str = sample
	for year in years:
		if year in file_name:
			year_str = year
	for systematic in systematics:
		if systematic in file_name:
			syst_str = systematic
	return year_str,sample_str,syst_str

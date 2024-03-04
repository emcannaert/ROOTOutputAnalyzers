import sys, os
import numpy as np
import pickle
if __name__=="__main__":
	Suu_mass_ =  list(map(str, map(int, 1000*np.array(range(4,9)))))
	chi_mass_ = list(map(str,map(int,1000*np.array(range(2,7))/2.0)))

	Suu_mass = []
	chi_mass = []

	years = {"UL16MiniAODAPVv2": "2015" ,
			 "UL16MiniAODv2":  "2016" ,
			 "UL17MiniAODv2": "2017" ,
			 "UL18MiniAODv2":  "2018"
		}

	Suu_mass = {"MSuu-4000":  "Suu4",
				"MSuu-5000":  "Suu5",
				"MSuu-6000":  "Suu6",
				"MSuu-7000":  "Suu7",
				"MSuu-8000":  "Suu8"
		}
	chi_mass = {"MChi-1000":  "chi1",
				"MChi-1500":  "chi1p5",
				"MChi-2000":  "chi2",
				"MChi-2500":  "chi12p5",
				"MChi-3000":  "chi3"
		}
	decays = ["WBWB", "HTHT", "ZTZT", "WBHT","WBZT", "HTZT"]

	with open("/Users/ethan/Documents/textFiles/signal_MC_datasets.txt", "r") as f:
		lines = f.readlines()


	signal_datasets = dict()
	num_files = 0
	for iii,line in enumerate(lines):
		
		if(line.split() == []):
			continue
		year_ = ""
		Suu_mass_ = ""
		chi_mass_ = ""
		decay_ = ""
		for long_year, year in years.items():
			if long_year in line:
				year_ = years[long_year]
		for long_Suu_mass, MSuu in Suu_mass.items():
			if long_Suu_mass in line:
				Suu_mass_ = Suu_mass[long_Suu_mass]
		for long_chi_mass, MChi in chi_mass.items():
			if long_chi_mass in line:
				chi_mass_ = chi_mass[long_chi_mass]
		for decay in decays:
			if decay in line:
				decay_ = decay
		any_failed = [ year_ == "", Suu_mass_ == "", chi_mass_ == "", decay_ == ""   ]
		if True in any_failed:
			print("ERROR: found bad line - %s"%line)
			continue
		num_files+=1
		mass_label = "%s_%s_%s"%(Suu_mass_,chi_mass_,decay_)

		if year_ not in signal_datasets.keys():
			signal_datasets[year_] = dict()
		if mass_label not in  signal_datasets[year_].keys():
			signal_datasets[year_][mass_label] = dict()
		signal_datasets[year_][mass_label] = line
		#print("year, Suu mass, chi mass, decay = %s/%s/%s/%s"%(year_,Suu_mass_,chi_mass_,decay_))


	print("Added %i files to the dictionary."%num_files)

	pickle.dumps(signal_datasets)







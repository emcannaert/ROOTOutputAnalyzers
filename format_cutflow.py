import sys,os
import numpy as np
from return_BR_SF import return_BR_SF
#### this script takes the output of readTreeApplySelection and converts it to a more readable yield text format
def convert_cutflow(filename):
	line_count = 0


	# index 10 are the yields
	# index 0 is the region
	# systematic is 3
	# index 4 is the sample
	#index 5 is the year

	""" dictionary shape : { "2015": { "sample1": {"Signal": [val1,val2, .... valn], "Control": val1,val2, .... valn], ...     }    }       

	}

	dict[year][region][sample] = [vals]
	"""
	all_yields = dict()
	regions = ["Signal", "Control", "AT1b", "AT0b"]
	with open(filename) as f:
		file_lines = f.readlines()
	for line in file_lines:
		space_split_line = line.split()
		if( len(space_split_line)> 0):
			if space_split_line[0] in regions:
				yields = np.array(space_split_line[10].split("-"))
				yields = list(map(float,yields))
				year = space_split_line[5]
				region = space_split_line[0]
				sample = space_split_line[4]
				systematic = space_split_line[3]	
				if systematic not in all_yields:
					all_yields[systematic]= dict()
				if year not in all_yields[systematic]:
					all_yields[systematic][year] = dict()
				if region not in all_yields[systematic][year]:
					all_yields[systematic][year][region] = dict()
				if sample not in all_yields[systematic][year]:
					all_yields[systematic][year][region][sample] = dict()
				all_yields[systematic][year][region][sample] = yields
	print_yields(all_yields)
	return

def print_yields(all_yields):
	output = open("/Users/ethan/Documents/textFiles/cutflow_output.txt", "w")
	for systematic, years in all_yields.items():
		for year,regions in years.items():
			for region, samples in regions.items():
				print("-------------------------- Start %s %s %s --------------------------------"%(year,region,systematic) ) 
				output.write("-------------------------- Start %s %s %s --------------------------------\n"%(year,region,systematic) ) 

				data_sum = np.zeros(6)
				MC_sum = np.zeros(6)
				for sample, yields in samples.items():
					use_sample = sample.replace("-","_")[:-1]
					if "data" in sample:
						data_sum += np.array(yields)
					elif "MC" in sample:
						sample_SF = float(return_BR_SF.return_BR_SF(year,use_sample))
						MC_sum += sample_SF*np.array(yields)
					print("%s	%s	%s	%s	%s\n"%(year,region,systematic,sample, "	".join( list(map(str,yields))) ))
					output.write("%s	%s	%s	%s	%s\n"%(year,region,systematic,sample, "	".join( list(map(str,yields))) ))


				print("----------------------------------------------------------------------\n")
				print("---    MC SUM:	%s\n"%("	".join(list(map(str,MC_sum))   )))
				print("---- DATA SUM:	%s\n"%("	".join(list(map(str,data_sum))   )))
				print("------- Ratio:	%s\n"%("	".join(list(map(str,np.array(data_sum)/np.array(MC_sum))) )))
				print("-------------------------- END %s %s %s ---------------------------------\n"%(year,region,systematic) ) 
				output.write("----------------------------------------------------------------------\n")
				output.write("---    MC SUM:	%s\n"%("	".join(list(map(str,MC_sum))   )))
				output.write("---- DATA SUM:	%s\n"%("	".join(list(map(str,data_sum))   )))
				output.write("------- Ratio:	%s\n"%("	".join(list(map(str,np.array(data_sum)/np.array(MC_sum))) )))
				output.write("-------------------------- END %s %s %s ---------------------------------\n"%(year,region,systematic) ) 

			print("")
			print("")
			print("")
if __name__=="__main__":

	if(len(sys.argv) != 2):
		sys.exit("ERROR: Incorrect number of inputs. Include only the text file with the cutflow info as an input. Ex: python3 format_cutflow.py cutflow.txt")
	filename = sys.argv[1]
	print("Converting %s."%filename)
	convert_cutflow(filename)


#! /usr/bin/env python
import argparse
import sys
import os
##############################################################################
#MAIN
##############################################################################
dirs = ['Suu8TeV_chi2TeV','Suu8TeV_chi1TeV','Suu7TeV_chi3TeV','Suu7TeV_chi2TeV','Suu7TeV_chi1TeV','Suu6TeV_chi2TeV','Suu6TeV_chi1p5TeV','Suu6TeV_chi1TeV','Suu5TeV_chi2TeV','Suu5TeV_chi1p5TeV','Suu5TeV_chi1TeV','Suu4TeV_chi1p5TeV','Suu4TeV_chi1TeV','Suu4TeV_chi850GeV','Suu4TeV_chi500GeV']

def main(argv):

	for index,directory in enumerate(dirs):
		os.system("mv /uscms_data/d3/cannaert/analysis/CMSSW_10_6_20/src/clusteringAnalyzer%s_cfg_copy.py /uscms_data/d3/cannaert/analysis/CMSSW_10_6_20/src/clusteringAnalyzer%s_cfg_copy_copy.py"%(directory,directory))
		oldCFG = open('/uscms_data/d3/cannaert/analysis/CMSSW_10_6_20/src/clusteringAnalyzer%s_cfg_copy_copy.py'%directory,'r')
		newCFG = open('/uscms_data/d3/cannaert/analysis/CMSSW_10_6_20/src/clusteringAnalyzer%s_cfg.py'%directory,'w')

		for line in oldCFG:
			sentence = line.split()
			if len(sentence) == 0:
				continue;
			elif(sentence[0] == 'tauCollection'):
				newCFG.write('tauCollection = cms.InputTag("slimmedTaus"),\n metCollection = cms.InputTag("slimmedMETs")\n')
			else:
				newCFG.write(line)
		oldCFG.close()

if __name__ == "__main__":
	main(sys.argv[1:])
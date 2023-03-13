#! /usr/bin/env python

import sys, os

##############################################################################
#MAIN
##############################################################################
def splitArgs(arg):

    argvSplit = []
    for par in arg:
        par = par.split(",")
        argvSplit.extend(par)
    return argvSplit

#def mergeFiles():


#    return

def interpretL1(temp):
    tempfile = open(temp, 'r')
    for line in tempfile:
        print(line)

#def interpretL2():

def getDatasetPaths(self,years,datasets):
    for year in years:
        for dataset in datasets:
            os.system("xrdfsls /store/user/ecannaer/%s > temp")
            nextString = interpretL1("temp")

    return
class getRunFiles():

    #_mergeFiles = mergeFiles
    _getDataSetPaths = getDatasetPaths
    def __init__(self, years, datasets):
        self.datafilePaths = []
        self._getDataSetPaths(years,datasets)
        #_mergeFiles()


    datasetDict = { "HT1000to1500":"QCD_HT1000to1500_TuneCP5_13TeV-madgraphMLM-pythia8" ,
                        "HT1500to2000": "QCD_HT1500to2000_TuneCP5_13TeV-madgraphMLM-pythia8",
                        "HT2000toInf" : "QCD_HT2000toInf_TuneCP5_13TeV-madgraphMLM-pythia8"}


    """                    
    self.default_HT1000to1500_dataset = "QCD_HT1000to1500_TuneCP5_13TeV-madgraphMLM-pythia8"
    self.default_HT1500to2000_dataset = "QCD_HT1500to2000_TuneCP5_13TeV-madgraphMLM-pythia8"
    self.default_HT2000toInf_dataset = "QCD_HT2000toInf_TuneCP5_13TeV-madgraphMLM-pythia8"
    """


def main(argv): 

    argvSplit = splitArgs(argv)

    yearRef = ['2016','2017','2018'] 
    datasetRef = ['HT1000to1500','HT1500to2000','HT2000toInf']
    if 'allYears' in argv:
        years = yearRef
    else:
        years = [ year for year in yearRef if year in argvSplit]
    if 'allDatasets' in argv:
        datasets = datasetRef
    else:
        datasets = [dataset for dataset in datasetRef if dataset in argvSplit]

    if (( len(years) + len(datasets) ) < 1):
        print("wrong inputs: enter the data years you want (separated by a comma, allYears for all) and datasets you want (allDatasets for all)")
        return

    getFiles = getRunFiles(years,datasets)

if __name__ == "__main__":
    main(sys.argv[1:])






#2018 - clustAlg_QCD_HT1000to1500_000, and then the golden for others
 



#config.Data.outputDatasetTag


# only want one dataset per folder (the most recent one), and don't want anything older than a few days ago
# options are to look at the folder age
# need to set what the major dataset name is, then look at the output names (look for years)


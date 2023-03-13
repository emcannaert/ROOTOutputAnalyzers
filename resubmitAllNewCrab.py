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
def editFiles(years, datasets):
    for year in years:
        for dataset in datasets:
            try:
                crabFileName = "crab_clustAlg_QCD_%s_%s_cfg.py"%(dataset,year)
            except:
                continue
            crabFileNameNew = "crab_clustAlg_QCD_%s_%s_cfg_new.py"%(dataset,year)
            oldfile = open(crabFileName, 'r')
            newfile = open(crabFileNameNew, 'w')
            for line in oldfile:
                splitLine = line.split()
                if (len(splitLine) > 0) and (splitLine[0] == 'config.General.requestName'):
                    submitNumber = splitLine[2].split('_')[-1]
                    splitsubmitNumber = int(submitNumber.replace("'","").replace('"',""))
                    splitsubmitNumber+=1
                    newfile.write(splitLine[0]+ " " + splitLine[1] + " 'crab_clustAlg_QCD_%s_%s_%i'\n"%(dataset,year,splitsubmitNumber))
                else:
                   newfile.write(line)
            oldfile.close()
            newfile.close()
    return
def swapFiles(years,datasets):
    for year in years:
        for dataset in datasets:
            os.rename("crab_clustAlg_QCD_%s_%s_cfg.py"%(dataset,year),"crab_clustAlg_QCD_%s_%s_cfg_lastCopy.py"%(dataset,year)    )
            os.rename("crab_clustAlg_QCD_%s_%s_cfg_new.py"%(dataset,year),"crab_clustAlg_QCD_%s_%s_cfg.py"%(dataset,year)    )
            if( os.path.isfile("crab_clustAlg_QCD_%s_%s_cfg_new.py"%(dataset,year)) ):
                os.remove("crab_clustAlg_QCD_%s_%s_cfg_new.py"%(dataset,year))
    return
def submitCrabJobs(years,datasets):
    swapFiles(years,datasets)
    for year in years:
        for dataset in datasets:
            os.system("crab submit -c crab_clustAlg_QCD_%s_%s_cfg.py"%(dataset,year)) 

def createCheckFiles(years,datasets):
    checkFile = open("checkCrab.sh",'w')
    resubmitFile = open("resubmitCrab.sh",'w')
    for year in years:
        for dataset in datasets:
            try:
                crabFileName = "crab_clustAlg_QCD_%s_%s_cfg.py"%(dataset,year)
            except:
                continue
            oldfile = open(crabFileName, 'r')
            for line in oldfile:
                splitLine = line.split()
                if (len(splitLine) > 0) and (splitLine[0] == 'config.General.requestName'):
                    submitNumber = splitLine[2].split('_')[-1]
                    splitsubmitNumber = submitNumber.replace("'","").replace('"',"")
                    checkFile.write("crab status -d crab_projects/crab_clustAlg_QCD_%s_%s_%s\n"%(dataset,year,splitsubmitNumber))
                    resubmitFile.write("crab resubmit -d crab_projects/crab_clustAlg_QCD_%s_%s_%s\n"%(dataset,year,splitsubmitNumber))
    checkFile.close()
    resubmitFile.close()
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

    print("Updating submit number for cfg files")
    editFiles(years,datasets)
    print("Submitting crab files")
    #submitCrabJobs(years,datasets)
    print("Creating files to check and resubmit jobs - checkCrab.sh & resubmitCrab.sh")
    createCheckFiles(years,datasets)
    print("Finished.")

if __name__ == "__main__":
    main(sys.argv[1:])

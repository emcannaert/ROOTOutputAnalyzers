#! /usr/bin/env python

import sys, os

##############################################################################
#MAIN
##############################################################################

def main(argv): 

    _datasets = []
    _datasetTags = []

    with open('QCD_datasets.txt') as f:
        datasetLines = f.readlines()

    for line in datasetLines:
        contents = line.split()
        _datasets.append(contents[0])
        _datasetTags.append(contents[1])

    with open('template_cfg.py') as f1:
        templateLines = f1.readlines()

    for i in range(0,len(_datasets)):
        newDatasetFile = open("crab_%s_cfg.py"%_datasetTags[i],"w")
        appendList = ["","","'BESTQCD_%s_0001'"%_datasetTags[i],"","","","","'%s'"%_datasets[i],"","","","'BESTTraining_QCD2018_%s'"%_datasetTags[i],""]
        for j,line in enumerate(templateLines):
            if(appendList[j] == ""):
                newDatasetFile.write(line.rstrip()+" "+appendList[j]+"\n")
            else:
                newDatasetFile.write(line.rstrip()+" "+appendList[j]+"\n")
        newDatasetFile.close()
            
if __name__ == "__main__":
    main(sys.argv[1:])
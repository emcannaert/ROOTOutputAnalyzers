#! /usr/bin/env python

import sys
import csv 
#Dataset name Total events Generator fragment name Generator Gridpack location Gridpack cards URL

#SuuToChiChi_FullyHadronic_WbZt_MSuu6TeV_MChi2TeV_slc7_amd64_gcc10_CMSSW_12_4_8_tarball.tar.xz


hadFrag = "https://raw.githubusercontent.com/cms-sw/genproductions/master/genfragments/ThirteenTeV/Hadronizer/Hadronizer_TuneCP5_13TeV_generic_LHE_pythia8_PSweights_cff.py"
generator = "madgraph"
datasetNamePrefix = "SuuToChiChi_"
datasetNameSuffix = "TuneCP5_13TeV_pythia8_PSweights"
# 0 = WbWb, 1 = WbZt, 2 = Wbht. 3 = htZt, 4 = ZtZt, 5 = htht
cardPaths = ["https://github.com/cms-sw/genproductions/tree/master/bin/MadGraph5_aMCatNLO/cards/production/2017/13TeV/SuuToChiChi_FullyHadronic_WbWb",
"https://github.com/cms-sw/genproductions/tree/master/bin/MadGraph5_aMCatNLO/cards/production/2017/13TeV/SuuToChiChi_FullyHadronic_ZtZt",
"https://github.com/cms-sw/genproductions/tree/master/bin/MadGraph5_aMCatNLO/cards/production/2017/13TeV/SuuToChiChi_FullyHadronic_htht",
"https://github.com/cms-sw/genproductions/tree/master/bin/MadGraph5_aMCatNLO/cards/production/2017/13TeV/SuuToChiChi_FullyHadronic_Wbht",
"https://github.com/cms-sw/genproductions/tree/master/bin/MadGraph5_aMCatNLO/cards/production/2017/13TeV/SuuToChiChi_FullyHadronic_WbZt",
"https://github.com/cms-sw/genproductions/tree/master/bin/MadGraph5_aMCatNLO/cards/production/2017/13TeV/SuuToChiChi_FullyHadronic_htZt"]

chiMassRange = [1.0,1.5,2.0,2.5,3.0]
chiMassRangeStr = ["1","1p5","2","2p5","3"]
SuumassRange = [4,5,6,7,8]
decayType    = ["WbWb","ZtZt","htht","Wbht","WbZt","htZt"]
isPuredecay  = [True,True,True,False,False,False]
def createFile():
    CSV_file = open("request.csv","w")
    CSV_file.write("Dataset name,Total events,Generator fragment name,Generator,Gridpack location,Gridpack cards URL\n")
    for SuuMass in SuumassRange:
        for i,chiMass in enumerate(chiMassRange):
            if (chiMass >= 1.0*SuuMass/2.0):
                continue
            for j,decay in enumerate(decayType):
                datasetName = datasetNamePrefix+decay+"_FullyHadronic_MSuu"+str(SuuMass)+"TeV_MChi"+chiMassRangeStr[i]+"TeV_"+datasetNameSuffix
                gridpackLocation = "/afs/cern.ch/work/e/ecannaer/public/finishedGridpacks/SuuToChiChi_FullyHadronic_%s_MSuu%iTeV_MChi%sTeV_slc7_amd64_gcc10_CMSSW_12_4_8_tarball.tar.xz"%(decay,SuuMass,chiMassRangeStr[i])
                numberOfEvents = -9999999999999999999
                if((SuuMass < 6) and isPuredecay[j]  ):
                    numberOfEvents = 60000
                elif((SuuMass < 6) and not isPuredecay[j]  ):
                    numberOfEvents = 100000
                elif((SuuMass >= 6) and isPuredecay[j]  ):
                    numberOfEvents = 30000
                elif((SuuMass >= 6) and not isPuredecay[j]  ):
                    numberOfEvents = 50000
                CSV_file.write("%s,%i,%s,%s,%s,%s\n"%(datasetName,numberOfEvents,hadFrag,generator,gridpackLocation,cardPaths[j]))
    CSV_file.close()
    return
##############################################################################
#MAIN
##############################################################################
def main(argv): 
    createFile()
    with open('request.csv', newline='', encoding='utf-8') as f:
        reader = csv.reader(f)
        for row in reader:
            print(row)
    return
if __name__ == "__main__":
    main(sys.argv[1:])

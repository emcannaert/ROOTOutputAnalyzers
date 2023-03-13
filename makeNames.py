#! /usr/bin/env python

import sys

def makeNames():
    fileToMake = open("outputFile.txt","w")
    startString = "add process p p > suu > H t H t,"
    higgsDecays = ["(H > b b~)","(H > Z Z, Z > j j , Z > j j)","(H > W+ W-, W+ > j j, W- > j j)"]
    for decay1 in higgsDecays:
        for decay2 in higgsDecays:
            fileToMake.write(startString+decay1+","+decay2+"\n")
    fileToMake.close()
##############################################################################
#MAIN
##############################################################################
def main(argv): 
    makeNames()
if __name__ == "__main__":
    main(sys.argv[1:])





#1.50833649 -> WT
#need to update WT 
#need to change branching fraction of VLQ decays
#! /usr/bin/env python

import sys
import numpy as np
import os
from math import floor, isnan
from array import array

def splitArgs(arg):    # for parsing options, haven't set this up yet
    argvSplit = []
    for par in arg:
        par = par.split(",")
        argvSplit.extend(par)
    return argvSplit




################## helper functions for class #####################################


def _ccuScanExt(self):        #does the CCU scanning and compares each scan to reference list
    #initialize environment to scanCCU
    scannedCCUList = []
    for iii in range(0,self.nScans):

        #do scan to get refList

        if(len(scannedCCUList) = 0 ):
            print("ERROR: No CCUs found from scanCCU, most likely scanning failed.")
            return
        self._compareToRefList(self,scannedCCUList)
    return

def _compareToRefListExt(self, scannedCCUList):   #compares scanned CCU list to ref list 
    for ccu in self.refCCUList:
        if not ccu in scannedCCUList:
            self.ccuBlackMarks[ccu]+=1
    return 
def resetCCUBlackMarksExt(self):    # can't remember exactly how python classes work, might need ccuBlackMarks as parameter
    for ccu in self.refCCUList:
        self.ccuBlackMarks['ccu'] = 0

def returnNonrespondingCCUsExt(self):     #writes out text file with nonresponding CCUs
    nBadCCUs = 0
    outFile = open("badCCUs.txt", "w")
    for ccu,nBlackMarks in self.ccuBlackMarks:
        if(nBlackMarks >= self.nStrikes):
            outFile.write(ccu+"\n")
            nBadCCUs+=1
    print("Found %i nonresponding CCUs."%nBadCCUs)
    return
####################################################################################


class ccuScan:
    refCCUList = ["dummyCCU"]      # This must match what we get as output from scanCCU. what is the best way to set this? scan at beginning of run or after last power cycle?  
    
    _ccuScan() = _ccuScanExt
    resetCCUBlackMarks = resetCCUBlackMarksExt
    _compareToRefList = _compareToRefListExt
    returnNonrespondingCCUs = returnNonrespondingCCUsExt

    # initialze vars and run processes
    def __init__(self, _nScans,_nStrikes):
        self.nStrikes = _nStrikes #number of times CCU can fail
        self.nScans = _nScans     #number of times that scanCCU will be run
        self.ccuBlackMarks = dict()
        resetCCUBlackMarks()
        _ccuScan()
        returnNonrespondingCCUs()


##############################################################################
#MAIN
##############################################################################
def main(argv):
    argvSplit = splitArgs(argv)
    _nScans = 3
    _nStrikes = 3
    if '--help' in argv or '-h' in argv or '--h' in argv:
        print("--------------------------------------------------------------------------------------------")
        print("      ccuScan.py runs scan CCU some number of times (default=3?) and tries to find CCUs")
        print("     that are missing each of those times. This can be used as a list of what should be ")
        print("     powercycled.")
        print("                       -- Formatting for input: python  --")
        print("       --                         Other options:                           --")
        print("              --                                                   --")
    """if '' in argv:
        
    else:
        
    if '' in argv:
        
    else:

    if (( len(years) + len(datasets) ) < 1):
        print("wrong inputs: ")
        return
    """
    ccuScan(_nScans,_nStrikes)    #do whole process

if __name__ == "__main__":
    main(sys.argv[1:])
#! /usr/bin/env python

import sys

##############################################################################
#MAIN
##############################################################################
def main(argv): 
    testList = [[1,0,2],[0,1,0],[1,1,0]]
    if testList(1,2):
        print("greater than 0")
if __name__ == "__main__":
    main(sys.argv[1:])

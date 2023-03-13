#! /usr/bin/env python
import sys
import glob
import os
##############################################################################
#MAIN
##############################################################################
def main(argv): 
    make_file(argv)
    analyzeFile()  
    makeOutputFile()

def analyze_file():

    #could make this alphabetical by defining set of all keys
    reprog_dict = dict()
    power_dict  = dict()
    blacklist   = dict()
    analyzeFile = open("SER_channels.txt", "r")
    for line in analyzeFile:
        data = line.split()
        if data[0] == "blacklisted"
        elif data[0] == "reprogrammed":
        elif data[0] == ""



def makeOutputFile():
    for key, runs in reprog_dict.items():
        if len(runs) > 3:
            print("%s with (%i) reprogrammings in runs %s"%(key, len(runs), ' '.join(runnum for runnum in runs)) )
            if key in power_dict:
                print ("(%i) powercycles in runs %s"%(len(power_dict[key]), ' '.join(runnum for runnum in power_dict[key])) )
            else:
                print("0 powercycles")
            if key in blacklist_dict:
                print ("(%i) blacklists in runs %s"%(len(blacklist_dict[key]), ' '.join(runnum for runnum in blacklists_dict[key])) )
            else:
                print("0 blacklists")
        print("\n")
    for key, runs in power_dict:
        if (key in reprog_dict):
            if (size(reprog_dict[key]) > 3):
                continue
        if (len(runs) > 3):
            if key in reprog_dict:
                print ("(%i) reprogrammings in runs %s"%(len(reprog_dict[key]), ' '.join(runnum for runnum in reprog_dict[key])) )
            else:
                print("0 reprogrammings")

            print ("(%i) powercycles in runs %s"%(len(runs), ' '.join(runnum for runnum in runs)) )
            
            if key in blacklist_dict:
                print ("(%i) blacklists in runs %s"%(len(blacklist_dict[key]), ' '.join(runnum for runnum in blacklist_dict[key])) )
            else:
                print("0 blacklists")
        print("\n")

    for key, runs in blacklist_dict:
        if (key in reprog_dict):
             if (size(reprog_dict[key]) > 3):
                if (key in power_dict)
                    if (size(power_dict[key])> 3):
                        continue
        if (len(runs) > 3):
            if key in reprog_dict:
                print ("(%i) reprogrammings in runs %s"%(len(reprog_dict[key]), ' '.join(runnum for runnum in reprog_dict[key])) )
            else:
                print("0 reprogrammings")

            if key in power_dict:
                print ("(%i) powercycles in runs %s"%(len(power_dict[key]), ' '.join(runnum for runnum in power_dict[key])) )
            else:
                print("0 powercycles")

            print("(%i) blacklists in runs %s"%(key, len(runs), ' '.join(runnum for runnum in runs)) )
        print("\n")
    return



def make_file(argv):
    tempfile = open("SER_channels_temp.txt","w")
    output = open("SER_channels.txt","w")
    linenum = 0
    for run_dir in argv:
        print(glob.glob(run_dir+"/*"))
        runnum = -99999
        for filename in glob.glob(run_dir+"/*"):
            doFile = open(filename,"r")
            for line in doFile:
                data = line.split()
                if linenum == 0:
                    runnum = data[2]
                    print("The run number is %s"%runnum)
                linenum +=1
                if (linenum > 0) and (runnum < 0):
                    print("Error: something went wrong while reading run number")
                tempfile.write(line+" %s\n"%runnum)      
            doFile.close()
        tempfile.close()
        tempfile = open("SER_channels_temp.txt","r")
        for line in tempfile:
            print(line)
    
    lines = open("SER_channels_temp.txt","r").readlines()
    for line in sorted(lines, key=lambda line: line.split()[0]):
        output.write(line)
    os.remove("SER_channels_temp.txt")
    return


if __name__ == "__main__":
    main(sys.argv[1:])
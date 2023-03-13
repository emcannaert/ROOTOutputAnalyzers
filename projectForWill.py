#! /usr/bin/env python
import sys
import glob
import os
#import numpy as np
import ROOT
from collections import defaultdict

##############################################################################





#USAGE:: Takes in a text file with the format of compare_bpix.txt as an argument, then prints out the difference between pp and cal v_{d} values for different layers/blades (for all layers in detector and also by SEC/DISK)
# also creates plots showing TH1 histograms of v_{d} for both pp and cal superimposed by layer.





##############################################################################




## make plots of vd for different modules and layers

# read in all lines once in order to create the required histograms 
def multi_dict(self,K, type):
    if K == 1:
        return defaultdict(type)
    else:
        return defaultdict(lambda: multi_dict(self,K-1, type))

def createHistograms(self):
    #open first file and get pp/cal values
    inputFile = open(self._fileName,"r")
    for line in inputFile:
        contents = line.split()
        if contents[1] == "vd":
            totROCName = contents[0].split("_")
            det    = totROCName[0]         
            halfC  = totROCName[1]
            numSEC = totROCName[2][-1]    #FOR FPIX: DISK
            numLYR = totROCName[3][-1]    #FOR FPIX: BLD
            numLDR = totROCName[4][3:]    #FOR FPIX: RNG
            numMOD = totROCName[5][-1]    #FOR FPIX: RNG
            numROC = totROCName[6][3:]
            self._pp_values[det][halfC][numSEC][numLYR][numLDR][numMOD][numROC] = float(contents[2])
            self._cal_values[det][halfC][numSEC][numLYR][numLDR][numMOD][numROC] = float(contents[3])

    # draw out vd values for all modules by layer
    numTotalLayers = 0
    weirdROCs = []
    #for all keys in the dictionary, create a histogram for all layers and modules
    for dets in self._pp_values.keys():
        for halfCs in self._pp_values[dets].keys():
            for SECs in self._pp_values[dets][halfCs].keys():
                numBinsLYRs = len(self._pp_values[dets][halfCs][SECs].keys())
                self._LYRHists[dets][halfCs][SECs] = ROOT.TProfile( "%s_%s_%s%s_ppCal_by%s_diff"%(dets,halfCs,self.STR1,SECs,self.STR2) ," vd_{pp}-vd_{Cal} By %s for %s_%s_%s%s"%(self.STR1,dets,halfCs,self.STR1,SECs) ,numBinsLYRs, 1,numBinsLYRs+1) 
                #self._LYRHistsValues[dets][halfCs][SECs] = ROOT.TProfile( "%s_%s_%s%s_by%s_vd"%(dets,halfCs,self.STR1,SECs,self.STR2) ," vd_{pp} By %s for %s_%s_%s%s"%(self.STR2,dets,halfCs,self.STR1,SECs) ,numBinsLYRs, 1,numBinsLYRs+1) 
                avg_layer_pp = 0
                avg_layer_cal = 0
                nMODs = 0
                for iLYR, LYRs in enumerate(self._pp_values[dets][halfCs][SECs].keys()):
                    self._layer_values_TH1D_pp[dets][halfCs][SECs][LYRs]  = ROOT.TH1D( "%s_%s_%s%s_%s%s_by%s_vd_TH1D_pp"%(dets,halfCs,self.STR1,SECs,self.STR2,LYRs,self.STR2) ," v_{d} for %s_%s_%s%s_%s%s_for pp "%(dets,halfCs,self.STR1,SECs,self.STR2,LYRs) ,50 ,0. ,500. )
                    self._layer_values_TH1D_cal[dets][halfCs][SECs][LYRs] = ROOT.TH1D( "%s_%s_%s%s_%s%s_by%s_vd_TH1D_cal"%(dets,halfCs,self.STR1,SECs,self.STR2,LYRs,self.STR1) ," v_{d} for %s_%s_%s%s_%s%s_for cal"%(dets,halfCs,self.STR1,SECs,self.STR2,LYRs) ,50 ,0. ,500. )
                    numROCsPerLayer = 0
                    numTotalLayers+=1
                    for LDRs in self._pp_values[dets][halfCs][SECs][LYRs].keys():
                        numBinsMODs = len(self._pp_values[dets][halfCs][SECs][LYRs][LDRs].keys())
                        self._MODHists[dets][halfCs][SECs][LYRs][LDRs] = ROOT.TProfile( "%s_%s_%s%s_%s%s_%s%s_ppCal_by%s_diff"%(dets,halfCs,self.STR1,SECs,self.STR2,LYRs,self.STR3,LDRs,self.STR4) ," vd_{pp}-vd_{Cal} By %s for %s_%s_%s%s_%s%s_%s%s"%(self.STR4,dets,halfCs,self.STR1,SECs,self.STR2,LYRs,self.STR3,LDRs) ,numBinsMODs , 1,numBinsMODs+1) 
                       # self._MODHistsValues[dets][halfCs][SECs][LYRs][LDRs] = ROOT.TProfile( "%s_%s_%s%s_%s%s_%s%s_by%s_vd"%(dets,halfCs,self.STR1,SECs,self.STR2,LYRs,self.STR3,LDRs,self.STR4) ," vd_{pp} By %s for %s_%s_%s%s_%s%s_%s%s"%(self.STR4,dets,halfCs,self.STR1,SECs,self.STR2,LYRs,self.STR3,LDRs) ,numBinsMODs , 1,numBinsMODs+1) 

                        for iMOD, MODs in enumerate(self._pp_values[dets][halfCs][SECs][LYRs][LDRs].keys()):
                            for ROCs in self._pp_values[dets][halfCs][SECs][LYRs][LDRs][MODs].keys():
                                try:
                                    if ( (self._pp_values[dets][halfCs][SECs][LYRs][LDRs][MODs][ROCs] < 20000. ) and (self._cal_values[dets][halfCs][SECs][LYRs][LDRs][MODs][ROCs] < 20000.) and (self._pp_values[dets][halfCs][SECs][LYRs][LDRs][MODs][ROCs] > 0. ) and (self._cal_values[dets][halfCs][SECs][LYRs][LDRs][MODs][ROCs] > 0.)  ):
                                        #self._MODHistsValues[dets][halfCs][SECs][LYRs][LDRs].Fill(iMOD+1,float(self._pp_values[dets][halfCs][SECs][LYRs][LDRs][MODs][ROCs]),1.0)
                                        #self._LYRHistsValues[dets][halfCs][SECs].Fill(iLYR+1 , float(self._pp_values[dets][halfCs][SECs][LYRs][LDRs][MODs][ROCs]),1.0) 
                                        self._MODHists[dets][halfCs][SECs][LYRs][LDRs].Fill(iMOD+1,float(self._pp_values[dets][halfCs][SECs][LYRs][LDRs][MODs][ROCs])-float(self._cal_values[dets][halfCs][SECs][LYRs][LDRs][MODs][ROCs]),1.0)
                                        self._LYRHists[dets][halfCs][SECs].Fill(iLYR+1 , float(self._pp_values[dets][halfCs][SECs][LYRs][LDRs][MODs][ROCs])-float(self._cal_values[dets][halfCs][SECs][LYRs][LDRs][MODs][ROCs]),1.0) 
                                        self._layer_values_TH1D_pp[dets][halfCs][SECs][LYRs].Fill(float(self._pp_values[dets][halfCs][SECs][LYRs][LDRs][MODs][ROCs]))
                                        self._layer_values_TH1D_cal[dets][halfCs][SECs][LYRs].Fill(float(self._cal_values[dets][halfCs][SECs][LYRs][LDRs][MODs][ROCs]))
                                        numROCsPerLayer+=1
                                        nMODs+=1
                                        avg_layer_pp+= float(self._pp_values[dets][halfCs][SECs][LYRs][LDRs][MODs][ROCs])
                                        avg_layer_cal+= float(self._cal_values[dets][halfCs][SECs][LYRs][LDRs][MODs][ROCs])
                                    if ((  float(self._pp_values[dets][halfCs][SECs][LYRs][LDRs][MODs][ROCs]) > 20000. ) and (float(self._cal_values[dets][halfCs][SECs][LYRs][LDRs][MODs][ROCs]) < 20000.)) or  ((  float(self._pp_values[dets][halfCs][SECs][LYRs][LDRs][MODs][ROCs]) < 20000. ) and (float(self._cal_values[dets][halfCs][SECs][LYRs][LDRs][MODs][ROCs]) > 20000.)):
                                        weirdROCs.append( ["%s_%s_%s%s_%s%s_%s%s_%s%s_ROC%s"%(dets,halfCs,self.STR1,SECs,self.STR2,LYRs,self.STR3,LDRs,self.STR4,MODs,ROCs),float(self._pp_values[dets][halfCs][SECs][LYRs][LDRs][MODs][ROCs]),float(self._cal_values[dets][halfCs][SECs][LYRs][LDRs][MODs][ROCs]) ] )
                                except:
                                    print("ERROR: Couldn't match up values between pp and cal files.")
                                    continue
                
                    if(nMODs>0):              
                        self._allVals_by_layer.append((avg_layer_pp-avg_layer_cal)/nMODs)
                        self._layers_names.append("%s_%s_%s%s_%s%s"%(dets,halfCs,self.STR1,SECs,self.STR2,LYRs))
    for weirdROC in weirdROCs:
        print "Weird ROC: %s vd for pp is %i, vd for cal is %i"%(weirdROC[0],weirdROC[1],weirdROC[2])



def drawHistograms(self):
    c1 = ROOT.TCanvas( 'c1', '', 400,20, 1500,1500);
    detType = ""
    for dets in self._pp_values:
        if detType == "":
            detType = dets
        for halfCs in self._pp_values[dets]:
            for SECs in self._pp_values[dets][halfCs]:
                for iLYR, LYRs in enumerate(self._pp_values[dets][halfCs][SECs]):
                    self._LYRHists[dets][halfCs][SECs].GetXaxis().SetBinLabel(iLYR+1,"%s_%s_%s%s_%s%s"%(dets,halfCs,self.STR1,SECs,self.STR2,LYRs))
                ROOT.gStyle.SetOptStat(0)
                self._LYRHists[dets][halfCs][SECs].GetXaxis().SetLabelSize(0.015);
                self._LYRHists[dets][halfCs][SECs].Draw()
                c1.Print ("vd_pp_vs_cal/%s_%s_%s%s_diff.png"%(dets,halfCs,self.STR1,SECs) )

                for iLYR, LYRs in enumerate(self._pp_values[dets][halfCs][SECs]):
                    ROOT.gStyle.SetOptStat(0)
  
                    self._layer_values_TH1D_pp[dets][halfCs][SECs][LYRs].GetXaxis().SetLabelSize(0.015);
                    self._layer_values_TH1D_cal[dets][halfCs][SECs][LYRs].GetXaxis().SetLabelSize(0.015);
                    self._layer_values_TH1D_pp[dets][halfCs][SECs][LYRs].SetLineColorAlpha(ROOT.kRed, 1.0);
                    self._layer_values_TH1D_cal[dets][halfCs][SECs][LYRs].SetLineColorAlpha(ROOT.kBlue, 0.2);
                    self._layer_values_TH1D_pp[dets][halfCs][SECs][LYRs].Draw()
                    self._layer_values_TH1D_cal[dets][halfCs][SECs][LYRs].Draw("SAME")
                    ROOT.gPad.BuildLegend(0.7,0.7,0.95,0.95);

                    c1.Print ( "vd_pp_vs_cal/h_%s_%s_%s%s_%s%s_pp_vs_cal_TH1.png"%(dets,halfCs,self.STR1,SECs,self.STR2,LYRs))
                    #for LDRs in self._pp_values[dets][halfCs][SECs][LYRs]:
                        #for iMOD, MODs in enumerate(self._pp_values[dets][halfCs][SECs][LYRs][LDRs].keys()):
                            #self._MODHists[dets][halfCs][SECs][LYRs][LDRs].GetXaxis().SetBinLabel(iMOD+1,"%s_%s_%s%s_%s%s_%s%s_%s%s"%(dets,halfCs,self.STR1,SECs,self.STR2,LYRs,self.STR3,LDRs,self.STR4,MODs))
                            #self._MODHistsValues[dets][halfCs][SECs][LYRs][LDRs].GetXaxis().SetBinLabel(iMOD+1,"%s_%s_SEC%s_LYR%s_LDR%s_MOD%s"%(dets,halfCs,SECs,LYRs,LDRs,MODs))
                        ## comment this to run faster    
                        #ROOT.gStyle.SetOptStat(0)
                        #self._MODHists[dets][halfCs][SECs][LYRs][LDRs].GetXaxis().SetLabelSize(0.015);
                        #self._MODHists[dets][halfCs][SECs][LYRs][LDRs].Draw()
                        #c1.Print ( "vd_pp_vs_cal/%s_%s_SEC%s_LYR%s_LDR%s_diff.png"%(dets,halfCs,SECs,LYRs,LDRs))
                        #self._MODHistsValues[dets][halfCs][SECs][LYRs][LDRs].GetXaxis().SetLabelSize(0.015);
                        #self._MODHistsValues[dets][halfCs][SECs][LYRs][LDRs].Draw()
                        #c1.Print ( "vd_pp_vs_cal/%s_%s_SEC%s_LYR%s_LDR%s_vd.png"%(dets,halfCs,SECs,LYRs,LDRs))

    h_allVals_by_layer = ROOT.TProfile( "vd_{pp}-vd_{cal} for all %s"%self.STR2 ,"vd_{pp}-vd_{cal} difference By %s"%self.STR2,len(self._allVals_by_layer), 1 ,len(self._allVals_by_layer)+1) 
    for iLYR, layerVal in enumerate(self._allVals_by_layer):
        h_allVals_by_layer.Fill(iLYR+1, layerVal)
        h_allVals_by_layer.GetXaxis().SetBinLabel(iLYR+1,self._layers_names[iLYR])
    h_allVals_by_layer.GetXaxis().SetLabelSize(0.01);
    h_allVals_by_layer.Draw("E1")
    c1.Print ( "vd_pp_vs_cal/%s_vd_all_%s.png"%(detType,self.STR2)) 
    return


def setStrings(self):
    if ("bpix" in self._fileName) or ("BPIX" in self._fileName) or ("Bpix" in self._fileName) or ("BPix" in self._fileName):
        self.STR1 = "SEC"
        self.STR2 = "LYR"
        self.STR3 = "LDR"
        self.STR4 = "MOD"
        return
    elif ("fpix" in self._fileName) or ("FPIX" in self._fileName) or ("Fpix" in self._fileName) or ("FPix" in self._fileName):
        self.STR1 = "D"
        self.STR2 = "BLD"
        self.STR3 = "PNL"
        self.STR4 = "RNG"
        return
    else:
        print("ERROR: something wrong with file name - use format compare_<fpix/bpix>.txt, or at least specify fpix/bpix in file name.")
        return

class analyzeFile:

    _createHistograms = createHistograms
    _multi_dict = multi_dict
    _drawHistograms = drawHistograms
    _setStrings = setStrings
    def __init__(self,filename):
        #self.name = name
        self._fileName = filename
        self.STR1 = ""
        self.STR2 = ""
        self.STR3 = ""
        self.STR4 = ""
        self._setStrings()
        self._pp_values = self._multi_dict(7, str,)
        self._cal_values = self._multi_dict(7, str,)

        self._MODHists = self._multi_dict(6, str,)
        self._LYRHists = self._multi_dict(3, str,)
        self._MODHistsValues = self._multi_dict(6, str,)
        self._LYRHistsValues = self._multi_dict(3, str,)
        self._allVals_by_layer = []
        self._layers_names = []
        self._layer_values_TH1D_pp = self._multi_dict(4, str,)
        self._layer_values_TH1D_cal = self._multi_dict(4, str,)

        self._createHistograms()
        self._drawHistograms()
def main(argv): 
    if len(argv)> 0:
        analyzeFile(argv[0])
    else:
        analyzeFile(argv)
    


if __name__ == "__main__":
    main(sys.argv[1:])


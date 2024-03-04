import sys
import ROOT
import glob
from get_file_info import get_file_info
######### usage information ##########

# first submit jobs for calculateBtagEFficiencyMaps for each sample and year 
# hadd these files together and put the combined root file in the data folder
# with the name scheme btagging_efficiencyMap_<sample>_<year>_output.root 
# Important: The output files are combined by background: ["QCDMC_combined","TTBarMC_combined","STMC_combined"]
# you can run all years and samples by giving the single option ALL
# this will only need to be done once unless some huge change is made
# from this information, the actual efficiency maps are made with this script
# this takes in the name of your sample and the year and write the output 
# efficiency map root file to the data/ folder
# 

######################################



def checkBtagEffMap(inFileName):

   #inFileName  = "../data/btaggingEffMapsRAW/btagging_efficiencyMap_%s_%s_output.root"%(sample,year)

   year, sample,systematic = get_file_info.get_file_info(inFileName)
   inFile = ROOT.TFile.Open(inFileName, "READ")

   h_effLight = inFile.Get( "h_effLightJets")
   h_effTrueb = inFile.Get( "h_effcJets")
   h_effTruec = inFile.Get( "h_effbJets")

   c = ROOT.TCanvas("","",1000,1000)

   h_empty_effLight = ROOT.TH2F("h_empty_effLight","Empty eff map bins (light jets); pt;eta",30,0, 3000, 18, -2.4, 2.4)
   h_empty_effTruec = ROOT.TH2F("h_empty_effTruec","Empty eff map bins; pt (true c);eta",30,0, 3000, 18, -2.4, 2.4)
   h_empty_effTrueb = ROOT.TH2F("h_empty_effTrueb","Empty eff map bins (true b); pt;eta", 30,0, 3000, 18, -2.4, 2.4)

   # /Users/ethan/Documents/plots/btagEffMapPlots
   max_bin = 31

   print("Looking at h_effLight")
   for iii in range(1, h_effLight.GetNbinsX()+1):
      for jjj in range(1, h_effLight.GetNbinsY() +1):
         if( h_effLight.GetBinContent(iii,jjj) <  1e-10):
            print("Found bad bin: (%i,%i), value = %s"%(iii,jjj,h_effLight.GetBinContent(iii,jjj) ))
            h_empty_effLight.SetBinContent(iii,jjj,1)


   h_empty_effLight.SetBinContent(1,1,5)
   h_empty_effLight.SetBinContent(30,18,2)
   h_empty_effLight.SetBinContent(1,18,3)
   h_empty_effLight.SetBinContent(30,1,4)
   print("Looking at h_effTrueb")
   for iii in range(1, h_effTrueb.GetNbinsX()+1):
      for jjj in range(1, h_effTrueb.GetNbinsY()+1):
         if( h_effTrueb.GetBinContent(iii,jjj) <  1e-10):
            print("Found bad bin: (%i,%i), value = %s"%(iii,jjj,h_effTrueb.GetBinContent(iii,jjj) ))
            h_empty_effTrueb.SetBinContent(iii,jjj,1)

   h_empty_effTrueb.SetBinContent(1,1,5)
   h_empty_effTrueb.SetBinContent(30,18,2)
   h_empty_effTrueb.SetBinContent(1,18,3)
   h_empty_effTrueb.SetBinContent(30,1,4)
   print("Looking at h_effTruec")
   for iii in range(1, h_effTruec.GetNbinsX()+1):
      for jjj in range(1, h_effTruec.GetNbinsY()+1):
         if( h_effTruec.GetBinContent(iii,jjj) <  1e-10):
            print("Found bad bin: (%s,%s), value = %s"%(iii,jjj,h_effTruec.GetBinContent(iii,jjj) ))
            h_empty_effTruec.SetBinContent(iii,jjj,1)
   h_empty_effTruec.SetBinContent(1,1,5)
   h_empty_effTruec.SetBinContent(30,18,2)
   h_empty_effTruec.SetBinContent(1,18,3)
   h_empty_effTruec.SetBinContent(30,1,4)

   h_empty_effLight.Draw("colz")
   c.SaveAs("/Users/ethan/Documents/plots/btagEffMapPlots/h_empty_effLight_%s.png"%sample)
   h_empty_effTruec.Draw("colz")
   c.SaveAs("/Users/ethan/Documents/plots/btagEffMapPlots/h_empty_effTruec_%s.png"%sample)
   h_empty_effTrueb.Draw("colz")
   c.SaveAs("/Users/ethan/Documents/plots/btagEffMapPlots/h_empty_effTrueb_%s.png"%sample)


   return
   
if __name__ == "__main__":
   filenames =  glob.glob("/Users/ethan/Documents/rootFiles/btaggingEfficiencyFiles/btaggingEffMaps/*2018*.root")
   for inFileName in filenames:
      print("Looking at file: %s"%inFileName)
      if "QCD" not in inFileName:
         continue
      checkBtagEffMap(inFileName)



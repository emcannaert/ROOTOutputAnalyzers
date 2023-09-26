#include <iostream>
#include <string>
#include "TLorentzVector.h"

using namespace std;

void doThings(std::string inFileName, std::string outFileName, double& nEvents,double &nHTcut,  double &nAK8JetCut, double &nHeavyAK8Cut,double &nBtagCut,double &nDoubleTagged, double &eventScaleFactors, std::string year)
{
   double totHT, dijetMassOne, dijetMassTwo;
   int nfatjets, nfatjet_pre;
   const char *_inFilename = inFileName.c_str();

   std::cout << "Reading file: " << _inFilename << std::endl;
   TFile *f = new TFile(_inFilename);
   
   const char *_outFilename = outFileName.c_str();

   TFile outFile(_outFilename,"RECREATE");
   
   TTree *t1 = (TTree*)f->Get("clusteringAnalyzerAll_/tree_");   // TO do 
   auto *t2 = t1->CloneTree(0);
   t2->SetName("skimmedTree");

   const Int_t nentries = t1->GetEntries();


   t1->SetBranchAddress("totHT", &totHT);   
   t1->SetBranchAddress("nfatjets", &nfatjets);     
   t1->SetBranchAddress("nfatjet_pre", &nfatjet_pre); 
   t1->SetBranchAddress("dijetMassOne", &dijetMassOne);   
   t1->SetBranchAddress("dijetMassTwo", &dijetMassTwo);   

   for (Int_t i=0;i<nentries;i++) 
   {  
      nEvents+=eventScaleFactors;
      t1->GetEntry(i);
      if (totHT < 1500.) continue; 
      nHTcut+=eventScaleFactors;
      if( (nfatjets < 3)   ) continue;
      nAK8JetCut+=eventScaleFactors;
      if ((nfatjet_pre < 2) && ( (dijetMassOne < 1000. ) || ( dijetMassTwo < 1000.)  ))continue;

      nHeavyAK8Cut+=eventScaleFactors;
      t2->Fill();
   }
   outFile.Write();
}


void readTreeApplySelection()
{

   // you must change these ........
   bool runData = false;
   bool includeTTBar = true;
   bool allHTBins    = true;
   double nEvents = 0.;
   double nHTcut  = 0.;
   double nAK8JetCut = 0.;
   double nHeavyAK8Cut = 0.;
   double nBtagCut = 0.;
   double nDoubleTagged = 0.;
   std::vector<std::string> dataYear = {"2015","2016","2017","2018"};
   
   if(!runData)
   {
      int yearNum = 0;
      if(includeTTBar && allHTBins)
      {


         //need to have the event scale factors calculated for each year and dataset
         double eventScaleFactors[4][4] = {  {1.0,1.0,1.0}, {1.0,1.0,1.0}, {1.0,1.0,1.0},{1.0,1.0,1.0}   }; //TODO
         for(auto year = dataYear.begin();year<dataYear.end();year++)
         {
            std::string dataYear = *year;
            std::vector<std::string> inFileNames = {
                                              ("/Users/ethan/Documents/rootFiles/combinedFilesAltDatasets/QCDMC_HT1000to1500_" +dataYear +"_combined.root").c_str(),
                                              ("/Users/ethan/Documents/rootFiles/combinedFilesAltDatasets/QCDMC_HT1500to2000_" +dataYear +"_combined.root").c_str(),
                                               ("/Users/ethan/Documents/rootFiles/combinedFilesAltDatasets/QCDMC_HT2000toInf_" +dataYear +"_combined.root").c_str(),
                                               ("/Users/ethan/Documents/rootFiles/combinedFilesAltDatasets/TTTohadronic_" +dataYear +"_combined.root").c_str()
                                            };
            std::vector<std::string> outFileNames = {
                                              ("/Users/ethan/Documents/rootFiles/skimmedRootFilesAlt/QCDMC_HT1000to1500_" +dataYear +"_SKIMMED.root").c_str(),
                                              ("/Users/ethan/Documents/rootFiles/skimmedRootFilesAlt/QCDMC_HT1500to2000_" +dataYear +"_SKIMMED.root").c_str(),
                                               ("/Users/ethan/Documents/rootFiles/skimmedRootFilesAlt/QCDMC_HT2000toInf_" +dataYear +"_SKIMMED.root").c_str(),
                                               ("/Users/ethan/Documents/rootFiles/skimmedRootFilesAlt/TTTohadronic_" +dataYear +"_SKIMMED.root").c_str()
                                            };
        
            for(unsigned int iii = 0; iii<inFileNames.size(); iii++)
            {
               doThings(inFileNames[iii],outFileNames[iii],nEvents,nHTcut,nAK8JetCut,nHeavyAK8Cut,nBtagCut,nDoubleTagged,eventScaleFactors[yearNum][iii],*year);
            }

            std::cout << "Finished with "<< inFileNames.size() << " files for "<< *year<< "." << std::endl;
            std::cout << "For " << *year<< ": total/HTcut/AK8jetCut/heavyAK8JetCut:" <<nEvents << "/" << nHTcut << "/" << nAK8JetCut<< "/" << nHeavyAK8Cut<< std::endl;

            yearNum++;
         }


      }
   }
}

//look at nBtag plots ... 
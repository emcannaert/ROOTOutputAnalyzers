#include <iostream>
#include <string>
#include "TLorentzVector.h"

using namespace std;

void doThings(std::string inFileName, std::string outFileName, double& nEvents,double &nHTcut,  double &nAK8JetCut, double &nHeavyAK8Cut,double &nBtagCut,double &nDoubleTagged, double &eventScaleFactors)
{

   double totHT, dijetMassOne, dijetMassTwo;
   int nfatjets, nfatjet_pre;
   const char *_inFilename = inFileName.c_str();

   std::cout << "Reading file: " << _inFilename << std::endl;
   TFile *f = new TFile(_inFilename);
   
   const char *_outFilename = outFileName.c_str();

   TFile outFile(_outFilename,"RECREATE");
   
   TTree *t1 = (TTree*)f->Get("clusteringAnalyzerAll/tree_");   // TO do 
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
   std::string dataYear = "2018";

   if(!runData)
   {
      if(includeTTBar && allHTBins)
      {
         double eventScaleFactors[3] = {0.6042726685,0.2132134533,0.06588049107};//,0.03616639075,0.04563489275};

         std::vector<std::string> inFileNames = {
                                           "/home/ethan/Documents/rootFiles/QCD_HT1500to2000_2018_combined.root",
                                           "/home/ethan/Documents/rootFiles/QCD_HT2000toInf_2018_combined.root",
                                            "/home/ethan/Documents/rootFiles/TTToHadronic_combined.root"};//,
                                            //"/home/ethan/TTToLeptonic.root",
                                            //"/home/ethan/TTToSemiLeptonic.root" };
         std::vector<std::string> outFileNames = {
                                               "/home/ethan/Documents/rootFiles/skimmedRootFiles/QCD_HT1500to2000_SKIMMED.root",
                                               "/home/ethan/Documents/rootFiles/skimmedRootFiles/QCD_HT2000toInf_SKIMMED.root",
                                               "/home/ethan/Documents/rootFiles/skimmedRootFiles/TTToHadronic_SKIMMED.root"};//,
                                               //"/home/ethan/Documents/TTTo2l2nu_combine_cutbased_SKIMMED.root",
                                               //"/home/ethan/Documents/TTtoSemiLeptonic_SKIMMED.root" };
     
         for(unsigned int iii = 0; iii<inFileNames.size(); iii++)
         {
            doThings(inFileNames[iii],outFileNames[iii],nEvents,nHTcut,nAK8JetCut,nHeavyAK8Cut,nBtagCut,nDoubleTagged,eventScaleFactors[iii]);
         }

         std::cout << "Finished with "<< inFileNames.size() << " files." << std::endl;
      }
      else if( !includeTTBar && allHTBins)
      {
      double eventScaleFactors[3] = {4.289571744,0.6042726685,0.2132134533};//,0.03616639075,0.04563489275};

         std::vector<std::string> inFileNames = {("/home/ethan/Documents/rootFiles/QCD_HT1000to1500_" + dataYear + ".root").c_str(),("/home/ethan/Documents/rootFiles/QCD_HT1500to2000_" + dataYear + ".root").c_str(), ("/home/ethan/Documents/rootFiles/QCD_HT2000toInf_" + dataYear + ".root").c_str()};

         std::vector<std::string> outFileNames = {("/home/ethan/Documents/rootFiles/skimmedRootFiles/QCD_HT1000to1500_SKIMMED_"+ dataYear + ".root").c_str(),("/home/ethan/Documents/rootFiles/skimmedRootFiles/QCD_HT1500to2000_SKIMMED_"+ dataYear + ".root").c_str(),("/home/ethan/Documents/rootFiles/skimmedRootFiles/QCD_HT2000toInf_SKIMMED_"+ dataYear + ".root").c_str()};
         for(unsigned int iii = 0; iii<inFileNames.size(); iii++)
         {
            doThings(inFileNames[iii],outFileNames[iii],nEvents,nHTcut,nAK8JetCut,nHeavyAK8Cut,nBtagCut,nDoubleTagged,eventScaleFactors[iii]);
         }
         std::cout << "Finished with "<< inFileNames.size() << " files." << std::endl;
      }
      else
      {
         double eventScaleFactors[1] = {0.2132134533};//,0.03616639075,0.04563489275};

         std::vector<std::string> inFileNames = {("/home/ethan/Documents/rootFiles/QCD_HT2000toInf_" + dataYear + ".root").c_str()};

         std::vector<std::string> outFileNames = {("/home/ethan/Documents/rootFiles/skimmedRootFiles/QCD_HT2000toInf_SKIMMED_"+ dataYear + ".root").c_str()};
         for(unsigned int iii = 0; iii<inFileNames.size(); iii++)
         {
            doThings(inFileNames[iii],outFileNames[iii],nEvents,nHTcut,nAK8JetCut,nHeavyAK8Cut,nBtagCut,nDoubleTagged,eventScaleFactors[iii]);
         }

         std::cout << "Finished with "<< inFileNames.size() << " files." << std::endl;
      }

   }
   else if(runData)
   {
      double eventScaleFactors[4] = {1.0,1.0,1.0,1.0};//,0.03616639075,0.04563489275};

      std::vector<std::string> inFileNames = {
                                        "/home/ethan/Documents/rootFiles/JetHT_2018A.root",
                                        "/home/ethan/Documents/rootFiles/JetHT_2018B.root",
                                         "/home/ethan/Documents/rootFiles/JetHT_2018C.root",
                                         "/home/ethan/Documents/rootFiles/JetHT_2018D.root"};

      std::vector<std::string> outFileNames = {
                                            "/home/ethan/Documents/rootFiles/skimmedRootFiles/JetHT_2018A_SKIMMED.root",
                                            "/home/ethan/Documents/rootFiles/skimmedRootFiles/JetHT_2018B_SKIMMED.root",
                                            "/home/ethan/Documents/rootFiles/skimmedRootFiles/JetHT_2018C_SKIMMED.root",
                                            "/home/ethan/Documents/rootFiles/skimmedRootFiles/JetHT_2018D_SKIMMED.root"};
  
      for(unsigned int iii = 0; iii<inFileNames.size(); iii++)
      {
            doThings(inFileNames[iii],outFileNames[iii],nEvents,nHTcut,nAK8JetCut,nHeavyAK8Cut,nBtagCut,nDoubleTagged,eventScaleFactors[iii]);
      }

      std::cout << "Finished with "<< inFileNames.size() << " files." << std::endl;      
   }
   std::cout << "total/HTcut/AK8jetCut/heavyAK8JetCut:" <<nEvents << "/" << nHTcut << "/" << nAK8JetCut<< "/" << nHeavyAK8Cut<< std::endl;
}

//look at nBtag plots ... 
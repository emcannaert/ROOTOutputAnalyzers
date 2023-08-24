#include <iostream>
#include <string>
#include "TLorentzVector.h"

using namespace std;

void doThings(std::string inFileName,std::string outFileName, std::string treeName)
{

   const char *_inFilename = inFileName.c_str();

   std::cout << "Reading file: " << _inFilename << std::endl;
   TFile *f = new TFile(_inFilename);
   double superJet_mass[100];
   const char *_outFilename = outFileName.c_str();

   TFile outFile(_outFilename,"RECREATE");
   
   TTree *t1 = (TTree*)f->Get(treeName.c_str());   // TO do 

   const Int_t nentries = t1->GetEntries();


   t1->SetBranchAddress("superJet_mass", superJet_mass);   


   TH1F* h_SJ_mass_JEC  = new TH1F("h_SJ_mass_JEC","superjet mass (JEC nom);Mass [GeV]; Events / 100 GeV",40,0.,4000);
   std::cout << nentries << std::endl;
   for (Int_t i=0;i<nentries;i++) 
   {  
      t1->GetEntry(i);
      h_SJ_mass_JEC->Fill(superJet_mass[0]);
      h_SJ_mass_JEC->Fill(superJet_mass[1]);

   }
   outFile.Write();
}


void extractHistsFromTree()
{

         std::vector<std::string> inFileNames = {
                                           "/home/ethan/Documents/rootFiles/ClusteringAlgorithmBR_JECup_output.root",
                                           "/home/ethan/Documents/rootFiles/ClusteringAlgorithmBR_data_output.root",
                                            "/home/ethan/Documents/rootFiles/ClusteringAlgorithmBR_JECdown_output.root"};//,

         std::vector<std::string> outFileNames = {
                                               "/home/ethan/Documents/rootFiles/processedRootFiles/ClusteringAlgorithmBR_JECup_output_processed.root",
                                               "/home/ethan/Documents/rootFiles/processedRootFiles/ClusteringAlgorithmBR_data_output_processed.root",
                                               "/home/ethan/Documents/rootFiles/processedRootFiles/ClusteringAlgorithmBR_JECdown_output_processed.root"};//,

         std::vector<std::string> treeName = {"clusteringAnalyzerAll/tree_JEC_up","clusteringAnalyzerAll/tree_","clusteringAnalyzerAll/tree_JEC_down"};
         for(unsigned int iii = 0; iii<inFileNames.size(); iii++)
         {
            doThings(inFileNames[iii],outFileNames[iii], treeName[iii]);
         }

         std::cout << "Finished with "<< inFileNames.size() << " files." << std::endl;

}

//look at nBtag plots ... 
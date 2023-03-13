#include <iostream>
#include <string>
#include "TLorentzVector.h"
#include <math.h>
using namespace std;

void doThings(std::string inFileName, std::string outFileName, std::string dataYear)
{
   int nfatjets = 0;
   double jet_pt[100], jet_mass[100];
   double AK4_mass_100[100];
   double superJet_mass[100];
   int SJ_nAK4_200[100],SJ_nAK4_300[100];
   int nAK4;
   int SJ_nAK4_100[100];
   double SJ_mass_100[100];
   double totHT = 0;
   int nfatjet_pre;

   double AK4_DeepJet_disc[100];
   double AK4_pt[100];
   double diSuperJet_mass;
   double AK4_bdisc[100];
   double dijetMassOne, dijetMassTwo;
   double AK4_ptot[100], AK4_eta[100], AK4_phi[100];
   int nGenBJets_AK4[100], AK4_partonFlavour[100],AK4_HadronFlavour[100];

   TH2F *h_nLightJets = new TH2F("h_nLightJets" ,"total number of true light jets; jet p_{T} [GeV];jet eta", 50,0, 2500, 24, -2.4, 2.4);
   TH2F *h_nTruebJets = new TH2F("h_nTruebJets" ,"total number of true b jets; jet p_{T} [GeV];jet eta", 50,0, 2500, 24, -2.4, 2.4);
   TH2F *h_nTruecJets = new TH2F("h_nTruecJets" ,"total number of true c jets; jet p_{T} [GeV];jet eta", 50,0, 2500, 24, -2.4, 2.4);

   TH2F *h_nLightJets_btagged = new TH2F("h_nLightJets_btagged" ,"total number of true light jets that are b-tagged; jet p_{T} [GeV];jet eta", 50,0, 2500, 24, -2.4, 2.4);
   TH2F *h_nTruebJets_btagged = new TH2F("h_nTruebJets_btagged" ,"total number of true b jets that are b-tagged; jet p_{T} [GeV];jet eta", 50,0, 2500, 24, -2.4, 2.4);
   TH2F *h_nTruecJets_btagged = new TH2F("h_nTruecJets_btagged" ,"total number of true c jets that are b-tagged; jet p_{T} [GeV];jet eta", 50,0, 2500, 24, -2.4, 2.4);


   TH2F *h_effLightJets = new TH2F( "h_effLightJets" ,"total number of true light jets that are b-tagged / total number of true light; jet p_{T} [GeV];jet eta", 50,0, 2500, 24, -2.4, 2.4);
   TH2F *h_effbJets = new TH2F( "h_effbJets" ,"total number of true b jets that are b-tagged / total number of true b jets; jet p_{T} [GeV];jet eta", 50,0, 2500, 24, -2.4, 2.4);
   TH2F *h_effcJets = new TH2F( "h_effcJets" ,"total number of true c jets that are b-tagged / total number of true c jets; jet p_{T} [GeV];jet eta", 50,0, 2500, 24, -2.4, 2.4);

   const char *_inFilename = inFileName.c_str();
   const char *_outFilename = outFileName.c_str();


   TFile *f = new TFile(_inFilename);
   TFile outFile(_outFilename,"RECREATE");

   TTree *t1 = (TTree*)f->Get("clusteringAnalyzerBR/tree");
   const Int_t nentries = t1->GetEntries();


   t1->SetBranchAddress("totHT", &totHT);   
   t1->SetBranchAddress("nfatjets", &nfatjets);     
   t1->SetBranchAddress("diSuperJet_mass", &diSuperJet_mass);   
   t1->SetBranchAddress("nfatjet_pre", &nfatjet_pre); 
   
   t1->SetBranchAddress("jet_mass", jet_mass);   
   t1->SetBranchAddress("totHT", &totHT);

   t1->SetBranchAddress("superJet_mass", superJet_mass);   

   t1->SetBranchAddress("SJ_nAK4_200", SJ_nAK4_200);  
   t1->SetBranchAddress("SJ_nAK4_300", SJ_nAK4_300);     

   t1->SetBranchAddress("nAK4" , &nAK4); 
   t1->SetBranchAddress("lab_AK4_pt", AK4_pt);     

   t1->SetBranchAddress("SJ_mass_100", SJ_mass_100);   

   t1->SetBranchAddress("dijetMassOne", &dijetMassOne); 
   t1->SetBranchAddress("dijetMassTwo", &dijetMassTwo); 
   t1->SetBranchAddress("AK4_DeepJet_disc", AK4_DeepJet_disc); 
   t1->SetBranchAddress("AK4_bdisc", AK4_bdisc); 

   t1->SetBranchAddress("AK4_partonFlavour", AK4_partonFlavour); 
   t1->SetBranchAddress("AK4_hadronFlavour", AK4_HadronFlavour); 

   t1->SetBranchAddress("AK4_eta", AK4_eta); 
   t1->SetBranchAddress("AK4_phi", AK4_phi); 
   t1->SetBranchAddress("AK4_ptot", AK4_ptot); 


   // depending on the year, change the WPs 

   double looseDeepJet;
   double medDeepJet;
   double tightDeepJet;

   double looseDeepCSV = 0.1241;
   double medDeepCSV   = 0.4184;
   double tightDeepCSV = 0.7527;

   if(dataYear == "2016")   //preVFP
   {
      looseDeepJet = 0.0508;
      medDeepJet   = 0.2598;
      tightDeepJet = 0.6502;
   }
   else if(dataYear == "2017")
   {
      looseDeepJet = 0.0532;
      medDeepJet   = 0.3040;
      tightDeepJet = 0.7476;
   }
   else if(dataYear == "2018")
   {
      looseDeepJet = 0.0490;
      medDeepJet   = 0.2783;
      tightDeepJet = 0.7100;
   }
   int nGenBtags[50] = {0},nRECOBtags[50] = {0};

   for (Int_t i=0;i<nentries;i++) 
   {  
      t1->GetEntry(i);

      /*      
      if( (nfatjets < 3) || (totHT < 1500.)     ) continue;

      if ((nfatjet_pre < 2) && ( (dijetMassOne < 1000. ) || ( dijetMassTwo < 1000.)  ))
      {
         continue;
      } 
      */
      for(int iii = 0;iii< nAK4; iii++)
      {

         if(AK4_HadronFlavour[iii] == 0)   //light jets
         {
            h_nLightJets->Fill(AK4_pt[iii],AK4_eta[iii]);
            if(AK4_DeepJet_disc[iii] > tightDeepJet)
            {
               h_nLightJets_btagged->Fill(AK4_pt[iii],AK4_eta[iii]);
               h_effLightJets->Fill(AK4_pt[iii],AK4_eta[iii]);
            }
         }
         else if(AK4_HadronFlavour[iii] == 4) //charm jets
         {
            h_nTruecJets->Fill(AK4_pt[iii],AK4_eta[iii]);
            if(AK4_DeepJet_disc[iii] > tightDeepJet)
            {
               h_nTruecJets_btagged->Fill(AK4_pt[iii],AK4_eta[iii]);
               h_effcJets->Fill(AK4_pt[iii],AK4_eta[iii]);
            }
         }
         else if(AK4_HadronFlavour[iii] == 5) // b jets
         {
            h_nTruebJets->Fill(AK4_pt[iii],AK4_eta[iii]);
            if(AK4_DeepJet_disc[iii] > tightDeepJet)
            {
               h_nTruebJets_btagged->Fill(AK4_pt[iii],AK4_eta[iii]);
               h_effbJets->Fill(AK4_pt[iii],AK4_eta[iii]);
            }

         }
      }
   }



   /*
      TH2F *h_nLightJets = new TH2F( ("h_nLightJets_"+ dataYear).c_str() ,"total number of true light jets; jet p_{T} [GeV];jet eta", 40,0, 2000, 24, -2.4, 2.4);
   TH2F *h_nTruebJets = new TH2F( ("h_nTruebJets"+ dataYear).c_str() ,"total number of true b jets; jet p_{T} [GeV];jet eta", 40,0, 2000, 24, -2.4, 2.4);
   TH2F *h_nTruecJets = new TH2F( ("h_nTruecJets"+ dataYear).c_str() ,"total number of true c jets; jet p_{T} [GeV];jet eta", 40,0, 2000, 24, -2.4, 2.4);

   TH2F *h_nLightJets_btagged = new TH2F( ("h_nLightJets_btagged_"+ dataYear).c_str() ,"total number of true light jets that are b-tagged; jet p_{T} [GeV];jet eta", 40,0, 2000, 24, -2.4, 2.4);
   TH2F *h_nTruebJets_btagged = new TH2F( ("h_nTruebJets_btagged_"+ dataYear).c_str() ,"total number of true b jets that are b-tagged; jet p_{T} [GeV];jet eta", 40,0, 2000, 24, -2.4, 2.4);
   TH2F *h_nTruecJets_btagged = new TH2F( ("h_nTruecJets_btagged_"+ dataYear).c_str() ,"total number of true c jets that are b-tagged; jet p_{T} [GeV];jet eta", 40,0, 2000, 24, -2.4, 2.4);

   */

   h_effLightJets->Divide(h_nLightJets);
   h_effcJets->Divide(h_nTruecJets);
   h_effbJets->Divide(h_nTruebJets);

  TCanvas *c1 = new TCanvas("c1","",400,20, 1500,1500);

   h_effbJets->Draw("colz");
   c1->SaveAs("h_effbJets.png"); 

   outFile.Write();
}


void readTreeMakeEfficiencyMaps()
{
   bool includeTTBar = false;
   std::string dataYear  = "2018";
   if(includeTTBar)
   {

      std::vector<std::string> inFileNames = {("/home/ethan/QCD_HT1000to1500_" + dataYear + ".root").c_str(),("/home/ethan/QCD_HT1500to2000_" + dataYear + ".root").c_str(), ("/home/ethan/QCD_HT2000toInf_" + dataYear + ".root").c_str()};
      std::vector<std::string> outFileNames = {("/home/ethan/Documents/QCD_HT1000to1500_efficiencyMap_"+ dataYear + ".root").c_str(),("/home/ethan/Documents/QCD_HT1500to2000_efficiencyMap_"+ dataYear + ".root").c_str(),("/home/ethan/Documents/QCD_HT2000toInf_efficiencyMap_"+ dataYear + ".root").c_str()};

      for(unsigned int iii = 0; iii<inFileNames.size(); iii++)
      {
         doThings(inFileNames[iii],outFileNames[iii],dataYear);
      }
      std::cout << "Finished creating efficiency maps for "<< inFileNames.size() << " files." << std::endl;
      std::cout << "Efficiency map files are ";
      for(auto iii = outFileNames.begin(); iii< outFileNames.end(); iii++)
      {
         std::cout << *iii << " ";
      }
      std::cout << std::endl;
   }
   else
   {

      std::vector<std::string> inFileNames = { ("/home/ethan/QCD_HT2000toInf_" + dataYear + ".root").c_str()};
      std::vector<std::string> outFileNames = {("/home/ethan/Documents/QCD_HT2000toInf_efficiencyMap_"+ dataYear + ".root").c_str()};

      for(unsigned int iii = 0; iii<inFileNames.size(); iii++)
      {
         doThings(inFileNames[iii],outFileNames[iii],dataYear);
      }
      std::cout << "Finished creating efficiency maps for "<< inFileNames.size() << " files." << std::endl;
      std::cout << "Efficiency map files are ";
      for(auto iii = outFileNames.begin(); iii< outFileNames.end(); iii++)
      {
         std::cout << *iii << " ";
      }
      std::cout << std::endl;

   }



}

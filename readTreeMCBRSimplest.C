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
   int nGenBJets_AK4[100], AK4_partonFlavour[100],AK4_HadronFlavour[100];


   const char *_inFilename = inFileName.c_str();
   const char *_outFilename = outFileName.c_str();


   TFile *f = new TFile(_inFilename);
   TFile outFile(_outFilename,"RECREATE");

   TH1F* h_totHT  = new TH1F("h_totHT","Total Event HT;H_{T} [GeV]; Events / 200 GeV",50,0.,10000);

   TH1F* h_totHT_DT  = new TH1F("h_totHT_DT","Event H_{T} (DT region);H_{T} [GeV]; Events / 200 GeV",50,0.,10000);
   TH1F* h_totHT_CR  = new TH1F("h_totHT_CR","Event H_{T} (CR region);H_{T} [GeV]; Events / 200 GeV",50,0.,10000);

   TH1F* h_SJ_mass_DT  = new TH1F("h_SJ_mass_DT","SuperJet Mass (Signal Region) ;Mass [GeV] ; Events / 125 GeV",40,0.,5000);
   TH1F* h_SJ_mass_CR  = new TH1F("h_SJ_mass_CR","SuperJet Mass (Control Region) ;Mass [GeV]; Events / 125 GeV",40,0.,5000);

   TH1F* h_disuperjet_mass_DT  = new TH1F("h_disuperjet_mass_DT","diSuperJet Mass (Signal Region) ;Mass [GeV]; Events / 400 GeV",25,0.,10000);
   TH1F* h_disuperjet_mass_CR  = new TH1F("h_disuperjet_mass_CR","diSuperJet Mass (Control Region);Mass[ GeV]; Events / 400 GeV",25,0.,10000);


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
   for (Int_t i=0;i<nentries;i++) 
   {  
      t1->GetEntry(i);
      
      if( (nfatjets < 3) || (totHT < 1500.)     ) continue;

      if ((nfatjet_pre < 2) && ( (dijetMassOne < 1000. ) || ( dijetMassTwo < 1000.)  ))
      {
         continue;
      } 
      h_totHT->Fill(totHT);

      //btagging stuff 
      int nLooseBtags = 0;
      int nMedBtags   = 0;
      int nTightBtags = 0;

      for(int iii = 0;iii< nAK4; iii++)
      {

         if ( (AK4_DeepJet_disc[iii] > looseDeepJet ) && (AK4_pt[iii] > 30.) ) nLooseBtags++;
         if ( (AK4_DeepJet_disc[iii] > medDeepJet )   && (AK4_pt[iii] > 30.) )   nMedBtags++;
         if ( (AK4_DeepJet_disc[iii] > tightDeepJet ) && (AK4_pt[iii] > 30.) ) nTightBtags++;

      }

      /// control region 
      if( nTightBtags < 1 ) 
      {
         h_totHT_CR->Fill(totHT);
         h_SJ_mass_CR->Fill(superJet_mass[0]);
         //h_SJ_mass_CR->Fill(superJet_mass[1]);
         h_disuperjet_mass_CR->Fill(diSuperJet_mass);

      }

      // signal region
      if ( (nTightBtags > 0)  )
      {
         h_totHT_DT->Fill(totHT);
         h_SJ_mass_DT->Fill(superJet_mass[0]);
         //h_SJ_mass_DT->Fill(superJet_mass[1]);
         h_disuperjet_mass_DT->Fill(diSuperJet_mass);

      }

   }



  TCanvas *c1 = new TCanvas("c1","",400,20, 1500,1500);
   outFile.Write();

}


void readTreeMCBRSimplest()
{
   bool includeTTBar = false;
   std::string dataYear  = "2018";
   if(includeTTBar)
   {



      std::vector<std::string> inFileNames = {("/home/ethan/QCD_HT1000to1500_" + dataYear + ".root").c_str(),("/home/ethan/QCD_HT1500to2000_" + dataYear + ".root").c_str(), ("/home/ethan/QCD_HT2000toInf_" + dataYear + ".root").c_str()};

      std::vector<std::string> outFileNames = {("/home/ethan/Documents/QCD_HT1000to1500_combined_cutbased_processed_TEST_"+ dataYear + "_SIMPLEST.root").c_str(),("/home/ethan/Documents/QCD_HT1500to2000_combined_cutbased_processed_TEST_"+ dataYear + "_SIMPLEST.root").c_str(),("/home/ethan/Documents/QCD_HT2000toInf_combined_cutbased_processed_TEST_"+ dataYear + "_SIMPLEST.root").c_str()};


      for(unsigned int iii = 0; iii<inFileNames.size(); iii++)
      {
         doThings(inFileNames[iii],outFileNames[iii], dataYear);
      }

      std::cout << "Finished with "<< inFileNames.size() << " files." << std::endl;
   }
   else
   {

      std::vector<std::string> inFileNames = {("/home/ethan/QCD_HT1000to1500_" + dataYear + ".root").c_str(),("/home/ethan/QCD_HT1500to2000_" + dataYear + ".root").c_str(), ("/home/ethan/QCD_HT2000toInf_" + dataYear + ".root").c_str()};

      std::vector<std::string> outFileNames = {("/home/ethan/Documents/QCD_HT1000to1500_combined_cutbased_processed_TEST_"+ dataYear + "_SIMPLEST.root").c_str(),("/home/ethan/Documents/QCD_HT1500to2000_combined_cutbased_processed_TEST_"+ dataYear + "_SIMPLEST.root").c_str(),("/home/ethan/Documents/QCD_HT2000toInf_combined_cutbased_processed_TEST_"+ dataYear + "_SIMPLEST.root").c_str()};
      //std::vector<std::string> inFileNames = {"/home/ethan/QCD_HT2000toInf.root"};

      //std::vector<std::string> outFileNames = {"/home/ethan/Documents/QCD_HT2000toInf_combined_cutbased_processed_TEST.root"};

      for(unsigned int iii = 0; iii<inFileNames.size(); iii++)
      {
         doThings(inFileNames[iii],outFileNames[iii],dataYear);
      }
      std::cout << "Finished with "<< inFileNames.size() << " files." << std::endl;
   }



}




// increasing the AK4 pT for tight jets - makes the totHT comparisons look worse - why is this unstable?
   // other plots look fine ...

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

   TH1F* h_totHT  = new TH1F("h_totHT","Total Event HT;H_{T} [GeV]; Events / 200 GeV",50,0.,5000);

   TH1F* h_totHT_DT  = new TH1F("h_totHT_DT","Event H_{T} (DT region);H_{T} [GeV]; Events / 200 GeV",50,0.,5000);
   TH1F* h_totHT_CR  = new TH1F("h_totHT_CR","Event H_{T} (CR region);H_{T} [GeV]; Events / 200 GeV",50,0.,5000);

   TH1F* h_deepFlavour_score  = new TH1F("h_deepFlavour_score","DeepFlavour score for AK4 jets; bdisc score",24,0.,1.2);

   TH1I* h_nLooseBtags  = new TH1I("h_nLooseBtags","number of loose b tags (DeepFlavour);",10,-0.5,9.5);

   TH1F* h_SJ_mass_DT  = new TH1F("h_SJ_mass_DT","SuperJet Mass (Signal Region) ;Mass [GeV] ; Events / 125 GeV",40,0.,5000);
   TH1F* h_SJ_mass_CR  = new TH1F("h_SJ_mass_CR","SuperJet Mass (Control Region) ;Mass [GeV]; Events / 125 GeV",40,0.,5000);

   TH1F* h_disuperjet_mass_DT  = new TH1F("h_disuperjet_mass_DT","diSuperJet Mass (Signal Region) ;Mass [GeV]; Events / 400 GeV",25,0.,5000);
   TH1F* h_disuperjet_mass_CR  = new TH1F("h_disuperjet_mass_CR","diSuperJet Mass (Control Region);Mass[ GeV]; Events / 400 GeV",25,0.,5000);


   auto prof_avg_DeepJetDisc_vs_pT  = new TProfile("prof_avg_DeepJetDisc_vs_pT","Average AK4 DeepFlavour Score vs AK4 p_{T}",25,0.,5000.,0.,1.2);

   auto prof_taggingEfficiency_vs_pT  = new TProfile("prof_taggingEfficiency_vs_pT","true b jet tagging efficiency vs AK4 p_{T}",25,0.,5000.,0.,1.1);

   auto prof_nonb_mistaggingRate_vs_pT  = new TProfile("prof_nonb_mistaggingRate_vs_pT","b-tagging mistagging rate for non b jets vs AK4 p_{T};AK4 p_{T};b mistagging rate",25,0.,5000.,0.,1.1);

   auto prof_charm_mistaggingRate_vs_pT  = new TProfile("prof_charm_mistaggingRate_vs_pT","b-tagging mistagging rate for charm jets vs AK4 p_{T};AK4 p_{T};b mistagging rate",25,0.,5000.,0.,1.1);
   auto prof_udsg_mistaggingRate_vs_pT  = new TProfile("prof_udsg_mistaggingRate_vs_pT","b-tagging mistagging rate for udsg jets vs AK4 p_{T};AK4 p_{T};b mistagging rate",25,0.,5000.,0.,1.1);

   auto prof_nAK4_vs_pT  = new TProfile("prof_nAK4_vs_pT","number of AK4 jets per Event vs HT",25,0.,5000.,0.,20.);

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


   // depending on the year, change the WPs 

   double looseDeepCSV_DeepJet;
   double medDeepCSV_DeepJet;
   double tightDeepCSV_DeepJet;

   double looseDeepCSV = 0.1241;
   double medDeepCSV   = 0.4184;
   double tightDeepCSV = 0.7527;

   if(dataYear == "2016")   //preVFP
   {
      looseDeepCSV_DeepJet = 0.0508;
      medDeepCSV_DeepJet   = 0.2598;
      tightDeepCSV_DeepJet = 0.6502;
   }
   else if(dataYear == "2017")
   {
      looseDeepCSV_DeepJet = 0.0532;
      medDeepCSV_DeepJet   = 0.3040;
      tightDeepCSV_DeepJet = 0.7476;
   }
   else if(dataYear == "2018")
   {
      looseDeepCSV_DeepJet = 0.0490;
      medDeepCSV_DeepJet   = 0.2783;
      tightDeepCSV_DeepJet = 0.7100;
   }
   int nGenBtags[50] = {0},nRECOBtags[50] = {0};

   for (Int_t i=0;i<nentries;i++) 
   {  
      t1->GetEntry(i);

      
      int HT_index = floor(totHT - 1200)/176.;
      
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
      int nBTagsRECO = 0;
      int nBTagsGen  = 0;
      for(int iii = 0;iii< nAK4; iii++)
      {

         //if ( (AK4_bdisc[iii] > looseDeepCSV ) && (AK4_pt[iii] > 80.) ) nLooseBtags++;

         if ( ( AK4_DeepJet_disc[iii] > looseDeepCSV_DeepJet  ) && (AK4_pt[iii] > 30.))
         {
            nRECOBtags[HT_index]++; 
            nBTagsRECO++;
         }
         if ( (AK4_DeepJet_disc[iii] > looseDeepCSV_DeepJet ) && (AK4_pt[iii] > 30.) ) nLooseBtags++;
         if ( (AK4_DeepJet_disc[iii] > medDeepCSV_DeepJet )   && (AK4_pt[iii] > 80.) )   nMedBtags++;
         if ( (AK4_DeepJet_disc[iii] > tightDeepCSV_DeepJet ) && (AK4_pt[iii] > 80.) ) nTightBtags++;
         if( (abs(AK4_partonFlavour[iii])==5)  ) //&& (AK4_pt[iii] > 80.))
         {  
            nGenBtags[HT_index]++;
            //nLooseBtags++;
            nBTagsGen++;
            if(AK4_DeepJet_disc[iii] > looseDeepCSV_DeepJet) prof_taggingEfficiency_vs_pT->Fill(AK4_pt[iii],1.);
            else { prof_taggingEfficiency_vs_pT->Fill(AK4_pt[iii],0.); } 

         }
         
         else if( (abs(AK4_partonFlavour[iii])==4) )   // the MC truth says this AK4 jet is NOT a b jet, but rather a c jet - how often are they tagged as b jets?
         {
            if(AK4_DeepJet_disc[iii] > looseDeepCSV_DeepJet) prof_charm_mistaggingRate_vs_pT->Fill(AK4_pt[iii],1.);
            else { prof_charm_mistaggingRate_vs_pT->Fill(AK4_pt[iii],0.); } 
         }
   
   
         else   // the MC truth says this AK4 jet is NOT a b jet or c jet, but how often are they tagged as such?
         {
            if(AK4_DeepJet_disc[iii] > looseDeepCSV_DeepJet) prof_udsg_mistaggingRate_vs_pT->Fill(AK4_pt[iii],1.);
            else { prof_udsg_mistaggingRate_vs_pT->Fill(AK4_pt[iii],0.); } 
         }

         h_deepFlavour_score->Fill(AK4_DeepJet_disc[iii]);
         prof_avg_DeepJetDisc_vs_pT->Fill(AK4_pt[iii], AK4_DeepJet_disc[iii]);

      }

      //else (prof_nRECOBTag_nGenBTag_ratio->Fill(totHT,0.));

/*
      h_nLooseBtags->Fill(nLooseBtags);
      /// control region 
      if( nBTagsGen < 1 ) 
      {
         h_totHT_CR->Fill(totHT);
         h_SJ_mass_CR->Fill(superJet_mass[0]);
         h_SJ_mass_CR->Fill(superJet_mass[1]);
         h_disuperjet_mass_CR->Fill(diSuperJet_mass);
         prof_nGenBtags_vs_pT_CR->Fill(totHT,nBTagsGen);
         prof_nRECOBtags_vs_pT_CR->Fill(totHT,nBTagsRECO);

      }

      // signal region
      if ( (nBTagsGen > 1)  )
      {
         h_totHT_DT->Fill(totHT);
         h_SJ_mass_DT->Fill(superJet_mass[0]);
         h_SJ_mass_DT->Fill(superJet_mass[1]);
         h_disuperjet_mass_DT->Fill(diSuperJet_mass);
         prof_nGenBtags_vs_pT_DT->Fill(totHT,nBTagsGen);
         prof_nRECOBtags_vs_pT_DT->Fill(totHT,nBTagsRECO);

      }
      */

   }


   double eff[50], HT[50];
   for(int iii=0;iii<50;iii++)
   {
      HT[iii] = 176*iii+1200.;
      if(nGenBtags[iii]>0) eff[iii] = double(nRECOBtags[iii])/double(nGenBtags[iii]);
      else {eff[iii] = 0;}
   }
  TCanvas *c1 = new TCanvas("c1","",400,20, 1500,1500);


   prof_taggingEfficiency_vs_pT->SetTitle("b-tagging Efficiency vs HT;event HT;Eff");
   prof_taggingEfficiency_vs_pT->Draw();
   c1->SaveAs( ("prof_taggingEfficiency_vs_pT_" + dataYear+".png").c_str()  ); 

   prof_avg_DeepJetDisc_vs_pT->SetTitle("Average AK4 DeepJet Score vs Event HT;event HT;avg btag score");
   prof_avg_DeepJetDisc_vs_pT->Draw();
   c1->SaveAs( ("prof_avg_DeepJetDisc_vs_pT_" + dataYear+".png").c_str()  ); 

   prof_nonb_mistaggingRate_vs_pT->Draw();
   c1->SaveAs( ("prof_nonb_mistaggingRate_vs_pT_" + dataYear+".png").c_str()  ); 

   prof_charm_mistaggingRate_vs_pT->Draw();
   c1->SaveAs( ("prof_charm_mistaggingRate_vs_pT_" + dataYear+".png").c_str()  ); 

   prof_udsg_mistaggingRate_vs_pT->Draw();
   c1->SaveAs( ("prof_udsg_mistaggingRate_vs_pT_" + dataYear+".png").c_str()  ); 




   outFile.Write();

}


void readTreeMCBRpT()
{
   bool includeTTBar = false;
   std::string dataYear  = "2018";
   if(includeTTBar)
   {



      std::vector<std::string> inFileNames = {("/home/ethan/QCD_HT1000to1500_" + dataYear + ".root").c_str(),("/home/ethan/QCD_HT1500to2000_" + dataYear + ".root").c_str(), ("/home/ethan/QCD_HT2000toInf_" + dataYear + ".root").c_str()};

      std::vector<std::string> outFileNames = {("/home/ethan/Documents/QCD_HT1000to1500_combined_cutbased_processed_TEST_"+ dataYear + ".root").c_str(),("/home/ethan/Documents/QCD_HT1500to2000_combined_cutbased_processed_TEST_"+ dataYear + ".root").c_str(),("/home/ethan/Documents/QCD_HT2000toInf_combined_cutbased_processed_TEST_"+ dataYear + ".root").c_str()};


      for(unsigned int iii = 0; iii<inFileNames.size(); iii++)
      {
         doThings(inFileNames[iii],outFileNames[iii], dataYear);
      }

      std::cout << "Finished with "<< inFileNames.size() << " files." << std::endl;
   }
   else
   {

      std::vector<std::string> inFileNames = {("/home/ethan/QCD_HT2000toInf_" + dataYear + ".root").c_str()};

      std::vector<std::string> outFileNames = {("/home/ethan/Documents/QCD_HT2000toInf_combined_cutbased_processed_TEST_"+ dataYear + ".root").c_str()};
      //std::vector<std::string> inFileNames = {"/home/ethan/QCD_HT2000toInf.root"};

      //std::vector<std::string> outFileNames = {"/home/ethan/Documents/QCD_HT2000toInf_combined_cutbased_processed_TEST.root"};

      for(unsigned int iii = 0; iii<inFileNames.size(); iii++)
      {
         doThings(inFileNames[iii],outFileNames[iii],dataYear);
      }
      std::cout << "Finished with "<< inFileNames.size() << " files." << std::endl;
   }



}



// look at bdisc of non b jet (through gen info) in SR and CR (defined by RECO b tags)

//look at charm tagging
   //which of the non b jets that are tagged at b jet are charm? 
   //



//things you have to change back 
   // b tag working point
   // files run on (in this analyzer and in plotter)

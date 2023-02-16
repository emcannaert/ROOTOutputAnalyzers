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

   TH1F* h_deepFlavour_score  = new TH1F("h_deepFlavour_score","DeepFlavour score for AK4 jets; bdisc score",24,0.,1.2);
   TH1F* h_deepFlavour_score_highpt  = new TH1F("h_deepFlavour_score_highpt","DeepFlavour score for high pT (pT > 1 TeV) AK4 jets; bdisc score",24,0.,1.2);

   TH1I* h_nLooseBtags  = new TH1I("h_nLooseBtags","number of loose b tags (DeepFlavour);",10,-0.5,9.5);

   TH1F* h_SJ_mass_DT  = new TH1F("h_SJ_mass_DT","SuperJet Mass (Signal Region) ;Mass [GeV] ; Events / 125 GeV",40,0.,5000);
   TH1F* h_SJ_mass_CR  = new TH1F("h_SJ_mass_CR","SuperJet Mass (Control Region) ;Mass [GeV]; Events / 125 GeV",40,0.,5000);

   TH1F* h_disuperjet_mass_DT  = new TH1F("h_disuperjet_mass_DT","diSuperJet Mass (Signal Region) ;Mass [GeV]; Events / 400 GeV",25,0.,10000);
   TH1F* h_disuperjet_mass_CR  = new TH1F("h_disuperjet_mass_CR","diSuperJet Mass (Control Region);Mass[ GeV]; Events / 400 GeV",25,0.,10000);

   auto prof_nGenBtags_vs_HT  = new TProfile("prof_nGenBtags_vs_HT","nGenBTags per event vs HT",25,0.,10000.,0.,15.);
   auto prof_nRECOBtags_vs_HT  = new TProfile("prof_nRECOBtags_vs_HT","nRECOBtags per event vs HT",25,0.,10000.,0.,15.);


   auto prof_nGenBtags_vs_HT_CR  = new TProfile("prof_nGenBtags_vs_HT_CR","nGenBTags per event vs HT (CR)",25,0.,10000.,0.,15.);
   auto prof_nRECOBtags_vs_HT_CR  = new TProfile("prof_nRECOBtags_vs_HT_CR","nRECOBtags per event vs HT (CR)",25,0.,10000.,0.,15.);

   auto prof_nGenBtags_vs_HT_DT  = new TProfile("prof_nGenBtags_vs_HT_DT","nGenBTags per event vs HT (SR)",25,0.,10000.,0.,15.);
   auto prof_nRECOBtags_vs_HT_DT  = new TProfile("prof_nRECOBtags_vs_HT_DT","nRECOBtags per event vs HT (SR)",25,0.,10000.,0.,15.);


   auto prof_avg_DeepJetDisc_vs_HT  = new TProfile("prof_avg_DeepJetDisc_vs_HT","Average AK4 DeepFlavour Score vs HT",25,0.,10000.,0.,1.2);

   auto prof_nRECOBTag_nGenBTag_ratio  = new TProfile("prof_nRECOBTag_nGenBTag_ratio","ratio of nRECOBtags to nGenBtags per Event vs HT",25,0.,10000.,0.,15.);


   auto prof_taggingEfficiency_vs_HT  = new TProfile("prof_taggingEfficiency_vs_HT","ratio of nRECOBtags to nGenBtags per Event vs HT",25,0.,10000.,0.,1.1);

   auto prof_nonb_mistaggingRate_vs_HT  = new TProfile("prof_nonb_mistaggingRate_vs_HT","b-tagging mistagging rate for non b jets vs HT;event HT;b mistagging rate",25,0.,10000.,0.,1.1);

   auto prof_charm_mistaggingRate_vs_HT  = new TProfile("prof_charm_mistaggingRate_vs_HT","b-tagging mistagging rate for charm jets vs HT;event HT;b mistagging rate",25,0.,10000.,0.,1.1);
   auto prof_udsg_mistaggingRate_vs_HT  = new TProfile("prof_udsg_mistaggingRate_vs_HT","b-tagging mistagging rate for udsg jets vs HT;event HT;b mistagging rate",25,0.,10000.,0.,1.1);

   auto prof_nAK4_vs_HT  = new TProfile("prof_nAK4_vs_HT","number of AK4 jets per Event vs HT",25,0.,10000.,0.,20.);

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

      
      int HT_index = floor(totHT - 1200)/176.;
      
      if( (nfatjets < 3) || (totHT < 1500.)     ) continue;

      if ((nfatjet_pre < 2) && ( (dijetMassOne < 1000. ) || ( dijetMassTwo < 1000.)  ))
      {
         continue;
      } 
      h_totHT->Fill(totHT);


      prof_nAK4_vs_HT->Fill(totHT,double(nAK4));
      //btagging stuff 
      int nLooseBtags = 0;
      int nMedBtags   = 0;
      int nTightBtags = 0;
      int nBTagsRECO = 0;
      int nBTagsGen  = 0;
      for(int iii = 0;iii< nAK4; iii++)
      {

         //if ( (AK4_bdisc[iii] > looseDeepCSV ) && (AK4_pt[iii] > 80.) ) nLooseBtags++;

         if ( ( AK4_DeepJet_disc[iii] > looseDeepJet  ) && (AK4_pt[iii] > 30.))
         {
            nRECOBtags[HT_index]++; 
            nBTagsRECO++;
         }
         if ( (AK4_DeepJet_disc[iii] > looseDeepJet ) && (AK4_pt[iii] > 30.) ) nLooseBtags++;
         if ( (AK4_DeepJet_disc[iii] > medDeepJet )   && (AK4_pt[iii] > 30.) )   nMedBtags++;
         if ( (AK4_DeepJet_disc[iii] > tightDeepJet ) && (AK4_pt[iii] > 30.) ) nTightBtags++;
         if( (abs(AK4_partonFlavour[iii])==5)  ) //&& (AK4_pt[iii] > 80.))
         {  
            nGenBtags[HT_index]++;
            //nLooseBtags++;
            nBTagsGen++;
            if(AK4_DeepJet_disc[iii] > looseDeepJet) prof_taggingEfficiency_vs_HT->Fill(totHT,1.);
            else { prof_taggingEfficiency_vs_HT->Fill(totHT,0.); } 

         }
         
         else if( (abs(AK4_partonFlavour[iii])==4) )   // the MC truth says this AK4 jet is NOT a b jet, but rather a c jet - how often are they tagged as b jets?
         {
            if(AK4_DeepJet_disc[iii] > looseDeepJet) prof_charm_mistaggingRate_vs_HT->Fill(totHT,1.);
            else { prof_charm_mistaggingRate_vs_HT->Fill(totHT,0.); } 
         }
   
         else   // the MC truth says this AK4 jet is NOT a b jet or c jet, but how often are they tagged as such?
         {
            if(AK4_DeepJet_disc[iii] > looseDeepJet) prof_udsg_mistaggingRate_vs_HT->Fill(totHT,1.);
            else { prof_udsg_mistaggingRate_vs_HT->Fill(totHT,0.); } 
         }

         h_deepFlavour_score->Fill(AK4_DeepJet_disc[iii]);
         if(AK4_pt[iii] > 1000.)h_deepFlavour_score_highpt->Fill(AK4_DeepJet_disc[iii]);
         prof_avg_DeepJetDisc_vs_HT->Fill(totHT, AK4_DeepJet_disc[iii]);

      }
      prof_nGenBtags_vs_HT->Fill(totHT,nBTagsGen);
      prof_nRECOBtags_vs_HT->Fill(totHT,nBTagsRECO);

      if(nBTagsGen > 0) prof_nRECOBTag_nGenBTag_ratio->Fill(totHT,double(nBTagsRECO)/double(nBTagsGen) );
      //else (prof_nRECOBTag_nGenBTag_ratio->Fill(totHT,0.));

      h_nLooseBtags->Fill(nLooseBtags);
      /// control region 
      if( nBTagsGen < 1 ) 
      {
         h_totHT_CR->Fill(totHT);
         h_SJ_mass_CR->Fill(superJet_mass[0]);
         h_SJ_mass_CR->Fill(superJet_mass[1]);
         h_disuperjet_mass_CR->Fill(diSuperJet_mass);
         prof_nGenBtags_vs_HT_CR->Fill(totHT,nBTagsGen);
         prof_nRECOBtags_vs_HT_CR->Fill(totHT,nBTagsRECO);

      }

      // signal region
      if ( (nBTagsGen > 1)  )
      {
         h_totHT_DT->Fill(totHT);
         h_SJ_mass_DT->Fill(superJet_mass[0]);
         h_SJ_mass_DT->Fill(superJet_mass[1]);
         h_disuperjet_mass_DT->Fill(diSuperJet_mass);
         prof_nGenBtags_vs_HT_DT->Fill(totHT,nBTagsGen);
         prof_nRECOBtags_vs_HT_DT->Fill(totHT,nBTagsRECO);

      }

   }


   double eff[50], HT[50];
   for(int iii=0;iii<50;iii++)
   {
      HT[iii] = 176*iii+1200.;
      if(nGenBtags[iii]>0) eff[iii] = double(nRECOBtags[iii])/double(nGenBtags[iii]);
      else {eff[iii] = 0;}
   }
  TCanvas *c1 = new TCanvas("c1","",400,20, 1500,1500);

   auto g_bTagEff_vs_HT = new TGraph(50,HT,eff);
   g_bTagEff_vs_HT->SetTitle("bTagEff vs HT;HT;nGenBtags/nRECOBtags");
   g_bTagEff_vs_HT->Draw("AC*");
   c1->SaveAs( ("g_bTagEff_vs_HT_looseWP_" + dataYear+".png").c_str()  ); 

   double nGenBtags_double[50],nRECOBtags_double[50];
   for(int iii=0;iii<50;iii++)
   {
      nGenBtags_double[iii] = double(nGenBtags[iii]);
      nRECOBtags_double[iii] = double(nRECOBtags[iii]);
   }
   auto g_nGenBtags_vs_HT = new TGraph(50,HT,nGenBtags_double);
   g_nGenBtags_vs_HT->SetTitle("nGenBtags vs HT;HT;nGenBtags");
   g_nGenBtags_vs_HT->Draw("AC*");
   c1->SaveAs( ("g_nGenBtags_vs_HT_looseWP_" + dataYear+".png").c_str()  ); 


   auto g_nRECOBtags_vs_HT = new TGraph(50,HT,nRECOBtags_double);
   g_nRECOBtags_vs_HT->SetTitle("nRECOBtags vs HT;HT;nRECOBtags");
   g_nRECOBtags_vs_HT->Draw("AC*");
   c1->SaveAs( ("g_nRECOBtags_vs_HT_looseWP_" + dataYear+".png").c_str()  ); 

   prof_nGenBtags_vs_HT->Draw();
   c1->SaveAs( ("prof_nGenBtags_vs_HT_looseWP_" + dataYear+".png").c_str()  ); 

   prof_nRECOBtags_vs_HT->Draw();
   c1->SaveAs( ("prof_nRECOBtags_vs_HT_looseWP_" + dataYear+".png").c_str()  ); 


   prof_nGenBtags_vs_HT_CR->Draw();
   c1->SaveAs( ("prof_nGenBtags_vs_HT_CR_looseWP_" + dataYear+".png").c_str()  ); 

   prof_nRECOBtags_vs_HT_CR->Draw();
   c1->SaveAs( ("prof_nRECOBtags_vs_HT_CR_looseWP_" + dataYear+".png").c_str()  ); 

   prof_nGenBtags_vs_HT_DT->Draw();
   c1->SaveAs( ("prof_nGenBtags_vs_HT_DT_looseWP_" + dataYear+".png").c_str()  ); 

   prof_nRECOBtags_vs_HT_DT->Draw();
   c1->SaveAs( ("prof_nRECOBtags_vs_HT_DT_looseWP_" + dataYear+".png").c_str()  ); 

   prof_nRECOBTag_nGenBTag_ratio->Draw();
   c1->SaveAs( ("prof_nRECOBTag_nGenBTag_ratio_looseWP_" + dataYear+".png").c_str()  ); 


   prof_taggingEfficiency_vs_HT->SetTitle("b-tagging Efficiency vs HT;event HT;Eff");
   prof_taggingEfficiency_vs_HT->Draw();
   c1->SaveAs( ("prof_taggingEfficiency_vs_HT_looseWP_" + dataYear+".png").c_str()  ); 

   prof_avg_DeepJetDisc_vs_HT->SetTitle("Average AK4 DeepJet Score vs Event HT;event HT;avg btag score");
   prof_avg_DeepJetDisc_vs_HT->Draw();
   c1->SaveAs( ("prof_avg_DeepJetDisc_vs_HT_looseWP_" + dataYear+".png").c_str()  ); 

   prof_nonb_mistaggingRate_vs_HT->Draw();
   c1->SaveAs( ("prof_nonb_mistaggingRate_vs_HT_looseWP_" + dataYear+".png").c_str()  ); 

   prof_charm_mistaggingRate_vs_HT->Draw();
   c1->SaveAs( ("prof_charm_mistaggingRate_vs_HT_looseWP_" + dataYear+".png").c_str()  ); 

   prof_udsg_mistaggingRate_vs_HT->Draw();
   c1->SaveAs( ("prof_udsg_mistaggingRate_vs_HT_looseWP_" + dataYear+".png").c_str()  ); 




   prof_nAK4_vs_HT->SetTitle("Average nAK4 per Event vs Event HT;event HT;avg nAK4");
   prof_nAK4_vs_HT->Draw();
   c1->SaveAs( ("prof_nAK4_vs_HT_looseWP_" + dataYear+".png").c_str()  ); 


   gPad->SetLogy();
   h_deepFlavour_score->Draw();
   c1->SaveAs( ("h_deepFlavour_score_looseWP_" + dataYear+".png").c_str()  ); 

   h_deepFlavour_score_highpt->Draw();
   c1->SaveAs( ("h_deepFlavour_score_highpt_" + dataYear+".png").c_str()  ); 






   outFile.Write();

}


void readTreeMCBRSimple()
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

#include <iostream>
#include <string>
#include "TLorentzVector.h"

using namespace std;

void doThings(std::string inFileName, std::string outFileName, std::string dataYear)
{
   int eventnum = 0;int nhadevents = 0;int nfatjets = 0;int raw_nfatjets;int tot_nAK4_50,tot_nAK4_70;int SJ_nAK4_50[100],SJ_nAK4_70[100];
   double jet_pt[100], jet_eta[100], jet_mass[100], jet_dr[100], raw_jet_mass[100],raw_jet_pt[100],raw_jet_phi[100];
   double jet_beta[100], beta_T[100], AK4_mass_20[100],AK4_mass_30[100],AK4_mass_50[100],AK4_mass_70[100],AK4_mass_100[100],SJ_mass_150[100],SJ_mass_600[100],SJ_mass_800[100],SJ_mass_1000[100];
   double SJ_mass_50[100], SJ_mass_70[100],superJet_mass[100],SJ_AK4_50_mass[100],SJ_AK4_70_mass[100],genSuperJetMass[100];double tot_jet_mass,decay_inv_mass, chi_inv_mass;
   int nSuperJets,correctlySortedChi1,correctlySortedChi2;
   int jet_ndaughters[100], jet_nAK4[100],jet_nAK4_20[100],jet_nAK4_30[100],jet_nAK4_50[100],jet_nAK4_70[100],SJ_nAK4_150[100],jet_nAK4_150[100],SJ_nAK4_200[100],SJ_nAK4_400[100],SJ_nAK4_600[100],SJ_nAK4_800[100],SJ_nAK4_1000[100];
   int ntotalevents = 0;
   int nAK4;
   double AK4_mass[100];
   double SJ_mass_100[100],AK4_E[500];
   int SJ_nAK4_100[100];
   double totHT = 0;
   int nbtaggedAK4 =0;
   int SJ_nAK4_300[100];
   int nfatjet_pre;
   double SJ_mass_300[100];
   double posSJP, negSJP;
   double AK4_bdisc[100],AK4_DeepJet_disc[100];
   double AK4_pt[100];
   double totMET;
   double diSuperJet_mass, diSuperJet_mass_100;
   double SJ_E[2],SJ_Px[2],SJ_Py[2],SJ_Pz[2];
   double dijetMassOne, dijetMassTwo;
   //have to multiply these by scale factors  
   double resonance_mass_comb;
   double daughter_mass_comb[100];
   int nGenBJets_AK4[100], AK4_partonFlavour[100],AK4_HadronFlavour[100];
   int SJ1_decision, SJ2_decision;


   ////////////////////////////   btag SF variables //////////////////////
   int _eventNumBTag,_eventNumPU, _nAK4;
   double _eventWeightBTag, _AK4_pt[100];

   const char *_inFilename = inFileName.c_str();
   const char *_outFilename = outFileName.c_str();
   std::cout << "Reading file: " << _inFilename << std::endl;
   std::cout << "Will write out file: " << _outFilename << std::endl;

   TFile *f = new TFile(_inFilename);

   TFile outFile(_outFilename,"RECREATE");

   TH1F* h_totHT  = new TH1F("h_totHT","Total Event HT;H_{T} [GeV]; Events / 200 GeV",50,0.,10000);
   TH1F* h_lead_SJ_mass  = new TH1F("h_lead_SJ_mass","SuperJet Mass;Mass [GeV]; Events / 100 GeV",40,0.,4000);
   TH1F* h_disuperjet_mass  = new TH1F("h_disuperjet_mass","diSuperJet Mass;Mass [GeV]; Events / 200 GeV",50,0.,10000);

   TTree *t1 = (TTree*)f->Get("clusteringAnalyzerAll/tree");   //need to change this to something relevenet

   const Int_t nentries = t1->GetEntries();

////////////////////////////////////////////////////////////////////////////////////////////////////////
   t1->SetBranchAddress("nfatjets", &nfatjets);   
   t1->SetBranchAddress("nSuperJets", &nSuperJets);   
   t1->SetBranchAddress("tot_nAK4_50", &tot_nAK4_50);               //total #AK4 jets (E>50 GeV) for BOTH superjets
   t1->SetBranchAddress("tot_nAK4_70", &tot_nAK4_70);   
   t1->SetBranchAddress("diSuperJet_mass", &diSuperJet_mass);   
   t1->SetBranchAddress("diSuperJet_mass_100", &diSuperJet_mass_100); 
   t1->SetBranchAddress("nfatjet_pre", &nfatjet_pre); 
   t1->SetBranchAddress("jet_pt", jet_pt);   
   t1->SetBranchAddress("jet_eta", jet_eta);   
   t1->SetBranchAddress("jet_mass", jet_mass);   
   t1->SetBranchAddress("SJ_nAK4_50", SJ_nAK4_50);   
   t1->SetBranchAddress("SJ_nAK4_70", SJ_nAK4_70);   
   t1->SetBranchAddress("SJ_mass_50", SJ_mass_50);   
   t1->SetBranchAddress("SJ_mass_70", SJ_mass_70); 
   t1->SetBranchAddress("SJ_mass_150", SJ_mass_150);
   t1->SetBranchAddress("nbtaggedAK4", &nbtaggedAK4);
   t1->SetBranchAddress("totHT", &totHT);
   t1->SetBranchAddress("SJ_nAK4_300", SJ_nAK4_300);
   t1->SetBranchAddress("SJ_mass_300", SJ_mass_300);
   t1->SetBranchAddress("SJ_mass_50", SJ_mass_50);
   t1->SetBranchAddress("SJ_mass_600", SJ_mass_600);
   t1->SetBranchAddress("SJ_mass_800", SJ_mass_800);
   t1->SetBranchAddress("SJ_mass_1000", SJ_mass_1000);
   t1->SetBranchAddress("superJet_mass", superJet_mass);   
   t1->SetBranchAddress("SJ_AK4_50_mass", SJ_AK4_50_mass);   //mass of individual reclustered AK4 jets
   t1->SetBranchAddress("SJ_AK4_70_mass", SJ_AK4_70_mass); 
   t1->SetBranchAddress("SJ_nAK4_150", SJ_nAK4_150);   
   t1->SetBranchAddress("SJ_nAK4_200", SJ_nAK4_200);  
   t1->SetBranchAddress("SJ_nAK4_300", SJ_nAK4_300);     
   t1->SetBranchAddress("SJ_nAK4_400", SJ_nAK4_400);   
   t1->SetBranchAddress("SJ_nAK4_600", SJ_nAK4_600);   
   t1->SetBranchAddress("SJ_nAK4_800", SJ_nAK4_800);   
   t1->SetBranchAddress("SJ_nAK4_1000", SJ_nAK4_1000);   
   t1->SetBranchAddress("nAK4" , &nAK4); 
   t1->SetBranchAddress("SJ_mass_100", SJ_mass_100);   
   t1->SetBranchAddress("SJ_nAK4_100", SJ_nAK4_100);   
   t1->SetBranchAddress("AK4_E", AK4_E);  
   t1->SetBranchAddress("daughter_mass_comb", daughter_mass_comb);   
   t1->SetBranchAddress("resonance_mass_comb", &resonance_mass_comb);  
   t1->SetBranchAddress("totMET", &totMET); 
   t1->SetBranchAddress("posSJP", &posSJP); 
   t1->SetBranchAddress("negSJP", &negSJP); 
   t1->SetBranchAddress("AK4_bdisc", AK4_bdisc); 

   t1->SetBranchAddress("AK4_mass", AK4_mass); 

   t1->SetBranchAddress("SJ1_decision", &SJ1_decision); 
   t1->SetBranchAddress("SJ2_decision", &SJ2_decision); 

   t1->SetBranchAddress("lab_AK4_pt", AK4_pt); 

   t1->SetBranchAddress("dijetMassOne", &dijetMassOne); 
   t1->SetBranchAddress("dijetMassTwo", &dijetMassTwo); 

   t1->SetBranchAddress("SJ_E", SJ_E); 
   t1->SetBranchAddress("SJ_Px", SJ_Px); 
   t1->SetBranchAddress("SJ_Py", SJ_Py); 
   t1->SetBranchAddress("SJ_Pz", SJ_Pz); 
   t1->SetBranchAddress("nGenBJets_AK4", nGenBJets_AK4); 

   t1->SetBranchAddress("AK4_partonFlavour", AK4_partonFlavour); 
   t1->SetBranchAddress("AK4_hadronFlavour", AK4_HadronFlavour); 
   t1->SetBranchAddress("AK4_DeepJet_disc", AK4_DeepJet_disc); 

   double looseDeepCSV_DeepJet = 0.0490;
   double medDeepCSV_DeepJet   = 0.2783;
   double tightDeepCSV_DeepJet = 0.7100;

   int totalEvents = 0;
   int passedHTandNFatjets = 0;
   int passesHeavyJets = 0;
   int passesBTag = 0;
   for (Int_t i=0;i<nentries;i++) 
   {  
      t1->GetEntry(i);
      totalEvents++;
      if( (nfatjets < 3) || (totHT < 1500.)     ) continue;
      passedHTandNFatjets++;
      if ((nfatjet_pre < 2) && ( (dijetMassOne < 1000. ) || ( dijetMassTwo < 1000.)  ))
      {
         continue;
      } 
      passesHeavyJets++;
      int nTightBTags = 0, nMedBTags = 0, nLooseBtags =0;

      for(int iii = 0;iii< nAK4; iii++)
      {
         if ( (AK4_DeepJet_disc[iii] > tightDeepCSV_DeepJet ) && (AK4_pt[iii] > 30.)) nTightBTags++;
      }
      if(nTightBTags > 0)
      {
         passesBTag++;
         h_totHT->Fill(totHT);
      }
   }

   outFile.Write();


   TCanvas *c1 = new TCanvas("c1","",400,20, 1500,1500);
   std::cout << "total:passesHT&nfatjets:passesHeavyJets:passesBTag " <<totalEvents << ":" <<passedHTandNFatjets << ":" << passesHeavyJets<< ":" << passesBTag << std::endl;
   h_totHT->Draw("HIST");
   c1->SaveAs("h_totHT.png");  

}

void readTreeMCBRSimplestest()
{
   std::string dataYear = "2018";


      std::vector<std::string> inFileNames = {("/home/ethan/pt15-7000-flat_combined_"+ dataYear + ".root").c_str()};

      std::vector<std::string> outFileNames = {("/home/ethan/Documents/pt15-7000-flat_combined_processed"+ dataYear + ".root").c_str()};
      for(unsigned int iii = 0; iii<inFileNames.size(); iii++)
      {
         doThings(inFileNames[iii],outFileNames[iii],dataYear );
      }

      std::cout << "Finished with "<< inFileNames.size() << " files." << std::endl;


}


//look at nBtag plots ... 
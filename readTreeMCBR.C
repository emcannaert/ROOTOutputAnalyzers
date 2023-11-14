#include <iostream>
#include <string>
#include "TLorentzVector.h"

//notes of things to do next week
// check out the mass combinations for TTbar - are these really not between 150 and 200 Gev? 
// check out the SJ mass ratio, this might be really weird for TTbar and could be used to kill some of this


using namespace std;
void doThings(std::string inFileName, std::string outFileName, double& nEvents, double& nHTcut, double& nAK8JetCut,double& nHeavyAK8Cut, double& nBtagCut, double& nDoubleTagged,double& nNoBjets, double& nDoubleTaggedCR, double& NNDoubleTag, double& nDoubleTaggedCRNN,double eventScaleFactor, std::string dataYear,std::string systematic)
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
   int SJ_nAK4_300[100];
   int nfatjet_pre;
   double SJ_mass_300[100];
   double AK4_bdisc[100],AK4_DeepJet_disc[100];
   double AK4_pt[100];
   double totMET;
   double diSuperJet_mass, diSuperJet_mass_100;
   double dijetMassOne, dijetMassTwo;
   //have to multiply these by scale factors  
   double daughter_mass_comb[100];
   int nGenBJets_AK4[100], AK4_partonFlavour[100],AK4_HadronFlavour[100];
   int SJ1_decision, SJ2_decision;

   double _eventWeightPU,_puWeightDown,_puWeightUp;
   int eventTTbarCRFlag =0;
   
   int nEventsTTbarCR = 0;   
   ////////////////////////////   btag SF variables //////////////////////
   int _eventNumBTag,_eventNumPU, _nAK4;
   double _eventWeightBTag, _AK4_pt[100];

   double diAK8Jet_mass [100];
   double fourAK8JetMass;

std::vector<std::string> systematic_suffices;

   if(systematic == "nom")
   {
      // want to run only once with the 
      systematic_suffices = {""};

   }
   else
   {
      systematic_suffices = {"up","down"};
   }


   const char *_inFilename = inFileName.c_str();
   const char *_outFilename = outFileName.c_str();

   std::cout << "Reading file: " << _inFilename << std::endl;
   TFile *f = new TFile(_inFilename);

   TFile outFile(_outFilename,"RECREATE");

   for(auto systematic_suffix = systematic_suffices.begin(); systematic_suffix < systematic_suffices.end();systematic_suffix++)
   {

      outFile.cd();   // return to outer directory
      gDirectory->mkdir( (systematic+"_"+ *systematic_suffix).c_str()  );   //create directory for this systematic
      outFile.cd( (systematic+"_"+*systematic_suffix).c_str() );   // go inside the systematic directory 


       // need to tunnel into the directory of the infile   JEC_up, nom_ /   skimmedTree_nom / skimmedTree_JER_up

      std::string tree_name;
      std::string folder_name;
      if(systematic == "nom")
      {
         tree_name = systematic;
         folder_name = systematic + "_";
      }
      else
      {
         tree_name = systematic+"_"+*systematic_suffix;
         folder_name = tree_name;
      }

      std::cout << "Looking for tree " << (folder_name+ "/skimmedTree_"+ tree_name ).c_str() << std::endl;

      TTree *t1 = (TTree*)f->Get(   (folder_name+ "/skimmedTree_"+ tree_name ).c_str()    );
      const Int_t nentries = t1->GetEntries();



      TH2F *h_Mjet_vs_pTjet = new TH2F("h_Mjet_vs_pTjet","Jet Mass vs Jet pT; jet p_{T} [GeV];jet mass", 80,0, 4000, 50, 0, 2000);
      
      TH1F* h_numAntiTagged = new TH1F("h_numAntiTagged","number of anti-tagged events per (near side) mass ;Mass [GeV]; Events / 100 GeV",40,0.,4000);
      TH1F* h_numMistagged  = new TH1F("h_numMistagged","number of mistagged second superjets per (near side) mass bin ;Mass [GeV]; Events / 100 GeV",40,0.,4000);
      TH1F* h_totHT  = new TH1F("h_totHT","Total Event HT;H_{T} [GeV]; Events / 200 GeV",50,0.,10000);
      TH1F* h_lead_SJ_mass  = new TH1F("h_lead_SJ_mass","SuperJet Mass;Mass [GeV]; Events / 100 GeV",40,0.,4000);
      TH1F* h_lead_SJ_mass_100  = new TH1F("h_lead_SJ_mass_100","SuperJet Mass (E_{AK4} > 100 GeV);Mass [GeV]; Events / 100 GeV",40,0.,4000);
      TH1F* h_disuperjet_mass  = new TH1F("h_disuperjet_mass","diSuperJet Mass;Mass [GeV]; Events / 200 GeV",50,0.,10000);
      TH1F* h_disuperjet_mass_100  = new TH1F("h_disuperjet_mass_100","diSuperJet Mass (E_{AK4} > 100 GeV);Mass [GeV]; Events / 200 GeV",50,0.,10000);

      TH1I* h_SJ_nAK4_100  = new TH1I("h_SJ_nAK4_100","Number of Reclustered AK4 Jets (E_{COM} > 100 GeV) per SJ ;nAK4 Jets (E_{COM} > 100 GeV); Events",10,-0.5,9.5);
      TH1I* h_SJ_nAK4_200  = new TH1I("h_SJ_nAK4_200","Number of Reclustered AK4 Jets (E_{COM} > 200 GeV) per SJ ;nAK4 Jets (E_{COM} > 200 GeV); Events",10,-0.5,9.5);
      TH1I* h_SJ_nAK4_300  = new TH1I("h_SJ_nAK4_300","Number of Reclustered AK4 Jets (E_{COM} > 300 GeV) per SJ ;nAK4 Jets (E_{COM} > 300 GeV); Events",10,-0.5,9.5);
      TH1I* h_SJ_nAK4_400  = new TH1I("h_SJ_nAK4_400","Number of Reclustered AK4 Jets (E_{COM} > 400 GeV) per SJ ;nAK4 Jets (E_{COM} > 400 GeV); Events",10,-0.5,9.5);
      TH1I* h_nfatjets_pre  = new TH1I("h_nfatjets_pre","Number of AK8 Jets (p_{T} > 500 GeV, M_{PUPPI} > 45 GeV) per Event ;nAK8 Jets; Events",10,-0.5,9.5);
      TH1F* h_avg_dijet_mass  = new TH1F("h_avg_dijet_mass","Average dijet mass (AK4 jets);Mass [GeV]; Events / 100 GeV",50,0.,5000);

      TH1F* h_diSJ_SJ_mass_ratio  = new TH1F("h_diSJ_SJ_mass_ratio","M_{diSJ} / (M_{SJ1} + M_{SJ2})",50,0.,10);
      TH2F *h_MSJ_mass_vs_MdSJ = new TH2F("h_MSJ_mass_vs_MdSJ","Tagged Superjet mass vs diSuperjet mass; diSuperjet mass [GeV];superjet mass", 25,0, 10000, 20, 0, 6000);
      TH2F *h_MSJ_mass_vs_MdSJ_doubleTag = new TH2F("h_MSJ_mass_vs_MdSJ_doubleTag","Avg (double) tagged Superjet mass vs diSuperjet mass; diSuperjet mass [GeV];superjet mass", 25,0, 10000, 20, 0, 6000);

      TH1F* h_MSJ1_MSJ2_ratio  = new TH1F("h_MSJ1_MSJ2_ratio","(M_{SJ_{1}} - M_{SJ_{2}})/(M_{SJ_{1}} + M_{SJ_{2}});",30,-3.,3.0);
      TH1F* h_MdiSJ_SJ12_ratios  = new TH1F("h_MdiSJ_SJ12_ratios","M_{diSJ} / (M_{SJ_{1}} + M_{SJ_{2}})",25,0.,5.0);

      // QCD control region stuff 
      TH1I* h_SJ_nAK4_100_CR  = new TH1I("h_SJ_nAK4_100_CR","Number of Reclustered AK4 Jets (E_{COM} > 100 GeV) per SJ (Control Region);nAK4 Jets (E_{COM} > 100 GeV); Events",10,-0.5,9.5);
      TH1I* h_SJ_nAK4_200_CR  = new TH1I("h_SJ_nAK4_200_CR","Number of Reclustered AK4 Jets (E_{COM} > 200 GeV) per SJ (Control Region);nAK4 Jets (E_{COM} > 200 GeV); Events",10,-0.5,9.5);
      TH1F* h_SJ_mass_CR  = new TH1F("h_SJ_mass_CR","SuperJet Mass (Control Region) ;Mass [GeV]; Events / 125 GeV",40,0.,5000);
      TH1F* h_disuperjet_mass_CR  = new TH1F("h_disuperjet_mass_CR","diSuperJet Mass (Control Region);Mass [GeV]; Events / 400 GeV",25,0.,10000);
      TH2F *h_MSJ_mass_vs_MdSJ_CR = new TH2F("h_MSJ_mass_vs_MdSJ_CR","Double Tagged Superjet mass vs diSuperjet mass (Control Region); diSuperjet mass [GeV];superjet mass", 22,1250., 9500, 20, 500, 3500);  /// 375 * 125

      // TTbar control region
      TH2F *h_MSJ_mass_vs_MdSJ_CRTTbar = new TH2F("h_MSJ_mass_vs_MdSJ_CRTTbar","Double Tagged Superjet mass vs diSuperjet mass (TTbar Control Region); diSuperjet mass [GeV];superjet mass", 22,1250., 9500, 20, 500, 3500);  /// 375 * 125


      // Signal regions stuff
      TH1I* h_SJ_nAK4_100_SR  = new TH1I("h_SJ_nAK4_100_SR","Number of Reclustered AK4 Jets (E_{COM} > 100 GeV) per SJ (Signal Region);nAK4 Jets (E_{COM} > 100 GeV); Events",10,-0.5,9.5);
      TH1I* h_SJ_nAK4_200_SR = new TH1I("h_SJ_nAK4_200_SR","Number of Reclustered AK4 Jets (E_{COM} > 200 GeV) per SJ (Signal Region);nAK4 Jets (E_{COM} > 200 GeV); Events",10,-0.5,9.5);
      TH1F* h_SJ_mass_SR  = new TH1F("h_SJ_mass_SR","SuperJet Mass (Signal Region) ;Mass [GeV]; Events / 100 GeV",40,0.,5000);
      TH1F* h_disuperjet_mass_SR  = new TH1F("h_disuperjet_mass_SR","diSuperJet Mass (Signal Region);Mass [GeV]; Events / / 400 GeV",25,0.,10000);
      TH2F *h_MSJ_mass_vs_MdSJ_SR = new TH2F("h_MSJ_mass_vs_MdSJ_SR","Double Tagged Superjet mass vs diSuperjet mass (Signal Region); diSuperjet mass [GeV];superjet mass", 22,1250., 9500, 20, 500, 3500);  /// 375 * 125

      TH2F *h_MSJ_mass_vs_MdSJ_dijet = new TH2F("h_MSJ_mass_vs_MdSJ_dijet","Double Tagged Superjet mass vs diSuperjet mass (dijet technique); 4-jet mass [GeV];avg dijet mass", 22,1250., 9500, 20, 500, 3500);  /// 375 * 125


      TH1I* h_nLooseBTags = new TH1I("h_nLooseBTags","Number of Loosely b-tagged AK4 Jets; Events",10,-0.5,9.5);
      TH1I* h_nMidBTags = new TH1I("h_nMidBTags","Number of Mediumly b-tagged AK4 Jets; Events",10,-0.5,9.5);
      TH1I* h_nTightBTags = new TH1I("h_nTightBTags","Number of Tightly b-tagged AK4 Jets; Events",10,-0.5,9.5);



      /////////////more for verifying the CR //////////////////////////////////////
      TH1F* h_AK8_jet_mass_SR  = new TH1F("h_AK8_jet_mass_SR","AK8 Jet Mass (SR region);Mass [GeV]; Events / 30 5GeV",50,0.,1500);
      TH1F* h_AK8_jet_mass_CR  = new TH1F("h_AK8_jet_mass_CR","AK8 Jet Mass (CR);Mass [GeV]; Events / 30 GeV",50,0.,1500);

      TH1F* h_AK4_jet_mass_SR  = new TH1F("h_AK4_jet_mass_SR","AK4 Jet Mass (SR region);Mass [GeV]; Events / 25 GeV",40,0.,1000);
      TH1F* h_AK4_jet_mass_CR  = new TH1F("h_AK4_jet_mass_CR","AK4 Jet Mass (CR);Mass [GeV]; Events / 25 GeV",40,0.,1000);

      TH1F* h_totHT_SR  = new TH1F("h_totHT_SR","Event H_{T} (DT region);H_{T} [GeV]; Events / 200 5GeV",50,0.,10000);
      TH1F* h_totHT_CR  = new TH1F("h_totHT_CR","Event H_{T} (CR);H_{T} [GeV]; Events / 200 GeV",50,0.,10000);

      TH1I* h_nfatjets_SR = new TH1I("h_nfatjets_SR","Number of AK8 Jets (E_{T} > 300 GeV per Event ;nAK8 Jets; Events",10,-0.5,9.5);
      TH1I* h_nfatjets_CR = new TH1I("h_nfatjets_CR","Number of AK8 Jets (E_{T} > 300 GeV per Event ;nAK8 Jets; Events",10,-0.5,9.5);

      TH1I* h_nAK4_SR = new TH1I("h_nAK4_SR","Number of AK4 Jets (E_{T} > 30 GeV per Event ;nAK8 Jets; Events",30,-0.5,29.5);
      TH1I* h_nAK4_CR = new TH1I("h_nAK4_CR","Number of AK4 Jets (E_{T} > 30 GeV per Event ;nAK8 Jets; Events",30,-0.5,29.5);


      TH1I* h_AK4_partonFlavour = new TH1I("h_AK4_partonFlavour","AK4 parton Flavour ;parton flavour ; Events",59,-29.5,29.5);

      TH1F* h_GenBtagged_HT = new TH1F("h_GenBtagged_HT","Event HT of AK4 jets tagged by genParts;H_{T}; Events/300 GeV",25,0.0,7500.0);
      TH1F* h_RECOBtagged_HT = new TH1F("h_RECOBtagged_HT","Event HT of AK4 jets tagged post RECO;H_{T}; Events/300 GeV",25,0.0,7500.0);

      TH1F* h_GenBtagged_pT = new TH1F("h_GenBtagged_pT","p_{T} of AK4 jets tagged by genParts;p_{T}; Events/100 GeV",25,0.0,2500.0);
      TH1F* h_RECOBtagged_pT = new TH1F("h_RECOBtagged_pT","p_{T} of AK4 jets tagged post RECO;p_{T}; Events/100 GeV",25,0.0,2500.0);

      TH1F* h_totHT_All  = new TH1F("h_totHT_All","Event H_{T} (All Events from EDAnalyzer);H_{T} [GeV]; Events / 200 GeV",50,0.,10000);
      TH1F* h_totHT_All1  = new TH1F("h_totHT_All1","Event H_{T} (All Events from EDAnalyzer 1);H_{T} [GeV]; Events / 200 GeV",50,0.,10000);
      TH1F* h_totHT_All2  = new TH1F("h_totHT_All2","Event H_{T} (All Events from EDAnalyzer 2 );H_{T} [GeV]; Events / 200 GeV",50,0.,10000);
      TH1F* h_totHT_All3  = new TH1F("h_totHT_All3","Event H_{T} (All Events from EDAnalyzer 3);H_{T} [GeV]; Events / 200 GeV",50,0.,10000);

      TH1F* h_AK4_DeepJet_disc  = new TH1F("h_AK4_DeepJet_disc","AK4 DeepFlavour bdisc scores;bdisc",25,0.,1.25);
      TH1F* h_AK4_DeepJet_disc_all  = new TH1F("h_AK4_DeepJet_disc_all","AK4 DeepFlavour bdisc scores;bdisc",25,0.,1.25);

      TH1I* h_nAK4 = new TH1I("h_nAK4","Number of AK4 jets;# AK4 jets; Events",20,-0.5,19.5);

      TH2F *h_MSJ_mass_vs_MdSJ_SR_NN = new TH2F("h_MSJ_mass_vs_MdSJ_SR_NN","Double Tagged Superjet mass vs diSuperjet mass (Signal Region, NN tagging); diSuperjet mass [GeV];superjet mass", 25,0, 10000, 20, 0, 6000);

     TH2F* h_MSJ1_vs_MSJ2_SR = new TH2F("h_MSJ1_vs_MSJ2_SR","M_{superjet 2} vs M_{superjet 1} in the Signal Region; M_{superjet 1} Events / 70 GeV;M_{superjet 2} Events / 70 GeV",50,0, 3500, 50, 0, 3500);

     TH2F* h_MSJ1_vs_MSJ2_CR = new TH2F("h_MSJ1_vs_MSJ2_CR","M_{superjet 2} vs M_{superjet 1} in the Control Region; M_{superjet 1} Events / 70 GeV;M_{superjet 2} Events / 70 GeV",50,0, 3500, 50, 0, 3500);


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
      t1->SetBranchAddress("totMET", &totMET); 
      t1->SetBranchAddress("AK4_bdisc", AK4_bdisc); 

      t1->SetBranchAddress("AK4_mass", AK4_mass); 

      t1->SetBranchAddress("SJ1_decision", &SJ1_decision); 
      t1->SetBranchAddress("SJ2_decision", &SJ2_decision); 

      t1->SetBranchAddress("lab_AK4_pt", AK4_pt); 

      t1->SetBranchAddress("dijetMassOne", &dijetMassOne); 
      t1->SetBranchAddress("dijetMassTwo", &dijetMassTwo); 

      t1->SetBranchAddress("nGenBJets_AK4", nGenBJets_AK4); 

      t1->SetBranchAddress("AK4_partonFlavour", AK4_partonFlavour); 
      t1->SetBranchAddress("AK4_hadronFlavour", AK4_HadronFlavour); 
      t1->SetBranchAddress("AK4_DeepJet_disc", AK4_DeepJet_disc); 

      t1->SetBranchAddress("eventTTbarCRFlag", &eventTTbarCRFlag); 

      t1->SetBranchAddress("fourAK8JetMass", &fourAK8JetMass); 
      t1->SetBranchAddress("diAK8Jet_mass", &diAK8Jet_mass); 

      int totalEvents = 0;
      int nPreselected = 0;
      int totWithNoHeavyAK8 = 0;
      int totWithNoLessHeavyAK8 = 0;
      int nPassPreSelection = 0;
      int nControlRegion = 0;
      double looseDeepCSV = 0.1241;
      double medDeepCSV   = 0.4184;
      double tightDeepCSV = 0.7527;
      int passHTandAK8 = 0;

      double looseDeepCSV_DeepJet;
      double medDeepCSV_DeepJet;
      double tightDeepCSV_DeepJet;

      if(dataYear == "2015")
      {
         looseDeepCSV_DeepJet = 0.0490;
         medDeepCSV_DeepJet   = 0.2783;
         tightDeepCSV_DeepJet = 0.7100;
      }
      else if(dataYear == "2016")
      {
         looseDeepCSV_DeepJet = 0.0490;
         medDeepCSV_DeepJet   = 0.2783;
         tightDeepCSV_DeepJet = 0.7100;
      }
      else if(dataYear == "2017")
      {
         looseDeepCSV_DeepJet = 0.0490;
         medDeepCSV_DeepJet   = 0.2783;
         tightDeepCSV_DeepJet = 0.7100;
      }
      else if(dataYear == "2018")
      {
         looseDeepCSV_DeepJet = 0.0490;
         medDeepCSV_DeepJet   = 0.2783;
         tightDeepCSV_DeepJet = 0.7100;
      }
      // this is outdated ...



      for (Int_t i=0;i<nentries;i++) 
      {  
         t1->GetEntry(i);
         nEvents+=eventScaleFactor;
         if ( (totHT < 1500.)    ) continue;
         nHTcut+=eventScaleFactor;
         if( (nfatjets < 3) ) continue;
         nAK8JetCut+=eventScaleFactor;
         if ((nfatjet_pre < 2) && ( (dijetMassOne < 1000. ) || ( dijetMassOne < 1000.)  ))
         {
            continue;
         } 
         nHeavyAK8Cut+=eventScaleFactor;
         h_nAK4->Fill(nAK4);

         double eventWeightToUse = 1.0;
         
         /////////////////////////////////////////////////////////////////////////////////
         /////////////////////////////////////////////////////////////////////////////////

         eventnum++;
         //int _nAK4 = 0;
         for(int iii = 0;iii< nAK4; iii++)
         {
            //if(AK4_pt[iii] > 80.) _nAK4++;
            h_AK4_DeepJet_disc_all->Fill(AK4_DeepJet_disc[iii],eventWeightToUse);
         }    
         
         int nTightBTags = 0, nMedBTags = 0, nLooseBtags =0;

         for(int iii = 0;iii< nAK4; iii++)
         {

            h_AK4_DeepJet_disc->Fill(AK4_DeepJet_disc[iii]);
            if ( (AK4_DeepJet_disc[iii] > tightDeepCSV_DeepJet ) && (AK4_pt[iii] > 30.)) nTightBTags++;
            if ( (AK4_DeepJet_disc[iii] > medDeepCSV_DeepJet )   && (AK4_pt[iii] > 30.)) nMedBTags++;
            if ( (AK4_DeepJet_disc[iii] > looseDeepCSV_DeepJet ) && (AK4_pt[iii] > 30.)) nLooseBtags++;
            //if(abs(AK4_partonFlavour[iii])==5) nLooseBtags++;

         }
         h_nTightBTags->Fill(nTightBTags,eventWeightToUse);
         h_nMidBTags->Fill(nMedBTags,eventWeightToUse);
         h_nLooseBTags->Fill(nLooseBtags,eventWeightToUse);


         for(int iii = 0;iii<nAK4;iii++)
         {
            //if(nGenBJets_AK4[iii]>0)nLooseBtags++;
            //h_AK4_partonFlavour->Fill(AK4_partonFlavour[iii]);
            //if(abs(AK4_partonFlavour[iii])==5) nLooseBtags++;
            if(abs(AK4_partonFlavour[iii])==5)
            {
               h_GenBtagged_HT->Fill(totHT,eventWeightToUse);
               h_GenBtagged_pT->Fill(AK4_pt[iii],eventWeightToUse);
            }
            //std::cout << AK4_partonFlavour[iii] << std::endl;

            if(AK4_DeepJet_disc[nAK4]>looseDeepCSV_DeepJet)
            {
               h_RECOBtagged_HT->Fill(totHT,eventWeightToUse);
               h_RECOBtagged_pT->Fill(AK4_pt[iii],eventWeightToUse);
            }
         }



         /// QCD control region 
         if( nTightBTags < 1 ) 
         {
               nNoBjets+=eventScaleFactor;
               h_SJ_nAK4_100_CR->Fill(SJ_nAK4_100[0],eventWeightToUse);
               h_SJ_nAK4_100_CR->Fill(SJ_nAK4_100[1],eventWeightToUse);

               h_SJ_nAK4_200_CR->Fill(SJ_nAK4_200[0],eventWeightToUse);
               h_SJ_nAK4_200_CR->Fill(SJ_nAK4_200[1],eventWeightToUse);

               //h_SJ_mass_CR->Fill( (superJet_mass[0]+superJet_mass[1])/2. ,eventWeightToUse   );
               h_SJ_mass_CR->Fill(superJet_mass[0]);
               h_SJ_mass_CR->Fill(superJet_mass[1]);

               //h_SJ_mass_CR->Fill( superJet_mass[0]    );
               //h_SJ_mass_CR->Fill( superJet_mass[1]    );

               h_disuperjet_mass_CR->Fill(diSuperJet_mass,eventWeightToUse);

               h_nfatjets_CR->Fill(nfatjets,eventWeightToUse);
               for(int iii = 0; iii< nfatjets; iii++)
               {
                  h_AK8_jet_mass_CR->Fill(jet_mass[iii],eventWeightToUse);
               }
               h_nAK4_CR->Fill(nAK4,eventWeightToUse);
               for(int iii = 0; iii< nAK4; iii++)
               {
                  h_AK4_jet_mass_CR->Fill(AK4_mass[iii],eventWeightToUse);
               }
               

               if(   (SJ_nAK4_300[0]>=2) && (SJ_mass_100[0]>400.)   )
               {
                  if((SJ_nAK4_300[1]>=2) && (SJ_mass_100[1]>=400.)   )
                  {
                     h_totHT_CR->Fill(totHT,eventWeightToUse);
                     nDoubleTaggedCR+=eventScaleFactor;
                     h_MSJ_mass_vs_MdSJ_CR->Fill(diSuperJet_mass,(    superJet_mass[1]+superJet_mass[0])/2   ,eventWeightToUse );
                     h_MSJ1_vs_MSJ2_CR->Fill(superJet_mass[0],superJet_mass[1]);

                  }

               }
                           // double tagging NN based
               if(  (SJ1_decision<3) && (SJ2_decision<3)  )
               {
                  {
                     nDoubleTaggedCRNN+=eventScaleFactor;
                  }
               }
         }

         nPassPreSelection++;

         // signal region and TTBar CR
         if ( (nTightBTags > 0)  )
         {
            h_MSJ_mass_vs_MdSJ_dijet->Fill(fourAK8JetMass, (diAK8Jet_mass[0]+diAK8Jet_mass[1])/2.);

            nBtagCut+=eventScaleFactor;
            h_SJ_nAK4_100_SR->Fill(SJ_nAK4_100[0],eventWeightToUse);
            h_SJ_nAK4_100_SR->Fill(SJ_nAK4_100[1],eventWeightToUse);

            h_SJ_nAK4_200_SR->Fill(SJ_nAK4_200[0],eventWeightToUse);
            h_SJ_nAK4_200_SR->Fill(SJ_nAK4_200[1],eventWeightToUse);

            //h_SJ_mass_SR->Fill(superJet_mass[0]);
            //h_SJ_mass_SR->Fill(superJet_mass[1]);


            h_nfatjets_SR->Fill(nfatjets);
            for(int iii = 0; iii< nfatjets; iii++)
            {
               h_AK8_jet_mass_SR->Fill(jet_mass[iii],eventWeightToUse);
            }
            h_nAK4_SR->Fill(nAK4,eventWeightToUse);
            for(int iii = 0; iii< nAK4; iii++)
            {
               h_AK4_jet_mass_SR->Fill(AK4_mass[iii],eventWeightToUse);
            }
            h_totHT_SR->Fill(totHT,eventWeightToUse);

            h_disuperjet_mass_SR->Fill(diSuperJet_mass,eventWeightToUse);
            //if (eventTTbarCRFlag == 0)   /////// full signal region
            //{
               //double tagging CUT BASED
               if(   (SJ_nAK4_300[0]>=2) && (SJ_mass_100[0]>400.)   )
               {
                  if((SJ_nAK4_300[1]>=2) && (SJ_mass_100[1]>=400.)   )
                  {
                     h_SJ_mass_SR->Fill( (superJet_mass[0]+superJet_mass[1])/2.  );
                     nDoubleTagged+= eventScaleFactor;
                     //h_MSJ_mass_vs_MdSJ_doubleTag->Fill( diSuperJet_mass, (superJet_mass[1]+superJet_mass[0]   )/2.  ,eventWeightToUse );
                     h_MSJ_mass_vs_MdSJ_SR->Fill(diSuperJet_mass,(    superJet_mass[1]+superJet_mass[0])/2 ,eventWeightToUse   );
                     h_MSJ1_vs_MSJ2_SR->Fill(superJet_mass[0],superJet_mass[1]);
                  }
               }
                  // double tagging NN based
               if(  (SJ1_decision<3) && (SJ2_decision<3)  )
               {
                  {
                     
                     h_MSJ_mass_vs_MdSJ_SR_NN->Fill(diSuperJet_mass, (superJet_mass[1]+superJet_mass[0]   )/2.,eventWeightToUse );
                     NNDoubleTag+=eventScaleFactor;
                  }
               }
         }

         //anti-tagging 
         if(   (SJ_nAK4_50[0]<1) && (SJ_mass_100[0]<150.)   )
         {
            if((SJ_nAK4_300[1]>=2) && (SJ_mass_100[1]>=400.)   )
            {
               h_totHT->Fill(totHT,eventWeightToUse);
               h_lead_SJ_mass->Fill(superJet_mass[1],eventWeightToUse);
               h_MSJ_mass_vs_MdSJ->Fill(diSuperJet_mass,superJet_mass[1],eventWeightToUse);
               h_SJ_nAK4_100->Fill(SJ_nAK4_100[1],eventWeightToUse);
               h_SJ_nAK4_200->Fill(SJ_nAK4_200[1],eventWeightToUse);
               h_SJ_nAK4_300->Fill(SJ_nAK4_300[1],eventWeightToUse);
               h_SJ_nAK4_400->Fill(SJ_nAK4_400[1],eventWeightToUse);
               h_diSJ_SJ_mass_ratio->Fill(diSuperJet_mass/(superJet_mass[0]+superJet_mass[1]),eventWeightToUse);
               h_lead_SJ_mass_100->Fill(SJ_mass_100[1],eventWeightToUse);

            }
            h_disuperjet_mass->Fill(diSuperJet_mass,eventWeightToUse);
            h_disuperjet_mass_100->Fill(diSuperJet_mass_100,eventWeightToUse);
            h_nfatjets_pre->Fill(nfatjet_pre,eventWeightToUse);
            h_avg_dijet_mass->Fill((dijetMassOne+dijetMassTwo)/2,eventWeightToUse);

         }

         

         nPreselected++;
      }
      outFile.Write();
   }

   outFile.Close();

}


void readTreeMCBR()
{
   bool includeTTBar = true;
   bool allHTBins    = true;
   bool runData      = false;
   std::vector<std::string> dataYears = {"2015","2016","2017","2018"};
   std::vector<std::string> systematics = {"nom","JEC","JER"};  //TESTING


   if(includeTTBar && allHTBins)  /// make sure you are
   {
      for(auto dataYear = dataYears.begin(); dataYear < dataYears.end();dataYear++ )
      {



         std::vector<std::string> dataBlocks; 
         std::string skimmedFilePaths;

         if(runData)
         {
            systematics = {"nom","JEC"};  //TESTING

            if(*dataYear == "2015")
            {
               dataBlocks = {"JetHT_dataB-ver2_","JetHT_dataC-HIPM_","JetHT_dataD-HIPM_","JetHT_dataE-HIPM_","JetHT_dataF-HIPM_"}; // JetHT_dataB-ver1 not present
            }
            else if(*dataYear == "2016")
            {
               dataBlocks = {"JetHT_dataF_", "JetHT_dataG_", "JetHT_dataH_"};
            }
            else if(*dataYear == "2017")
            {
               dataBlocks = {"JetHT_dataB_","JetHT_dataC_","JetHT_dataD_","JetHT_dataE_", "JetHT_dataF_"};
            }
            else if(*dataYear == "2018")
            {
               dataBlocks = {"JetHT_dataA_","JetHT_dataB_","JetHT_dataC_","JetHT_dataD_"};
            }
         }

         else
         {  
           //dataBlocks = {"TTToSemiLeptonic_"}; 
           dataBlocks = {"QCDMC1000to1500_","QCDMC1500to2000_","QCDMC2000toInf_","TTToHadronic_", "TTToSemiLeptonic_", "TTToLeptonic_"};
         }


         for(auto systematic = systematics.begin();systematic<systematics.end();systematic++)
         {
            double eventScaleFactor = 1; 

            for(auto dataBlock = dataBlocks.begin();dataBlock < dataBlocks.end();dataBlock++)
            {

               double nEvents = 0;
               double nHTcut  = 0;
               double nAK8JetCut = 0;
               double nHeavyAK8Cut = 0;
               double nBtagCut = 0;
               double nDoubleTagged = 0;
               double nNoBjets = 0;
               double nDoubleTaggedCR = 0;
               double NNDoubleTag = 0;
               double nDoubleTaggedCRNN = 0;

               std::string year = *dataYear;
               std::string systematic_str = *systematic;

               std::string inFileName = ("/Users/ethan/Documents/rootFiles/skimmedRootFiles/"+*dataBlock+year +  "_"+ systematic_str+ "_SKIMMED.root").c_str();
               std::string outFileName = ("/Users/ethan/Documents/rootFiles/processedRootFiles/"+ *dataBlock+year +  "_"+ systematic_str+ "_processed.root").c_str();

               doThings(inFileName,outFileName,nEvents,nHTcut,nAK8JetCut,nHeavyAK8Cut,nBtagCut,nDoubleTagged,nNoBjets,nDoubleTaggedCR, NNDoubleTag,nDoubleTaggedCRNN, eventScaleFactor, *dataYear,*systematic );
               
               std::cout << "Total breadown: " << nEvents<< " events total, " <<nHTcut << " passed HT cut, " <<nAK8JetCut << " passsed nAK8 jet cut, " <<nHeavyAK8Cut << " passed heavy AK8 jet/ dijet cut, " << nBtagCut << " passed BJet cut, " << nDoubleTagged<< " double tagged." << std::endl;
               std::cout << "Events not passing b-tag requirement: " <<nNoBjets << " , number of events in Control region: " <<nDoubleTaggedCR << ", number of NN doubled-tagged events: "<< nDoubleTaggedCRNN << std::endl;

               std::cout << "number of events NN tagged: " << NNDoubleTag << std::endl;

               std::cout << "Finished with "<< inFileName << "." << std::endl;
            }

            
         }
      }
   }
}


//look at nBtag plots ... 
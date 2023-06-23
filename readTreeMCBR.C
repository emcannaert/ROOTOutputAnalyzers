#include <iostream>
#include <string>
#include "TLorentzVector.h"

using namespace std;

void doThings(std::string inFileName, std::string outFileName, double& nEvents, double& nHTcut, double& nAK8JetCut,double& nHeavyAK8Cut, double& nBtagCut, double& nDoubleTagged,double& nNoBjets, double& nDoubleTaggedCR, double& NNDoubleTag, double& nDoubleTaggedCRNN,double eventScaleFactor, std::string dataYear)
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

   double _eventWeightPU,_puWeightDown,_puWeightUp;


   ////////////////////////////   btag SF variables //////////////////////
   int _eventNumBTag,_eventNumPU, _nAK4;
   double _eventWeightBTag, _AK4_pt[100];

   const char *_inFilename = inFileName.c_str();
   const char *_outFilename = outFileName.c_str();
   std::string _inFilebTaggingSF = "/home/ethan/Documents/bTag_eventWeight_2018.root";
   std::string _inFilePUSF = "/home/ethan/Documents/bTag_eventWeight_2018.root";

   const char * _inFilebTaggingSFUse = _inFilebTaggingSF.c_str();
   const char * _inFilePUSFUse = _inFilePUSF.c_str();

   std::cout << "Reading file: " << _inFilename << std::endl;
   TFile *f = new TFile(_inFilename);
   std::cout << "Also reading b-tag SF file: " << _inFilebTaggingSF << std::endl;
   TFile *f2 = new TFile(_inFilebTaggingSFUse);
   TFile *f3 = new TFile(_inFilePUSFUse);

   TFile outFile(_outFilename,"RECREATE");

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

   // control region stuff 
   TH1I* h_SJ_nAK4_100_CR  = new TH1I("h_SJ_nAK4_100_CR","Number of Reclustered AK4 Jets (E_{COM} > 100 GeV) per SJ (Control Region);nAK4 Jets (E_{COM} > 100 GeV); Events",10,-0.5,9.5);
   TH1I* h_SJ_nAK4_200_CR  = new TH1I("h_SJ_nAK4_200_CR","Number of Reclustered AK4 Jets (E_{COM} > 200 GeV) per SJ (Control Region);nAK4 Jets (E_{COM} > 200 GeV); Events",10,-0.5,9.5);
   TH1F* h_SJ_mass_CR  = new TH1F("h_SJ_mass_CR","SuperJet Mass (Control Region) ;Mass [GeV]; Events / 125 GeV",40,0.,5000);
   TH1F* h_disuperjet_mass_CR  = new TH1F("h_disuperjet_mass_CR","diSuperJet Mass (Control Region);Mass [GeV]; Events / 400 GeV",25,0.,10000);
   TH2F *h_MSJ_mass_vs_MdSJ_CR = new TH2F("h_MSJ_mass_vs_MdSJ_CR","Double Tagged Superjet mass vs diSuperjet mass (Control Region); diSuperjet mass [GeV];superjet mass", 25,0, 10000, 20, 0, 6000);



   // double-tag stuff
   TH1I* h_SJ_nAK4_100_DT  = new TH1I("h_SJ_nAK4_100_DT","Number of Reclustered AK4 Jets (E_{COM} > 100 GeV) per SJ (Signal Region);nAK4 Jets (E_{COM} > 100 GeV); Events",10,-0.5,9.5);
   TH1I* h_SJ_nAK4_200_DT = new TH1I("h_SJ_nAK4_200_DT","Number of Reclustered AK4 Jets (E_{COM} > 200 GeV) per SJ (Signal Region);nAK4 Jets (E_{COM} > 200 GeV); Events",10,-0.5,9.5);
   TH1F* h_SJ_mass_DT  = new TH1F("h_SJ_mass_DT","SuperJet Mass (Signal Region) ;Mass [GeV]; Events / 125 GeV",40,0.,5000);
   TH1F* h_disuperjet_mass_DT  = new TH1F("h_disuperjet_mass_DT","diSuperJet Mass (Signal Region);Mass [GeV]; Events / / 400 GeV",25,0.,10000);
   TH2F *h_MSJ_mass_vs_MdSJ_DT = new TH2F("h_MSJ_mass_vs_MdSJ_DT","Double Tagged Superjet mass vs diSuperjet mass (Signal Region); diSuperjet mass [GeV];superjet mass", 25,0, 10000, 20, 0, 6000);

   TH1I* h_nLooseBTags = new TH1I("h_nLooseBTags","Number of Loosely b-tagged AK4 Jets; Events",10,-0.5,9.5);
   TH1I* h_nMidBTags = new TH1I("h_nMidBTags","Number of Mediumly b-tagged AK4 Jets; Events",10,-0.5,9.5);
   TH1I* h_nTightBTags = new TH1I("h_nTightBTags","Number of Tightly b-tagged AK4 Jets; Events",10,-0.5,9.5);



   /////////////more for verifying the CR //////////////////////////////////////
   TH1F* h_AK8_jet_mass_DT  = new TH1F("h_AK8_jet_mass_DT","AK8 Jet Mass (DT region);Mass [GeV]; Events / 30 5GeV",50,0.,1500);
   TH1F* h_AK8_jet_mass_CR  = new TH1F("h_AK8_jet_mass_CR","AK8 Jet Mass (CR);Mass [GeV]; Events / 30 GeV",50,0.,1500);

   TH1F* h_AK4_jet_mass_DT  = new TH1F("h_AK4_jet_mass_DT","AK4 Jet Mass (DT region);Mass [GeV]; Events / 25 GeV",40,0.,1000);
   TH1F* h_AK4_jet_mass_CR  = new TH1F("h_AK4_jet_mass_CR","AK4 Jet Mass (CR);Mass [GeV]; Events / 25 GeV",40,0.,1000);

   TH1F* h_totHT_DT  = new TH1F("h_totHT_DT","Event H_{T} (DT region);H_{T} [GeV]; Events / 200 5GeV",50,0.,10000);
   TH1F* h_totHT_CR  = new TH1F("h_totHT_CR","Event H_{T} (CR);H_{T} [GeV]; Events / 200 GeV",50,0.,10000);

   TH1I* h_nfatjets_DT = new TH1I("h_nfatjets_DT","Number of AK8 Jets (E_{T} > 300 GeV per Event ;nAK8 Jets; Events",10,-0.5,9.5);
   TH1I* h_nfatjets_CR = new TH1I("h_nfatjets_CR","Number of AK8 Jets (E_{T} > 300 GeV per Event ;nAK8 Jets; Events",10,-0.5,9.5);

   TH1I* h_nAK4_DT = new TH1I("h_nAK4_DT","Number of AK4 Jets (E_{T} > 30 GeV per Event ;nAK8 Jets; Events",30,-0.5,29.5);
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

   //TH1I* h_nAK4_CR = new TH1I("nGenBJets_AK4_CR","Number of AK4 Jets (E_{T} > 30 GeV per Event ;nAK8 Jets; Events",30,-0.5,29.5);

   int nAntiTaggedAntiTagged = 0;
   int nAntiTaggedTagged     = 0;
   int nTaggedAntiTagged     = 0;
   int nTaggedTagged         = 0;

   int failedHT = 0;
   int failedbTag = 0;
   int failedRatio = 0;
   int failednAK8 = 0;

   TCanvas *c1 = new TCanvas("c1","",400,20, 2000,2000);
   // run this file four times, once for each of the different 2018 dataset pieces

   TTree *t1 = (TTree*)f->Get("skimmedTree");   //need to change this to something relevenet
   const Int_t nentries = t1->GetEntries();

   TTree *t2 = (TTree*)f2->Get("T");   //need to change this to something relevenet   weightsBTagging
   TTree *t3 = (TTree*)f3->Get("weightsPU");   //need to change this to something relevenet

   
   //const Int_t nentries_btagSF = t2->GetEntries();

   t1->AddFriend(t2);
   //t1->AddFriend(t3);

   //std::cout << t1->GetListOfBranches()->FindObject("AK4_partonFlavour") << std::endl;
   //t1->GetListOfBranches()->Print(); 
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


   //////////////////////btag SF variables/////////////////////
   t1->SetBranchAddress("T._eventNumBTag", &_eventNumBTag); 
   t1->SetBranchAddress("T._nAK4", &_nAK4); 
   t1->SetBranchAddress("T._eventWeightBTag", &_eventWeightBTag); 
   t1->SetBranchAddress("T._AK4_pt", _AK4_pt); 

/*
   t1->SetBranchAddress("weightsPU._eventNumPU", &_eventNumPU); 
   t1->SetBranchAddress("weightsPU._eventWeightPU", &_eventWeightPU); 
   t1->SetBranchAddress("weightsPU._puWeightDown", &_puWeightDown); 
   t1->SetBranchAddress("weightsPU._puWeightUp", &_puWeightUp); 
*/

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

 
   double looseDeepCSV_DeepJet = 0.0490;
   double medDeepCSV_DeepJet   = 0.2783;
   double tightDeepCSV_DeepJet = 0.7100;

   for (Int_t i=0;i<nentries;i++) 
   {  
      t1->GetEntry(i);
      if( (nfatjets < 3) || (totHT < 1500.)     ) continue;

      if ((nfatjet_pre < 2) && ( (dijetMassOne < 1000. ) || ( dijetMassTwo < 1000.)  ))
      {
         continue;
      } 
      h_nAK4->Fill(nAK4);


      /////////////////////////////////////////////////////////////////////////////////
      ///////make sure event matches from analyzer matches event from btagSF tree//////
      double eventWeightToUse = 1.0;
      /*
      double epsilon = 1e-8;
      int jetsMatch = 1;
      if((eventnum == _eventNumBTag) && (nAK4 == _nAK4) ) 
      {
         for(int iii =0;iii<nAK4;iii++)
         {
            if( abs(AK4_pt[iii]-_AK4_pt[iii]) > epsilon)jetsMatch*=0;
         }
         if(jetsMatch > 0)
         {
            eventWeightToUse *=_eventWeightBTag;
            //eventWeightToUse *=_eventNumPU;
         }
         else { std::cout << "bad event - AK4 jet pt does not match ... " << std::endl;}
      }  
      else
      {
         std::cout << "something didnt match: eventnums: " << eventnum << "/" << _eventNumBTag << "/" <<  " nAK4: " << nAK4 << "/" << _nAK4 << std::endl;
      }
      */
      
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



      /// control region 
      if( nLooseBtags < 1 ) 
      {

            nNoBjets+=eventScaleFactor;
            h_SJ_nAK4_100_CR->Fill(SJ_nAK4_100[0],eventWeightToUse);
            h_SJ_nAK4_100_CR->Fill(SJ_nAK4_100[1],eventWeightToUse);

            h_SJ_nAK4_200_CR->Fill(SJ_nAK4_200[0],eventWeightToUse);
            h_SJ_nAK4_200_CR->Fill(SJ_nAK4_200[1],eventWeightToUse);

            h_SJ_mass_CR->Fill( (superJet_mass[0]+superJet_mass[1])/2. ,eventWeightToUse   );
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
            h_totHT_CR->Fill(totHT,eventWeightToUse);

            if(   (SJ_nAK4_300[0]>=2) && (SJ_mass_100[0]>400.)   )
            {
               if((SJ_nAK4_300[1]>=2) && (SJ_mass_100[1]>=400.)   )
               {

                  nDoubleTaggedCR+=eventScaleFactor;
                  h_MSJ_mass_vs_MdSJ_CR->Fill(diSuperJet_mass,(    superJet_mass[1]+superJet_mass[0])/2   ,eventWeightToUse );
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

      // signal region
      if ( (nTightBTags > 0)  )
      {
            
         nBtagCut+=eventScaleFactor;
         h_SJ_nAK4_100_DT->Fill(SJ_nAK4_100[0],eventWeightToUse);
         h_SJ_nAK4_100_DT->Fill(SJ_nAK4_100[1],eventWeightToUse);

         h_SJ_nAK4_200_DT->Fill(SJ_nAK4_200[0],eventWeightToUse);
         h_SJ_nAK4_200_DT->Fill(SJ_nAK4_200[1],eventWeightToUse);

         h_SJ_mass_DT->Fill( (superJet_mass[0]+superJet_mass[1])/2. ,eventWeightToUse  );
         //h_SJ_mass_DT->Fill(superJet_mass[0]);
         //h_SJ_mass_DT->Fill(superJet_mass[1]);


         h_nfatjets_DT->Fill(nfatjets);
         for(int iii = 0; iii< nfatjets; iii++)
         {
            h_AK8_jet_mass_DT->Fill(jet_mass[iii],eventWeightToUse);
         }
         h_nAK4_DT->Fill(nAK4,eventWeightToUse);
         for(int iii = 0; iii< nAK4; iii++)
         {
            h_AK4_jet_mass_DT->Fill(AK4_mass[iii],eventWeightToUse);
         }
         h_totHT_DT->Fill(totHT,eventWeightToUse);

         h_disuperjet_mass_DT->Fill(diSuperJet_mass,eventWeightToUse);
      
         //double tagging CUT BASED
         if(   (SJ_nAK4_300[0]>=2) && (SJ_mass_100[0]>400.)   )
         {
            if((SJ_nAK4_300[1]>=2) && (SJ_mass_100[1]>=400.)   )
            {
               nDoubleTagged+= eventScaleFactor;
               h_MSJ_mass_vs_MdSJ_doubleTag->Fill( diSuperJet_mass, (superJet_mass[1]+superJet_mass[0]   )/2.  ,eventWeightToUse );
               h_MSJ_mass_vs_MdSJ_DT->Fill(diSuperJet_mass,(    superJet_mass[1]+superJet_mass[0])/2 ,eventWeightToUse   );
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
   //std::cout << "nControlRegion / nTotal : " << nControlRegion << "/" << nPassPreSelection << std::endl;
/*
   h_AK4_partonFlavour->Draw("HIST");
   c1->SaveAs("h_MSJ_mass_vs_MdSJ_doubleTag.png");

   h_MSJ_mass_vs_MdSJ_doubleTag->Draw("colz");
   c1->SaveAs("h_MSJ_mass_vs_MdSJ_doubleTag.png");

   h_MSJ_mass_vs_MdSJ_DT->Draw("colz");
   c1->SaveAs("h_MSJ_mass_vs_MdSJ_DT.png");
   h_MSJ_mass_vs_MdSJ_CR->Draw("colz");
   c1->SaveAs("h_MSJ_mass_vs_MdSJ_CR.png");

   h_SJ_nAK4_100_DT->Draw("colz");
   c1->SaveAs("h_SJ_nAK4_100_DT.png");

   h_SJ_nAK4_200_DT->Draw("colz");
   c1->SaveAs("h_SJ_nAK4_200_DT.png");

   h_SJ_mass_DT->Draw("colz");
   c1->SaveAs("h_SJ_mass_DT.png");

   h_disuperjet_mass_DT->Draw("colz");
   c1->SaveAs("h_disuperjet_mass_DT.png");

   h_MSJ_mass_vs_MdSJ_DT->Draw("colz");
   c1->SaveAs("h_MSJ_mass_vs_MdSJ_DT.png");

   h_SJ_nAK4_100_CR->Draw("colz");
   c1->SaveAs("h_SJ_nAK4_100_CR.png");

   h_SJ_nAK4_200_CR->Draw("colz");
   c1->SaveAs("h_SJ_nAK4_200_CR.png");

   h_SJ_mass_CR->Draw("colz");
   c1->SaveAs("h_SJ_mass_CR.png");

   h_disuperjet_mass_CR->Draw("colz");
   c1->SaveAs("h_disuperjet_mass_CR.png");

   h_MSJ_mass_vs_MdSJ_CR->Draw("colz");
   c1->SaveAs("h_MSJ_mass_vs_MdSJ_CR.png");

   h_nTightBTags->Draw();
   c1->SaveAs("h_nTightBTags.png");
   h_nMidBTags->Draw();
   c1->SaveAs("h_nMidBTags.png");
   h_nLooseBTags->Draw();
   c1->SaveAs("h_nLooseBTags.png");
*/

   outFile.Write();
   //outFile.Close();

}


void readTreeMCBR()
{
   bool includeTTBar = false;
   bool allHTBins    = false;
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
   std::string dataYear = "2018";

   if(includeTTBar && allHTBins)
   {
      double eventScaleFactors[6] = {4.289571744,0.6042726685,0.2132134533,0.06588049107,0.03616639075,0.04563489275};

      std::vector<std::string> inFileNames = {"/home/ethan/Documents/QCD_HT1000to1500_SKIMMED_TEST.root",
                                            "/home/ethan/Documents/QCD_HT1500to2000_SKIMMED_TEST.root",
                                            "/home/ethan/Documents/QCD_HT2000toInf_SKIMMED_TEST.root",
                                            "/home/ethan/Documents/TTToHadronic_SKIMMED_TEST.root",
                                            "/home/ethan/Documents/TTTo2l2nu_SKIMMED.root",
                                            "/home/ethan/Documents/TTtoSemiLeptonic_SKIMMED_TEST.root" };
      std::vector<std::string> outFileNames = {"/home/ethan/Documents/QCD_HT1000to1500_processed_TEST.root",
                                            "/home/ethan/Documents/QCD_HT1500to2000_processed_TEST.root",
                                            "/home/ethan/Documents/QCD_HT2000toInf_processed_TEST.root",
                                            "/home/ethan/Documents/TTToHadronic_processed_TEST.root",
                                            "/home/ethan/Documents/TTTo2l2nu_processed_TEST.root",
                                            "/home/ethan/Documents/TTtoSemiLeptonic_processed_TEST.root" };
      for(unsigned int iii = 0; iii<inFileNames.size(); iii++)
      {
         doThings(inFileNames[iii],outFileNames[iii],nEvents,nHTcut,nAK8JetCut,nHeavyAK8Cut,nBtagCut,nDoubleTagged,nNoBjets,nDoubleTaggedCR,NNDoubleTag,nDoubleTaggedCRNN, eventScaleFactors[iii],dataYear );
      }
      std::cout << "Total breadown: " << nEvents<< " events total, " <<nHTcut << " passed HT cut, " <<nAK8JetCut << " passsed nAK8 jet cut, " <<nHeavyAK8Cut << " passed heavy AK8 jet/ dijet cut, " << nBtagCut << " passed BJet cut, " << nDoubleTagged<< " double tagged." << std::endl;
      std::cout << "Events not passing b-tag requirement: " <<nNoBjets << " , number of events in Control region: " <<nDoubleTaggedCR << ", number of NN doubled-tagged events: "<< nDoubleTaggedCRNN << std::endl;

      std::cout << "number of events NN tagged: " << NNDoubleTag << std::endl;

      std::cout << "Finished with "<< inFileNames.size() << " files." << std::endl;
   }
   else if( !includeTTBar && allHTBins)
   {
      double eventScaleFactors[3] = {4.289571744,0.6042726685,0.2132134533};

      std::vector<std::string> inFileNames = {("/home/ethan/Documents/QCD_HT1000to1500_SKIMMED_TEST_"+ dataYear + ".root").c_str(),("/home/ethan/Documents/QCD_HT1500to2000_SKIMMED_TEST_"+ dataYear + ".root").c_str(),("/home/ethan/Documents/QCD_HT2000toInf_SKIMMED_TEST_"+ dataYear + ".root").c_str()};

      std::vector<std::string> outFileNames = {("/home/ethan/Documents/QCD_HT1000to1500_processed_TEST_NOBTSF"+ dataYear + ".root").c_str(),("/home/ethan/Documents/QCD_HT1500to2000_processed_TEST_NOBTSF"+ dataYear + ".root").c_str(),("/home/ethan/Documents/QCD_HT2000toInf_processed_TEST_NOBTSF"+ dataYear + ".root").c_str()};
      for(unsigned int iii = 0; iii<inFileNames.size(); iii++)
      {
         doThings(inFileNames[iii],outFileNames[iii],nEvents,nHTcut,nAK8JetCut,nHeavyAK8Cut,nBtagCut,nDoubleTagged,nNoBjets,nDoubleTaggedCR,NNDoubleTag,nDoubleTaggedCRNN,eventScaleFactors[iii],dataYear );
      }
      std::cout << "Total breadown: " << nEvents<< " events total, " <<nHTcut << " passed HT cut, " <<nAK8JetCut << " passsed nAK8 jet cut, " <<nHeavyAK8Cut << " passed heavy AK8 jet/ dijet cut, " << nBtagCut << " passed BJet cut, " << nDoubleTagged<< " double tagged." << std::endl;
      std::cout << "number of events NN tagged: " << NNDoubleTag << std::endl;

      std::cout << "Events not passing b-tag requirement: " <<nNoBjets << " , number of events in Control region: " <<nDoubleTaggedCR << ", number of NN doubled-tagged events: "<< nDoubleTaggedCRNN << std::endl;

      std::cout << "Finished with "<< inFileNames.size() << " files." << std::endl;
   }
   else
   {
      double eventScaleFactors[3] = {4.289571744,0.6042726685,0.2132134533};

      std::vector<std::string> inFileNames = {("/home/ethan/Documents/QCD_HT2000toInf_SKIMMED_TEST_"+ dataYear + ".root").c_str()};

      std::vector<std::string> outFileNames = {("/home/ethan/Documents/QCD_HT2000toInf_processed_TEST_NOBTSF"+ dataYear + ".root").c_str()};
      for(unsigned int iii = 0; iii<inFileNames.size(); iii++)
      {
         doThings(inFileNames[iii],outFileNames[iii],nEvents,nHTcut,nAK8JetCut,nHeavyAK8Cut,nBtagCut,nDoubleTagged,nNoBjets,nDoubleTaggedCR,NNDoubleTag,nDoubleTaggedCRNN,eventScaleFactors[iii],dataYear );
      }
      std::cout << "Total breadown: " << nEvents<< " events total, " <<nHTcut << " passed HT cut, " <<nAK8JetCut << " passsed nAK8 jet cut, " <<nHeavyAK8Cut << " passed heavy AK8 jet/ dijet cut, " << nBtagCut << " passed BJet cut, " << nDoubleTagged<< " double tagged." << std::endl;
      std::cout << "number of events NN tagged: " << NNDoubleTag << std::endl;

      std::cout << "Events not passing b-tag requirement: " <<nNoBjets << " , number of events in Control region: " <<nDoubleTaggedCR << ", number of NN doubled-tagged events: "<< nDoubleTaggedCRNN << std::endl;

      std::cout << "Finished with "<< inFileNames.size() << " files." << std::endl;
   }

}


//look at nBtag plots ... 
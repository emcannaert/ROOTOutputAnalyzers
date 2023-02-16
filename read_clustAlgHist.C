#include <iostream>
#include <string>
#include "TLorentzVector.h"

using namespace std;


void read_clustAlgHist()
{

   int eventnum = 0;
   int nhadevents = 0;
   int nfatjets = 0;
   int raw_nfatjets;
   int tot_nAK4_50,tot_nAK4_70;
   int SJ_nAK4_50[100],SJ_nAK4_70[100];
   double jet_pt[100], jet_eta[100], jet_mass[100], jet_dr[100], raw_jet_mass[100],raw_jet_pt[100],raw_jet_phi[100];
   double jet_beta[100], beta_T[100], AK4_mass_20[100],AK4_mass_30[100],AK4_mass_50[100],AK4_mass_70[100],AK4_mass_100[100],AK4_mass_150[100];
   double SJ_mass_50[100], SJ_mass_70[100],superJet_mass[100],SJ_AK4_50_mass[100],SJ_AK4_70_mass[100],genSuperJetMass[100];
   double tot_jet_mass,decay_inv_mass, chi_inv_mass;
   int nSuperJets,correctlySortedChi1,correctlySortedChi2;
   int nSuccessfulSorts = 0;
   int jet_ndaughters[100], jet_nAK4[100],jet_nAK4_20[100],jet_nAK4_30[100],jet_nAK4_50[100],jet_nAK4_70[100],jet_nAK4_100[100],jet_nAK4_150[100];
   int ntotalevents = 0;
   int nAK4;
   double topAK8_dr,WSuuAK8_dr,bSuuAK8_dr,higgsAK8_dr,topWAK8_dr,topbAK8_dr,topAK4_dr,WSuuAK4_dr,bSuuAK4_dr,higgsAK4_dr,topWAK4_dr,topbAK4_dr;
   double AK4_mass[100];
   double chi_dr,topPart_dr,higgs_dr,SuuW_dr,HiggsTop_dr,SuuWb_dr;
   int tot_mpp_AK4;
   double SJ_mass_100[100],SJ_mass_125[100],SJ_mass_150[100],SJ_mass_200[100],SJ_mass_300[100],SJ_mass_400[100],SJ_mass_600[100],SJ_mass_800[100],SJ_mass_1000[100],AK4_E[500];
   int SJ_nAK4_100[100], SJ_nAK4_125[100], SJ_nAK4_150[100], SJ_nAK4_200[100], SJ_nAK4_300[100], SJ_nAK4_400[100],SJ_nAK4_600[100],SJ_nAK4_800[100],SJ_nAK4_1000[100];
   double genPartChiDaughterMPP_angle[2];
   double genHiggsThrustCos[100], genTopWThrustCos[100], genSuuWThrustCos[100];
   double genTopbThrustCos,genSuubThrustCos,diSuperJet_mass,diSuperJet_mass_100;
   double jet_thrust_cos[100];
   double totHT;
   int nonHadFlag;
   int nbtaggedAK4;
   int nfatjet_pre;

   bool _htWb;
   bool _htZt;
   bool _ZtWb;
   bool _WbWb;
   bool _htht;
   bool _ZtZt;

   //TFile *f = new TFile("/home/ethan/Documents/ClusteringAlgorithm_SuuTeV_chi3TeV_ALLDECAYS_RATIO_SORT_output.root");
   //TFile outFile("/home/ethan/Documents/ClusteringAlgorithm_Suu8TeV_chi3TeV_ALLDECAYS_processed.root","RECREATE");
   
   TFile *f = new TFile("/home/ethan/Documents/ClusteringAlgorithm_Suu4TeV_chi850GeV_RATIO_SORT_output.root");
   TFile outFile("/home/ethan/Documents/ClusteringAlgorithm_Suu4TeV_chi850GeV_RATIO_SORT_MCTRUH_processed.root","RECREATE");

   //TFile *f = new TFile("/home/ethan/Documents/ClusteringAlgorithm_Suu4TeV_chi850GeV_RATIO_NOSORT_output.root");
   //TFile outFile("/home/ethan/Documents/ClusteringAlgorithm_Suu4TeV_chi850GeV_RATIO_NOSORT_MCTRUH_processed.root","RECREATE");
   TCanvas *c1 = new TCanvas("c1","",400,20, 2000,2000);



   ////////////////////////require 3 AK4 jets E > 70, maybe go to 100 GeV? limit ETA to 2.4, require 3+ AK8 jets to begin with, b-tagged jets?
////////////////////////Change this to go back do diquark! Change the tree
   TTree *t1 = (TTree*)f->Get("clusteringAnalyzer/tree");
   const Int_t nentries = t1->GetEntries();

////////////////////////////////////////////////////////////////////////////////////////////////////////

   TH1I* h_nfatjets = new TH1I("h_nfatjets","Number of AK8 Jets; # AK8 Jets",8,-0.5,7.5);

   TH1F* h_SJ_AK4_50_mass = new TH1F("h_SJ_AK4_50_mass","Mass of Reclustered AK4 Jets (E_{MPP} >50 GeV);p_{T} [GeV];Events / 20 GeV",40,0.,800);
   TH1F* h_SJ_AK4_70_mass = new TH1F("h_SJ_AK4_70_mass","Mass of Reclustered AK4 Jets (E_{MPP} >70 GeV);p_{T} [GeV]; Events / 20 GeV",40,0.,800);

   TH1F* h_SJ_mass_50 = new TH1F("h_SJ_mass_50","Mass of Reclustered SuperJet (E_{MPP} >50 GeV);p_{T} [GeV]; Events / 160 GeV",50,0.,8000);
   TH1F* h_SJ_mass_70 = new TH1F("h_SJ_mass_70","Mass of Reclustered SuperJet (E_{MPP} >70 GeV);p_{T} [GeV]; Events / 160 GeV",50,0.,8000);

   TH1I* h_nAK4 = new TH1I("h_nAK4","Number of AK4 Jets; # AK4 Jets",30,-0.5,29.5);
   TH1F* h_topAK8_dr = new TH1F("h_topAK8_dr","delta R between gen Top and nearest AK8 Jet;delta R",50,0.,7.0);
   TH1F* h_WSuuAK8_dr = new TH1F("h_WSuuAK8_dr","delta R between gen Suu W and nearest AK8 Jet;delta R",50,0.,7.0);
   TH1F* h_bSuuAK8_dr = new TH1F("h_bSuuAK8_dr","delta R between gen Suu b and nearest AK8 Jet;delta R",50,0.,7.0);
   TH1F* h_higgsAK8_dr = new TH1F("h_higgsAK8_dr","delta R between gen Higgs and nearest AK8 Jet;delta R",50,0.,7.0);
   TH1F* h_topWAK8_dr = new TH1F("h_topWAK8_dr","delta R between gen Top W and nearest AK8 Jet;delta R",50,0.,7.0);
   TH1F* h_topbAK8_dr = new TH1F("h_topbAK8_dr","delta R between gen Top b and nearest AK8 Jet;delta R",50,0.,7.0);

   TH1F* h_topAK4_dr = new TH1F("h_topAK4_dr","delta R between gen Top and nearest AK4 Jet;delta R",50,0.,7.0);
   TH1F* h_WSuuAK4_dr = new TH1F("h_WSuuAK4_dr","delta R between gen Suu W and nearest AK4 Jet;delta R",50,0.,7.0);
   TH1F* h_bSuuAK4_dr = new TH1F("h_bSuuAK4_dr","delta R between gen Suu b and nearest AK4 Jet;delta R",50,0.,7.0);
   TH1F* h_higgsAK4_dr = new TH1F("h_higgsAK4_dr","delta R between gen Higgs and nearest AK4 Jet;delta R",50,0.,7.0);
   TH1F* h_topWAK4_dr = new TH1F("h_topWAK4_dr","delta R between gen Top W and nearest AK4 Jet;delta R",50,0.,7.0);
   TH1F* h_topbAK4_dr = new TH1F("h_topbAK4_dr","delta R between gen Top b and nearest AK4 Jet;delta R",50,0.,7.0);

   TH1F* h_AK4_mass = new TH1F("h_AK4_mass","Mass of AK4 Jets;Mass [GeV]",30,0.,600);

   TH1F* h_chi_dr = new TH1F("h_chi_dr","delta R between gen Chis ;delta R",50,0.,7.0);
   TH1F* h_topPart_dr = new TH1F("h_topPart_dr","delta R between gen Top Constituents ;delta R",50,0.,7.0);
   TH1F* h_higgs_dr = new TH1F("h_higgs_dr","delta R between gen Higgs Constituents ;delta R",50,0.,7.0);
   TH1F* h_SuuW_dr = new TH1F("h_SuuW_dr","delta R between gen Suu W Constituents ;delta R",50,0.,7.0);
   TH1F* h_HiggsTop_dr = new TH1F("h_HiggsTop_dr","delta R between gen Higgs and Top;delta R",50,0.,7.0);
   TH1F* h_SuuWb_dr = new TH1F("h_HiggsTop_dr","delta R between gen Suu W and b;delta R",50,0.,7.0);

   TH1F* h_superJet_mass = new TH1F("h_superJet_mass","Mass of SuperJets; Mass [GeV];Events / 100 GeV",25,0.,2500.);


   TH1F* h_AK4_E = new TH1F("h_AK4_E","Energy of AK4 Jets;Energy [GeV]",100,0.,600.);
   TH1F* h_SJ_mass_100 = new TH1F("h_SJ_mass_100","Mass of SuperJets (E_{MPP}> 100 GeV);Mass [GeV]; Events / 160 GeV",50,0.,8000.);
   TH1F* h_SJ_mass_125 = new TH1F("h_SJ_mass_125","Mass of SuperJets (E_{MPP}> 125 GeV);Mass [GeV]; Events / 160 GeV",50,0.,8000.);
   TH1F* h_SJ_mass_150 = new TH1F("h_SJ_mass_150","Mass of SuperJets (E_{MPP}> 150 GeV);Mass [GeV]; Events / 160 GeV",50,0.,8000.);
   TH1F* h_SJ_mass_200 = new TH1F("h_SJ_mass_200","Mass of SuperJets (E_{MPP}> 200 GeV);Mass [GeV]; Events / 160 GeV",50,0.,8000.);
   TH1F* h_SJ_mass_300 = new TH1F("h_SJ_mass_300","Mass of SuperJets (E_{MPP}> 300 GeV);Mass [GeV]; Events / 160 GeV",50,0.,8000.);
   TH1F* h_SJ_mass_400 = new TH1F("h_SJ_mass_400","Mass of SuperJets (E_{MPP}> 400 GeV);Mass [GeV]; Events / 160 GeV",50,0.,8000.);

   TH1I* h_SJ_nAK4_100 = new TH1I("h_SJ_nAK4_100","Number of AK4 Jets (E_{MPP} > 100 GeV); # AK4 Jets",9,-0.5,8.5);
   TH1I* h_SJ_nAK4_125 = new TH1I("h_SJ_nAK4_125","Number of AK4 Jets (E_{MPP} > 125 GeV); # AK4 Jets",9,-0.5,8.5);
   TH1I* h_SJ_nAK4_150 = new TH1I("h_SJ_nAK4_150","Number of AK4 Jets (E_{MPP} > 150 GeV); # AK4 Jets",9,-0.5,8.5);
   TH1I* h_SJ_nAK4_200 = new TH1I("h_SJ_nAK4_200","Number of AK4 Jets (E_{MPP} > 200 GeV); # AK4 Jets",9,-0.5,8.5);
   TH1I* h_SJ_nAK4_300 = new TH1I("h_SJ_nAK4_300","Number of AK4 Jets (E_{MPP} > 300 GeV); # AK4 Jets",9,-0.5,8.5);
   TH1I* h_SJ_nAK4_400 = new TH1I("h_SJ_nAK4_400","Number of AK4 Jets (E_{MPP} > 400 GeV); # AK4 Jets",9,-0.5,8.5);
   TH1I* h_SJ_nAK4_600 = new TH1I("h_SJ_nAK4_600","Number of AK4 Jets (E_{MPP} > 600 GeV); # AK4 Jets",9,-0.5,8.5);
   TH1I* h_SJ_nAK4_800 = new TH1I("h_SJ_nAK4_800","Number of AK4 Jets (E_{MPP} > 800 GeV); # AK4 Jets",9,-0.5,8.5);
   TH1I* h_SJ_nAK4_1000 = new TH1I("h_SJ_nAK4_1000","Number of AK4 Jets (E_{MPP} > 1000 GeV); # AK4 Jets",9,-0.5,8.5);
   
   TH1F* h_genSuperJet1Mass = new TH1F("h_genSuperJet1Mass","Mass of (Gen) SuperJet 1;Mass [GeV]",100,0.,8000.);
   TH1F* h_genSuperJet2Mass = new TH1F("h_genSuperJet2Mass","Mass of (Gen) SuperJet 2;Mass [GeV]",100,0.,8000.);


   TH1F* h_genPartChi1DaughterMPP_angle = new TH1F("h_genPartChi1DaughterMPP_angle","(largest) Angle between gen Chi 1 Daughters;Angle [Rads]",50,0.,3.25);
   TH1F* h_genPartChi2DaughterMPP_angle = new TH1F("h_genPartChi2DaughterMPP_angle","(largest) Angle between gen Chi 2 Daughters;Angle [Rads]",50,0.,3.25);

   TH1F* h_genPartChiDaughterMPP_angle = new TH1F("h_genPartChiDaughterMPP_angle","(largest) Angle between gen Chi Daughters;Angle [Rads]",50,0.,3.25);
   TH1F* h_genSuperJetMass = new TH1F("h_genSuperJetMass","Mass of (Gen) SuperJets ;Mass [GeV]",100,0.,8000.);
   TH1F* h_genHiggsThrustCos = new TH1F("h_genHiggsThrustCos","Cos of Angle between gen Higgs Daughters and Thrust Axis;Cos",50,-1.,1.);
   TH1F* h_genTopWThrustCos = new TH1F("h_genTopWThrustCos","Cos of Angle between gen Top W daughters and Thrust Axis;Cos",50,-1.,1.);
   TH1F* h_genSuuWThrustCos = new TH1F("h_genSuuWThrustCos","Cos of Angle between gen Suu W daughters and Thrust Axis;Cos",50,-1.,1.);
   TH1F* h_genTopbThrustCos = new TH1F("h_genTopbThrustCos","Cos of Angle between gen Top b and Thrust Axis;Cos",50,-1.,1.);
   TH1F* h_genSuubThrustCos = new TH1F("h_genSuubThrustCos","Cos of Angle between gen Suu b and Thrust Axis;Cos",50,-1.,1.);

   TH1F* h_diSuperJet_mass = new TH1F("h_diSuperJet_mass","diSuperJet Mass;Mass [GeV]; Events / 200 GeV",50,0.,10000.);
   TH1F* h_diSuperJet_mass_100 = new TH1F("h_diSuperJet_mass_100","diSuperJet Mass (E_{MPP} > 100 GeV);Mass [GeV]; Events / 200 GeV",50,0.,10000.);
   TH1F* h_jet_thrust_cos = new TH1F("h_jet_thrust_cos","Cos of Angle between AK8 jets and Thrust Axis;Cos",50,-1.,1.);

   TH1F* h_diSuperJet_mass_diag = new TH1F("h_diSuperJet_mass_diag","diSuperJet Mass (Along SJ mass diagonal);Mass [GeV]; Events / 200 GeV",50,0.,10000.);

   TH2F* h_superJet_mass_TH2 = new TH2F("h_superJet_mass_TH2", "SuperJet 1 Mass vs SuperJet 2 Mass [GeV];Events / 100 GeV", 50, 0., 5000., 50., 0., 5000.);

   t1->SetBranchAddress("nfatjets", &nfatjets);   
   t1->SetBranchAddress("nSuperJets", &nSuperJets);   
   t1->SetBranchAddress("tot_nAK4_50", &tot_nAK4_50);               //total #AK4 jets (E>50 GeV) for BOTH superjets
   t1->SetBranchAddress("tot_nAK4_70", &tot_nAK4_70);   
   t1->SetBranchAddress("diSuperJet_mass", &diSuperJet_mass);   
   t1->SetBranchAddress("diSuperJet_mass_100", &diSuperJet_mass_100);   

   t1->SetBranchAddress("jet_pt", jet_pt);   
   t1->SetBranchAddress("jet_eta", jet_eta);   
   t1->SetBranchAddress("jet_mass", jet_mass);   

   t1->SetBranchAddress("SJ_nAK4_50", SJ_nAK4_50);   
   t1->SetBranchAddress("SJ_nAK4_70", SJ_nAK4_70);   
   t1->SetBranchAddress("SJ_mass_50", SJ_mass_50);   
   t1->SetBranchAddress("SJ_mass_70", SJ_mass_70);   
   t1->SetBranchAddress("superJet_mass", superJet_mass);   
   t1->SetBranchAddress("SJ_AK4_50_mass", SJ_AK4_50_mass);   //mass of individual reclustered AK4 jets
   t1->SetBranchAddress("SJ_AK4_70_mass", SJ_AK4_70_mass);   

   t1->SetBranchAddress("totHT" , &totHT); 
   t1->SetBranchAddress("nbtaggedAK4" , &nbtaggedAK4); 
   t1->SetBranchAddress("nonHadFlag" , &nonHadFlag); 

   t1->SetBranchAddress("nAK4" , &nAK4); 
   t1->SetBranchAddress("topAK8_dr" , &topAK8_dr); 
   t1->SetBranchAddress("WSuuAK8_dr" , &WSuuAK8_dr ); 
   t1->SetBranchAddress("bSuuAK8_dr" , &bSuuAK8_dr ); 
   t1->SetBranchAddress("higgsAK8_dr" ,&higgsAK8_dr ); 
   t1->SetBranchAddress("topWAK8_dr" , &topWAK8_dr); 
   t1->SetBranchAddress("topbAK8_dr" , &topbAK8_dr); 
   t1->SetBranchAddress("topAK4_dr" ,&topAK4_dr ); 
   t1->SetBranchAddress("WSuuAK4_dr" ,&WSuuAK4_dr ); 
   t1->SetBranchAddress("bSuuAK4_dr" ,&bSuuAK4_dr ); 
   t1->SetBranchAddress("higgsAK4_dr" , &higgsAK4_dr); 
   t1->SetBranchAddress("topWAK4_dr" ,&topWAK4_dr ); 
   t1->SetBranchAddress("topbAK4_dr" ,&topbAK4_dr ); 
   t1->SetBranchAddress("AK4_mass" , AK4_mass); 
   t1->SetBranchAddress("chi_dr" , &chi_dr); 
   t1->SetBranchAddress("topPart_dr" ,&topPart_dr ); 
   t1->SetBranchAddress("higgs_dr" , &higgs_dr); 
   t1->SetBranchAddress("SuuW_dr" ,&SuuW_dr ); 
   t1->SetBranchAddress("HiggsTop_dr" , &HiggsTop_dr); 
   t1->SetBranchAddress("SuuWb_dr" ,&SuuWb_dr ); 
   t1->SetBranchAddress("correctlySortedChi1" ,&correctlySortedChi1 ); 
   t1->SetBranchAddress("correctlySortedChi2" ,&correctlySortedChi2 ); 
   t1->SetBranchAddress("nfatjet_pre" ,&nfatjet_pre ); 



   t1->SetBranchAddress("tot_mpp_AK4" , &tot_mpp_AK4); 
   t1->SetBranchAddress("SJ_mass_100", SJ_mass_100);   
   t1->SetBranchAddress("SJ_mass_125", SJ_mass_125);   
   t1->SetBranchAddress("SJ_mass_150", SJ_mass_150);   
   t1->SetBranchAddress("SJ_mass_200", SJ_mass_200);   
   t1->SetBranchAddress("SJ_mass_300", SJ_mass_300);   
   t1->SetBranchAddress("SJ_mass_400", SJ_mass_400);   
   t1->SetBranchAddress("SJ_mass_600", SJ_mass_600);
   t1->SetBranchAddress("SJ_mass_800", SJ_mass_800);
   t1->SetBranchAddress("SJ_mass_1000", SJ_mass_1000);

   t1->SetBranchAddress("SJ_nAK4_100", SJ_nAK4_100); 
   t1->SetBranchAddress("SJ_nAK4_125", SJ_nAK4_125);   
   t1->SetBranchAddress("SJ_nAK4_150", SJ_nAK4_150);   
   t1->SetBranchAddress("SJ_nAK4_200", SJ_nAK4_200);   
   t1->SetBranchAddress("SJ_nAK4_300", SJ_nAK4_300);   
   t1->SetBranchAddress("SJ_nAK4_400", SJ_nAK4_400);   
   t1->SetBranchAddress("SJ_nAK4_600", SJ_nAK4_600);   
   t1->SetBranchAddress("SJ_nAK4_800", SJ_nAK4_800);   
   t1->SetBranchAddress("SJ_nAK4_1000", SJ_nAK4_1000);   

   t1->SetBranchAddress("AK4_E", AK4_E);  
   t1->SetBranchAddress("genPartChiDaughterMPP_angle", genPartChiDaughterMPP_angle);  
   t1->SetBranchAddress("genSuperJetMass", genSuperJetMass);  

   t1->SetBranchAddress("genHiggsThrustCos", genHiggsThrustCos);  
   t1->SetBranchAddress("genTopWThrustCos", genTopWThrustCos);  
   t1->SetBranchAddress("genSuuWThrustCos", genSuuWThrustCos);  
   t1->SetBranchAddress("genTopbThrustCos", &genTopbThrustCos);  
   t1->SetBranchAddress("genSuubThrustCos", &genSuubThrustCos);  

   t1->SetBranchAddress("jet_thrust_cos", jet_thrust_cos);  

   t1->SetBranchAddress("_htWb", &_htWb);  
   t1->SetBranchAddress("_htZt", &_htZt);  
   t1->SetBranchAddress("_ZtWb", &_ZtWb);  
   t1->SetBranchAddress("_WbWb", &_WbWb);  
   t1->SetBranchAddress("_htht", &_htht);  
   t1->SetBranchAddress("_ZtZt", &_ZtZt);  
   
   TGraph *h_genSJ_mass_versus = new TGraph();
   h_genSJ_mass_versus->SetTitle("SuperJet 1 Mass vs SuperJet 2 Mass");
   h_genSJ_mass_versus->GetXaxis()->SetTitle("Gen SuperJet 1 Mass [GeV]");
   h_genSJ_mass_versus->GetYaxis()->SetTitle("Gen SuperJet 2 Mass [GeV]");
   h_genSJ_mass_versus->GetYaxis()->SetTitleOffset(1.5);

   TGraph *h_Mchichi_vs_Mchi_SJ1 = new TGraph();
   h_Mchichi_vs_Mchi_SJ1->SetName("h_Mchichi_vs_Mchi_SJ1");
   h_Mchichi_vs_Mchi_SJ1->SetTitle("M_{chi chi} vs SuperJet 1 M_{chi}");
   h_Mchichi_vs_Mchi_SJ1->GetYaxis()->SetTitle("M_{chi chi} [GeV]");
   h_Mchichi_vs_Mchi_SJ1->GetXaxis()->SetTitle("M_{chi} [GeV]");
   h_Mchichi_vs_Mchi_SJ1->GetYaxis()->SetTitleOffset(1.5);

   TGraph *h_Mchichi_vs_Mchi_SJ2 = new TGraph();
   h_Mchichi_vs_Mchi_SJ2->SetName("h_Mchichi_vs_Mchi_SJ2");
   h_Mchichi_vs_Mchi_SJ2->SetTitle("M_{chi chi} vs SuperJet 2 M_{chi}");
   h_Mchichi_vs_Mchi_SJ2->GetYaxis()->SetTitle("M_{chi chi} [GeV]");
   h_Mchichi_vs_Mchi_SJ2->GetXaxis()->SetTitle("M_{chi} [GeV]");
   h_Mchichi_vs_Mchi_SJ2->GetYaxis()->SetTitleOffset(1.5);

   TGraph *h_Mchichi_vs_Mchi_SJ1_diag = new TGraph();
   h_Mchichi_vs_Mchi_SJ1->SetName("h_Mchichi_vs_Mchi_SJ1_diag");
   h_Mchichi_vs_Mchi_SJ1->SetTitle("M_{chi chi} vs SuperJet 1 M_{chi} (Events Along SJ1/SJ2 Diagonal)");
   h_Mchichi_vs_Mchi_SJ1->GetYaxis()->SetTitle("M_{chi chi} [GeV]");
   h_Mchichi_vs_Mchi_SJ1->GetXaxis()->SetTitle("M_{chi} [GeV]");
   h_Mchichi_vs_Mchi_SJ1->GetYaxis()->SetTitleOffset(1.5);

   TGraph *h_SJ_mass_versus = new TGraph();
   h_SJ_mass_versus->GetXaxis()->SetLimits(0.0,6000.);
   h_SJ_mass_versus->GetYaxis()->SetLimits(0.0,6000.);
   h_SJ_mass_versus->SetName("h_SJ_mass_versus");
   h_SJ_mass_versus->SetTitle("SuperJet 1 Mass vs SuperJet 2 Mass");
   h_SJ_mass_versus->GetXaxis()->SetTitle("SuperJet 1 Mass [GeV]");
   h_SJ_mass_versus->GetYaxis()->SetTitle("SuperJet 2 Mass [GeV]");
   h_SJ_mass_versus->GetYaxis()->SetTitleOffset(1.5);

   TGraph *h_SJ_mass_50_versus = new TGraph();
   h_SJ_mass_50_versus->SetTitle("SuperJet 1 Mass vs SuperJet 2 Mass (MPP AK4 E>50 GeV)");
   h_SJ_mass_50_versus->GetXaxis()->SetTitle("SuperJet 1 Mass");
   h_SJ_mass_50_versus->GetYaxis()->SetTitle("SuperJet 2 Mass");
   h_SJ_mass_50_versus->GetYaxis()->SetTitleOffset(1.5);


   TGraph *h_SJ_mass_70_versus = new TGraph();
   h_SJ_mass_70_versus->SetTitle("SuperJet 1 Mass vs SuperJet 2 Mass (MPP AK4 E>70 GeV)");
   h_SJ_mass_70_versus->GetXaxis()->SetTitle("SuperJet 1 Mass");
   h_SJ_mass_70_versus->GetYaxis()->SetTitle("SuperJet 2 Mass");
   h_SJ_mass_70_versus->GetYaxis()->SetTitleOffset(1.5);





/////////////////////////looking into high masses/////////////////////////////////////////////
   TGraph *h_SJ_nAK4_150_highMass_vs = new TGraph();
   h_SJ_nAK4_150_highMass_vs->SetTitle("SuperJet 1 nAK4 vs SuperJet 2 nAK4 (MPP AK4 E>150 GeV), high superjet mass");
   h_SJ_nAK4_150_highMass_vs->GetXaxis()->SetTitle("SuperJet 1 nAK4");
   h_SJ_nAK4_150_highMass_vs->GetYaxis()->SetTitle("SuperJet 2 nAK4");
   h_SJ_nAK4_150_highMass_vs->GetYaxis()->SetTitleOffset(1.5);

   TGraph *h_superJet_mass_highMass_vs = new TGraph();
   h_superJet_mass_highMass_vs->SetTitle("SuperJet 1 mass vs SuperJet 2 mass, high superjet mass");
   h_superJet_mass_highMass_vs->GetXaxis()->SetTitle("SuperJet 1 mass");
   h_superJet_mass_highMass_vs->GetYaxis()->SetTitle("SuperJet 2 mass");
   h_superJet_mass_highMass_vs->GetYaxis()->SetTitleOffset(1.5);

   TGraph *h_genSuperJetMass_highMass_vs = new TGraph();
   h_genSuperJetMass_highMass_vs->SetTitle("Gen SuperJet 1 mass vs Gen SuperJet 2 mass (MPP AK4 E>150 GeV), high superjet mass");
   h_genSuperJetMass_highMass_vs->GetXaxis()->SetTitle("gen SuperJet 1 mass");
   h_genSuperJetMass_highMass_vs->GetYaxis()->SetTitle("gen SuperJet 2 mass");
   h_genSuperJetMass_highMass_vs->GetYaxis()->SetTitleOffset(1.5);

   TH1I* h_nfatjets_highMass = new TH1I("h_nfatjets_highMass","Number of AK8 Jets; # AK8 Jets (high superjet mass)",8,-0.5,7.5);
   TH1F* h_diSuperJet_mass_highMass = new TH1F("h_diSuperJet_mass_highMass","diSuperJet Mass (high superjet mass);Mass [GeV]; Events / 200 GeV",50,0.,10000.);
   TH1F* h_genSuubThrustCos_highMass = new TH1F("h_genSuubThrustCos_highMass","Cos of Angle between gen Suu b and Thrust Axis (high superjet mass);Cos",50,-1.,1.);
   TH1F* h_jet_thrust_cos_highMass = new TH1F("h_jet_thrust_cos_highMass","Cos of Angle between AK8 jets and Thrust Axis (high superjet mass);Cos",50,-1.,1.);


   TH2F* h_superJet_mass_highMass_TH2 = new TH2F("h_superJet_mass_highMass_TH2", "SuperJet 1 Mass vs SuperJet 2 Mass [GeV];", 50, 0., 2500., 50., 0., 2500.);
   TH2F* h_genSuperJetMass_highMass_TH2 = new TH2F("h_genSuperJetMass_highMass_TH2", "gen SuperJet 1 Mass vs gen SuperJet 2 Mass [GeV], high mass;", 50, 0., 2500., 50., 0., 2500.);
   TH2I* h_SJ_nAK4_150_highMass_TH2 = new TH2I("h_SJ_nAK4_150_highMass_TH2", "SuperJet 1 nAK4 (E>150 GeV) vs SuperJet 2 nAK4 (E>150 GeV), High mass ;", 10, -0.5, 9.5, 10, -0.5, 9.5);

   //h_SJ_mass_versus->SetMinimum(0.);
   //h_AK4_mass_70_vs->SetMaximum(1200.);
   //double SF_SuuChiChi = 0.338;
   double SF_SuuChiChi = 0.362;

   int nevents = 0,nDiagPoints = 0, nHighMassJets = 0;

   for (Int_t i=0;i<nentries;i++) 
   {  
      t1->GetEntry(i);


      if((totHT<3000.)||(nbtaggedAK4<2))continue;

      if((SJ_nAK4_200[0]<2)||(SJ_nAK4_200[1]<2) || (nfatjet_pre < 3)|| (SJ_mass_100[0]<500.) || (SJ_mass_100[1]<500.) ) continue;

      h_genPartChiDaughterMPP_angle->Fill(genPartChiDaughterMPP_angle[0],SF_SuuChiChi);
      h_genPartChiDaughterMPP_angle->Fill(genPartChiDaughterMPP_angle[1],SF_SuuChiChi);

      h_genSuperJetMass->Fill(genSuperJetMass[0],SF_SuuChiChi);
      h_genSuperJetMass->Fill(genSuperJetMass[1],SF_SuuChiChi);

      h_genHiggsThrustCos->Fill(genHiggsThrustCos[0],SF_SuuChiChi);
      h_genHiggsThrustCos->Fill(genHiggsThrustCos[1],SF_SuuChiChi);

      h_genTopWThrustCos->Fill(genTopWThrustCos[0],SF_SuuChiChi);
      h_genTopWThrustCos->Fill(genTopWThrustCos[1],SF_SuuChiChi);

      h_genSuuWThrustCos->Fill(genSuuWThrustCos[0],SF_SuuChiChi);
      h_genSuuWThrustCos->Fill(genSuuWThrustCos[1],SF_SuuChiChi);

      h_genTopbThrustCos->Fill(genTopbThrustCos,SF_SuuChiChi);
      h_genTopbThrustCos->Fill(genTopbThrustCos,SF_SuuChiChi);

      h_genSuubThrustCos->Fill(genSuubThrustCos,SF_SuuChiChi);
      h_genSuubThrustCos->Fill(genSuubThrustCos,SF_SuuChiChi);

      if((correctlySortedChi1 ==1)&&(correctlySortedChi2 == 1))nSuccessfulSorts++;
      ntotalevents++;
      h_genSJ_mass_versus->SetPoint(nevents,genSuperJetMass[0],genSuperJetMass[1]);
      h_genSuperJet1Mass->Fill(genSuperJetMass[0],SF_SuuChiChi);
      h_genSuperJet2Mass->Fill(genSuperJetMass[1],SF_SuuChiChi);
      for(int iii = 0;iii<tot_mpp_AK4;iii++)
      {
         h_AK4_E->Fill(AK4_E[tot_mpp_AK4],SF_SuuChiChi);
      }
      h_SJ_nAK4_100->Fill(SJ_nAK4_100[0]);
      h_SJ_nAK4_100->Fill(SJ_nAK4_100[1]);

      h_SJ_nAK4_125->Fill(SJ_nAK4_125[0]);
      h_SJ_nAK4_125->Fill(SJ_nAK4_125[1]);

      h_SJ_nAK4_150->Fill(SJ_nAK4_150[0]);
      h_SJ_nAK4_150->Fill(SJ_nAK4_150[1]);

      h_SJ_nAK4_200->Fill(SJ_nAK4_200[0]);
      h_SJ_nAK4_200->Fill(SJ_nAK4_200[1]);

      h_SJ_nAK4_300->Fill(SJ_nAK4_300[0]);
      h_SJ_nAK4_300->Fill(SJ_nAK4_300[1]);

      h_SJ_nAK4_400->Fill(SJ_nAK4_400[0]);
      h_SJ_nAK4_400->Fill(SJ_nAK4_400[1]);

      h_SJ_nAK4_600->Fill(SJ_nAK4_600[0]);
      h_SJ_nAK4_600->Fill(SJ_nAK4_600[1]);

      h_SJ_nAK4_800->Fill(SJ_nAK4_800[0]);
      h_SJ_nAK4_800->Fill(SJ_nAK4_800[1]);

      h_SJ_nAK4_1000->Fill(SJ_nAK4_1000[0]);
      h_SJ_nAK4_1000->Fill(SJ_nAK4_1000[1]);

      h_nfatjets->Fill(nfatjets);

      h_genPartChi1DaughterMPP_angle->Fill(genPartChiDaughterMPP_angle[0],SF_SuuChiChi);
      h_genPartChi2DaughterMPP_angle->Fill(genPartChiDaughterMPP_angle[1],SF_SuuChiChi);

      for(int iii=0;iii<nfatjets;iii++)
      {
         h_jet_thrust_cos->Fill(jet_thrust_cos[iii]);
      }

      h_diSuperJet_mass->Fill(diSuperJet_mass,SF_SuuChiChi);
      h_diSuperJet_mass_100->Fill(diSuperJet_mass_100,SF_SuuChiChi);
      
      if( (superJet_mass[0]/superJet_mass[1] > 0.8)&&(superJet_mass[0]/superJet_mass[1] < 1.25) )
      {
         h_diSuperJet_mass_diag->Fill(diSuperJet_mass,SF_SuuChiChi);
         h_Mchichi_vs_Mchi_SJ1_diag->SetPoint(nDiagPoints, superJet_mass[0], diSuperJet_mass);
         nDiagPoints++;
      }
      //else {std::cout << superJet_mass[0]/superJet_mass[1] <<std::endl;}
      //std::cout << "Number of diagonal values: " << nDiagPoints << std::endl;
      h_superJet_mass_TH2->Fill(superJet_mass[0],superJet_mass[1],SF_SuuChiChi);

      TRandom3 * ran = new TRandom3(0);
      double rannum = ran->Rndm();
      //if(rannum < SF_SuuChiChi) 
      //{
         h_SJ_mass_versus->SetPoint(nevents,superJet_mass[0],superJet_mass[1]);
         h_Mchichi_vs_Mchi_SJ1->SetPoint(nevents, superJet_mass[0], diSuperJet_mass);
         h_Mchichi_vs_Mchi_SJ2->SetPoint(nevents, superJet_mass[1], diSuperJet_mass);
      //}



      h_SJ_mass_50_versus->SetPoint(nevents,SJ_mass_50[0],SJ_mass_50[1]);
      h_SJ_mass_70_versus->SetPoint(nevents,SJ_mass_70[0],SJ_mass_70[1]);

      h_superJet_mass->Fill(superJet_mass[0],SF_SuuChiChi);
      h_superJet_mass->Fill(superJet_mass[1],SF_SuuChiChi);

      for(int iii=0; iii<tot_nAK4_50;iii++)
      {
        h_SJ_AK4_50_mass->Fill(SJ_AK4_50_mass[iii],SF_SuuChiChi);
      }
     for(int iii=0; iii<tot_nAK4_70;iii++)
      {
        h_SJ_AK4_70_mass->Fill(SJ_AK4_70_mass[iii],SF_SuuChiChi);
      }
      for(int iii = 0;iii<2;iii++)
      {
        h_SJ_mass_50->Fill(SJ_mass_50[iii],SF_SuuChiChi);
        h_SJ_mass_70->Fill(SJ_mass_70[iii],SF_SuuChiChi);
        h_SJ_mass_100->Fill(SJ_mass_100[iii],SF_SuuChiChi);

        h_SJ_mass_125->Fill(SJ_mass_125[iii],SF_SuuChiChi);
        h_SJ_mass_150->Fill(SJ_mass_150[iii],SF_SuuChiChi);
        h_SJ_mass_200->Fill(SJ_mass_200[iii],SF_SuuChiChi);
        h_SJ_mass_300->Fill(SJ_mass_300[iii],SF_SuuChiChi);
        h_SJ_mass_400->Fill(SJ_mass_400[iii],SF_SuuChiChi);

      }
      h_nAK4->Fill(nAK4);
      for(int iii = 0;iii<nAK4;iii++)
      {
         h_AK4_mass->Fill(AK4_mass[iii],SF_SuuChiChi);
      }
      h_topAK8_dr->Fill(topAK8_dr,SF_SuuChiChi);
      h_WSuuAK8_dr->Fill(WSuuAK8_dr,SF_SuuChiChi);
      h_bSuuAK8_dr->Fill(bSuuAK8_dr,SF_SuuChiChi);
      h_higgsAK8_dr->Fill(higgsAK8_dr,SF_SuuChiChi);
      h_topWAK8_dr->Fill(topWAK8_dr,SF_SuuChiChi);
      h_topbAK8_dr->Fill(topbAK8_dr,SF_SuuChiChi);

      h_topAK4_dr->Fill(topAK4_dr,SF_SuuChiChi);
      h_WSuuAK4_dr->Fill(WSuuAK4_dr,SF_SuuChiChi);
      h_bSuuAK4_dr->Fill(bSuuAK4_dr,SF_SuuChiChi);
      h_higgsAK4_dr->Fill(higgsAK4_dr,SF_SuuChiChi);
      h_topWAK4_dr->Fill(topWAK4_dr,SF_SuuChiChi);
      h_topbAK4_dr->Fill(topbAK4_dr,SF_SuuChiChi);

      h_chi_dr->Fill(chi_dr,SF_SuuChiChi);
      h_topPart_dr->Fill(topPart_dr,SF_SuuChiChi);
      h_higgs_dr->Fill(higgs_dr,SF_SuuChiChi);
      h_SuuW_dr->Fill(SuuW_dr,SF_SuuChiChi);
      h_HiggsTop_dr->Fill(HiggsTop_dr,SF_SuuChiChi);
      h_SuuWb_dr->Fill(SuuWb_dr,SF_SuuChiChi);
      nevents++;

      //cos of thrust for each jet
      for(int iii = 0; iii<nSuperJets;iii++)
      {
         if(superJet_mass[iii]>1200.)
         {
            //nfatjets, nAK4 > 150, disuperjet mass, gen superjet masses, gen Suu b thrust, 
            //std::cout << "nfatjets,diSuperJet mass/genSuubThrustCos  - " << nfatjets << "/" << diSuperJet_mass << "/" << genSuubThrustCos <<    "   SJ1: mass/nAK4(E>150 GeV)/genSuperJetMass   " << superJet_mass[0] << "/" << SJ_nAK4_150[0] << "/" << genSuperJetMass[0] << "   SJ2: mass/nAK4(E>150 GeV)/genSuperJetMass  " << superJet_mass[1] << "/" << SJ_nAK4_150[1] << "/" << genSuperJetMass[1] << std::endl;
            h_SJ_nAK4_150_highMass_vs->SetPoint(nHighMassJets,SJ_nAK4_150[0],SJ_nAK4_150[1]);
            h_genSuperJetMass_highMass_vs->SetPoint(nHighMassJets,genSuperJetMass[0],genSuperJetMass[1]);
            h_superJet_mass_highMass_vs->SetPoint(nHighMassJets, superJet_mass[0],superJet_mass[1]); 

            h_superJet_mass_highMass_TH2->Fill(superJet_mass[0],superJet_mass[1]);
            h_genSuperJetMass_highMass_TH2->Fill(genSuperJetMass[0],genSuperJetMass[1]);
            h_SJ_nAK4_150_highMass_TH2->Fill(SJ_nAK4_150[0],SJ_nAK4_150[1]);

            h_nfatjets_highMass->Fill(nfatjets);
            h_diSuperJet_mass_highMass->Fill(diSuperJet_mass);
            h_genSuubThrustCos_highMass->Fill(genSuubThrustCos);
            for(int jjj = 0; jjj<nfatjets; jjj++)
            {
               h_jet_thrust_cos_highMass->Fill(jet_thrust_cos[jjj]);
            }

            nHighMassJets++;
         }    
      }

    }

   //f->Close();

  // std::cout << "Out of " << nevents << " events, " << nantitagged << " are antitagged, and of the partners, " << ntagged50 << " have > 1 reclustered AK4 jets w/ E > 50 GeV " << std::endl;

   //std::cout << "Number of Successful Sorts / total events = " << nSuccessfulSorts << " / " << ntotalevents << std::endl;

   h_SJ_mass_versus->Write();
   h_SJ_nAK4_150_highMass_vs->Write();
   h_genSuperJetMass_highMass_vs->Write();
   h_superJet_mass_highMass_vs->Write(); 





   h_SJ_nAK4_150_highMass_vs->Draw("AP*");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_SJ_nAK4_150_highMass_vs.png");  
   h_genSuperJetMass_highMass_vs->Draw("AP*");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_genSuperJetMass_highMass_vs.png");  

   h_diSuperJet_mass->Draw("HIST");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_diSuperJet_mass.png"); 

   h_nfatjets_highMass->Draw("HIST");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_nfatjets_highMass.png"); 
   h_diSuperJet_mass_highMass->Draw("HIST");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_diSuperJet_mass_highMass.png"); 
   h_genSuubThrustCos_highMass->Draw("HIST");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_genSuubThrustCos_highMass.png"); 

   h_SJ_mass_versus->Draw("AP*");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_SJ_mass_versus.png");  

   h_SJ_mass_50_versus->Draw("AP*");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_SJ_mass_50_versus.png"); 

   h_SJ_mass_70_versus->Draw("AP*");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_SJ_mass_70_versus.png"); 

   h_superJet_mass->Draw("HIST");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_superJet_mass.png"); 

   
   
   

   h_superJet_mass_highMass_TH2->Draw("colz");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_superJet_mass_highMass_TH2.png"); 
   h_SJ_nAK4_150_highMass_TH2->Draw("colz");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_SJ_nAK4_150_highMass_TH2.png"); 
   h_genSuperJetMass_highMass_TH2->Draw("colz");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_genSuperJetMass_highMass_TH2.png"); 

   h_genPartChi1DaughterMPP_angle->Draw("HIST");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_genPartChi1DaughterMPP_angle.png"); 
   h_genPartChi2DaughterMPP_angle->Draw("HIST");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_genPartChi2DaughterMPP_angle.png"); 



   h_jet_thrust_cos_highMass->Draw("HIST");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_jet_thrust_cos_highMass.png"); 
   h_jet_thrust_cos->Draw("HIST");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_jet_thrust_cos.png"); 

   h_genSJ_mass_versus->Draw("HIST");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_genSJ_mass_versus.png"); 
   h_genSuperJet1Mass->Draw("HIST");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_genSuperJet1Mass.png"); 
   h_genSuperJet2Mass->Draw("HIST");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_genSuperJet2Mass.png"); 
   h_genSuperJetMass->Draw("HIST");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_genSuperJetMass.png"); 

   h_genPartChiDaughterMPP_angle->Draw("HIST");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_genPartChiDaughterMPP_angle.png"); 
   h_genHiggsThrustCos->Draw("HIST");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_genHiggsThrustCos.png"); 
   h_genTopWThrustCos->Draw("HIST");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_genTopWThrustCos.png"); 
   h_genSuuWThrustCos->Draw("HIST");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_genSuuWThrustCos.png"); 
   h_genTopbThrustCos->Draw("HIST");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_genTopbThrustCos.png"); 
   h_genSuubThrustCos->Draw("HIST");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_genSuubThrustCos.png"); 

   h_nfatjets->Draw("HIST");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_nfatjets.png"); 
   
   h_superJet_mass_TH2->Draw("colz");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_superJet_mass_TH2.png"); 

   h_Mchichi_vs_Mchi_SJ1->Write("HIST");
   h_Mchichi_vs_Mchi_SJ2->Write("HIST");

   h_diSuperJet_mass_diag->Draw("HIST");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_diSuperJet_mass_diag.png"); 

   

   //gPad->SetLogy();

   h_SJ_nAK4_100->Draw("HIST");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_SJ_nAK4_100.png"); 
   h_SJ_nAK4_125->Draw("HIST");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_SJ_nAK4_125.png");
   h_SJ_nAK4_150->Draw("HIST");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_SJ_nAK4_150.png");
   h_SJ_nAK4_200->Draw("HIST");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_SJ_nAK4_200.png");
   h_SJ_nAK4_300->Draw("HIST");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_SJ_nAK4_300.png");
   h_SJ_nAK4_400->Draw("HIST");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_SJ_nAK4_400.png");
   h_SJ_nAK4_600->Draw("HIST");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_SJ_nAK4_600.png");
   h_SJ_nAK4_800->Draw("HIST");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_SJ_nAK4_800.png");
   h_SJ_nAK4_1000->Draw("HIST");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_SJ_nAK4_1000.png");


   h_SJ_mass_50->Draw("HIST");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_SJ_mass_50.png");

   h_SJ_mass_70->Draw("HIST");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_SJ_mass_70.png");

   h_SJ_mass_100->Draw("HIST");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_SJ_mass_100.png"); 

   h_SJ_mass_125->Draw("HIST");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_SJ_mass_125.png"); 
   h_SJ_mass_150->Draw("HIST");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_SJ_mass_150.png"); 
   h_SJ_mass_200->Draw("HIST");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_SJ_mass_200.png"); 
   h_SJ_mass_300->Draw("HIST");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_SJ_mass_300.png"); 
   h_SJ_mass_400->Draw("HIST");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_SJ_mass_400.png"); 



   h_SJ_AK4_50_mass->Draw("HIST");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_SJ_AK4_50_mass.png"); 

   h_SJ_AK4_70_mass->Draw("HIST");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_SJ_AK4_70_mass.png");



   h_AK4_mass->Draw("HIST");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_AK4_mass.png");
   
   h_topAK8_dr->Draw("HIST");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_topAK8_dr.png"); 
   h_WSuuAK8_dr->Draw("HIST");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_WSuuAK8_dr.png"); 
   h_bSuuAK8_dr->Draw("HIST");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_bSuuAK8_dr.png"); 
   h_higgsAK8_dr->Draw("HIST");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_higgsAK8_dr.png"); 
   h_topWAK8_dr->Draw("HIST");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_topWAK8_dr.png"); 
   h_topbAK8_dr->Draw("HIST");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_topbAK8_dr.png"); 
   h_topAK4_dr->Draw("HIST");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_topAK4_dr.png"); 
   h_WSuuAK4_dr->Draw("HIST");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_WSuuAK4_dr.png"); 
   h_bSuuAK4_dr->Draw("HIST");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_bSuuAK4_dr.png"); 
   h_higgsAK4_dr->Draw("HIST");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_higgsAK4_dr.png"); 
   h_topWAK4_dr->Draw("HIST");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_topWAK4_dr.png"); 
   h_topbAK4_dr->Draw("HIST");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_topbAK4_dr.png"); 
   h_chi_dr->Draw("HIST");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_chi_dr.png"); 
   h_topPart_dr->Draw("HIST");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_topPart_dr.png"); 
   h_higgs_dr->Draw("HIST");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_higgs_dr.png"); 
   h_SuuW_dr->Draw("HIST");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_SuuW_dr.png"); 
   h_HiggsTop_dr->Draw("HIST");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_HiggsTop_dr.png"); 
   h_SuuWb_dr->Draw("HIST");
   c1->SaveAs("clustAlg_Suu4TeV_chi850GeV_MCTRUTH/h_SuuWb_dr.png"); 




   outFile.Write();
}


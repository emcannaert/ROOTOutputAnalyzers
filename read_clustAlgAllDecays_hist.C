#include <iostream>
#include <string>
#include "TLorentzVector.h"

using namespace std;
 
void doAnalysis(const char * inputFilename, const char * outputFilename, std::string folderName, double scaleFactor, double cut_totHT, int cut_nbtaggedAK4, int cut_SJ1_nAK4_200, int cut_SJ2_nAK4_200, int cut_nfatjets_pre, double cut_SJ1_mass_100, double cut_SJ2_mass_100)
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

   double nPassed_totHT = 0;
   double nPassed_btagged_AK4 = 0;
   double nPassed_nfatjets = 0;
   double nPassed_SJ_nAK4_200 = 0;
   double nPassed_SJ_mass_100 = 0;
   double totMET;

   double resonance_mass_comb;
   double daughter_mass_comb[100];
   //const char * _inputFilename = &inputFilename;
   //const char * _outputFilename = &outputFilename;

   TFile *f = new TFile(inputFilename);
   TFile outFile(outputFilename,"RECREATE");
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

   TH1F* h_AK4_mass = new TH1F("h_AK4_mass","Mass of AK4 Jets;Mass [GeV]",30,0.,600);


   TH1F* h_superJet_mass = new TH1F("h_superJet_mass","Mass of SuperJets; Mass [GeV];Events / 100 GeV",40,0.,4000.);
   TH1F* h_superJet_mass_50 = new TH1F("h_superJet_mass_50","Mass of SuperJets; Mass [GeV];Events / 100 GeV",40,0.,4000.);

   TH1F* h_lead_superJet_mass = new TH1F("h_lead_superJet_mass","Mass of SuperJets; Mass [GeV];Events / 100 GeV",40,0.,4000.);

   TH1F* h_diSuperJet_mass = new TH1F("h_diSuperJet_mass","diSuperJet Mass;Mass [GeV]; Events / 200 GeV",50,0.,10000.);


   TH1F* h_AK4_E = new TH1F("h_AK4_E","Energy of AK4 Jets;Energy [GeV]",100,0.,600.);
   TH1F* h_SJ_mass_100 = new TH1F("h_SJ_mass_100","Mass of SuperJets (E_{MPP}> 100 GeV);Mass [GeV]; Events / 80 GeV",100,0.,8000.);
   TH1F* h_SJ_mass_125 = new TH1F("h_SJ_mass_125","Mass of SuperJets (E_{MPP}> 125 GeV);Mass [GeV]; Events / 80 GeV",100,0.,8000.);
   TH1F* h_SJ_mass_150 = new TH1F("h_SJ_mass_150","Mass of SuperJets (E_{MPP}> 150 GeV);Mass [GeV]; Events / 80 GeV",100,0.,8000.);
   TH1F* h_SJ_mass_200 = new TH1F("h_SJ_mass_200","Mass of SuperJets (E_{MPP}> 200 GeV);Mass [GeV]; Events / 80 GeV",100,0.,8000.);
   TH1F* h_SJ_mass_300 = new TH1F("h_SJ_mass_300","Mass of SuperJets (E_{MPP}> 300 GeV);Mass [GeV]; Events / 80 GeV",100,0.,8000.);
   TH1F* h_SJ_mass_400 = new TH1F("h_SJ_mass_400","Mass of SuperJets (E_{MPP}> 400 GeV);Mass [GeV]; Events / 80 GeV",100,0.,8000.);

   TH1I* h_SJ_nAK4_100 = new TH1I("h_SJ_nAK4_100","Number of AK4 Jets (E_{MPP} > 100 GeV); # AK4 Jets",9,-0.5,8.5);
   TH1I* h_SJ_nAK4_125 = new TH1I("h_SJ_nAK4_125","Number of AK4 Jets (E_{MPP} > 125 GeV); # AK4 Jets",9,-0.5,8.5);
   TH1I* h_SJ_nAK4_150 = new TH1I("h_SJ_nAK4_150","Number of AK4 Jets (E_{MPP} > 150 GeV); # AK4 Jets",9,-0.5,8.5);
   TH1I* h_SJ_nAK4_200 = new TH1I("h_SJ_nAK4_200","Number of AK4 Jets (E_{MPP} > 200 GeV); # AK4 Jets",9,-0.5,8.5);
   TH1I* h_SJ_nAK4_300 = new TH1I("h_SJ_nAK4_300","Number of AK4 Jets (E_{MPP} > 300 GeV); # AK4 Jets",9,-0.5,8.5);
   TH1I* h_SJ_nAK4_400 = new TH1I("h_SJ_nAK4_400","Number of AK4 Jets (E_{MPP} > 400 GeV); # AK4 Jets",9,-0.5,8.5);
   TH1I* h_SJ_nAK4_600 = new TH1I("h_SJ_nAK4_600","Number of AK4 Jets (E_{MPP} > 600 GeV); # AK4 Jets",9,-0.5,8.5);
   TH1I* h_SJ_nAK4_800 = new TH1I("h_SJ_nAK4_800","Number of AK4 Jets (E_{MPP} > 800 GeV); # AK4 Jets",9,-0.5,8.5);
   TH1I* h_SJ_nAK4_1000 = new TH1I("h_SJ_nAK4_1000","Number of AK4 Jets (E_{MPP} > 1000 GeV); # AK4 Jets",9,-0.5,8.5);
   



   TH1F* h_diSuperJet_mass_100 = new TH1F("h_diSuperJet_mass_100","diSuperJet Mass (E_{SJ COM}> 100 GeV);Mass [GeV]; Events / 160 GeV",50,0.,8000.);
   TH1F* h_jet_thrust_cos = new TH1F("h_jet_thrust_cos","Cos of Angle between AK8 jets and Thrust Axis;Cos",50,-1.,1.);


   TH2F* h_superJet_mass_TH2 = new TH2F("h_superJet_mass_TH2", "SuperJet 1 Mass vs SuperJet 2 Mass;SuperJet 1 mass [GeV] / 70 GeV; SuperJet 2 mass [GeV] / 70 GeV", 30 , 400., 2500., 30., 400., 2500.);

   TH1I* h_SJ_nAK4_200_pre = new TH1I("h_SJ_nAK4_200_pre","Number of AK4 Jets (E_{MPP} > 200 GeV); # AK4 Jets",9,-0.5,8.5);

   TH1F* h_superJet_mass_pre = new TH1F("h_superJet_mass_pre","Mass of SuperJets; Mass [GeV];Events / 80 GeV",100,0.,8000.);
   TH1F* h_diSuperJet_mass_pre = new TH1F("h_diSuperJet_mass_pre","diSuperJet Mass;Mass [GeV]; Events / 200 GeV",50,0.,10000.);


   TH1F* h_superJet_mass_comb = new TH1F("h_superJet_mass_comb","Mass of SuperJets (full combinatorics); Mass [GeV];Events / 100 GeV",40,0.,4000.);
   TH1F* h_diSuperJet_mass_comb = new TH1F("h_diSuperJet_mass_comb","diSuperJet Mass (full combinatorics);Mass [GeV]; Events / 200 GeV",50,0.,10000.);

   TH1F* h_SJ_mass_50_pre = new TH1F("h_SJ_mass_50_pre","Mass of SuperJets (E_{SJ COM}> 50 GeV);Mass [GeV]; Events / 70 GeV",50,0.,3500.);
   TH1F* h_SJ_mass_100_pre = new TH1F("h_SJ_mass_100_pre","Mass of SuperJets (E_{SJ COM}> 100 GeV);Mass [GeV]; Events / 70 GeV",50,0.,3500.);



   TH1F* h_totHT = new TH1F("h_totHT","Total Event HT; HT [GeV]; Events / 80 GeV",100,0.,8000.);
   TH1I* h_nbtaggedAk4 = new TH1I("h_nbtaggedAk4","Number of b-tagged AK4 Jets; # b-tagged AK4 Jets",8,-0.5,7.5);
   TH1I* h_nfatjets_pre = new TH1I("h_nfatjets_pre","Number of AK8 Jets (M PUPPI > 45 GeV,pT> 500 GeV ); # AK8 Jets",8,-0.5,7.5);
   TH1F* h_totMET = new TH1F("h_totMET","Total (pf) MET in Event; MET [GeV];Events / 60 GeV",50,0.,3000.);
   TH1F* h_totMET_sig = new TH1F("h_totMET_sig","(pf) MET significance (MET/HT)",25,0.,2.5);



   TH1F* h_superJet_mass_avg = new TH1F("h_superJet_mass_avg","Average Mass of the Two SuperJets; Mass [GeV];Events / 70 GeV",50,0.,3500.);


   //TH1F* h_diSuperJet_mass_diag = new TH1F("h_diSuperJet_mass_diag","diSuperJet Mass (Along SJ mass diagonal);Mass [GeV]; Events / 200 GeV",50,0.,10000.);


/*
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

   TH1F* h_superJet_mass_htWb = new TH1F("h_superJet_mass_htWb","Mass of SuperJets htWb; Mass [GeV];Events / 80 GeV",100,0.,8000.);
   TH1F* h_superJet_mass_htZt = new TH1F("h_superJet_mass_htZt","Mass of SuperJets htZt; Mass [GeV];Events / 80 GeV",100,0.,8000.);
   TH1F* h_superJet_mass_ZtWb = new TH1F("h_superJet_mass_ZtWb","Mass of SuperJets ZtWb; Mass [GeV];Events / 80 GeV",100,0.,8000.);
   TH1F* h_superJet_mass_WbWb = new TH1F("h_superJet_mass_WbWb","Mass of SuperJets WbWb; Mass [GeV];Events / 80 GeV",100,0.,8000.);
   TH1F* h_superJet_mass_htht = new TH1F("h_superJet_mass_htht","Mass of SuperJets htht; Mass [GeV];Events / 80 GeV",100,0.,8000.);
   TH1F* h_superJet_mass_ZtZt = new TH1F("h_superJet_mass_ZtZt","Mass of SuperJets ZtZt; Mass [GeV];Events / 80 GeV",100,0.,8000.);

   TH1F* h_chi_dr = new TH1F("h_chi_dr","delta R between gen Chis ;delta R",50,0.,7.0);
   TH1F* h_topPart_dr = new TH1F("h_topPart_dr","delta R between gen Top Constituents ;delta R",50,0.,7.0);
   TH1F* h_higgs_dr = new TH1F("h_higgs_dr","delta R between gen Higgs Constituents ;delta R",50,0.,7.0);
   TH1F* h_SuuW_dr = new TH1F("h_SuuW_dr","delta R between gen Suu W Constituents ;delta R",50,0.,7.0);
   TH1F* h_HiggsTop_dr = new TH1F("h_HiggsTop_dr","delta R between gen Higgs and Top;delta R",50,0.,7.0);
   TH1F* h_SuuWb_dr = new TH1F("h_HiggsTop_dr","delta R between gen Suu W and b;delta R",50,0.,7.0);

   TH1F* h_diSuperJet_mass_htWb = new TH1F("h_diSuperJet_mass_htWb","diSuperJet Mass htWb;Mass [GeV]; Events / 200 GeV",50,0.,10000.);
   TH1F* h_diSuperJet_mass_htZt = new TH1F("h_diSuperJet_mass_htZt","diSuperJet Mass htZt;Mass [GeV]; Events / 200 GeV",50,0.,10000.);
   TH1F* h_diSuperJet_mass_ZtWb = new TH1F("h_diSuperJet_mass_ZtWb","diSuperJet Mass ZtWb;Mass [GeV]; Events / 200 GeV",50,0.,10000.);
   TH1F* h_diSuperJet_mass_WbWb = new TH1F("h_diSuperJet_mass WbWb","diSuperJet Mass WbWb;Mass [GeV]; Events / 200 GeV",50,0.,10000.);
   TH1F* h_diSuperJet_mass_htht = new TH1F("h_diSuperJet_mass_htht","diSuperJet Mass htht;Mass [GeV]; Events / 200 GeV",50,0.,10000.);
   TH1F* h_diSuperJet_mass_ZtZt = new TH1F("h_diSuperJet_mass_ZtZt","diSuperJet Mass ZtZt;Mass [GeV]; Events / 200 GeV",50,0.,10000.);

   TH1I* h_SJ_nAK4_150_htWb = new TH1I("h_SJ_nAK4_150_htWb","Number of AK4 Jets (E_{MPP} > 150 GeV) htWb; # AK4 Jets",9,-0.5,8.5);
   TH1I* h_SJ_nAK4_150_htZt = new TH1I("h_SJ_nAK4_150_htZt","Number of AK4 Jets (E_{MPP} > 150 GeV) htZt; # AK4 Jets",9,-0.5,8.5);
   TH1I* h_SJ_nAK4_150_ZtWb = new TH1I("h_SJ_nAK4_150_ZtWb","Number of AK4 Jets (E_{MPP} > 150 GeV) ZtWb; # AK4 Jets",9,-0.5,8.5);
   TH1I* h_SJ_nAK4_150_WbWb = new TH1I("h_SJ_nAK4_150_WbWb","Number of AK4 Jets (E_{MPP} > 150 GeV) WbWb; # AK4 Jets",9,-0.5,8.5);
   TH1I* h_SJ_nAK4_150_htht = new TH1I("h_SJ_nAK4_150_htht","Number of AK4 Jets (E_{MPP} > 150 GeV) htht; # AK4 Jets",9,-0.5,8.5);
   TH1I* h_SJ_nAK4_150_ZtZt = new TH1I("h_SJ_nAK4_150_ZtZt","Number of AK4 Jets (E_{MPP} > 150 GeV) ZtZt; # AK4 Jets",9,-0.5,8.5);


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

   TH1I* h_nfatjets_htWb = new TH1I("h_nfatjets_htWb","Number of AK8 Jets htWb; # AK8 Jets",8,-0.5,7.5);
   TH1I* h_nfatjets_htZt = new TH1I("h_nfatjets_htZt","Number of AK8 Jets htZt; # AK8 Jets",8,-0.5,7.5);
   TH1I* h_nfatjets_ZtWb = new TH1I("h_nfatjets_ZtWb","Number of AK8 Jets ZtWb; # AK8 Jets",8,-0.5,7.5);
   TH1I* h_nfatjets_WbWb = new TH1I("h_nfatjets_WbWb","Number of AK8 Jets WbWb; # AK8 Jets",8,-0.5,7.5);
   TH1I* h_nfatjets_htht = new TH1I("h_nfatjets_htht","Number of AK8 Jets htht; # AK8 Jets",8,-0.5,7.5);
   TH1I* h_nfatjets_ZtZt = new TH1I("h_nfatjets_ZtZt","Number of AK8 Jets ZtZt; # AK8 Jets",8,-0.5,7.5);
*/
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
   t1->SetBranchAddress("SJ_mass_50", SJ_mass_50);

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
   t1->SetBranchAddress("totMET", &totMET);  


   t1->SetBranchAddress("daughter_mass_comb", daughter_mass_comb);   
   t1->SetBranchAddress("resonance_mass_comb", &resonance_mass_comb);  
 
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
   h_SJ_mass_versus->SetName("h_SJ_mass_versus");
   h_SJ_mass_versus->SetTitle("SuperJet 1 Mass vs SuperJet 2 Mass (Signal)");
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






   int nevents = 0,nDiagPoints = 0, nHighMassJets = 0;
   int nevents_pre = 0;
   for (Int_t i=0;i<nentries;i++) 
   {  
      t1->GetEntry(i);

      h_nfatjets->Fill(nfatjets);
      h_totHT->Fill(totHT);
      h_nfatjets_pre->Fill(nfatjet_pre);
      h_nbtaggedAk4->Fill(nbtaggedAK4);
      h_totMET->Fill(totMET);
      h_totMET_sig->Fill(totMET/totHT);
      if((totHT>cut_totHT)&&(nbtaggedAK4>=cut_nbtaggedAK4)&& (nfatjet_pre >=cut_nfatjets_pre))
      {

         if(    (superJet_mass[0]>300.)&&(superJet_mass[1]>300.) ) h_superJet_mass_TH2->Fill(superJet_mass[0],superJet_mass[1]);
         h_superJet_mass_TH2->Fill(superJet_mass[0],superJet_mass[1]);

         if( (superJet_mass[0]/superJet_mass[1] < 1.40)&&(superJet_mass[0]/superJet_mass[1] > 0.6)     )
         {
            h_SJ_nAK4_200_pre->Fill(SJ_nAK4_200[0]);
            h_SJ_nAK4_200_pre->Fill(SJ_nAK4_200[1]);

            h_superJet_mass_pre->Fill(superJet_mass[0],scaleFactor);
            h_superJet_mass_pre->Fill(superJet_mass[1],scaleFactor);
            h_diSuperJet_mass_pre->Fill(diSuperJet_mass,scaleFactor);


            h_diSuperJet_mass_100->Fill(diSuperJet_mass_100,scaleFactor);

         
            h_superJet_mass_comb->Fill(daughter_mass_comb[0],scaleFactor);
            h_superJet_mass_comb->Fill(daughter_mass_comb[1],scaleFactor);
            h_diSuperJet_mass_comb->Fill(resonance_mass_comb,scaleFactor);


            h_SJ_mass_50_pre->Fill(SJ_mass_50[0],scaleFactor);
            h_SJ_mass_50_pre->Fill(SJ_mass_50[1],scaleFactor);

            h_SJ_mass_100_pre->Fill(SJ_mass_100[0],scaleFactor);
            h_SJ_mass_100_pre->Fill(SJ_mass_100[1],scaleFactor);

         }
      }
      nevents_pre++;

      if( (totHT>=cut_totHT) )
      {
         nPassed_totHT+= scaleFactor;
         if (nbtaggedAK4>=cut_nbtaggedAK4)
         {
            nPassed_btagged_AK4+=scaleFactor;
            if( nfatjet_pre >= cut_nfatjets_pre   )
            {
               nPassed_nfatjets+=scaleFactor;
               if( (SJ_nAK4_300[0]>=cut_SJ1_nAK4_200)&&(SJ_nAK4_300[1]>=cut_SJ2_nAK4_200) && (SJ_mass_100[0]>=cut_SJ1_mass_100) && (SJ_mass_100[1]>=cut_SJ2_mass_100)  )nPassed_SJ_nAK4_200+=scaleFactor;
            }
         }
      }


      if((totHT >cut_totHT)&&(nbtaggedAK4>=cut_nbtaggedAK4)&& (nfatjet_pre >= cut_nfatjets_pre) && (SJ_nAK4_200[0]>=cut_SJ1_nAK4_200)&&(SJ_nAK4_200[1]>=cut_SJ2_nAK4_200))
      {
         h_SJ_mass_100_pre->Fill(SJ_mass_100[0],scaleFactor);
         h_SJ_mass_100_pre->Fill(SJ_mass_100[1],scaleFactor);

      }

      if((totHT<cut_totHT)||(nbtaggedAK4<cut_nbtaggedAK4))continue;

      if((SJ_nAK4_150[0]<cut_SJ1_nAK4_200)||(SJ_nAK4_150[1]<cut_SJ2_nAK4_200) || (nfatjet_pre < cut_nfatjets_pre)|| (SJ_mass_100[0]<cut_SJ1_mass_100) || (SJ_mass_100[1]<cut_SJ2_mass_100) ) continue;      
      if( (superJet_mass[0]/superJet_mass[1] > 1.20)||(superJet_mass[0]/superJet_mass[1] < 0.8)     )continue;

      ntotalevents++;
      for(int iii = 0;iii<tot_mpp_AK4;iii++)
      {
         h_AK4_E->Fill(AK4_E[tot_mpp_AK4],scaleFactor);
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



      h_lead_superJet_mass->Fill(superJet_mass[0],scaleFactor);
     /*
      if(_htWb)
      {
         h_nfatjets_htWb->Fill(nfatjets);
         h_superJet_mass_htWb->Fill(superJet_mass[0]);
         h_superJet_mass_htWb->Fill(superJet_mass[1]);
         h_diSuperJet_mass_htWb->Fill(diSuperJet_mass);
         h_SJ_nAK4_150_htWb->Fill(SJ_nAK4_150[0]);
         h_SJ_nAK4_150_htWb->Fill(SJ_nAK4_150[1]);

      }
      else if(_htZt)
      {
         h_nfatjets_htZt->Fill(nfatjets);
         h_superJet_mass_htZt->Fill(superJet_mass[0]);
         h_superJet_mass_htZt->Fill(superJet_mass[1]);
         h_diSuperJet_mass_htZt->Fill(diSuperJet_mass);
         h_SJ_nAK4_150_htZt->Fill(SJ_nAK4_150[0]);
         h_SJ_nAK4_150_htZt->Fill(SJ_nAK4_150[1]);

      }

      else if(_ZtWb)
      {
         h_nfatjets_ZtWb->Fill(nfatjets);
         h_superJet_mass_ZtWb->Fill(superJet_mass[0]);
         h_superJet_mass_ZtWb->Fill(superJet_mass[1]);
         h_diSuperJet_mass_ZtWb->Fill(diSuperJet_mass);
         h_SJ_nAK4_150_ZtWb->Fill(SJ_nAK4_150[0]);
         h_SJ_nAK4_150_ZtWb->Fill(SJ_nAK4_150[1]);

      }
      else if(_WbWb)
      {
         h_nfatjets_WbWb->Fill(nfatjets);
         h_superJet_mass_WbWb->Fill(superJet_mass[0]);
         h_superJet_mass_WbWb->Fill(superJet_mass[1]);
         h_diSuperJet_mass_WbWb->Fill(diSuperJet_mass);
         h_SJ_nAK4_150_WbWb->Fill(SJ_nAK4_150[0]);
         h_SJ_nAK4_150_WbWb->Fill(SJ_nAK4_150[1]);

      }
      else if(_htht)
      {
         h_nfatjets_htht->Fill(nfatjets);
         h_superJet_mass_htht->Fill(superJet_mass[0]);
         h_superJet_mass_htht->Fill(superJet_mass[1]);
         h_diSuperJet_mass_htht->Fill(diSuperJet_mass);
         h_SJ_nAK4_150_htht->Fill(SJ_nAK4_150[0]);
         h_SJ_nAK4_150_htht->Fill(SJ_nAK4_150[1]);

      }
      else if(_ZtZt)
      {
         h_nfatjets_ZtZt->Fill(nfatjets);
         h_superJet_mass_ZtZt->Fill(superJet_mass[0]);
         h_superJet_mass_ZtZt->Fill(superJet_mass[1]);
         h_diSuperJet_mass_ZtZt->Fill(diSuperJet_mass);
         h_SJ_nAK4_150_ZtZt->Fill(SJ_nAK4_150[0]);
         h_SJ_nAK4_150_ZtZt->Fill(SJ_nAK4_150[1]);

      }
      */
      for(int iii=0;iii<nfatjets;iii++)
      {
         h_jet_thrust_cos->Fill(jet_thrust_cos[iii]);
      }

      h_diSuperJet_mass->Fill(diSuperJet_mass,scaleFactor);
      h_diSuperJet_mass_100->Fill(diSuperJet_mass_100,scaleFactor);
      
      h_superJet_mass_50->Fill(SJ_mass_50[0],scaleFactor);
      h_superJet_mass_50->Fill(SJ_mass_50[1],scaleFactor);

      h_superJet_mass->Fill(superJet_mass[0],scaleFactor);
      h_superJet_mass->Fill(superJet_mass[1],scaleFactor);


      TRandom3 * ran = new TRandom3(0);
      double rannum = ran->Rndm();
      //if(rannum < scaleFactor) 
      //{
         h_Mchichi_vs_Mchi_SJ1->SetPoint(nevents, superJet_mass[0], diSuperJet_mass);
         h_Mchichi_vs_Mchi_SJ2->SetPoint(nevents, superJet_mass[1], diSuperJet_mass);
      //}



      h_SJ_mass_50_versus->SetPoint(nevents,SJ_mass_50[0],SJ_mass_50[1]);
      h_SJ_mass_70_versus->SetPoint(nevents,SJ_mass_70[0],SJ_mass_70[1]);


      for(int iii=0; iii<tot_nAK4_50;iii++)
      {
        h_SJ_AK4_50_mass->Fill(SJ_AK4_50_mass[iii],scaleFactor);
      }
     for(int iii=0; iii<tot_nAK4_70;iii++)
      {
        h_SJ_AK4_70_mass->Fill(SJ_AK4_70_mass[iii],scaleFactor);
      }
      for(int iii = 0;iii<2;iii++)
      {
        h_SJ_mass_50->Fill(SJ_mass_50[iii],scaleFactor);
        h_SJ_mass_70->Fill(SJ_mass_70[iii],scaleFactor);
        h_SJ_mass_100->Fill(SJ_mass_100[iii],scaleFactor);

        h_SJ_mass_125->Fill(SJ_mass_125[iii],scaleFactor);
        h_SJ_mass_150->Fill(SJ_mass_150[iii],scaleFactor);
        h_SJ_mass_200->Fill(SJ_mass_200[iii],scaleFactor);
        h_SJ_mass_300->Fill(SJ_mass_300[iii],scaleFactor);
        h_SJ_mass_400->Fill(SJ_mass_400[iii],scaleFactor);

      }
      h_nAK4->Fill(nAK4);
      for(int iii = 0;iii<nAK4;iii++)
      {
         h_AK4_mass->Fill(AK4_mass[iii],scaleFactor);
      }

      h_superJet_mass_avg->Fill((superJet_mass[0]+superJet_mass[1])/2.);
      nevents++;

    }
   std::cout << " lepton veto & trigger = 5478, HT = " << nPassed_totHT << " , btagged AK8 = " << nPassed_btagged_AK4 << " , nfatjets = " << nPassed_nfatjets << " , jet substructure = " << nPassed_SJ_nAK4_200 << std::endl;

   //f->Close();

  // std::cout << "Out of " << nevents << " events, " << nantitagged << " are antitagged, and of the partners, " << ntagged50 << " have > 1 reclustered AK4 jets w/ E > 50 GeV " << std::endl;

   //std::cout << "Number of Successful Sorts / total events = " << nSuccessfulSorts << " / " << ntotalevents << std::endl;


   gStyle->SetOptStat(0);

   TAxis *axis = h_SJ_mass_versus->GetXaxis();
   axis->SetLimits(0.,2000.);                 // along X
   h_SJ_mass_versus->GetHistogram()->SetMaximum(2000.);   // along          
   h_SJ_mass_versus->GetHistogram()->SetMinimum(0.);
   h_SJ_mass_versus->Draw("AP*");
   c1->SaveAs(   (folderName+"/h_SJ_mass_versus.png").c_str()    );   

   //h_SJ_nAK4_150_highMass_vs->Write();
   //h_genSuperJetMass_highMass_vs->Write();
   //h_superJet_mass_highMass_vs->Write(); 


   h_nfatjets->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_nfatjets.png").c_str()    ); 
   h_totHT->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_totHT.png").c_str()    ); 
   h_nfatjets_pre->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_nfatjets_pre.png").c_str()    ); 
   h_nbtaggedAk4->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_nbtaggedAk4.png").c_str()    ); 

   //h_SJ_nAK4_150_highMass_vs->Draw("AP*");
   //c1->SaveAs(   (folderName+"/h_SJ_nAK4_150_highMass_vs.png").c_str()    );  
   //h_genSuperJetMass_highMass_vs->Draw("AP*");
   //c1->SaveAs(   (folderName+"/h_genSuperJetMass_highMass_vs.png").c_str()    );  

   h_diSuperJet_mass->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_diSuperJet_mass.png").c_str()    ); 

   //h_nfatjets_highMass->Draw("HIST");
   //c1->SaveAs(   (folderName+"/h_nfatjets_highMass.png").c_str()    ); 
   //h_diSuperJet_mass_highMass->Draw("HIST");
  // c1->SaveAs(   (folderName+"/h_diSuperJet_mass_highMass.png").c_str()    ); 
   //h_genSuubThrustCos_highMass->Draw("HIST");
  // c1->SaveAs(   (folderName+"/h_genSuubThrustCos_highMass.png").c_str()    ); 




   h_SJ_mass_versus->Draw("AP*");
   c1->SaveAs(   (folderName+"/h_SJ_mass_versus.png").c_str()    );  

   h_SJ_mass_50_versus->Draw("AP*");
   c1->SaveAs(   (folderName+"/h_SJ_mass_50_versus.png").c_str()    ); 

   h_SJ_mass_70_versus->Draw("AP*");
   c1->SaveAs(   (folderName+"/h_SJ_mass_70_versus.png").c_str()    ); 

   h_superJet_mass->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_superJet_mass.png").c_str()    ); 

   
   
   
/*
   h_superJet_mass_highMass_TH2->Draw("colz");
   c1->SaveAs(   (folderName+"/h_superJet_mass_highMass_TH2.png").c_str()    ); 
   h_SJ_nAK4_150_highMass_TH2->Draw("colz");
   c1->SaveAs(   (folderName+"/h_SJ_nAK4_150_highMass_TH2.png").c_str()    ); 
   h_genSuperJetMass_highMass_TH2->Draw("colz");
   c1->SaveAs(   (folderName+"/h_genSuperJetMass_highMass_TH2.png").c_str()    ); 

   h_genPartChi1DaughterMPP_angle->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_genPartChi1DaughterMPP_angle.png").c_str()    ); 
   h_genPartChi2DaughterMPP_angle->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_genPartChi2DaughterMPP_angle.png").c_str()    ); 
*/
   h_jet_thrust_cos->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_jet_thrust_cos.png").c_str()    ); 

/*
   h_genSJ_mass_versus->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_genSJ_mass_versus.png").c_str()    ); 
   h_genSuperJet1Mass->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_genSuperJet1Mass.png").c_str()    ); 
   h_genSuperJet2Mass->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_genSuperJet2Mass.png").c_str()    ); 
   h_genSuperJetMass->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_genSuperJetMass.png").c_str()    ); 

   h_genPartChiDaughterMPP_angle->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_genPartChiDaughterMPP_angle.png").c_str()    ); 
   h_genHiggsThrustCos->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_genHiggsThrustCos.png").c_str()    ); 
   h_genTopWThrustCos->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_genTopWThrustCos.png").c_str()    ); 
   h_genSuuWThrustCos->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_genSuuWThrustCos.png").c_str()    ); 
   h_genTopbThrustCos->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_genTopbThrustCos.png").c_str()    ); 
   h_genSuubThrustCos->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_genSuubThrustCos.png").c_str()    ); 
*/

   h_superJet_mass_TH2->Draw("colz");
   c1->SaveAs(   (folderName+"/h_superJet_mass_TH2.png").c_str()    ); 

   h_Mchichi_vs_Mchi_SJ1->Write("HIST");
   h_Mchichi_vs_Mchi_SJ2->Write("HIST");

   //h_diSuperJet_mass_diag->Draw("HIST");
   //c1->SaveAs(   (folderName+"/h_diSuperJet_mass_diag.png").c_str()    ); 

   

   //gPad->SetLogy();

   h_SJ_nAK4_100->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_SJ_nAK4_100.png").c_str()    ); 
   h_SJ_nAK4_125->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_SJ_nAK4_125.png").c_str()    );
   h_SJ_nAK4_150->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_SJ_nAK4_150.png").c_str()    );
   h_SJ_nAK4_200->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_SJ_nAK4_200.png").c_str()    );
   h_SJ_nAK4_300->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_SJ_nAK4_300.png").c_str()    );
   h_SJ_nAK4_400->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_SJ_nAK4_400.png").c_str()    );
   h_SJ_nAK4_600->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_SJ_nAK4_600.png").c_str()    );
   h_SJ_nAK4_800->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_SJ_nAK4_800.png").c_str()    );
   h_SJ_nAK4_1000->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_SJ_nAK4_1000.png").c_str()    );


   h_SJ_mass_50->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_SJ_mass_50.png").c_str()    );

   h_SJ_mass_70->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_SJ_mass_70.png").c_str()    );

   h_SJ_mass_100->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_SJ_mass_100.png").c_str()    ); 

   h_SJ_mass_125->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_SJ_mass_125.png").c_str()    ); 
   h_SJ_mass_150->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_SJ_mass_150.png").c_str()    ); 
   h_SJ_mass_200->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_SJ_mass_200.png").c_str()    ); 
   h_SJ_mass_300->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_SJ_mass_300.png").c_str()    ); 
   h_SJ_mass_400->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_SJ_mass_400.png").c_str()    ); 



   h_SJ_AK4_50_mass->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_SJ_AK4_50_mass.png").c_str()    ); 

   h_SJ_AK4_70_mass->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_SJ_AK4_70_mass.png").c_str()    );



   h_AK4_mass->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_AK4_mass.png").c_str()    );

   gPad->SetLogy();
   h_SJ_mass_100_pre->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_SJ_mass_100_pre.png").c_str()    );

   h_superJet_mass_comb->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_superJet_mass_comb.png").c_str()    );
   h_diSuperJet_mass_comb->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_diSuperJet_mass_comb.png").c_str()    );

   h_lead_superJet_mass->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_lead_superJet_mass.png").c_str()    );
   
   h_superJet_mass_avg->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_superJet_mass_avg.png").c_str()    ); 

   h_superJet_mass_50->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_superJet_mass_50.png").c_str()    ); 

   h_SJ_nAK4_200_pre->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_SJ_nAK4_200_pre.png").c_str()    ); 


/*
   h_topAK8_dr->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_topAK8_dr.png").c_str()    ); 
   h_WSuuAK8_dr->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_WSuuAK8_dr.png").c_str()    ); 
   h_bSuuAK8_dr->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_bSuuAK8_dr.png").c_str()    ); 
   h_higgsAK8_dr->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_higgsAK8_dr.png").c_str()    ); 
   h_topWAK8_dr->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_topWAK8_dr.png").c_str()    ); 
   h_topbAK8_dr->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_topbAK8_dr.png").c_str()    ); 
   h_topAK4_dr->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_topAK4_dr.png").c_str()    ); 
   h_WSuuAK4_dr->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_WSuuAK4_dr.png").c_str()    ); 
   h_bSuuAK4_dr->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_bSuuAK4_dr.png").c_str()    ); 
   h_higgsAK4_dr->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_higgsAK4_dr.png").c_str()     ); 
   h_topWAK4_dr->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_topWAK4_dr.png").c_str()    ); 
   h_topbAK4_dr->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_topbAK4_dr.png").c_str()    ); 
   h_chi_dr->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_chi_dr.png").c_str()    ); 
   h_topPart_dr->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_topPart_dr.png").c_str()    ); 
   h_higgs_dr->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_higgs_dr.png").c_str()    ); 
   h_SuuW_dr->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_SuuW_dr.png").c_str()    ); 
   h_HiggsTop_dr->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_HiggsTop_dr.png").c_str()    ); 
   h_SuuWb_dr->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_SuuWb_dr.png").c_str()    ); 


   h_nfatjets_ZtZt->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_nfatjets_ZtZt.png").c_str()    ); 
   h_superJet_mass_ZtZt->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_superJet_mass_ZtZt.png").c_str()    ); 
   h_superJet_mass_ZtZt->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_superJet_mass_ZtZt.png").c_str()    ); 
   h_diSuperJet_mass_ZtZt->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_diSuperJet_mass_ZtZt.png").c_str()    ); 
   h_SJ_nAK4_150_ZtZt->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_SJ_nAK4_150_ZtZt.png").c_str()    ); 
   h_SJ_nAK4_150_ZtZt->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_SJ_nAK4_150_ZtZt.png").c_str()    ); 


   h_nfatjets_htht->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_nfatjets_htht.png").c_str()    ); 
   h_superJet_mass_htht->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_superJet_mass_htht.png").c_str()    ); 
   h_superJet_mass_htht->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_superJet_mass_htht.png").c_str()    ); 
   h_diSuperJet_mass_htht->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_diSuperJet_mass_htht.png").c_str()    ); 
   h_SJ_nAK4_150_htht->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_SJ_nAK4_150_htht.png").c_str()    ); 
   h_SJ_nAK4_150_htht->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_SJ_nAK4_150_htht.png").c_str()    ); 

   h_nfatjets_WbWb->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_nfatjets_WbWb.png").c_str()    ); 
   h_superJet_mass_WbWb->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_superJet_mass_WbWb.png").c_str()    ); 
   h_superJet_mass_WbWb->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_superJet_mass_WbWb.png").c_str()    ); 
   h_diSuperJet_mass_WbWb->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_diSuperJet_mass_WbWb.png").c_str()    ); 
   h_SJ_nAK4_150_WbWb->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_SJ_nAK4_150_WbWb.png").c_str()    ); 
   h_SJ_nAK4_150_WbWb->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_SJ_nAK4_150_WbWb.png").c_str()    ); 

   h_nfatjets_ZtWb->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_nfatjets_ZtWb.png").c_str()    ); 
   h_superJet_mass_ZtWb->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_superJet_mass_ZtWb.png").c_str()    ); 
   h_superJet_mass_ZtWb->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_superJet_mass_ZtWb.png").c_str()    ); 
   h_diSuperJet_mass_ZtWb->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_diSuperJet_mass_ZtWb.png").c_str()    ); 
   h_SJ_nAK4_150_ZtWb->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_SJ_nAK4_150_ZtWb.png").c_str()    ); 
   h_SJ_nAK4_150_ZtWb->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_SJ_nAK4_150_ZtWb.png").c_str()    ); 

   h_nfatjets_htZt->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_nfatjets_htZt.png").c_str()    ); 
   h_superJet_mass_htZt->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_superJet_mass_htZt.png").c_str()    ); 
   h_superJet_mass_htZt->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_superJet_mass_htZt.png").c_str()    ); 
   h_diSuperJet_mass_htZt->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_diSuperJet_mass_htZt.png").c_str()    ); 
   h_SJ_nAK4_150_htZt->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_SJ_nAK4_150_htZt.png").c_str()    ); 
   h_SJ_nAK4_150_htZt->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_SJ_nAK4_150_htZt.png").c_str()    ); 

   h_nfatjets_htWb->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_nfatjets_htWb.png").c_str()    ); 
   h_superJet_mass_htWb->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_superJet_mass_htWb.png").c_str()    ); 
   h_superJet_mass_htWb->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_superJet_mass_htWb.png").c_str()    ); 
   h_diSuperJet_mass_htWb->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_diSuperJet_mass_htWb.png").c_str()    ); 
   h_SJ_nAK4_150_htWb->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_SJ_nAK4_150_htWb.png").c_str()    ); 
   h_SJ_nAK4_150_htWb->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_SJ_nAK4_150_htWb.png").c_str()    ); 
   
   */
   outFile.Write();
}
void read_clustAlgAllDecays_hist()
{  
   const char *inputFilenames[]  = {"clusteringInputs/ClusteringAlgorithm_Suu4TeV_chi500GeV_ALLDECAYS_output.root",
"clusteringInputs/ClusteringAlgorithm_Suu4TeV_chi850GeV_ALLDECAYS_output.root",
"clusteringInputs/ClusteringAlgorithm_Suu4TeV_chi1TeV_ALLDECAYS_output.root",
"clusteringInputs/ClusteringAlgorithm_Suu4TeV_chi1p5TeV_ALLDECAYS_output.root",
"clusteringInputs/ClusteringAlgorithm_Suu5TeV_chi1TeV_ALLDECAYS_output.root",
"clusteringInputs/ClusteringAlgorithm_Suu5TeV_chi1p5TeV_ALLDECAYS_output.root",
"clusteringInputs/ClusteringAlgorithm_Suu5TeV_chi2TeV_ALLDECAYS_output.root",
"clusteringInputs/ClusteringAlgorithm_Suu6TeV_chi1TeV_ALLDECAYS_output.root",
"clusteringInputs/ClusteringAlgorithm_Suu6TeV_chi1p5TeV_ALLDECAYS_output.root",
"clusteringInputs/ClusteringAlgorithm_Suu6TeV_chi2TeV_ALLDECAYS_output.root",
"clusteringInputs/ClusteringAlgorithm_Suu7TeV_chi1TeV_ALLDECAYS_output.root",
"clusteringInputs/ClusteringAlgorithm_Suu7TeV_chi2TeV_ALLDECAYS_output.root",
"clusteringInputs/ClusteringAlgorithm_Suu7TeV_chi3TeV_ALLDECAYS_output.root",
"clusteringInputs/ClusteringAlgorithm_Suu8TeV_chi1TeV_ALLDECAYS_output.root",
"clusteringInputs/ClusteringAlgorithm_Suu8TeV_chi2TeV_ALLDECAYS_output.root",
"clusteringInputs/ClusteringAlgorithm_Suu8TeV_chi3TeV_ALLDECAYS_output.root",};
   const char * outputFilenames[] = {"clusteringProcessed/ClusteringAlgorithm_Suu4TeV_chi500GeV_ALLDECAY_processed.root",
 "clusteringProcessed/ClusteringAlgorithm_Suu4TeV_chi850GeV_ALLDECAY_processed.root",
 "clusteringProcessed/ClusteringAlgorithm_Suu4TeV_chi1TeV_ALLDECAY_processed.root",  
 "clusteringProcessed/ClusteringAlgorithm_Suu4TeV_chi1p5TeV_ALLDECAY_processed.root",
 "clusteringProcessed/ClusteringAlgorithm_Suu5TeV_chi1TeV_ALLDECAY_processed.root",
 "clusteringProcessed/ClusteringAlgorithm_Suu5TeV_chi1p5TeV_ALLDECAY_processed.root",
 "clusteringProcessed/ClusteringAlgorithm_Suu5TeV_chi2TeV_ALLDECAY_processed.root",
 "clusteringProcessed/ClusteringAlgorithm_Suu6TeV_chi1TeV_ALLDECAY_processed.root",
 "clusteringProcessed/ClusteringAlgorithm_Suu6TeV_chi1p5TeV_ALLDECAY_processed.root",
 "clusteringProcessed/ClusteringAlgorithm_Suu6TeV_chi2TeV_ALLDECAY_processed.root",
 "clusteringProcessed/ClusteringAlgorithm_Suu7TeV_chi1TeV_ALLDECAY_processed.root",
 "clusteringProcessed/ClusteringAlgorithm_Suu7TeV_chi2TeV_ALLDECAY_processed.root",
 "clusteringProcessed/ClusteringAlgorithm_Suu7TeV_chi3TeV_ALLDECAY_processed.root",
 "clusteringProcessed/ClusteringAlgorithm_Suu8TeV_chi1TeV_ALLDECAY_processed.root",
 "clusteringProcessed/ClusteringAlgorithm_Suu8TeV_chi2TeV_ALLDECAY_processed.root",
 "clusteringProcessed/ClusteringAlgorithm_Suu8TeV_chi3TeV_ALLDECAY_processed.root"};
   std::string folderNames[]     = {"clustAlgPlots/Suu4TeV_chi500GeV",
   "clustAlgPlots/Suu4TeV_chi850GeV",
   "clustAlgPlots/Suu4TeV_chi1TeV",
   "clustAlgPlots/Suu4TeV_chi1p5TeV",
   "clustAlgPlots/Suu5TeV_chi1TeV",
   "clustAlgPlots/Suu5TeV_chi1p5TeV",
   "clustAlgPlots/Suu5TeV_chi2TeV",
   "clustAlgPlots/Suu6TeV_chi1TeV",
   "clustAlgPlots/Suu6TeV_chi1p5TeV",
   "clustAlgPlots/Suu6TeV_chi2TeV",
   "clustAlgPlots/Suu7TeV_chi1TeV",
   "clustAlgPlots/Suu7TeV_chi2TeV",
   "clustAlgPlots/Suu7TeV_chi3TeV",
   "clustAlgPlots/Suu8TeV_chi1TeV",
   "clustAlgPlots/Suu8TeV_chi2TeV",
   "clustAlgPlots/Suu8TeV_chi3TeV"};



   //totHT nbtaggedAK4 SJ_nAK4[0] SJ_nAK4[1] nfatjet_pre SJ_mass_100[0] SJ_mass_100[1]


   double cuts_totHT[] = { 1500.,
   1500,
   1500,
   1500,
   2250,
   2250,
   2250,
   2250,
   2250,
   2250,
   2250,
   1500,
   1500,
   1500,
   1500,
   1500
   };
                              //  0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
   int cuts_nbtaggedAK4[] =       { 2,2,2,2,2,2,2,2,2,2, 2, 2, 2, 2, 2, 2};
   int cuts_SJ1_nAK4_300[] =      { 2,2,2,2,2,2,2,2,2,2, 2, 2, 2, 2, 2, 2};
   int cuts_SJ2_nAK4_300[] =      { 2,2,2,2,2,2,2,2,2,2, 2, 2, 2, 2, 2, 2};
   int cuts_nfatjets_pre[] =      { 3,3,3,3,2,2,2,2,2,2, 2, 2, 2, 2, 2, 2};  
   double cuts_SJ1_mass_100[] =   { 500,500,500,500,600,600,600,600,600,600, 500, 500, 500, 500, 500, 500};
   double cuts_SJ2_mass_100[] =   { 500,500,500,500,600,600,600,600,600,600, 500, 500, 500, 500, 500, 500};
   double scaleFactors[]      = {4.34e0/5.,  
4.05e0/5.,
3.87e0/5.,
2.89e0/5.,
6.84e-1/3.,
5.93e-1/3.,
4.33e-1/3.,
1.41e-1/2,
1.29e-1/2,
1.10e-1/2,
2.01e-1/6,
1.71e-1/6,
1.31e-1/6,
2.17e-2/9,
1.93e-2/9,
1.74e-2/9};

   for(int iii = 0; iii< 16;iii++)
   {
      std::cout << "Doing analysis in " << folderNames[iii] << std::endl;
      doAnalysis(inputFilenames[iii], outputFilenames[iii], folderNames[iii], scaleFactors[iii],cuts_totHT[iii],cuts_nbtaggedAK4[iii],cuts_SJ1_nAK4_300[iii],cuts_SJ2_nAK4_300[iii], cuts_nfatjets_pre[iii],cuts_SJ1_mass_100[iii],cuts_SJ2_mass_100[iii] );
      std::cout << "Finished analysis for " << folderNames[iii] << std::endl;
   }

   return;

}


#include <iostream>
#include <string>
#include "TLorentzVector.h"

using namespace std;


void doAnalysis(const char * inputFilename, const char * outputFilename, std::string folderName, double scaleFactor)
{

   int eventnum = 0;
   int nhadevents = 0;
   int nfatjets = 0;
   int raw_nfatjets;
   int tot_nAK4_50,tot_nAK4_70;
   int SJ_nAK4_50[100],SJ_nAK4_70[100];
   double jet_pt[100], jet_eta[100], jet_mass[100], jet_dr[100], raw_jet_mass[100],raw_jet_pt[100],raw_jet_phi[100];
   double jet_beta[100], beta_T[100], AK4_mass_20[100],AK4_mass_30[100],AK4_mass_50[100],AK4_mass_70[100],AK4_mass_100[100],SJ_mass_150[100],SJ_mass_600[100],SJ_mass_800[100],SJ_mass_1000[100];
   double SJ_mass_50[100], SJ_mass_70[100],superJet_mass[100],SJ_AK4_50_mass[100],SJ_AK4_70_mass[100],genSuperJetMass[100];
   double tot_jet_mass,decay_inv_mass, chi_inv_mass;
   int nSuperJets,correctlySortedChi1,correctlySortedChi2;
   int nSuccessfulSorts = 0;
   int jet_ndaughters[100], jet_nAK4[100],jet_nAK4_20[100],jet_nAK4_30[100],jet_nAK4_50[100],jet_nAK4_70[100],SJ_nAK4_150[100],jet_nAK4_150[100],SJ_nAK4_200[100],SJ_nAK4_400[100],SJ_nAK4_600[100],SJ_nAK4_800[100],SJ_nAK4_1000[100];
   int ntotalevents = 0;
   int nAK4;
   double topAK8_dr,WSuuAK8_dr,bSuuAK8_dr,higgsAK8_dr,topWAK8_dr,topbAK8_dr,topAK4_dr,WSuuAK4_dr,bSuuAK4_dr,higgsAK4_dr,topWAK4_dr,topbAK4_dr;
   double AK4_mass[100];
   double chi_dr,topPart_dr,higgs_dr,SuuW_dr,HiggsTop_dr,SuuWb_dr;
   int tot_mpp_AK4;
   double SJ_mass_100[100],AK4_E[500];
   int SJ_nAK4_100[100];
   double totHT = 0;
   int nbtaggedAK4 =0;
   int SJ_nAK4_300[100];
   double genPartChiDaughterMPP_angle[2];
   double genHiggsThrustCos[100], genTopWThrustCos[100], genSuuWThrustCos[100];
   int nfatjet_pre;

   double genTopbThrustCos,genSuubThrustCos,diSuperJet_mass,diSuperJet_mass_100;
   double resonance_mass_comb;
   double daughter_mass_comb[100];
   double nPassed_totHT = 0;
   double nPassed_btagged_AK4 = 0;
   double nPassed_nfatjets = 0;
   double nPassed_SJ_nAK4_200 = 0;
   double nPassed_SJ_mass_100 = 0;
   double SJ_mass_300[100];

   double totMET;

   TFile *f = new TFile(inputFilename);
   TFile outFile(outputFilename,"RECREATE");

   TCanvas *c1 = new TCanvas("c1","",400,20, 2000,2000);

////////////////////////Change this to go back do diquark! Change the tree
   TTree *t1 = (TTree*)f->Get("clusteringAnalyzerBR/tree");
   const Int_t nentries = t1->GetEntries();

////////////////////////////////////////////////////////////////////////////////////////////////////////

   TH1I* h_nfatjets = new TH1I("h_nfatjets","Number of AK8 Jets; # AK8 Jets",8,-0.5,7.5);
   TH1I* h_nAK4 = new TH1I("h_nAK4","Number of AK4 Jets; # AK8 Jets",20,-0.5,19.5);

   TH1F* h_SJ_AK4_50_mass = new TH1F("h_SJ_AK4_50_mass","Mass of Reclustered AK4 Jets (E_{SJ COM} >50 GeV);p_{T} [GeV];Events / 10 GeV",80,0.,800);
   TH1F* h_SJ_AK4_70_mass = new TH1F("h_SJ_AK4_70_mass","Mass of Reclustered AK4 Jets (E_{SJ COM} >70 GeV);p_{T} [GeV]; Events / 10 GeV",80,0.,800);


   TH1F* h_SJ_mass_50 = new TH1F("h_SJ_mass_50","Mass of Reclustered SuperJet (E_{MPP} >50 GeV);p_{T} [GeV]; Events / 160 GeV",50,0.,8000);
   TH1F* h_SJ_mass_70 = new TH1F("h_SJ_mass_70","Mass of Reclustered SuperJet (E_{MPP} >70 GeV);p_{T} [GeV]; Events / 160 GeV",50,0.,8000);
   TH1F* h_AK4_mass = new TH1F("h_AK4_mass","Mass of AK4 Jets;Mass [GeV]",60,0.,600);
   TH1F* h_superJet_mass = new TH1F("h_superJet_mass","Mass of SuperJets; Mass [GeV];Events / 100 GeV",40,0.,4000.);
   TH1F* h_superJet_mass_50 = new TH1F("h_superJet_mass_50","Mass of SuperJets; Mass [GeV];Events / 100 GeV",40,0.,4000.);

   TH1F* h_jet_mass = new TH1F("h_jet_mass","Mass of AK8 Jets; Mass [GeV]; Events / 30 GeV",40,0.,1200);
   TH1F* h_SJ_mass_100 = new TH1F("h_SJ_mass_100","Mass of SuperJets (E_{SJ COM}> 100 GeV);Mass [GeV]; Events / 80 GeV",100,0.,8000.);

   TH1F* h_SJ_mass_50_pre = new TH1F("h_SJ_mass_50_pre","Mass of SuperJets (E_{SJ COM}> 50 GeV);Mass [GeV]; Events / 70 GeV",50,0.,3500.);
   TH1F* h_SJ_mass_100_pre = new TH1F("h_SJ_mass_100_pre","Mass of SuperJets (E_{SJ COM}> 100 GeV);Mass [GeV]; Events / 70 GeV",50,0.,3500.);


   TH1F* h_AK4_E = new TH1F("h_AK4_E","Energy of AK4 Jets;Energy [GeV]",100,0.,600.);
   TH1I* h_SJ_nAK4_100 = new TH1I("h_SJ_nAK4_100","Number of AK4 Jets (E_{SJ COM} > 100 GeV); # AK4 Jets",9,-0.5,8.5);
   TH1I* h_SJ_nAK4_125 = new TH1I("h_SJ_nAK4_125","Number of AK4 Jets (E_{SJ COM} > 125 GeV); # AK4 Jets",9,-0.5,8.5);
   TH1I* h_SJ_nAK4_150 = new TH1I("h_SJ_nAK4_150","Number of AK4 Jets (E_{SJ COM} > 150 GeV); # AK4 Jets",9,-0.5,8.5);
   TH1I* h_SJ_nAK4_200 = new TH1I("h_SJ_nAK4_200","Number of AK4 Jets (E_{SJ COM} > 200 GeV); # AK4 Jets",9,-0.5,8.5);
   TH1I* h_SJ_nAK4_300 = new TH1I("h_SJ_nAK4_300","Number of AK4 Jets (E_{SJ COM} > 300 GeV); # AK4 Jets",9,-0.5,8.5);
   TH1I* h_SJ_nAK4_400 = new TH1I("h_SJ_nAK4_400","Number of AK4 Jets (E_{SJ COM} > 400 GeV); # AK4 Jets",9,-0.5,8.5);
   TH1I* h_SJ_nAK4_600 = new TH1I("h_SJ_nAK4_600","Number of AK4 Jets (E_{SJ COM} > 600 GeV); # AK4 Jets",9,-0.5,8.5);
   TH1I* h_SJ_nAK4_800 = new TH1I("h_SJ_nAK4_800","Number of AK4 Jets (E_{SJ COM} > 800 GeV); # AK4 Jets",9,-0.5,8.5);
   TH1I* h_SJ_nAK4_1000 = new TH1I("h_SJ_nAK4_1000","Number of AK4 Jets (E_{SJ COM} > 1000 GeV); # AK4 Jets",9,-0.5,8.5);

   TH1F* h_diSuperJet_mass = new TH1F("h_diSuperJet_mass","diSuperJet Mass;Mass [GeV]; Events / 200 GeV",50,0.,10000.);
   TH1F* h_diSuperJet_mass_100 = new TH1F("h_diSuperJet_mass_100","diSuperJet Mass (E_{SJ COM}> 100 GeV);Mass [GeV]; Events / 160 GeV",50,0.,8000.);

   TH2F* h_superJet_mass_TH2 = new TH2F("h_superJet_mass_TH2", "SuperJet 1 Mass vs SuperJet 2 Mass;SuperJet 1 mass [GeV] / 70 GeV; SuperJet 2 mass [GeV] / 70 GeV", 30 , 400., 2500., 30., 400., 2500.);
   TH1F* h_diSuperJet_mass_diag = new TH1F("h_diSuperJet_mass_diag","diSuperJet Mass (Along SJ mass diagonal);Mass [GeV]; Events / 50 GeV",50,0.,2500.);



   //can probably be deleted soon
   TH1I* h_SJ_nAK4_200_pre = new TH1I("h_SJ_nAK4_200_pre","Number of AK4 Jets (E_{SJ COM} > 200 GeV); # AK4 Jets",9,-0.5,8.5);

   TH1F* h_superJet_mass_pre = new TH1F("h_superJet_mass_pre","Mass of SuperJets; Mass [GeV];Events / 80 GeV",100,0.,8000.);

   TH1F* h_diSuperJet_mass_pre = new TH1F("h_diSuperJet_mass_pre","diSuperJet Mass;Mass [GeV]; Events / 200 GeV",50,0.,10000.);

   TH1F* h_superJet_mass_comb = new TH1F("h_superJet_mass_comb","Mass of SuperJets (full combinatorics); Mass [GeV];Events / 100 GeV",40,0.,4000.);
   TH1F* h_diSuperJet_mass_comb = new TH1F("h_diSuperJet_mass_comb","diSuperJet Mass (full combinatorics);Mass [GeV]; Events / 200 GeV",50,0.,10000.);


   TH1F* h_totHT = new TH1F("h_totHT","Total Event HT; HT [GeV]; Events / 80 GeV",100,0.,8000.);
   TH1I* h_nbtaggedAk4 = new TH1I("h_nbtaggedAk4","; ; Events",6,-0.5,5.5);
   TH1I* h_nfatjets_pre = new TH1I("h_nfatjets_pre","Number of AK8 Jets (M PUPPI > 45 GeV,pT> 500 GeV ); # AK8 Jets",8,-0.5,7.5);

   TH1F* h_superJet_mass_avg = new TH1F("h_superJet_mass_avg","Average Mass of the Two SuperJets; Mass [GeV];Events / 70 GeV",50,0.,3500.);
   TH1F* h_totMET = new TH1F("h_totMET","Total (pf) MET in Event; MET [GeV];Events / 60 GeV",50,0.,3000.);
   TH1F* h_totMET_sig = new TH1F("h_totMET_sig","(pf) MET significance (MET/HT)",25,0.,2.5);



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
   t1->SetBranchAddress("SJ_mass_50", SJ_mass_50);

   t1->SetBranchAddress("SJ_mass_600", SJ_mass_600);
   t1->SetBranchAddress("SJ_mass_800", SJ_mass_800);
   t1->SetBranchAddress("SJ_mass_300", SJ_mass_300);

   t1->SetBranchAddress("SJ_mass_1000", SJ_mass_1000);

   t1->SetBranchAddress("superJet_mass", superJet_mass);   
   t1->SetBranchAddress("SJ_AK4_50_mass", SJ_AK4_50_mass);   //mass of individual reclustered AK4 jets
   t1->SetBranchAddress("SJ_AK4_70_mass", SJ_AK4_70_mass); 

   
   t1->SetBranchAddress("SJ_nAK4_150", SJ_nAK4_150);   

   t1->SetBranchAddress("SJ_nAK4_200", SJ_nAK4_200);   
   t1->SetBranchAddress("SJ_nAK4_400", SJ_nAK4_400);   
   t1->SetBranchAddress("SJ_nAK4_600", SJ_nAK4_600);   
   t1->SetBranchAddress("SJ_nAK4_800", SJ_nAK4_800);   
   t1->SetBranchAddress("SJ_nAK4_1000", SJ_nAK4_1000);   

   t1->SetBranchAddress("nAK4" , &nAK4); 

   t1->SetBranchAddress("tot_mpp_AK4" , &tot_mpp_AK4); 
   t1->SetBranchAddress("SJ_mass_100", SJ_mass_100);   
   t1->SetBranchAddress("SJ_nAK4_100", SJ_nAK4_100);   
   t1->SetBranchAddress("AK4_E", AK4_E);  

   t1->SetBranchAddress("daughter_mass_comb", daughter_mass_comb);   
   t1->SetBranchAddress("resonance_mass_comb", &resonance_mass_comb);  
   t1->SetBranchAddress("totMET", &totMET);  



   TGraph *h_SJ_mass_versus = new TGraph();
   h_SJ_mass_versus->SetName("h_SJ_mass_versus");
   h_SJ_mass_versus->SetTitle("SuperJet 1 Mass vs SuperJet 2 Mass (QCD)");
   h_SJ_mass_versus->GetXaxis()->SetTitle("SuperJet 1 Mass [GeV]");
   h_SJ_mass_versus->GetYaxis()->SetTitle("SuperJet 2 Mass [GeV]");
   h_SJ_mass_versus->GetYaxis()->SetTitleOffset(1.5);


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

   TGraph *h_SJ_mass_50_versus = new TGraph();
   h_SJ_mass_50_versus->SetTitle("SuperJet 1 Mass vs SuperJet 2 Mass (SJ COM AK4 E>50 GeV)");
   h_SJ_mass_50_versus->GetXaxis()->SetTitle("SuperJet 1 Mass");
   h_SJ_mass_50_versus->GetYaxis()->SetTitle("SuperJet 2 Mass");
   h_SJ_mass_50_versus->GetYaxis()->SetTitleOffset(1.5);


   TGraph *h_SJ_mass_70_versus = new TGraph();
   h_SJ_mass_70_versus->SetTitle("SuperJet 1 Mass vs SuperJet 2 Mass (SJ COM AK4 E>70 GeV)");
   h_SJ_mass_70_versus->GetXaxis()->SetTitle("SuperJet 1 Mass");
   h_SJ_mass_70_versus->GetYaxis()->SetTitle("SuperJet 2 Mass");
   h_SJ_mass_70_versus->GetYaxis()->SetTitleOffset(1.5);

   //cuts to change here 
   //totHT nbtaggedAK4 SJ_nAK4[0] SJ_nAK4[1] nfatjet_pre SJ_mass_100[0] SJ_mass_100[1]

   //double cut_totHT = 3000.; int cut_nbtaggedAK4 =2;int cut_SJ1_nAK4_200 = 2;int cut_SJ2_nAK4_200 = 2;int cut_nfatjet_pre =3; double cut_SJ1_mass_100 = 250.;double cut_SJ2_mass_100 = 250.;   // 
   //double cut_totHT = 3000.; int cut_nbtaggedAK4 =2;int cut_SJ1_nAK4_200 = 2;int cut_SJ2_nAK4_200 = 2;int cut_nfatjet_pre =3; double cut_SJ1_mass_100 = 500.;double cut_SJ2_mass_100 = 500.;   //
   //double cut_totHT = 3000.; int cut_nbtaggedAK4 =2;int cut_SJ1_nAK4_200 = 2;int cut_SJ2_nAK4_200 = 2;int cut_nfatjet_pre =3; double cut_SJ1_mass_100 = 500.;double cut_SJ2_mass_100 = 500.;   // 
   //double cut_totHT = 3000.; int cut_nbtaggedAK4 =2;int cut_SJ1_nAK4_200 = 2;int cut_SJ2_nAK4_200 = 2;int cut_nfatjet_pre =3; double cut_SJ1_mass_100 = 500.;double cut_SJ2_mass_100 = 500.;   // 
   //double cut_totHT = 3500.; int cut_nbtaggedAK4 =2;int cut_SJ1_nAK4_200 = 2;int cut_SJ2_nAK4_200 = 2;int cut_nfatjet_pre =3; double cut_SJ1_mass_100 = 500.;double cut_SJ2_mass_100 = 500.;   // 
   //double cut_totHT = 3500.; int cut_nbtaggedAK4 =2;int cut_SJ1_nAK4_200 = 2;int cut_SJ2_nAK4_200 = 2;int cut_nfatjet_pre =3; double cut_SJ1_mass_100 = 500.;double cut_SJ2_mass_100 = 500.;   // 
   //double cut_totHT = 3500.; int cut_nbtaggedAK4 =2;int cut_SJ1_nAK4_200 = 2;int cut_SJ2_nAK4_200 = 2;int cut_nfatjet_pre =3; double cut_SJ1_mass_100 = 500.;double cut_SJ2_mass_100 = 500.;   // 
   //double cut_totHT = 4000.; int cut_nbtaggedAK4 =2;int cut_SJ1_nAK4_200 = 2;int cut_SJ2_nAK4_200 = 2;int cut_nfatjet_pre =2; double cut_SJ1_mass_100 = 500.;double cut_SJ2_mass_100 = 500.;   // 
   double cut_totHT = 2250.; int cut_nbtaggedAK4 =2;int cut_SJ1_nAK4_200 = 2;int cut_SJ2_nAK4_200 = 2;int cut_nfatjet_pre =2; double cut_SJ1_mass_100 = 600.;double cut_SJ2_mass_100 = 600.;   // 
   //double cut_totHT = 4000.; int cut_nbtaggedAK4 =2;int cut_SJ1_nAK4_200 = 2;int cut_SJ2_nAK4_200 = 2;int cut_nfatjet_pre =2; double cut_SJ1_mass_100 = 500.;double cut_SJ2_mass_100 = 500.;   // 
   //double cut_totHT = 4000.; int cut_nbtaggedAK4 =2;int cut_SJ1_nAK4_200 = 2;int cut_SJ2_nAK4_200 = 2;int cut_nfatjet_pre =2; double cut_SJ1_mass_100 = 500.;double cut_SJ2_mass_100 = 500.;   // 
   //double cut_totHT = 4000.; int cut_nbtaggedAK4 =2;int cut_SJ1_nAK4_200 = 2;int cut_SJ2_nAK4_200 = 2;int cut_nfatjet_pre =2; double cut_SJ1_mass_100 = 500.;double cut_SJ2_mass_100 = 500.;   // 
   //double cut_totHT = 4000.; int cut_nbtaggedAK4 =2;int cut_SJ1_nAK4_200 = 2;int cut_SJ2_nAK4_200 = 2;int cut_nfatjet_pre =2; double cut_SJ1_mass_100 = 500.;double cut_SJ2_mass_100 = 500.;   // 
   //double cut_totHT = 4000.; int cut_nbtaggedAK4 =2;int cut_SJ1_nAK4_200 = 2;int cut_SJ2_nAK4_200 = 2;int cut_nfatjet_pre =2; double cut_SJ1_mass_100 = 500.;double cut_SJ2_mass_100 = 500.;   // 
   //double cut_totHT = 4000.; int cut_nbtaggedAK4 =2;int cut_SJ1_nAK4_200 = 2;int cut_SJ2_nAK4_200 = 2;int cut_nfatjet_pre =2; double cut_SJ1_mass_100 = 500.;double cut_SJ2_mass_100 = 500.;   // 
   //double cut_totHT = 4000.; int cut_nbtaggedAK4 =2;int cut_SJ1_nAK4_200 = 2;int cut_SJ2_nAK4_200 = 2;int cut_nfatjet_pre =2; double cut_SJ1_mass_100 = 500.;double cut_SJ2_mass_100 = 500.;   // 
   //double cut_totHT = 4000.; int cut_nbtaggedAK4 =2;int cut_SJ1_nAK4_200 = 2;int cut_SJ2_nAK4_200 = 2;int cut_nfatjet_pre =2; double cut_SJ1_mass_100 = 500.;double cut_SJ2_mass_100 = 500.;   // 

   int nevents = 0;int nDiagPoints = 0;
   int  nevents_pre = 0;

   for (Int_t i=0;i<nentries;i++) 
   {  
      t1->GetEntry(i);
      h_nfatjets->Fill(nfatjets);
      h_totHT->Fill(totHT);
      h_nfatjets_pre->Fill(nfatjet_pre);
      h_nbtaggedAk4->Fill(nbtaggedAK4);
      h_totMET->Fill(totMET);
      h_totMET_sig->Fill(totMET/totHT);

      //if((nbtaggedAK4>=cut_nbtaggedAK4) && (nfatjet_pre >=2))
      if((totHT>cut_totHT)&&(nbtaggedAK4>=cut_nbtaggedAK4) && (nfatjet_pre >=cut_nfatjet_pre))      //if((nbtaggedAK4>=cut_nbtaggedAK4) && (nfatjet_pre >=2))

      {

         if(    (superJet_mass[0]>300.)&&(superJet_mass[1]>300.) ) h_superJet_mass_TH2->Fill(superJet_mass[0],superJet_mass[1]);
         h_SJ_mass_versus->SetPoint(nevents_pre,superJet_mass[0],superJet_mass[1]);

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

      /*
      if((totHT>cut_totHT)&&(nbtaggedAK4>=cut_nbtaggedAK4)&& (nfatjet_pre >= cut_nfatjet_pre) && (SJ_nAK4_200[0]>=cut_SJ1_nAK4_200)&&(SJ_nAK4_200[1]>=cut_SJ2_nAK4_200))
      {
         h_SJ_mass_100_pre->Fill(SJ_mass_100[0],scaleFactor);
         h_SJ_mass_100_pre->Fill(SJ_mass_100[1],scaleFactor);

      }
      */
      if( (totHT>=cut_totHT) )
      {
         nPassed_totHT+= scaleFactor;
         if (nbtaggedAK4>=cut_nbtaggedAK4)
         {
            nPassed_btagged_AK4+=scaleFactor;
            if( nfatjet_pre >= cut_nfatjet_pre   )
            {
               nPassed_nfatjets+=scaleFactor;
               if( (SJ_nAK4_200[0]>=cut_SJ1_nAK4_200)&&(SJ_nAK4_200[1]>=cut_SJ2_nAK4_200) && (SJ_mass_100[0]>=cut_SJ1_mass_100) && (SJ_mass_100[1]>=cut_SJ2_mass_100)  )nPassed_SJ_nAK4_200+=scaleFactor;
            }
         }
      }
      if((totHT<cut_totHT)||(nbtaggedAK4<cut_nbtaggedAK4)|| (nfatjet_pre < cut_nfatjet_pre))continue;

      if((SJ_nAK4_200[0]<cut_SJ1_nAK4_200)||(SJ_nAK4_200[1]<cut_SJ2_nAK4_200) || (SJ_mass_100[0]<cut_SJ1_mass_100) || (SJ_mass_100[1]<cut_SJ2_mass_100) ) continue;      
      if( (superJet_mass[0]/superJet_mass[1] > 1.20)||(superJet_mass[0]/superJet_mass[1] < 0.8)     )continue;

      h_superJet_mass_50->Fill(SJ_mass_50[0],scaleFactor);
      h_superJet_mass_50->Fill(SJ_mass_50[1],scaleFactor);

      h_superJet_mass->Fill(superJet_mass[0],scaleFactor);
      h_superJet_mass->Fill(superJet_mass[1],scaleFactor);

      ntotalevents++;
      for(int iii = 0;iii<tot_mpp_AK4;iii++)
      {
         h_AK4_E->Fill(AK4_E[tot_mpp_AK4],scaleFactor);
      }

      h_nfatjets->Fill(nfatjets);

      h_SJ_nAK4_100->Fill(SJ_nAK4_100[0]);
      h_SJ_nAK4_100->Fill(SJ_nAK4_100[1]);

      h_SJ_nAK4_200->Fill(SJ_nAK4_200[0]);
      h_SJ_nAK4_200->Fill(SJ_nAK4_200[1]);

      h_SJ_nAK4_400->Fill(SJ_nAK4_400[0]);
      h_SJ_nAK4_400->Fill(SJ_nAK4_400[1]);

      h_SJ_nAK4_600->Fill(SJ_nAK4_600[0]);
      h_SJ_nAK4_600->Fill(SJ_nAK4_600[1]);

      h_SJ_nAK4_800->Fill(SJ_nAK4_800[0]);
      h_SJ_nAK4_800->Fill(SJ_nAK4_800[1]);

      h_SJ_nAK4_1000->Fill(SJ_nAK4_1000[0]);
      h_SJ_nAK4_1000->Fill(SJ_nAK4_1000[1]);

      for(int iii=0;iii<nfatjets;iii++)
      {
         h_jet_mass->Fill(jet_mass[iii]);
      }
      

      h_diSuperJet_mass->Fill(diSuperJet_mass,scaleFactor);
//(diSuperJet_mass_100 < 4000.)
      if( (superJet_mass[0]/superJet_mass[1] > 0.8)&&(superJet_mass[0]/superJet_mass[1] < 1.25) )
      {
         h_diSuperJet_mass_diag->Fill(diSuperJet_mass,scaleFactor);
         h_Mchichi_vs_Mchi_SJ1_diag->SetPoint(nDiagPoints, superJet_mass[0], diSuperJet_mass);
         nDiagPoints++;
      }
      h_superJet_mass_TH2->Fill(superJet_mass[0],superJet_mass[1],scaleFactor);

      TRandom3 * ran = new TRandom3(0);
      double rannum = ran->Rndm();
      //if(rannum < scaleFactor) 
      h_Mchichi_vs_Mchi_SJ1->SetPoint(nevents, superJet_mass[0], diSuperJet_mass);
      h_Mchichi_vs_Mchi_SJ2->SetPoint(nevents, superJet_mass[1], diSuperJet_mass);



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
      }
      h_nAK4->Fill(nAK4,scaleFactor);
      for(int iii = 0;iii<nAK4;iii++)
      {
         h_AK4_mass->Fill(AK4_mass[iii],scaleFactor);
      }


      h_superJet_mass_avg->Fill((superJet_mass[0]+superJet_mass[1])/2.);
      nevents++;
    }


   //f->Close();
   std::cout << " lepton veto & trigger = 5478, HT = " << nPassed_totHT << " , btagged AK8 = " << nPassed_btagged_AK4 << " , nfatjets = " << nPassed_nfatjets << " , jet substructure = " << nPassed_SJ_nAK4_200 << std::endl;

   gStyle->SetOptStat(0);

   TAxis *axis = h_SJ_mass_versus->GetXaxis();
   axis->SetLimits(0.,2000.);                 // along X
   h_SJ_mass_versus->GetHistogram()->SetMaximum(2000.);   // along          
   h_SJ_mass_versus->GetHistogram()->SetMinimum(0.);
   h_SJ_mass_versus->Draw("AP*");
   c1->SaveAs(   (folderName+"/h_SJ_mass_versus.png").c_str()    );   


   h_nfatjets->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_nfatjets.png").c_str()    );   

   h_totHT->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_totHT.png").c_str()    );   
   h_nfatjets_pre->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_nfatjets_pre.png").c_str()    ); 


   gStyle->SetOptStat(0);

   h_nbtaggedAk4->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_nbtaggedAk4.png").c_str()    ); 


   h_jet_mass->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_jet_mass.png").c_str()    ); 
   
   h_superJet_mass_TH2->Draw("colz");
   c1->SaveAs(   (folderName+"/h_superJet_mass_TH2.png").c_str()    );   

   h_diSuperJet_mass_diag->Draw();
   c1->SaveAs(   (folderName+"/h_diSuperJet_mass_diag.png").c_str()    );  

   h_Mchichi_vs_Mchi_SJ1->Write();
   h_Mchichi_vs_Mchi_SJ1_diag->Write();
   h_Mchichi_vs_Mchi_SJ2->Write();

   h_SJ_nAK4_100->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_SJ_nAK4_100.png").c_str()    );   
   h_SJ_nAK4_200->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_SJ_nAK4_200.png").c_str()    );   
   h_SJ_nAK4_400->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_SJ_nAK4_400.png").c_str()    );   
   h_SJ_nAK4_600->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_SJ_nAK4_600.png").c_str()    );   
   h_SJ_nAK4_800->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_SJ_nAK4_800.png").c_str()    );   
   h_SJ_nAK4_1000->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_SJ_nAK4_1000.png").c_str()    );   
   h_superJet_mass->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_superJet_mass.png").c_str()    );   

   h_SJ_mass_50_versus->Draw("AP*");
   c1->SaveAs(   (folderName+"/h_SJ_mass_50_versus.png").c_str()    );  

   h_SJ_mass_70_versus->Draw("AP*");
   c1->SaveAs(   (folderName+"/h_SJ_mass_70_versus.png").c_str()    );  

   h_SJ_mass_50->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_SJ_mass_50.png").c_str()    ); 

   h_SJ_mass_70->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_SJ_mass_70.png").c_str()    ); 

   h_SJ_mass_100->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_SJ_mass_100.png").c_str()    );  

   h_SJ_AK4_50_mass->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_SJ_AK4_50_mass.png").c_str()    );  

   h_SJ_AK4_70_mass->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_SJ_AK4_70_mass.png").c_str()    ); 

   h_AK4_mass->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_AK4_mass.png").c_str()    ); 


   h_superJet_mass_pre->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_superJet_mass_pre.png").c_str()    ); 
   h_diSuperJet_mass_pre->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_diSuperJet_mass_pre.png").c_str()    ); 


   h_superJet_mass_comb->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_superJet_mass_comb.png").c_str()    ); 
   h_diSuperJet_mass_comb->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_diSuperJet_mass_comb.png").c_str()    ); 

   h_SJ_mass_50_pre->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_SJ_mass_50_pre.png").c_str()    ); 

   h_SJ_mass_100_pre->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_SJ_mass_100_pre.png").c_str()    ); 

   h_diSuperJet_mass_100->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_diSuperJet_mass_100.png").c_str()    ); 


   h_superJet_mass_50->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_superJet_mass_50.png").c_str()    ); 


   h_superJet_mass_avg->Draw("HIST");
   c1->SaveAs(   (folderName+"/_superJet_mass_avg.png").c_str()    ); 

   gPad->SetLogy();
   h_SJ_nAK4_200_pre->Draw("HIST");
   c1->SaveAs(   (folderName+"/h_SJ_nAK4_200_pre.png").c_str()    ); 

     
   //gPad->SetLogy();
   //h_SJ_mass_100_pre->Draw("HIST");
   //c1->SaveAs(   (folderName+"/h_SJ_mass_100_pre.png").c_str()    ); 


   outFile.Write();
   outFile.Close();

}




void read_clustAlgQCDHist()
{  
   const char *inputFilenames[]  = {"ClusteringAlgorithmBR_QCD_HT1000to1500_output.root",
      "ClusteringAlgorithmBR_QCD_HT1500to2000_output.root",
      "ClusteringAlgorithmBR_QCD_HT2000toInf_output.root"};
   const char * outputFilenames[] = {"processed_QCD/HT1000to1500/clustAlg_QCD_HT1000to1500_processed.root",
      "processed_QCD/HT1500to2000/clustAlg_QCD_HT1500to2000_processed.root",
      "processed_QCD/HT2000toInf/clustAlg_QCD_HT2000toInf_processed.root"};
   std::string folderNames[]     = {"processed_QCD/HT1000to1500",
         "processed_QCD/HT1500to2000",
         "processed_QCD/HT2000toInf"};


   double scaleFactors[]      = {4.264568209,0.6137820751,0.2894646169};

   for(int iii = 0; iii< 3;iii++)
   {
      std::cout << "Doing analysis on " << folderNames[iii] << std::endl;
      doAnalysis(inputFilenames[iii], outputFilenames[iii], folderNames[iii], scaleFactors[iii]);
      std::cout << "Finished analysis for " << folderNames[iii] << std::endl;
   }

   return;

}
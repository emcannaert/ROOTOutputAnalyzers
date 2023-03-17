#include <iostream>
#include <string>
#include "TLorentzVector.h"
#include "TRatioPlot.h"
#include "THStack.h"
using namespace std;

void makeCompareBTSF()
{

  double QCD_HT1000to1500_SF = 4.289571744;
  double QCD_HT1500to2000_SF = 0.6042726685;
  double QCD_HT2000toInf_SF = 0.2132134533;
  double TTJets_inclusive_SF = 4.742226033;
  double h_WJetsToLNu_SF = 0.02459688845;
  double h_WJet_QQ_SF = 0.1266526072;


  double h_TTToHadronic_SF = 0.06588049107;
  double h_TTTo2l2nu_SF =0.03616639075 ;
  double h_TTToSemiLeptonic_SF = 0.04563489275;

  double h_Suu5TeV_chi2TeV_SF = 0.867;
  double h_Suu5TeV_chi1p5TeV_SF = 1.19E+00;
  double h_Suu6TeV_chi2TeV_SF = 2.20E-01;
  double h_Suu4TeV_chi1p5TeV_SF = 2.89E+00;
  double h_Suu8TeV_chi2TeV_SF = 1.93E-02;
  double h_Suu8TeV_chi3TeV_SF = 1.74E-02;
  double h_Suu8TeV_chi1TeV_SF = 2.17E-02;

  bool includeTTBar = true;

  std::cout << "Open Files" << std::endl;
  TFile *f1 = new TFile("/home/ethan/Documents/QCD_HT2000toInf_processed_TEST_2018.root");   //need to add these two together
  TFile *f2 = new TFile("/home/ethan/Documents/QCD_HT2000toInf_processed_TEST_NOBTSF2018.root");

  //create histogramas for each of the different plots for different HT levels, scale histograms, add together histograms, normalize, do division/ comparison
  std::cout << "Get histograms" << std::endl;
  ///////////////////////////////1000to1500//////////////////////////////////

  TH1F *h_disuperjet_mass_wsf         =  (TH1F*)f1->Get("h_disuperjet_mass");
  TH1F *h_lead_SJ_mass_wsf            =  (TH1F*)f1->Get("h_lead_SJ_mass");
  TH1F *h_disuperjet_mass_nosf        =  (TH1F*)f2->Get("h_disuperjet_mass");
  TH1F *h_lead_SJ_mass_nosf           =  (TH1F*)f2->Get("h_lead_SJ_mass");



////////////////////////////////////////////////////////////////////////////////////////////////////////

  TCanvas *c1 = new TCanvas("c1","",400,20, 1500,1500);

  gPad->SetLogy();

  //gStyle->SetOptStat(0

  std::cout << "do ratio plots" << std::endl;

  //std::cout << "Number of events: " << h_SJ_nAK4_100_CR->GetEntries() << "/" << h_SJ_nAK4_100_DT->GetEntries() <<std::endl;
  auto rp_h_disuperjet_mass = new TRatioPlot(h_disuperjet_mass_wsf,h_disuperjet_mass_nosf);
  rp_h_disuperjet_mass->Draw("HIST,E");
  rp_h_disuperjet_mass->GetLowerRefYaxis()->SetTitle("with SF / no SF");
  rp_h_disuperjet_mass->GetLowerRefGraph()->SetMinimum(0.95);
  rp_h_disuperjet_mass->GetLowerRefGraph()->SetMaximum(1.05);

  rp_h_disuperjet_mass->GetUpperRefYaxis()->SetTitle("Events");
  c1->SaveAs("rp_h_disuperjet_mass_BTSF.png");  

  auto rp_lead_SJ_mass = new TRatioPlot(h_lead_SJ_mass_wsf,h_lead_SJ_mass_nosf);
  rp_lead_SJ_mass->Draw("HIST,E");
  rp_lead_SJ_mass->GetLowerRefYaxis()->SetTitle("with SF / no SF");
  rp_lead_SJ_mass->GetLowerRefGraph()->SetMaximum(1.05);
  rp_lead_SJ_mass->GetLowerRefGraph()->SetMinimum(0.95);
  rp_lead_SJ_mass->GetUpperRefYaxis()->SetTitle("Events");
  c1->SaveAs("rp_lead_SJ_mass_BTSF.png");  
}

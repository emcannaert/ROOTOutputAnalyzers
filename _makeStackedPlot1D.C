#include <iostream>
#include <string>
#include "TLorentzVector.h"
#include "TRatioPlot.h"
#include "THStack.h"
#include <string>
using namespace std;

void _makeStackedPlot1D()
{
  double QCD1000to1500_SF = 4.289571744;
  double QCD1500to2000_SF = 0.6042726685;
  double QCD2000toInf_SF = 0.2132134533;
  double TTJets_inclusive_SF = 4.742226033;
  double h_WJetsToLNu_SF = 0.02459688845;
  double h_WJet_QQ_SF = 0.1266526072;
  double h_TTToHadronic_SF = 0.06588049107;
  double h_TTTo2l2nu_SF = 0.03616639075;
  double h_TTToSemiLeptonic_SF = 0.04563489275;

  double Suu8TeV_chi3TeV_SF = 1.74E-02;
  double Suu5TeV_chi1p5TeV_SF = 1.19E+00/5.;
  double Suu6TeV_chi2TeV_SF = 2.20E-01;

  double h_Suu5TeV_chi2TeV_SF = 0.867;
  double h_Suu5TeV_chi1p5TeV_SF = 1.19E+00/5.;
  double h_Suu6TeV_chi2TeV_SF = 2.20E-01;
  double h_Suu4TeV_chi1p5TeV_SF = 2.89E+00;
  double h_Suu8TeV_chi2TeV_SF = 1.93E-02;
  double h_Suu8TeV_chi3TeV_SF = 1.74E-02;
  double h_Suu8TeV_chi1TeV_SF = 2.17E-02;

  TFile *f2 = new TFile("/home/ethan/Documents/rootFiles/processedRootFiles/QCD_HT1500to2000_processed.root");
  TFile *f3 = new TFile("/home/ethan/Documents/rootFiles/processedRootFiles/QCD_HT2000toInf_processed.root");   //need to add these two together
  TFile *f11 = new TFile("/home/ethan/Documents/rootFiles/processedRootFiles/TTToHadronic_processed.root");
  TFile *f12 = new TFile("/home/ethan/Documents/rootFiles/processedRootFiles/JetHT_2018_combined.root");  // data

  TFile *f13 = new TFile("/home/ethan/Documents/rootFiles/signalRootFiles/ClusteringAlgorithm_MSuu8TeV-MChi3TeV_cutbased_processed.root");  // sig MC
  TFile *f14 = new TFile("/home/ethan/Documents/rootFiles/signalRootFiles/ClusteringAlgorithm_MSuu5TeV-MChi1p5TeV_cutbased_processed.root");  // sig MC
  TCanvas *c1 = new TCanvas("c1","",400,20, 1500,1500);


  TH1F *h_SJ_mass_DT_HT1500to2000_TH2        = (TH1F*)f2->Get("h_SJ_mass_DT");
  TH1F *h_SJ_mass_DT_HT2000toInf_TH2         = (TH1F*)f3->Get("h_SJ_mass_DT");
  TH1F *h_SJ_mass_DT_TTbar                   = (TH1F*)f11->Get("h_SJ_mass_DT");
  TH1F *h_SJ_mass_DT_Suu5TeV_chi1p5TeV       = (TH1F*)f14->Get("h_SJ_mass_SR");
  TH1F *h_SJ_mass_DT_Suu8TeV_chi3TeV         = (TH1F*)f13->Get("h_SJ_mass_SR");

  h_SJ_mass_DT_HT1500to2000_TH2->Scale(QCD1500to2000_SF);
  h_SJ_mass_DT_HT2000toInf_TH2->Scale(QCD2000toInf_SF);
  h_SJ_mass_DT_TTbar->Scale(h_TTToHadronic_SF);
  h_SJ_mass_DT_Suu5TeV_chi1p5TeV->Scale(Suu5TeV_chi1p5TeV_SF);
  h_SJ_mass_DT_Suu8TeV_chi3TeV->Scale(h_Suu8TeV_chi3TeV_SF);

  TH1F *h_AllBR_combined = new TH1F(*h_SJ_mass_DT_HT2000toInf_TH2);
  h_AllBR_combined->Add(h_SJ_mass_DT_HT1500to2000_TH2);
  h_AllBR_combined->Add(h_SJ_mass_DT_TTbar);


  TH1F *h_SJ_mass_1D_Suu5TeV_chi1p5TeV_sensitivity = new TH1F(*h_SJ_mass_DT_Suu5TeV_chi1p5TeV);
  TH1F *h_SJ_mass_1D_Suu8TeV_chi3TeV_sensitivity = new TH1F(*h_SJ_mass_DT_Suu8TeV_chi3TeV);

  TH1F *h_AllBR_combined_TH1_sqrt = new TH1F(*h_AllBR_combined);  
  for(int iii=0;iii<h_AllBR_combined->GetNbinsX();iii++)
  {
      h_AllBR_combined_TH1_sqrt->SetBinContent(iii,sqrt(h_AllBR_combined->GetBinContent(iii)));
  }
  h_SJ_mass_1D_Suu5TeV_chi1p5TeV_sensitivity->Divide(h_AllBR_combined_TH1_sqrt);
  h_SJ_mass_1D_Suu5TeV_chi1p5TeV_sensitivity->Draw("HIST");
  c1->SaveAs("/home/ethan/Documents/plots/h_SJ_mass_1D_Suu5TeV_chi1p5TeV_sensitivity.png"); 

  h_SJ_mass_1D_Suu8TeV_chi3TeV_sensitivity->Divide(h_AllBR_combined_TH1_sqrt);
  h_SJ_mass_1D_Suu8TeV_chi3TeV_sensitivity->Draw("HIST");
  c1->SaveAs("/home/ethan/Documents/plots/h_SJ_mass_1D_Suu8TeV_chi3TeV_sensitivity.png"); 

}

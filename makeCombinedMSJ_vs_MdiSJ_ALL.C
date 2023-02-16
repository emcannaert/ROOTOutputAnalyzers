#include <iostream>
#include <string>
#include "TLorentzVector.h"
#include "TRatioPlot.h"
#include "THStack.h"
using namespace std;

void makeCombinedMSJ_vs_MdiSJ_ALL()
{

  double QCD1000to1500_SF = 4.289571744;
  double QCD1500to2000_SF = 0.6042726685;
  double QCD2000toInf_SF = 0.2132134533;
  double TTJets_inclusive_SF = 4.742226033;
  double h_WJetsToLNu_SF = 0.02459688845;
  double h_WJet_QQ_SF = 0.1266526072;
  double h_TTToHadronic_SF = 0.06588049107;
  double h_TTTo2l2nu_SF =0.03616639075 ;
  double h_TTToSemiLeptonic_SF = 0.04563489275;
  //double h_TTJets2500toInf_SF  = 0.00008408965681;


  TFile *f1 = new TFile("/home/ethan/Documents/QCD_HT1000to1500_combined_processed.root");
  TFile *f2 = new TFile("/home/ethan/Documents/QCD_HT1500to2000_combined_processed.root");
  TFile *f3 = new TFile("/home/ethan/Documents/QCD_HT2000toInf_combined_processed.root");   //need to add these two together
  //TFile *f9 = new TFile("/home/ethan/Documents/WJetsToLNu_combined_processed.root");
  //TFile *f10 = new TFile("/home/ethan/Documents/WJet_QQ_combined_processed.root");
  TFile *f11 = new TFile("/home/ethan/Documents/TTToHadronic_combined_processed.root");
  TFile *f12 = new TFile("/home/ethan/Documents/TTTo2l2nu_combine_processed.root");
  TFile *f13 = new TFile("/home/ethan/Documents/TTtoSemiLeptonic_combined_processed.root");


  TH2F *h_HT1000to1500_HT = (TH2F*)f1->Get("h_MSJ_mass_vs_MdSJ_all");
  TH2F *h_HT1500to2000_HT = (TH2F*)f2->Get("h_MSJ_mass_vs_MdSJ_all");
  TH2F *h_HT2000toInf_HT = (TH2F*)f3->Get("h_MSJ_mass_vs_MdSJ_all");

  h_HT1000to1500_HT->Scale(QCD1000to1500_SF);
  h_HT1500to2000_HT->Scale(QCD1500to2000_SF);
  h_HT2000toInf_HT->Scale(QCD2000toInf_SF);

  //TH2F *h_WJetsToLNu = (TH2F*)f9->Get("h_MSJ_mass_vs_MdSJ_all");
  //TH2F *h_WJet_QQ = (TH2F*)f10->Get("h_MSJ_mass_vs_MdSJ_all");
  TH2F *h_TTToHadronic = (TH2F*)f11->Get("h_MSJ_mass_vs_MdSJ_all");
  TH2F *h_TTTo2l2nu = (TH2F*)f12->Get("h_MSJ_mass_vs_MdSJ_all");
  TH2F *h_TTToSemiLeptonic = (TH2F*)f13->Get("h_MSJ_mass_vs_MdSJ_all");


  //h_WJetsToLNu->Scale(h_WJetsToLNu_SF);
  //h_WJet_QQ->Scale(h_WJet_QQ_SF);
  h_TTToHadronic->Scale(h_TTToHadronic_SF);
  h_TTTo2l2nu->Scale(h_TTTo2l2nu_SF);
  h_TTToSemiLeptonic->Scale(h_TTToSemiLeptonic_SF);


  TH2F *h_TTbar_combined = new TH2F(*h_TTToHadronic);
  h_TTbar_combined->Add(h_TTTo2l2nu);
  h_TTbar_combined->Add(h_TTToSemiLeptonic);
  //TH2F *h_WJets_combined = new TH2F(*h_WJetsToLNu);
  //h_WJets_combined->Add(h_WJet_QQ);
  
  TH2F *h_QCD_combined = new TH2F(*h_HT1000to1500_HT);
  h_QCD_combined->Add(h_HT1500to2000_HT);
  h_QCD_combined->Add(h_HT2000toInf_HT);


  TCanvas *c1 = new TCanvas("c1","",400,20, 1500,1500);
  gPad->SetLogz();

  TH2F *h_BR_combined = new TH2F(*h_QCD_combined);

  h_BR_combined->SetTitle("M_{SJ} vs M_{diSJ} for Combined Backgrounds with No Further Selection; M_{diSJ};M_{SJ}");
  h_BR_combined->GetYaxis()->SetTitleOffset(1.35);
  h_BR_combined->GetYaxis()->SetLabelSize(0.015);
  h_BR_combined->Add(h_TTbar_combined);
  //h_BR_combined->Add(h_WJets_combined);

  h_BR_combined->Draw("colz");

  c1->SaveAs("MSJ_vs_MdiSJ_BR_ALL.png"); 

}

#include <iostream>
#include <string>
#include "TLorentzVector.h"
#include "TRatioPlot.h"
#include "THStack.h"
using namespace std;

void makeStackedPlotSJRatio()
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
  TFile *f4 = new TFile("/home/ethan/Documents/TTJets_inclusive_combined_processed.root");

  TFile *f9 = new TFile("/home/ethan/Documents/WJetsToLNu_combined_processed.root");
  TFile *f10 = new TFile("/home/ethan/Documents/WJet_QQ_combined_processed.root");
  TFile *f11 = new TFile("/home/ethan/Documents/TTToHadronic_combined_processed.root");
  TFile *f12 = new TFile("/home/ethan/Documents/TTTo2l2nu_combine_processed.root");
  TFile *f13 = new TFile("/home/ethan/Documents/TTtoSemiLeptonic_combined_processed.root");


  TH1F *h_HT1000to1500_HT = (TH1F*)f1->Get("h_MSJ1_MSJ2_ratio");
  TH1F *h_HT1500to2000_HT = (TH1F*)f2->Get("h_MSJ1_MSJ2_ratio");
  TH1F *h_HT2000toInf_HT = (TH1F*)f3->Get("h_MSJ1_MSJ2_ratio");

  h_HT1000to1500_HT->Scale(QCD1000to1500_SF);
  h_HT1500to2000_HT->Scale(QCD1500to2000_SF);
  h_HT2000toInf_HT->Scale(QCD2000toInf_SF);



  TH1F *h_WJetsToLNu = (TH1F*)f9->Get("h_MSJ1_MSJ2_ratio");
  TH1F *h_WJet_QQ = (TH1F*)f10->Get("h_MSJ1_MSJ2_ratio");
  TH1F *h_TTToHadronic = (TH1F*)f11->Get("h_MSJ1_MSJ2_ratio");
  TH1F *h_TTTo2l2nu = (TH1F*)f12->Get("h_MSJ1_MSJ2_ratio");
  TH1F *h_TTToSemiLeptonic = (TH1F*)f13->Get("h_MSJ1_MSJ2_ratio");

  h_WJetsToLNu->Scale(h_WJetsToLNu_SF);
  h_WJet_QQ->Scale(h_WJet_QQ_SF);
  h_TTToHadronic->Scale(h_TTToHadronic_SF);
  h_TTTo2l2nu->Scale(h_TTTo2l2nu_SF);
  h_TTToSemiLeptonic->Scale(h_TTToSemiLeptonic_SF);

  TH1F *h_TTbar_combined = new TH1F(*h_TTToHadronic);
  h_TTbar_combined->Add(h_TTTo2l2nu);
  h_TTbar_combined->Add(h_TTToSemiLeptonic);

  TH1F *h_WJets_combined = new TH1F(*h_WJetsToLNu);
  h_WJets_combined->Add(h_WJet_QQ);


  TH1F *h_QCD_combined = new TH1F(*h_HT1000to1500_HT);
  h_QCD_combined->Add(h_HT1500to2000_HT);
  h_QCD_combined->Add(h_HT2000toInf_HT);


  h_QCD_combined->SetFillColor(kRed);
  h_TTbar_combined->SetFillColor(kBlue);
  h_WJets_combined->SetFillColor(kGreen);


  TCanvas *c1 = new TCanvas("c1","",400,20, 1500,1500);
  //gPad->SetLogy();

  THStack *hs = new THStack("hs","MC SJ Ratio Stack");
  hs->Add(h_QCD_combined);
  hs->Add(h_TTbar_combined);
  hs->Add(h_WJets_combined);
  hs->Draw("HIST");
  c1->SaveAs("SJ_mass_ratio_stack.png"); 
f
}

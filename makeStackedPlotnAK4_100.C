#include <iostream>
#include <string>
#include "TLorentzVector.h"
#include "TRatioPlot.h"
#include "THStack.h"
using namespace std;

void makeStackedPlotnAK4_100()
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
  TFile *f5 = new TFile("/home/ethan/Documents/dataMistagRates_JetHT2018A.root");
  TFile *f6 = new TFile("/home/ethan/Documents/dataMistagRates_JetHT2018B.root");
  TFile *f7 = new TFile("/home/ethan/Documents/dataMistagRates_JetHT2018C.root");
  TFile *f8 = new TFile("/home/ethan/Documents/dataMistagRates_JetHT2018D.root");

  TFile *f9 = new TFile("/home/ethan/Documents/WJetsToLNu_combined_processed.root");
  TFile *f10 = new TFile("/home/ethan/Documents/WJet_QQ_combined_processed.root");
  TFile *f11 = new TFile("/home/ethan/Documents/TTToHadronic_combined_processed.root");
  TFile *f12 = new TFile("/home/ethan/Documents/TTTo2l2nu_combine_processed.root");
  TFile *f13 = new TFile("/home/ethan/Documents/TTtoSemiLeptonic_combined_processed.root");


  TH1I *h_HT1000to1500_HT = (TH1I*)f1->Get("h_SJ_nAK4_100");
  TH1I *h_HT1500to2000_HT = (TH1I*)f2->Get("h_SJ_nAK4_100");
  TH1I *h_HT2000toInf_HT = (TH1I*)f3->Get("h_SJ_nAK4_100");

  h_HT1000to1500_HT->Scale(QCD1000to1500_SF);
  h_HT1500to2000_HT->Scale(QCD1500to2000_SF);
  h_HT2000toInf_HT->Scale(QCD2000toInf_SF);


  TH1I *h_WJetsToLNu = (TH1I*)f9->Get("h_SJ_nAK4_100");
  TH1I *h_WJet_QQ = (TH1I*)f10->Get("h_SJ_nAK4_100");
  TH1I *h_TTToHadronic = (TH1I*)f11->Get("h_SJ_nAK4_100");
  TH1I *h_TTTo2l2nu = (TH1I*)f12->Get("h_SJ_nAK4_100");
  TH1I *h_TTToSemiLeptonic = (TH1I*)f13->Get("h_SJ_nAK4_100");

  h_WJetsToLNu->Scale(h_WJetsToLNu_SF);
  h_WJet_QQ->Scale(h_WJet_QQ_SF);
  h_TTToHadronic->Scale(h_TTToHadronic_SF);
  h_TTTo2l2nu->Scale(h_TTTo2l2nu_SF);
  h_TTToSemiLeptonic->Scale(h_TTToSemiLeptonic_SF);

  TH1I *h_TTbar_combined = new TH1I(*h_TTToHadronic);
  h_TTbar_combined->Add(h_TTTo2l2nu);
  h_TTbar_combined->Add(h_TTToSemiLeptonic);

  TH1I *h_WJets_combined = new TH1I(*h_WJetsToLNu);
  h_WJets_combined->Add(h_WJet_QQ);



  TH1I *h_JetHTA_HT = (TH1I*)f5->Get("h_SJ_nAK4_100");
  TH1I *h_JetHTB_HT = (TH1I*)f6->Get("h_SJ_nAK4_100");
  TH1I *h_JetHTC_HT = (TH1I*)f7->Get("h_SJ_nAK4_100");
  TH1I *h_JetHTD_HT = (TH1I*)f8->Get("h_SJ_nAK4_100");


  TH1I *h_JetHT_combined = new TH1I(*h_JetHTA_HT);
  h_JetHT_combined->Add(h_JetHTB_HT);
  h_JetHT_combined->Add(h_JetHTC_HT);
  h_JetHT_combined->Add(h_JetHTD_HT);

  TH1I *h_QCD_combined = new TH1I(*h_HT1000to1500_HT);
  h_QCD_combined->Add(h_HT1500to2000_HT);
  h_QCD_combined->Add(h_HT2000toInf_HT);


  h_QCD_combined->SetFillColor(kRed);
  h_TTbar_combined->SetFillColor(kBlue);
  h_WJets_combined->SetFillColor(kGreen);

  TCanvas *c1 = new TCanvas("c1","",400,20, 1500,1500);
  gPad->SetLogy();
  h_JetHT_combined->SetMarkerStyle(8);
  h_JetHT_combined->SetMarkerSize(1.25);

  THStack *hs = new THStack("hs","Data vs MC nAK4 (E_{COM} > 100 GeV)");
  hs->Add(h_QCD_combined);
  hs->Add(h_TTbar_combined);
  hs->Add(h_WJets_combined);

  hs->Draw("HIST");
  h_JetHT_combined->Draw("SAME,P,E");
  c1->SaveAs("nAK4_100_stack.png"); 

  TH1I *h_BR_combined = new TH1I(*h_QCD_combined);
  h_BR_combined->Add(h_TTbar_combined);
  h_BR_combined->Add(h_WJets_combined);

  std::cout << "There are " << h_JetHT_combined->Integral(0,50) << " data nAK4 100." << std::endl;
  std::cout << "There are " << h_BR_combined->Integral(0,50) << " MC nAK4 100." << std::endl;

  auto rp_HT = new TRatioPlot(h_JetHT_combined,h_BR_combined);
  //h_BR_combined->Draw("HIST");
  rp_HT->Draw("HIST,EP");
  rp_HT->GetLowerRefYaxis()->SetTitle("data/MC ratio");
  rp_HT->GetLowerRefGraph()->SetMaximum(2.);
  rp_HT->GetUpperRefYaxis()->SetTitle("Events");


  c1->SaveAs("tot_nAK4_100_ratio.png"); 

}

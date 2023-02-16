#include <iostream>
#include <string>
#include "TLorentzVector.h"
#include "TRatioPlot.h"
#include "THStack.h"
using namespace std;

void makeStackedPlotTH2()
{
  double QCD1500to2000_SF = 0.6042726685;
  double QCD2000toInf_SF = 0.2132134533;
  double h_TTJets1200to2500_SF = 0.003918532089;
  double h_TTJets2500toInf_SF  = 0.00008408965681;

  TFile *f1 = new TFile("/home/ethan/Documents/QCD_HT2000toInf_combined_processed.root");
  TFile *f2 = new TFile("/home/ethan/Documents/QCD_HT1500to2000_combined_processed.root");
  TFile *f3 = new TFile("/home/ethan/Documents/TTJets_HT1200to2500_combined_processed.root");   //need to add these two together
  TFile *f4 = new TFile("/home/ethan/Documents/TTJets_HT2500toInf_combined_processed.root");
  TFile *f5 = new TFile("/home/ethan/Documents/dataMistagRates_JetHT2018A.root");
  TFile *f6 = new TFile("/home/ethan/Documents/dataMistagRates_JetHT2018B.root");
  TFile *f7 = new TFile("/home/ethan/Documents/dataMistagRates_JetHT2018C.root");
  TFile *f8 = new TFile("/home/ethan/Documents/dataMistagRates_JetHT2018D.root");


  TH2F *h_HT2000toInf_HT = (TH2F*)f1->Get("h_MSJ_mass_vs_MdSJ");
  TH2F *h_HT1500to2000_HT = (TH2F*)f2->Get("h_MSJ_mass_vs_MdSJ");
  h_HT1500to2000_HT->Scale(QCD1500to2000_SF);
  h_HT2000toInf_HT->Scale(QCD2000toInf_SF);

  TH2F *h_TTJets1200to2500_HT = (TH2F*)f3->Get("h_MSJ_mass_vs_MdSJ");
  TH2F *h_TTJets2500toInf_HT = (TH2F*)f4->Get("h_MSJ_mass_vs_MdSJ");
  h_TTJets1200to2500_HT->Scale(h_TTJets1200to2500_SF);
  h_TTJets2500toInf_HT->Scale(h_TTJets2500toInf_SF);

  //TH1F *h_JetHTA_HT = (TH1F*)f5->Get("h_MSJ_mass_vs_MdSJ");
  //TH1F *h_JetHTB_HT = (TH1F*)f6->Get("h_MSJ_mass_vs_MdSJ");
  //TH1F *h_JetHTC_HT = (TH1F*)f7->Get("h_MSJ_mass_vs_MdSJ");
  //TH1F *h_JetHTD_HT = (TH1F*)f8->Get("h_MSJ_mass_vs_MdSJ");

  TH2F *h_QCD_combined = new TH2F(*h_HT1500to2000_HT);
  h_QCD_combined->Add(h_HT2000toInf_HT);
  h_QCD_combined->Add(h_TTJets1200to2500_HT);
  h_QCD_combined->Add(h_TTJets2500toInf_HT);
  TCanvas *c1 = new TCanvas("c1","",400,20, 1500,1500);

  gPad->SetLogz();

  //TH1F *h_TTbar_combined = new TH1F(*h_TTJets1200to2500_HT);
  //h_TTbar_combined->Add(h_TTJets2500toInf_HT);

  //TH1F *h_JetHT_combined = new TH1F(*h_JetHTA_HT);
  //h_JetHT_combined->Add(h_JetHTB_HT);
  //h_JetHT_combined->Add(h_JetHTC_HT);
  //h_JetHT_combined->Add(h_JetHTD_HT);


  //h_QCD_combined->SetFillColor(kRed);
  //h_TTbar_combined->SetFillColor(kBlue);

  h_QCD_combined->Draw("colz");
  c1->SaveAs("h_MSJ_vs_MdSJ_combined.png"); 


  //THStack *hs = new THStack("hs","Data vs MC Lead SuperJet Mass; M_{SJ} [GeV]");
  //hs->Add(h_QCD_combined);
  //hs->Add(h_TTbar_combined);
  //hs->Draw("HIST");
  //h_JetHT_combined->Draw("SAME");
  //c1->SaveAs("SJ_mass_stack.png"); 

  //TH1F *h_BR_combined = new TH1F(*h_QCD_combined);
  //h_BR_combined->Add(h_TTbar_combined);

  //std::cout << "There are " << h_JetHT_combined->Integral(0,50) << " data superjets." << std::endl;
  //std::cout << "There are " << h_BR_combined->Integral(0,50) << " MC superjets." << std::endl;

  //auto rp_HT = new TRatioPlot(h_JetHT_combined,h_BR_combined);
  ///h_BR_combined->Draw("HIST");
  //rp_HT->Draw("HIST,EP");
  //rp_HT->GetLowerRefYaxis()->SetTitle("data/MC ratio");
  //rp_HT->GetLowerRefGraph()->SetMaximum(2.);
  //rp_HT->GetUpperRefYaxis()->SetTitle("Events");



}

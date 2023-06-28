#include <iostream>
#include <string>
#include "TLorentzVector.h"
#include "TRatioPlot.h"
#include "THStack.h"
using namespace std;

void makeStackedPlot()
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
  //double h_TTJets2500toInf_SF  = 0.00008408965681;

//  TFile *f1 = new TFile("/home/ethan/Documents/QCD_HT1000to1500_combined_processed.root");
  TFile *f2 = new TFile("/home/ethan/Documents/rootFiles/processedRootFiles/QCD_HT1500to2000_processed.root");
  TFile *f3 = new TFile("/home/ethan/Documents/rootFiles/processedRootFiles/QCD_HT2000toInf_processed.root");   //need to add these two together
/*  
  TFile *f5 = new TFile("/home/ethan/Documents/dataMistagRates_JetHT2018A.root");
  TFile *f6 = new TFile("/home/ethan/Documents/dataMistagRates_JetHT2018B.root");
  TFile *f7 = new TFile("/home/ethan/Documents/dataMistagRates_JetHT2018C.root");
  TFile *f8 = new TFile("/home/ethan/Documents/dataMistagRates_JetHT2018D.root");
*/

  TFile *f11 = new TFile("/home/ethan/Documents/rootFiles/processedRootFiles/TTToHadronic_processed.root");
//  TFile *f12 = new TFile("/home/ethan/Documents/TTTo2l2nu_combine_processed.root");
//  TFile *f13 = new TFile("/home/ethan/Documents/TTtoSemiLeptonic_combined_processed.root");


//  TH1F *h_HT1000to1500_HT = (TH1F*)f1->Get("h_totHT");
  TH1F *h_HT1500to2000_HT = (TH1F*)f2->Get("h_totHT");
  TH1F *h_HT2000toInf_HT = (TH1F*)f3->Get("h_totHT");


//  h_HT1000to1500_HT->Scale(QCD1000to1500_SF);
  h_HT1500to2000_HT->Scale(QCD1500to2000_SF);
  h_HT2000toInf_HT->Scale(QCD2000toInf_SF);


//  TH1F *h_WJetsToLNu = (TH1F*)f9->Get("h_totHT");
//  TH1F *h_WJet_QQ = (TH1F*)f10->Get("h_totHT");
  TH1F *h_TTToHadronic = (TH1F*)f11->Get("h_totHT");
//  TH1F *h_TTTo2l2nu = (TH1F*)f12->Get("h_totHT");
//  TH1F *h_TTToSemiLeptonic = (TH1F*)f13->Get("h_totHT");

  TH2F *h_MSJ_mass_vs_MdSJ_DT_HT1500to2000 = (TH2F*)f2->Get("h_MSJ_mass_vs_MdSJ_DT");
  TH2F *h_MSJ_mass_vs_MdSJ_DT_HT2000toInf  = (TH2F*)f3->Get("h_MSJ_mass_vs_MdSJ_DT");
  TH2F *h_MSJ_mass_vs_MdSJ_DT_TTToHadronic = (TH2F*)f11->Get("h_MSJ_mass_vs_MdSJ_DT");

  h_MSJ_mass_vs_MdSJ_DT_HT1500to2000->Scale(QCD1500to2000_SF);
  h_MSJ_mass_vs_MdSJ_DT_HT2000toInf->Scale(QCD2000toInf_SF);
  h_MSJ_mass_vs_MdSJ_DT_TTToHadronic->Scale(h_TTToHadronic_SF);

  TH2F *h_MSJ_mass_vs_MdSJ_CR_HT1500to2000 = (TH2F*)f2->Get("h_MSJ_mass_vs_MdSJ_CR");
  TH2F *h_MSJ_mass_vs_MdSJ_CR_HT2000toInf  = (TH2F*)f3->Get("h_MSJ_mass_vs_MdSJ_CR");
  TH2F *h_MSJ_mass_vs_MdSJ_CR_TTToHadronic = (TH2F*)f11->Get("h_MSJ_mass_vs_MdSJ_CR");

  h_MSJ_mass_vs_MdSJ_CR_HT1500to2000->Scale(QCD1500to2000_SF);
  h_MSJ_mass_vs_MdSJ_CR_HT2000toInf->Scale(QCD2000toInf_SF);
  h_MSJ_mass_vs_MdSJ_CR_TTToHadronic->Scale(h_TTToHadronic_SF);




  h_TTToHadronic->Scale(h_TTToHadronic_SF);
//  h_TTTo2l2nu->Scale(h_TTTo2l2nu_SF);
//  h_TTToSemiLeptonic->Scale(h_TTToSemiLeptonic_SF);

  TH1F *h_TTbar_combined = new TH1F(*h_TTToHadronic);
//  h_TTbar_combined->Add(h_TTTo2l2nu);
//  h_TTbar_combined->Add(h_TTToSemiLeptonic);



/*
  TH1F *h_JetHTA_HT = (TH1F*)f5->Get("h_totHT");
  TH1F *h_JetHTB_HT = (TH1F*)f6->Get("h_totHT");
  TH1F *h_JetHTC_HT = (TH1F*)f7->Get("h_totHT");
  TH1F *h_JetHTD_HT = (TH1F*)f8->Get("h_totHT");
*/
/*
  TH1F *h_JetHT_combined = new TH1F(*h_JetHTA_HT);
  h_JetHT_combined->Add(h_JetHTB_HT);
  h_JetHT_combined->Add(h_JetHTC_HT);
  h_JetHT_combined->Add(h_JetHTD_HT);
*/
  TH1F *h_QCD_combined = new TH1F(*h_HT2000toInf_HT);
  h_QCD_combined->Add(h_HT1500to2000_HT);
//  h_QCD_combined->Add(h_HT1000to1500_HT);
  TCanvas *c1 = new TCanvas("c1","",400,20, 1500,1500);

/////////////////////////////SR TH2////////////////////////////////////////
  TH2F *h_QCD_combined_TH2 = new TH2F(*h_MSJ_mass_vs_MdSJ_DT_HT2000toInf);
  h_QCD_combined_TH2->Add(h_MSJ_mass_vs_MdSJ_DT_HT1500to2000);
  TH2F *h_TTBar_combined_TH2 = new TH2F(*h_MSJ_mass_vs_MdSJ_DT_TTToHadronic);
  h_QCD_combined_TH2->Draw("colz");
  c1->SaveAs("/home/ethan/Documents/plots/h_QCD_TH2.png"); 

  h_TTBar_combined_TH2->Draw("colz");
  c1->SaveAs("/home/ethan/Documents/plots/h_TTBar_TH2.png"); 

  TH2F *h_TTBar_combined_TH2_copy = new TH2F(*h_MSJ_mass_vs_MdSJ_DT_TTToHadronic);

  TH2F *h_AllBR_combined_TH2 = new TH2F(*h_QCD_combined_TH2);
  h_AllBR_combined_TH2->Add(h_TTBar_combined_TH2);

  h_TTBar_combined_TH2_copy->Divide(h_AllBR_combined_TH2);
  h_TTBar_combined_TH2_copy->Draw("colz");
  c1->SaveAs("/home/ethan/Documents/plots/h_TTBar_over_totBR.png"); 
///////////////////////////////////////////////////////////////////////////////

/////////////////////////////CR TH2////////////////////////////////////////
  TH2F *h_QCD_combined_CR_TH2 = new TH2F(*h_MSJ_mass_vs_MdSJ_CR_HT2000toInf);
  h_QCD_combined_CR_TH2->Add(h_MSJ_mass_vs_MdSJ_CR_HT1500to2000);
  TH2F *h_TTBar_combined_CR_TH2 = new TH2F(*h_MSJ_mass_vs_MdSJ_CR_TTToHadronic);
  h_QCD_combined_CR_TH2->Draw("colz");
  c1->SaveAs("/home/ethan/Documents/plots/h_QCD_CR_TH2.png"); 

  h_TTBar_combined_CR_TH2->Draw("colz");
  c1->SaveAs("/home/ethan/Documents/plots/h_TTBar_CR_TH2.png"); 

  TH2F *h_TTBar_combined_CR_TH2_copy = new TH2F(*h_MSJ_mass_vs_MdSJ_CR_TTToHadronic);

  TH2F *h_AllBR_combined_CR_TH2 = new TH2F(*h_QCD_combined_CR_TH2);
  h_AllBR_combined_CR_TH2->Add(h_TTBar_combined_CR_TH2);

  h_TTBar_combined_CR_TH2_copy->Divide(h_AllBR_combined_CR_TH2);
  h_TTBar_combined_CR_TH2_copy->Draw("colz");
  c1->SaveAs("/home/ethan/Documents/plots/h_TTBar_over_totBR_CR.png"); 

///////////////////////////////////////////////////////////////////////////


  h_QCD_combined->SetFillColor(kRed);
  h_TTbar_combined->SetFillColor(kBlue);



  gPad->SetLogy();
//  h_JetHT_combined->SetMarkerStyle(8);
//  h_JetHT_combined->SetMarkerSize(1.25);

  THStack *hs = new THStack("hs","Data vs MC H_{T}; H_{T} [GeV]");
  hs->Add(h_QCD_combined);
  hs->Add(h_TTbar_combined);
//  hs->Add(h_WJets_combined);
  hs->Draw("HIST");
  
 // h_JetHT_combined->Draw("SAME,P,E");
  c1->SaveAs("/home/ethan/Documents/plots/tot_HT_stack.png"); 

  TH1F *h_BR_combined = new TH1F(*h_QCD_combined);
  h_BR_combined->Add(h_TTbar_combined);
//  h_BR_combined->Add(h_WJets_combined);

//  std::cout << "There are " << h_JetHT_combined->Integral(0,50) << " data HT events." << std::endl;
  std::cout << "There are " << h_BR_combined->Integral(0,50) << " MC HT events." << std::endl;


/*
  auto rp_HT = new TRatioPlot(h_JetHT_combined,h_BR_combined);
  //
  rp_HT->Draw();
  rp_HT->GetLowerRefYaxis()->SetTitle("data/MC ratio");
  rp_HT->GetLowerRefGraph()->SetMaximum(2.);
  rp_HT->GetUpperRefYaxis()->SetTitle("Events");
  //h_JetHT_combined->Draw("SAME,P,E");
  //h_BR_combined->Draw("SAME,HIST");

  c1->SaveAs("tot_HT_ratio.png"); 
*/

}

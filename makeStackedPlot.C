#include <iostream>
#include <string>
#include "TLorentzVector.h"
#include "TRatioPlot.h"
#include "THStack.h"
#include <string>
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

  double Suu8TeV_chi3TeV_SF = 1.74E-02;
  double Suu5TeV_chi1p5TeV_SF = 1.19E+00;
  double Suu6TeV_chi2TeV_SF = 2.20E-01;

  double h_Suu5TeV_chi2TeV_SF = 0.867;
  double h_Suu5TeV_chi1p5TeV_SF = 1.19E+00;
  double h_Suu6TeV_chi2TeV_SF = 2.20E-01;
  double h_Suu4TeV_chi1p5TeV_SF = 2.89E+00;
  double h_Suu8TeV_chi2TeV_SF = 1.93E-02;
  double h_Suu8TeV_chi3TeV_SF = 1.74E-02;
  double h_Suu8TeV_chi1TeV_SF = 2.17E-02;
  //TH2F *h_MSJ_mass_vs_MdSJ_doubleTag = new TH2F("h_MSJ_mass_vs_MdSJ_doubleTag","Avg (double) tagged Superjet mass vs diSuperjet mass; diSuperjet mass [GeV];superjet mass", 25,0, 10000, 20, 0, 6000);

  TH1F* h_MSJ_mass_vs_MdSJ_DT_unwrapped_QCD = new TH1F("h_MSJ_mass_vs_MdSJ_DT_unwrapped_QCD","Unwrapped QCD M_{SJ,avg} vs M_{diSJ};; Events / 375x125 GeV",440,0.,440);
  TH1F* h_MSJ_mass_vs_MdSJ_DT_unwrapped_TTbar = new TH1F("h_MSJ_mass_vs_MdSJ_DT_unwrapped_TTbar","Unwrapped TTbar M_{SJ,avg} vs M_{diSJ};; Events / 375x125 GeV",440,0.,440);

  TH1F* h_MSJ_mass_vs_MdSJ_CR_unwrapped_QCD = new TH1F("h_MSJ_mass_vs_MdSJ_CR_unwrapped_QCD","Unwrapped QCD M_{SJ,avg} vs M_{diSJ};; Events / 375x125 GeV",440,0.,440);
  TH1F* h_MSJ_mass_vs_MdSJ_CR_unwrapped_TTbar = new TH1F("h_MSJ_mass_vs_MdSJ_CR_unwrapped_TTbar","Unwrapped TTbar M_{SJ,avg} vs M_{diSJ};; Events / 375x125 GeV",440,0.,440);

  TFile *f2 = new TFile("/home/ethan/Documents/rootFiles/processedRootFiles/QCD_HT1500to2000_processed.root");
  TFile *f3 = new TFile("/home/ethan/Documents/rootFiles/processedRootFiles/QCD_HT2000toInf_processed.root");   //need to add these two together
  TFile *f11 = new TFile("/home/ethan/Documents/rootFiles/processedRootFiles/TTToHadronic_processed.root");
  TFile *f12 = new TFile("/home/ethan/Documents/rootFiles/processedRootFiles/JetHT_2018_combined.root");  // data

  TFile *f13 = new TFile("/home/ethan/Documents/rootFiles/signalRootFiles/ClusteringAlgorithm_MSuu8TeV-MChi3TeV_cutbased_processed.root");  // sig MC
  TFile *f14 = new TFile("/home/ethan/Documents/rootFiles/signalRootFiles/ClusteringAlgorithm_MSuu5TeV-MChi1p5TeV_cutbased_processed.root");  // sig MC


//  TH1F *h_HT1000to1500_HT = (TH1F*)f1->Get("h_totHT");
  TH1F *h_HT1500to2000_HT = (TH1F*)f2->Get("h_totHT");
  TH1F *h_HT2000toInf_HT = (TH1F*)f3->Get("h_totHT");


//  h_HT1000to1500_HT->Scale(QCD1000to1500_SF);
  h_HT1500to2000_HT->Scale(QCD1500to2000_SF);
  h_HT2000toInf_HT->Scale(QCD2000toInf_SF);

  TH1F *h_TTToHadronic = (TH1F*)f11->Get("h_totHT");
//  TH1F *h_TTTo2l2nu = (TH1F*)f12->Get("h_totHT");
//  TH1F *h_TTToSemiLeptonic = (TH1F*)f13->Get("h_totHT");

  TH2F *h_MSJ_mass_vs_MdSJ_DT_HT1500to2000 = (TH2F*)f2->Get("h_MSJ_mass_vs_MdSJ_DT");
  TH2F *h_MSJ_mass_vs_MdSJ_DT_HT2000toInf  = (TH2F*)f3->Get("h_MSJ_mass_vs_MdSJ_DT");
  TH2F *h_MSJ_mass_vs_MdSJ_DT_TTToHadronic = (TH2F*)f11->Get("h_MSJ_mass_vs_MdSJ_DT");

  TH2F *h_MSJ_mass_vs_MdSJ_DT_Suu8TeV_chi3TeV = (TH2F*)f13->Get("h_MSJ_mass_vs_MdSJ_DT");
  TH2F *h_MSJ_mass_vs_MdSJ_DT_Suu5TeV_chi1p5TeV = (TH2F*)f14->Get("h_MSJ_mass_vs_MdSJ_DT");

  h_MSJ_mass_vs_MdSJ_DT_Suu8TeV_chi3TeV->Scale(Suu8TeV_chi3TeV_SF);
  h_MSJ_mass_vs_MdSJ_DT_Suu5TeV_chi1p5TeV->Scale(Suu5TeV_chi1p5TeV_SF/5.);

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


  TH1F *h_QCD_combined = new TH1F(*h_HT2000toInf_HT);
  h_QCD_combined->Add(h_HT1500to2000_HT);
  //  h_QCD_combined->Add(h_HT1000to1500_HT);
  TCanvas *c1 = new TCanvas("c1","",400,20, 1500,1500);



  gStyle->SetOptStat(0);


  ////////////////////////////  1D comparison masses //////////////////////////
  // h_SJ_mass_CR
  // h_disuperjet_mass_CR

  TH1F *h_SJ_mass_CR_HT1500to2000 = (TH1F*)f2->Get("h_SJ_mass_CR");
  TH1F *h_SJ_mass_CR_HT2000toInf  = (TH1F*)f3->Get("h_SJ_mass_CR");
  TH1F *h_SJ_mass_CR_TTToHadronic = (TH1F*)f11->Get("h_SJ_mass_CR");
  TH1F *h_SJ_mass_CR_data         = (TH1F*)f12->Get("h_SJ_mass_CR");


  TH1F *h_disuperjet_mass_CR_HT1500to2000 = (TH1F*)f2->Get("h_disuperjet_mass_CR");
  TH1F *h_disuperjet_mass_CR_HT2000toInf  = (TH1F*)f3->Get("h_disuperjet_mass_CR");
  TH1F *h_disuperjet_mass_CR_TTToHadronic = (TH1F*)f11->Get("h_disuperjet_mass_CR");
  TH1F *h_disuperjet_mass_CR_data         = (TH1F*)f12->Get("h_disuperjet_mass_CR");

  h_SJ_mass_CR_HT1500to2000->Scale(QCD1500to2000_SF);
  h_SJ_mass_CR_HT2000toInf->Scale(QCD2000toInf_SF);
  h_SJ_mass_CR_TTToHadronic->Scale(h_TTToHadronic_SF);

  h_disuperjet_mass_CR_HT1500to2000->Scale(QCD1500to2000_SF);
  h_disuperjet_mass_CR_HT2000toInf->Scale(QCD2000toInf_SF);
  h_disuperjet_mass_CR_TTToHadronic->Scale(h_TTToHadronic_SF);

  TH1F *h_SJ_mass_CR_BR_combined = new TH1F(*h_SJ_mass_CR_HT1500to2000);
  h_SJ_mass_CR_BR_combined->Add(h_SJ_mass_CR_HT2000toInf);
  //h_SJ_mass_CR_BR_combined->Add(h_SJ_mass_CR_TTToHadronic);

  TH1F *h_disuperjet_mass_CR_BR_combined = new TH1F(*h_disuperjet_mass_CR_HT1500to2000);
  h_disuperjet_mass_CR_BR_combined->Add(h_disuperjet_mass_CR_HT2000toInf);
  //h_disuperjet_mass_CR_BR_combined->Add(h_disuperjet_mass_CR_TTToHadronic);

  auto rp_SJ_mass = new TRatioPlot(h_SJ_mass_CR_data,h_SJ_mass_CR_BR_combined);
  rp_SJ_mass->Draw();
  rp_SJ_mass->GetLowerRefYaxis()->SetTitle("data/MC ratio");
  rp_SJ_mass->GetLowerRefGraph()->SetMaximum(2.);
  rp_SJ_mass->GetUpperRefYaxis()->SetTitle("Events");
  c1->SaveAs("/home/ethan/Documents/plots/SJ_mass_ratio.png"); 

  auto rp_diSJ_mass = new TRatioPlot(h_disuperjet_mass_CR_data,h_disuperjet_mass_CR_BR_combined);
  //
  rp_diSJ_mass->Draw();
  rp_diSJ_mass->GetLowerRefYaxis()->SetTitle("data/MC ratio");
  rp_diSJ_mass->GetLowerRefGraph()->SetMaximum(2.);
  rp_diSJ_mass->GetUpperRefYaxis()->SetTitle("Events");
  c1->SaveAs("/home/ethan/Documents/plots/diSJ_mass_ratio.png"); 







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
  TFile outFile("/home/ethan/Documents/rootFiles/processedRootFiles/stackedPlots_output.root", "RECREATE");





//create the sentitivity plot for NN - 5 TeV

  TH2F *h_MSJ_mass_vs_MdSJ_DT_NN_HT1500to2000 = (TH2F*)f2->Get("h_MSJ_mass_vs_MdSJ_SR_NN");
  TH2F *h_MSJ_mass_vs_MdSJ_DT_NN_HT2000toInf  = (TH2F*)f3->Get("h_MSJ_mass_vs_MdSJ_SR_NN");
  TH2F *h_MSJ_mass_vs_MdSJ_DT_NN_TToHadronic = (TH2F*)f11->Get("h_MSJ_mass_vs_MdSJ_SR_NN");

  TH2F *h_MSJ_mass_vs_MdSJ_DT_NN_Suu8TeV_chi3TeV = (TH2F*)f13->Get("h_MSJ_mass_vs_MdSJ_DTNN");
  TH2F *h_MSJ_mass_vs_MdSJ_DT_NN_Suu5TeV_chi1p5TeV = (TH2F*)f14->Get("h_MSJ_mass_vs_MdSJ_DTNN");

  h_MSJ_mass_vs_MdSJ_DT_NN_HT1500to2000->Scale(QCD1500to2000_SF);
  h_MSJ_mass_vs_MdSJ_DT_NN_HT2000toInf->Scale(QCD2000toInf_SF);
  h_MSJ_mass_vs_MdSJ_DT_NN_TToHadronic->Scale(h_TTToHadronic_SF);

  h_MSJ_mass_vs_MdSJ_DT_NN_Suu8TeV_chi3TeV->Scale(Suu8TeV_chi3TeV_SF);
  h_MSJ_mass_vs_MdSJ_DT_NN_Suu5TeV_chi1p5TeV->Scale(Suu5TeV_chi1p5TeV_SF);
//  c1->SetLogz();
  c1->SetRightMargin(0.15);
  c1->SetLeftMargin(0.15);
  TH2F *h_QCD_combined_TH2_NN = new TH2F(*h_MSJ_mass_vs_MdSJ_DT_NN_HT2000toInf);
  h_QCD_combined_TH2_NN->Add(h_MSJ_mass_vs_MdSJ_DT_NN_HT1500to2000);

  TH2F *h_AllBR_combined_TH2_NN = new TH2F(*h_QCD_combined_TH2_NN);
  h_AllBR_combined_TH2_NN->Add(h_MSJ_mass_vs_MdSJ_DT_NN_TToHadronic);

  TH2F *h_MSJ_mass_vs_MdSJ_SR_NN_Suu5TeV_chi1p5Tev_sensitivity = new TH2F(*h_MSJ_mass_vs_MdSJ_DT_NN_Suu5TeV_chi1p5TeV);

  TH2F *h_AllBR_NN_combined_TH2_sqrt = new TH2F(*h_AllBR_combined_TH2_NN);  
  for(int iii=0;iii<h_AllBR_combined_TH2_NN->GetNbinsX();iii++)
  {
    for(int jjj=0;jjj<h_AllBR_combined_TH2_NN->GetNbinsY();jjj++)
    {
      h_AllBR_NN_combined_TH2_sqrt->SetBinContent(iii,jjj,sqrt(h_AllBR_combined_TH2_NN->GetBinContent(iii,jjj)));
    }
  }
  h_AllBR_NN_combined_TH2_sqrt->Draw("colz");
  c1->SaveAs("/home/ethan/Documents/plots/h_AllBR_NN_combined_TH2_sqrt.png");

  h_MSJ_mass_vs_MdSJ_DT_NN_Suu5TeV_chi1p5TeV->Draw("colz");
  c1->SaveAs("/home/ethan/Documents/plots/h_MSJ_mass_vs_MdSJ_DT_NN_Suu5TeV_chi1p5TeV.png");

  h_MSJ_mass_vs_MdSJ_DT_NN_Suu8TeV_chi3TeV->Draw("colz");
  c1->SaveAs("/home/ethan/Documents/plots/h_MSJ_mass_vs_MdSJ_DT_NN_Suu8TeV_chi3TeV.png");

  h_MSJ_mass_vs_MdSJ_SR_NN_Suu5TeV_chi1p5Tev_sensitivity->Divide(h_AllBR_NN_combined_TH2_sqrt);
  h_MSJ_mass_vs_MdSJ_SR_NN_Suu5TeV_chi1p5Tev_sensitivity->SetName("h_MSJ_mass_vs_MdSJ_SR_NN_Suu5TeV_chi1p5Tev_sensitivity");
  h_MSJ_mass_vs_MdSJ_SR_NN_Suu5TeV_chi1p5Tev_sensitivity->Write();
  h_MSJ_mass_vs_MdSJ_SR_NN_Suu5TeV_chi1p5Tev_sensitivity->Draw("colz");
  c1->SaveAs("/home/ethan/Documents/plots/TH2_sensitivity_NN_Suu5Tev_chi1p5TeV.png");




//create the sentitivity plot for NN - 8 TeV


  TH2F *h_MSJ_mass_vs_MdSJ_SR_NN_Suu8TeV_chi3Tev_sensitivity = new TH2F(*h_MSJ_mass_vs_MdSJ_DT_NN_Suu8TeV_chi3TeV);

  h_MSJ_mass_vs_MdSJ_SR_NN_Suu8TeV_chi3Tev_sensitivity->Divide(h_AllBR_NN_combined_TH2_sqrt);
  h_MSJ_mass_vs_MdSJ_SR_NN_Suu8TeV_chi3Tev_sensitivity->SetName("h_MSJ_mass_vs_MdSJ_SR_NN_Suu8TeV_chi3Tev_sensitivity");
  h_MSJ_mass_vs_MdSJ_SR_NN_Suu8TeV_chi3Tev_sensitivity->Write();
  h_MSJ_mass_vs_MdSJ_SR_NN_Suu8TeV_chi3Tev_sensitivity->Draw("colz");
  c1->SaveAs("/home/ethan/Documents/plots/TH2_sensitivity_NN_Suu8Tev_chi3TeV.png");











  //create the sentitivity plot - 
  TH2F *h_MSJ_mass_vs_MdSJ_SR_Suu8TeV_chi3Tev_sensitivity = new TH2F(*h_MSJ_mass_vs_MdSJ_DT_Suu8TeV_chi3TeV);

  h_AllBR_combined_TH2->Draw("colz");
  c1->SaveAs("/home/ethan/Documents/plots/h_AllBR_combined_TH2_SR.png");

  TH2F *h_AllBR_combined_TH2_sqrt = new TH2F(*h_AllBR_combined_TH2);  
  for(int iii=0;iii<h_AllBR_combined_TH2->GetNbinsX();iii++)
  {
    for(int jjj=0;jjj<h_AllBR_combined_TH2->GetNbinsY();jjj++)
    {
      h_AllBR_combined_TH2_sqrt->SetBinContent(iii,jjj,sqrt(h_AllBR_combined_TH2->GetBinContent(iii,jjj)));
    }
  }
  h_MSJ_mass_vs_MdSJ_SR_Suu8TeV_chi3Tev_sensitivity->Divide(h_AllBR_combined_TH2_sqrt);
  h_MSJ_mass_vs_MdSJ_SR_Suu8TeV_chi3Tev_sensitivity->SetName("h_MSJ_mass_vs_MdSJ_SR_Suu8TeV_chi3Tev_sensitivity");
  h_MSJ_mass_vs_MdSJ_SR_Suu8TeV_chi3Tev_sensitivity->Write();
  h_MSJ_mass_vs_MdSJ_SR_Suu8TeV_chi3Tev_sensitivity->Draw("colz");
  c1->SaveAs("/home/ethan/Documents/plots/TH2_sensitivity_Suu8Tev_chi3TeV.png");


  TH2F *h_MSJ_mass_vs_MdSJ_SR_Suu5TeV_chi1p5Tev_sensitivity = new TH2F(*h_MSJ_mass_vs_MdSJ_DT_Suu5TeV_chi1p5TeV);
  h_MSJ_mass_vs_MdSJ_SR_Suu5TeV_chi1p5Tev_sensitivity->SetName("h_MSJ_mass_vs_MdSJ_SR_Suu5TeV_chi1p5Tev_sensitivity");
  h_MSJ_mass_vs_MdSJ_SR_Suu5TeV_chi1p5Tev_sensitivity->Divide(h_AllBR_combined_TH2_sqrt);
  h_MSJ_mass_vs_MdSJ_SR_Suu5TeV_chi1p5Tev_sensitivity->Write();
  h_MSJ_mass_vs_MdSJ_SR_Suu5TeV_chi1p5Tev_sensitivity->Draw("colz");
  c1->SaveAs("/home/ethan/Documents/plots/TH2_sensitivity_Suu5Tev_chi1p5TeV.png");
  //outFile.WriteObject(&h_MSJ_mass_vs_MdSJ_SR_Suu5TeV_chi1p5Tev_sensitivity, "h_MSJ_mass_vs_MdSJ_SR_Suu5TeV_chi1p5Tev_sensitivity");
  //outFile.WriteObject(&h_MSJ_mass_vs_MdSJ_SR_Suu8TeV_chi3Tev_sensitivity, "h_MSJ_mass_vs_MdSJ_SR_Suu8TeV_chi3Tev_sensitivity");

  TH1F *h_SJ_mass_HT1500to2000 = (TH1F*)f2->Get("h_SJ_mass_DT");
  TH1F *h_SJ_mass_HT2000toInf = (TH1F*)f3->Get("h_SJ_mass_DT");
  TH1F *h_SJ_mass_TTbar       = (TH1F*)f11->Get("h_SJ_mass_DT");
  h_SJ_mass_HT1500to2000->Scale(QCD1500to2000_SF);
  h_SJ_mass_HT2000toInf->Scale(QCD2000toInf_SF);
  h_SJ_mass_TTbar->Scale(h_TTToHadronic_SF);

  TH1F *h_SJ_mass_QCD_combined = new TH1F(*h_SJ_mass_HT2000toInf);
  h_SJ_mass_QCD_combined->Add(h_SJ_mass_HT1500to2000);
  h_SJ_mass_QCD_combined->SetName("h_SJ_mass_QCD_combined");
  THStack *hs_BR_SR = new THStack("hs_BR_SR","MC SR Contributions from main backgrounds");
  h_SJ_mass_QCD_combined->SetFillColor(kRed);
  h_SJ_mass_TTbar->SetFillColor(kYellow);
  h_SJ_mass_TTbar->SetName("h_SJ_mass_TTbar");
  hs_BR_SR->Add(h_SJ_mass_QCD_combined);
  hs_BR_SR->Add(h_SJ_mass_TTbar);
  
  hs_BR_SR->Draw("HIST");
/*
   auto legend6 = new TLegend(0.6,0.25,0.85,0.4);
   legend6->SetHeader("","C"); // option "C" allows to center the header
   legend6->AddEntry(h_SJ_mass_TTbar,"TTToHadronic","f");
   legend6->AddEntry(h_SJ_mass_QCD_combined,"QCD","f");
   legend6->Draw();
*/
  h_SJ_mass_QCD_combined->Write();
  h_SJ_mass_TTbar->Write();
    c1->SaveAs("/home/ethan/Documents/plots/hs_BR_SR.png"); 

  TH2F *h_MSJ_mass_vs_MdSJ_CR_HT1500to2000_TH2        = (TH2F*)f2->Get("h_MSJ_mass_vs_MdSJ_CR");
  TH2F *h_MSJ_mass_vs_MdSJ_CR_HT2000toInf_TH2         = (TH2F*)f3->Get("h_MSJ_mass_vs_MdSJ_CR");
  TH2F *h_MSJ_mass_vs_MdSJ_CR_TTbar               = (TH2F*)f11->Get("h_MSJ_mass_vs_MdSJ_CR");
  TH2F *h_MSJ_mass_vs_MdSJ_CR_Suu5TeV_chi1p5TeV   = (TH2F*)f14->Get("h_MSJ_mass_vs_MdSJ_CR");



  h_MSJ_mass_vs_MdSJ_CR_HT1500to2000_TH2->Scale(QCD1500to2000_SF);
  h_MSJ_mass_vs_MdSJ_CR_HT2000toInf_TH2->Scale(QCD2000toInf_SF);
  h_MSJ_mass_vs_MdSJ_CR_TTbar->Scale(h_TTToHadronic_SF);
  h_MSJ_mass_vs_MdSJ_CR_Suu5TeV_chi1p5TeV->Scale(Suu5TeV_chi1p5TeV_SF);

  h_MSJ_mass_vs_MdSJ_CR_Suu5TeV_chi1p5TeV->Draw("colz");
  c1->SaveAs("/home/ethan/Documents/plots/h_MSJ_mass_vs_MdSJ_CR_Suu5TeV_chi1p5TeV.png"); 

  TH2F *h_MSJ_mass_vs_MdSJ_CR_allBR = new TH2F(*h_MSJ_mass_vs_MdSJ_CR_HT2000toInf_TH2);
  h_MSJ_mass_vs_MdSJ_CR_allBR->Add(h_MSJ_mass_vs_MdSJ_CR_HT1500to2000_TH2);
  h_MSJ_mass_vs_MdSJ_CR_allBR->Add(h_MSJ_mass_vs_MdSJ_CR_TTbar);

  h_MSJ_mass_vs_MdSJ_CR_allBR->Draw("colz");
  c1->SaveAs("/home/ethan/Documents/plots/h_MSJ_mass_vs_MdSJ_CR_allBR.png"); 

  TH2F *h_MSJ_mass_vs_MdSJ_CR_all = new TH2F(*h_MSJ_mass_vs_MdSJ_CR_HT2000toInf_TH2);
  h_MSJ_mass_vs_MdSJ_CR_all->Add(h_MSJ_mass_vs_MdSJ_CR_HT1500to2000_TH2);
  h_MSJ_mass_vs_MdSJ_CR_all->Add(h_MSJ_mass_vs_MdSJ_CR_TTbar);
  h_MSJ_mass_vs_MdSJ_CR_all->Add(h_MSJ_mass_vs_MdSJ_CR_Suu5TeV_chi1p5TeV);

  TH2F *h_MSJ_mass_vs_MdSJ_CR_sig_contamination   = new TH2F(*h_MSJ_mass_vs_MdSJ_CR_all);
  h_MSJ_mass_vs_MdSJ_CR_sig_contamination->SetName("h_MSJ_mass_vs_MdSJ_CR_sig_contamination");
  h_MSJ_mass_vs_MdSJ_CR_sig_contamination->Divide(h_MSJ_mass_vs_MdSJ_CR_HT2000toInf_TH2);
  h_MSJ_mass_vs_MdSJ_CR_sig_contamination->Draw("colz");
  //c1->SaveAs("/home/ethan/Documents/plots/h_MSJ_mass_vs_MdSJ_CR_sig_contamination.png"); 
  c1->SaveAs("h_MSJ_mass_vs_MdSJ_CR_sig_contamination.png"); 

  //h_MSJ_mass_vs_MdSJ_CR_Suu5TeV_chi1p5TeV->Write();
  outFile.Close();






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


  TH2F *h_MSJ1_vs_MSJ2_SR_QCD = (TH2F*)f3->Get("h_MSJ1_vs_MSJ2_SR");
  TH2F *h_MSJ1_vs_MSJ2_SR_TTbar = (TH2F*)f11->Get("h_MSJ1_vs_MSJ2_SR");

  h_MSJ1_vs_MSJ2_SR_QCD->Draw("colz");
  auto fa1 = new TF1("fa1","x",0,3500);
  fa1->Draw("same");
  c1->SaveAs("/home/ethan/Documents/plots/h_MSJ1_vs_MSJ2_SR_QCD.png");


  h_MSJ1_vs_MSJ2_SR_TTbar->Draw("colz");
  fa1->Draw("same");
  c1->SaveAs("/home/ethan/Documents/plots/h_MSJ1_vs_MSJ2_SR_TTbar.png");

  ////////////////////////////////////////SR TH2 stack plot///////////////////////////////////////
  //go from 500 to 3000 in SJ mass (y) and 1200 to 9500 in diSJ mass, goes in steps of 300 in y and 400 in x

  //unwrap TH2 QCD///////////////
  //std::string binNumbers[440];
  for(int iii =0;iii<20;iii++)
    for(int jjj=0; jjj<22;jjj++)
    {
      int binToUse = jjj*20+iii;
      auto str = std::to_string(jjj); 

      h_MSJ_mass_vs_MdSJ_DT_unwrapped_QCD->SetBinContent(binToUse,h_QCD_combined_TH2->GetBinContent(jjj,iii));
      //if(binToUse%5 == 0)h_MSJ_mass_vs_MdSJ_DT_unwrapped_QCD->GetXaxis()->SetBinLabel(binToUse,str.c_str());

    }
  h_MSJ_mass_vs_MdSJ_DT_unwrapped_QCD->Draw("HIST");
  c1->SaveAs("/home/ethan/Documents/plots/h_MSJ_mass_vs_MdSJ_DT_unwrapped_QCD.png");

  ////////////////////////////
  //unwrap TH2 TTbar///////////////
  for(int iii =0;iii<20;iii++)
    for(int jjj=0; jjj<22;jjj++)
    {
      int binToUse = jjj*20+iii;
      auto str = std::to_string(jjj); 

      h_MSJ_mass_vs_MdSJ_DT_unwrapped_TTbar->SetBinContent(binToUse,h_TTBar_combined_TH2->GetBinContent(jjj,iii));
      //if(binToUse%5 == 0)h_MSJ_mass_vs_MdSJ_DT_unwrapped_TTbar->GetXaxis()->SetBinLabel(binToUse,str.c_str());
    }
  h_MSJ_mass_vs_MdSJ_DT_unwrapped_TTbar->Draw("HIST");
  c1->SaveAs("/home/ethan/Documents/plots/h_MSJ_mass_vs_MdSJ_DT_unwrapped_QCD.png"); 

  ////////////////////////////
  THStack *hs_TH2_unwrapped = new THStack("hs_TH2_unwrapped","SR QCD and TTbar contributions to unwrapped M_{SJ} vs M_{diSJ}");
  h_MSJ_mass_vs_MdSJ_DT_unwrapped_TTbar->SetFillColor(kYellow);
  h_MSJ_mass_vs_MdSJ_DT_unwrapped_QCD->SetFillColor(kRed);
  hs_TH2_unwrapped->Add(h_MSJ_mass_vs_MdSJ_DT_unwrapped_QCD);
  hs_TH2_unwrapped->Add(h_MSJ_mass_vs_MdSJ_DT_unwrapped_TTbar);

//  hs->Add(h_WJets_combined);
  hs_TH2_unwrapped->Draw("HIST");

   auto legend = new TLegend(0.6,0.25,0.85,0.4);
   legend->SetHeader("","C"); // option "C" allows to center the header
   legend->AddEntry(h_MSJ_mass_vs_MdSJ_DT_unwrapped_TTbar,"TTToHadronic","f");
   legend->AddEntry(h_MSJ_mass_vs_MdSJ_DT_unwrapped_QCD,"QCD (HT1500toInf)","f");
   legend->Draw();
  c1->SaveAs("/home/ethan/Documents/plots/h_unwrapped_TH2_stacked_SR.png"); 
  //////////////////////////////////////////////////////////////////////////////////////////////////////


  /////////////TTbar control region stuff
  TH2F *h_MSJ_mass_vs_MdSJ_CRTTbar = (TH2F*)f11->Get("h_MSJ_mass_vs_MdSJ_CRTTbar");
  h_MSJ_mass_vs_MdSJ_CRTTbar->Scale(h_TTToHadronic_SF);
  h_MSJ_mass_vs_MdSJ_CRTTbar->Draw("colz");
  c1->SaveAs("/home/ethan/Documents/plots/h_MSJ_mass_vs_MdSJ_CRTTbar.png"); 


  
  ////////////////////////////////////////CR TH2 stack plot///////////////////////////////////////
  //go from 500 to 3000 in SJ mass (y) and 1200 to 9500 in diSJ mass, goes in steps of 300 in y and 400 in x

  //unwrap TH2 QCD///////////////
  //std::string binNumbers[440];
  for(int iii =0;iii<20;iii++)
    for(int jjj=0; jjj<22;jjj++)
    {
      int binToUse = jjj*20+iii;
      auto str = std::to_string(jjj); 

      h_MSJ_mass_vs_MdSJ_CR_unwrapped_QCD->SetBinContent(binToUse,h_QCD_combined_CR_TH2->GetBinContent(jjj,iii));
    }
  h_MSJ_mass_vs_MdSJ_CR_unwrapped_QCD->Draw("HIST");
  c1->SaveAs("/home/ethan/Documents/plots/h_MSJ_mass_vs_MdSJ_CR_unwrapped_QCD.png");

  ////////////////////////////
  //unwrap TH2 TTbar///////////////
  for(int iii =0;iii<20;iii++)
    for(int jjj=0; jjj<22;jjj++)
    {
      int binToUse = jjj*20+iii;
      auto str = std::to_string(jjj); 

      h_MSJ_mass_vs_MdSJ_CR_unwrapped_TTbar->SetBinContent(binToUse,h_TTBar_combined_CR_TH2->GetBinContent(jjj,iii));
    }
  h_MSJ_mass_vs_MdSJ_CR_unwrapped_TTbar->Draw("HIST");
  c1->SaveAs("/home/ethan/Documents/plots/h_MSJ_mass_vs_MdSJ_CR_unwrapped_QCD.png"); 

  ////////////////////////////
  THStack *hs_TH2_unwrapped_CR = new THStack("hs_TH2_CR_unwrapped","CR QCD and TTbar contributions to unwrapped M_{SJ} vs M_{diSJ}");
  h_MSJ_mass_vs_MdSJ_CR_unwrapped_TTbar->SetFillColor(kYellow);
  h_MSJ_mass_vs_MdSJ_CR_unwrapped_QCD->SetFillColor(kRed);
  hs_TH2_unwrapped_CR->Add(h_MSJ_mass_vs_MdSJ_CR_unwrapped_QCD);
  hs_TH2_unwrapped_CR->Add(h_MSJ_mass_vs_MdSJ_CR_unwrapped_TTbar);

//  hs->Add(h_WJets_combined);
  hs_TH2_unwrapped_CR->Draw("HIST");

   auto legend2 = new TLegend(0.6,0.25,0.85,0.4);
   legend2->SetHeader("","C"); // option "C" allows to center the header
   legend2->AddEntry(h_MSJ_mass_vs_MdSJ_CR_unwrapped_TTbar,"TTToHadronic","f");
   legend2->AddEntry(h_MSJ_mass_vs_MdSJ_CR_unwrapped_QCD,"QCD (HT1500toInf)","f");
   legend2->Draw();
    c1->SaveAs("/home/ethan/Documents/plots/h_unwrapped_TH2_stacked_CR.png"); 
  ///////////////////////////////////////////////////////////////////////////////////////////////////////





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

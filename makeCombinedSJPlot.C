#include <iostream>
#include <string>
#include "TLorentzVector.h"
#include "TRatioPlot.h"
#include "THStack.h"
using namespace std;

void makeCombinedSJPlot()
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


  TFile *f1 = new TFile("/home/ethan/Documents/cutBasedLessGeometric/ClusteringAlgorithm_MSuu8TeV-MChi3TeV_cutbased_output.root");
  TFile *f2 = new TFile("/home/ethan/Documents/cutBasedLessGeometric/ClusteringAlgorithm_MSuu8TeV-MChi1TeV_cutbased_output.root");
  TFile *f3 = new TFile("/home/ethan/Documents/cutBasedLessGeometric/ClusteringAlgorithm_MSuu5TeV-MChi1p5TeV_cutbased_output.root");   //need to add these two together
  //TFile *f9 = new TFile("/home/ethan/Documents/WJetsToLNu_combined_processed.root");
  //TFile *f10 = new TFile("/home/ethan/Documents/WJet_QQ_combined_processed.root");
  TFile *f4 = new TFile("/home/ethan/Documents/cutBasedLessGeometric/ClusteringAlgorithm_MSuu6TeV-MChi1TeV_cutbased_output.root");
  TFile *f5 = new TFile("/home/ethan/Documents/cutBasedLessGeometric/ClusteringAlgorithm_MSuu7TeV-MChi1TeV_cutbased_output.root");
  TFile *f6 = new TFile("/home/ethan/Documents/cutBasedLessGeometric/ClusteringAlgorithm_MSuu8TeV-MChi2TeV_cutbased_output.root");
  TFile *f7 = new TFile("/home/ethan/Documents/cutBasedLessGeometric/ClusteringAlgorithm_MSuu4TeV-MChi1TeV_cutbased_output.root");

/*
ClusteringAlgorithm_MSuu8TeV-MChi3TeV_cutbased_output.root
-rw-r--r-- 1 ethan ethan 18K Nov  9 15:07 ClusteringAlgorithm_MSuu8TeV-MChi2TeV_cutbased_output.root
-rw-r--r-- 1 ethan ethan 18K Nov  9 15:07 ClusteringAlgorithm_MSuu8TeV-MChi1TeV_cutbased_output.root
-rw-r--r-- 1 ethan ethan 18K Nov  9 15:07 ClusteringAlgorithm_MSuu7TeV-MChi1TeV_cutbased_output.root
-rw-r--r-- 1 ethan ethan 18K Nov  9 15:07 ClusteringAlgorithm_MSuu7TeV-MChi2TeV_cutbased_output.root
-rw-r--r-- 1 ethan ethan 17K Nov  9 15:07 ClusteringAlgorithm_MSuu6TeV-MChi1p5TeV_cutbased_output.root
-rw-r--r-- 1 ethan ethan 17K Nov  9 15:07 ClusteringAlgorithm_MSuu6TeV-MChi1TeV_cutbased_output.root
-rw-r--r-- 1 ethan ethan 16K Nov  9 15:08 ClusteringAlgorithm_MSuu5TeV-MChi1p5TeV_cutbased_output.root
-rw-r--r-- 1 ethan ethan 17K Nov  9 15:08 ClusteringAlgorithm_MSuu5TeV-MChi1TeV_cutbased_output.root


8 and 1  = 8 and 2
8 and 3
5 and 1p5 
6 and 1
7 and 1

*/
  TCanvas *c1 = new TCanvas("c1","",400,20, 1500,1500);
  gStyle->SetOptStat(0);

  TH1F *h_SJ_mass_Suu8_chi3   = (TH1F*)f1->Get("h_SJ_mass");
  TH1F *h_SJ_mass_Suu8_chi1   = (TH1F*)f2->Get("h_SJ_mass");
  TH1F *h_SJ_mass_Suu7_chi1   = (TH1F*)f5->Get("h_SJ_mass");
  TH1F *h_SJ_mass_Suu6_chi1   = (TH1F*)f4->Get("h_SJ_mass");
  TH1F *h_SJ_mass_Suu5_chi1p5 = (TH1F*)f3->Get("h_SJ_mass");
  TH1F *h_SJ_mass_Suu4_chi1 =   (TH1F*)f7->Get("h_SJ_mass");

  h_SJ_mass_Suu8_chi3->Draw();
  h_SJ_mass_Suu8_chi3->GetXaxis()->SetRangeUser(0,4250);
  h_SJ_mass_Suu8_chi3->SetTitle("Reconstructed Superjet (VLQ) Mass");
  h_SJ_mass_Suu8_chi3->GetXaxis()->SetTitle("Mass [GeV]");
  h_SJ_mass_Suu8_chi3->GetYaxis()->SetTitle("Events / 80 GeV");


  h_SJ_mass_Suu8_chi3->GetYaxis()->SetRangeUser(0., 700);
  h_SJ_mass_Suu8_chi3->GetYaxis()->SetTitleOffset(1.35);
  h_SJ_mass_Suu8_chi3->GetYaxis()->SetLabelSize(0.015);
  h_SJ_mass_Suu8_chi3->SetLineColor(kRed);
  h_SJ_mass_Suu8_chi3->SetLineWidth(5);
  h_SJ_mass_Suu8_chi1->SetLineWidth(5);
  h_SJ_mass_Suu4_chi1->SetLineWidth(5);
  h_SJ_mass_Suu6_chi1->SetLineWidth(5);

  h_SJ_mass_Suu8_chi1->SetLineColor(kBlue);
  h_SJ_mass_Suu6_chi1->SetLineColor(kGreen);
  h_SJ_mass_Suu4_chi1->SetLineColor(kOrange);
  h_SJ_mass_Suu8_chi1->Draw("SAME");
  //h_SJ_mass_Suu7_chi1->Draw("SAME");
  h_SJ_mass_Suu6_chi1->Draw("SAME");
  h_SJ_mass_Suu4_chi1->Draw("SAME");
  //h_SJ_mass_Suu5_chi1p5->Draw("SAME");


   auto legend = new TLegend(0.90,0.75,0.4,0.90);
   legend->SetHeader("","C"); // option "C" allows to center the header
   legend->AddEntry(h_SJ_mass_Suu8_chi3,"M_{S_{uu}}=8 TeV, M_{chi} = 3 TeV","f");
   legend->AddEntry(h_SJ_mass_Suu8_chi1,"M_{S_{uu}}=8 TeV, M_{chi} = 2 TeV","f");
   legend->AddEntry(h_SJ_mass_Suu6_chi1,"M_{S_{uu}}=6 TeV, M_{chi} = 1.5 TeV","f");
   legend->AddEntry(h_SJ_mass_Suu4_chi1,"M_{S_{uu}}=4 TeV, M_{chi} = 1 TeV","f");
   legend->Draw();
  c1->SaveAs("h_SJ_mass_combined.png"); 

}

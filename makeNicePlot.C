#include <iostream>
#include <string>
#include "TLorentzVector.h"
#include "TRatioPlot.h"
#include "THStack.h"
using namespace std;


void makeNicePlot()
{

  TFile *f1 = new TFile("clustAlgBR_ttbar_processed_.root");
  TFile *f2 = new TFile("processed_QCD/HT1000to1500/clustAlg_QCD_HT1000to1500_processed.root");
  TFile *f3 = new TFile("processed_QCD/HT1500to2000/clustAlg_QCD_HT1500to2000_processed.root");
  TFile *f4 = new TFile("processed_QCD/HT2000toInf/clustAlg_QCD_HT2000toInf_processed.root");
  TFile *f5 = new TFile("clusteringProcessed/ClusteringAlgorithm_Suu4TeV_chi1p5TeV_ALLDECAY_processed.root");
  TCanvas *c1 = new TCanvas("c1","",400,20, 1500,1500);
  //gPad->SetLogy();

  TH1F *h_nbtaggedAk4 =  (TH1F*)f3->Get("h_nbtaggedAk4");   //QCD 2000 to Inf 

  TText T; T.SetTextFont(30); T.SetTextAlign(22);
  gStyle->SetOptStat(0);
  h_nbtaggedAk4->Draw("HIST");

  TPaveText *pt = new TPaveText(0.9,0.45,0.70,0.55,"NDC");
  pt->SetTextSize(0.0275);
  pt->SetFillColor(0);
  pt->SetTextAlign(14);
  pt->AddText("Simulated QCD,");
  pt->AddText("H_{T} > 2000 GeV");
  pt->Draw();


 TText *CMSLabel = new TText();
 CMSLabel-> SetNDC();
 CMSLabel -> SetTextFont(1);
 CMSLabel -> SetTextColor(1);
 CMSLabel -> SetTextSize(0.0425);
 CMSLabel -> SetTextAlign(22);
 CMSLabel -> SetTextAngle(0);
 CMSLabel -> DrawText(0.215, 0.93, "CMS");
 CMSLabel->Draw();

 TText *simLabel = new TText();
 simLabel-> SetNDC();
 simLabel -> SetTextFont(52);
 simLabel -> SetTextColor(1);
 simLabel -> SetTextSize(0.028);
 simLabel -> SetTextAlign(22);
 simLabel -> SetTextAngle(0);
 simLabel -> DrawText(0.3925, 0.93, "Simulation Preliminary");
 simLabel->Draw();


/*
 TString lumistuff =  "59.83 fb^{-1} (13 TeV)";

  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);    
  latex.SetTextFont(42);
  latex.SetTextAlign(31); 
  latex.SetTextSize(0.045);    
  latex.DrawLatex(0.935,0.92,lumistuff);
*/
 TText *xlabelSJ = new TText();
 xlabelSJ-> SetNDC();
 //xlabel -> SetTextFont(52);
 xlabelSJ -> SetTextColor(1);
 xlabelSJ -> SetTextSize(0.038);
 xlabelSJ -> SetTextAlign(22);
 xlabelSJ -> SetTextAngle(0);
 xlabelSJ -> DrawText(0.78, 0.03, "# b tagged AK4 jets");
 xlabelSJ->Draw();

  c1->SaveAs("h_nbtaggedAk4_QCD2000toInf.png"); 

 
}
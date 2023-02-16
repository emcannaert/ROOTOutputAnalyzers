#include <iostream>
#include <string>
#include "TLorentzVector.h"
#include "TRatioPlot.h"
#include "THStack.h"
using namespace std;

void makeVsSuperimposePlot2()
{

  TFile *f1 = new TFile("/home/ethan/Documents/clustAlg_Suu8TeV_chi3TeV_processed.root");
  TFile *f2 = new TFile("/home/ethan/Documents/clustAlg_QCD2000toInf_processed.root");
  TCanvas *c1 = new TCanvas("c1","",400,20, 2000,2000);
  //gPad->SetLogy();
  gStyle->SetOptStat(0);

  TGraph *h_mChichi_vs_Mchi_SJ1 =  (TGraph*)f1->Get("h_Mchichi_vs_Mchi_SJ1");
  TGraph *h_Mchichi_Mchi_SJ1 = (TGraph*)f2->Get("h_Mchichi_vs_Mchi_SJ1");


  h_mChichi_vs_Mchi_SJ1->SetMarkerStyle(22);
  h_mChichi_vs_Mchi_SJ1->SetMarkerColor(kBlue);
  h_mChichi_vs_Mchi_SJ1->SetMarkerSize(2.5);
  h_mChichi_vs_Mchi_SJ1->SetDrawOption("P");


  //h_mChichi_vs_Mchi_SJ1->GetXaxis()->SetLimits(0.0,6000.);
  //h_mChichi_vs_Mchi_SJ1->GetYaxis()->SetLimits(0.0,6000.);
  //h_mChichi_vs_Mchi_SJ1->Draw("AP*");

  h_Mchichi_Mchi_SJ1->SetMarkerStyle(22);
  h_Mchichi_Mchi_SJ1->SetMarkerSize(2.5);
  h_Mchichi_Mchi_SJ1->SetMarkerColor(kRed);
  h_Mchichi_Mchi_SJ1->SetDrawOption("P");

  //h_Mchichi_Mchi_SJ1->GetXaxis()->SetLimits(0.0,6000.);
  //h_Mchichi_Mchi_SJ1->GetYaxis()->SetLimits(0.0,6000.);
  //h_Mchichi_Mchi_SJ1->Draw("P* same");


  auto mg = new TMultiGraph();
  mg->SetTitle("M_{chi chi} vs SuperJet 1 M_{chi}");

  mg->Add(h_Mchichi_Mchi_SJ1); 
  mg->Add(h_mChichi_vs_Mchi_SJ1);
  mg->Draw("AP");
  mg->GetXaxis()->SetLimits(0,4000.);
  mg->SetMinimum(0.);
  mg->SetMaximum(9000.);
  mg->GetXaxis()->SetTitle("M_{chi} [GeV]");
  mg->GetYaxis()->SetTitle("M_{chi chi} [GeV]");
  mg->GetYaxis()->SetTitleOffset(2.2);
  mg->GetYaxis()->SetTitleSize(0.025);
  mg->GetXaxis()->SetTitleOffset(2.0);
  mg->GetXaxis()->SetTitleSize(0.025);
  gPad->Modified();
  gPad->Update();


  TLegend *legend3 = new TLegend(0.60,0.15,0.85,0.25);
  legend3->AddEntry(h_mChichi_vs_Mchi_SJ1,"S_{uu} [4 TeV] -> Chi Chi [850GeV]","p");
  legend3->AddEntry(h_Mchichi_Mchi_SJ1,"2018 UL QCD MC (HT > 2000 GeV)","p");
  legend3->Draw();

  c1->SaveAs("M_chichi_vs_Mchi_superposition_Suu4TeV_chi850GeV.png");  
}

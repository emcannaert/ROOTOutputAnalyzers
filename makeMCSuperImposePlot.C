#include <iostream>
#include <string>
#include "TLorentzVector.h"
#include "TRatioPlot.h"
#include "THStack.h"
using namespace std;

void makeMCSuperImposePlot()
{

  TFile *f1 = new TFile("/home/ethan/Documents/clustAlg_Suu8TeV_chi3TeV_processed_cos70.root");
  TFile *f2 = new TFile("/home/ethan/Documents/clustAlg_Suu8TeV_chi3TeV_processed_cos75.root");
  TFile *f3 = new TFile("/home/ethan/Documents/clustAlg_Suu8TeV_chi3TeV_processed_cos80.root");
  TFile *f4 = new TFile("/home/ethan/Documents/clustAlg_Suu8TeV_chi3TeV_processed_cos85.root");

  TCanvas *c1 = new TCanvas("c1","",400,20, 1500,1500);
  //gPad->SetLogy();
  gStyle->SetOptStat(0);

  TH1F *h_mass_cos70 = (TH1F*)f1->Get("h_SJ_mass_100");
  TH1F *h_mass_cos75 = (TH1F*)f2->Get("h_SJ_mass_100");
  TH1F *h_mass_cos80 = (TH1F*)f3->Get("h_SJ_mass_100");
  TH1F *h_mass_cos85 = (TH1F*)f4->Get("h_SJ_mass_100");



  h_mass_cos85->SetTitle("Mass ofs Signal MC SuperJets (Different Sorting cos thresholds) [59.83 fb^{-1}]");
  h_mass_cos85->SetLineColor(kBlue);
  h_mass_cos85->SetMarkerColor(kBlue);
  h_mass_cos85->SetLineWidth(3);
  h_mass_cos85->Draw("HIST");

  h_mass_cos80->SetLineColor(kYellow);
  h_mass_cos80->SetMarkerColor(kYellow);
  h_mass_cos80->SetLineWidth(3);
  h_mass_cos80->Draw("HIST same");

  h_mass_cos75->SetLineColor(kRed);
  h_mass_cos75->SetMarkerColor(kRed);
  h_mass_cos75->SetLineWidth(3);
  h_mass_cos75->Draw("HIST same");

  h_mass_cos70->SetLineColor(kGreen);
  h_mass_cos70->SetMarkerColor(kGreen);
  h_mass_cos70->SetLineWidth(3);
  h_mass_cos70->Draw("HIST same");

  TLegend *legend = new TLegend(1.0,0.8,0.48,0.9);
  legend->AddEntry(h_mass_cos70,"Sig MC cos 70","l");
  legend->AddEntry(h_mass_cos75,"Sig MC cos 75","l");
  legend->AddEntry(h_mass_cos80,"Sig MC cos 80","l");
  legend->AddEntry(h_mass_cos85,"Sig MC cos 85","l");
  legend->Draw();

  c1->SaveAs("SJ_MC_mass_100_superimpose.png"); 



}
  
#include <iostream>
#include <string>
#include "TLorentzVector.h"
#include "TRatioPlot.h"
#include "THStack.h"
using namespace std;

void makeVsSuperimposePlot()
{

  TFile *f1 = new TFile("/Users/ethan/Documents/rootFiles/cutflowPlots/cutflow_plot_histograms_QCDMC2000toInf_2018.root");
  TCanvas *c1 = new TCanvas("c1","",400,20, 2000,2000);
  gStyle->SetOptStat(0);

  TGraph *h_MC_SJ_mass_versus =  (TGraph*)f1->Get("h_SJ_mass_versus");
  TGraph *h_QCD_SJ_mass_versus = (TGraph*)f2->Get("h_SJ_mass_versus");


  h_MC_SJ_mass_versus->SetMarkerStyle(22);
  h_MC_SJ_mass_versus->SetMarkerColor(kBlue);
  h_MC_SJ_mass_versus->SetMarkerSize(2.5);
  h_MC_SJ_mass_versus->SetDrawOption("P");


  //h_MC_SJ_mass_versus->GetXaxis()->SetLimits(0.0,6000.);
  //h_MC_SJ_mass_versus->GetYaxis()->SetLimits(0.0,6000.);
  //h_MC_SJ_mass_versus->Draw("AP*");

  h_QCD_SJ_mass_versus->SetMarkerStyle(22);
  h_QCD_SJ_mass_versus->SetMarkerSize(2.5);
  h_QCD_SJ_mass_versus->SetMarkerColor(kRed);
  h_QCD_SJ_mass_versus->SetDrawOption("P");

  //h_QCD_SJ_mass_versus->GetXaxis()->SetLimits(0.0,6000.);
  //h_QCD_SJ_mass_versus->GetYaxis()->SetLimits(0.0,6000.);
  //h_QCD_SJ_mass_versus->Draw("P* same");


  auto mg = new TMultiGraph();
  mg->SetTitle("SuperJet 1 Mass vs SuperJet 2 Mass");

  mg->Add(h_QCD_SJ_mass_versus); 
  mg->Add(h_MC_SJ_mass_versus);
  mg->Draw("AP");
  mg->GetXaxis()->SetLimits(0,6000.);
  mg->SetMinimum(0.);
  mg->SetMaximum(6000.);
  mg->GetXaxis()->SetTitle("SuperJet 2 Mass [GeV]");
  mg->GetYaxis()->SetTitle("SuperJet 1 Mass [GeV]");
  mg->GetYaxis()->SetTitleOffset(2.2);
  mg->GetYaxis()->SetTitleSize(0.025);
  mg->GetXaxis()->SetTitleOffset(2.0);
  mg->GetXaxis()->SetTitleSize(0.025);
  gPad->Modified();
  gPad->Update();


  TLegend *legend3 = new TLegend(1.0,0.8,0.48,0.9);
  legend3->AddEntry(h_MC_SJ_mass_versus,"S_{uu} -> Chi Chi","p");
  legend3->AddEntry(h_QCD_SJ_mass_versus,"2018 UL QCD MC (HT > 2000 GeV)","p");
  legend3->Draw();

  c1->SaveAs("superJet_vs_superposition.png");  
}

#include <iostream>
#include <string>
#include "TLorentzVector.h"
#include "TRatioPlot.h"
#include "THStack.h"
#include <string>
#include <TH2F>
using namespace std;

// creates the root file that will be given to combine, here using an 8 TeV Suu and 3 TeV chi with QCD and TTbar MC as BRs. Not sure what to do with data ...
// This is set up to do ONLY the QCD control region ... trying to make it more generic created annoying errors

//need to do this for all signal mass points
void compareSystematics()
{

  TCanvas *c1 = new TCanvas("c1","",400,20, 1500,1500);

  TFile *f1 = new TFile("/home/ethan/Documents/rootFiles/processedRootFiles/ClusteringAlgorithmBR_JECup_output_processed.root");
  TFile *f2 = new TFile("/home/ethan/Documents/rootFiles/processedRootFiles/ClusteringAlgorithmBR_data_output_processed.root"); 
  TFile *f3 = new TFile("/home/ethan/Documents/rootFiles/processedRootFiles/ClusteringAlgorithmBR_JECdown_output_processed.root");

  //c1->SetLogy();
  TH1F *  h_JECup   = (TH1F*)f1->Get("h_SJ_mass_JEC");
  TH1F *  h_JECnom  = (TH1F*)f2->Get("h_SJ_mass_JEC");
  TH1F *  h_JECdown = (TH1F*)f3->Get("h_SJ_mass_JEC");


  h_JECup->SetLineColor(kBlue);
  h_JECnom->SetLineColor(kRed);
  h_JECdown->SetLineColor(kGreen);

  h_JECup->SetLineWidth(3);
  h_JECnom->SetLineWidth(3);
  h_JECdown->SetLineWidth(3);

  h_JECup->Draw("HIST");
  h_JECnom->Draw("SAME");
  h_JECdown->Draw("SAME");

  c1->SaveAs("h_JEC_upNomDown.png"); 


}
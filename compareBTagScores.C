#include <iostream>
#include <string>
#include "TLorentzVector.h"
#include "TRatioPlot.h"
#include "THStack.h"
using namespace std;

void compareBTagScores()
{


  std::cout << "Open Files" << std::endl;
  TFile *f1 = new TFile("/home/ethan/Documents/QCD_HT2000toInf_combined_cutbased_processed_TEST_2018.root");   //need to add these two together

  TH1F* h_deepFlavour_score_highpt        =      (TH1F*)f1->Get("h_deepFlavour_score_highpt");
  TH1F* h_deepFlavour_score            =      (TH1F*)f1->Get("h_deepFlavour_score");
  
  h_deepFlavour_score_highpt->Scale(1./h_deepFlavour_score_highpt->Integral());
    h_deepFlavour_score->Scale(1./h_deepFlavour_score->Integral());

  h_deepFlavour_score_highpt->SetLineColor(kRed);
  h_deepFlavour_score_highpt->SetLineWidth(6);

  h_deepFlavour_score->SetLineColor(kBlue);
  h_deepFlavour_score->SetLineWidth(6);



  TCanvas *c1 = new TCanvas("c1","",400,20, 1500,1500);
  gPad->SetLogy();

  h_deepFlavour_score->Draw();
  h_deepFlavour_score_highpt->Draw("SAME");
  h_deepFlavour_score->SetStats(0);
  h_deepFlavour_score_highpt->SetStats(0);

  TLegend *legend = new TLegend(1.0,0.8,0.48,0.9);
  legend->AddEntry(h_deepFlavour_score,"All AK4 jets","l");
  legend->AddEntry(h_deepFlavour_score_highpt,"AK4 w/ p_{T} > 1 TeV","l");

  legend->Draw();
  //gStyle->SetOptStat(0);

  c1->SaveAs("h_deepFlavour_scores.png"); 


}

#include <iostream>
#include <string>
#include "TLorentzVector.h"
#include "TRatioPlot.h"
#include "THStack.h"
using namespace std;

void makeAntiTagDoubleTagComparison()
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


  //TFile *f1 = new TFile("/home/ethan/Documents/QCD_HT1000to1500_combined_processed.root");
  TFile *f2 = new TFile("/home/ethan/Documents/QCD_HT1500to2000_combined_cutbased_processed.root");
  TFile *f3 = new TFile("/home/ethan/Documents/QCD_HT2000toInf_combined_cutbased_processed.root");   //need to add these two together

  //TH2F *h_MSJ_mass_vs_MdSJ_HT1000to1500_antitag  = (TH2F*)f1->Get("h_MSJ_mass_vs_MdSJ");
  TH2F *h_MSJ_mass_vs_MdSJ_HT1500to2000_antitag  = (TH2F*)f2->Get("h_MSJ_mass_vs_MdSJ");
  TH2F *h_MSJ_mass_vs_MdSJ_HT2000toInf_antitag   = (TH2F*)f3->Get("h_MSJ_mass_vs_MdSJ");

  //TH2F *h_MSJ_mass_vs_MdSJ_HT1000to1500_doubletag  = (TH2F*)f1->Get("h_MSJ_mass_vs_MdSJ_doubleTag");
  TH2F *h_MSJ_mass_vs_MdSJ_HT1500to2000_doubletag  = (TH2F*)f2->Get("h_MSJ_mass_vs_MdSJ_doubleTag");
  TH2F *h_MSJ_mass_vs_MdSJ_HT2000toInf_doubletag   = (TH2F*)f3->Get("h_MSJ_mass_vs_MdSJ_doubleTag");


  //h_MSJ_mass_vs_MdSJ_HT1000to1500_antitag->Scale(QCD1000to1500_SF);
  h_MSJ_mass_vs_MdSJ_HT1500to2000_antitag->Scale(QCD1500to2000_SF);
  h_MSJ_mass_vs_MdSJ_HT2000toInf_antitag->Scale(QCD2000toInf_SF);

  //h_MSJ_mass_vs_MdSJ_HT1000to1500_doubletag->Scale(QCD1000to1500_SF);
  h_MSJ_mass_vs_MdSJ_HT1500to2000_doubletag->Scale(QCD1500to2000_SF);
  h_MSJ_mass_vs_MdSJ_HT2000toInf_doubletag->Scale(QCD2000toInf_SF);

  TCanvas *c1 = new TCanvas("c1","",400,20, 1500,1500);

  TH2F *h_QCD_combined_antitag = new TH2F(*h_MSJ_mass_vs_MdSJ_HT1500to2000_antitag);
  h_QCD_combined_antitag->Add(h_MSJ_mass_vs_MdSJ_HT2000toInf_antitag);
  h_QCD_combined_antitag->Draw("colz");
  c1->SaveAs("h_QCD_combined_antitag.png"); 

  //h_QCD_combined_antitag->Add(h_MSJ_mass_vs_MdSJ_HT2000toInf_antitag);

  TH2F *h_QCD_combined_doubletag = new TH2F(*h_MSJ_mass_vs_MdSJ_HT1500to2000_doubletag);
  h_QCD_combined_doubletag->Add(h_MSJ_mass_vs_MdSJ_HT2000toInf_doubletag);
  h_QCD_combined_doubletag->Draw("colz");
  c1->SaveAs("h_QCD_combined_doubletag.png"); 

 // h_QCD_combined_doubletag->Add(h_MSJ_mass_vs_MdSJ_HT2000toInf_doubletag);


  //gPad->SetLogz();


  TH2F *h_MSJ_mass_vs_MdSJ_diff = new TH2F("h_MSJ_mass_vs_MdSJ_diff","Dfference between Anti-tagged and Double-tagged M_{SJ} vs M_{diSJ} ; diSuperjet mass [GeV];superjet mass", 25,0, 10000, 20, 0, 6000);
  h_MSJ_mass_vs_MdSJ_diff->GetYaxis()->SetTitleOffset(1.35);
  h_MSJ_mass_vs_MdSJ_diff->GetYaxis()->SetLabelSize(0.015);
  
  //h_MSJ_mass_vs_MdSJ_diff->Add(h_QCD_combined_doubletag);
  //h_MSJ_mass_vs_MdSJ_diff->Add(h_QCD_combined_antitag,-1.);
  for(int iii = 0; iii<h_MSJ_mass_vs_MdSJ_diff->GetNbinsX(); iii++)
  {
    for(int jjj=0;jjj<h_MSJ_mass_vs_MdSJ_diff->GetNbinsY();jjj++)
    {
      if(  ( (h_QCD_combined_antitag->GetBinContent(iii,jjj) < 1e-15)&&(h_QCD_combined_doubletag->GetBinContent(iii,jjj))> 1e-15 ) )
      {
        h_MSJ_mass_vs_MdSJ_diff->SetBinContent(iii,jjj,1.0);
      }
      else if(( (h_QCD_combined_antitag->GetBinContent(iii,jjj) > 1e-15)&&(h_QCD_combined_doubletag->GetBinContent(iii,jjj)) < 1e-15 )  )
      {
        h_MSJ_mass_vs_MdSJ_diff->SetBinContent(iii,jjj,-1.0);
      }
    }
  }

  h_MSJ_mass_vs_MdSJ_diff->Draw("colz");
  c1->SaveAs("h_MSJ_mass_vs_MdSJ_diff.png"); 


  TH2F *h_MSJ_mass_vs_MdSJ_overlay = new TH2F("h_MSJ_mass_vs_MdSJ_overlay","Overlay of Anti-tagged and Double-tagged M_{SJ} vs M_{diSJ} ; diSuperjet mass [GeV];superjet mass", 25,0, 10000, 20, 0, 6000);
  h_MSJ_mass_vs_MdSJ_overlay->GetYaxis()->SetTitleOffset(1.35);
  h_MSJ_mass_vs_MdSJ_overlay->GetYaxis()->SetLabelSize(0.015);
  
  //h_MSJ_mass_vs_MdSJ_diff->Add(h_QCD_combined_doubletag);
  //h_MSJ_mass_vs_MdSJ_diff->Add(h_QCD_combined_antitag,-1.);
  for(int iii = 0; iii<h_MSJ_mass_vs_MdSJ_overlay->GetNbinsX(); iii++)
  {
    for(int jjj=0;jjj<h_MSJ_mass_vs_MdSJ_overlay->GetNbinsY();jjj++)
    {
      if(  ( (h_QCD_combined_antitag->GetBinContent(iii,jjj) < 1e-15)&&(h_QCD_combined_doubletag->GetBinContent(iii,jjj))> 1e-15 ) )
      {
        h_MSJ_mass_vs_MdSJ_overlay->SetBinContent(iii,jjj,3.0);
      }
      else if(( (h_QCD_combined_antitag->GetBinContent(iii,jjj) > 1e-15)&&(h_QCD_combined_doubletag->GetBinContent(iii,jjj)) < 1e-15 )  )
      {
        h_MSJ_mass_vs_MdSJ_overlay->SetBinContent(iii,jjj,2.0);
      }
      else if(( (h_QCD_combined_antitag->GetBinContent(iii,jjj) > 1e-15)&&(h_QCD_combined_doubletag->GetBinContent(iii,jjj)) > 1e-15 )  )
      {
        h_MSJ_mass_vs_MdSJ_overlay->SetBinContent(iii,jjj,1.0);
      }
    }
  }

  h_MSJ_mass_vs_MdSJ_overlay->Draw("colz");
  c1->SaveAs("h_MSJ_mass_vs_MdSJ_overlay.png"); 

}

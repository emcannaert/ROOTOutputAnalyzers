#include <iostream>
#include <string>
#include "TLorentzVector.h"
#include "TRatioPlot.h"
#include "THStack.h"
#include <string>
using namespace std;

// creates the root file that will be given to combine, here using an 8 TeV Suu and 3 TeV chi with QCD and TTbar MC as BRs. Not sure what to do with data ...



void prepareCombineRoot()
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

  TH1F* h_MSJ_mass_vs_MdSJ_DT_unwrapped_QCD = new TH1F("QCD","Unwrapped QCD M_{SJ,avg} vs M_{diSJ};; Events / 375x125 GeV",440,0.,440);
  TH1F* h_MSJ_mass_vs_MdSJ_DT_unwrapped_TTbar = new TH1F("TTbar","Unwrapped TTbar M_{SJ,avg} vs M_{diSJ};; Events / 375x125 GeV",440,0.,440);

  //TH1F* h_MSJ_mass_vs_MdSJ_CR_unwrapped_QCD = new TH1F("h_MSJ_mass_vs_MdSJ_CR_unwrapped_QCD","Unwrapped QCD M_{SJ,avg} vs M_{diSJ};; Events / 375x125 GeV",440,0.,440);
  //TH1F* h_MSJ_mass_vs_MdSJ_CR_unwrapped_TTbar = new TH1F("h_MSJ_mass_vs_MdSJ_CR_unwrapped_TTbar","Unwrapped TTbar M_{SJ,avg} vs M_{diSJ};; Events / 375x125 GeV",440,0.,440);


  TFile *f2 = new TFile("/home/ethan/Documents/rootFiles/processedRootFiles/QCD_HT1500to2000_processed.root");
  TFile *f3 = new TFile("/home/ethan/Documents/rootFiles/processedRootFiles/QCD_HT2000toInf_processed.root"); 
  TFile *f11 = new TFile("/home/ethan/Documents/rootFiles/processedRootFiles/TTToHadronic_processed.root");

  TH2F *h_MSJ_mass_vs_MdSJ_SR_HT1500to2000 = (TH2F*)f2->Get("h_MSJ_mass_vs_MdSJ_DT");
  TH2F *h_MSJ_mass_vs_MdSJ_SR_HT2000toInf  = (TH2F*)f3->Get("h_MSJ_mass_vs_MdSJ_DT");
  TH2F *h_MSJ_mass_vs_MdSJ_SR_TTToHadronic = (TH2F*)f11->Get("h_MSJ_mass_vs_MdSJ_DT");

  h_MSJ_mass_vs_MdSJ_SR_HT1500to2000->Scale(QCD1500to2000_SF);
  h_MSJ_mass_vs_MdSJ_SR_HT2000toInf->Scale(QCD2000toInf_SF);
  h_MSJ_mass_vs_MdSJ_SR_TTToHadronic->Scale(h_TTToHadronic_SF);



/*
  TH2F *h_MSJ_mass_vs_MdSJ_CR_HT1500to2000 = (TH2F*)f2->Get("h_MSJ_mass_vs_MdSJ_CR");
  TH2F *h_MSJ_mass_vs_MdSJ_CR_HT2000toInf  = (TH2F*)f3->Get("h_MSJ_mass_vs_MdSJ_CR");
  TH2F *h_MSJ_mass_vs_MdSJ_CR_TTToHadronic = (TH2F*)f11->Get("h_MSJ_mass_vs_MdSJ_CR");

  h_MSJ_mass_vs_MdSJ_CR_HT1500to2000->Scale(QCD1500to2000_SF);
  h_MSJ_mass_vs_MdSJ_CR_HT2000toInf->Scale(QCD2000toInf_SF);
  h_MSJ_mass_vs_MdSJ_CR_TTToHadronic->Scale(h_TTToHadronic_SF);
*/

  TCanvas *c1 = new TCanvas("c1","",400,20, 1500,1500);
  gStyle->SetOptStat(0);



  /////////////////////////////SR TH2////////////////////////////////////////
  TH2F *h_QCD_combined_TH2 = new TH2F(*h_MSJ_mass_vs_MdSJ_SR_HT2000toInf);
  h_QCD_combined_TH2->Add(h_MSJ_mass_vs_MdSJ_SR_HT1500to2000);
  TH2F *h_TTBar_combined_TH2 = new TH2F(*h_MSJ_mass_vs_MdSJ_SR_TTToHadronic);

  //TH2F *h_AllBR_combined_TH2 = new TH2F(*h_QCD_combined_TH2);
  //h_AllBR_combined_TH2->Add(h_TTBar_combined_TH2);

  ///////////////////////////////////////////////////////////////////////////////

  /////////////////////////////CR TH2////////////////////////////////////////
/*  TH2F *h_QCD_combined_CR_TH2 = new TH2F(*h_MSJ_mass_vs_MdSJ_CR_HT2000toInf);
  h_QCD_combined_CR_TH2->Add(h_MSJ_mass_vs_MdSJ_CR_HT1500to2000);
  TH2F *h_TTBar_combined_CR_TH2 = new TH2F(*h_MSJ_mass_vs_MdSJ_CR_TTToHadronic);
  ///////////////////////////////////////////////////////////////////////////
*/
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

}

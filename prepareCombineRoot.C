#include <iostream>
#include <string>
#include "TLorentzVector.h"
#include "TRatioPlot.h"
#include "THStack.h"
#include <string>
using namespace std;

// creates the root file that will be given to combine, here using an 8 TeV Suu and 3 TeV chi with QCD and TTbar MC as BRs. Not sure what to do with data ...
// This is set up to do ONLY the QCD control region ... trying to make it more generic created annoying errors

//need to do this for all signal mass points
void do_Stuff(std::string SuuMass, std::string ChiMass, std::string regionType, double sigScaleFactor)
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


  TFile outFile( ("/home/ethan/Documents/rootFiles/combineRootFiles/SuuToChiChi_MSuu" + SuuMass+ "TeV-MChi"+ChiMass +"TeV_" + regionType + ".root").c_str(),"RECREATE");
  outFile.cd();
  gDirectory->mkdir(regionType.c_str());
  outFile.cd(regionType.c_str());

  TH1F* h_MSJ_mass_vs_MdSJ_unwrapped_QCD   = new TH1F("QCD",  ("Unwrapped QCD M_{SJ,avg} vs M_{diSJ} ("+ regionType +");; Events / 375x125 GeV").c_str(),440,0.,440);
  TH1F* h_MSJ_mass_vs_MdSJ_unwrapped_TTbar = new TH1F("TTbar",("Unwrapped TTbar M_{SJ,avg} vs M_{diSJ} ("+ regionType+");; Events / 375x125 GeV").c_str(),440,0.,440);
  TH1F* h_MSJ_mass_vs_MdSJ_unwrapped_sig   = new TH1F("SuuToChiChi",("Unwrapped SuuToChiChi M_{SJ,avg} vs M_{diSJ} ("+ regionType+");; Events / 375x125 GeV").c_str(),440,0.,440);
  TH1F* h_MSJ_mass_vs_MdSJ_unwrapped_Data  = new TH1F("data_obs", ("Unwrapped Data M_{SJ,avg} vs M_{diSJ} ("+ regionType+");; Events / 375x125 GeV").c_str(),440,0.,440);

  TFile *f2 = new TFile("/home/ethan/Documents/rootFiles/processedRootFiles/QCD_HT1500to2000_processed.root");
  TFile *f3 = new TFile("/home/ethan/Documents/rootFiles/processedRootFiles/QCD_HT2000toInf_processed.root"); 
  TFile *f11 = new TFile("/home/ethan/Documents/rootFiles/processedRootFiles/TTToHadronic_processed.root");
  TFile *f12 = new TFile("/home/ethan/Documents/rootFiles/processedRootFiles/JetHT_2018_combined.root");
  TFile *f13 = new TFile( ("/home/ethan/Documents/rootFiles/signalRootFiles/ClusteringAlgorithm_MSuu"+SuuMass+"TeV-MChi"+ChiMass+"TeV_cutbased_processed.root").c_str());

  TH2F *h_MSJ_mass_vs_MdSJ_HT1500to2000;
  TH2F *h_MSJ_mass_vs_MdSJ_HT2000toInf;
  TH2F *h_MSJ_mass_vs_MdSJ_TTToHadronic;
  TH2F *h_MSJ_mass_vs_MdSJ_sig;
  TH2F *h_MSJ_mass_vs_MdSJ_Data;



/*
  ////////////////// Check scaling with a ratio plot of HT in CR ////////////////////////////

  TCanvas *c1 = new TCanvas("c1","",400,20, 1800,1600);

  TH1F * h_HT_HT1500to2000 = (TH1F*)f2->Get("h_totHT_CR");
  TH1F * h_HT_HT2000toInf  = (TH1F*)f3->Get("h_totHT_CR");
  TH1F * h_HT_TTToHadronic = (TH1F*)f11->Get("h_totHT_CR");
  TH1F * h_HT_Data         = (TH1F*)f12->Get("h_totHT_CR");

  h_HT_HT1500to2000->Scale(QCD1500to2000_SF);
  h_HT_HT2000toInf->Scale(QCD2000toInf_SF);
  h_HT_TTToHadronic->Scale(h_TTToHadronic_SF);

  TH1F *h_HT_BR_combined = new TH1F(*h_HT_HT1500to2000);
  h_HT_BR_combined->Add(h_HT_HT2000toInf);
  h_HT_BR_combined->Add(h_HT_TTToHadronic);

  auto rp_HT = new TRatioPlot(h_HT_Data,h_HT_BR_combined);
  //
  rp_HT->Draw();
  rp_HT->GetLowerRefYaxis()->SetTitle("data/MC ratio");
  rp_HT->GetLowerRefGraph()->SetMaximum(2.);
  rp_HT->GetUpperRefYaxis()->SetTitle("Events");

  c1->SaveAs("tot_HT_ratio.png"); 
*/
  /////////////////////////////////////////////////////////////////////////////////////////////

  if (regionType.find("CR") != std::string::npos)
  {

    h_MSJ_mass_vs_MdSJ_HT1500to2000 = (TH2F*)f2->Get("h_MSJ_mass_vs_MdSJ_CR");
    h_MSJ_mass_vs_MdSJ_HT2000toInf  = (TH2F*)f3->Get("h_MSJ_mass_vs_MdSJ_CR");
    h_MSJ_mass_vs_MdSJ_TTToHadronic = (TH2F*)f11->Get("h_MSJ_mass_vs_MdSJ_CR");
    h_MSJ_mass_vs_MdSJ_sig          = (TH2F*)f13->Get("h_MSJ_mass_vs_MdSJ_CR");
    h_MSJ_mass_vs_MdSJ_Data         = (TH2F*)f12->Get("h_MSJ_mass_vs_MdSJ_CR");
  }
  else if (regionType.find("SR") != std::string::npos)           ////////////// NEED TO CHANGE ALL THE SIGNAL REGION HISTOGRAMS TO BE FOR SR ////////////////
  {
    h_MSJ_mass_vs_MdSJ_HT1500to2000 = (TH2F*)f2->Get("h_MSJ_mass_vs_MdSJ_SR");
    h_MSJ_mass_vs_MdSJ_HT2000toInf  = (TH2F*)f3->Get("h_MSJ_mass_vs_MdSJ_SR");
    h_MSJ_mass_vs_MdSJ_TTToHadronic = (TH2F*)f11->Get("h_MSJ_mass_vs_MdSJ_SR");
    h_MSJ_mass_vs_MdSJ_sig          = (TH2F*)f13->Get("h_MSJ_mass_vs_MdSJ_SR");
    h_MSJ_mass_vs_MdSJ_Data         = (TH2F*)f12->Get("h_MSJ_mass_vs_MdSJ_SR");   
  }
  else
  {
    std::cout << "Invalid region: " << regionType << ". Use a valid region type." << std::endl;
    return;
  }

  h_MSJ_mass_vs_MdSJ_HT1500to2000->Scale(QCD1500to2000_SF);
  h_MSJ_mass_vs_MdSJ_HT2000toInf->Scale(QCD2000toInf_SF);
  h_MSJ_mass_vs_MdSJ_TTToHadronic->Scale(h_TTToHadronic_SF);
  h_MSJ_mass_vs_MdSJ_sig->Scale(sigScaleFactor);
  gStyle->SetOptStat(0);

  TH2F *h_QCD_combined_TH2 = new TH2F(*h_MSJ_mass_vs_MdSJ_HT2000toInf);
  h_QCD_combined_TH2->Add(h_MSJ_mass_vs_MdSJ_HT1500to2000);
  TH2F *h_TTBar_combined_TH2 = new TH2F(*h_MSJ_mass_vs_MdSJ_TTToHadronic);
  ///////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////SR TH2 stack plot///////////////////////////////////////
  //go from 500 to 3000 in SJ mass (y) and 1200 to 9500 in diSJ mass, goes in steps of 300 in y and 400 in x

  //unwrap TH2 QCD///////////////
  //std::string binNumbers[440];
  for(int iii =0;iii<20;iii++)
    for(int jjj=0; jjj<22;jjj++)
    {
      int binToUse = jjj*20+iii;
      auto str = std::to_string(jjj); 

      h_MSJ_mass_vs_MdSJ_unwrapped_QCD->SetBinContent(binToUse,h_QCD_combined_TH2->GetBinContent(jjj,iii));
    }

  ////////////////////////////
  //unwrap TH2 TTbar///////////////
  for(int iii =0;iii<20;iii++)
    for(int jjj=0; jjj<22;jjj++)
    {
      int binToUse = jjj*20+iii;
      auto str = std::to_string(jjj); 

      h_MSJ_mass_vs_MdSJ_unwrapped_TTbar->SetBinContent(binToUse,h_TTBar_combined_TH2->GetBinContent(jjj,iii));
    }


  ////////////////////////////
  //unwrap TH2 sig///////////////
  for(int iii =0;iii<20;iii++)
    for(int jjj=0; jjj<22;jjj++)
    {
      int binToUse = jjj*20+iii;
      auto str = std::to_string(jjj); 

      h_MSJ_mass_vs_MdSJ_unwrapped_sig->SetBinContent(binToUse,h_MSJ_mass_vs_MdSJ_sig->GetBinContent(jjj,iii));
    }


  ////////////////////////////
  //unwrap TH2 Data///////////////
  for(int iii =0;iii<20;iii++)
    for(int jjj=0; jjj<22;jjj++)
    {
      int binToUse = jjj*20+iii;
      auto str = std::to_string(jjj);

      h_MSJ_mass_vs_MdSJ_unwrapped_Data->SetBinContent(binToUse,h_MSJ_mass_vs_MdSJ_Data->GetBinContent(jjj,iii));
    }


  f2->Close();
  f3->Close();
  f11->Close();
  f12->Close();
  f13->Close();

  outFile.cd();
  outFile.cd("QCD_CR");
  h_MSJ_mass_vs_MdSJ_unwrapped_TTbar->Write();
  h_MSJ_mass_vs_MdSJ_unwrapped_QCD->Write();
  h_MSJ_mass_vs_MdSJ_unwrapped_sig->Write();
  h_MSJ_mass_vs_MdSJ_unwrapped_Data->Write();
}


void prepareCombineRoot()
{
  std::vector<int> SuuMass = {4,5,6,7,8};
  std::vector<double> ChiMass = {1,1.5,2.0,2.5,3.0};
  std::vector<std::string> ChiMass_str = {"1","1p5","2","2p5","3"};

  double sigScaleFactor[5][5] = { {3.87E+00, 2.89E+00, -99999., -99999., -99999.  },   // MSuu = 4 TeV
                                  {1.37E+00, 1.19E+00, 8.67E-01, -99999., -99999. },   // MSuu = 5 Tev
                                  {2.82E-01, 2.58E-01, 2.20E-01, -99999., -99999. },   // MSuu = 6 TeV       //////////// NEED TO CALCULATE THE 2.5 TEV MCHI SFs //////////////
                                  {2.01E-01, 1.89E-01, 1.71E-01, -99999., 1.31E-01},   // MSuu = 7 TeV
                                  {2.17E-02, 2.08E-02, 1.93E-02, -99999., 1.74E-02 }    // MSuu = 8 TeV                                       
};
  for(int iii = 0; iii<SuuMass.size();iii++)
  {
    for(int jjj = 0; jjj < ChiMass.size();jjj++)
    {
      if ( ( SuuMass[iii]!=8) || (ChiMass_str[jjj]!='3')) continue;
      if(( SuuMass[iii]> 2*ChiMass[jjj]  )) do_Stuff( std::to_string(SuuMass[iii]), ChiMass_str[jjj] ,"QCD_CR" , sigScaleFactor[iii][jjj]  );
    }
  }
    
}
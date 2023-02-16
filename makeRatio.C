#include <iostream>
#include <string>
#include "TLorentzVector.h"
#include "TRatioPlot.h"
#include "THStack.h"
using namespace std;

void makeRatio()
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

  double h_Suu5TeV_chi2TeV_SF = 0.867;
  double h_Suu5TeV_chi1p5TeV_SF = 1.19E+00;
  double h_Suu6TeV_chi2TeV_SF = 2.20E-01;
  double h_Suu4TeV_chi1p5TeV_SF = 2.89E+00;
  double h_Suu8TeV_chi2TeV_SF = 1.93E-02;
  double h_Suu8TeV_chi3TeV_SF = 1.74E-02;
  double h_Suu8TeV_chi1TeV_SF = 2.17E-02;



  double scaleFactorSignal = h_Suu5TeV_chi1p5TeV_SF;


  //double h_TTJets2500toInf_SF  = 0.00008408965681;

  std::cout << "Open Files" << std::endl;
  TFile *f2 = new TFile("/home/ethan/Documents/QCD_HT1500to2000_combined_cutbased_processed.root");
  TFile *f3 = new TFile("/home/ethan/Documents/QCD_HT2000toInf_combined_cutbased_processed.root");   //need to add these two together
  TFile *f4 = new TFile("/home/ethan/Documents/cutBasedLessGeometric/ClusteringAlgorithm_MSuu5TeV-MChi1p5TeV_cutbased_output.root");   //need to add these two together

  //create histogramas for each of the different plots for different HT levels, scale histograms, add together histograms, normalize, do division/ comparison
  std::cout << "Get histograms" << std::endl;

  TH2F *h_MSJ_mass_vs_MdSJ_CR_HT1500to2000 = (TH2F*)f2->Get("h_MSJ_mass_vs_MdSJ_CR");
  TH2F *h_MSJ_mass_vs_MdSJ_CR_HT2000toInf = (TH2F*)f3->Get("h_MSJ_mass_vs_MdSJ_CR");
  TH2F *h_MSJ_mass_vs_MdSJ_CR_sig = (TH2F*)f4->Get("h_MSJ_mass_vs_MdSJ_CR");


  h_MSJ_mass_vs_MdSJ_CR_HT1500to2000->Scale(QCD1500to2000_SF);
  h_MSJ_mass_vs_MdSJ_CR_HT2000toInf->Scale(QCD2000toInf_SF);
  h_MSJ_mass_vs_MdSJ_CR_sig->Scale(h_Suu5TeV_chi1p5TeV_SF);
  gStyle->SetOptStat(0);

  TH2F *h_MSJ_mass_vs_MdSJ_CR_BRCombined = new TH2F(*h_MSJ_mass_vs_MdSJ_CR_HT1500to2000);
  h_MSJ_mass_vs_MdSJ_CR_BRCombined->Add(h_MSJ_mass_vs_MdSJ_CR_HT2000toInf);

  TH2F *h_MSJ_mass_vs_MdSJ_CR_ALLCombined = new TH2F(*h_MSJ_mass_vs_MdSJ_CR_BRCombined);
  h_MSJ_mass_vs_MdSJ_CR_ALLCombined->Add(h_MSJ_mass_vs_MdSJ_CR_sig);

  TCanvas *c1 = new TCanvas("c1","",400,20, 2000,1500);
  gPad->SetLogz();

  std::cout << "do TH2" << std::endl;

  h_MSJ_mass_vs_MdSJ_CR_ALLCombined->Divide(h_MSJ_mass_vs_MdSJ_CR_BRCombined);
  h_MSJ_mass_vs_MdSJ_CR_ALLCombined->SetTitle("M_{SJ} vs M_{diSJ} Ratio (double-tagged sig + BR in CR / double-tagged BR in CR); M_{diSJ};M_{SJ}");
  h_MSJ_mass_vs_MdSJ_CR_ALLCombined->GetYaxis()->SetTitleOffset(1.35);
  h_MSJ_mass_vs_MdSJ_CR_ALLCombined->GetYaxis()->SetLabelSize(0.015);
  h_MSJ_mass_vs_MdSJ_CR_ALLCombined->Draw("colz");
  c1->SaveAs("h_MSJ_mass_vs_MdSJ_CR_ratio_sigBR.png"); 

  //make Suu 5TeV, chi 2 TeV + BR / BR TH2


}

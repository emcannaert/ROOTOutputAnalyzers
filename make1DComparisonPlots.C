#include <iostream>
#include <string>
#include "TLorentzVector.h"
#include "TRatioPlot.h"
#include "THStack.h"
using namespace std;

void make1DComparisonPlots()  // and a couple 2D plots
{

  double QCD_HT1000to1500_SF = 4.289571744;
  double QCD_HT1500to2000_SF = 0.6042726685;
  double QCD_HT2000toInf_SF = 0.2132134533;
  double TTJets_inclusive_SF = 4.742226033;
  double h_WJetsToLNu_SF = 0.02459688845;
  double h_WJet_QQ_SF = 0.1266526072;


  double h_TTToHadronic_SF = 0.06588049107;
  double h_TTTo2l2nu_SF =0.03616639075 ;
  double h_TTToSemiLeptonic_SF = 0.04563489275;

  double h_Suu5TeV_chi2TeV_SF = 0.867;
  double h_Suu5TeV_chi1TeV_SF = 1.37;

  double h_Suu5TeV_chi1p5TeV_SF = 1.19E+00;
  double h_Suu6TeV_chi2TeV_SF = 2.20E-01;
  double h_Suu6TeV_chi1p5TeV_SF = 2.58E-01;

  double h_Suu4TeV_chi1p5TeV_SF = 2.89E+00;
  double h_Suu8TeV_chi2TeV_SF = 1.93E-02;
  double h_Suu8TeV_chi3TeV_SF = 1.74E-02;
  double h_Suu8TeV_chi1TeV_SF = 2.17E-02;

  bool includeTTBar = true;



  // show superjet mass
  // show disuperjet mass
  std::cout << "Open Files" << std::endl;
  TFile *f1 = new TFile("/home/ethan/Documents/QCD_HT1000to1500_combined_cutbased_processed.root");   //need to add these two together
  TFile *f2 = new TFile("/home/ethan/Documents/QCD_HT1500to2000_combined_cutbased_processed.root");
  TFile *f3 = new TFile("/home/ethan/Documents/QCD_HT2000toInf_combined_cutbased_processed.root"); 

  TFile *f7 = new TFile("/home/ethan/Documents/ClusteringAlgorithm_MSuu5TeV-MChi1p5TeV_cutbased_output.root");   

  //create histogramas for each of the different plots for different HT levels, scale histograms, add together histograms, normalize, do division/ comparison
  std::cout << "Get histograms" << std::endl;
  ///////////////////////////////1000to1500//////////////////////////////////
  TH1F *h_SJ_mass_HT1000to1500 =      (TH1F*)f1->Get("h_SJ_mass_DT");
  TH1F *h_disuperjet_mass_HT1000to1500 =      (TH1F*)f1->Get("h_disuperjet_mass");


  TH2F *h_MSJ_mass_vs_MdSJ_DT_HT1000to1500 =      (TH2F*)f1->Get("h_MSJ_mass_vs_MdSJ_DT");
  TH2F *h_MSJ_mass_vs_MdSJ_SR_NN_HT1000to1500 =      (TH2F*)f1->Get("h_MSJ_mass_vs_MdSJ_SR_NN");

////////////////////////////////////// 1500to2000 /////////////////////////////////////////
  TH1F *h_SJ_mass_HT1500to2000 =      (TH1F*)f2->Get("h_SJ_mass_DT");
  TH1F *h_disuperjet_mass_HT1500to2000 =      (TH1F*)f2->Get("h_disuperjet_mass");

  TH2F *h_MSJ_mass_vs_MdSJ_DT_HT1500to2000 =      (TH2F*)f2->Get("h_MSJ_mass_vs_MdSJ_DT");
  TH2F *h_MSJ_mass_vs_MdSJ_SR_NN_HT1500to2000 =      (TH2F*)f2->Get("h_MSJ_mass_vs_MdSJ_SR_NN");

////////////////////////////////////// 2000toInf /////////////////////////////////////////
  TH1F *h_SJ_mass_HT2000toInf =      (TH1F*)f3->Get("h_SJ_mass_DT");
  TH1F *h_disuperjet_mass_HT2000toInf =      (TH1F*)f3->Get("h_disuperjet_mass");

  TH2F *h_MSJ_mass_vs_MdSJ_DT_HT2000toInf =      (TH2F*)f3->Get("h_MSJ_mass_vs_MdSJ_DT");
  TH2F *h_MSJ_mass_vs_MdSJ_SR_NN_HT2000toInf =      (TH2F*)f3->Get("h_MSJ_mass_vs_MdSJ_SR_NN");

  //////////////////////////////////// JetHT combined data /////////////////////////////////////////
  TH1F *h_SJ_mass_signal =      (TH1F*)f7->Get("h_SJ_mass");
  TH1F *h_disuperjet_mass_signal =      (TH1F*)f7->Get("h_disuperjet_mass");

  TH2F *h_MSJ_mass_vs_MdSJ_DT_signal =      (TH2F*)f7->Get("h_MSJ_mass_vs_MdSJ_doubleTag");
  TH2F *h_MSJ_mass_vs_MdSJ_SR_NN_signal =      (TH2F*)f7->Get("h_MSJ_mass_vs_MdSJ_doubleTagNN");


  std::cout << "Scale histograms 1" << std::endl;

  h_SJ_mass_HT1000to1500->Scale(QCD_HT1000to1500_SF);
  h_disuperjet_mass_HT1000to1500->Scale(QCD_HT1000to1500_SF);
  h_SJ_mass_HT1500to2000->Scale(QCD_HT1500to2000_SF);
  h_disuperjet_mass_HT1500to2000->Scale(QCD_HT1500to2000_SF);
  h_SJ_mass_HT2000toInf->Scale(QCD_HT2000toInf_SF);
  h_disuperjet_mass_HT2000toInf->Scale(QCD_HT2000toInf_SF);
  h_SJ_mass_signal->Scale(h_Suu5TeV_chi1p5TeV_SF);
  h_disuperjet_mass_signal->Scale(h_Suu5TeV_chi1p5TeV_SF);


  h_MSJ_mass_vs_MdSJ_DT_HT1000to1500->Scale(QCD_HT1000to1500_SF);
  h_MSJ_mass_vs_MdSJ_SR_NN_HT1000to1500->Scale(QCD_HT1000to1500_SF);

  h_MSJ_mass_vs_MdSJ_DT_HT1500to2000->Scale(QCD_HT1500to2000_SF);
  h_MSJ_mass_vs_MdSJ_SR_NN_HT1500to2000->Scale(QCD_HT1500to2000_SF);

  h_MSJ_mass_vs_MdSJ_DT_HT2000toInf->Scale(QCD_HT2000toInf_SF);
  h_MSJ_mass_vs_MdSJ_SR_NN_HT2000toInf->Scale(QCD_HT2000toInf_SF);

  h_MSJ_mass_vs_MdSJ_DT_signal->Scale(h_Suu5TeV_chi1p5TeV_SF);
  h_MSJ_mass_vs_MdSJ_SR_NN_signal->Scale(h_Suu5TeV_chi1p5TeV_SF);
////////////////////////////////////////////////////////////////////////////////////////////////////////

  std::cout << "Add and scale histograms" << std::endl;


  ////////////h_SJ_mass//////////////

  TH1F *h_SJ_mass = new TH1F(*h_SJ_mass_HT2000toInf);
  h_SJ_mass->Add(h_SJ_mass_HT1500to2000);
  h_SJ_mass->Add(h_SJ_mass_HT1000to1500);

  //h_SJ_mass->SetFillColor(kRed);

  ////////////h_diSuperjet_mass//////////////

  TH1F *h_disuperjet_mass = new TH1F(*h_disuperjet_mass_HT2000toInf);
  h_disuperjet_mass->Add(h_disuperjet_mass_HT1500to2000);
  h_disuperjet_mass->Add(h_disuperjet_mass_HT1000to1500);

  //h_disuperjet_mass->SetFillColor(kRed);

  ////////////h_MSJ_mass_vs_MdSJ_DT//////////////

  TH2F *h_MSJ_mass_vs_MdSJ_DT = new TH2F(*h_MSJ_mass_vs_MdSJ_DT_HT2000toInf);
  h_MSJ_mass_vs_MdSJ_DT->Add(h_MSJ_mass_vs_MdSJ_DT_HT1500to2000);
  h_MSJ_mass_vs_MdSJ_DT->Add(h_MSJ_mass_vs_MdSJ_DT_HT1000to1500);


  ////////////h_MSJ_mass_vs_MdSJ_SR_NN//////////////

  TH2F *h_MSJ_mass_vs_MdSJ_SR_NN = new TH2F(*h_MSJ_mass_vs_MdSJ_SR_NN_HT2000toInf);
  h_MSJ_mass_vs_MdSJ_SR_NN->Add(h_MSJ_mass_vs_MdSJ_SR_NN_HT1500to2000);
  h_MSJ_mass_vs_MdSJ_SR_NN->Add(h_MSJ_mass_vs_MdSJ_SR_NN_HT1000to1500);





  TH2F *h_MSJ_mass_vs_MdSJ_DT_both = new TH2F(*h_MSJ_mass_vs_MdSJ_DT);
  h_MSJ_mass_vs_MdSJ_DT_both->Add(h_MSJ_mass_vs_MdSJ_DT_signal);

  TH2F *h_MSJ_mass_vs_MdSJ_SR_NN_both = new TH2F(*h_MSJ_mass_vs_MdSJ_SR_NN);
  h_MSJ_mass_vs_MdSJ_SR_NN_both->Add(h_MSJ_mass_vs_MdSJ_SR_NN_signal);


  h_MSJ_mass_vs_MdSJ_DT_both->Divide(h_MSJ_mass_vs_MdSJ_DT);
  h_MSJ_mass_vs_MdSJ_SR_NN_both->Divide(h_MSJ_mass_vs_MdSJ_SR_NN);



  TCanvas *c1 = new TCanvas("c1","",400,20, 2000,1500);

  gStyle->SetOptStat(0);


  h_MSJ_mass_vs_MdSJ_DT->Draw("colz");
  h_MSJ_mass_vs_MdSJ_DT->SetTitle("M_{avg SJ} vs M_{diSJ} ,  (double-tagged MC, cut-based)");
  c1->SaveAs("h_MSJ_mass_vs_MdSJ_DT_BR.png"); 

  h_MSJ_mass_vs_MdSJ_SR_NN->Draw("colz");
  h_MSJ_mass_vs_MdSJ_SR_NN->SetTitle("M_{avg SJ} vs M_{diSJ} ,  (double-tagged MC, NN-based)");

  c1->SaveAs("h_MSJ_mass_vs_MdSJ_SR_NN_BR.png"); 


  h_MSJ_mass_vs_MdSJ_DT_both->SetTitle("M_{avg SJ} vs M_{diSJ} - ( Sig+BR/BR ),  (double-tagged MC, cut-based)");
  h_MSJ_mass_vs_MdSJ_DT_both->GetYaxis()->SetTitleOffset(1.35);
  h_MSJ_mass_vs_MdSJ_DT_both->Draw("colz");
  c1->SaveAs("h_MSJ_mass_vs_MdSJ_DT_BRSig.png"); 

  h_MSJ_mass_vs_MdSJ_SR_NN_both->SetTitle("M_{avg SJ} vs M_{diSJ} - ( Sig+BR/BR ), (double-tagged MC, NN-based)");
  h_MSJ_mass_vs_MdSJ_SR_NN_both->GetYaxis()->SetTitleOffset(1.35);
  h_MSJ_mass_vs_MdSJ_SR_NN_both->Draw("colz");
  c1->SaveAs("h_MSJ_mass_vs_MdSJ_SR_NN_BRSig.png"); 

  gPad->SetLogy();

  std::cout << "do TH1s" << std::endl;


  h_SJ_mass->SetTitle("superjet mass (Signal Region)");
  h_SJ_mass->SetLineColor(kRed);
  h_SJ_mass->SetLineWidth(6);
  h_SJ_mass->Draw("HIST");
  h_SJ_mass_signal->SetLineColor(kBlue);
  h_SJ_mass_signal->SetLineWidth(6);
  h_SJ_mass_signal->Draw("SAME");


   auto legend = new TLegend(0.90,0.80,0.4,0.90);
   legend->SetHeader("","C"); // option "C" allows to center the header
   legend->AddEntry(h_SJ_mass,"Combined QCD BR MC","f");
   legend->AddEntry(h_SJ_mass_signal,"M_{S_{uu}}=5 TeV, M_{chi} = 1.5 TeV","f");
   legend->Draw();
   c1->SaveAs("h_SJ_mass_BRSig.png"); 


  h_disuperjet_mass->SetTitle("diSuperjet mass (Signal Region)");

  h_disuperjet_mass->SetLineWidth(6);
  h_disuperjet_mass->SetLineColor(kRed);
  h_disuperjet_mass->Draw("HIST");
  h_disuperjet_mass_signal->SetLineColor(kBlue);
  h_disuperjet_mass_signal->SetLineWidth(6);
  h_disuperjet_mass_signal->Draw("SAME,AP*");

   auto legend1 = new TLegend(0.90,0.80,0.4,0.90);
   legend1->SetHeader("","C"); // option "C" allows to center the header
   legend1->AddEntry(h_disuperjet_mass,"Combined QCD BR MC","f");
   legend1->AddEntry(h_disuperjet_mass_signal,"M_{S_{uu}}= 5 TeV, M_{chi} = 1.5 TeV","f");
   legend1->Draw();
  c1->SaveAs("h_disuperjet_mass_BRSig.png"); 


} 

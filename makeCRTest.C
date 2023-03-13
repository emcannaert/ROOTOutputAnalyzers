#include <iostream>
#include <string>
#include "TLorentzVector.h"
#include "TRatioPlot.h"
#include "THStack.h"
using namespace std;

void makeCRTest()
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
  double h_Suu5TeV_chi1p5TeV_SF = 1.19E+00;
  double h_Suu6TeV_chi2TeV_SF = 2.20E-01;
  double h_Suu4TeV_chi1p5TeV_SF = 2.89E+00;
  double h_Suu8TeV_chi2TeV_SF = 1.93E-02;
  double h_Suu8TeV_chi3TeV_SF = 1.74E-02;
  double h_Suu8TeV_chi1TeV_SF = 2.17E-02;

  bool includeTTBar = true;

  std::cout << "Open Files" << std::endl;
  TFile *f1 = new TFile("/home/ethan/Documents/QCD_HT1000to1500_combined_cutbased_processed_TEST_2018.root");   //need to add these two together
  TFile *f2 = new TFile("/home/ethan/Documents/QCD_HT1500to2000_combined_cutbased_processed_TEST_2018.root");
  TFile *f3 = new TFile("/home/ethan/Documents/QCD_HT2000toInf_combined_cutbased_processed_TEST_2018.root"); 

//  TFile *f4 = new TFile("/home/ethan/Documents/TTToHadronic_combined_cutbased_processed_TEST.root");  
 // TFile *f5 = new TFile("/home/ethan/Documents/TTTo2l2nu_combine_cutbased_processed_TEST.root");   
 // TFile *f6 = new TFile("/home/ethan/Documents/TTtoSemiLeptonic_combined_cutbased_processed_TEST.root");   
  
  //create histogramas for each of the different plots for different HT levels, scale histograms, add together histograms, normalize, do division/ comparison
  std::cout << "Get histograms" << std::endl;
  ///////////////////////////////1000to1500//////////////////////////////////

  TH1F* h_totHT_QCD_HT1000to1500_CR           =      (TH1F*)f1->Get("h_totHT_CR");
  TH1F* h_totHT_QCD_HT1000to1500_DT           =      (TH1F*)f1->Get("h_totHT_DT");
  //TH1F* h_deepFlavour_score_HT1000to1500      =      (TH1F*)f1->Get("h_deepFlavour_score");
  TH1I* h_nLooseBtags_HT1000to1500            =      (TH1I*)f1->Get("h_nLooseBtags");

  TH1F* h_SJ_mass_HT1000to1500_DT            =      (TH1F*)f1->Get("h_SJ_mass_DT");
  TH1F* h_disuperjet_mass_HT1000to1500_DT       =      (TH1F*)f1->Get("h_disuperjet_mass_DT");

  TH1F* h_SJ_mass_HT1000to1500_CR            =      (TH1F*)f1->Get("h_SJ_mass_CR");
  TH1F* h_disuperjet_mass_HT1000to1500_CR       =      (TH1F*)f1->Get("h_disuperjet_mass_CR");

//h_SJ_mass_DT
//h_disuperjet_mass_DT
////////////////////////////////////// 1500to2000 /////////////////////////////////////////

  TH1F* h_totHT_QCD_HT1500to2000_CR           =      (TH1F*)f2->Get("h_totHT_CR");
  TH1F* h_totHT_QCD_HT1500to2000_DT           =      (TH1F*)f2->Get("h_totHT_DT");
  //TH1F* h_deepFlavour_score_HT1500to2000      =      (TH1F*)f2->Get("h_deepFlavour_score");
  TH1I* h_nLooseBtags_HT1500to2000            =      (TH1I*)f2->Get("h_nLooseBtags");


  TH1F* h_SJ_mass_HT1500to2000_DT           =      (TH1F*)f2->Get("h_SJ_mass_DT");
  TH1F* h_disuperjet_mass_HT1500to2000_DT        =      (TH1F*)f2->Get("h_disuperjet_mass_DT");

  TH1F* h_SJ_mass_HT1500to2000_CR            =      (TH1F*)f2->Get("h_SJ_mass_CR");
  TH1F* h_disuperjet_mass_HT1500to2000_CR       =      (TH1F*)f2->Get("h_disuperjet_mass_CR");


////////////////////////////////////// 2000toInf /////////////////////////////////////////

  TH1F* h_totHT_QCD_HT2000toInf_CR           =      (TH1F*)f3->Get("h_totHT_CR");
  TH1F* h_totHT_QCD_HT2000toInf_DT           =      (TH1F*)f3->Get("h_totHT_DT");
  //TH1F* h_deepFlavour_score_HT2000toInf      =      (TH1F*)f3->Get("h_deepFlavour_score");
  TH1I* h_nLooseBtags_HT2000toInf            =      (TH1I*)f3->Get("h_nLooseBtags");

  TH1F* h_SJ_mass_HT2000toInf_DT           =      (TH1F*)f3->Get("h_SJ_mass_DT");
  TH1F* h_disuperjet_mass_HT2000toInf_DT        =      (TH1F*)f3->Get("h_disuperjet_mass_DT");

  TH1F* h_SJ_mass_HT2000toInf_CR            =      (TH1F*)f3->Get("h_SJ_mass_CR");
  TH1F* h_disuperjet_mass_HT2000toInf_CR       =      (TH1F*)f3->Get("h_disuperjet_mass_CR");


  ////////////////////////////////////// TTTohadronic /////////////////////////////////////////
/*

  TH1F* h_totHT_TTToHadronic_CR           =      (TH1F*)f4->Get("h_totHT_CR");
  TH1F* h_totHT_TTToHadronic_DT           =      (TH1F*)f4->Get("h_totHT_DT");


  ////////////////////////////////////// TTToLeptonic /////////////////////////////////////////

  TH1F* h_totHT_TTTo2l2nu_CR           =      (TH1F*)f5->Get("h_totHT_CR");
  TH1F* h_totHT_TTTo2l2nu_DT           =      (TH1F*)f5->Get("h_totHT_DT");

  ////////////////////////////////////// TTToSemiLeptonic /////////////////////////////////////////

  TH1F* h_totHT_TTtoSemiLeptonic_CR           =      (TH1F*)f6->Get("h_totHT_CR");
  TH1F* h_totHT_TTtoSemiLeptonic_DT           =      (TH1F*)f6->Get("h_totHT_DT");

  */
  std::cout << "Scale histograms 1" << std::endl;

  h_totHT_QCD_HT1000to1500_CR->Scale(QCD_HT1000to1500_SF);
  h_totHT_QCD_HT1000to1500_DT->Scale(QCD_HT1000to1500_SF);


  h_totHT_QCD_HT1500to2000_CR->Scale(QCD_HT1500to2000_SF);
  h_totHT_QCD_HT1500to2000_DT->Scale(QCD_HT1500to2000_SF);

  h_totHT_QCD_HT2000toInf_CR->Scale(QCD_HT2000toInf_SF);
  h_totHT_QCD_HT2000toInf_DT->Scale(QCD_HT2000toInf_SF);


  h_SJ_mass_HT1000to1500_DT->Scale(QCD_HT1000to1500_SF);
  h_SJ_mass_HT1500to2000_DT->Scale(QCD_HT1500to2000_SF);
  h_SJ_mass_HT2000toInf_DT->Scale(QCD_HT2000toInf_SF);

  h_SJ_mass_HT1000to1500_CR->Scale(QCD_HT1000to1500_SF);
  h_SJ_mass_HT1500to2000_CR->Scale(QCD_HT1500to2000_SF);
  h_SJ_mass_HT2000toInf_CR->Scale(QCD_HT2000toInf_SF);

  h_disuperjet_mass_HT1000to1500_DT->Scale(QCD_HT1000to1500_SF);
  h_disuperjet_mass_HT1500to2000_DT->Scale(QCD_HT1500to2000_SF);
  h_disuperjet_mass_HT2000toInf_DT->Scale(QCD_HT2000toInf_SF);

  h_disuperjet_mass_HT1000to1500_CR->Scale(QCD_HT1000to1500_SF);
  h_disuperjet_mass_HT1500to2000_CR->Scale(QCD_HT1500to2000_SF);
  h_disuperjet_mass_HT2000toInf_CR->Scale(QCD_HT2000toInf_SF);



  //h_deepFlavour_score_HT1000to1500->Scale(QCD_HT1000to1500_SF);
  //h_deepFlavour_score_HT1500to2000->Scale(QCD_HT1500to2000_SF);
  //h_deepFlavour_score_HT2000toInf->Scale(QCD_HT2000toInf_SF);

  //h_nLooseBtags_HT1000to1500->Scale();
 // h_nLooseBtags_HT1500to2000->Scale();
 // h_nLooseBtags_HT2000toInf->Scale();
/*
  h_totHT_TTToHadronic_CR->Scale(h_TTToHadronic_SF);
  h_totHT_TTToHadronic_DT->Scale(h_TTToHadronic_SF);

  h_totHT_TTTo2l2nu_CR->Scale(h_TTTo2l2nu_SF);
  h_totHT_TTTo2l2nu_DT->Scale(h_TTTo2l2nu_SF);

  h_totHT_TTtoSemiLeptonic_CR->Scale(h_TTToSemiLeptonic_SF);
  h_totHT_TTtoSemiLeptonic_DT->Scale(h_TTToSemiLeptonic_SF);
*/
////////////////////////////////////////////////////////////////////////////////////////////////////////

  std::cout << "Add and scale histograms" << std::endl;


//h_SJ_mass_DT
//h_disuperjet_mass_DT
///////////////////////////////////////////////////////////////////
///////////h_totHT//////////////////////
  TH1F *h_totHT_CR = new TH1F(*h_totHT_QCD_HT2000toInf_CR);    //);
  h_totHT_CR->Add(h_totHT_QCD_HT1000to1500_CR);
  h_totHT_CR->Add(h_totHT_QCD_HT1500to2000_CR);


  //h_totHT_CR->Add(h_totHT_TTToHadronic_CR);
  //h_totHT_CR->Add(h_totHT_TTTo2l2nu_CR);
  //h_totHT_CR->Add(h_totHT_TTtoSemiLeptonic_CR);
  h_totHT_CR->Scale(1./h_totHT_CR->Integral());

  TH1F *h_totHT_DT = new TH1F(*h_totHT_QCD_HT2000toInf_DT); //); 
  h_totHT_DT->Add(h_totHT_QCD_HT1000to1500_DT);
  h_totHT_DT->Add(h_totHT_QCD_HT1500to2000_DT);

  //h_totHT_DT->Add(h_totHT_TTToHadronic_DT);
  //h_totHT_DT->Add(h_totHT_TTTo2l2nu_DT);
  //h_totHT_DT->Add(h_totHT_TTtoSemiLeptonic_DT);
  h_totHT_DT->Scale(1./h_totHT_DT->Integral());

  //TH1F *h_deepFlavour_score = new TH1F(*h_deepFlavour_score_HT2000toInf);//);
  //h_deepFlavour_score->Add(h_deepFlavour_score_HT1000to1500);
  //h_deepFlavour_score->Add(h_deepFlavour_score_HT1500to2000);
  //h_totHT_DT->Add(h_totHT_TTToHadronic_DT);
  //h_totHT_DT->Add(h_totHT_TTTo2l2nu_DT);
  //h_totHT_DT->Add(h_totHT_TTtoSemiLeptonic_DT);
  //h_deepFlavour_score->Scale(1./h_deepFlavour_score->Integral());

/*
  TH1I *h_nLooseBtags = new TH1I(*h_nLooseBtags_HT2000toInf);//);
  h_nLooseBtags->Add(h_nLooseBtags_HT1000to1500);
  h_nLooseBtags->Add(h_nLooseBtags_HT1500to2000);
  //h_nLooseBtags->Add(h_nLooseBtags_TTToHadronic_DT);
  //h_nLooseBtags->Add(h_nLooseBtags_TTTo2l2nu_DT);
  //h_nLooseBtags->Add(h_nLooseBtags_TTtoSemiLeptonic_DT);
  h_nLooseBtags->Scale(1./h_nLooseBtags->Integral());
*/

  TH1F *h_SJ_mass_DT = new TH1F(*h_SJ_mass_HT2000toInf_DT);    //);
  h_SJ_mass_DT->Add(h_SJ_mass_HT1500to2000_DT);
  h_SJ_mass_DT->Add(h_SJ_mass_HT1000to1500_DT);
  h_SJ_mass_DT->Scale(1./h_SJ_mass_DT->Integral());


  TH1F *h_SJ_mass_CR = new TH1F(*h_SJ_mass_HT2000toInf_CR);    //);
  h_SJ_mass_CR->Add(h_SJ_mass_HT1500to2000_CR);
  h_SJ_mass_CR->Add(h_SJ_mass_HT1000to1500_CR);
  h_SJ_mass_CR->Scale(1./h_SJ_mass_CR->Integral());



  TH1F *h_disuperjet_mass_DT = new TH1F(*h_disuperjet_mass_HT2000toInf_DT);    //);
  h_disuperjet_mass_DT->Add(h_disuperjet_mass_HT1500to2000_DT);
  h_disuperjet_mass_DT->Add(h_disuperjet_mass_HT1000to1500_DT);
  h_disuperjet_mass_DT->Scale(1./h_disuperjet_mass_DT->Integral());

  TH1F *h_disuperjet_mass_CR = new TH1F(*h_disuperjet_mass_HT2000toInf_CR);    //);
  h_disuperjet_mass_CR->Add(h_disuperjet_mass_HT1500to2000_CR);
  h_disuperjet_mass_CR->Add(h_disuperjet_mass_HT1000to1500_CR);
  h_disuperjet_mass_CR->Scale(1./h_disuperjet_mass_CR->Integral());



  TCanvas *c1 = new TCanvas("c1","",400,20, 1500,1500);


  //h_deepFlavour_score->Draw("HIST");
  //c1->SaveAs("h_deepFlavour_score.png");



  //h_nLooseBtags->Draw();
  //c1->SaveAs("h_nLooseBtags_TEST.png");

   gPad->SetLogy();


  std::cout << "do ratio plots" << std::endl;

  auto rp_totHT = new TRatioPlot(h_totHT_CR,h_totHT_DT);
  rp_totHT->Draw("HIST,E");
  rp_totHT->GetLowerRefYaxis()->SetTitle("CR MC / SR MC");
  rp_totHT->GetLowerRefGraph()->SetMaximum(2.);
  rp_totHT->GetUpperRefYaxis()->SetTitle("Events");
  c1->SaveAs("rp_totHT_TEST.png"); 
 
  auto rp_disuperjet_mass = new TRatioPlot(h_disuperjet_mass_CR,h_disuperjet_mass_DT);
  rp_disuperjet_mass->Draw("HIST,E");
  rp_disuperjet_mass->GetLowerRefYaxis()->SetTitle("CR MC / SR MC");
  rp_disuperjet_mass->GetLowerRefGraph()->SetMaximum(2.);
  rp_disuperjet_mass->GetUpperRefYaxis()->SetTitle("Events");
  c1->SaveAs("rp_disuperjet_mass_TEST.png"); 
 
  auto rp_SJ_mass = new TRatioPlot(h_SJ_mass_CR,h_SJ_mass_DT);
  rp_SJ_mass->Draw("HIST,E");
  rp_SJ_mass->GetLowerRefYaxis()->SetTitle("CR MC / SR MC");
  rp_SJ_mass->GetLowerRefGraph()->SetMaximum(2.);
  rp_SJ_mass->GetUpperRefYaxis()->SetTitle("Events");
  c1->SaveAs("rp_SJ_mass_TEST.png"); 
 
}
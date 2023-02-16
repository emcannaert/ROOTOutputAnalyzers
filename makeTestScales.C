#include <iostream>
#include <string>
#include "TLorentzVector.h"
#include "TRatioPlot.h"
#include "THStack.h"
using namespace std;

void makeTestScales()
{

  double QCD_HT1000to1500_SF = 4.289571744;
  double QCD_HT1500to2000_SF = 0.6042726685;
  double QCD_HT2000toInf_SF = 0.2132134533;


  std::cout << "Open Files" << std::endl;
  TFile *f1 = new TFile("/home/ethan/Documents/QCD_HT1000to1500_combined_cutbased_processed.root");   //need to add these two together
  TFile *f2 = new TFile("/home/ethan/Documents/QCD_HT1500to2000_combined_cutbased_processed.root");
  TFile *f3 = new TFile("/home/ethan/Documents/QCD_HT2000toInf_combined_cutbased_processed.root"); 

  TFile *f7 = new TFile("/home/ethan/Documents/JetHT_combined_processed.root");   

  //create histogramas for each of the different plots for different HT levels, scale histograms, add together histograms, normalize, do division/ comparison
  std::cout << "Get histograms" << std::endl;
  ///////////////////////////////1000to1500//////////////////////////////////
  TH1F *h_totHT_All_HT1000to1500 =  (TH1F*)f1->Get("h_totHT_All");
  TH1F *h_totHT_All1_HT1000to1500 =  (TH1F*)f1->Get("h_totHT_All1");
  TH1F *h_totHT_All2_HT1000to1500 =  (TH1F*)f1->Get("h_totHT_All2");
  TH1F *h_totHT_All3_HT1000to1500 =  (TH1F*)f1->Get("h_totHT_All3");

  TH1F *h_SJ_mass_CR_HT1000to1500 =          (TH1F*)f1->Get("h_SJ_mass_CR");
  TH1I *h_nAK4_all_CR_HT1000to1500 =          (TH1I*)f1->Get("h_nAK4");


////////////////////////////////////// 1500to2000 /////////////////////////////////////////
  TH1F *h_totHT_All_HT1500to2000 =  (TH1F*)f2->Get("h_totHT_All");
  TH1F *h_totHT_All1_HT1500to2000 =  (TH1F*)f2->Get("h_totHT_All1");
  TH1F *h_totHT_All2_HT1500to2000 =  (TH1F*)f2->Get("h_totHT_All2");
  TH1F *h_totHT_All3_HT1500to2000 =  (TH1F*)f2->Get("h_totHT_All3");

  TH1F *h_SJ_mass_CR_HT1500to2000 =          (TH1F*)f2->Get("h_SJ_mass_CR");
  TH1I *h_nAK4_all_CR_HT1500to2000 =          (TH1I*)f2->Get("h_nAK4");

////////////////////////////////////// 2000toInf /////////////////////////////////////////
  TH1F *h_totHT_All_HT2000toInf =  (TH1F*)f3->Get("h_totHT_All");
  TH1F *h_totHT_All1_HT2000toInf =  (TH1F*)f3->Get("h_totHT_All1");
  TH1F *h_totHT_All2_HT2000toInf =  (TH1F*)f3->Get("h_totHT_All2");
  TH1F *h_totHT_All3_HT2000toInf =  (TH1F*)f3->Get("h_totHT_All3");

  TH1F *h_SJ_mass_CR_HT2000toInf =          (TH1F*)f3->Get("h_SJ_mass_CR");
  TH1I *h_nAK4_all_CR_HT2000toInf =          (TH1I*)f3->Get("h_nAK4");


  //////////////////////////////////// JetHT combined data /////////////////////////////////////////
  TH1F *h_totHT_All_data =  (TH1F*)f7->Get("h_totHT_All");
  TH1F *h_totHT_All1_data =  (TH1F*)f7->Get("h_totHT_All1");
  TH1F *h_totHT_All2_data =  (TH1F*)f7->Get("h_totHT_All2");
  TH1F *h_totHT_All3_data =  (TH1F*)f7->Get("h_totHT_All3");

  TH1F *h_SJ_mass_CR_data           =  (TH1F*)f7->Get("h_SJ_mass_CR");
  TH1I *h_nAK4_all_CR_data =          (TH1I*)f7->Get("h_nAK4");


  std::cout << "Scale histograms 1" << std::endl;

  h_totHT_All_HT1000to1500->Scale(QCD_HT1000to1500_SF);
  h_totHT_All_HT1500to2000->Scale(QCD_HT1500to2000_SF);
  h_totHT_All_HT2000toInf->Scale(QCD_HT2000toInf_SF);

  h_totHT_All1_HT1000to1500->Scale(QCD_HT1000to1500_SF);
  h_totHT_All1_HT1500to2000->Scale(QCD_HT1500to2000_SF);
  h_totHT_All1_HT2000toInf->Scale(QCD_HT2000toInf_SF);

  h_totHT_All2_HT1000to1500->Scale(QCD_HT1000to1500_SF);
  h_totHT_All2_HT1500to2000->Scale(QCD_HT1500to2000_SF);
  h_totHT_All2_HT2000toInf->Scale(QCD_HT2000toInf_SF);

  h_totHT_All3_HT1000to1500->Scale(QCD_HT1000to1500_SF);
  h_totHT_All3_HT1500to2000->Scale(QCD_HT1500to2000_SF);
  h_totHT_All3_HT2000toInf->Scale(QCD_HT2000toInf_SF);

  h_SJ_mass_CR_HT1000to1500->Scale(QCD_HT1000to1500_SF);
  h_SJ_mass_CR_HT1500to2000->Scale(QCD_HT1500to2000_SF);
  h_SJ_mass_CR_HT2000toInf->Scale(QCD_HT2000toInf_SF);


  h_nAK4_all_CR_HT1000to1500->Scale(QCD_HT1000to1500_SF);
  h_nAK4_all_CR_HT1500to2000->Scale(QCD_HT1500to2000_SF);
  h_nAK4_all_CR_HT2000toInf->Scale(QCD_HT2000toInf_SF);



////////////////////////////////////////////////////////////////////////////////////////////////////////

  std::cout << "Add and scale histograms" << std::endl;

    TCanvas *c1 = new TCanvas("c1","",400,20, 1500,1500);

  ////////////h_totHT_All//////////////
  
  TH1F *h_totHT_All = new TH1F(*h_totHT_All_HT2000toInf);
  h_totHT_All->Add(h_totHT_All_HT1500to2000);
  h_totHT_All->Add(h_totHT_All_HT1000to1500);

  ////////////h_totHT_All1//////////////
  
  TH1F *h_totHT_All1 = new TH1F(*h_totHT_All1_HT2000toInf);
  h_totHT_All1->Add(h_totHT_All1_HT1500to2000);
  h_totHT_All1->Add(h_totHT_All1_HT1000to1500);

  ////////////h_totHT_All//////////////
  
  TH1F *h_totHT_All2 = new TH1F(*h_totHT_All2_HT2000toInf);
  h_totHT_All2->Add(h_totHT_All2_HT1500to2000);
  h_totHT_All2->Add(h_totHT_All2_HT1000to1500);

  ////////////h_totHT_All//////////////
  
  TH1F *h_totHT_All3 = new TH1F(*h_totHT_All3_HT2000toInf);
  h_totHT_All3->Add(h_totHT_All3_HT1500to2000);
  h_totHT_All3->Add(h_totHT_All3_HT1000to1500);

///////////////////////////////////////////////////////////
///////////h_SJ_mass//////////////////////
  TH1F *h_SJ_mass_CR = new TH1F(*h_SJ_mass_CR_HT2000toInf);
  h_SJ_mass_CR->Add(h_SJ_mass_CR_HT1000to1500);
  h_SJ_mass_CR->Add(h_SJ_mass_CR_HT1500to2000);

//the 2000toInf and 1500toInf are the same??


///////////h_nAK4//////////////////////
  TH1I *h_nAK4_all = new TH1I(*h_nAK4_all_CR_HT2000toInf);  //
  h_nAK4_all->Add(h_nAK4_all_CR_HT1500to2000);
  h_nAK4_all->Add(h_nAK4_all_CR_HT1000to1500);


  std::cout << "nEvents data/MC = " << h_totHT_All_data->Integral() << "/" << h_totHT_All->Integral() << std::endl;
  std::cout << "nEvents CR data/MC = " << h_SJ_mass_CR_data->Integral()/2. << "/" << h_SJ_mass_CR->Integral()/2. << std::endl;

  gPad->SetLogy();


  auto rp_totHT_All_test = new TRatioPlot(h_totHT_All_data,h_totHT_All);
  rp_totHT_All_test->Draw("HIST,E");
  rp_totHT_All_test->GetLowerRefYaxis()->SetTitle("Data / MC");
  rp_totHT_All_test->GetLowerRefGraph()->SetMaximum(1.2);
  rp_totHT_All_test->GetUpperRefYaxis()->SetTitle("Events");
  c1->SaveAs("rp_totHT_All_test_DataMC.png");  

  auto rp_totHT_All1_test = new TRatioPlot(h_totHT_All1_data, h_totHT_All1);
  rp_totHT_All1_test->Draw("HIST,E");
  rp_totHT_All1_test->GetLowerRefYaxis()->SetTitle("Data / MC");
  rp_totHT_All1_test->GetLowerRefGraph()->SetMaximum(2.0);
  rp_totHT_All1_test->GetUpperRefYaxis()->SetTitle("Events");
  c1->SaveAs("rp_totHT_All1_test_DataMC.png");  

  auto rp_totHT_All2_test = new TRatioPlot(h_totHT_All2_data,h_totHT_All2);
  rp_totHT_All2_test->Draw("HIST,E");
  rp_totHT_All2_test->GetLowerRefYaxis()->SetTitle("Data / MC");
  rp_totHT_All2_test->GetLowerRefGraph()->SetMaximum(2.0);
  rp_totHT_All2_test->GetUpperRefYaxis()->SetTitle("Events");
  c1->SaveAs("rp_totHT_All2_test_DataMC.png");  

  auto rp_totHT_All3_test = new TRatioPlot(h_totHT_All3_data,h_totHT_All3);
  rp_totHT_All3_test->Draw("HIST,E");
  rp_totHT_All3_test->GetLowerRefYaxis()->SetTitle("Data / MC");
  rp_totHT_All3_test->GetLowerRefGraph()->SetMaximum(2.0);
  rp_totHT_All3_test->GetUpperRefYaxis()->SetTitle("Events");
  c1->SaveAs("rp_totHT_All3_test_DataMC.png");  


  auto rp_SJ_mass = new TRatioPlot(h_SJ_mass_CR_data,h_SJ_mass_CR);
  rp_SJ_mass->Draw("HIST,E");
  rp_SJ_mass->GetLowerRefYaxis()->SetTitle("CR Data / CR MC");
  rp_SJ_mass->GetLowerRefGraph()->SetMaximum(2.0);
  rp_SJ_mass->GetUpperRefYaxis()->SetTitle("Events");
  c1->SaveAs("rp_DataMC_SJ_mass_test_DataMC.png"); 

  auto rp_nAK4_all = new TRatioPlot(h_nAK4_all_CR_data,h_nAK4_all);
  rp_nAK4_all->Draw("HIST,E");
  rp_nAK4_all->GetLowerRefYaxis()->SetTitle("CR Data / CR MC");
  rp_nAK4_all->GetLowerRefGraph()->SetMaximum(2.0);
  rp_nAK4_all->GetUpperRefYaxis()->SetTitle("Events");
  c1->SaveAs("rp_nAK4_all_test_DataMC.png"); 



}

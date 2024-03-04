#include <iostream>
#include <string>
#include "TLorentzVector.h"
#include "TRatioPlot.h"
#include "THStack.h"
#include "TRatioPlot.h"
using namespace std;

void create_plot(std::string year, int counter)
{
  double QCD1000to1500_SF[4] = {1.578683216,1.482632755,3.126481451,4.289571744}; //TODO, 
  double QCD1500to2000_SF[4] = {0.2119142341,0.195224041,0.3197450474,0.4947703875}; //TODO
  double QCD2000toInf_SF[4] = {0.08568186031,0.07572795371,0.14306915,0.2132134533}; //TODO
  double h_TTToHadronic_SF[4] = {0.075592,0.05808655696,0.06651018525,0.06588049107}; //TODO
  double h_TTToSemiLeptonic_SF[4] = {0.05395328118,0.05808655696,0.04264829286,0.04563489275}; //TODO
  double h_TTTo2l2nu_SF[4] = {0.0459517611,0.03401684391,0.03431532926,00.03617828025}; //TODO

  double ST_t_channel_top_5f_SF[4] = {0.0409963154,0.03607115071,0.03494669125,0.03859114659}; //TODO
  double ST_t_channel_antitop_5f_SF[4] = {0.05673857623,0.04102705994,0.04238814865,0.03606630944}; //TODO
  double ST_s_channel_4f_hadrons_SF[4] = {0.04668187234,0.03564988679,0.03985938616,0.04102795437}; //TODO
  double ST_s_channel_4f_leptons_SF[4] = {0.01323030083,0.01149139097,0.01117527734,0.01155448784}; //TODO
  double ST_tW_antitop_5f_SF[4] = {0.2967888696,0.2301666797,0.2556495594,0.2700032391}; //TODO
  double ST_tW_top_5f_SF[4] = {0.2962796522,0.2355829386,0.2563403788,0.2625270613}; //TODO

  TCanvas *c1 = new TCanvas("c1","",400,20, 2000,1500);

  int SF_index = 0;
  if(year == "2016")
  {
    SF_index = 1;
  }
  if(year == "2017")
  {
    SF_index = 2;
  }
  else if(year == "2018")
  {
    SF_index = 3;
  }
  std::string plot_home = "/Users/ethan/Documents/plots/ratioPlotsAdHoc/";
  TFile *f1 = new TFile( ("/Users/ethan/Documents/rootFiles/processedRootFiles/QCDMC1000to1500_" + year +"_nom_processed.root").c_str() );
  TFile *f2 = new TFile(("/Users/ethan/Documents/rootFiles/processedRootFiles/QCDMC1500to2000_" + year +"_nom_processed.root").c_str() );
  TFile *f3 = new TFile(("/Users/ethan/Documents/rootFiles/processedRootFiles/QCDMC2000toInf_" + year +"_nom_processed.root").c_str() );

  TFile *f4 = new TFile(("/Users/ethan/Documents/rootFiles/processedRootFiles/TTToHadronicMC_" + year +"_nom_processed.root").c_str() ); 
  TFile *f5 = new TFile(("/Users/ethan/Documents/rootFiles/processedRootFiles/TTToLeptonicMC_" + year +"_nom_processed.root").c_str() );
  TFile *f6 = new TFile(("/Users/ethan/Documents/rootFiles/processedRootFiles/TTToSemiLeptonicMC_" + year +"_nom_processed.root").c_str() );

  TFile *f7 = new TFile(("/Users/ethan/Documents/rootFiles/processedRootFiles/ST_s-channel-hadronsMC_" + year +"_nom_processed.root").c_str() );
  TFile *f8 = new TFile(("/Users/ethan/Documents/rootFiles/processedRootFiles/ST_s-channel-leptonsMC_" + year +"_nom_processed.root").c_str() );
  TFile *f9 = new TFile(("/Users/ethan/Documents/rootFiles/processedRootFiles/ST_t-channel-antitop_inclMC_" + year +"_nom_processed.root").c_str() );
  TFile *f10 = new TFile(("/Users/ethan/Documents/rootFiles/processedRootFiles/ST_t-channel-top_inclMC_" + year +"_nom_processed.root").c_str() );
  TFile *f11 = new TFile(("/Users/ethan/Documents/rootFiles/processedRootFiles/ST_tW-antiTop_inclMC_" + year +"_nom_processed.root").c_str() );
  TFile *f12 = new TFile(("/Users/ethan/Documents/rootFiles/processedRootFiles/ST_tW-top_inclMC_" + year +"_nom_processed.root").c_str() );


  std::vector<TFile*> dataFiles;
  if(year == "2018")
  {
    dataFiles.push_back(new TFile("/Users/ethan/Documents/rootFiles/processedRootFiles/dataA_2018_nom_processed.root"));
    dataFiles.push_back(new TFile("/Users/ethan/Documents/rootFiles/processedRootFiles/dataB_2018_nom_processed.root"));
    dataFiles.push_back(new TFile("/Users/ethan/Documents/rootFiles/processedRootFiles/dataC_2018_nom_processed.root"));
    dataFiles.push_back(new TFile("/Users/ethan/Documents/rootFiles/processedRootFiles/dataD_2018_nom_processed.root"));
  }
  else if(year=="2017")
  {
    dataFiles.push_back(new TFile("/Users/ethan/Documents/rootFiles/processedRootFiles/dataB_2017_nom_processed.root"));
    dataFiles.push_back(new TFile("/Users/ethan/Documents/rootFiles/processedRootFiles/dataC_2017_nom_processed.root"));
    dataFiles.push_back(new TFile("/Users/ethan/Documents/rootFiles/processedRootFiles/dataD_2017_nom_processed.root"));
    dataFiles.push_back(new TFile("/Users/ethan/Documents/rootFiles/processedRootFiles/dataE_2017_nom_processed.root"));
    dataFiles.push_back(new TFile("/Users/ethan/Documents/rootFiles/processedRootFiles/dataF_2017_nom_processed.root"));
  }
  else if(year=="2016")
  {
    dataFiles.push_back(new TFile("/Users/ethan/Documents/rootFiles/processedRootFiles/dataF_2016_nom_processed.root"));
    dataFiles.push_back(new TFile("/Users/ethan/Documents/rootFiles/processedRootFiles/dataG_2016_nom_processed.root"));
    dataFiles.push_back(new TFile("/Users/ethan/Documents/rootFiles/processedRootFiles/dataH_2016_nom_processed.root"));
  }
  

  // get MC
  TH1F *h_SJ_mass_CR_HT1000to1500_antiTag_1b = (TH1F*)f1->Get("nom_/h_SJ_mass_antiTag_1b");
  TH1F *h_SJ_mass_CR_HT1500to2000_antiTag_1b = (TH1F*)f2->Get("nom_/h_SJ_mass_antiTag_1b");
  TH1F *h_SJ_mass_CR_HT2000toInf_antiTag_1b = (TH1F*)f3->Get("nom_/h_SJ_mass_antiTag_1b");

  TH1F *h_SJ_mass_CR_TTToHadronicMC_antiTag_1b = (TH1F*)f4->Get("nom_/h_SJ_mass_antiTag_1b");
  TH1F *h_SJ_mass_CR_TTToLeptonicMC_antiTag_1b = (TH1F*)f5->Get("nom_/h_SJ_mass_antiTag_1b");
  TH1F *h_SJ_mass_CR_TTToSemiLeptonicMC_antiTag_1b = (TH1F*)f6->Get("nom_/h_SJ_mass_antiTag_1b");

  TH1F *h_SJ_mass_CR_ST_s_channel_hadronsMC_antiTag_1b = (TH1F*)f7->Get("nom_/h_SJ_mass_antiTag_1b");
  TH1F *h_SJ_mass_CR_ST_s_channel_leptonsMC_antiTag_1b = (TH1F*)f8->Get("nom_/h_SJ_mass_antiTag_1b");
  TH1F *h_SJ_mass_CR_ST_t_channel_antitop_antiTag_1b = (TH1F*)f9->Get("nom_/h_SJ_mass_antiTag_1b");
  TH1F *h_SJ_mass_CR_ST_t_channel_top_antiTag_1b = (TH1F*)f10->Get("nom_/h_SJ_mass_antiTag_1b");
  TH1F *h_SJ_mass_CR_ST_tW_antiTop_antiTag_1b = (TH1F*)f11->Get("nom_/h_SJ_mass_antiTag_1b");
  TH1F *h_SJ_mass_CR_ST_tW_top_antiTag_1b = (TH1F*)f12->Get("nom_/h_SJ_mass_antiTag_1b");

  // scale MC

  h_SJ_mass_CR_HT1000to1500_antiTag_1b->Scale(QCD1000to1500_SF[SF_index]);
  h_SJ_mass_CR_HT1500to2000_antiTag_1b->Scale(QCD1500to2000_SF[SF_index]);
  h_SJ_mass_CR_HT2000toInf_antiTag_1b->Scale(QCD2000toInf_SF[SF_index]);
  h_SJ_mass_CR_TTToHadronicMC_antiTag_1b->Scale(h_TTToHadronic_SF[SF_index]);
  h_SJ_mass_CR_TTToLeptonicMC_antiTag_1b->Scale(h_TTTo2l2nu_SF[SF_index]);
  h_SJ_mass_CR_TTToSemiLeptonicMC_antiTag_1b->Scale(h_TTToSemiLeptonic_SF[SF_index]);
  h_SJ_mass_CR_ST_s_channel_hadronsMC_antiTag_1b->Scale(ST_s_channel_4f_hadrons_SF[SF_index]);
  h_SJ_mass_CR_ST_s_channel_leptonsMC_antiTag_1b->Scale(ST_s_channel_4f_leptons_SF[SF_index]);
  h_SJ_mass_CR_ST_t_channel_antitop_antiTag_1b->Scale(ST_t_channel_antitop_5f_SF[SF_index]);
  h_SJ_mass_CR_ST_t_channel_top_antiTag_1b->Scale(ST_t_channel_top_5f_SF[SF_index]);
  h_SJ_mass_CR_ST_tW_antiTop_antiTag_1b->Scale(ST_tW_antitop_5f_SF[SF_index]);
  h_SJ_mass_CR_ST_tW_top_antiTag_1b->Scale(ST_tW_top_5f_SF[SF_index]);

  // add MC
  TH1F *h_SJ_mass_allBR_antiTag_1b = new TH1F(*h_SJ_mass_CR_HT1000to1500_antiTag_1b);

  h_SJ_mass_allBR_antiTag_1b->Add(h_SJ_mass_CR_HT1500to2000_antiTag_1b);
  h_SJ_mass_allBR_antiTag_1b->Add(h_SJ_mass_CR_HT2000toInf_antiTag_1b);
  h_SJ_mass_allBR_antiTag_1b->Add(h_SJ_mass_CR_TTToHadronicMC_antiTag_1b);
  h_SJ_mass_allBR_antiTag_1b->Add(h_SJ_mass_CR_TTToLeptonicMC_antiTag_1b);
  h_SJ_mass_allBR_antiTag_1b->Add(h_SJ_mass_CR_TTToSemiLeptonicMC_antiTag_1b);
  h_SJ_mass_allBR_antiTag_1b->Add(h_SJ_mass_CR_ST_s_channel_hadronsMC_antiTag_1b);
  h_SJ_mass_allBR_antiTag_1b->Add(h_SJ_mass_CR_ST_s_channel_leptonsMC_antiTag_1b);
  h_SJ_mass_allBR_antiTag_1b->Add(h_SJ_mass_CR_ST_t_channel_antitop_antiTag_1b);
  h_SJ_mass_allBR_antiTag_1b->Add(h_SJ_mass_CR_ST_t_channel_top_antiTag_1b);
  h_SJ_mass_allBR_antiTag_1b->Add(h_SJ_mass_CR_ST_tW_antiTop_antiTag_1b);
  h_SJ_mass_allBR_antiTag_1b->Add(h_SJ_mass_CR_ST_tW_top_antiTag_1b);

  std::vector<TH1F*>  h_SJ_mass_CR_data_hists_antiTag_1b  = get_histograms<TH1F*>(dataFiles, "h_SJ_mass_antiTag_1b");
  TH1F*  h_SJ_mass_allData_antiTag_1b  = combine_histograms<TH1F*>(h_SJ_mass_CR_data_hists_antiTag_1b);

  std::vector<TH1F*>  h_diSuperjet_mass_CR_data_hists_antiTag_1b  = get_histograms<TH1F*>(dataFiles, "h_disuperjet_mass_antiTag_1b");
  TH1F*  h_diSuperjet_mass_allData_antiTag_1b  = combine_histograms<TH1F*>(h_diSuperjet_mass_CR_data_hists_antiTag_1b);

  // create RP
  auto rp_SJ_mass_antiTag_1b = new TRatioPlot(h_SJ_mass_allData_antiTag_1b,h_SJ_mass_allBR_antiTag_1b);

  rp_SJ_mass_antiTag_1b->Draw("HIST,EP");
  rp_SJ_mass_antiTag_1b->GetLowerRefYaxis()->SetTitle("data/MC ratio");
  rp_SJ_mass_antiTag_1b->GetLowerRefGraph()->SetMaximum(2.);
  rp_SJ_mass_antiTag_1b->GetUpperRefYaxis()->SetTitle("Events");
  c1->SaveAs( (plot_home + "h_SJ_mass_antitag_1b_DataMC_ratio_"+ year+".png").c_str()); 


}



void makeAdHocRatio()
{
  std::vector<std::string> years = {};


  int counter == 0;

  for(auto year = input_files.begin(); year < input_files.end(); year++)
  {
    create_plot(year,counter );
  }
 


}
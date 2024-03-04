#include <iostream>
#include <string>
#include "TLorentzVector.h"
#include "TRatioPlot.h"
#include "THStack.h"
#include "TRatioPlot.h"
using namespace std;



template <typename T> std::vector<T> get_histograms(std::vector<TFile*> _files, std::string hist_name)
{

    std::vector<T> return_files;
    std::cout << "There are " <<_files.size() << " files found for this year" << std::endl;
    for(auto iii = _files.begin();iii<_files.end();iii++)
    {
      return_files.push_back( (T)(*iii)->Get( ("nom_/" + hist_name).c_str() )  );
      //std::cout << "File: " << typeid((T)(*iii)->Get( ("nom_/" + hist_name).c_str() )).name() << " " << std::endl;
    }
    return return_files;
}

template <typename T> T combine_histograms(std::vector<T> _hists)
{
  T comb_hist = T(_hists[0]);
  for(auto iii = _hists.begin() + 1;iii<_hists.end();iii++)
  {
    comb_hist->Add(*iii);
  }
  return comb_hist;
}

/*
template <typename T> void print_hists(std::string histName, std::string outputName, std::string ratioName = "data/MC")
{

  std::string getName = "nom_/"+ hist_name;
  T h_HT1000to1500 = (T)f1->Get( getName.c_str());
  T h_HT1500to2000 = (T)f2->Get( getName.c_str());
  T h_HT2000toInf = (T)f3->Get( getName.c_str());

  T h_TTToHadronicMC = (T)f4->Get( getName.c_str());
  T h_TTToLeptonicMC = (T)f5->Get( getName.c_str());
  T h_TTToSemiLeptonicMC = (T)f6->Get( getName.c_str());

  T h_ST_s_channel_hadronsMC = (T)f7->Get( getName.c_str());
  T h_ST_s_channel_leptonsMC = (T)f8->Get( getName.c_str());
  T h_ST_t_channel_antitop = (T)f9->Get( getName.c_str());
  T h_ST_t_channel_top = (T)f10->Get( getName.c_str());
  T h_ST_tW_antiTop = (T)f11->Get( getName.c_str());
  T h_ST_tW_top = (T)f12->Get( getName.c_str());


  std::vector<T>  h_data_hists  = get_histograms<T>(dataFiles, getName.c_str());
  T  h_all_data  = combine_histograms<T>(h_data_hists);

  h_HT1000to1500->Scale(QCD1000to1500_SF[SF_index]);
  h_HT1500to2000->Scale(QCD1500to2000_SF[SF_index]);
  h_HT2000toInf->Scale(QCD2000toInf_SF[SF_index]);
  h_TTToHadronicMC->Scale(h_TTToHadronic_SF[SF_index]);
  h_TTToLeptonicMC->Scale(h_TTTo2l2nu_SF[SF_index]);
  h_TTToSemiLeptonicMC->Scale(h_TTToSemiLeptonic_SF[SF_index]);
  h_ST_s_channel_hadronsMC->Scale(ST_s_channel_4f_hadrons_SF[SF_index]);
  h_ST_s_channel_leptonsMC->Scale(ST_s_channel_4f_leptons_SF[SF_index]);
  h_ST_t_channel_antitop->Scale(ST_t_channel_antitop_5f_SF[SF_index]);
  h_ST_t_channel_top->Scale(ST_t_channel_top_5f_SF[SF_index]);
  h_ST_tW_antiTop->Scale(ST_tW_antitop_5f_SF[SF_index]);
  h_ST_tW_top->Scale(ST_tW_top_5f_SF[SF_index]);

  T h_allBR = new T(*h_HT1000to1500);

  h_allBR->Add(h_HT1500to2000);
  h_allBR->Add(h_HT2000toInf);
  h_allBR->Add(h_TTToHadronicMC);
  h_allBR->Add(h_TTToLeptonicMC);
  h_allBR->Add(h_TTToSemiLeptonicMC);
  h_allBR->Add(h_ST_s_channel_hadronsMC);
  h_allBR->Add(h_ST_s_channel_leptonsMC);
  h_allBR->Add(h_ST_t_channel_antitop);
  h_allBR->Add(h_ST_t_channel_top);
  h_allBR->Add(h_ST_tW_antiTop);
  h_allBR->Add(h_ST_tW_top);


  h_allBR->GetXaxis()->SetRangeUser(0., 5000.);
  std::string plot_home = "/Users/ethan/Documents/plots/ratioPlots/";

  auto rp_nAK4 = new TRatioPlot(h_allData,h_allBR);
  //h_BR_combined->Draw("HIST");
  rp_nAK4->Draw("HIST,EP");
  rp_nAK4->GetLowerRefYaxis()->SetTitle( ratioName.c_str() );
  rp_nAK4->GetLowerRefGraph()->SetMaximum(2.);
  rp_nAK4->GetUpperRefYaxis()->SetTitle("Events");
  c1->SaveAs( (plot_home + outputName +""+ year+".png").c_str()); 

}

*/
void makeRatio()
{


  // make ratio plots between XXXX and MC for 2018

  double SuuToChiChi_MSuu8TeV_Mchi3TeV_SF = 1.93E-02;
  double SuuToChiChi_MSuu5TeV_Mchi2TeV_SF = 8.67E-01;

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





  //double h_TTJets2500toInf_SF  = 0.00008408965681;
  TCanvas *c1 = new TCanvas("c1","",400,20, 2000,1500);


  std::string year = "2018";

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
  std::string plot_home = "/Users/ethan/Documents/plots/ratioPlots/";
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

  //TFile *f13;TFile *f14;TFile *f15;TFile *f16;TFile *f18;
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
  // why is there no 2015??
  
  //create histogramas for each of the different plots for different HT levels, scale histograms, add together histograms, normalize, do division/ comparison


  /////// make CR anti-tag ratio plot
  // want to see the normalization difference between the two
  // want to see comparisons of the superjet and disuperjet masses
  // want to see 2D ratio plot
  std::vector<TH1F*>  h_SJ_mass_CR_data_hists_antiTag_0b  = get_histograms<TH1F*>(dataFiles, "h_SJ_mass_antiTagCR");
  TH1F*  h_SJ_mass_allData_0b_antiTag  = combine_histograms<TH1F*>(h_SJ_mass_CR_data_hists_antiTag_0b);

  std::vector<TH1F*>  h_diSuperjet_mass_CR_data_hists_antiTag_0b  = get_histograms<TH1F*>(dataFiles, "h_disuperjet_mass_antiTagCR");
  TH1F*  h_diSuperjet_mass_allData_0b_antiTag  = combine_histograms<TH1F*>(h_diSuperjet_mass_CR_data_hists_antiTag_0b);

  std::vector<TH2F*> h_MSJ_vs_MdiSJ_CR_data_hists_antiTag_0b = get_histograms<TH2F*>(dataFiles, "h_MSJ_mass_vs_MdSJ_antiTagCR");
  TH2F * h_MSJ_mass_vs_MdSJ_antiTagCR_allData_antiTag = combine_histograms<TH2F*>(h_MSJ_vs_MdiSJ_CR_data_hists_antiTag_0b);



  // make SJ_mass_comparison
  TH1F *h_SJ_mass_CR_HT1000to1500_antiTag = (TH1F*)f1->Get("nom_/h_SJ_mass_antiTagCR");
  TH1F *h_SJ_mass_CR_HT1500to2000_antiTag = (TH1F*)f2->Get("nom_/h_SJ_mass_antiTagCR");
  TH1F *h_SJ_mass_CR_HT2000toInf_antiTag = (TH1F*)f3->Get("nom_/h_SJ_mass_antiTagCR");

  TH1F *h_SJ_mass_CR_TTToHadronicMC_antiTag = (TH1F*)f4->Get("nom_/h_SJ_mass_antiTagCR");
  TH1F *h_SJ_mass_CR_TTToLeptonicMC_antiTag = (TH1F*)f5->Get("nom_/h_SJ_mass_antiTagCR");
  TH1F *h_SJ_mass_CR_TTToSemiLeptonicMC_antiTag = (TH1F*)f6->Get("nom_/h_SJ_mass_antiTagCR");

  TH1F *h_SJ_mass_CR_ST_s_channel_hadronsMC_antiTag = (TH1F*)f7->Get("nom_/h_SJ_mass_antiTagCR");
  TH1F *h_SJ_mass_CR_ST_s_channel_leptonsMC_antiTag = (TH1F*)f8->Get("nom_/h_SJ_mass_antiTagCR");
  TH1F *h_SJ_mass_CR_ST_t_channel_antitop_antiTag = (TH1F*)f9->Get("nom_/h_SJ_mass_antiTagCR");
  TH1F *h_SJ_mass_CR_ST_t_channel_top_antiTag = (TH1F*)f10->Get("nom_/h_SJ_mass_antiTagCR");
  TH1F *h_SJ_mass_CR_ST_tW_antiTop_antiTag = (TH1F*)f11->Get("nom_/h_SJ_mass_antiTagCR");
  TH1F *h_SJ_mass_CR_ST_tW_top_antiTag = (TH1F*)f12->Get("nom_/h_SJ_mass_antiTagCR");

  h_SJ_mass_CR_HT1000to1500_antiTag->Scale(QCD1000to1500_SF[SF_index]);
  h_SJ_mass_CR_HT1500to2000_antiTag->Scale(QCD1500to2000_SF[SF_index]);
  h_SJ_mass_CR_HT2000toInf_antiTag->Scale(QCD2000toInf_SF[SF_index]);
  h_SJ_mass_CR_TTToHadronicMC_antiTag->Scale(h_TTToHadronic_SF[SF_index]);
  h_SJ_mass_CR_TTToLeptonicMC_antiTag->Scale(h_TTTo2l2nu_SF[SF_index]);
  h_SJ_mass_CR_TTToSemiLeptonicMC_antiTag->Scale(h_TTToSemiLeptonic_SF[SF_index]);
  h_SJ_mass_CR_ST_s_channel_hadronsMC_antiTag->Scale(ST_s_channel_4f_hadrons_SF[SF_index]);
  h_SJ_mass_CR_ST_s_channel_leptonsMC_antiTag->Scale(ST_s_channel_4f_leptons_SF[SF_index]);
  h_SJ_mass_CR_ST_t_channel_antitop_antiTag->Scale(ST_t_channel_antitop_5f_SF[SF_index]);
  h_SJ_mass_CR_ST_t_channel_top_antiTag->Scale(ST_t_channel_top_5f_SF[SF_index]);
  h_SJ_mass_CR_ST_tW_antiTop_antiTag->Scale(ST_tW_antitop_5f_SF[SF_index]);
  h_SJ_mass_CR_ST_tW_top_antiTag->Scale(ST_tW_top_5f_SF[SF_index]);

  TH1F *h_SJ_mass_allBR_antiTag = new TH1F(*h_SJ_mass_CR_HT1000to1500_antiTag);

  h_SJ_mass_allBR_antiTag->Add(h_SJ_mass_CR_HT1500to2000_antiTag);
  h_SJ_mass_allBR_antiTag->Add(h_SJ_mass_CR_HT2000toInf_antiTag);
  h_SJ_mass_allBR_antiTag->Add(h_SJ_mass_CR_TTToHadronicMC_antiTag);
  h_SJ_mass_allBR_antiTag->Add(h_SJ_mass_CR_TTToLeptonicMC_antiTag);
  h_SJ_mass_allBR_antiTag->Add(h_SJ_mass_CR_TTToSemiLeptonicMC_antiTag);
  h_SJ_mass_allBR_antiTag->Add(h_SJ_mass_CR_ST_s_channel_hadronsMC_antiTag);
  h_SJ_mass_allBR_antiTag->Add(h_SJ_mass_CR_ST_s_channel_leptonsMC_antiTag);
  h_SJ_mass_allBR_antiTag->Add(h_SJ_mass_CR_ST_t_channel_antitop_antiTag);
  h_SJ_mass_allBR_antiTag->Add(h_SJ_mass_CR_ST_t_channel_top_antiTag);
  h_SJ_mass_allBR_antiTag->Add(h_SJ_mass_CR_ST_tW_antiTop_antiTag);
  h_SJ_mass_allBR_antiTag->Add(h_SJ_mass_CR_ST_tW_top_antiTag);
  h_SJ_mass_allData_0b_antiTag->SetTitle("SJ Mass Shape Ratio of 0b antiTag data to 0b antiTag MC ");
  auto rp_SJ_mass_antiTag = new TRatioPlot(h_SJ_mass_allData_0b_antiTag,h_SJ_mass_allBR_antiTag);
  //h_BR_combined->Draw("HIST");

  rp_SJ_mass_antiTag->Draw("HIST,EP");
  rp_SJ_mass_antiTag->GetLowerRefYaxis()->SetTitle("data/MC ratio");
  rp_SJ_mass_antiTag->GetLowerRefGraph()->SetMaximum(2.);
  rp_SJ_mass_antiTag->GetUpperRefYaxis()->SetTitle("Events");
  c1->SaveAs( (plot_home + "h_SJ_mass_antitag_DataMC_ratio_"+ year+".png").c_str()); 

  ///// disuperjet mass ratio 
  TH1F *h_disuperjet_mass_antiTagCR_HT1000to1500 = (TH1F*)f1->Get("nom_/h_disuperjet_mass_antiTagCR");
  TH1F *h_disuperjet_mass_antiTagCR_HT1500to2000 = (TH1F*)f2->Get("nom_/h_disuperjet_mass_antiTagCR");
  TH1F *h_disuperjet_mass_antiTagCR_HT2000toInf = (TH1F*)f3->Get("nom_/h_disuperjet_mass_antiTagCR");

  TH1F *h_disuperjet_mass_antiTagCR_TTToHadronicMC = (TH1F*)f4->Get("nom_/h_disuperjet_mass_antiTagCR");
  TH1F *h_disuperjet_mass_antiTagCR_TTToLeptonicMC = (TH1F*)f5->Get("nom_/h_disuperjet_mass_antiTagCR");
  TH1F *h_disuperjet_mass_antiTagCR_TTToSemiLeptonicMC = (TH1F*)f6->Get("nom_/h_disuperjet_mass_antiTagCR");

  TH1F *h_disuperjet_mass_antiTagCR_ST_s_channel_hadronsMC = (TH1F*)f7->Get("nom_/h_disuperjet_mass_antiTagCR");
  TH1F *h_disuperjet_mass_antiTagCR_ST_s_channel_leptonsMC = (TH1F*)f8->Get("nom_/h_disuperjet_mass_antiTagCR");
  TH1F *h_disuperjet_mass_antiTagCR_ST_t_channel_antitop = (TH1F*)f9->Get("nom_/h_disuperjet_mass_antiTagCR");
  TH1F *h_disuperjet_mass_antiTagCR_ST_t_channel_top = (TH1F*)f10->Get("nom_/h_disuperjet_mass_antiTagCR");
  TH1F *h_disuperjet_mass_antiTagCR_ST_tW_antiTop = (TH1F*)f11->Get("nom_/h_disuperjet_mass_antiTagCR");
  TH1F *h_disuperjet_mass_antiTagCR_ST_tW_top = (TH1F*)f12->Get("nom_/h_disuperjet_mass_antiTagCR");

  h_disuperjet_mass_antiTagCR_HT1000to1500->Scale(QCD1000to1500_SF[SF_index]);
  h_disuperjet_mass_antiTagCR_HT1500to2000->Scale(QCD1500to2000_SF[SF_index]);
  h_disuperjet_mass_antiTagCR_HT2000toInf->Scale(QCD2000toInf_SF[SF_index]);
  h_disuperjet_mass_antiTagCR_TTToHadronicMC->Scale(h_TTToHadronic_SF[SF_index]);
  h_disuperjet_mass_antiTagCR_TTToLeptonicMC->Scale(h_TTTo2l2nu_SF[SF_index]);
  h_disuperjet_mass_antiTagCR_TTToSemiLeptonicMC->Scale(h_TTToSemiLeptonic_SF[SF_index]);
  h_disuperjet_mass_antiTagCR_ST_s_channel_hadronsMC->Scale(ST_s_channel_4f_hadrons_SF[SF_index]);
  h_disuperjet_mass_antiTagCR_ST_s_channel_leptonsMC->Scale(ST_s_channel_4f_leptons_SF[SF_index]);
  h_disuperjet_mass_antiTagCR_ST_t_channel_antitop->Scale(ST_t_channel_antitop_5f_SF[SF_index]);
  h_disuperjet_mass_antiTagCR_ST_t_channel_top->Scale(ST_t_channel_top_5f_SF[SF_index]);
  h_disuperjet_mass_antiTagCR_ST_tW_antiTop->Scale(ST_tW_antitop_5f_SF[SF_index]);
  h_disuperjet_mass_antiTagCR_ST_tW_top->Scale(ST_tW_top_5f_SF[SF_index]);

  TH1F *h_diSuperjet_mass_allBR_antiTag = new TH1F(*h_disuperjet_mass_antiTagCR_HT1000to1500);

  h_diSuperjet_mass_allBR_antiTag->Add(h_disuperjet_mass_antiTagCR_HT1500to2000);
  h_diSuperjet_mass_allBR_antiTag->Add(h_disuperjet_mass_antiTagCR_HT2000toInf);
  h_diSuperjet_mass_allBR_antiTag->Add(h_disuperjet_mass_antiTagCR_TTToHadronicMC);
  h_diSuperjet_mass_allBR_antiTag->Add(h_disuperjet_mass_antiTagCR_TTToLeptonicMC);
  h_diSuperjet_mass_allBR_antiTag->Add(h_disuperjet_mass_antiTagCR_TTToSemiLeptonicMC);
  h_diSuperjet_mass_allBR_antiTag->Add(h_disuperjet_mass_antiTagCR_ST_s_channel_hadronsMC);
  h_diSuperjet_mass_allBR_antiTag->Add(h_disuperjet_mass_antiTagCR_ST_s_channel_leptonsMC);
  h_diSuperjet_mass_allBR_antiTag->Add(h_disuperjet_mass_antiTagCR_ST_t_channel_antitop);
  h_diSuperjet_mass_allBR_antiTag->Add(h_disuperjet_mass_antiTagCR_ST_t_channel_top);
  h_diSuperjet_mass_allBR_antiTag->Add(h_disuperjet_mass_antiTagCR_ST_tW_antiTop);
  h_diSuperjet_mass_allBR_antiTag->Add(h_disuperjet_mass_antiTagCR_ST_tW_top);


  h_diSuperjet_mass_allData_0b_antiTag->SetTitle("diSuperjet Mass Shape Ratio of 0b antiTag data to 0b antiTag MC ");

  auto rp_diSuperjet_mass_antiTag = new TRatioPlot(h_diSuperjet_mass_allData_0b_antiTag,h_diSuperjet_mass_allBR_antiTag);
  //h_BR_combined->Draw("HIST");

  rp_diSuperjet_mass_antiTag->Draw("HIST,EP");
  rp_diSuperjet_mass_antiTag->GetLowerRefYaxis()->SetTitle("data/MC ratio");
  rp_diSuperjet_mass_antiTag->GetLowerRefGraph()->SetMaximum(2.);
  rp_diSuperjet_mass_antiTag->GetUpperRefYaxis()->SetTitle("Events");
  c1->SaveAs( (plot_home + "h_diSuperjet_mass_antitag_DataMC_ratio_"+ year+".png").c_str()); 



  ////// 2D ratio plot

  ///// disuperjet mass ratio 
  TH2F *h_MSJ_mass_vs_MdSJ_antiTagCR_HT1000to1500 = (TH2F*)f1->Get("nom_/h_MSJ_mass_vs_MdSJ_antiTagCR");
  TH2F *h_MSJ_mass_vs_MdSJ_antiTagCR_HT1500to2000 = (TH2F*)f2->Get("nom_/h_MSJ_mass_vs_MdSJ_antiTagCR");
  TH2F *h_MSJ_mass_vs_MdSJ_antiTagCR_HT2000toInf = (TH2F*)f3->Get("nom_/h_MSJ_mass_vs_MdSJ_antiTagCR");

  TH2F *h_MSJ_mass_vs_MdSJ_antiTagCR_TTToHadronicMC = (TH2F*)f4->Get("nom_/h_MSJ_mass_vs_MdSJ_antiTagCR");
  TH2F *h_MSJ_mass_vs_MdSJ_antiTagCR_TTToLeptonicMC = (TH2F*)f5->Get("nom_/h_MSJ_mass_vs_MdSJ_antiTagCR");
  TH2F *h_MSJ_mass_vs_MdSJ_antiTagCR_TTToSemiLeptonicMC = (TH2F*)f6->Get("nom_/h_MSJ_mass_vs_MdSJ_antiTagCR");

  TH2F *h_MSJ_mass_vs_MdSJ_antiTagCR_ST_s_channel_hadronsMC = (TH2F*)f7->Get("nom_/h_MSJ_mass_vs_MdSJ_antiTagCR");
  TH2F *h_MSJ_mass_vs_MdSJ_antiTagCR_ST_s_channel_leptonsMC = (TH2F*)f8->Get("nom_/h_MSJ_mass_vs_MdSJ_antiTagCR");
  TH2F *h_MSJ_mass_vs_MdSJ_antiTagCR_ST_t_channel_antitop = (TH2F*)f9->Get("nom_/h_MSJ_mass_vs_MdSJ_antiTagCR");
  TH2F *h_MSJ_mass_vs_MdSJ_antiTagCR_ST_t_channel_top = (TH2F*)f10->Get("nom_/h_MSJ_mass_vs_MdSJ_antiTagCR");
  TH2F *h_MSJ_mass_vs_MdSJ_antiTagCR_ST_tW_antiTop = (TH2F*)f11->Get("nom_/h_MSJ_mass_vs_MdSJ_antiTagCR");
  TH2F *h_MSJ_mass_vs_MdSJ_antiTagCR_ST_tW_top = (TH2F*)f12->Get("nom_/h_MSJ_mass_vs_MdSJ_antiTagCR");

  h_MSJ_mass_vs_MdSJ_antiTagCR_HT1000to1500->Scale(QCD1000to1500_SF[SF_index]);
  h_MSJ_mass_vs_MdSJ_antiTagCR_HT1500to2000->Scale(QCD1500to2000_SF[SF_index]);
  h_MSJ_mass_vs_MdSJ_antiTagCR_HT2000toInf->Scale(QCD2000toInf_SF[SF_index]);
  h_MSJ_mass_vs_MdSJ_antiTagCR_TTToHadronicMC->Scale(h_TTToHadronic_SF[SF_index]);
  h_MSJ_mass_vs_MdSJ_antiTagCR_TTToLeptonicMC->Scale(h_TTTo2l2nu_SF[SF_index]);
  h_MSJ_mass_vs_MdSJ_antiTagCR_TTToSemiLeptonicMC->Scale(h_TTToSemiLeptonic_SF[SF_index]);
  h_MSJ_mass_vs_MdSJ_antiTagCR_ST_s_channel_hadronsMC->Scale(ST_s_channel_4f_hadrons_SF[SF_index]);
  h_MSJ_mass_vs_MdSJ_antiTagCR_ST_s_channel_leptonsMC->Scale(ST_s_channel_4f_leptons_SF[SF_index]);
  h_MSJ_mass_vs_MdSJ_antiTagCR_ST_t_channel_antitop->Scale(ST_t_channel_antitop_5f_SF[SF_index]);
  h_MSJ_mass_vs_MdSJ_antiTagCR_ST_t_channel_top->Scale(ST_t_channel_top_5f_SF[SF_index]);
  h_MSJ_mass_vs_MdSJ_antiTagCR_ST_tW_antiTop->Scale(ST_tW_antitop_5f_SF[SF_index]);
  h_MSJ_mass_vs_MdSJ_antiTagCR_ST_tW_top->Scale(ST_tW_top_5f_SF[SF_index]);

  TH2F *h_MSJ_mass_vs_MdSJ_antiTagCR_allBR_antiTag = new TH2F(*h_MSJ_mass_vs_MdSJ_antiTagCR_HT1000to1500);


  h_MSJ_mass_vs_MdSJ_antiTagCR_allBR_antiTag->Add(h_MSJ_mass_vs_MdSJ_antiTagCR_HT1500to2000);
  h_MSJ_mass_vs_MdSJ_antiTagCR_allBR_antiTag->Add(h_MSJ_mass_vs_MdSJ_antiTagCR_HT2000toInf);
  h_MSJ_mass_vs_MdSJ_antiTagCR_allBR_antiTag->Add(h_MSJ_mass_vs_MdSJ_antiTagCR_TTToHadronicMC);
  h_MSJ_mass_vs_MdSJ_antiTagCR_allBR_antiTag->Add(h_MSJ_mass_vs_MdSJ_antiTagCR_TTToLeptonicMC);
  h_MSJ_mass_vs_MdSJ_antiTagCR_allBR_antiTag->Add(h_MSJ_mass_vs_MdSJ_antiTagCR_TTToSemiLeptonicMC);
  h_MSJ_mass_vs_MdSJ_antiTagCR_allBR_antiTag->Add(h_MSJ_mass_vs_MdSJ_antiTagCR_ST_s_channel_hadronsMC);
  h_MSJ_mass_vs_MdSJ_antiTagCR_allBR_antiTag->Add(h_MSJ_mass_vs_MdSJ_antiTagCR_ST_s_channel_leptonsMC);
  h_MSJ_mass_vs_MdSJ_antiTagCR_allBR_antiTag->Add(h_MSJ_mass_vs_MdSJ_antiTagCR_ST_t_channel_antitop);
  h_MSJ_mass_vs_MdSJ_antiTagCR_allBR_antiTag->Add(h_MSJ_mass_vs_MdSJ_antiTagCR_ST_t_channel_top);
  h_MSJ_mass_vs_MdSJ_antiTagCR_allBR_antiTag->Add(h_MSJ_mass_vs_MdSJ_antiTagCR_ST_tW_antiTop);
  h_MSJ_mass_vs_MdSJ_antiTagCR_allBR_antiTag->Add(h_MSJ_mass_vs_MdSJ_antiTagCR_ST_tW_top);


  gStyle->SetOptStat(0);


  h_MSJ_mass_vs_MdSJ_antiTagCR_allBR_antiTag->Draw("colz");
  c1->SaveAs( (plot_home + "h_MSJ_mass_vs_MdSJ_antiTagCR_allBR_antiTag_"+ year+".png").c_str());

  h_MSJ_mass_vs_MdSJ_antiTagCR_allData_antiTag->Draw("colz");
  c1->SaveAs( (plot_home + "h_MSJ_mass_vs_MdSJ_antiTagCR_allData_antiTag_"+ year+".png").c_str());

  TH2F * ratio_2D_hist = (TH2F*) h_MSJ_mass_vs_MdSJ_antiTagCR_allData_antiTag->Clone();

  ratio_2D_hist->Divide(h_MSJ_mass_vs_MdSJ_antiTagCR_allBR_antiTag);

  ratio_2D_hist->SetTitle("data/MC ratio in the 0 b-jet anti-tag region (2018)");
  ratio_2D_hist->SetMaximum(5.0); 
  ratio_2D_hist->Draw("colz");
  c1->SaveAs( (plot_home + "h_MSJ_mass_vs_MdSJ_antiTagCR_antitag_DataMC_ratio_"+ year+".png").c_str());












  //////////// 1 b-tag anti-tag region comparisons //////////////


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

  std::vector<TH1F*>  h_SJ_mass_CR_data_hists_antiTag_1b  = get_histograms<TH1F*>(dataFiles, "h_SJ_mass_antiTag_1b");
  TH1F*  h_SJ_mass_allData_antiTag_1b  = combine_histograms<TH1F*>(h_SJ_mass_CR_data_hists_antiTag_1b);

  std::vector<TH1F*>  h_diSuperjet_mass_CR_data_hists_antiTag_1b  = get_histograms<TH1F*>(dataFiles, "h_disuperjet_mass_antiTag_1b");
  TH1F*  h_diSuperjet_mass_allData_antiTag_1b  = combine_histograms<TH1F*>(h_diSuperjet_mass_CR_data_hists_antiTag_1b);

  std::vector<TH2F*> h_MSJ_vs_MdiSJ_CR_data_hists_antiTag_1b = get_histograms<TH2F*>(dataFiles, "h_MSJ_mass_vs_MdSJ_antiTag_1b");
  TH2F * h_MSJ_mass_vs_MdSJ_antiTag_1b_allData_antiTag_1b = combine_histograms<TH2F*>(h_MSJ_vs_MdiSJ_CR_data_hists_antiTag_1b);


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


  double data_MC_SF_1b_antiTag = h_SJ_mass_allBR_antiTag_1b->Integral() / h_SJ_mass_allData_antiTag_1b->Integral();

  //h_SJ_mass_allData_antiTag_1b->Scale(data_MC_SF_1b_antiTag);    //// SCALING Data

  h_SJ_mass_allData_antiTag_1b->SetTitle("SJ Mass Shape Ratio of 1b antiTag data to 1b antiTag MC ");

  auto rp_SJ_mass_antiTag_1b = new TRatioPlot(h_SJ_mass_allData_antiTag_1b,h_SJ_mass_allBR_antiTag_1b);
  //h_BR_combined->Draw("HIST");

  rp_SJ_mass_antiTag_1b->Draw("HIST,EP");
  rp_SJ_mass_antiTag_1b->GetLowerRefYaxis()->SetTitle("data/MC ratio");
  rp_SJ_mass_antiTag_1b->GetLowerRefGraph()->SetMaximum(2.);
  rp_SJ_mass_antiTag_1b->GetUpperRefYaxis()->SetTitle("Events");
  c1->SaveAs( (plot_home + "h_SJ_mass_antitag_1b_DataMC_ratio_"+ year+".png").c_str()); 


  // compare yields 
  std::cout << "data/MC total yields are " <<h_SJ_mass_allData_antiTag_1b->Integral() << "/" << h_SJ_mass_allBR_antiTag_1b->Integral()<< std::endl;

  ///// disuperjet mass ratio 
  TH1F *h_disuperjet_mass_antiTag_1b_HT1000to1500 = (TH1F*)f1->Get("nom_/h_disuperjet_mass_antiTag_1b");
  TH1F *h_disuperjet_mass_antiTag_1b_HT1500to2000 = (TH1F*)f2->Get("nom_/h_disuperjet_mass_antiTag_1b");
  TH1F *h_disuperjet_mass_antiTag_1b_HT2000toInf = (TH1F*)f3->Get("nom_/h_disuperjet_mass_antiTag_1b");

  TH1F *h_disuperjet_mass_antiTag_1b_TTToHadronicMC = (TH1F*)f4->Get("nom_/h_disuperjet_mass_antiTag_1b");
  TH1F *h_disuperjet_mass_antiTag_1b_TTToLeptonicMC = (TH1F*)f5->Get("nom_/h_disuperjet_mass_antiTag_1b");
  TH1F *h_disuperjet_mass_antiTag_1b_TTToSemiLeptonicMC = (TH1F*)f6->Get("nom_/h_disuperjet_mass_antiTag_1b");

  TH1F *h_disuperjet_mass_antiTag_1b_ST_s_channel_hadronsMC = (TH1F*)f7->Get("nom_/h_disuperjet_mass_antiTag_1b");
  TH1F *h_disuperjet_mass_antiTag_1b_ST_s_channel_leptonsMC = (TH1F*)f8->Get("nom_/h_disuperjet_mass_antiTag_1b");
  TH1F *h_disuperjet_mass_antiTag_1b_ST_t_channel_antitop = (TH1F*)f9->Get("nom_/h_disuperjet_mass_antiTag_1b");
  TH1F *h_disuperjet_mass_antiTag_1b_ST_t_channel_top = (TH1F*)f10->Get("nom_/h_disuperjet_mass_antiTag_1b");
  TH1F *h_disuperjet_mass_antiTag_1b_ST_tW_antiTop = (TH1F*)f11->Get("nom_/h_disuperjet_mass_antiTag_1b");
  TH1F *h_disuperjet_mass_antiTag_1b_ST_tW_top = (TH1F*)f12->Get("nom_/h_disuperjet_mass_antiTag_1b");

  h_disuperjet_mass_antiTag_1b_HT1000to1500->Scale(QCD1000to1500_SF[SF_index]);
  h_disuperjet_mass_antiTag_1b_HT1500to2000->Scale(QCD1500to2000_SF[SF_index]);
  h_disuperjet_mass_antiTag_1b_HT2000toInf->Scale(QCD2000toInf_SF[SF_index]);
  h_disuperjet_mass_antiTag_1b_TTToHadronicMC->Scale(h_TTToHadronic_SF[SF_index]);
  h_disuperjet_mass_antiTag_1b_TTToLeptonicMC->Scale(h_TTTo2l2nu_SF[SF_index]);
  h_disuperjet_mass_antiTag_1b_TTToSemiLeptonicMC->Scale(h_TTToSemiLeptonic_SF[SF_index]);
  h_disuperjet_mass_antiTag_1b_ST_s_channel_hadronsMC->Scale(ST_s_channel_4f_hadrons_SF[SF_index]);
  h_disuperjet_mass_antiTag_1b_ST_s_channel_leptonsMC->Scale(ST_s_channel_4f_leptons_SF[SF_index]);
  h_disuperjet_mass_antiTag_1b_ST_t_channel_antitop->Scale(ST_t_channel_antitop_5f_SF[SF_index]);
  h_disuperjet_mass_antiTag_1b_ST_t_channel_top->Scale(ST_t_channel_top_5f_SF[SF_index]);
  h_disuperjet_mass_antiTag_1b_ST_tW_antiTop->Scale(ST_tW_antitop_5f_SF[SF_index]);
  h_disuperjet_mass_antiTag_1b_ST_tW_top->Scale(ST_tW_top_5f_SF[SF_index]);

  TH1F *h_diSuperjet_mass_allBR_antiTag_1b = new TH1F(*h_disuperjet_mass_antiTag_1b_HT1000to1500);

  h_diSuperjet_mass_allBR_antiTag_1b->Add(h_disuperjet_mass_antiTag_1b_HT1500to2000);
  h_diSuperjet_mass_allBR_antiTag_1b->Add(h_disuperjet_mass_antiTag_1b_HT2000toInf);
  h_diSuperjet_mass_allBR_antiTag_1b->Add(h_disuperjet_mass_antiTag_1b_TTToHadronicMC);
  h_diSuperjet_mass_allBR_antiTag_1b->Add(h_disuperjet_mass_antiTag_1b_TTToLeptonicMC);
  h_diSuperjet_mass_allBR_antiTag_1b->Add(h_disuperjet_mass_antiTag_1b_TTToSemiLeptonicMC);
  h_diSuperjet_mass_allBR_antiTag_1b->Add(h_disuperjet_mass_antiTag_1b_ST_s_channel_hadronsMC);
  h_diSuperjet_mass_allBR_antiTag_1b->Add(h_disuperjet_mass_antiTag_1b_ST_s_channel_leptonsMC);
  h_diSuperjet_mass_allBR_antiTag_1b->Add(h_disuperjet_mass_antiTag_1b_ST_t_channel_antitop);
  h_diSuperjet_mass_allBR_antiTag_1b->Add(h_disuperjet_mass_antiTag_1b_ST_t_channel_top);
  h_diSuperjet_mass_allBR_antiTag_1b->Add(h_disuperjet_mass_antiTag_1b_ST_tW_antiTop);
  h_diSuperjet_mass_allBR_antiTag_1b->Add(h_disuperjet_mass_antiTag_1b_ST_tW_top);

  h_diSuperjet_mass_allBR_antiTag_1b->GetXaxis()->SetRangeUser(0., 5000.);


  //h_diSuperjet_mass_allData_antiTag_1b->Scale(data_MC_SF_1b_antiTag);   //// SCALING Data


  h_diSuperjet_mass_allData_antiTag_1b->GetXaxis()->SetRangeUser(0., 5000.);



  auto rp_diSuperjet_mass_antiTag_1b = new TRatioPlot(h_diSuperjet_mass_allData_antiTag_1b,h_diSuperjet_mass_allBR_antiTag_1b);
  //h_BR_combined->Draw("HIST");
  c1->SetTitle("diSuperjet Mass Shape Ratio of 1b antiTag data to 1b antiTag MC ");

  rp_diSuperjet_mass_antiTag_1b->Draw("HIST,EP");
  rp_diSuperjet_mass_antiTag_1b->GetLowerRefYaxis()->SetTitle("data/MC ratio");
  rp_diSuperjet_mass_antiTag_1b->GetLowerRefGraph()->SetMaximum(2.);
  rp_diSuperjet_mass_antiTag_1b->GetUpperRefYaxis()->SetTitle("Events");
  c1->SaveAs( (plot_home + "h_diSuperjet_mass_antitag_1b_DataMC_ratio_"+ year+".png").c_str()); 



  ////// 2D ratio plot

  ///// disuperjet mass ratio 
  TH2F *h_MSJ_mass_vs_MdSJ_antiTag_1b_HT1000to1500 = (TH2F*)f1->Get("nom_/h_MSJ_mass_vs_MdSJ_antiTag_1b");
  TH2F *h_MSJ_mass_vs_MdSJ_antiTag_1b_HT1500to2000 = (TH2F*)f2->Get("nom_/h_MSJ_mass_vs_MdSJ_antiTag_1b");
  TH2F *h_MSJ_mass_vs_MdSJ_antiTag_1b_HT2000toInf = (TH2F*)f3->Get("nom_/h_MSJ_mass_vs_MdSJ_antiTag_1b");

  TH2F *h_MSJ_mass_vs_MdSJ_antiTag_1b_TTToHadronicMC = (TH2F*)f4->Get("nom_/h_MSJ_mass_vs_MdSJ_antiTag_1b");
  TH2F *h_MSJ_mass_vs_MdSJ_antiTag_1b_TTToLeptonicMC = (TH2F*)f5->Get("nom_/h_MSJ_mass_vs_MdSJ_antiTag_1b");
  TH2F *h_MSJ_mass_vs_MdSJ_antiTag_1b_TTToSemiLeptonicMC = (TH2F*)f6->Get("nom_/h_MSJ_mass_vs_MdSJ_antiTag_1b");

  TH2F *h_MSJ_mass_vs_MdSJ_antiTag_1b_ST_s_channel_hadronsMC = (TH2F*)f7->Get("nom_/h_MSJ_mass_vs_MdSJ_antiTag_1b");
  TH2F *h_MSJ_mass_vs_MdSJ_antiTag_1b_ST_s_channel_leptonsMC = (TH2F*)f8->Get("nom_/h_MSJ_mass_vs_MdSJ_antiTag_1b");
  TH2F *h_MSJ_mass_vs_MdSJ_antiTag_1b_ST_t_channel_antitop = (TH2F*)f9->Get("nom_/h_MSJ_mass_vs_MdSJ_antiTag_1b");
  TH2F *h_MSJ_mass_vs_MdSJ_antiTag_1b_ST_t_channel_top = (TH2F*)f10->Get("nom_/h_MSJ_mass_vs_MdSJ_antiTag_1b");
  TH2F *h_MSJ_mass_vs_MdSJ_antiTag_1b_ST_tW_antiTop = (TH2F*)f11->Get("nom_/h_MSJ_mass_vs_MdSJ_antiTag_1b");
  TH2F *h_MSJ_mass_vs_MdSJ_antiTag_1b_ST_tW_top = (TH2F*)f12->Get("nom_/h_MSJ_mass_vs_MdSJ_antiTag_1b");

  h_MSJ_mass_vs_MdSJ_antiTag_1b_HT1000to1500->Scale(QCD1000to1500_SF[SF_index]);
  h_MSJ_mass_vs_MdSJ_antiTag_1b_HT1500to2000->Scale(QCD1500to2000_SF[SF_index]);
  h_MSJ_mass_vs_MdSJ_antiTag_1b_HT2000toInf->Scale(QCD2000toInf_SF[SF_index]);
  h_MSJ_mass_vs_MdSJ_antiTag_1b_TTToHadronicMC->Scale(h_TTToHadronic_SF[SF_index]);
  h_MSJ_mass_vs_MdSJ_antiTag_1b_TTToLeptonicMC->Scale(h_TTTo2l2nu_SF[SF_index]);
  h_MSJ_mass_vs_MdSJ_antiTag_1b_TTToSemiLeptonicMC->Scale(h_TTToSemiLeptonic_SF[SF_index]);
  h_MSJ_mass_vs_MdSJ_antiTag_1b_ST_s_channel_hadronsMC->Scale(ST_s_channel_4f_hadrons_SF[SF_index]);
  h_MSJ_mass_vs_MdSJ_antiTag_1b_ST_s_channel_leptonsMC->Scale(ST_s_channel_4f_leptons_SF[SF_index]);
  h_MSJ_mass_vs_MdSJ_antiTag_1b_ST_t_channel_antitop->Scale(ST_t_channel_antitop_5f_SF[SF_index]);
  h_MSJ_mass_vs_MdSJ_antiTag_1b_ST_t_channel_top->Scale(ST_t_channel_top_5f_SF[SF_index]);
  h_MSJ_mass_vs_MdSJ_antiTag_1b_ST_tW_antiTop->Scale(ST_tW_antitop_5f_SF[SF_index]);
  h_MSJ_mass_vs_MdSJ_antiTag_1b_ST_tW_top->Scale(ST_tW_top_5f_SF[SF_index]);

  TH2F *h_MSJ_mass_vs_MdSJ_antiTag_1b_allBR_antiTag_1b = new TH2F(*h_MSJ_mass_vs_MdSJ_antiTag_1b_HT1000to1500);


  h_MSJ_mass_vs_MdSJ_antiTag_1b_allBR_antiTag_1b->Add(h_MSJ_mass_vs_MdSJ_antiTag_1b_HT1500to2000);
  h_MSJ_mass_vs_MdSJ_antiTag_1b_allBR_antiTag_1b->Add(h_MSJ_mass_vs_MdSJ_antiTag_1b_HT2000toInf);
  h_MSJ_mass_vs_MdSJ_antiTag_1b_allBR_antiTag_1b->Add(h_MSJ_mass_vs_MdSJ_antiTag_1b_TTToHadronicMC );
  h_MSJ_mass_vs_MdSJ_antiTag_1b_allBR_antiTag_1b->Add(h_MSJ_mass_vs_MdSJ_antiTag_1b_TTToLeptonicMC );
  h_MSJ_mass_vs_MdSJ_antiTag_1b_allBR_antiTag_1b->Add(h_MSJ_mass_vs_MdSJ_antiTag_1b_TTToSemiLeptonicMC);
  h_MSJ_mass_vs_MdSJ_antiTag_1b_allBR_antiTag_1b->Add(h_MSJ_mass_vs_MdSJ_antiTag_1b_ST_s_channel_hadronsMC );
  h_MSJ_mass_vs_MdSJ_antiTag_1b_allBR_antiTag_1b->Add(h_MSJ_mass_vs_MdSJ_antiTag_1b_ST_s_channel_leptonsMC);
  h_MSJ_mass_vs_MdSJ_antiTag_1b_allBR_antiTag_1b->Add(h_MSJ_mass_vs_MdSJ_antiTag_1b_ST_t_channel_antitop );
  h_MSJ_mass_vs_MdSJ_antiTag_1b_allBR_antiTag_1b->Add(h_MSJ_mass_vs_MdSJ_antiTag_1b_ST_t_channel_top );
  h_MSJ_mass_vs_MdSJ_antiTag_1b_allBR_antiTag_1b->Add(h_MSJ_mass_vs_MdSJ_antiTag_1b_ST_tW_antiTop );
  h_MSJ_mass_vs_MdSJ_antiTag_1b_allBR_antiTag_1b->Add(h_MSJ_mass_vs_MdSJ_antiTag_1b_ST_tW_top );

  //h_MSJ_mass_vs_MdSJ_antiTag_1b_allData_antiTag_1b->Scale(data_MC_SF_1b_antiTag);   //// SCALING Data


  gStyle->SetOptStat(0);

  // problem: these plots are wrong 


  h_MSJ_mass_vs_MdSJ_antiTag_1b_allBR_antiTag_1b->Draw("colz");
  c1->SaveAs( (plot_home + "h_MSJ_mass_vs_MdSJ_antiTag_1b_allBR_antiTag_"+ year+".png").c_str());

  h_MSJ_mass_vs_MdSJ_antiTag_1b_allData_antiTag_1b->Draw("colz");
  c1->SaveAs( (plot_home + "h_MSJ_mass_vs_MdSJ_antiTag_1b_allData_antiTag_"+ year+".png").c_str());

  TH2F * ratio_2D_hist_antitag_1b = (TH2F*) h_MSJ_mass_vs_MdSJ_antiTag_1b_allData_antiTag_1b->Clone();


  ratio_2D_hist_antitag_1b->Divide(h_MSJ_mass_vs_MdSJ_antiTag_1b_allBR_antiTag_1b);
  ratio_2D_hist_antitag_1b->SetTitle("data/MC ratio in the 1 b-jet anti-tag region (2018)");
  ratio_2D_hist_antitag_1b->SetMaximum(5.0); 

  ratio_2D_hist_antitag_1b->GetXaxis()->SetRangeUser(0., 5000.);
  ratio_2D_hist_antitag_1b->Draw("colz");
  c1->SaveAs( (plot_home + "h_MSJ_mass_vs_MdSJ_antiTag_1b_antitag_DataMC_ratio_"+ year+".png").c_str());




  /// get signal hists an scale them
  TFile *f17 = new TFile("/Users/ethan/Documents/rootFiles/processedRootFiles/Suu8_chi3_2018_nom_processed.root");   
  TH2F *h_MSJ_mass_vs_MdSJ_SR_antiTag_1b_Sig_MSuu8TeV_MChi3TeV = (TH2F*)f17->Get("nom_/h_MSJ_mass_vs_MdSJ_SR");
  h_MSJ_mass_vs_MdSJ_SR_antiTag_1b_Sig_MSuu8TeV_MChi3TeV->Scale(SuuToChiChi_MSuu8TeV_Mchi3TeV_SF);




  TH2F * ratio_2D_BR_sig_antitag_1b = (TH2F*) h_MSJ_mass_vs_MdSJ_antiTag_1b_allBR_antiTag_1b->Clone();
  ratio_2D_BR_sig_antitag_1b->Add(h_MSJ_mass_vs_MdSJ_SR_antiTag_1b_Sig_MSuu8TeV_MChi3TeV );

  
  ratio_2D_BR_sig_antitag_1b->Divide(h_MSJ_mass_vs_MdSJ_antiTag_1b_allBR_antiTag_1b);
  ratio_2D_BR_sig_antitag_1b->SetTitle("data/MC ratio in the 1 b-jet anti-tag region (2018)");
  ratio_2D_BR_sig_antitag_1b->SetMaximum(5.0); 
  ratio_2D_BR_sig_antitag_1b->Draw("colz");
  c1->SaveAs( (plot_home + "h_MSJ_mass_vs_MdSJ_antiTag_1b_antitag_allBR_sig_ratio_"+ year+".png").c_str());










 ///////////////////// SIGNAL REGION COMPARISONS //////////////////




  TH2F *h_MSJ_mass_vs_MdSJ_SR_HT1000to1500 = (TH2F*)f1->Get("nom_/h_MSJ_mass_vs_MdSJ_SR");
  TH2F *h_MSJ_mass_vs_MdSJ_SR_HT1500to2000 = (TH2F*)f2->Get("nom_/h_MSJ_mass_vs_MdSJ_SR");
  TH2F *h_MSJ_mass_vs_MdSJ_SR_HT2000toInf = (TH2F*)f3->Get("nom_/h_MSJ_mass_vs_MdSJ_SR");

  TH2F *h_MSJ_mass_vs_MdSJ_SR_TTToHadronicMC = (TH2F*)f4->Get("nom_/h_MSJ_mass_vs_MdSJ_SR");
  TH2F *h_MSJ_mass_vs_MdSJ_SR_TTToLeptonicMC = (TH2F*)f5->Get("nom_/h_MSJ_mass_vs_MdSJ_SR");
  TH2F *h_MSJ_mass_vs_MdSJ_SR_TTToSemiLeptonicMC = (TH2F*)f6->Get("nom_/h_MSJ_mass_vs_MdSJ_SR");

  TH2F *h_MSJ_mass_vs_MdSJ_SR_ST_s_channel_hadronsMC = (TH2F*)f7->Get("nom_/h_MSJ_mass_vs_MdSJ_SR");
  TH2F *h_MSJ_mass_vs_MdSJ_SR_ST_s_channel_leptonsMC = (TH2F*)f8->Get("nom_/h_MSJ_mass_vs_MdSJ_SR");
  TH2F *h_MSJ_mass_vs_MdSJ_SR_ST_t_channel_antitop = (TH2F*)f9->Get("nom_/h_MSJ_mass_vs_MdSJ_SR");
  TH2F *h_MSJ_mass_vs_MdSJ_SR_ST_t_channel_top = (TH2F*)f10->Get("nom_/h_MSJ_mass_vs_MdSJ_SR");
  TH2F *h_MSJ_mass_vs_MdSJ_SR_ST_tW_antiTop = (TH2F*)f11->Get("nom_/h_MSJ_mass_vs_MdSJ_SR");
  TH2F *h_MSJ_mass_vs_MdSJ_SR_ST_tW_top = (TH2F*)f12->Get("nom_/h_MSJ_mass_vs_MdSJ_SR");

  std::vector<TH1F*>  h_SJ_mass_CR_data_hists_SR  = get_histograms<TH1F*>(dataFiles, "h_SJ_mass_SR");
  TH1F*  h_SJ_mass_SR_allData  = combine_histograms<TH1F*>(h_SJ_mass_CR_data_hists_SR);

  std::vector<TH1F*>  h_diSuperjet_mass_CR_data_SR  = get_histograms<TH1F*>(dataFiles, "h_disuperjet_mass_SR");
  TH1F*  h_diSuperjet_mass_allData_SR  = combine_histograms<TH1F*>(h_diSuperjet_mass_CR_data_SR);

  std::vector<TH2F*> h_MSJ_vs_MdiSJ_SR_data_hists_R = get_histograms<TH2F*>(dataFiles, "h_MSJ_mass_vs_MdSJ_SR");
  TH2F * h_MSJ_mass_vs_MdSJ_SR_allData = combine_histograms<TH2F*>(h_MSJ_vs_MdiSJ_SR_data_hists_R);



  h_MSJ_mass_vs_MdSJ_SR_HT1000to1500->Scale(QCD1000to1500_SF[SF_index]);
  h_MSJ_mass_vs_MdSJ_SR_HT1500to2000->Scale(QCD1500to2000_SF[SF_index]);
  h_MSJ_mass_vs_MdSJ_SR_HT2000toInf->Scale(QCD2000toInf_SF[SF_index]);
  h_MSJ_mass_vs_MdSJ_SR_TTToHadronicMC->Scale(h_TTToHadronic_SF[SF_index]);
  h_MSJ_mass_vs_MdSJ_SR_TTToLeptonicMC->Scale(h_TTTo2l2nu_SF[SF_index]);
  h_MSJ_mass_vs_MdSJ_SR_TTToSemiLeptonicMC->Scale(h_TTToSemiLeptonic_SF[SF_index]);
  h_MSJ_mass_vs_MdSJ_SR_ST_s_channel_hadronsMC->Scale(ST_s_channel_4f_hadrons_SF[SF_index]);
  h_MSJ_mass_vs_MdSJ_SR_ST_s_channel_leptonsMC->Scale(ST_s_channel_4f_leptons_SF[SF_index]);
  h_MSJ_mass_vs_MdSJ_SR_ST_t_channel_antitop->Scale(ST_t_channel_antitop_5f_SF[SF_index]);
  h_MSJ_mass_vs_MdSJ_SR_ST_t_channel_top->Scale(ST_t_channel_top_5f_SF[SF_index]);
  h_MSJ_mass_vs_MdSJ_SR_ST_tW_antiTop->Scale(ST_tW_antitop_5f_SF[SF_index]);
  h_MSJ_mass_vs_MdSJ_SR_ST_tW_top->Scale(ST_tW_top_5f_SF[SF_index]);



  TH2F *h_MSJ_mass_vs_MdSJ_SR_allBR = new TH2F(*h_MSJ_mass_vs_MdSJ_SR_HT1000to1500);
  h_MSJ_mass_vs_MdSJ_SR_allBR->Add(h_MSJ_mass_vs_MdSJ_SR_HT1500to2000);
  h_MSJ_mass_vs_MdSJ_SR_allBR->Add(h_MSJ_mass_vs_MdSJ_SR_HT2000toInf);
  h_MSJ_mass_vs_MdSJ_SR_allBR->Add(h_MSJ_mass_vs_MdSJ_SR_TTToHadronicMC);
  h_MSJ_mass_vs_MdSJ_SR_allBR->Add(h_MSJ_mass_vs_MdSJ_SR_TTToLeptonicMC);
  h_MSJ_mass_vs_MdSJ_SR_allBR->Add(h_MSJ_mass_vs_MdSJ_SR_TTToSemiLeptonicMC);
  h_MSJ_mass_vs_MdSJ_SR_allBR->Add(h_MSJ_mass_vs_MdSJ_SR_ST_s_channel_hadronsMC);
  h_MSJ_mass_vs_MdSJ_SR_allBR->Add(h_MSJ_mass_vs_MdSJ_SR_ST_s_channel_leptonsMC);
  h_MSJ_mass_vs_MdSJ_SR_allBR->Add(h_MSJ_mass_vs_MdSJ_SR_ST_t_channel_antitop);
  h_MSJ_mass_vs_MdSJ_SR_allBR->Add(h_MSJ_mass_vs_MdSJ_SR_ST_t_channel_top);
  h_MSJ_mass_vs_MdSJ_SR_allBR->Add(h_MSJ_mass_vs_MdSJ_SR_ST_tW_antiTop);
  h_MSJ_mass_vs_MdSJ_SR_allBR->Add(h_MSJ_mass_vs_MdSJ_SR_ST_tW_top);


  //h_MSJ_mass_vs_MdSJ_SR_allData->Scale(data_MC_SF_1b_antiTag);    //// SCALING Data

  h_MSJ_mass_vs_MdSJ_SR_allBR->Draw("colz");
  c1->SaveAs( (plot_home + "h_MSJ_mass_vs_MdSJ_SR_allBR_"+ year+".png").c_str()); 

  h_MSJ_mass_vs_MdSJ_SR_allData->Draw("colz");
  c1->SaveAs( (plot_home + "h_MSJ_mass_vs_MdSJ_SR_allData_"+ year+".png").c_str()); 


  //gPad->SetLogz();

  std::cout << "The integrals of each are data/MC: " << h_MSJ_mass_vs_MdSJ_SR_allData->Integral() << "/" << h_MSJ_mass_vs_MdSJ_SR_allBR->Integral() << std::endl;
  h_MSJ_mass_vs_MdSJ_SR_allData->Divide(h_MSJ_mass_vs_MdSJ_SR_allBR);

  h_MSJ_mass_vs_MdSJ_SR_allData->SetMinimum(0.5);
  h_MSJ_mass_vs_MdSJ_SR_allData->SetMaximum(2.5); 
  h_MSJ_mass_vs_MdSJ_SR_allData->SetTitle("M_{SJ} vs M_{diSJ} Ratio (double-tagged data in SR / double-tagged MC BR in data SR); M_{diSJ};M_{SJ}");
  h_MSJ_mass_vs_MdSJ_SR_allData->GetYaxis()->SetTitleOffset(1.35);
  h_MSJ_mass_vs_MdSJ_SR_allData->GetYaxis()->SetLabelSize(0.015);
  h_MSJ_mass_vs_MdSJ_SR_allData->Draw("colz");
  c1->SaveAs( (plot_home + "h_MSJ_mass_vs_MdSJ_Data_ratio_SR_"+ year+".png").c_str()); 

  ////////////////////////////////////////////


  TH1F *h_SJ_mass_SR_HT1000to1500 = (TH1F*)f1->Get("nom_/h_SJ_mass_SR");
  TH1F *h_SJ_mass_SR_HT1500to2000 = (TH1F*)f2->Get("nom_/h_SJ_mass_SR");
  TH1F *h_SJ_mass_SR_HT2000toInf = (TH1F*)f3->Get("nom_/h_SJ_mass_SR");

  TH1F *h_SJ_mass_SR_TTToHadronicMC = (TH1F*)f4->Get("nom_/h_SJ_mass_SR");
  TH1F *h_SJ_mass_SR_TTToLeptonicMC = (TH1F*)f5->Get("nom_/h_SJ_mass_SR");
  TH1F *h_SJ_mass_SR_TTToSemiLeptonicMC = (TH1F*)f6->Get("nom_/h_SJ_mass_SR");

  TH1F *h_SJ_mass_SR_ST_s_channel_hadronsMC = (TH1F*)f7->Get("nom_/h_SJ_mass_SR");
  TH1F *h_SJ_mass_SR_ST_s_channel_leptonsMC = (TH1F*)f8->Get("nom_/h_SJ_mass_SR");
  TH1F *h_SJ_mass_SR_ST_t_channel_antitop = (TH1F*)f9->Get("nom_/h_SJ_mass_SR");
  TH1F *h_SJ_mass_SR_ST_t_channel_top = (TH1F*)f10->Get("nom_/h_SJ_mass_SR");
  TH1F *h_SJ_mass_SR_ST_tW_antiTop = (TH1F*)f11->Get("nom_/h_SJ_mass_SR");
  TH1F *h_SJ_mass_SR_ST_tW_top = (TH1F*)f12->Get("nom_/h_SJ_mass_SR");


  h_SJ_mass_SR_HT1000to1500->Scale(QCD1000to1500_SF[SF_index]);
  h_SJ_mass_SR_HT1500to2000->Scale(QCD1500to2000_SF[SF_index]);
  h_SJ_mass_SR_HT2000toInf->Scale(QCD2000toInf_SF[SF_index]);
  h_SJ_mass_SR_TTToHadronicMC->Scale(h_TTToHadronic_SF[SF_index]);
  h_SJ_mass_SR_TTToLeptonicMC->Scale(h_TTTo2l2nu_SF[SF_index]);
  h_SJ_mass_SR_TTToSemiLeptonicMC->Scale(h_TTToSemiLeptonic_SF[SF_index]);
  h_SJ_mass_SR_ST_s_channel_hadronsMC->Scale(ST_s_channel_4f_hadrons_SF[SF_index]);
  h_SJ_mass_SR_ST_s_channel_leptonsMC->Scale(ST_s_channel_4f_leptons_SF[SF_index]);
  h_SJ_mass_SR_ST_t_channel_antitop->Scale(ST_t_channel_antitop_5f_SF[SF_index]);
  h_SJ_mass_SR_ST_t_channel_top->Scale(ST_t_channel_top_5f_SF[SF_index]);
  h_SJ_mass_SR_ST_tW_antiTop->Scale(ST_tW_antitop_5f_SF[SF_index]);
  h_SJ_mass_SR_ST_tW_top->Scale(ST_tW_top_5f_SF[SF_index]);


  TH1F *h_SJ_mass_SR_allBR = new TH1F(*h_SJ_mass_SR_HT1000to1500);





  h_SJ_mass_SR_allBR->Add(h_SJ_mass_SR_HT1500to2000);
  h_SJ_mass_SR_allBR->Add(h_SJ_mass_SR_HT2000toInf);
  h_SJ_mass_SR_allBR->Add(h_SJ_mass_SR_TTToHadronicMC);
  h_SJ_mass_SR_allBR->Add(h_SJ_mass_SR_TTToLeptonicMC);
  h_SJ_mass_SR_allBR->Add(h_SJ_mass_SR_TTToSemiLeptonicMC);
  h_SJ_mass_SR_allBR->Add(h_SJ_mass_SR_ST_s_channel_hadronsMC);
  h_SJ_mass_SR_allBR->Add(h_SJ_mass_SR_ST_s_channel_leptonsMC);
  h_SJ_mass_SR_allBR->Add(h_SJ_mass_SR_ST_t_channel_antitop);
  h_SJ_mass_SR_allBR->Add(h_SJ_mass_SR_ST_t_channel_top);
  h_SJ_mass_SR_allBR->Add(h_SJ_mass_SR_ST_tW_antiTop);
  h_SJ_mass_SR_allBR->Add(h_SJ_mass_SR_ST_tW_top);

  //h_SJ_mass_SR_allData->Scale(data_MC_SF_1b_antiTag);    //// SCALING Data


  h_SJ_mass_SR_allData->SetTitle("SJ Mass Shape Ratio of SR data to SR MC ");
  auto rp_SJ_mass_SR = new TRatioPlot(h_SJ_mass_SR_allData,h_SJ_mass_SR_allBR);
  //h_BR_combined->Draw("HIST");
  rp_SJ_mass_SR->Draw("HIST,EP");
  rp_SJ_mass_SR->GetLowerRefYaxis()->SetTitle("data/MC ratio");
  rp_SJ_mass_SR->GetLowerRefGraph()->SetMaximum(2.);
  rp_SJ_mass_SR->GetUpperRefYaxis()->SetTitle("Events");
  c1->SaveAs( (plot_home + "h_SJ_mass_DataMC_ratio_SR_"+ year+".png").c_str()); 



  // what does the difference between the SR data and MC look like?
  
  TH1F *h_SJ_mass_SR_dataMC_diff = new TH1F(*h_SJ_mass_SR_allData);
  h_SJ_mass_SR_dataMC_diff->SetTitle("Difference in superjet mass between SR data and MC");

  h_SJ_mass_SR_dataMC_diff->Add(h_SJ_mass_SR_allBR,-1);
  h_SJ_mass_SR_dataMC_diff->Draw("HIST");
  c1->SaveAs( (plot_home + "h_SJ_mass_SR_dataMC_diff_"+ year+".png").c_str());


  //rp_SJ_mass->SetTitle("SJ mass ratio (double-tagged BR in SR / double-tagged BR in data SR); SJ mass [GeV]");
  //rp_SJ_mass->GetYaxis()->SetTitleOffset(1.35);
  //rp_SJ_mass->GetYaxis()->SetLabelSize(0.015);


  TH2F *h_MSJ_mass_vs_MdSJ_SR_allQCD = new TH2F(*h_MSJ_mass_vs_MdSJ_SR_HT1000to1500);
  h_MSJ_mass_vs_MdSJ_SR_allQCD->Add(h_MSJ_mass_vs_MdSJ_SR_HT1500to2000);
  h_MSJ_mass_vs_MdSJ_SR_allQCD->Add(h_MSJ_mass_vs_MdSJ_SR_HT2000toInf);
  h_MSJ_mass_vs_MdSJ_SR_allQCD->Draw("LEGO2");
  c1->SaveAs( (plot_home + "h_MSJ_mass_vs_MdSJ_SR_allQCD_"+ year+".png").c_str());


  ///// disuperjet mass ratio 
  TH1F *h_disuperjet_mass_SR_HT1000to1500 = (TH1F*)f1->Get("nom_/h_disuperjet_mass_SR");
  TH1F *h_disuperjet_mass_SR_HT1500to2000 = (TH1F*)f2->Get("nom_/h_disuperjet_mass_SR");
  TH1F *h_disuperjet_mass_SR_HT2000toInf = (TH1F*)f3->Get("nom_/h_disuperjet_mass_SR");

  TH1F *h_disuperjet_mass_SR_TTToHadronicMC = (TH1F*)f4->Get("nom_/h_disuperjet_mass_SR");
  TH1F *h_disuperjet_mass_SR_TTToLeptonicMC = (TH1F*)f5->Get("nom_/h_disuperjet_mass_SR");
  TH1F *h_disuperjet_mass_SR_TTToSemiLeptonicMC = (TH1F*)f6->Get("nom_/h_disuperjet_mass_SR");

  TH1F *h_disuperjet_mass_SR_ST_s_channel_hadronsMC = (TH1F*)f7->Get("nom_/h_disuperjet_mass_SR");
  TH1F *h_disuperjet_mass_SR_ST_s_channel_leptonsMC = (TH1F*)f8->Get("nom_/h_disuperjet_mass_SR");
  TH1F *h_disuperjet_mass_SR_ST_t_channel_antitop = (TH1F*)f9->Get("nom_/h_disuperjet_mass_SR");
  TH1F *h_disuperjet_mass_SR_ST_t_channel_top = (TH1F*)f10->Get("nom_/h_disuperjet_mass_SR");
  TH1F *h_disuperjet_mass_SR_ST_tW_antiTop = (TH1F*)f11->Get("nom_/h_disuperjet_mass_SR");
  TH1F *h_disuperjet_mass_SR_ST_tW_top = (TH1F*)f12->Get("nom_/h_disuperjet_mass_SR");

  h_disuperjet_mass_SR_HT1000to1500->Scale(QCD1000to1500_SF[SF_index]);
  h_disuperjet_mass_SR_HT1500to2000->Scale(QCD1500to2000_SF[SF_index]);
  h_disuperjet_mass_SR_HT2000toInf->Scale(QCD2000toInf_SF[SF_index]);
  h_disuperjet_mass_SR_TTToHadronicMC->Scale(h_TTToHadronic_SF[SF_index]);
  h_disuperjet_mass_SR_TTToLeptonicMC->Scale(h_TTTo2l2nu_SF[SF_index]);
  h_disuperjet_mass_SR_TTToSemiLeptonicMC->Scale(h_TTToSemiLeptonic_SF[SF_index]);
  h_disuperjet_mass_SR_ST_s_channel_hadronsMC->Scale(ST_s_channel_4f_hadrons_SF[SF_index]);
  h_disuperjet_mass_SR_ST_s_channel_leptonsMC->Scale(ST_s_channel_4f_leptons_SF[SF_index]);
  h_disuperjet_mass_SR_ST_t_channel_antitop->Scale(ST_t_channel_antitop_5f_SF[SF_index]);
  h_disuperjet_mass_SR_ST_t_channel_top->Scale(ST_t_channel_top_5f_SF[SF_index]);
  h_disuperjet_mass_SR_ST_tW_antiTop->Scale(ST_tW_antitop_5f_SF[SF_index]);
  h_disuperjet_mass_SR_ST_tW_top->Scale(ST_tW_top_5f_SF[SF_index]);

  TH1F *h_diSuperjet_mass_allBR_SR = new TH1F(*h_disuperjet_mass_SR_HT1000to1500);

  h_diSuperjet_mass_allBR_SR->Add(h_disuperjet_mass_SR_HT1500to2000);
  h_diSuperjet_mass_allBR_SR->Add(h_disuperjet_mass_SR_HT2000toInf);
  h_diSuperjet_mass_allBR_SR->Add(h_disuperjet_mass_SR_TTToHadronicMC);
  h_diSuperjet_mass_allBR_SR->Add(h_disuperjet_mass_SR_TTToLeptonicMC);
  h_diSuperjet_mass_allBR_SR->Add(h_disuperjet_mass_SR_TTToSemiLeptonicMC);
  h_diSuperjet_mass_allBR_SR->Add(h_disuperjet_mass_SR_ST_s_channel_hadronsMC);
  h_diSuperjet_mass_allBR_SR->Add(h_disuperjet_mass_SR_ST_s_channel_leptonsMC);
  h_diSuperjet_mass_allBR_SR->Add(h_disuperjet_mass_SR_ST_t_channel_antitop);
  h_diSuperjet_mass_allBR_SR->Add(h_disuperjet_mass_SR_ST_t_channel_top);
  h_diSuperjet_mass_allBR_SR->Add(h_disuperjet_mass_SR_ST_tW_antiTop);
  h_diSuperjet_mass_allBR_SR->Add(h_disuperjet_mass_SR_ST_tW_top);

  h_diSuperjet_mass_allBR_SR->GetXaxis()->SetRangeUser(0., 5000.);


  //h_diSuperjet_mass_allData_SR->Scale(data_MC_SF_1b_antiTag);   //// SCALING Data


  h_diSuperjet_mass_allData_SR->GetXaxis()->SetRangeUser(0., 5000.);


  h_diSuperjet_mass_allData_SR->SetTitle("diSuperjet Mass Shape Ratio of SR data to SR MC ");
  auto rp_diSuperjet_mass_SR = new TRatioPlot(h_diSuperjet_mass_allData_SR,h_diSuperjet_mass_allBR_SR);
  //h_BR_combined->Draw("HIST");
  rp_diSuperjet_mass_SR->Draw("HIST,EP");
  rp_diSuperjet_mass_SR->GetLowerRefYaxis()->SetTitle("data/MC ratio");
  rp_diSuperjet_mass_SR->GetLowerRefGraph()->SetMaximum(2.);
  rp_diSuperjet_mass_SR->GetUpperRefYaxis()->SetTitle("Events");
  c1->SaveAs( (plot_home + "h_diSuperjet_mass_SR_DataMC_ratio_"+ year+".png").c_str()); 



  // what does the difference between the SR data and MC look like?
  
  TH1F *h_diSuperjet_mass_SR_dataMC_diff = new TH1F(*h_diSuperjet_mass_allData_SR);
  h_diSuperjet_mass_SR_dataMC_diff->SetTitle("Difference in disuperjet mass between SR data and MC");
  h_diSuperjet_mass_SR_dataMC_diff->Add(h_diSuperjet_mass_allBR_SR,-1);
  h_diSuperjet_mass_SR_dataMC_diff->Draw("HIST");
  c1->SaveAs( (plot_home + "h_diSuperjet_mass_SR_dataMC_diff_"+ year+".png").c_str());













  ///////////////// CONTROL REGION COMPARISONS //////////////////////////
  TH2F *h_MSJ_mass_vs_MdSJ_CR_HT1000to1500 = (TH2F*)f1->Get("nom_/h_MSJ_mass_vs_MdSJ_CR");
  TH2F *h_MSJ_mass_vs_MdSJ_CR_HT1500to2000 = (TH2F*)f2->Get("nom_/h_MSJ_mass_vs_MdSJ_CR");
  TH2F *h_MSJ_mass_vs_MdSJ_CR_HT2000toInf = (TH2F*)f3->Get("nom_/h_MSJ_mass_vs_MdSJ_CR");

  TH2F *h_MSJ_mass_vs_MdSJ_CR_TTToHadronicMC = (TH2F*)f4->Get("nom_/h_MSJ_mass_vs_MdSJ_CR");
  TH2F *h_MSJ_mass_vs_MdSJ_CR_TTToLeptonicMC = (TH2F*)f5->Get("nom_/h_MSJ_mass_vs_MdSJ_CR");
  TH2F *h_MSJ_mass_vs_MdSJ_CR_TTToSemiLeptonicMC = (TH2F*)f6->Get("nom_/h_MSJ_mass_vs_MdSJ_CR");

  TH2F *h_MSJ_mass_vs_MdSJ_CR_ST_s_channel_hadronsMC = (TH2F*)f7->Get("nom_/h_MSJ_mass_vs_MdSJ_CR");
  TH2F *h_MSJ_mass_vs_MdSJ_CR_ST_s_channel_leptonsMC = (TH2F*)f8->Get("nom_/h_MSJ_mass_vs_MdSJ_CR");
  TH2F *h_MSJ_mass_vs_MdSJ_CR_ST_t_channel_antitop = (TH2F*)f9->Get("nom_/h_MSJ_mass_vs_MdSJ_CR");
  TH2F *h_MSJ_mass_vs_MdSJ_CR_ST_t_channel_top = (TH2F*)f10->Get("nom_/h_MSJ_mass_vs_MdSJ_CR");
  TH2F *h_MSJ_mass_vs_MdSJ_CR_ST_tW_antiTop = (TH2F*)f11->Get("nom_/h_MSJ_mass_vs_MdSJ_CR");
  TH2F *h_MSJ_mass_vs_MdSJ_CR_ST_tW_top = (TH2F*)f12->Get("nom_/h_MSJ_mass_vs_MdSJ_CR");


  std::vector<TH1F*>  h_SJ_mass_CR_data_hists_CR  = get_histograms<TH1F*>(dataFiles, "h_SJ_mass_CR");
  TH1F*  h_SJ_mass_CR_allData  = combine_histograms<TH1F*>(h_SJ_mass_CR_data_hists_CR);

  std::vector<TH1F*>  h_diSuperjet_mass_CR_data_CR  = get_histograms<TH1F*>(dataFiles, "h_disuperjet_mass_CR");
  TH1F*  h_diSuperjet_mass_allData_CR  = combine_histograms<TH1F*>(h_diSuperjet_mass_CR_data_CR);

  std::vector<TH2F*> h_MSJ_vs_MdiSJ_CR_data_hists_CR = get_histograms<TH2F*>(dataFiles, "h_MSJ_mass_vs_MdSJ_CR");
  TH2F * h_MSJ_mass_vs_MdSJ_CR_allData = combine_histograms<TH2F*>(h_MSJ_vs_MdiSJ_CR_data_hists_CR);


  h_MSJ_mass_vs_MdSJ_CR_HT1000to1500->Scale(QCD1000to1500_SF[SF_index]);
  h_MSJ_mass_vs_MdSJ_CR_HT1500to2000->Scale(QCD1500to2000_SF[SF_index]);
  h_MSJ_mass_vs_MdSJ_CR_ST_s_channel_leptonsMC->Scale(ST_s_channel_4f_leptons_SF[SF_index]);
  h_MSJ_mass_vs_MdSJ_CR_HT2000toInf->Scale(QCD2000toInf_SF[SF_index]);
  h_MSJ_mass_vs_MdSJ_CR_TTToHadronicMC->Scale(h_TTToHadronic_SF[SF_index]);
  h_MSJ_mass_vs_MdSJ_CR_TTToLeptonicMC->Scale(h_TTTo2l2nu_SF[SF_index]);
  h_MSJ_mass_vs_MdSJ_CR_TTToSemiLeptonicMC->Scale(h_TTToSemiLeptonic_SF[SF_index]);
  h_MSJ_mass_vs_MdSJ_CR_ST_s_channel_hadronsMC->Scale(ST_s_channel_4f_hadrons_SF[SF_index]);
  h_MSJ_mass_vs_MdSJ_CR_ST_t_channel_antitop->Scale(ST_t_channel_antitop_5f_SF[SF_index]);
  h_MSJ_mass_vs_MdSJ_CR_ST_t_channel_top->Scale(ST_t_channel_top_5f_SF[SF_index]);
  h_MSJ_mass_vs_MdSJ_CR_ST_tW_antiTop->Scale(ST_tW_antitop_5f_SF[SF_index]);
  h_MSJ_mass_vs_MdSJ_CR_ST_tW_top->Scale(ST_tW_top_5f_SF[SF_index]);


  TH2F *h_MSJ_mass_vs_MdSJ_CR_allBR = new TH2F(*h_MSJ_mass_vs_MdSJ_CR_HT1000to1500);
  h_MSJ_mass_vs_MdSJ_CR_allBR->Add(h_MSJ_mass_vs_MdSJ_CR_HT1500to2000);
  h_MSJ_mass_vs_MdSJ_CR_allBR->Add(h_MSJ_mass_vs_MdSJ_CR_HT2000toInf);
  h_MSJ_mass_vs_MdSJ_CR_allBR->Add(h_MSJ_mass_vs_MdSJ_CR_TTToHadronicMC);
  h_MSJ_mass_vs_MdSJ_CR_allBR->Add(h_MSJ_mass_vs_MdSJ_CR_TTToLeptonicMC);
  h_MSJ_mass_vs_MdSJ_CR_allBR->Add(h_MSJ_mass_vs_MdSJ_CR_TTToSemiLeptonicMC);
  h_MSJ_mass_vs_MdSJ_CR_allBR->Add(h_MSJ_mass_vs_MdSJ_CR_ST_s_channel_hadronsMC);
  h_MSJ_mass_vs_MdSJ_CR_allBR->Add(h_MSJ_mass_vs_MdSJ_CR_ST_s_channel_leptonsMC);
  h_MSJ_mass_vs_MdSJ_CR_allBR->Add(h_MSJ_mass_vs_MdSJ_CR_ST_t_channel_antitop);
  h_MSJ_mass_vs_MdSJ_CR_allBR->Add(h_MSJ_mass_vs_MdSJ_CR_ST_t_channel_top);
  h_MSJ_mass_vs_MdSJ_CR_allBR->Add(h_MSJ_mass_vs_MdSJ_CR_ST_tW_antiTop);
  h_MSJ_mass_vs_MdSJ_CR_allBR->Add(h_MSJ_mass_vs_MdSJ_CR_ST_tW_top);


  h_MSJ_mass_vs_MdSJ_CR_allBR->Draw("colz");
  c1->SaveAs( (plot_home + "h_MSJ_mass_vs_MdSJ_CR_allBR_"+ year+".png").c_str()); 

  h_MSJ_mass_vs_MdSJ_CR_allData->Draw("colz");
  c1->SaveAs( (plot_home + "h_MSJ_mass_vs_MdSJ_CR_allData_"+ year+".png").c_str()); 


  //gPad->SetLogz();

  std::cout << "The integrals of each are data/MC: " << h_MSJ_mass_vs_MdSJ_CR_allData->Integral() << "/" << h_MSJ_mass_vs_MdSJ_CR_allBR->Integral() << std::endl;
  h_MSJ_mass_vs_MdSJ_CR_allData->Divide(h_MSJ_mass_vs_MdSJ_CR_allBR);

  h_MSJ_mass_vs_MdSJ_CR_allData->SetMinimum(0.5);
  h_MSJ_mass_vs_MdSJ_CR_allData->SetMaximum(2.5); 
  h_MSJ_mass_vs_MdSJ_CR_allData->SetTitle("M_{SJ} vs M_{diSJ} Ratio (double-tagged data in CR / double-tagged MC BR in CR); M_{diSJ};M_{SJ}");
  h_MSJ_mass_vs_MdSJ_CR_allData->GetYaxis()->SetTitleOffset(1.35);
  h_MSJ_mass_vs_MdSJ_CR_allData->GetYaxis()->SetLabelSize(0.015);
  h_MSJ_mass_vs_MdSJ_CR_allData->Draw("colz");
  c1->SaveAs( (plot_home + "h_MSJ_mass_vs_MdSJ_Data_ratio_CR_"+ year+".png").c_str()); 

  ////////////////////////////////////////////


  TH1F *h_SJ_mass_CR_HT1000to1500 = (TH1F*)f1->Get("nom_/h_SJ_mass_CR");
  TH1F *h_SJ_mass_CR_HT1500to2000 = (TH1F*)f2->Get("nom_/h_SJ_mass_CR");
  TH1F *h_SJ_mass_CR_HT2000toInf = (TH1F*)f3->Get("nom_/h_SJ_mass_CR");

  TH1F *h_SJ_mass_CR_TTToHadronicMC = (TH1F*)f4->Get("nom_/h_SJ_mass_CR");
  TH1F *h_SJ_mass_CR_TTToLeptonicMC = (TH1F*)f5->Get("nom_/h_SJ_mass_CR");
  TH1F *h_SJ_mass_CR_TTToSemiLeptonicMC = (TH1F*)f6->Get("nom_/h_SJ_mass_CR");

  TH1F *h_SJ_mass_CR_ST_s_channel_hadronsMC = (TH1F*)f7->Get("nom_/h_SJ_mass_CR");
  TH1F *h_SJ_mass_CR_ST_s_channel_leptonsMC = (TH1F*)f8->Get("nom_/h_SJ_mass_CR");
  TH1F *h_SJ_mass_CR_ST_t_channel_antitop = (TH1F*)f9->Get("nom_/h_SJ_mass_CR");
  TH1F *h_SJ_mass_CR_ST_t_channel_top = (TH1F*)f10->Get("nom_/h_SJ_mass_CR");
  TH1F *h_SJ_mass_CR_ST_tW_antiTop = (TH1F*)f11->Get("nom_/h_SJ_mass_CR");
  TH1F *h_SJ_mass_CR_ST_tW_top = (TH1F*)f12->Get("nom_/h_SJ_mass_CR");


  h_SJ_mass_CR_HT1000to1500->Scale(QCD1000to1500_SF[SF_index]);
  h_SJ_mass_CR_HT1500to2000->Scale(QCD1500to2000_SF[SF_index]);
  h_SJ_mass_CR_HT2000toInf->Scale(QCD2000toInf_SF[SF_index]);
  h_SJ_mass_CR_TTToHadronicMC->Scale(h_TTToHadronic_SF[SF_index]);
  h_SJ_mass_CR_TTToLeptonicMC->Scale(h_TTTo2l2nu_SF[SF_index]);
  h_SJ_mass_CR_TTToSemiLeptonicMC->Scale(h_TTToSemiLeptonic_SF[SF_index]);
  h_SJ_mass_CR_ST_s_channel_hadronsMC->Scale(ST_s_channel_4f_hadrons_SF[SF_index]);
  h_SJ_mass_CR_ST_s_channel_leptonsMC->Scale(ST_s_channel_4f_leptons_SF[SF_index]);
  h_SJ_mass_CR_ST_t_channel_antitop->Scale(ST_t_channel_antitop_5f_SF[SF_index]);
  h_SJ_mass_CR_ST_t_channel_top->Scale(ST_t_channel_top_5f_SF[SF_index]);
  h_SJ_mass_CR_ST_tW_antiTop->Scale(ST_tW_antitop_5f_SF[SF_index]);
  h_SJ_mass_CR_ST_tW_top->Scale(ST_tW_top_5f_SF[SF_index]);


  TH1F *h_SJ_mass_CR_allBR = new TH1F(*h_SJ_mass_CR_HT1000to1500);





  h_SJ_mass_CR_allBR->Add(h_SJ_mass_CR_HT1500to2000);
  h_SJ_mass_CR_allBR->Add(h_SJ_mass_CR_HT2000toInf);
  h_SJ_mass_CR_allBR->Add(h_SJ_mass_CR_TTToHadronicMC);
  h_SJ_mass_CR_allBR->Add(h_SJ_mass_CR_TTToLeptonicMC);
  h_SJ_mass_CR_allBR->Add(h_SJ_mass_CR_TTToSemiLeptonicMC);
  h_SJ_mass_CR_allBR->Add(h_SJ_mass_CR_ST_s_channel_hadronsMC);
  h_SJ_mass_CR_allBR->Add(h_SJ_mass_CR_ST_s_channel_leptonsMC);
  h_SJ_mass_CR_allBR->Add(h_SJ_mass_CR_ST_t_channel_antitop);
  h_SJ_mass_CR_allBR->Add(h_SJ_mass_CR_ST_t_channel_top);
  h_SJ_mass_CR_allBR->Add(h_SJ_mass_CR_ST_tW_antiTop);
  h_SJ_mass_CR_allBR->Add(h_SJ_mass_CR_ST_tW_top);

  h_SJ_mass_CR_allData->SetTitle("SJ Mass Shape Ratio of CR data to CR MC ");
  auto rp_SJ_mass_CR = new TRatioPlot(h_SJ_mass_CR_allData,h_SJ_mass_CR_allBR);
  //h_BR_combined->Draw("HIST");
  rp_SJ_mass_CR->Draw("HIST,EP");
  rp_SJ_mass_CR->GetLowerRefYaxis()->SetTitle("data/MC ratio");
  rp_SJ_mass_CR->GetLowerRefGraph()->SetMaximum(2.);
  rp_SJ_mass_CR->GetUpperRefYaxis()->SetTitle("Events");
  c1->SaveAs( (plot_home + "h_SJ_mass_DataMC_ratio_CR_"+ year+".png").c_str()); 





  //rp_SJ_mass->SetTitle("SJ mass ratio (double-tagged BR in CR / double-tagged BR in data CR); SJ mass [GeV]");
  //rp_SJ_mass->GetYaxis()->SetTitleOffset(1.35);
  //rp_SJ_mass->GetYaxis()->SetLabelSize(0.015);


  TH2F *h_MSJ_mass_vs_MdSJ_CR_allQCD = new TH2F(*h_MSJ_mass_vs_MdSJ_CR_HT1000to1500);
  h_MSJ_mass_vs_MdSJ_CR_allQCD->Add(h_MSJ_mass_vs_MdSJ_CR_HT1500to2000);
  h_MSJ_mass_vs_MdSJ_CR_allQCD->Add(h_MSJ_mass_vs_MdSJ_CR_HT2000toInf);
  h_MSJ_mass_vs_MdSJ_CR_allQCD->Draw("LEGO2");
  c1->SaveAs( (plot_home + "h_MSJ_mass_vs_MdSJ_CR_allQCD_"+ year+".png").c_str());


  ///// disuperjet mass ratio 
  TH1F *h_disuperjet_mass_CR_HT1000to1500 = (TH1F*)f1->Get("nom_/h_disuperjet_mass_CR");
  TH1F *h_disuperjet_mass_CR_HT1500to2000 = (TH1F*)f2->Get("nom_/h_disuperjet_mass_CR");
  TH1F *h_disuperjet_mass_CR_HT2000toInf = (TH1F*)f3->Get("nom_/h_disuperjet_mass_CR");

  TH1F *h_disuperjet_mass_CR_TTToHadronicMC = (TH1F*)f4->Get("nom_/h_disuperjet_mass_CR");
  TH1F *h_disuperjet_mass_CR_TTToLeptonicMC = (TH1F*)f5->Get("nom_/h_disuperjet_mass_CR");
  TH1F *h_disuperjet_mass_CR_TTToSemiLeptonicMC = (TH1F*)f6->Get("nom_/h_disuperjet_mass_CR");

  TH1F *h_disuperjet_mass_CR_ST_s_channel_hadronsMC = (TH1F*)f7->Get("nom_/h_disuperjet_mass_CR");
  TH1F *h_disuperjet_mass_CR_ST_s_channel_leptonsMC = (TH1F*)f8->Get("nom_/h_disuperjet_mass_CR");
  TH1F *h_disuperjet_mass_CR_ST_t_channel_antitop = (TH1F*)f9->Get("nom_/h_disuperjet_mass_CR");
  TH1F *h_disuperjet_mass_CR_ST_t_channel_top = (TH1F*)f10->Get("nom_/h_disuperjet_mass_CR");
  TH1F *h_disuperjet_mass_CR_ST_tW_antiTop = (TH1F*)f11->Get("nom_/h_disuperjet_mass_CR");
  TH1F *h_disuperjet_mass_CR_ST_tW_top = (TH1F*)f12->Get("nom_/h_disuperjet_mass_CR");

  h_disuperjet_mass_CR_HT1000to1500->Scale(QCD1000to1500_SF[SF_index]);
  h_disuperjet_mass_CR_HT1500to2000->Scale(QCD1500to2000_SF[SF_index]);
  h_disuperjet_mass_CR_HT2000toInf->Scale(QCD2000toInf_SF[SF_index]);
  h_disuperjet_mass_CR_TTToHadronicMC->Scale(h_TTToHadronic_SF[SF_index]);
  h_disuperjet_mass_CR_TTToLeptonicMC->Scale(h_TTTo2l2nu_SF[SF_index]);
  h_disuperjet_mass_CR_TTToSemiLeptonicMC->Scale(h_TTToSemiLeptonic_SF[SF_index]);
  h_disuperjet_mass_CR_ST_s_channel_hadronsMC->Scale(ST_s_channel_4f_hadrons_SF[SF_index]);
  h_disuperjet_mass_CR_ST_s_channel_leptonsMC->Scale(ST_s_channel_4f_leptons_SF[SF_index]);
  h_disuperjet_mass_CR_ST_t_channel_antitop->Scale(ST_t_channel_antitop_5f_SF[SF_index]);
  h_disuperjet_mass_CR_ST_t_channel_top->Scale(ST_t_channel_top_5f_SF[SF_index]);
  h_disuperjet_mass_CR_ST_tW_antiTop->Scale(ST_tW_antitop_5f_SF[SF_index]);
  h_disuperjet_mass_CR_ST_tW_top->Scale(ST_tW_top_5f_SF[SF_index]);

  TH1F *h_diSuperjet_mass_allBR_CR = new TH1F(*h_disuperjet_mass_CR_HT1000to1500);

  h_diSuperjet_mass_allBR_CR->Add(h_disuperjet_mass_CR_HT1500to2000);
  h_diSuperjet_mass_allBR_CR->Add(h_disuperjet_mass_CR_HT2000toInf);
  h_diSuperjet_mass_allBR_CR->Add(h_disuperjet_mass_CR_TTToHadronicMC);
  h_diSuperjet_mass_allBR_CR->Add(h_disuperjet_mass_CR_TTToLeptonicMC);
  h_diSuperjet_mass_allBR_CR->Add(h_disuperjet_mass_CR_TTToSemiLeptonicMC);
  h_diSuperjet_mass_allBR_CR->Add(h_disuperjet_mass_CR_ST_s_channel_hadronsMC);
  h_diSuperjet_mass_allBR_CR->Add(h_disuperjet_mass_CR_ST_s_channel_leptonsMC);
  h_diSuperjet_mass_allBR_CR->Add(h_disuperjet_mass_CR_ST_t_channel_antitop);
  h_diSuperjet_mass_allBR_CR->Add(h_disuperjet_mass_CR_ST_t_channel_top);
  h_diSuperjet_mass_allBR_CR->Add(h_disuperjet_mass_CR_ST_tW_antiTop);
  h_diSuperjet_mass_allBR_CR->Add(h_disuperjet_mass_CR_ST_tW_top);

  h_diSuperjet_mass_allBR_CR->GetXaxis()->SetRangeUser(0., 5000.);

  h_diSuperjet_mass_allData_CR->GetXaxis()->SetRangeUser(0., 5000.);


  h_diSuperjet_mass_allData_CR->SetTitle("diSuperjet Mass Shape Ratio of CR data to CR MC ");
  auto rp_diSuperjet_mass_CR = new TRatioPlot(h_diSuperjet_mass_allData_CR,h_diSuperjet_mass_allBR_CR);
  //h_BR_combined->Draw("HIST");
  rp_diSuperjet_mass_CR->Draw("HIST,EP");
  rp_diSuperjet_mass_CR->GetLowerRefYaxis()->SetTitle("data/MC ratio");
  rp_diSuperjet_mass_CR->GetLowerRefGraph()->SetMaximum(2.);
  rp_diSuperjet_mass_CR->GetUpperRefYaxis()->SetTitle("Events");
  c1->SaveAs( (plot_home + "h_diSuperjet_mass_CR_DataMC_ratio_"+ year+".png").c_str()); 









  // compare normalized SR data to CR data 
  TH1F *h_diSuperjet_mass_data_SR_copy = (TH1F*)h_diSuperjet_mass_allData_SR->Clone();
  TH1F *h_diSuperjet_mass_data_CR_copy = (TH1F*)h_diSuperjet_mass_allData_CR->Clone();

  TH1F *h_SJ_mass_SR_allData_copy = (TH1F*)h_SJ_mass_SR_allData->Clone();
  TH1F *h_SJ_mass_CR_allData_copy = (TH1F*)h_SJ_mass_CR_allData->Clone();

  h_diSuperjet_mass_data_SR_copy->Scale(1.0/h_diSuperjet_mass_data_SR_copy->Integral());
  h_diSuperjet_mass_data_CR_copy->Scale(1.0/h_diSuperjet_mass_data_CR_copy->Integral());

  h_SJ_mass_SR_allData_copy->Scale(1.0/h_SJ_mass_SR_allData_copy->Integral());
  h_SJ_mass_CR_allData_copy->Scale(1.0/h_SJ_mass_CR_allData_copy->Integral());

  h_diSuperjet_mass_data_SR_copy->SetTitle("diSuperjet Mass Shape Ratio of SR data to CR data ");
  auto rp_diSuperjet_mass_SRCR = new TRatioPlot(h_diSuperjet_mass_data_SR_copy,h_diSuperjet_mass_data_CR_copy);
  //h_BR_combined->Draw("HIST");
  rp_diSuperjet_mass_SRCR->Draw("HIST,EP");
  rp_diSuperjet_mass_SRCR->GetLowerRefYaxis()->SetTitle("SR/CR ratio");
  rp_diSuperjet_mass_SRCR->GetLowerRefGraph()->SetMaximum(2.);
  rp_diSuperjet_mass_SRCR->GetUpperRefYaxis()->SetTitle("Events");
  c1->SaveAs( (plot_home + "h_diSuperjet_mass_data_SRCR_ratio_"+ year+".png").c_str());   /// same as h_diSuperjet_mass_data_antiTag_ratio??


  h_SJ_mass_SR_allData_copy->SetTitle("SJ Mass Shape Ratio of SR data to CR data ");
  auto rp_SJ_mass_SRCR = new TRatioPlot(h_SJ_mass_SR_allData_copy,h_SJ_mass_CR_allData_copy);
  //h_BR_combined->Draw("HIST");
  rp_SJ_mass_SRCR->Draw("HIST,EP");
  rp_SJ_mass_SRCR->GetLowerRefYaxis()->SetTitle("SR/CR ratio");
  rp_SJ_mass_SRCR->GetLowerRefGraph()->SetMaximum(2.);
  rp_SJ_mass_SRCR->GetUpperRefYaxis()->SetTitle("Events");
  c1->SaveAs( (plot_home + "h_SJ_mass_data_SRCR_ratio_"+ year+".png").c_str()); 





  // compare normalized 0 and 1b anti-tag distributions 
  // compare normalized SR data to CR data 
  TH1F *h_diSuperjet_mass_data_1b_antiTag_copy = (TH1F*) h_diSuperjet_mass_allData_antiTag_1b->Clone();
  TH1F *h_diSuperjet_mass_data_0b_antiTag_copy = (TH1F*) h_diSuperjet_mass_allData_0b_antiTag->Clone();

  TH1F *h_SJ_mass_1b_antiTag_allData_copy = (TH1F*)h_SJ_mass_allData_antiTag_1b->Clone();
  TH1F *h_SJ_mass_0b_antiTag_allData_copy = (TH1F*)h_SJ_mass_allData_0b_antiTag->Clone();

  h_diSuperjet_mass_data_1b_antiTag_copy->Scale(1.0/h_diSuperjet_mass_data_1b_antiTag_copy->Integral());
  h_diSuperjet_mass_data_0b_antiTag_copy->Scale(1.0/h_diSuperjet_mass_data_0b_antiTag_copy->Integral());

  h_SJ_mass_1b_antiTag_allData_copy->Scale(1.0/h_SJ_mass_1b_antiTag_allData_copy->Integral());
  h_SJ_mass_0b_antiTag_allData_copy->Scale(1.0/h_SJ_mass_0b_antiTag_allData_copy->Integral());

  h_diSuperjet_mass_data_1b_antiTag_copy->SetTitle("diSuperjet Mass Shape Ratio of 1b antiTag data to 0b antiTag data ");
  auto rp_diSuperjet_mass_antiTag_norm = new TRatioPlot(h_diSuperjet_mass_data_1b_antiTag_copy,h_diSuperjet_mass_data_0b_antiTag_copy);
  //h_BR_combined->Draw("HIST");
  rp_diSuperjet_mass_antiTag_norm->Draw("HIST,EP");
  rp_diSuperjet_mass_antiTag_norm->GetLowerRefYaxis()->SetTitle("1b antiTag/0b antiTag ratio");
  rp_diSuperjet_mass_antiTag_norm->GetLowerRefGraph()->SetMaximum(2.);
  rp_diSuperjet_mass_antiTag_norm->GetUpperRefYaxis()->SetTitle("Events");
  c1->SaveAs( (plot_home + "h_diSuperjet_mass_data_antiTag_ratio_"+ year+".png").c_str()); 

  h_SJ_mass_1b_antiTag_allData_copy->SetTitle("SJ Mass Shape Ratio of 1b antiTag data to 0b antiTag data ");
  auto rp_SJ_mass_antiTag_norm = new TRatioPlot(h_SJ_mass_1b_antiTag_allData_copy,h_SJ_mass_0b_antiTag_allData_copy);
  //h_BR_combined->Draw("HIST");
  rp_SJ_mass_antiTag_norm->Draw("HIST,EP");
  rp_SJ_mass_antiTag_norm->GetLowerRefYaxis()->SetTitle("1b antiTag/0b antiTag ratio");
  rp_SJ_mass_antiTag_norm->GetLowerRefGraph()->SetMaximum(2.);
  rp_SJ_mass_antiTag_norm->GetUpperRefYaxis()->SetTitle("Events");
  c1->SaveAs( (plot_home + "h_SJ_mass_data_antiTag_ratio_"+ year+".png").c_str()); 








  //////////////////////////////////////////
  // make ratio plots comparing the normalized MC BR shapes in each region (all 3 plots)


  // SJ mass
  TH1F *h_SJ_mass_allBR_antiTag_norm    = (TH1F*) h_SJ_mass_allBR_antiTag->Clone();
  h_SJ_mass_allBR_antiTag_norm->Scale(1.0/h_SJ_mass_allBR_antiTag_norm->Integral());
  TH1F *h_SJ_mass_allBR_antiTag_1b_norm = (TH1F*) h_SJ_mass_allBR_antiTag_1b->Clone();
  h_SJ_mass_allBR_antiTag_1b_norm->Scale(1.0/h_SJ_mass_allBR_antiTag_1b_norm->Integral());

  TH1F *h_SJ_mass_allBR_SR_norm = (TH1F*) h_SJ_mass_SR_allBR->Clone();
  h_SJ_mass_allBR_SR_norm->Scale(1.0/h_SJ_mass_allBR_SR_norm->Integral());

  TH1F *h_SJ_mass_allBR_CR_norm = (TH1F*) h_SJ_mass_CR_allBR->Clone();
  h_SJ_mass_allBR_CR_norm->Scale(1.0/h_SJ_mass_allBR_CR_norm->Integral());


  // diSJ mass
  TH1F *h_disuperjet_mass_allBR_antiTag_norm    = (TH1F*) h_diSuperjet_mass_allBR_antiTag->Clone();
  h_disuperjet_mass_allBR_antiTag_norm->Scale(1.0/h_disuperjet_mass_allBR_antiTag_norm->Integral());
  TH1F *h_disuperjet_mass_allBR_antiTag_1b_norm = (TH1F*) h_diSuperjet_mass_allBR_antiTag_1b->Clone();
  h_disuperjet_mass_allBR_antiTag_1b_norm->Scale(1.0/h_disuperjet_mass_allBR_antiTag_1b_norm->Integral());

  TH1F *h_disuperjet_mass_allBR_SR_norm = (TH1F*) h_diSuperjet_mass_allBR_SR->Clone();
  h_disuperjet_mass_allBR_SR_norm->Scale(1.0/h_diSuperjet_mass_allBR_SR->Integral());

  TH1F *h_disuperjet_mass_allBR_CR_norm = (TH1F*) h_diSuperjet_mass_allBR_CR->Clone();
  h_disuperjet_mass_allBR_CR_norm->Scale(1.0/h_diSuperjet_mass_allBR_CR->Integral());


  // 2D distributions

  TH2F *h_MSJ_mass_vs_MdSJ_CR_allBR_norm = (TH2F*)h_MSJ_mass_vs_MdSJ_CR_allBR->Clone();
  h_MSJ_mass_vs_MdSJ_CR_allBR_norm->Scale(1.0/h_MSJ_mass_vs_MdSJ_CR_allBR_norm->Integral());
  TH2F *h_MSJ_mass_vs_MdSJ_SR_allBR_norm = (TH2F*)h_MSJ_mass_vs_MdSJ_SR_allBR->Clone();
  h_MSJ_mass_vs_MdSJ_SR_allBR_norm->Scale(1.0/h_MSJ_mass_vs_MdSJ_SR_allBR_norm->Integral());

  TH2F *h_MSJ_mass_vs_MdSJ_antiTagCR_allBR_antiTag_norm = (TH2F*)h_MSJ_mass_vs_MdSJ_antiTagCR_allBR_antiTag->Clone();
  h_MSJ_mass_vs_MdSJ_antiTagCR_allBR_antiTag_norm->Scale(1.0/h_MSJ_mass_vs_MdSJ_antiTagCR_allBR_antiTag_norm->Integral());

  TH2F *h_MSJ_mass_vs_MdSJ_antiTag_1b_allBR_antiTag_1b_norm = (TH2F*)h_MSJ_mass_vs_MdSJ_antiTag_1b_allBR_antiTag_1b->Clone();
  h_MSJ_mass_vs_MdSJ_antiTag_1b_allBR_antiTag_1b_norm->Scale(1.0/h_MSJ_mass_vs_MdSJ_antiTag_1b_allBR_antiTag_1b_norm->Integral());


  /////// SRCR ////////

  h_SJ_mass_allBR_SR_norm->SetTitle("SJ Mass Ratio of SR MC to CR MC ");
  auto rp_SJ_mass_MC_SRCR = new TRatioPlot(h_SJ_mass_allBR_SR_norm,h_SJ_mass_allBR_CR_norm);
  //h_BR_combined->Draw("HIST");
  rp_SJ_mass_MC_SRCR->Draw("HIST,EP");
  rp_SJ_mass_MC_SRCR->GetLowerRefYaxis()->SetTitle("SR MC/CR MC ratio");
  rp_SJ_mass_MC_SRCR->GetLowerRefGraph()->SetMaximum(2.);
  rp_SJ_mass_MC_SRCR->GetUpperRefYaxis()->SetTitle("Events");
  c1->SaveAs( (plot_home + "rp_SJ_mass_MC_SRCR_"+ year+".png").c_str()); 

  h_disuperjet_mass_allBR_SR_norm->SetTitle("diSuperjet Mass Ratio of SR MC to CR MC ");
  auto rp_disuperjet_mass_MC_SRCR = new TRatioPlot(h_disuperjet_mass_allBR_SR_norm,h_disuperjet_mass_allBR_CR_norm);
  //h_BR_combined->Draw("HIST");
  rp_disuperjet_mass_MC_SRCR->Draw("HIST,EP");
  rp_disuperjet_mass_MC_SRCR->GetLowerRefYaxis()->SetTitle("SR MC / CR MC ratio");
  rp_disuperjet_mass_MC_SRCR->GetLowerRefGraph()->SetMaximum(2.);
  rp_disuperjet_mass_MC_SRCR->GetUpperRefYaxis()->SetTitle("Events");
  c1->SaveAs( (plot_home + "rp_disuperjet_mass_MC_SRCR_"+ year+".png").c_str()); 


  h_MSJ_mass_vs_MdSJ_SR_allBR_norm->Divide(h_MSJ_mass_vs_MdSJ_CR_allBR_norm);
  h_MSJ_mass_vs_MdSJ_SR_allBR_norm->SetTitle("SR MC /CR MC ratio (2018)");
  h_MSJ_mass_vs_MdSJ_SR_allBR_norm->SetMaximum(5.0); 
  h_MSJ_mass_vs_MdSJ_SR_allBR_norm->Draw("colz");
  c1->SaveAs( (plot_home + "h_MSJ_mass_vs_MdSJ_allBR_SRCR_ratio_"+ year+".png").c_str());

  // antiTag

  h_SJ_mass_allBR_antiTag_1b_norm->SetTitle("SJ Mass Ratio of 1b antiTag Region MC to 0b antiTag Region MC ");
  auto rp_SJ_mass_MC_antiTag = new TRatioPlot(h_SJ_mass_allBR_antiTag_1b_norm,h_SJ_mass_allBR_antiTag_norm);
  //h_BR_combined->Draw("HIST");
  rp_SJ_mass_MC_antiTag->Draw("HIST,EP");
  rp_SJ_mass_MC_antiTag->GetLowerRefYaxis()->SetTitle("1b antiTag MC/0b antiTag MC ratio");
  rp_SJ_mass_MC_antiTag->GetLowerRefGraph()->SetMaximum(2.);
  rp_SJ_mass_MC_antiTag->GetUpperRefYaxis()->SetTitle("Events");
  c1->SaveAs( (plot_home + "rp_SJ_mass_MC_antiTag_"+ year+".png").c_str()); 

  h_disuperjet_mass_allBR_antiTag_1b_norm->SetTitle("diSuperjet Mass Ratio of 1b antiTag Region MC to 0b antiTag Region MC");
  auto rp_disuperjet_mass_MC_antiTag = new TRatioPlot(h_disuperjet_mass_allBR_antiTag_1b_norm,h_disuperjet_mass_allBR_antiTag_norm);
  //h_BR_combined->Draw("HIST");
  rp_disuperjet_mass_MC_antiTag->Draw("HIST,EP");
  rp_disuperjet_mass_MC_antiTag->GetLowerRefYaxis()->SetTitle("1b antiTag MC/0b antiTag MC ratio");
  rp_disuperjet_mass_MC_antiTag->GetLowerRefGraph()->SetMaximum(2.);
  rp_disuperjet_mass_MC_antiTag->GetUpperRefYaxis()->SetTitle("Events");
  c1->SaveAs( (plot_home + "rp_disuperjet_mass_MC_antiTag_"+ year+".png").c_str()); 


  h_MSJ_mass_vs_MdSJ_antiTag_1b_allBR_antiTag_1b_norm->Divide(h_MSJ_mass_vs_MdSJ_antiTagCR_allBR_antiTag_norm);
  h_MSJ_mass_vs_MdSJ_antiTag_1b_allBR_antiTag_1b_norm->SetTitle("1b antiTag MC/0b antiTag MC ratio");
  h_MSJ_mass_vs_MdSJ_antiTag_1b_allBR_antiTag_1b_norm->SetMaximum(5.0); 
  h_MSJ_mass_vs_MdSJ_antiTag_1b_allBR_antiTag_1b_norm->Draw("colz");
  c1->SaveAs( (plot_home + "h_MSJ_mass_vs_MdSJ_allBR_antiTag_ratio_"+ year+".png").c_str());



  // do AK4 stuff
  //print_hists("h_nAK4_all","rp_nAK4_all");





  TH1F *h_nAK4_HT1000to1500 = (TH1F*)f1->Get("nom_/h_nAK4_all");
  TH1F *h_nAK4_HT1500to2000 = (TH1F*)f2->Get("nom_/h_nAK4_all");
  TH1F *h_nAK4_HT2000toInf = (TH1F*)f3->Get("nom_/h_nAK4_all");

  TH1F *h_nAK4_TTToHadronicMC = (TH1F*)f4->Get("nom_/h_nAK4_all");
  TH1F *h_nAK4_TTToLeptonicMC = (TH1F*)f5->Get("nom_/h_nAK4_all");
  TH1F *h_nAK4_TTToSemiLeptonicMC = (TH1F*)f6->Get("nom_/h_nAK4_all");

  TH1F *h_nAK4_ST_s_channel_hadronsMC = (TH1F*)f7->Get("nom_/h_nAK4_all");
  TH1F *h_nAK4_ST_s_channel_leptonsMC = (TH1F*)f8->Get("nom_/h_nAK4_all");
  TH1F *h_nAK4_ST_t_channel_antitop = (TH1F*)f9->Get("nom_/h_nAK4_all");
  TH1F *h_nAK4_ST_t_channel_top = (TH1F*)f10->Get("nom_/h_nAK4_all");
  TH1F *h_nAK4_ST_tW_antiTop = (TH1F*)f11->Get("nom_/h_nAK4_all");
  TH1F *h_nAK4_ST_tW_top = (TH1F*)f12->Get("nom_/h_nAK4_all");


  std::vector<TH2F*> h_nAK4_data_hists = get_histograms<TH2F*>(dataFiles, "h_nAK4_all");
  TH2F * h_nAK4_allData = combine_histograms<TH2F*>(h_nAK4_data_hists);


  h_nAK4_HT1000to1500->Scale(QCD1000to1500_SF[SF_index]);
  h_nAK4_HT1500to2000->Scale(QCD1500to2000_SF[SF_index]);
  h_nAK4_HT2000toInf->Scale(QCD2000toInf_SF[SF_index]);
  h_nAK4_TTToHadronicMC->Scale(h_TTToHadronic_SF[SF_index]);
  h_nAK4_TTToLeptonicMC->Scale(h_TTTo2l2nu_SF[SF_index]);
  h_nAK4_TTToSemiLeptonicMC->Scale(h_TTToSemiLeptonic_SF[SF_index]);
  h_nAK4_ST_s_channel_hadronsMC->Scale(ST_s_channel_4f_hadrons_SF[SF_index]);
  h_nAK4_ST_s_channel_leptonsMC->Scale(ST_s_channel_4f_leptons_SF[SF_index]);
  h_nAK4_ST_t_channel_antitop->Scale(ST_t_channel_antitop_5f_SF[SF_index]);
  h_nAK4_ST_t_channel_top->Scale(ST_t_channel_top_5f_SF[SF_index]);
  h_nAK4_ST_tW_antiTop->Scale(ST_tW_antitop_5f_SF[SF_index]);
  h_nAK4_ST_tW_top->Scale(ST_tW_top_5f_SF[SF_index]);

  TH1F *h_nAK4_allBR = new TH1F(*h_nAK4_HT1000to1500);

  h_nAK4_allBR->Add(h_nAK4_HT1500to2000);
  h_nAK4_allBR->Add(h_nAK4_HT2000toInf);
  h_nAK4_allBR->Add(h_nAK4_TTToHadronicMC);
  h_nAK4_allBR->Add(h_nAK4_TTToLeptonicMC);
  h_nAK4_allBR->Add(h_nAK4_TTToSemiLeptonicMC);
  h_nAK4_allBR->Add(h_nAK4_ST_s_channel_hadronsMC);
  h_nAK4_allBR->Add(h_nAK4_ST_s_channel_leptonsMC);
  h_nAK4_allBR->Add(h_nAK4_ST_t_channel_antitop);
  h_nAK4_allBR->Add(h_nAK4_ST_t_channel_top);
  h_nAK4_allBR->Add(h_nAK4_ST_tW_antiTop);
  h_nAK4_allBR->Add(h_nAK4_ST_tW_top);

  h_nAK4_allBR->GetXaxis()->SetRangeUser(0., 5000.);



  auto rp_nAK4 = new TRatioPlot(h_nAK4_allData,h_nAK4_allBR);
  //h_BR_combined->Draw("HIST");
  rp_nAK4->Draw("HIST,EP");
  rp_nAK4->GetLowerRefYaxis()->SetTitle("data/MC ratio");
  rp_nAK4->GetLowerRefGraph()->SetMaximum(2.);
  rp_nAK4->GetUpperRefYaxis()->SetTitle("Events");
  c1->SaveAs( (plot_home + "rp_nAK4_all_"+ year+".png").c_str()); 



/////////


  TH1F *h_nAK4_all_barrel_HT1000to1500 = (TH1F*)f1->Get("nom_/h_nAK4_all_barrel");
  TH1F *h_nAK4_all_barrel_HT1500to2000 = (TH1F*)f2->Get("nom_/h_nAK4_all_barrel");
  TH1F *h_nAK4_all_barrel_HT2000toInf = (TH1F*)f3->Get("nom_/h_nAK4_all_barrel");

  TH1F *h_nAK4_all_barrel_TTToHadronicMC = (TH1F*)f4->Get("nom_/h_nAK4_all_barrel");
  TH1F *h_nAK4_all_barrel_TTToLeptonicMC = (TH1F*)f5->Get("nom_/h_nAK4_all_barrel");
  TH1F *h_nAK4_all_barrel_TTToSemiLeptonicMC = (TH1F*)f6->Get("nom_/h_nAK4_all_barrel");

  TH1F *h_nAK4_all_barrel_ST_s_channel_hadronsMC = (TH1F*)f7->Get("nom_/h_nAK4_all_barrel");
  TH1F *h_nAK4_all_barrel_ST_s_channel_leptonsMC = (TH1F*)f8->Get("nom_/h_nAK4_all_barrel");
  TH1F *h_nAK4_all_barrel_ST_t_channel_antitop = (TH1F*)f9->Get("nom_/h_nAK4_all_barrel");
  TH1F *h_nAK4_all_barrel_ST_t_channel_top = (TH1F*)f10->Get("nom_/h_nAK4_all_barrel");
  TH1F *h_nAK4_all_barrel_ST_tW_antiTop = (TH1F*)f11->Get("nom_/h_nAK4_all_barrel");
  TH1F *h_nAK4_all_barrel_ST_tW_top = (TH1F*)f12->Get("nom_/h_nAK4_all_barrel");


  std::vector<TH2F*> h_nAK4_all_barrel_data_hists = get_histograms<TH2F*>(dataFiles, "h_nAK4_all_barrel");
  TH2F * h_nAK4_all_barrel_allData = combine_histograms<TH2F*>(h_nAK4_all_barrel_data_hists);


  h_nAK4_all_barrel_HT1000to1500->Scale(QCD1000to1500_SF[SF_index]);
  h_nAK4_all_barrel_HT1500to2000->Scale(QCD1500to2000_SF[SF_index]);
  h_nAK4_all_barrel_HT2000toInf->Scale(QCD2000toInf_SF[SF_index]);
  h_nAK4_all_barrel_TTToHadronicMC->Scale(h_TTToHadronic_SF[SF_index]);
  h_nAK4_all_barrel_TTToLeptonicMC->Scale(h_TTTo2l2nu_SF[SF_index]);
  h_nAK4_all_barrel_TTToSemiLeptonicMC->Scale(h_TTToSemiLeptonic_SF[SF_index]);
  h_nAK4_all_barrel_ST_s_channel_hadronsMC->Scale(ST_s_channel_4f_hadrons_SF[SF_index]);
  h_nAK4_all_barrel_ST_s_channel_leptonsMC->Scale(ST_s_channel_4f_leptons_SF[SF_index]);
  h_nAK4_all_barrel_ST_t_channel_antitop->Scale(ST_t_channel_antitop_5f_SF[SF_index]);
  h_nAK4_all_barrel_ST_t_channel_top->Scale(ST_t_channel_top_5f_SF[SF_index]);
  h_nAK4_all_barrel_ST_tW_antiTop->Scale(ST_tW_antitop_5f_SF[SF_index]);
  h_nAK4_all_barrel_ST_tW_top->Scale(ST_tW_top_5f_SF[SF_index]);

  TH1F *h_nAK4_all_barrel_allBR = new TH1F(*h_nAK4_all_barrel_HT1000to1500);

  h_nAK4_all_barrel_allBR->Add(h_nAK4_all_barrel_HT1500to2000);
  h_nAK4_all_barrel_allBR->Add(h_nAK4_all_barrel_HT2000toInf);
  h_nAK4_all_barrel_allBR->Add(h_nAK4_all_barrel_TTToHadronicMC);
  h_nAK4_all_barrel_allBR->Add(h_nAK4_all_barrel_TTToLeptonicMC);
  h_nAK4_all_barrel_allBR->Add(h_nAK4_all_barrel_TTToSemiLeptonicMC);
  h_nAK4_all_barrel_allBR->Add(h_nAK4_all_barrel_ST_s_channel_hadronsMC);
  h_nAK4_all_barrel_allBR->Add(h_nAK4_all_barrel_ST_s_channel_leptonsMC);
  h_nAK4_all_barrel_allBR->Add(h_nAK4_all_barrel_ST_t_channel_antitop);
  h_nAK4_all_barrel_allBR->Add(h_nAK4_all_barrel_ST_t_channel_top);
  h_nAK4_all_barrel_allBR->Add(h_nAK4_all_barrel_ST_tW_antiTop);
  h_nAK4_all_barrel_allBR->Add(h_nAK4_all_barrel_ST_tW_top);

  h_nAK4_all_barrel_allBR->GetXaxis()->SetRangeUser(0., 5000.);



  auto rp_nAK4_endcap = new TRatioPlot(h_nAK4_all_barrel_allData,h_nAK4_all_barrel_allBR);
  //h_BR_combined->Draw("HIST");
  rp_nAK4_endcap->Draw("HIST,EP");
  rp_nAK4_endcap->GetLowerRefYaxis()->SetTitle("data/MC ratio");
  rp_nAK4_endcap->GetLowerRefGraph()->SetMaximum(2.);
  rp_nAK4_endcap->GetUpperRefYaxis()->SetTitle("Events");
  c1->SaveAs( (plot_home + "rp_nAK4_endcap_all_"+ year+".png").c_str()); 




  TH1F *h_nAK4_all_endcap_HT1000to1500 = (TH1F*)f1->Get("nom_/h_nAK4_all_endcap");
  TH1F *h_nAK4_all_endcap_HT1500to2000 = (TH1F*)f2->Get("nom_/h_nAK4_all_endcap");
  TH1F *h_nAK4_all_endcap_HT2000toInf = (TH1F*)f3->Get("nom_/h_nAK4_all_endcap");

  TH1F *h_nAK4_all_endcap_TTToHadronicMC = (TH1F*)f4->Get("nom_/h_nAK4_all_endcap");
  TH1F *h_nAK4_all_endcap_TTToLeptonicMC = (TH1F*)f5->Get("nom_/h_nAK4_all_endcap");
  TH1F *h_nAK4_all_endcap_TTToSemiLeptonicMC = (TH1F*)f6->Get("nom_/h_nAK4_all_endcap");

  TH1F *h_nAK4_all_endcap_ST_s_channel_hadronsMC = (TH1F*)f7->Get("nom_/h_nAK4_all_endcap");
  TH1F *h_nAK4_all_endcap_ST_s_channel_leptonsMC = (TH1F*)f8->Get("nom_/h_nAK4_all_endcap");
  TH1F *h_nAK4_all_endcap_ST_t_channel_antitop = (TH1F*)f9->Get("nom_/h_nAK4_all_endcap");
  TH1F *h_nAK4_all_endcap_ST_t_channel_top = (TH1F*)f10->Get("nom_/h_nAK4_all_endcap");
  TH1F *h_nAK4_all_endcap_ST_tW_antiTop = (TH1F*)f11->Get("nom_/h_nAK4_all_endcap");
  TH1F *h_nAK4_all_endcap_ST_tW_top = (TH1F*)f12->Get("nom_/h_nAK4_all_endcap");


  std::vector<TH2F*> h_nAK4_all_endcap_data_hists = get_histograms<TH2F*>(dataFiles, "h_nAK4_all_endcap");
  TH2F * h_nAK4_all_endcap_allData = combine_histograms<TH2F*>(h_nAK4_all_endcap_data_hists);


  h_nAK4_all_endcap_HT1000to1500->Scale(QCD1000to1500_SF[SF_index]);
  h_nAK4_all_endcap_HT1500to2000->Scale(QCD1500to2000_SF[SF_index]);
  h_nAK4_all_endcap_HT2000toInf->Scale(QCD2000toInf_SF[SF_index]);
  h_nAK4_all_endcap_TTToHadronicMC->Scale(h_TTToHadronic_SF[SF_index]);
  h_nAK4_all_endcap_TTToLeptonicMC->Scale(h_TTTo2l2nu_SF[SF_index]);
  h_nAK4_all_endcap_TTToSemiLeptonicMC->Scale(h_TTToSemiLeptonic_SF[SF_index]);
  h_nAK4_all_endcap_ST_s_channel_hadronsMC->Scale(ST_s_channel_4f_hadrons_SF[SF_index]);
  h_nAK4_all_endcap_ST_s_channel_leptonsMC->Scale(ST_s_channel_4f_leptons_SF[SF_index]);
  h_nAK4_all_endcap_ST_t_channel_antitop->Scale(ST_t_channel_antitop_5f_SF[SF_index]);
  h_nAK4_all_endcap_ST_t_channel_top->Scale(ST_t_channel_top_5f_SF[SF_index]);
  h_nAK4_all_endcap_ST_tW_antiTop->Scale(ST_tW_antitop_5f_SF[SF_index]);
  h_nAK4_all_endcap_ST_tW_top->Scale(ST_tW_top_5f_SF[SF_index]);

  TH1F *h_nAK4_all_endcap_allBR = new TH1F(*h_nAK4_all_endcap_HT1000to1500);

  h_nAK4_all_endcap_allBR->Add(h_nAK4_all_endcap_HT1500to2000);
  h_nAK4_all_endcap_allBR->Add(h_nAK4_all_endcap_HT2000toInf);
  h_nAK4_all_endcap_allBR->Add(h_nAK4_all_endcap_TTToHadronicMC);
  h_nAK4_all_endcap_allBR->Add(h_nAK4_all_endcap_TTToLeptonicMC);
  h_nAK4_all_endcap_allBR->Add(h_nAK4_all_endcap_TTToSemiLeptonicMC);
  h_nAK4_all_endcap_allBR->Add(h_nAK4_all_endcap_ST_s_channel_hadronsMC);
  h_nAK4_all_endcap_allBR->Add(h_nAK4_all_endcap_ST_s_channel_leptonsMC);
  h_nAK4_all_endcap_allBR->Add(h_nAK4_all_endcap_ST_t_channel_antitop);
  h_nAK4_all_endcap_allBR->Add(h_nAK4_all_endcap_ST_t_channel_top);
  h_nAK4_all_endcap_allBR->Add(h_nAK4_all_endcap_ST_tW_antiTop);
  h_nAK4_all_endcap_allBR->Add(h_nAK4_all_endcap_ST_tW_top);

  h_nAK4_all_endcap_allBR->GetXaxis()->SetRangeUser(0., 5000.);



  auto rp_nAK4_barrel = new TRatioPlot(h_nAK4_all_endcap_allData,h_nAK4_all_endcap_allBR);
  //h_BR_combined->Draw("HIST");
  rp_nAK4_barrel->Draw("HIST,EP");
  rp_nAK4_barrel->GetLowerRefYaxis()->SetTitle("data/MC ratio");
  rp_nAK4_barrel->GetLowerRefGraph()->SetMaximum(2.);
  rp_nAK4_barrel->GetUpperRefYaxis()->SetTitle("Events");
  c1->SaveAs( (plot_home + "rp_nAK4_barrel_all_"+ year+".png").c_str()); 
}

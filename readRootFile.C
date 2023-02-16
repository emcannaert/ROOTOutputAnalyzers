#include <iostream>
#include <string>
#include "TLorentzVector.h"
#include "TRatioPlot.h"
#include "THStack.h"
using namespace std;

void readRootFile()
{

  TFile *f1 = new TFile("/home/ethan/Downloads/mttbar_inputHists_ALPtoTTbar_MinWorkExample_fa5p0.root");

  TH1F *SR0T_bin1_ALP_ttbar_signal = (TH1F*)f1->Get("SR0T_bin1_ALP_ttbar_signal");
  TH1F *SR0T_bin1_ALP_ttbar_signal_shapeSystUp = (TH1F*)f1->Get("SR0T_bin1_ALP_ttbar_signal_shapeSystUp");
  TH1F *SR0T_bin1_ALP_ttbar_signal_shapeSystDown = (TH1F*)f1->Get("SR0T_bin1_ALP_ttbar_signal_shapeSystDown");
  TH1F *SR0T_bin1_ALP_ttbar_interference = (TH1F*)f1->Get("SR0T_bin1_ALP_ttbar_interference");
  TH1F *SR0T_bin1_ALP_ttbar_interference_shapeSystUp = (TH1F*)f1->Get("SR0T_bin1_ALP_ttbar_interference_shapeSystUp");
  TH1F *SR0T_bin1_ALP_ttbar_interference_shapeSystDown = (TH1F*)f1->Get("SR0T_bin1_ALP_ttbar_interference_shapeSystDown");
  TH1F *SR0T_bin1_TTbar = (TH1F*)f1->Get("SR0T_bin1_TTbar");
  TH1F *SR0T_bin1_ST = (TH1F*)f1->Get("SR0T_bin1_ST");
  TH1F *SR0T_bin1_WJets = (TH1F*)f1->Get("SR0T_bin1_WJets");
  TH1F *SR0T_bin1_others = (TH1F*)f1->Get("SR0T_bin1_others");
  TH1F *SR0T_bin1_data_obs = (TH1F*)f1->Get("SR0T_bin1_data_obs");

  std::cout << "SR0T_bin1_ALP_ttbar_signal Integral is " << SR0T_bin1_ALP_ttbar_signal->Integral() << std::endl;
  std::cout << "SR0T_bin1_ALP_ttbar_signal_shapeSystUp Integral is " << SR0T_bin1_ALP_ttbar_signal_shapeSystUp->Integral()<< std::endl;
  std::cout << "SR0T_bin1_ALP_ttbar_signal_shapeSystDown Integral is " << SR0T_bin1_ALP_ttbar_signal_shapeSystDown->Integral()<< std::endl;
  std::cout << "SR0T_bin1_ALP_ttbar_interference Integral is " << SR0T_bin1_ALP_ttbar_interference->Integral() << std::endl;
  std::cout << "SR0T_bin1_ALP_ttbar_interference_shapeSystUp Integral is " << SR0T_bin1_ALP_ttbar_interference_shapeSystUp->Integral() << std::endl;
  std::cout << "SR0T_bin1_ALP_ttbar_interference_shapeSystDown Integral is " << SR0T_bin1_ALP_ttbar_interference_shapeSystDown->Integral()<< std::endl;
  std::cout << "SR0T_bin1_TTbar Integral is " << SR0T_bin1_TTbar->Integral()<< std::endl;
  std::cout << "SR0T_bin1_ST Integral is " << SR0T_bin1_ST->Integral() << std::endl;
  std::cout << "SR0T_bin1_WJets Integral is " << SR0T_bin1_WJets->Integral() << std::endl;
  std::cout << "SR0T_bin1_others Integral is " << SR0T_bin1_others->Integral()<< std::endl;
  std::cout << "SR0T_bin1_data_obs Integral is " << SR0T_bin1_data_obs->Integral() << std::endl;

}

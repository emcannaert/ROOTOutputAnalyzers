#include <iostream>
#include <string>
#include "TLorentzVector.h"
#include "TRatioPlot.h"
#include "THStack.h"
using namespace std;

void makeDataMCCRComparison()
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

  TFile *f4 = new TFile("/home/ethan/Documents/JetHT_2018A_processed.root");   
  TFile *f5 = new TFile("/home/ethan/Documents/JetHT_2018B_processed.root");   
  TFile *f6 = new TFile("/home/ethan/Documents/JetHT_2018C_processed.root");   
  TFile *f7 = new TFile("/home/ethan/Documents/JetHT_2018D_processed.root");   

  //create histogramas for each of the different plots for different HT levels, scale histograms, add together histograms, normalize, do division/ comparison
  std::cout << "Get histograms" << std::endl;
  ///////////////////////////////1000to1500//////////////////////////////////
  TH1I *h_SJ_nAK4_100_CR_HT1000to1500 =      (TH1I*)f1->Get("h_SJ_nAK4_100_CR");
  TH1I *h_SJ_nAK4_200_CR_HT1000to1500 =      (TH1I*)f1->Get("h_SJ_nAK4_200_CR");
  TH1F *h_SJ_mass_CR_HT1000to1500 =          (TH1F*)f1->Get("h_SJ_mass_CR");
  TH1F *h_disuperjet_mass_CR_HT1000to1500 =  (TH1F*)f1->Get("h_disuperjet_mass_CR");
  TH2F *h_MSJ_mass_vs_MdSJ_CR_HT1000to1500 = (TH2F*)f1->Get("h_MSJ_mass_vs_MdSJ_CR");
  TH1F *h_totHT_All_HT1000to1500 =  (TH1F*)f1->Get("h_totHT_All");

  TH1F* h_AK8_jet_mass_QCD_HT1000to1500_CR    =      (TH1F*)f1->Get("h_AK8_jet_mass_CR");
  TH1F* h_AK4_jet_mass_QCD_HT1000to1500_CR    =      (TH1F*)f1->Get("h_AK4_jet_mass_CR");
  TH1F* h_totHT_QCD_HT1000to1500_CR           =      (TH1F*)f1->Get("h_totHT_CR");
  TH1I* h_nfatjets_QCD_HT1000to1500_CR        =      (TH1I*)f1->Get("h_nfatjets_CR");
  TH1I* h_nAK4_QCD_HT1000to1500_CR            =      (TH1I*)f1->Get("h_nAK4_CR");

  TH1I* h_nTightBTags_HT1000to1500_CR            =      (TH1I*)f1->Get("h_nTightBTags");
  TH1I* h_nMidBTags_HT1000to1500_CR              =      (TH1I*)f1->Get("h_nMidBTags");
  TH1I* h_nLooseBTags_HT1000to1500_CR            =      (TH1I*)f1->Get("h_nLooseBTags");

  TH1F* h_AK4_DeepJet_disc_HT1000to1500_CR    =      (TH1F*)f1->Get("h_AK4_DeepJet_disc");
  TH1I* h_nAK4_HT1000to1500_CR            =      (TH1I*)f1->Get("h_nAK4");




////////////////////////////////////// 1500to2000 /////////////////////////////////////////
  TH1I *h_SJ_nAK4_100_CR_HT1500to2000 =      (TH1I*)f2->Get("h_SJ_nAK4_100_CR");
  TH1I *h_SJ_nAK4_200_CR_HT1500to2000 =      (TH1I*)f2->Get("h_SJ_nAK4_200_CR");
  TH1F *h_SJ_mass_CR_HT1500to2000 =          (TH1F*)f2->Get("h_SJ_mass_CR");
  TH1F *h_disuperjet_mass_CR_HT1500to2000 =  (TH1F*)f2->Get("h_disuperjet_mass_CR");
  TH2F *h_MSJ_mass_vs_MdSJ_CR_HT1500to2000 = (TH2F*)f2->Get("h_MSJ_mass_vs_MdSJ_CR");
  TH1F *h_totHT_All_HT1500to2000 =  (TH1F*)f2->Get("h_totHT_All");

  TH1F* h_AK8_jet_mass_QCD_HT1500to2000_CR    =      (TH1F*)f2->Get("h_AK8_jet_mass_CR");
  TH1F* h_AK4_jet_mass_QCD_HT1500to2000_CR    =      (TH1F*)f2->Get("h_AK4_jet_mass_CR");
  TH1F* h_totHT_QCD_HT1500to2000_CR           =      (TH1F*)f2->Get("h_totHT_CR");
  TH1I* h_nfatjets_QCD_HT1500to2000_CR        =      (TH1I*)f2->Get("h_nfatjets_CR");
  TH1I* h_nAK4_QCD_HT1500to2000_CR            =      (TH1I*)f2->Get("h_nAK4_CR");

  TH1I* h_nTightBTags_HT1500to2000_CR            =      (TH1I*)f2->Get("h_nTightBTags");
  TH1I* h_nMidBTags_HT1500to2000_CR              =      (TH1I*)f2->Get("h_nMidBTags");
  TH1I* h_nLooseBTags_HT1500to2000_CR            =      (TH1I*)f2->Get("h_nLooseBTags");

  TH1F* h_AK4_DeepJet_disc_HT1500to2000_CR    =      (TH1F*)f2->Get("h_AK4_DeepJet_disc");
  TH1I* h_nAK4_HT1500to2000_CR            =      (TH1I*)f2->Get("h_nAK4");

////////////////////////////////////// 2000toInf /////////////////////////////////////////
  TH1I *h_SJ_nAK4_100_CR_HT2000toInf =      (TH1I*)f3->Get("h_SJ_nAK4_100_CR");
  TH1I *h_SJ_nAK4_200_CR_HT2000toInf =      (TH1I*)f3->Get("h_SJ_nAK4_200_CR");
  TH1F *h_SJ_mass_CR_HT2000toInf =          (TH1F*)f3->Get("h_SJ_mass_CR");
  TH1F *h_disuperjet_mass_CR_HT2000toInf =  (TH1F*)f3->Get("h_disuperjet_mass_CR");
  TH2F *h_MSJ_mass_vs_MdSJ_CR_HT2000toInf = (TH2F*)f3->Get("h_MSJ_mass_vs_MdSJ_CR");
  TH1F *h_totHT_All_HT2000toInf =  (TH1F*)f3->Get("h_totHT_All");

  TH1F* h_AK8_jet_mass_QCD_HT2000toInf_CR    =      (TH1F*)f3->Get("h_AK8_jet_mass_CR");
  TH1F* h_AK4_jet_mass_QCD_HT2000toInf_CR    =      (TH1F*)f3->Get("h_AK4_jet_mass_CR");
  TH1F* h_totHT_QCD_HT2000toInf_CR           =      (TH1F*)f3->Get("h_totHT_CR");
  TH1I* h_nfatjets_QCD_HT2000toInf_CR        =      (TH1I*)f3->Get("h_nfatjets_CR");
  TH1I* h_nAK4_QCD_HT2000toInf_CR            =      (TH1I*)f3->Get("h_nAK4_CR");

  TH1I* h_nTightBTags_HT2000toInf_CR            =      (TH1I*)f3->Get("h_nTightBTags");
  TH1I* h_nMidBTags_HT2000toInf_CR              =      (TH1I*)f3->Get("h_nMidBTags");
  TH1I* h_nLooseBTags_HT2000toInf_CR            =      (TH1I*)f3->Get("h_nLooseBTags");

  TH1F* h_AK4_DeepJet_disc_HT2000toInf_CR    =      (TH1F*)f3->Get("h_AK4_DeepJet_disc");
  TH1I* h_nAK4_HT2000toInf_CR            =      (TH1I*)f3->Get("h_nAK4");


  //////////////////////////////////// JetHT combined data /////////////////////////////////////////

  TH1I *h_SJ_nAK4_100_CR_2018A       =  (TH1I*)f4->Get("h_SJ_nAK4_100_CR");
  TH1I *h_SJ_nAK4_200_CR_2018A       =  (TH1I*)f4->Get("h_SJ_nAK4_200_CR");
  TH1F *h_SJ_mass_CR_2018A           =  (TH1F*)f4->Get("h_SJ_mass_CR");
  TH1F *h_disuperjet_mass_CR_2018A   =  (TH1F*)f4->Get("h_disuperjet_mass_CR");
  TH2F *h_MSJ_mass_vs_MdSJ_CR_2018A  =  (TH2F*)f4->Get("h_MSJ_mass_vs_MdSJ_CR");
  TH1F *h_totHT_All_2018A            =  (TH1F*)f4->Get("h_totHT_All");

  TH1F* h_AK8_jet_mass_2018A        =      (TH1F*)f4->Get("h_AK8_jet_mass_CR");
  TH1F* h_AK4_jet_mass_2018A        =      (TH1F*)f4->Get("h_AK4_jet_mass_CR");
  TH1F* h_totHT_CR_2018A           =      (TH1F*)f4->Get("h_totHT_CR");
  TH1I* h_nfatjets_CR_2018A        =      (TH1I*)f4->Get("h_nfatjets_CR");
  TH1I* h_nAK4_CR_2018A            =      (TH1I*)f4->Get("h_nAK4_CR");

/////////////////////////////////////////////////////////////////////////////////
  TH1I *h_SJ_nAK4_100_CR_2018B       =  (TH1I*)f5->Get("h_SJ_nAK4_100_CR");
  TH1I *h_SJ_nAK4_200_CR_2018B       =  (TH1I*)f5->Get("h_SJ_nAK4_200_CR");
  TH1F *h_SJ_mass_CR_2018B           =  (TH1F*)f5->Get("h_SJ_mass_CR");
  TH1F *h_disuperjet_mass_CR_2018B   =  (TH1F*)f5->Get("h_disuperjet_mass_CR");
  TH2F *h_MSJ_mass_vs_MdSJ_CR_2018B  =  (TH2F*)f5->Get("h_MSJ_mass_vs_MdSJ_CR");
  TH1F *h_totHT_All_2018B            =  (TH1F*)f5->Get("h_totHT_All");

  TH1F* h_AK8_jet_mass_2018B        =      (TH1F*)f5->Get("h_AK8_jet_mass_CR");
  TH1F* h_AK4_jet_mass_2018B        =      (TH1F*)f5->Get("h_AK4_jet_mass_CR");
  TH1F* h_totHT_CR_2018B           =      (TH1F*)f5->Get("h_totHT_CR");
  TH1I* h_nfatjets_CR_2018B        =      (TH1I*)f5->Get("h_nfatjets_CR");
  TH1I* h_nAK4_CR_2018B            =      (TH1I*)f5->Get("h_nAK4_CR");

/////////////////////////////////////////////////////////////////////////////////
  TH1I *h_SJ_nAK4_100_CR_2018C       =  (TH1I*)f6->Get("h_SJ_nAK4_100_CR");
  TH1I *h_SJ_nAK4_200_CR_2018C       =  (TH1I*)f6->Get("h_SJ_nAK4_200_CR");
  TH1F *h_SJ_mass_CR_2018C           =  (TH1F*)f6->Get("h_SJ_mass_CR");
  TH1F *h_disuperjet_mass_CR_2018C   =  (TH1F*)f6->Get("h_disuperjet_mass_CR");
  TH2F *h_MSJ_mass_vs_MdSJ_CR_2018C  =  (TH2F*)f6->Get("h_MSJ_mass_vs_MdSJ_CR");
  TH1F *h_totHT_All_2018C            =  (TH1F*)f6->Get("h_totHT_All");

  TH1F* h_AK8_jet_mass_2018C        =      (TH1F*)f6->Get("h_AK8_jet_mass_CR");
  TH1F* h_AK4_jet_mass_2018C        =      (TH1F*)f6->Get("h_AK4_jet_mass_CR");
  TH1F* h_totHT_CR_2018C           =      (TH1F*)f6->Get("h_totHT_CR");
  TH1I* h_nfatjets_CR_2018C        =      (TH1I*)f6->Get("h_nfatjets_CR");
  TH1I* h_nAK4_CR_2018C            =      (TH1I*)f6->Get("h_nAK4_CR");
///////////////////////////////////////////////////////////////////////////////


  TH1I *h_SJ_nAK4_100_CR_2018D       =  (TH1I*)f7->Get("h_SJ_nAK4_100_CR");
  TH1I *h_SJ_nAK4_200_CR_2018D       =  (TH1I*)f7->Get("h_SJ_nAK4_200_CR");
  TH1F *h_SJ_mass_CR_2018D           =  (TH1F*)f7->Get("h_SJ_mass_CR");
  TH1F *h_disuperjet_mass_CR_2018D   =  (TH1F*)f7->Get("h_disuperjet_mass_CR");
  TH2F *h_MSJ_mass_vs_MdSJ_CR_2018D  =  (TH2F*)f7->Get("h_MSJ_mass_vs_MdSJ_CR");
  TH1F *h_totHT_All_2018D            =  (TH1F*)f7->Get("h_totHT_All");

  TH1F* h_AK8_jet_mass_2018D        =      (TH1F*)f7->Get("h_AK8_jet_mass_CR");
  TH1F* h_AK4_jet_mass_2018D        =      (TH1F*)f7->Get("h_AK4_jet_mass_CR");
  TH1F* h_totHT_CR_2018D           =      (TH1F*)f7->Get("h_totHT_CR");
  TH1I* h_nfatjets_CR_2018D        =      (TH1I*)f7->Get("h_nfatjets_CR");
  TH1I* h_nAK4_CR_2018D            =      (TH1I*)f7->Get("h_nAK4_CR");

/*
  TH1I* h_nTightBTags_data            =      (TH1I*)f7->Get("h_nTightBTags");
  TH1I* h_nMidBTags_data              =      (TH1I*)f7->Get("h_nMidBTags");
  TH1I* h_nLooseBTags_data            =      (TH1I*)f7->Get("h_nLooseBTags");

  TH1F* h_AK4_DeepJet_disc_data    =      (TH1F*)f7->Get("h_AK4_DeepJet_disc");
  TH1I* h_nAK4_data            =      (TH1I*)f7->Get("h_nAK4");
*/

  std::cout << "Scale histograms 1" << std::endl;

  h_SJ_nAK4_100_CR_HT1000to1500->Scale(QCD_HT1000to1500_SF);
  h_SJ_nAK4_200_CR_HT1000to1500->Scale(QCD_HT1000to1500_SF);
  h_SJ_mass_CR_HT1000to1500->Scale(QCD_HT1000to1500_SF);
  h_disuperjet_mass_CR_HT1000to1500->Scale(QCD_HT1000to1500_SF);
  h_MSJ_mass_vs_MdSJ_CR_HT1000to1500->Scale(QCD_HT1000to1500_SF);
  h_AK8_jet_mass_QCD_HT1000to1500_CR->Scale(QCD_HT1000to1500_SF);
  h_AK4_jet_mass_QCD_HT1000to1500_CR->Scale(QCD_HT1000to1500_SF);
  h_totHT_QCD_HT1000to1500_CR->Scale(QCD_HT1000to1500_SF);
  h_nfatjets_QCD_HT1000to1500_CR->Scale(QCD_HT1000to1500_SF);
  h_nAK4_QCD_HT1000to1500_CR->Scale(QCD_HT1000to1500_SF);
  h_totHT_All_HT1000to1500->Scale(QCD_HT1000to1500_SF);
  h_nTightBTags_HT1000to1500_CR->Scale(QCD_HT1000to1500_SF);
  h_nMidBTags_HT1000to1500_CR->Scale(QCD_HT1000to1500_SF);
  h_nLooseBTags_HT1000to1500_CR->Scale(QCD_HT1000to1500_SF);
  h_AK4_DeepJet_disc_HT1000to1500_CR->Scale(QCD_HT1000to1500_SF);
  h_nAK4_HT1000to1500_CR->Scale(QCD_HT1000to1500_SF);



  h_SJ_nAK4_100_CR_HT1500to2000->Scale(QCD_HT1500to2000_SF);
  h_SJ_nAK4_200_CR_HT1500to2000->Scale(QCD_HT1500to2000_SF);
  h_SJ_mass_CR_HT1500to2000->Scale(QCD_HT1500to2000_SF);
  h_disuperjet_mass_CR_HT1500to2000->Scale(QCD_HT1500to2000_SF);
  h_MSJ_mass_vs_MdSJ_CR_HT1500to2000->Scale(QCD_HT1500to2000_SF);
  h_AK8_jet_mass_QCD_HT1500to2000_CR->Scale(QCD_HT1500to2000_SF);
  h_AK4_jet_mass_QCD_HT1500to2000_CR->Scale(QCD_HT1500to2000_SF);
  h_totHT_QCD_HT1500to2000_CR->Scale(QCD_HT1500to2000_SF);
  h_nfatjets_QCD_HT1500to2000_CR->Scale(QCD_HT1500to2000_SF);
  h_nAK4_QCD_HT1500to2000_CR->Scale(QCD_HT1500to2000_SF);
  h_totHT_All_HT1500to2000->Scale(QCD_HT1500to2000_SF);
  h_nTightBTags_HT1500to2000_CR->Scale(QCD_HT1500to2000_SF);
  h_nMidBTags_HT1500to2000_CR->Scale(QCD_HT1500to2000_SF);
  h_nLooseBTags_HT1500to2000_CR->Scale(QCD_HT1500to2000_SF);
  h_AK4_DeepJet_disc_HT1500to2000_CR->Scale(QCD_HT1500to2000_SF);
  h_nAK4_HT1500to2000_CR->Scale(QCD_HT1500to2000_SF);



  h_SJ_nAK4_100_CR_HT2000toInf->Scale(QCD_HT2000toInf_SF);
  h_SJ_nAK4_200_CR_HT2000toInf->Scale(QCD_HT2000toInf_SF);
  h_SJ_mass_CR_HT2000toInf->Scale(QCD_HT2000toInf_SF);
  h_disuperjet_mass_CR_HT2000toInf->Scale(QCD_HT2000toInf_SF);
  h_MSJ_mass_vs_MdSJ_CR_HT2000toInf->Scale(QCD_HT2000toInf_SF);
  h_AK8_jet_mass_QCD_HT2000toInf_CR->Scale(QCD_HT2000toInf_SF);
  h_AK4_jet_mass_QCD_HT2000toInf_CR->Scale(QCD_HT2000toInf_SF);
  h_totHT_QCD_HT2000toInf_CR->Scale(QCD_HT2000toInf_SF);
  h_nfatjets_QCD_HT2000toInf_CR->Scale(QCD_HT2000toInf_SF);
  h_nAK4_QCD_HT2000toInf_CR->Scale(QCD_HT2000toInf_SF);
  h_totHT_All_HT2000toInf->Scale(QCD_HT2000toInf_SF);
  h_nTightBTags_HT2000toInf_CR->Scale(QCD_HT2000toInf_SF);
  h_nMidBTags_HT2000toInf_CR->Scale(QCD_HT2000toInf_SF);
  h_nLooseBTags_HT2000toInf_CR->Scale(QCD_HT2000toInf_SF);
  h_AK4_DeepJet_disc_HT2000toInf_CR->Scale(QCD_HT2000toInf_SF);
  h_nAK4_HT2000toInf_CR->Scale(QCD_HT2000toInf_SF);



////////////////////////////////////////////////////////////////////////////////////////////////////////

  std::cout << "Add and scale histograms" << std::endl;


  ////////////h_nAK4//////////////
  TH1I *h_nAK4 = new TH1I(*h_nAK4_HT2000toInf_CR);
  h_nAK4->Add(h_nAK4_HT1500to2000_CR);
  h_nAK4->Add(h_nAK4_HT1000to1500_CR);

  ////////////h_AK4_DeepJet_disc//////////////
  TH1F *h_AK4_DeepJet_disc = new TH1F(*h_AK4_DeepJet_disc_HT2000toInf_CR);
  h_AK4_DeepJet_disc->Add(h_AK4_DeepJet_disc_HT1500to2000_CR);
  h_AK4_DeepJet_disc->Add(h_AK4_DeepJet_disc_HT1000to1500_CR);

  ////////////h_nLooseBTags//////////////
  TH1I *h_nLooseBTags = new TH1I(*h_nLooseBTags_HT2000toInf_CR);
  h_nLooseBTags->Add(h_nLooseBTags_HT1500to2000_CR);
  h_nLooseBTags->Add(h_nLooseBTags_HT1000to1500_CR);

  ////////////h_nMidBTags//////////////
  TH1I *h_nMidBTags = new TH1I(*h_nMidBTags_HT2000toInf_CR);
  h_nMidBTags->Add(h_nMidBTags_HT1500to2000_CR);
  h_nMidBTags->Add(h_nMidBTags_HT1000to1500_CR);

  ////////////h_nLooseBTags//////////////

  TH1I *h_nTightBTags = new TH1I(*h_nTightBTags_HT2000toInf_CR);
  h_nTightBTags->Add(h_nTightBTags_HT1500to2000_CR);
  h_nTightBTags->Add(h_nTightBTags_HT1000to1500_CR);
  
  ////////////h_totHT_All//////////////
  TH1F *h_totHT_All = new TH1F(*h_totHT_All_HT2000toInf);
  h_totHT_All->Add(h_totHT_All_HT1500to2000);
  h_totHT_All->Add(h_totHT_All_HT1000to1500);

  ////////////nAK4_100//////////////
  TH1I *h_SJ_nAK4_100_CR = new TH1I(*h_SJ_nAK4_100_CR_HT2000toInf);
  h_SJ_nAK4_100_CR->Add(h_SJ_nAK4_100_CR_HT1500to2000);
  h_SJ_nAK4_100_CR->Add(h_SJ_nAK4_100_CR_HT1000to1500);

  h_SJ_nAK4_100_CR->SetFillColor(kRed);

//////////////////////////////////////////////////////////
  ////////////nAK4_200//////////////
  TH1I *h_SJ_nAK4_200_CR = new TH1I(*h_SJ_nAK4_200_CR_HT2000toInf);
  h_SJ_nAK4_200_CR->Add(h_SJ_nAK4_200_CR_HT1000to1500);
  h_SJ_nAK4_200_CR->Add(h_SJ_nAK4_200_CR_HT1500to2000);
  h_SJ_nAK4_200_CR->SetFillColor(kRed);


///////////////////////////////////////////////////////////
///////////h_SJ_mass//////////////////////
  TH1F *h_SJ_mass_CR = new TH1F(*h_SJ_mass_CR_HT2000toInf);
  h_SJ_mass_CR->Add(h_SJ_mass_CR_HT1000to1500);
  h_SJ_mass_CR->Add(h_SJ_mass_CR_HT1500to2000);
  h_SJ_mass_CR->SetFillColor(kRed);

///////////////////////////////////////////////////////////
///////////h_disuperjet_mass//////////////////////
  TH1F *h_disuperjet_mass_CR = new TH1F(*h_disuperjet_mass_CR_HT2000toInf);
  h_disuperjet_mass_CR->Add(h_disuperjet_mass_CR_HT1000to1500);
  h_disuperjet_mass_CR->Add(h_disuperjet_mass_CR_HT1500to2000);
  h_disuperjet_mass_CR->SetFillColor(kRed);

///////////////////////////////////////////////////////////
///////////h_disuperjet_mass//////////////////////
  TH2F *h_MSJ_mass_vs_MdSJ_CR = new TH2F(*h_MSJ_mass_vs_MdSJ_CR_HT2000toInf);
  h_MSJ_mass_vs_MdSJ_CR->Add(h_MSJ_mass_vs_MdSJ_CR_HT1000to1500);
  h_MSJ_mass_vs_MdSJ_CR->Add(h_MSJ_mass_vs_MdSJ_CR_HT1500to2000);

///////////////////////////////////////////////////////////
///////////h_AK8_jet_mass//////////////////////
  TH1F *h_AK8_jet_mass_CR = new TH1F(*h_AK8_jet_mass_QCD_HT2000toInf_CR);
  h_AK8_jet_mass_CR->Add(h_AK8_jet_mass_QCD_HT1000to1500_CR);
  h_AK8_jet_mass_CR->Add(h_AK8_jet_mass_QCD_HT1500to2000_CR);

///////////////////////////////////////////////////////////////////
///////////h_AK4_jet_mass//////////////////////
  TH1F *h_AK4_jet_mass_CR = new TH1F(*h_AK4_jet_mass_QCD_HT2000toInf_CR);
  h_AK4_jet_mass_CR->Add(h_AK4_jet_mass_QCD_HT1000to1500_CR);
  h_AK4_jet_mass_CR->Add(h_AK4_jet_mass_QCD_HT1500to2000_CR);

///////////////////////////////////////////////////////////////////
///////////h_totHT//////////////////////
  TH1F *h_totHT_CR = new TH1F(*h_totHT_QCD_HT2000toInf_CR);
  h_totHT_CR->Add(h_totHT_QCD_HT1000to1500_CR);
  h_totHT_CR->Add(h_totHT_QCD_HT1500to2000_CR);

///////////////////////////////////////////////////////////////////
///////////h_nfatjets//////////////////////
  TH1I *h_nfatjets_CR = new TH1I(*h_nfatjets_QCD_HT2000toInf_CR);
  h_nfatjets_CR->Add(h_nfatjets_QCD_HT1000to1500_CR);
  h_nfatjets_CR->Add(h_nfatjets_QCD_HT1500to2000_CR);

//////////////////////////////////////////////////////////////
///////////h_nAK4//////////////////////
  TH1I *h_nAK4_CR = new TH1I(*h_nAK4_QCD_HT2000toInf_CR);
  h_nAK4_CR->Add(h_nAK4_QCD_HT1000to1500_CR);
  h_nAK4_CR->Add(h_nAK4_QCD_HT1500to2000_CR);


////////////////////combine data//////////////////////////////

  TH1I *h_SJ_nAK4_100_data_CR = new TH1I(*h_SJ_nAK4_100_CR_2018A);
  h_SJ_nAK4_100_data_CR->Add(h_SJ_nAK4_100_CR_2018B);
  h_SJ_nAK4_100_data_CR->Add(h_SJ_nAK4_100_CR_2018C);
  h_SJ_nAK4_100_data_CR->Add(h_SJ_nAK4_100_CR_2018D);

  TH1I *h_SJ_nAK4_200_data_CR = new TH1I(*h_SJ_nAK4_200_CR_2018A);
  h_SJ_nAK4_200_data_CR->Add(h_SJ_nAK4_200_CR_2018B);
  h_SJ_nAK4_200_data_CR->Add(h_SJ_nAK4_200_CR_2018C);
  h_SJ_nAK4_200_data_CR->Add(h_SJ_nAK4_200_CR_2018D);

  TH1F *h_SJ_mass_data_CR = new TH1F(*h_SJ_mass_CR_2018A);
  h_SJ_mass_data_CR->Add(h_SJ_mass_CR_2018B);
  h_SJ_mass_data_CR->Add(h_SJ_mass_CR_2018C);
  h_SJ_mass_data_CR->Add(h_SJ_mass_CR_2018D);

  TH1F *h_disuperjet_mass_data_CR = new TH1F(*h_disuperjet_mass_CR_2018A);
  h_disuperjet_mass_data_CR->Add(h_disuperjet_mass_CR_2018B);
  h_disuperjet_mass_data_CR->Add(h_disuperjet_mass_CR_2018C);
  h_disuperjet_mass_data_CR->Add(h_disuperjet_mass_CR_2018D);

  TH1F *h_AK8_jet_mass_data_CR = new TH1F(*h_AK8_jet_mass_2018A);
  h_AK8_jet_mass_data_CR->Add(h_AK8_jet_mass_2018B);
  h_AK8_jet_mass_data_CR->Add(h_AK8_jet_mass_2018C);
  h_AK8_jet_mass_data_CR->Add(h_AK8_jet_mass_2018D);

  TH1F *h_AK4_jet_mass_data_CR = new TH1F(*h_AK4_jet_mass_2018A);
  h_AK4_jet_mass_data_CR->Add(h_AK4_jet_mass_2018B);
  h_AK4_jet_mass_data_CR->Add(h_AK4_jet_mass_2018C);
  h_AK4_jet_mass_data_CR->Add(h_AK4_jet_mass_2018D);

  TH1F *h_totHT_data_CR = new TH1F(*h_totHT_CR_2018A);
  h_totHT_data_CR->Add(h_totHT_CR_2018B);
  h_totHT_data_CR->Add(h_totHT_CR_2018C);
  h_totHT_data_CR->Add(h_totHT_CR_2018D);

  TH1I *h_nfatjets_data_CR = new TH1I(*h_nfatjets_CR_2018A);
  h_nfatjets_data_CR->Add(h_nfatjets_CR_2018B);
  h_nfatjets_data_CR->Add(h_nfatjets_CR_2018C);
  h_nfatjets_data_CR->Add(h_nfatjets_CR_2018D);

  TH1I *h_nAK4_data_CR = new TH1I(*h_nAK4_CR_2018A);
  h_nAK4_data_CR->Add(h_nAK4_CR_2018B);
  h_nAK4_data_CR->Add(h_nAK4_CR_2018C);
  h_nAK4_data_CR->Add(h_nAK4_CR_2018D);


  TCanvas *c1 = new TCanvas("c1","",400,20, 1500,1500);

  std::cout << "do TH2" << std::endl;

  h_MSJ_mass_vs_MdSJ_CR_2018D->Divide(h_MSJ_mass_vs_MdSJ_CR);
  h_MSJ_mass_vs_MdSJ_CR_2018D->SetTitle("M_{SJ} vs M_{diSJ} Ratio (Events double-tagged, Data Control Region / Scaled QCD MC ); M_{diSJ};M_{SJ}");
  h_MSJ_mass_vs_MdSJ_CR_2018D->GetYaxis()->SetTitleOffset(1.35);
  h_MSJ_mass_vs_MdSJ_CR_2018D->GetYaxis()->SetLabelSize(0.015);
  h_MSJ_mass_vs_MdSJ_CR_2018D->Draw("colz");
  c1->SaveAs("mSJ_vs_mdiSJ_CR_DataMC_ratio_MC_DataMC.png"); 


  gPad->SetLogy();

  //gStyle->SetOptStat(0)



  std::cout << "do ratio plots" << std::endl;

/*
  auto rp_nAK4_all = new TRatioPlot(h_nAK4_data,h_nAK4);
  rp_nAK4_all->Draw("HIST,E");
  rp_nAK4_all->GetLowerRefYaxis()->SetTitle("Data / MC");
  rp_nAK4_all->GetLowerRefGraph()->SetMaximum(2.);
  rp_nAK4_all->GetUpperRefYaxis()->SetTitle("Events");
  c1->SaveAs("rp_nAK4_all_2018DMC.png");  

  auto rp_AK4_DeepJet_disc = new TRatioPlot(h_AK4_DeepJet_disc_data,h_AK4_DeepJet_disc);
  rp_AK4_DeepJet_disc->Draw("HIST,E");
  rp_AK4_DeepJet_disc->GetLowerRefYaxis()->SetTitle("Data / MC");
  rp_AK4_DeepJet_disc->GetLowerRefGraph()->SetMaximum(2.);
  rp_AK4_DeepJet_disc->GetUpperRefYaxis()->SetTitle("Events");
  c1->SaveAs("rp_AK4_DeepJet_disc_DataMC.png");  


  auto rp_nLooseBTags = new TRatioPlot(h_nLooseBTags_data,h_nLooseBTags);
  rp_nLooseBTags->Draw("HIST,E");
  rp_nLooseBTags->GetLowerRefYaxis()->SetTitle("Data / MC");
  rp_nLooseBTags->GetLowerRefGraph()->SetMaximum(2.);
  rp_nLooseBTags->GetUpperRefYaxis()->SetTitle("Events");
  c1->SaveAs("rp_nLooseBTags_DataMC.png");  

  auto rp_nMidBTags = new TRatioPlot(h_nMidBTags_data,h_nMidBTags);
  rp_nMidBTags->Draw("HIST,E");
  rp_nMidBTags->GetLowerRefYaxis()->SetTitle("Data / MC");
  rp_nMidBTags->GetLowerRefGraph()->SetMaximum(2.);
  rp_nMidBTags->GetUpperRefYaxis()->SetTitle("Events");
  c1->SaveAs("rp_nMidBTags_DataMC.png");  

  auto rp_nTightBTags = new TRatioPlot(h_nTightBTags_data,h_nTightBTags);
  rp_nTightBTags->Draw("HIST,E");
  rp_nTightBTags->GetLowerRefYaxis()->SetTitle("Data / MC");
  rp_nTightBTags->GetLowerRefGraph()->SetMaximum(2.);
  rp_nTightBTags->GetUpperRefYaxis()->SetTitle("Events");
  c1->SaveAs("rp_nTightBTags_DataMC.png");  


  std::cout << "nEvents data/MC = " << h_totHT_All_2018D->Integral() << "/" << h_totHT_All->Integral() << std::endl;
  auto rp_totHT_All = new TRatioPlot(h_totHT_All_2018D,h_totHT_All);
  rp_totHT_All->Draw("HIST,E");
  rp_totHT_All->GetLowerRefYaxis()->SetTitle("Data / MC");
  rp_totHT_All->GetLowerRefGraph()->SetMaximum(2.);
  rp_totHT_All->GetUpperRefYaxis()->SetTitle("Events");
  c1->SaveAs("rp_totHT_All_2018DMC.png");  

*/
  //std::cout << "Number of events: " << h_SJ_nAK4_100_CR->GetEntries() << "/" << h_SJ_nAK4_100_DT->GetEntries() <<std::endl;
  auto rp_SJ_nAK4_100 = new TRatioPlot(h_SJ_nAK4_100_data_CR,h_SJ_nAK4_100_CR);
  rp_SJ_nAK4_100->Draw("HIST,E");
  rp_SJ_nAK4_100->GetLowerRefYaxis()->SetTitle("CR Data / CR MC");
  rp_SJ_nAK4_100->GetLowerRefGraph()->SetMaximum(2.);
  rp_SJ_nAK4_100->GetUpperRefYaxis()->SetTitle("Events");
  c1->SaveAs("rp_DataMC_SJ_nAK4_100_DataMC.png");  


  auto rp_SJ_nAK4_200 = new TRatioPlot(h_SJ_nAK4_200_data_CR,h_SJ_nAK4_200_CR);
  rp_SJ_nAK4_200->Draw("HIST,E");
  rp_SJ_nAK4_200->GetLowerRefYaxis()->SetTitle("CR Data / CR MC");
  rp_SJ_nAK4_200->GetLowerRefGraph()->SetMaximum(2.);
  rp_SJ_nAK4_200->GetUpperRefYaxis()->SetTitle("Events");
  c1->SaveAs("rp_DataMC_SJ_nAK4_200_DataMC.png"); 

  auto rp_SJ_mass = new TRatioPlot(h_SJ_mass_data_CR,h_SJ_mass_CR);
  rp_SJ_mass->Draw("HIST,E");
  rp_SJ_mass->GetLowerRefYaxis()->SetTitle("CR Data / CR MC");
  rp_SJ_mass->GetLowerRefGraph()->SetMaximum(2.);
  rp_SJ_mass->GetUpperRefYaxis()->SetTitle("Events");
  c1->SaveAs("rp_DataMC_SJ_mass_2018DMC.png"); 

  auto rp_disuperjet_mass = new TRatioPlot(h_disuperjet_mass_data_CR,h_disuperjet_mass_CR);
  rp_disuperjet_mass->Draw("HIST,E");
  rp_disuperjet_mass->GetLowerRefYaxis()->SetTitle("CR Data / CR MC");
  rp_disuperjet_mass->GetLowerRefGraph()->SetMaximum(2.);
  rp_disuperjet_mass->GetUpperRefYaxis()->SetTitle("Events");
  c1->SaveAs("rp_DataMC_disuperjet_mass_2018DMC.png"); 

  auto rp_AK8_jet_mass = new TRatioPlot(h_AK8_jet_mass_data_CR,h_AK8_jet_mass_CR);
  rp_AK8_jet_mass->Draw("HIST,E");
  rp_AK8_jet_mass->GetLowerRefYaxis()->SetTitle("CR Data / CR MC");
  rp_AK8_jet_mass->GetLowerRefGraph()->SetMaximum(2.);
  rp_AK8_jet_mass->GetUpperRefYaxis()->SetTitle("Events");
  c1->SaveAs("rp_DataMC_AK8_jet_mass_2018DMC.png"); 


  auto rp_AK4_jet_mass = new TRatioPlot(h_AK4_jet_mass_data_CR,h_AK4_jet_mass_CR);
  rp_AK4_jet_mass->Draw("HIST,E");
  rp_AK4_jet_mass->GetLowerRefYaxis()->SetTitle("CR Data / CR MC");
  rp_AK4_jet_mass->GetLowerRefGraph()->SetMaximum(2.);
  rp_AK4_jet_mass->GetUpperRefYaxis()->SetTitle("Events");
  c1->SaveAs("rp_DataMC_AK4_jet_mass_2018DMC.png"); 

  auto rp_totHT = new TRatioPlot(h_totHT_data_CR,h_totHT_CR);
  rp_totHT->Draw("HIST,E");
  rp_totHT->GetLowerRefYaxis()->SetTitle("CR Data / CR MC");
  rp_totHT->GetLowerRefGraph()->SetMaximum(2.);
  rp_totHT->GetUpperRefYaxis()->SetTitle("Events");
  c1->SaveAs("rp_DataMC_totHT_DataMC.png"); 


  auto rp_nfatjets = new TRatioPlot(h_nfatjets_data_CR,h_nfatjets_CR);
  rp_nfatjets->Draw("HIST,E");
  rp_nfatjets->GetLowerRefYaxis()->SetTitle("CR Data / CR MC");
  rp_nfatjets->GetLowerRefGraph()->SetMaximum(2.);
  rp_nfatjets->GetUpperRefYaxis()->SetTitle("Events");
  c1->SaveAs("rp_DataMC_nfatjets_DataMC.png"); 

  auto rp_nAK4 = new TRatioPlot(h_nAK4_data_CR,h_nAK4_CR);
  rp_nAK4->Draw("HIST,E");
  rp_nAK4->GetLowerRefYaxis()->SetTitle("CR Data / CR MC");
  rp_nAK4->GetLowerRefGraph()->SetMaximum(2.);
  rp_nAK4->GetUpperRefYaxis()->SetTitle("Events");
  c1->SaveAs("rp_DataMC_nAK4_DataMC.png"); 


}


 //read out TTree output from here, try to find if all event numbers are actually there

 //VIM: 3GNAXBEX9KS572173
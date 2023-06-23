#include <iostream>
#include <string>
#include "TLorentzVector.h"
#include "TRatioPlot.h"
#include "THStack.h"
using namespace std;

void makeCRComparisonPlots()
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

  bool includeTTBar = false;
  bool includeAllHTBins = false;
  //double h_TTJets2500toInf_SF  = 0.00008408965681;

  std::cout << "Open Files" << std::endl;

  TFile *f3 = new TFile("/home/ethan/Documents/QCD_HT2000toInf_processed_TEST_NOBTSF2018.root"); 

/*
   TH1F* h_AK8_jet_mass_DT  = new TH1F("h_AK8_jet_mass_DT","AK8 Jet Mass (DT region);Mass [GeV]; Events / 30 5GeV",50,0.,1500);
   TH1F* h_AK8_jet_mass_CR  = new TH1F("h_AK8_jet_mass_CR","AK8 Jet Mass (CR);Mass [GeV]; Events / 30 GeV",50,0.,1500);

   TH1F* h_AK4_jet_mass_DT  = new TH1F("h_AK4_jet_mass_DT","AK4 Jet Mass (DT region);Mass [GeV]; Events / 25 GeV",40,0.,1000);
   TH1F* h_AK4_jet_mass_CR  = new TH1F("h_AK4_jet_mass_CR","AK4 Jet Mass (CR);Mass [GeV]; Events / 25 GeV",40,0.,1000);

   TH1F* h_totHT_DT  = new TH1F("h_totHT_DT","Event H_{T} (DT region);H_{T} [GeV]; Events / 200 5GeV",50,0.,10000);
   TH1F* h_totHT_CR  = new TH1F("h_totHT_CR","Event H_{T}} (CR);H_{T} [GeV]; Events / 200 GeV",50,0.,10000);

   TH1I* h_nfatjets_DT = new TH1I("h_nfatjets_DT","Number of AK8 Jets (E_{T} > 300 GeV per Event ;nAK8 Jets; Events",10,-0.5,9.5);
   TH1I* h_nfatjets_CR = new TH1I("h_nfatjets_CR","Number of AK8 Jets (E_{T} > 300 GeV per Event ;nAK8 Jets; Events",10,-0.5,9.5);

   TH1I* h_nAK4_DT = new TH1I("h_nAK4_DT","Number of AK4 Jets (E_{T} > 30 GeV per Event ;nAK8 Jets; Events",30,-0.5,29.5);
   TH1I* h_nAK4_CR = new TH1I("h_nAK4_CR","Number of AK4 Jets (E_{T} > 30 GeV per Event ;nAK8 Jets; Events",30,-0.5,29.5);
*/

  
  //create histogramas for each of the different plots for different HT levels, scale histograms, add together histograms, normalize, do division/ comparison
  std::cout << "Get histograms" << std::endl;

////////////////////////////////////// 2000toInf /////////////////////////////////////////

  TH1I *h_SJ_nAK4_100_DT_HT2000toInf =      (TH1I*)f3->Get("h_SJ_nAK4_100_DT");
  TH1I *h_SJ_nAK4_200_DT_HT2000toInf =      (TH1I*)f3->Get("h_SJ_nAK4_200_DT");
  TH1F *h_SJ_mass_DT_HT2000toInf =          (TH1F*)f3->Get("h_SJ_mass_DT");
  TH1F *h_disuperjet_mass_DT_HT2000toInf =  (TH1F*)f3->Get("h_disuperjet_mass_DT");
  TH2F *h_MSJ_mass_vs_MdSJ_DT_HT2000toInf = (TH2F*)f3->Get("h_MSJ_mass_vs_MdSJ_DT");

  TH1I *h_SJ_nAK4_100_CR_HT2000toInf =      (TH1I*)f3->Get("h_SJ_nAK4_100_CR");
  TH1I *h_SJ_nAK4_200_CR_HT2000toInf =      (TH1I*)f3->Get("h_SJ_nAK4_200_CR");
  TH1F *h_SJ_mass_CR_HT2000toInf =          (TH1F*)f3->Get("h_SJ_mass_CR");
  TH1F *h_disuperjet_mass_CR_HT2000toInf =  (TH1F*)f3->Get("h_disuperjet_mass_CR");
  TH2F *h_MSJ_mass_vs_MdSJ_CR_HT2000toInf = (TH2F*)f3->Get("h_MSJ_mass_vs_MdSJ_CR");

  TH1F* h_AK8_jet_mass_QCD_HT2000toInf_CR    =      (TH1F*)f3->Get("h_AK8_jet_mass_CR");
  TH1F* h_AK4_jet_mass_QCD_HT2000toInf_CR    =      (TH1F*)f3->Get("h_AK4_jet_mass_CR");
  TH1F* h_totHT_QCD_HT2000toInf_CR           =      (TH1F*)f3->Get("h_totHT_CR");
  TH1I* h_nfatjets_QCD_HT2000toInf_CR        =      (TH1I*)f3->Get("h_nfatjets_CR");
  TH1I* h_nAK4_QCD_HT2000toInf_CR            =      (TH1I*)f3->Get("h_nAK4_CR");

  TH1F* h_AK8_jet_mass_QCD_HT2000toInf_DT    =      (TH1F*)f3->Get("h_AK8_jet_mass_DT");
  TH1F* h_AK4_jet_mass_QCD_HT2000toInf_DT    =      (TH1F*)f3->Get("h_AK4_jet_mass_DT");
  TH1F* h_totHT_QCD_HT2000toInf_DT           =      (TH1F*)f3->Get("h_totHT_DT");
  TH1I* h_nfatjets_QCD_HT2000toInf_DT        =      (TH1I*)f3->Get("h_nfatjets_DT");
  TH1I* h_nAK4_QCD_HT2000toInf_DT            =      (TH1I*)f3->Get("h_nAK4_DT");


  
  std::cout << "Scale histograms 1" << std::endl;


  h_SJ_nAK4_100_CR_HT2000toInf->Scale(QCD_HT2000toInf_SF);
  h_SJ_nAK4_200_CR_HT2000toInf->Scale(QCD_HT2000toInf_SF);
  h_SJ_mass_CR_HT2000toInf->Scale(QCD_HT2000toInf_SF);
  h_disuperjet_mass_CR_HT2000toInf->Scale(QCD_HT2000toInf_SF);
  h_MSJ_mass_vs_MdSJ_CR_HT2000toInf->Scale(QCD_HT2000toInf_SF);
  h_SJ_nAK4_100_DT_HT2000toInf->Scale(QCD_HT2000toInf_SF);
  h_SJ_nAK4_200_DT_HT2000toInf->Scale(QCD_HT2000toInf_SF);
  h_SJ_mass_DT_HT2000toInf->Scale(QCD_HT2000toInf_SF);
  h_disuperjet_mass_DT_HT2000toInf->Scale(QCD_HT2000toInf_SF);
  h_MSJ_mass_vs_MdSJ_DT_HT2000toInf->Scale(QCD_HT2000toInf_SF);
  h_AK8_jet_mass_QCD_HT2000toInf_CR->Scale(QCD_HT2000toInf_SF);
  h_AK4_jet_mass_QCD_HT2000toInf_CR->Scale(QCD_HT2000toInf_SF);
  h_totHT_QCD_HT2000toInf_CR->Scale(QCD_HT2000toInf_SF);
  h_nfatjets_QCD_HT2000toInf_CR->Scale(QCD_HT2000toInf_SF);
  h_nAK4_QCD_HT2000toInf_CR->Scale(QCD_HT2000toInf_SF);
  h_AK8_jet_mass_QCD_HT2000toInf_DT->Scale(QCD_HT2000toInf_SF);
  h_AK4_jet_mass_QCD_HT2000toInf_DT->Scale(QCD_HT2000toInf_SF);
  h_totHT_QCD_HT2000toInf_DT->Scale(QCD_HT2000toInf_SF);
  h_nfatjets_QCD_HT2000toInf_DT->Scale(QCD_HT2000toInf_SF);
  h_nAK4_QCD_HT2000toInf_DT->Scale(QCD_HT2000toInf_SF);






////////////////////////////////////////////////////////////////////////////////////////////////////////

  std::cout << "Add and scale histograms" << std::endl;

  ////////////nAK4_100//////////////

  TH1I *h_SJ_nAK4_100_CR = new TH1I(*h_SJ_nAK4_100_CR_HT2000toInf);
  h_SJ_nAK4_100_CR->Scale(1000000./h_SJ_nAK4_100_CR->Integral());
  std::cout << "Integral-h_SJ_nAK4_100_CR " <<  h_SJ_nAK4_100_CR->Integral() <<std::endl;

  TH1 *h_SJ_nAK4_100_DT = new TH1I(*h_SJ_nAK4_100_DT_HT2000toInf);
  h_SJ_nAK4_100_DT->Scale(1000000./h_SJ_nAK4_100_DT->Integral());
  std::cout << "Integral-h_SJ_nAK4_100_DT " <<  h_SJ_nAK4_100_DT->Integral() <<std::endl;
  h_SJ_nAK4_100_CR->SetFillColor(kRed);
  h_SJ_nAK4_100_DT->SetFillColor(kBlue);

//////////////////////////////////////////////////////////
  ////////////nAK4_200//////////////

  TH1I *h_SJ_nAK4_200_CR = new TH1I(*h_SJ_nAK4_200_CR_HT2000toInf);
  h_SJ_nAK4_200_CR->Scale(1000000/h_SJ_nAK4_200_CR->Integral());
  std::cout << "Integral-h_SJ_nAK4_200_CR " <<  h_SJ_nAK4_200_CR->Integral() <<std::endl;

  TH1I *h_SJ_nAK4_200_DT = new TH1I(*h_SJ_nAK4_200_DT_HT2000toInf);
  h_SJ_nAK4_200_DT->Scale(1000000/h_SJ_nAK4_200_DT->Integral());
  std::cout << "Integral-h_SJ_nAK4_200_DT " <<  h_SJ_nAK4_200_DT->Integral() <<std::endl;
  h_SJ_nAK4_200_CR->SetFillColor(kRed);
  h_SJ_nAK4_200_DT->SetFillColor(kBlue);


///////////////////////////////////////////////////////////
///////////h_SJ_mass//////////////////////
  TH1F *h_SJ_mass_CR = new TH1F(*h_SJ_mass_CR_HT2000toInf);
  h_SJ_mass_CR->Scale(1./h_SJ_mass_CR->Integral());
  std::cout << "Integral-h_SJ_mass_CR " <<  h_SJ_mass_CR->Integral() <<std::endl;

  TH1F *h_SJ_mass_DT = new TH1F(*h_SJ_mass_DT_HT2000toInf);
  h_SJ_mass_DT->Scale(1./h_SJ_mass_DT->Integral());
  std::cout << "Integral-h_SJ_mass_DT " <<  h_SJ_mass_DT->Integral() <<std::endl;

  h_SJ_mass_CR->SetFillColor(kRed);
  h_SJ_mass_DT->SetFillColor(kBlue);

///////////////////////////////////////////////////////////
///////////h_disuperjet_mass//////////////////////
  TH1F *h_disuperjet_mass_CR = new TH1F(*h_disuperjet_mass_CR_HT2000toInf);
  h_disuperjet_mass_CR->Scale(1./h_disuperjet_mass_CR->Integral());
  std::cout << "Integral-h_disuperjet_mass_CR " <<  h_disuperjet_mass_CR->Integral() <<std::endl;

  TH1F *h_disuperjet_mass_DT = new TH1F(*h_disuperjet_mass_DT_HT2000toInf);
  h_disuperjet_mass_DT->Scale(1./h_disuperjet_mass_DT->Integral());
  std::cout << "Integral-h_disuperjet_mass_DT " <<  h_disuperjet_mass_DT->Integral() <<std::endl;

  h_disuperjet_mass_CR->SetFillColor(kRed);
  h_disuperjet_mass_DT->SetFillColor(kBlue);

///////////////////////////////////////////////////////////
///////////h_disuperjet_mass//////////////////////
  TH2F *h_MSJ_mass_vs_MdSJ_CR = new TH2F(*h_MSJ_mass_vs_MdSJ_CR_HT2000toInf);
  h_MSJ_mass_vs_MdSJ_CR->Scale(1000000/h_MSJ_mass_vs_MdSJ_CR->Integral());
  std::cout << "Integral-h_MSJ_mass_vs_MdSJ_CR " <<  h_MSJ_mass_vs_MdSJ_CR->Integral() <<std::endl;

  TH2F *h_MSJ_mass_vs_MdSJ_DT = new TH2F(*h_MSJ_mass_vs_MdSJ_DT_HT2000toInf);
  h_MSJ_mass_vs_MdSJ_DT->Scale(1000000/h_MSJ_mass_vs_MdSJ_DT->Integral());
  std::cout << "Integral-h_MSJ_mass_vs_MdSJ_DT " <<  h_MSJ_mass_vs_MdSJ_DT->Integral() <<std::endl;


///////////////////////////////////////////////////////////
///////////h_AK8_jet_mass//////////////////////
  TH1F *h_AK8_jet_mass_CR = new TH1F(*h_AK8_jet_mass_QCD_HT2000toInf_CR);
  h_AK8_jet_mass_CR->Scale(1000000/h_AK8_jet_mass_CR->Integral());

  TH1F *h_AK8_jet_mass_DT = new TH1F(*h_AK8_jet_mass_QCD_HT2000toInf_DT);
  h_AK8_jet_mass_DT->Scale(1000000/h_AK8_jet_mass_DT->Integral());



///////////////////////////////////////////////////////////////////
///////////h_AK4_jet_mass//////////////////////
  TH1F *h_AK4_jet_mass_CR = new TH1F(*h_AK4_jet_mass_QCD_HT2000toInf_CR);
  h_AK4_jet_mass_CR->Scale(1000000/h_AK4_jet_mass_CR->Integral());

  TH1F *h_AK4_jet_mass_DT = new TH1F(*h_AK4_jet_mass_QCD_HT2000toInf_DT);
  h_AK4_jet_mass_DT->Scale(1000000/h_AK4_jet_mass_DT->Integral());


///////////////////////////////////////////////////////////////////
///////////h_totHT//////////////////////
  TH1F *h_totHT_CR = new TH1F(*h_totHT_QCD_HT2000toInf_CR);
  h_totHT_CR->Scale(1000000/h_totHT_CR->Integral());

  TH1F *h_totHT_DT = new TH1F(*h_totHT_QCD_HT2000toInf_DT);
  h_totHT_DT->Scale(1000000/h_totHT_DT->Integral());


///////////////////////////////////////////////////////////////////
///////////h_nfatjets//////////////////////
  TH1I *h_nfatjets_CR = new TH1I(*h_nfatjets_QCD_HT2000toInf_CR);
  std::cout << "Total number of events in control region: " << h_nfatjets_CR->Integral() << std::endl;
  h_nfatjets_CR->Scale(1000000/h_nfatjets_CR->Integral());

  TH1I *h_nfatjets_DT = new TH1I(*h_nfatjets_QCD_HT2000toInf_DT);
  h_nfatjets_DT->Scale(1000000/h_nfatjets_DT->Integral());

///////////////////////////////////////////////////////////////////
///////////h_nAK4//////////////////////
  TH1I *h_nAK4_CR = new TH1I(*h_nAK4_QCD_HT2000toInf_CR);
  h_nAK4_CR->Scale(1000000/h_nAK4_CR->Integral());

  TH1I *h_nAK4_DT = new TH1I(*h_nAK4_QCD_HT2000toInf_DT);
  h_nAK4_DT->Scale(1000000/h_nAK4_DT->Integral());


  TH1I *h_SJ_nLooseBtag_HT2000toInf  =      (TH1I*)f3->Get("h_nLooseBTags");
  h_SJ_nLooseBtag_HT2000toInf->Scale();

  TH1I *h_SJ_nLooseBtag = new TH1I(*h_SJ_nLooseBtag_HT2000toInf);


  /// other HT bin stuff
  if(includeAllHTBins)
  {
    TFile *f1 = new TFile("/home/ethan/Documents/QCD_HT1000to1500_combined_cutbased_processed.root");   //need to add these two together
    TFile *f2 = new TFile("/home/ethan/Documents/QCD_HT1500to2000_combined_cutbased_processed.root");   

    ///////////////////////////////1000to1500//////////////////////////////////
    TH1I *h_SJ_nAK4_100_CR_HT1000to1500 =      (TH1I*)f1->Get("h_SJ_nAK4_100_CR");
    TH1I *h_SJ_nAK4_200_CR_HT1000to1500 =      (TH1I*)f1->Get("h_SJ_nAK4_200_CR");
    TH1F *h_SJ_mass_CR_HT1000to1500 =          (TH1F*)f1->Get("h_SJ_mass_CR");
    TH1F *h_disuperjet_mass_CR_HT1000to1500 =  (TH1F*)f1->Get("h_disuperjet_mass_CR");
    TH2F *h_MSJ_mass_vs_MdSJ_CR_HT1000to1500 = (TH2F*)f1->Get("h_MSJ_mass_vs_MdSJ_CR");

    TH1I *h_SJ_nAK4_100_DT_HT1000to1500 =      (TH1I*)f1->Get("h_SJ_nAK4_100_DT");
    TH1I *h_SJ_nAK4_200_DT_HT1000to1500 =      (TH1I*)f1->Get("h_SJ_nAK4_200_DT");
    TH1F *h_SJ_mass_DT_HT1000to1500 =          (TH1F*)f1->Get("h_SJ_mass_DT");
    TH1F *h_disuperjet_mass_DT_HT1000to1500 =  (TH1F*)f1->Get("h_disuperjet_mass_DT");
    TH2F *h_MSJ_mass_vs_MdSJ_DT_HT1000to1500 = (TH2F*)f1->Get("h_MSJ_mass_vs_MdSJ_DT");

    TH1F* h_AK8_jet_mass_QCD_HT1000to1500_CR    =      (TH1F*)f1->Get("h_AK8_jet_mass_CR");
    TH1F* h_AK4_jet_mass_QCD_HT1000to1500_CR    =      (TH1F*)f1->Get("h_AK4_jet_mass_CR");
    TH1F* h_totHT_QCD_HT1000to1500_CR           =      (TH1F*)f1->Get("h_totHT_CR");
    TH1I* h_nfatjets_QCD_HT1000to1500_CR        =      (TH1I*)f1->Get("h_nfatjets_CR");
    TH1I* h_nAK4_QCD_HT1000to1500_CR            =      (TH1I*)f1->Get("h_nAK4_CR");

    TH1F* h_AK8_jet_mass_QCD_HT1000to1500_DT    =      (TH1F*)f1->Get("h_AK8_jet_mass_DT");
    TH1F* h_AK4_jet_mass_QCD_HT1000to1500_DT    =      (TH1F*)f1->Get("h_AK4_jet_mass_DT");
    TH1F* h_totHT_QCD_HT1000to1500_DT           =      (TH1F*)f1->Get("h_totHT_DT");
    TH1I* h_nfatjets_QCD_HT1000to1500_DT        =      (TH1I*)f1->Get("h_nfatjets_DT");
    TH1I* h_nAK4_QCD_HT1000to1500_DT            =      (TH1I*)f1->Get("h_nAK4_DT");
  ////////////////////////////////////// 1500to2000 /////////////////////////////////////////
    TH1I *h_SJ_nAK4_100_CR_HT1500to2000 =      (TH1I*)f2->Get("h_SJ_nAK4_100_CR");
    TH1I *h_SJ_nAK4_200_CR_HT1500to2000 =      (TH1I*)f2->Get("h_SJ_nAK4_200_CR");
    TH1F *h_SJ_mass_CR_HT1500to2000 =          (TH1F*)f2->Get("h_SJ_mass_CR");
    TH1F *h_disuperjet_mass_CR_HT1500to2000 =  (TH1F*)f2->Get("h_disuperjet_mass_CR");
    TH2F *h_MSJ_mass_vs_MdSJ_CR_HT1500to2000 = (TH2F*)f2->Get("h_MSJ_mass_vs_MdSJ_CR");

    TH1I *h_SJ_nAK4_100_DT_HT1500to2000 =      (TH1I*)f2->Get("h_SJ_nAK4_100_DT");
    TH1I *h_SJ_nAK4_200_DT_HT1500to2000 =      (TH1I*)f2->Get("h_SJ_nAK4_200_DT");
    TH1F *h_SJ_mass_DT_HT1500to2000 =          (TH1F*)f2->Get("h_SJ_mass_DT");
    TH1F *h_disuperjet_mass_DT_HT1500to2000 =  (TH1F*)f2->Get("h_disuperjet_mass_DT");
    TH2F *h_MSJ_mass_vs_MdSJ_DT_HT1500to2000 = (TH2F*)f2->Get("h_MSJ_mass_vs_MdSJ_DT");

    TH1F* h_AK8_jet_mass_QCD_HT1500to2000_CR    =      (TH1F*)f2->Get("h_AK8_jet_mass_CR");
    TH1F* h_AK4_jet_mass_QCD_HT1500to2000_CR    =      (TH1F*)f2->Get("h_AK4_jet_mass_CR");
    TH1F* h_totHT_QCD_HT1500to2000_CR           =      (TH1F*)f2->Get("h_totHT_CR");
    TH1I* h_nfatjets_QCD_HT1500to2000_CR        =      (TH1I*)f2->Get("h_nfatjets_CR");
    TH1I* h_nAK4_QCD_HT1500to2000_CR            =      (TH1I*)f2->Get("h_nAK4_CR");

    TH1F* h_AK8_jet_mass_QCD_HT1500to2000_DT    =      (TH1F*)f2->Get("h_AK8_jet_mass_DT");
    TH1F* h_AK4_jet_mass_QCD_HT1500to2000_DT    =      (TH1F*)f2->Get("h_AK4_jet_mass_DT");
    TH1F* h_totHT_QCD_HT1500to2000_DT           =      (TH1F*)f2->Get("h_totHT_DT");
    TH1I* h_nfatjets_QCD_HT1500to2000_DT        =      (TH1I*)f2->Get("h_nfatjets_DT");
    TH1I* h_nAK4_QCD_HT1500to2000_DT            =      (TH1I*)f2->Get("h_nAK4_DT"); 

    h_SJ_nAK4_100_CR_HT1000to1500->Scale(QCD_HT1000to1500_SF);
    h_SJ_nAK4_200_CR_HT1000to1500->Scale(QCD_HT1000to1500_SF);
    h_SJ_mass_CR_HT1000to1500->Scale(QCD_HT1000to1500_SF);
    h_disuperjet_mass_CR_HT1000to1500->Scale(QCD_HT1000to1500_SF);
    h_MSJ_mass_vs_MdSJ_CR_HT1000to1500->Scale(QCD_HT1000to1500_SF);
    h_SJ_nAK4_100_DT_HT1000to1500->Scale(QCD_HT1000to1500_SF);
    h_SJ_nAK4_200_DT_HT1000to1500->Scale(QCD_HT1000to1500_SF);
    h_SJ_mass_DT_HT1000to1500->Scale(QCD_HT1000to1500_SF);
    h_disuperjet_mass_DT_HT1000to1500->Scale(QCD_HT1000to1500_SF);
    h_MSJ_mass_vs_MdSJ_DT_HT1000to1500->Scale(QCD_HT1000to1500_SF);
    h_AK8_jet_mass_QCD_HT1000to1500_CR->Scale(QCD_HT1000to1500_SF);
    h_AK4_jet_mass_QCD_HT1000to1500_CR->Scale(QCD_HT1000to1500_SF);
    h_totHT_QCD_HT1000to1500_CR->Scale(QCD_HT1000to1500_SF);
    h_nfatjets_QCD_HT1000to1500_CR->Scale(QCD_HT1000to1500_SF);
    h_nAK4_QCD_HT1000to1500_CR->Scale(QCD_HT1000to1500_SF);
    h_AK8_jet_mass_QCD_HT1000to1500_DT->Scale(QCD_HT1000to1500_SF);
    h_AK4_jet_mass_QCD_HT1000to1500_DT->Scale(QCD_HT1000to1500_SF);
    h_totHT_QCD_HT1000to1500_DT->Scale(QCD_HT1000to1500_SF);
    h_nfatjets_QCD_HT1000to1500_DT->Scale(QCD_HT1000to1500_SF);
    h_nAK4_QCD_HT1000to1500_DT->Scale(QCD_HT1000to1500_SF);

    h_SJ_nAK4_100_CR_HT1500to2000->Scale(QCD_HT1500to2000_SF);
    h_SJ_nAK4_200_CR_HT1500to2000->Scale(QCD_HT1500to2000_SF);
    h_SJ_mass_CR_HT1500to2000->Scale(QCD_HT1500to2000_SF);
    h_disuperjet_mass_CR_HT1500to2000->Scale(QCD_HT1500to2000_SF);
    h_MSJ_mass_vs_MdSJ_CR_HT1500to2000->Scale(QCD_HT1500to2000_SF);
    h_SJ_nAK4_100_DT_HT1500to2000->Scale(QCD_HT1500to2000_SF);
    h_SJ_nAK4_200_DT_HT1500to2000->Scale(QCD_HT1500to2000_SF);
    h_SJ_mass_DT_HT1500to2000->Scale(QCD_HT1500to2000_SF);
    h_disuperjet_mass_DT_HT1500to2000->Scale(QCD_HT1500to2000_SF);
    h_MSJ_mass_vs_MdSJ_DT_HT1500to2000->Scale(QCD_HT1500to2000_SF);
    h_AK8_jet_mass_QCD_HT1500to2000_CR->Scale(QCD_HT1500to2000_SF);
    h_AK4_jet_mass_QCD_HT1500to2000_CR->Scale(QCD_HT1500to2000_SF);
    h_totHT_QCD_HT1500to2000_CR->Scale(QCD_HT1500to2000_SF);
    h_nfatjets_QCD_HT1500to2000_CR->Scale(QCD_HT1500to2000_SF);
    h_nAK4_QCD_HT1500to2000_CR->Scale(QCD_HT1500to2000_SF);
    h_AK8_jet_mass_QCD_HT1500to2000_DT->Scale(QCD_HT1500to2000_SF);
    h_AK4_jet_mass_QCD_HT1500to2000_DT->Scale(QCD_HT1500to2000_SF);
    h_totHT_QCD_HT1500to2000_DT->Scale(QCD_HT1500to2000_SF);
    h_nfatjets_QCD_HT1500to2000_DT->Scale(QCD_HT1500to2000_SF);
    h_nAK4_QCD_HT1500to2000_DT->Scale(QCD_HT1500to2000_SF);

    h_SJ_nAK4_100_CR->Add(h_SJ_nAK4_100_CR_HT1500to2000);
    h_SJ_nAK4_100_CR->Add(h_SJ_nAK4_100_CR_HT1000to1500);
    h_SJ_nAK4_100_CR->Scale(1000000./h_SJ_nAK4_100_CR->Integral());

    h_SJ_nAK4_100_DT->Add(h_SJ_nAK4_100_DT_HT1000to1500);
    h_SJ_nAK4_100_DT->Add(h_SJ_nAK4_100_DT_HT1500to2000);
    h_SJ_nAK4_100_DT->Scale(1000000./h_SJ_nAK4_100_DT->Integral());

    h_SJ_nAK4_200_CR->Add(h_SJ_nAK4_200_CR_HT1000to1500);
    h_SJ_nAK4_200_CR->Add(h_SJ_nAK4_200_CR_HT1500to2000);
    h_SJ_nAK4_200_CR->Scale(1000000/h_SJ_nAK4_200_CR->Integral());

    h_SJ_nAK4_200_DT->Add(h_SJ_nAK4_200_DT_HT1000to1500);
    h_SJ_nAK4_200_DT->Add(h_SJ_nAK4_200_DT_HT1500to2000);
    h_SJ_nAK4_200_DT->Scale(1000000/h_SJ_nAK4_200_DT->Integral());

    h_SJ_mass_CR->Add(h_SJ_mass_CR_HT1000to1500);
    h_SJ_mass_CR->Add(h_SJ_mass_CR_HT1500to2000);
    h_SJ_mass_CR->Scale(1./h_SJ_mass_CR->Integral());

    h_SJ_mass_DT->Add(h_SJ_mass_DT_HT1000to1500);
    h_SJ_mass_DT->Add(h_SJ_mass_DT_HT1500to2000);
    h_SJ_mass_DT->Scale(1./h_SJ_mass_DT->Integral());

    h_disuperjet_mass_CR->Add(h_disuperjet_mass_CR_HT1000to1500);
    h_disuperjet_mass_CR->Add(h_disuperjet_mass_CR_HT1500to2000);
    h_disuperjet_mass_CR->Scale(1./h_disuperjet_mass_CR->Integral());

    h_disuperjet_mass_DT->Add(h_disuperjet_mass_DT_HT1000to1500);
    h_disuperjet_mass_DT->Add(h_disuperjet_mass_DT_HT1500to2000);
    h_disuperjet_mass_DT->Scale(1./h_disuperjet_mass_DT->Integral());


    h_MSJ_mass_vs_MdSJ_CR->Add(h_MSJ_mass_vs_MdSJ_CR_HT1000to1500);
    h_MSJ_mass_vs_MdSJ_CR->Add(h_MSJ_mass_vs_MdSJ_CR_HT1500to2000);
    h_MSJ_mass_vs_MdSJ_CR->Scale(1000000/h_MSJ_mass_vs_MdSJ_CR->Integral());


    h_MSJ_mass_vs_MdSJ_DT->Add(h_MSJ_mass_vs_MdSJ_DT_HT1000to1500);
    h_MSJ_mass_vs_MdSJ_DT->Add(h_MSJ_mass_vs_MdSJ_DT_HT1500to2000);
    h_MSJ_mass_vs_MdSJ_DT->Scale(1000000/h_MSJ_mass_vs_MdSJ_DT->Integral());

    h_AK8_jet_mass_CR->Add(h_AK8_jet_mass_QCD_HT1000to1500_CR);
    h_AK8_jet_mass_CR->Add(h_AK8_jet_mass_QCD_HT1500to2000_CR);
    h_AK8_jet_mass_CR->Scale(1000000/h_AK8_jet_mass_CR->Integral());

    h_AK8_jet_mass_DT->Add(h_AK8_jet_mass_QCD_HT1000to1500_DT);
    h_AK8_jet_mass_DT->Add(h_AK8_jet_mass_QCD_HT1500to2000_DT);
    h_AK8_jet_mass_DT->Scale(1000000/h_AK8_jet_mass_DT->Integral());

    h_AK4_jet_mass_CR->Add(h_AK4_jet_mass_QCD_HT1000to1500_CR);
    h_AK4_jet_mass_CR->Add(h_AK4_jet_mass_QCD_HT1500to2000_CR);
    h_AK4_jet_mass_CR->Scale(1000000/h_AK4_jet_mass_CR->Integral());

    h_AK4_jet_mass_DT->Add(h_AK4_jet_mass_QCD_HT1000to1500_DT);
    h_AK4_jet_mass_DT->Add(h_AK4_jet_mass_QCD_HT1500to2000_DT);
    h_AK4_jet_mass_DT->Scale(1000000/h_AK4_jet_mass_DT->Integral());

    h_totHT_CR->Add(h_totHT_QCD_HT1000to1500_CR);
    h_totHT_CR->Add(h_totHT_QCD_HT1500to2000_CR);
    h_totHT_CR->Scale(1000000/h_totHT_CR->Integral());

    h_totHT_DT->Add(h_totHT_QCD_HT1000to1500_DT);
    h_totHT_DT->Add(h_totHT_QCD_HT1500to2000_DT);
    h_totHT_DT->Scale(1000000/h_totHT_DT->Integral());


    h_nfatjets_CR->Add(h_nfatjets_QCD_HT1000to1500_CR);
    h_nfatjets_CR->Add(h_nfatjets_QCD_HT1500to2000_CR);
    h_nfatjets_CR->Scale(1000000/h_nfatjets_CR->Integral());

    h_nfatjets_DT->Add(h_nfatjets_QCD_HT1000to1500_DT);
    h_nfatjets_DT->Add(h_nfatjets_QCD_HT1500to2000_DT);
    h_nfatjets_DT->Scale(1000000/h_nfatjets_DT->Integral());

    h_nAK4_CR->Add(h_nAK4_QCD_HT1000to1500_CR);
    h_nAK4_CR->Add(h_nAK4_QCD_HT1500to2000_CR);
    h_nAK4_CR->Scale(1000000/h_nAK4_CR->Integral());

    h_nAK4_DT->Add(h_nAK4_QCD_HT1000to1500_DT);
    h_nAK4_DT->Add(h_nAK4_QCD_HT1500to2000_DT);
    h_nAK4_DT->Scale(1000000/h_nAK4_DT->Integral());

  std::cout << "Integral-h_SJ_nAK4_100_DT_HT1500to2000 (post scaling) " <<  h_SJ_nAK4_100_DT_HT1500to2000->Integral() <<std::endl;


    TH1I *h_SJ_nLooseBtag_HT1000to1500 =      (TH1I*)f1->Get("h_nLooseBTags");
    TH1I *h_SJ_nLooseBtag_HT1500to2000 =      (TH1I*)f2->Get("h_nLooseBTags");


    h_SJ_nLooseBtag_HT1000to1500->Scale();
    h_SJ_nLooseBtag_HT1500to2000->Scale();

    h_SJ_nLooseBtag->Add(h_SJ_nLooseBtag_HT1500to2000);
    h_SJ_nLooseBtag->Add(h_SJ_nLooseBtag_HT1000to1500);
  }


///////////////////////////////TTBar stuff /////////////////////////

  if(includeTTBar)
  {


  TFile *f4 = new TFile("/home/ethan/Documents/TTToHadronic_combined_cutbased_processed.root");  
  TFile *f5 = new TFile("/home/ethan/Documents/TTTo2l2nu_combine_cutbased_processed.root");   
  TFile *f6 = new TFile("/home/ethan/Documents/TTtoSemiLeptonic_combined_cutbased_processed.root");   
  ////////////////////////////////////// TTToSemiLeptonic /////////////////////////////////////////

  TH1I *h_SJ_nAK4_100_DT_TTToHadronic =      (TH1I*)f4->Get("h_SJ_nAK4_100_DT");
  TH1I *h_SJ_nAK4_200_DT_TTToHadronic =      (TH1I*)f4->Get("h_SJ_nAK4_200_DT");
  TH1F *h_SJ_mass_DT_TTToHadronic =          (TH1F*)f4->Get("h_SJ_mass_DT");
  TH1F *h_disuperjet_mass_DT_TTToHadronic =  (TH1F*)f4->Get("h_disuperjet_mass_DT");
  TH2F *h_MSJ_mass_vs_MdSJ_DT_TTToHadronic = (TH2F*)f4->Get("h_MSJ_mass_vs_MdSJ_DT");

  TH1I *h_SJ_nAK4_100_CR_TTToHadronic      =  (TH1I*)f4->Get("h_SJ_nAK4_100_CR");
  TH1I *h_SJ_nAK4_200_CR_TTToHadronic      =  (TH1I*)f4->Get("h_SJ_nAK4_200_CR");
  TH1F *h_SJ_mass_CR_TTToHadronic          =  (TH1F*)f4->Get("h_SJ_mass_CR");
  TH1F *h_disuperjet_mass_CR_TTToHadronic  =  (TH1F*)f4->Get("h_disuperjet_mass_CR");
  TH2F *h_MSJ_mass_vs_MdSJ_CR_TTToHadronic =  (TH2F*)f4->Get("h_MSJ_mass_vs_MdSJ_CR");

  TH1F* h_AK8_jet_mass_TTToHadronic_CR    =      (TH1F*)f4->Get("h_AK8_jet_mass_CR");
  TH1F* h_AK4_jet_mass_TTToHadronic_CR    =      (TH1F*)f4->Get("h_AK4_jet_mass_CR");
  TH1F* h_totHT_TTToHadronic_CR           =      (TH1F*)f4->Get("h_totHT_CR");
  TH1I* h_nfatjets_TTToHadronic_CR        =      (TH1I*)f4->Get("h_nfatjets_CR");
  TH1I* h_nAK4_TTToHadronic_CR            =      (TH1I*)f4->Get("h_nAK4_CR");

  TH1F* h_AK8_jet_mass_TTToHadronic_DT    =      (TH1F*)f4->Get("h_AK8_jet_mass_DT");
  TH1F* h_AK4_jet_mass_TTToHadronic_DT    =      (TH1F*)f4->Get("h_AK4_jet_mass_DT");
  TH1F* h_totHT_TTToHadronic_DT           =      (TH1F*)f4->Get("h_totHT_DT");
  TH1I* h_nfatjets_TTToHadronic_DT        =      (TH1I*)f4->Get("h_nfatjets_DT");
  TH1I* h_nAK4_TTToHadronic_DT            =      (TH1I*)f4->Get("h_nAK4_DT");

  ////////////////////////////////////// TTToLeptonic /////////////////////////////////////////

  TH1I *h_SJ_nAK4_100_DT_TTTo2l2nu =      (TH1I*)f5->Get("h_SJ_nAK4_100_DT");
  TH1I *h_SJ_nAK4_200_DT_TTTo2l2nu =      (TH1I*)f5->Get("h_SJ_nAK4_200_DT");
  TH1F *h_SJ_mass_DT_TTTo2l2nu =          (TH1F*)f5->Get("h_SJ_mass_DT");
  TH1F *h_disuperjet_mass_DT_TTTo2l2nu =  (TH1F*)f5->Get("h_disuperjet_mass_DT");
  TH2F *h_MSJ_mass_vs_MdSJ_DT_TTTo2l2nu = (TH2F*)f5->Get("h_MSJ_mass_vs_MdSJ_DT");

  TH1I *h_SJ_nAK4_100_CR_TTTo2l2nu      =  (TH1I*)f5->Get("h_SJ_nAK4_100_CR");
  TH1I *h_SJ_nAK4_200_CR_TTTo2l2nu      =  (TH1I*)f5->Get("h_SJ_nAK4_200_CR");
  TH1F *h_SJ_mass_CR_TTTo2l2nu          =  (TH1F*)f5->Get("h_SJ_mass_CR");
  TH1F *h_disuperjet_mass_CR_TTTo2l2nu  =  (TH1F*)f5->Get("h_disuperjet_mass_CR");
  TH2F *h_MSJ_mass_vs_MdSJ_CR_TTTo2l2nu =  (TH2F*)f5->Get("h_MSJ_mass_vs_MdSJ_CR");

  TH1F* h_AK8_jet_mass_TTto2l2nu_CR    =      (TH1F*)f5->Get("h_AK8_jet_mass_CR");
  TH1F* h_AK4_jet_mass_TTTo2l2nu_CR    =      (TH1F*)f5->Get("h_AK4_jet_mass_CR");
  TH1F* h_totHT_TTTo2l2nu_CR           =      (TH1F*)f5->Get("h_totHT_CR");
  TH1I* h_nfatjets_TTTo2l2nu_CR        =      (TH1I*)f5->Get("h_nfatjets_CR");
  TH1I* h_nAK4_TTTo2l2nu_CR            =      (TH1I*)f5->Get("h_nAK4_CR");

  TH1F* h_AK8_jet_mass_TTTo2l2nu_DT    =      (TH1F*)f5->Get("h_AK8_jet_mass_DT");
  TH1F* h_AK4_jet_mass_TTTo2l2nu_DT    =      (TH1F*)f5->Get("h_AK4_jet_mass_DT");
  TH1F* h_totHT_TTTo2l2nu_DT           =      (TH1F*)f5->Get("h_totHT_DT");
  TH1I* h_nfatjets_TTTo2l2nu_DT        =      (TH1I*)f5->Get("h_nfatjets_DT");
  TH1I* h_nAK4_TTTo2l2nu_DT            =      (TH1I*)f5->Get("h_nAK4_DT");

  TH1I *h_SJ_nAK4_100_DT_TTtoSemiLeptonic =      (TH1I*)f6->Get("h_SJ_nAK4_100_DT");
  TH1I *h_SJ_nAK4_200_DT_TTtoSemiLeptonic   =      (TH1I*)f6->Get("h_SJ_nAK4_200_DT");
  TH1F *h_SJ_mass_DT_TTtoSemiLeptonic =          (TH1F*)f6->Get("h_SJ_mass_DT");
  TH1F *h_disuperjet_mass_DT_TTtoSemiLeptonic =  (TH1F*)f6->Get("h_disuperjet_mass_DT");
  TH2F *h_MSJ_mass_vs_MdSJ_DT_TTtoSemiLeptonic = (TH2F*)f6->Get("h_MSJ_mass_vs_MdSJ_DT");

  TH1I *h_SJ_nAK4_100_CR_TTtoSemiLeptonic      =  (TH1I*)f6->Get("h_SJ_nAK4_100_CR");
  TH1I *h_SJ_nAK4_200_CR_TTtoSemiLeptonic      =  (TH1I*)f6->Get("h_SJ_nAK4_200_CR");
  TH1F *h_SJ_mass_CR_TTtoSemiLeptonic          =  (TH1F*)f6->Get("h_SJ_mass_CR");
  TH1F *h_disuperjet_mass_CR_TTtoSemiLeptonic  =  (TH1F*)f6->Get("h_disuperjet_mass_CR");
  TH2F *h_MSJ_mass_vs_MdSJ_CR_TTtoSemiLeptonic =  (TH2F*)f6->Get("h_MSJ_mass_vs_MdSJ_CR");

  TH1F* h_AK8_jet_mass_TTtoSemiLeptonic_CR    =      (TH1F*)f6->Get("h_AK8_jet_mass_CR");
  TH1F* h_AK4_jet_mass_TTtoSemiLeptonic_CR    =      (TH1F*)f6->Get("h_AK4_jet_mass_CR");
  TH1F* h_totHT_TTtoSemiLeptonic_CR           =      (TH1F*)f6->Get("h_totHT_CR");
  TH1I* h_nfatjets_TTtoSemiLeptonic_CR        =      (TH1I*)f6->Get("h_nfatjets_CR");
  TH1I* h_nAK4_TTtoSemiLeptonic_CR            =      (TH1I*)f6->Get("h_nAK4_CR");

  TH1F* h_AK8_jet_mass_TTtoSemiLeptonic_DT    =      (TH1F*)f6->Get("h_AK8_jet_mass_DT");
  TH1F* h_AK4_jet_mass_TTtoSemiLeptonic_DT    =      (TH1F*)f6->Get("h_AK4_jet_mass_DT");
  TH1F* h_totHT_TTtoSemiLeptonic_DT           =      (TH1F*)f6->Get("h_totHT_DT");
  TH1I* h_nfatjets_TTtoSemiLeptonic_DT        =      (TH1I*)f6->Get("h_nfatjets_DT");
  TH1I* h_nAK4_TTtoSemiLeptonic_DT            =      (TH1I*)f6->Get("h_nAK4_DT");



  h_SJ_nAK4_100_CR_TTToHadronic->Scale(h_TTToHadronic_SF);
  h_SJ_nAK4_200_CR_TTToHadronic->Scale(h_TTToHadronic_SF);
  h_SJ_mass_CR_TTToHadronic->Scale(h_TTToHadronic_SF);
  h_disuperjet_mass_CR_TTToHadronic->Scale(h_TTToHadronic_SF);
  h_MSJ_mass_vs_MdSJ_CR_TTToHadronic->Scale(h_TTToHadronic_SF);
  h_SJ_nAK4_100_DT_TTToHadronic->Scale(h_TTToHadronic_SF);
  h_SJ_nAK4_200_DT_TTToHadronic->Scale(h_TTToHadronic_SF);
  h_SJ_mass_DT_TTToHadronic->Scale(h_TTToHadronic_SF);
  h_disuperjet_mass_DT_TTToHadronic->Scale(h_TTToHadronic_SF);
  h_MSJ_mass_vs_MdSJ_DT_TTToHadronic->Scale(h_TTToHadronic_SF);
  h_AK8_jet_mass_TTToHadronic_CR->Scale(h_TTToHadronic_SF);
  h_AK4_jet_mass_TTToHadronic_CR->Scale(h_TTToHadronic_SF);
  h_totHT_TTToHadronic_CR->Scale(h_TTToHadronic_SF);
  h_nfatjets_TTToHadronic_CR->Scale(h_TTToHadronic_SF);
  h_nAK4_TTToHadronic_CR->Scale(h_TTToHadronic_SF);
  h_AK8_jet_mass_TTToHadronic_DT->Scale(h_TTToHadronic_SF);
  h_AK4_jet_mass_TTToHadronic_DT->Scale(h_TTToHadronic_SF);
  h_totHT_TTToHadronic_DT->Scale(h_TTToHadronic_SF);
  h_nfatjets_TTToHadronic_DT->Scale(h_TTToHadronic_SF);
  h_nAK4_TTToHadronic_DT->Scale(h_TTToHadronic_SF);

  h_SJ_nAK4_100_CR_TTTo2l2nu->Scale(h_TTTo2l2nu_SF);
  h_SJ_nAK4_200_CR_TTTo2l2nu->Scale(h_TTTo2l2nu_SF);
  h_SJ_mass_CR_TTTo2l2nu->Scale(h_TTTo2l2nu_SF);
  h_disuperjet_mass_CR_TTTo2l2nu->Scale(h_TTTo2l2nu_SF);
  h_MSJ_mass_vs_MdSJ_CR_TTTo2l2nu->Scale(h_TTTo2l2nu_SF);
  h_SJ_nAK4_100_DT_TTTo2l2nu->Scale(h_TTTo2l2nu_SF);
  h_SJ_nAK4_200_DT_TTTo2l2nu->Scale(h_TTTo2l2nu_SF);
  h_SJ_mass_DT_TTTo2l2nu->Scale(h_TTTo2l2nu_SF);
  h_disuperjet_mass_DT_TTTo2l2nu->Scale(h_TTTo2l2nu_SF);
  h_MSJ_mass_vs_MdSJ_DT_TTTo2l2nu->Scale(h_TTTo2l2nu_SF);
  h_AK8_jet_mass_TTto2l2nu_CR->Scale(h_TTTo2l2nu_SF);
  h_AK4_jet_mass_TTTo2l2nu_CR->Scale(h_TTTo2l2nu_SF);
  h_totHT_TTTo2l2nu_CR->Scale(h_TTTo2l2nu_SF);
  h_nfatjets_TTTo2l2nu_CR->Scale(h_TTTo2l2nu_SF);
  h_nAK4_TTTo2l2nu_CR->Scale(h_TTTo2l2nu_SF);
  h_AK8_jet_mass_TTTo2l2nu_DT->Scale(h_TTTo2l2nu_SF);
  h_AK4_jet_mass_TTTo2l2nu_DT->Scale(h_TTTo2l2nu_SF);
  h_totHT_TTTo2l2nu_DT->Scale(h_TTTo2l2nu_SF);
  h_nfatjets_TTTo2l2nu_DT->Scale(h_TTTo2l2nu_SF);
  h_nAK4_TTTo2l2nu_DT->Scale(h_TTTo2l2nu_SF);

  h_SJ_nAK4_100_CR_TTtoSemiLeptonic->Scale(h_TTToSemiLeptonic_SF);
  h_SJ_nAK4_200_CR_TTtoSemiLeptonic->Scale(h_TTToSemiLeptonic_SF);
  h_SJ_mass_CR_TTtoSemiLeptonic->Scale(h_TTToSemiLeptonic_SF);
  h_disuperjet_mass_CR_TTtoSemiLeptonic->Scale(h_TTToSemiLeptonic_SF);
  h_MSJ_mass_vs_MdSJ_CR_TTtoSemiLeptonic->Scale(h_TTToSemiLeptonic_SF);
  h_SJ_nAK4_100_DT_TTtoSemiLeptonic->Scale(h_TTToSemiLeptonic_SF);
  h_SJ_nAK4_200_DT_TTtoSemiLeptonic->Scale(h_TTToSemiLeptonic_SF);
  h_SJ_mass_DT_TTtoSemiLeptonic->Scale(h_TTToSemiLeptonic_SF);
  h_disuperjet_mass_DT_TTtoSemiLeptonic->Scale(h_TTToSemiLeptonic_SF);
  h_MSJ_mass_vs_MdSJ_DT_TTtoSemiLeptonic->Scale(h_TTToSemiLeptonic_SF);
  h_AK8_jet_mass_TTtoSemiLeptonic_CR->Scale(h_TTToSemiLeptonic_SF);
  h_AK4_jet_mass_TTtoSemiLeptonic_CR->Scale(h_TTToSemiLeptonic_SF);
  h_totHT_TTtoSemiLeptonic_CR->Scale(h_TTToSemiLeptonic_SF);
  h_nfatjets_TTtoSemiLeptonic_CR->Scale(h_TTToSemiLeptonic_SF);
  h_nAK4_TTtoSemiLeptonic_CR->Scale(h_TTToSemiLeptonic_SF);
  h_AK8_jet_mass_TTtoSemiLeptonic_DT->Scale(h_TTToSemiLeptonic_SF);
  h_AK4_jet_mass_TTtoSemiLeptonic_DT->Scale(h_TTToSemiLeptonic_SF);
  h_totHT_TTtoSemiLeptonic_DT->Scale(h_TTToSemiLeptonic_SF);
  h_nfatjets_TTtoSemiLeptonic_DT->Scale(h_TTToSemiLeptonic_SF);
  h_nAK4_TTtoSemiLeptonic_DT->Scale(h_TTToSemiLeptonic_SF);



    h_nAK4_DT->Add(h_nAK4_TTToHadronic_DT);
  h_nAK4_DT->Add(h_nAK4_TTTo2l2nu_DT);
  h_nAK4_DT->Add(h_nAK4_TTtoSemiLeptonic_DT);
  h_nAK4_DT->Scale(1000000/h_nAK4_DT->Integral());

    h_nAK4_CR->Add(h_nAK4_TTToHadronic_CR);
  h_nAK4_CR->Add(h_nAK4_TTTo2l2nu_CR);
  h_nAK4_CR->Add(h_nAK4_TTtoSemiLeptonic_CR);
  h_nAK4_CR->Scale(1000000/h_nAK4_CR->Integral());

    h_nfatjets_DT->Add(h_nfatjets_TTToHadronic_DT);
  h_nfatjets_DT->Add(h_nfatjets_TTTo2l2nu_DT);
  h_nfatjets_DT->Add(h_nfatjets_TTtoSemiLeptonic_DT);
    h_nfatjets_DT->Scale(1000000/h_nfatjets_DT->Integral());

  h_nfatjets_CR->Add(h_nfatjets_TTToHadronic_CR);
  h_nfatjets_CR->Add(h_nfatjets_TTTo2l2nu_CR);
  h_nfatjets_CR->Add(h_nfatjets_TTtoSemiLeptonic_CR);
    h_nfatjets_CR->Scale(1000000/h_nfatjets_CR->Integral());

  h_totHT_DT->Add(h_totHT_TTToHadronic_DT);
  h_totHT_DT->Add(h_totHT_TTTo2l2nu_DT);
  h_totHT_DT->Add(h_totHT_TTtoSemiLeptonic_DT);
    h_totHT_DT->Scale(1000000/h_totHT_DT->Integral());

  h_totHT_CR->Add(h_totHT_TTToHadronic_CR);
  h_totHT_CR->Add(h_totHT_TTTo2l2nu_CR);
  h_totHT_CR->Add(h_totHT_TTtoSemiLeptonic_CR);
    h_totHT_CR->Scale(1000000/h_totHT_CR->Integral());

  h_AK4_jet_mass_DT->Add(h_AK4_jet_mass_TTToHadronic_DT);
  h_AK4_jet_mass_DT->Add(h_AK4_jet_mass_TTTo2l2nu_DT);
  h_AK4_jet_mass_DT->Add(h_AK4_jet_mass_TTtoSemiLeptonic_DT);
    h_AK4_jet_mass_DT->Scale(1000000/h_AK4_jet_mass_DT->Integral());

  h_AK4_jet_mass_CR->Add(h_AK4_jet_mass_TTToHadronic_CR);
  h_AK4_jet_mass_CR->Add(h_AK4_jet_mass_TTTo2l2nu_CR);
  h_AK4_jet_mass_CR->Add(h_AK4_jet_mass_TTtoSemiLeptonic_CR);
    h_AK4_jet_mass_CR->Scale(1000000/h_AK4_jet_mass_CR->Integral());

  h_AK8_jet_mass_DT->Add(h_AK8_jet_mass_TTToHadronic_DT);
  h_AK8_jet_mass_DT->Add(h_AK8_jet_mass_TTTo2l2nu_DT);
  h_AK8_jet_mass_DT->Add(h_AK8_jet_mass_TTtoSemiLeptonic_DT);
    h_AK8_jet_mass_DT->Scale(1000000/h_AK8_jet_mass_DT->Integral());

  h_AK8_jet_mass_CR->Add(h_AK8_jet_mass_TTToHadronic_CR);
  h_AK8_jet_mass_CR->Add(h_AK8_jet_mass_TTto2l2nu_CR);
  h_AK8_jet_mass_CR->Add(h_AK8_jet_mass_TTtoSemiLeptonic_CR);
    h_AK8_jet_mass_CR->Scale(1000000/h_AK8_jet_mass_CR->Integral());

  h_MSJ_mass_vs_MdSJ_DT->Add(h_MSJ_mass_vs_MdSJ_DT_TTToHadronic);
  h_MSJ_mass_vs_MdSJ_DT->Add(h_MSJ_mass_vs_MdSJ_DT_TTTo2l2nu);
  h_MSJ_mass_vs_MdSJ_DT->Add(h_MSJ_mass_vs_MdSJ_DT_TTtoSemiLeptonic);
    h_MSJ_mass_vs_MdSJ_DT->Scale(1000000/h_MSJ_mass_vs_MdSJ_DT->Integral());


  h_MSJ_mass_vs_MdSJ_CR->Add(h_MSJ_mass_vs_MdSJ_CR_TTToHadronic);
  h_MSJ_mass_vs_MdSJ_CR->Add(h_MSJ_mass_vs_MdSJ_CR_TTTo2l2nu);
  h_MSJ_mass_vs_MdSJ_CR->Add(h_MSJ_mass_vs_MdSJ_CR_TTtoSemiLeptonic);
    h_MSJ_mass_vs_MdSJ_CR->Scale(1000000/h_MSJ_mass_vs_MdSJ_CR->Integral());

  h_disuperjet_mass_DT->Add(h_disuperjet_mass_DT_TTToHadronic);
  h_disuperjet_mass_DT->Add(h_disuperjet_mass_DT_TTTo2l2nu);
  h_disuperjet_mass_DT->Add(h_disuperjet_mass_DT_TTtoSemiLeptonic);
    h_disuperjet_mass_DT->Scale(1./h_disuperjet_mass_DT->Integral());

  h_disuperjet_mass_CR->Add(h_disuperjet_mass_CR_TTToHadronic);
  h_disuperjet_mass_CR->Add(h_disuperjet_mass_CR_TTTo2l2nu);
  h_disuperjet_mass_CR->Add(h_disuperjet_mass_CR_TTtoSemiLeptonic);
    h_disuperjet_mass_CR->Scale(1./h_disuperjet_mass_CR->Integral());

  h_SJ_mass_DT->Add(h_SJ_mass_DT_TTToHadronic);
  h_SJ_mass_DT->Add(h_SJ_mass_DT_TTTo2l2nu);
  h_SJ_mass_DT->Add(h_SJ_mass_DT_TTtoSemiLeptonic);
    h_SJ_mass_DT->Scale(1./h_SJ_mass_DT->Integral());

  h_SJ_mass_CR->Add(h_SJ_mass_CR_TTToHadronic);
  h_SJ_mass_CR->Add(h_SJ_mass_CR_TTTo2l2nu);
  h_SJ_mass_CR->Add(h_SJ_mass_CR_TTtoSemiLeptonic);
    h_SJ_mass_CR->Scale(1./h_SJ_mass_CR->Integral());

  h_SJ_nAK4_200_DT->Add(h_SJ_nAK4_200_DT_TTToHadronic);
  h_SJ_nAK4_200_DT->Add(h_SJ_nAK4_200_DT_TTTo2l2nu);
  h_SJ_nAK4_200_DT->Add(h_SJ_nAK4_200_DT_TTtoSemiLeptonic);
    h_SJ_nAK4_200_DT->Scale(1000000/h_SJ_nAK4_200_DT->Integral());

  h_SJ_nAK4_200_CR->Add(h_SJ_nAK4_200_CR_TTToHadronic);
  h_SJ_nAK4_200_CR->Add(h_SJ_nAK4_200_CR_TTTo2l2nu);
  h_SJ_nAK4_200_CR->Add(h_SJ_nAK4_200_CR_TTtoSemiLeptonic);
    h_SJ_nAK4_200_CR->Scale(1000000/h_SJ_nAK4_200_CR->Integral());

  h_SJ_nAK4_100_DT->Add(h_SJ_nAK4_100_DT_TTToHadronic);
  h_SJ_nAK4_100_DT->Add(h_SJ_nAK4_100_DT_TTTo2l2nu);
  h_SJ_nAK4_100_DT->Add(h_SJ_nAK4_100_DT_TTtoSemiLeptonic);
    h_SJ_nAK4_100_DT->Scale(1000000./h_SJ_nAK4_100_DT->Integral());

  h_SJ_nAK4_100_CR->Add(h_SJ_nAK4_100_CR_TTToHadronic);
  h_SJ_nAK4_100_CR->Add(h_SJ_nAK4_100_CR_TTTo2l2nu);
  h_SJ_nAK4_100_CR->Add(h_SJ_nAK4_100_CR_TTtoSemiLeptonic);
    h_SJ_nAK4_100_CR->Scale(1000000./h_SJ_nAK4_100_CR->Integral());


  }


  TCanvas *c1 = new TCanvas("c1","",400,20, 1500,1500);

  h_SJ_nLooseBtag->Draw("HIST");
  c1->SaveAs("h_nLooseBtag.png");  


 
  h_MSJ_mass_vs_MdSJ_CR->Divide(h_MSJ_mass_vs_MdSJ_DT);
  h_MSJ_mass_vs_MdSJ_CR->SetTitle("M_{SJ} vs M_{diSJ} Ratio (Normalized double tagged BR MC Control region / Normalized double tagged BR MC Signal Region); M_{diSJ};M_{SJ}");
  h_MSJ_mass_vs_MdSJ_CR->GetYaxis()->SetTitleOffset(1.35);
  h_MSJ_mass_vs_MdSJ_CR->GetYaxis()->SetLabelSize(0.015);
  h_MSJ_mass_vs_MdSJ_CR->Draw("colz");
  c1->SaveAs("mSJ_vs_mdiSJ_CR_DT_ratio_MC_CRSR.png"); 



  gPad->SetLogy();

  std::cout << "do ratio plots" << std::endl;

  //std::cout << "Number of events: " << h_SJ_nAK4_100_CR->GetEntries() << "/" << h_SJ_nAK4_100_DT->GetEntries() <<std::endl;
  auto rp_SJ_nAK4_100 = new TRatioPlot(h_SJ_nAK4_100_CR,h_SJ_nAK4_100_DT);
  rp_SJ_nAK4_100->Draw("HIST,E");
  rp_SJ_nAK4_100->GetLowerRefYaxis()->SetTitle("CR MC / SR MC");
  rp_SJ_nAK4_100->GetLowerRefGraph()->SetMaximum(2.);
  rp_SJ_nAK4_100->GetUpperRefYaxis()->SetTitle("Events");
  c1->SaveAs("rp_SJ_nAK4_100_CRSR.png");  


  auto rp_SJ_nAK4_200 = new TRatioPlot(h_SJ_nAK4_200_CR,h_SJ_nAK4_200_DT);
  rp_SJ_nAK4_200->Draw("HIST,E");
  rp_SJ_nAK4_200->GetLowerRefYaxis()->SetTitle("CR MC / SR MC");
  rp_SJ_nAK4_200->GetLowerRefGraph()->SetMaximum(2.);
  rp_SJ_nAK4_200->GetUpperRefYaxis()->SetTitle("Events");
  c1->SaveAs("rp_SJ_nAK4_200_CRSR.png"); 

  auto rp_SJ_mass = new TRatioPlot(h_SJ_mass_CR,h_SJ_mass_DT);
  rp_SJ_mass->Draw("HIST,E");
  rp_SJ_mass->GetLowerRefYaxis()->SetTitle("CR MC / SR MC");
  rp_SJ_mass->GetLowerRefGraph()->SetMaximum(2.);
  rp_SJ_mass->GetUpperRefYaxis()->SetTitle("Events");
  c1->SaveAs("rp_SJ_mass_CRSR.png"); 

  auto rp_disuperjet_mass = new TRatioPlot(h_disuperjet_mass_CR,h_disuperjet_mass_DT);
  //rp_disuperjet_mass->SetTitle("diSuperJet Mass (CR=Red, SR=Points");
  rp_disuperjet_mass->Draw("HIST,E");
  rp_disuperjet_mass->GetLowerRefYaxis()->SetTitle("CR MC / SR MC");
  rp_disuperjet_mass->GetLowerRefGraph()->SetMaximum(2.);
  rp_disuperjet_mass->GetUpperRefYaxis()->SetTitle("Events");
  c1->SaveAs("rp_disuperjet_mass_CRSR.png"); 



  auto rp_AK8_jet_mass = new TRatioPlot(h_AK8_jet_mass_CR,h_AK8_jet_mass_DT);
  //rp_disuperjet_mass->SetTitle("diSuperJet Mass (CR=Red, SR=Points");
  rp_AK8_jet_mass->Draw("HIST,E");
  rp_AK8_jet_mass->GetLowerRefYaxis()->SetTitle("CR MC / SR MC");
  rp_AK8_jet_mass->GetLowerRefGraph()->SetMaximum(2.);
  rp_AK8_jet_mass->GetUpperRefYaxis()->SetTitle("Events");
  c1->SaveAs("rp_AK8_jet_mass_CRSR.png"); 


  auto rp_AK4_jet_mass = new TRatioPlot(h_AK4_jet_mass_CR,h_AK4_jet_mass_DT);
  //rp_disuperjet_mass->SetTitle("diSuperJet Mass (CR=Red, SR=Points");
  rp_AK4_jet_mass->Draw("HIST,E");
  rp_AK4_jet_mass->GetLowerRefYaxis()->SetTitle("CR MC / SR MC");
  rp_AK4_jet_mass->GetLowerRefGraph()->SetMaximum(2.);
  rp_AK4_jet_mass->GetUpperRefYaxis()->SetTitle("Events");
  c1->SaveAs("rp_AK4_jet_mass_CRSR.png"); 

  auto rp_totHT = new TRatioPlot(h_totHT_CR,h_totHT_DT);
  //rp_disuperjet_mass->SetTitle("diSuperJet Mass (CR=Red, SR=Points");
  rp_totHT->Draw("HIST,E");
  rp_totHT->GetLowerRefYaxis()->SetTitle("CR MC / SR MC");
  rp_totHT->GetLowerRefGraph()->SetMaximum(2.);
  rp_totHT->GetUpperRefYaxis()->SetTitle("Events");
  c1->SaveAs("rp_totHT_CRSR.png"); 


  auto rp_nfatjets = new TRatioPlot(h_nfatjets_CR,h_nfatjets_DT);
  //rp_disuperjet_mass->SetTitle("diSuperJet Mass (CR=Red, SR=Points");
  rp_nfatjets->Draw("HIST,E");
  rp_nfatjets->GetLowerRefYaxis()->SetTitle("CR MC / SR MC");
  rp_nfatjets->GetLowerRefGraph()->SetMaximum(2.);
  rp_nfatjets->GetUpperRefYaxis()->SetTitle("Events");
  c1->SaveAs("rp_nfatjets_CRSR.png"); 

  auto rp_nAK4 = new TRatioPlot(h_nAK4_CR,h_nAK4_DT);
  //rp_disuperjet_mass->SetTitle("diSuperJet Mass (CR=Red, SR=Points");
  rp_nAK4->Draw("HIST,E");
  rp_nAK4->GetLowerRefYaxis()->SetTitle("CR MC / SR MC");
  rp_nAK4->GetLowerRefGraph()->SetMaximum(2.);
  rp_nAK4->GetUpperRefYaxis()->SetTitle("Events");
  c1->SaveAs("rp_nAK4_CRSR.png"); 

  std::cout << "do TH2" << std::endl;




  //make Suu 5TeV, chi 2 TeV + BR / BR TH2


}



// /store/user/ecannaer/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/clustAlg_TTToHadronic/221227_152237/0000



/*
old things I'm not using 

  TH1F* h_GenBtagged_HT_HT1000to1500        =      (TH1F*)f1->Get("h_GenBtagged_HT");
  TH1F* h_GenBtagged_HT_HT1500to2000        =      (TH1F*)f2->Get("h_GenBtagged_HT");
  TH1F* h_GenBtagged_HT_HT2000toInf         =      (TH1F*)f3->Get("h_GenBtagged_HT");
  TH1F* h_GenBtagged_HT_TTToHadronic        =      (TH1F*)f4->Get("h_GenBtagged_HT");
  TH1F* h_GenBtagged_HT_TTTo2l2nu           =      (TH1F*)f5->Get("h_GenBtagged_HT");
  TH1F* h_GenBtagged_HT_TTtoSemiLeptonic    =      (TH1F*)f6->Get("h_GenBtagged_HT");

  TH1F* h_GenBtagged_pT_HT1000to1500        =      (TH1F*)f1->Get("h_GenBtagged_pT");
  TH1F* h_GenBtagged_pT_HT1500to2000        =      (TH1F*)f2->Get("h_GenBtagged_pT");
  TH1F* h_GenBtagged_pT_HT2000toInf         =      (TH1F*)f3->Get("h_GenBtagged_pT");
  TH1F* h_GenBtagged_pT_TTToHadronic        =      (TH1F*)f4->Get("h_GenBtagged_pT");
  TH1F* h_GenBtagged_pT_TTTo2l2nu           =      (TH1F*)f5->Get("h_GenBtagged_pT");
  TH1F* h_GenBtagged_pT_TTtoSemiLeptonic    =      (TH1F*)f6->Get("h_GenBtagged_pT");

  TH1F* h_RECOBTagged_HT_HT1000to1500        =      (TH1F*)f1->Get("h_RECOBtagged_HT");
  TH1F* h_RECOBTagged_HT_HT1500to2000        =      (TH1F*)f2->Get("h_RECOBtagged_HT");
  TH1F* h_RECOBTagged_HT_HT2000toInf         =      (TH1F*)f3->Get("h_RECOBtagged_HT");
  TH1F* h_RECOBTagged_HT_TTToHadronic        =      (TH1F*)f4->Get("h_RECOBtagged_HT");
  TH1F* h_RECOBTagged_HT_TTTo2l2nu           =      (TH1F*)f5->Get("h_RECOBtagged_HT");
  TH1F* h_RECOBTagged_HT_TTtoSemiLeptonic    =      (TH1F*)f6->Get("h_RECOBtagged_HT");

  TH1F* h_RECOBTagged_pT_HT1000to1500        =      (TH1F*)f1->Get("h_RECOBtagged_pT");
  TH1F* h_RECOBTagged_pT_HT1500to2000        =      (TH1F*)f2->Get("h_RECOBtagged_pT");
  TH1F* h_RECOBTagged_pT_HT2000toInf         =      (TH1F*)f3->Get("h_RECOBtagged_pT");
  TH1F* h_RECOBTagged_pT_TTToHadronic        =      (TH1F*)f4->Get("h_RECOBtagged_pT");
  TH1F* h_RECOBTagged_pT_TTTo2l2nu           =      (TH1F*)f5->Get("h_RECOBtagged_pT");
  TH1F* h_RECOBTagged_pT_TTtoSemiLeptonic    =      (TH1F*)f6->Get("h_RECOBtagged_pT");






  h_GenBtagged_HT_HT1000to1500->Scale(QCD_HT1000to1500_SF);    
  h_GenBtagged_HT_HT1500to2000->Scale(QCD_HT1500to2000_SF);    
  h_GenBtagged_HT_HT2000toInf->Scale(QCD_HT2000toInf_SF);     

  h_GenBtagged_pT_HT1000to1500->Scale(QCD_HT1000to1500_SF);    
  h_GenBtagged_pT_HT1500to2000->Scale(QCD_HT1500to2000_SF);    
  h_GenBtagged_pT_HT2000toInf->Scale(QCD_HT2000toInf_SF);     

  h_RECOBTagged_HT_HT1000to1500->Scale(QCD_HT1000to1500_SF);    
  h_RECOBTagged_HT_HT1500to2000->Scale(QCD_HT1500to2000_SF);    
  h_RECOBTagged_HT_HT2000toInf->Scale(QCD_HT2000toInf_SF);     

  h_RECOBTagged_pT_HT1000to1500->Scale(QCD_HT1000to1500_SF);    
  h_RECOBTagged_pT_HT1500to2000->Scale(QCD_HT1500to2000_SF);    
  h_RECOBTagged_pT_HT2000toInf->Scale(QCD_HT2000toInf_SF);     


  TH1I *h_nLooseBtag_all = new TH1I(*h_SJ_nLooseBtag_HT1000to1500);
  h_nLooseBtag_all->Add(h_SJ_nLooseBtag_HT1500to2000);
  h_nLooseBtag_all->Add(h_SJ_nLooseBtag_HT2000toInf);


     
  TH1F *h_GenBtagged_HT = new TH1F(*h_GenBtagged_HT_HT1000to1500);
  h_GenBtagged_HT->Add(h_GenBtagged_HT_HT1500to2000);
  h_GenBtagged_HT->Add(h_GenBtagged_HT_HT2000toInf);

  TH1F *h_GenBtagged_pT = new TH1F(*h_GenBtagged_pT_HT1000to1500);
  h_GenBtagged_pT->Add(h_GenBtagged_pT_HT1500to2000);
  h_GenBtagged_pT->Add(h_GenBtagged_pT_HT2000toInf);
  if(includeTTBar)h_GenBtagged_pT->Add(h_GenBtagged_pT_TTToHadronic);
  if(includeTTBar)h_GenBtagged_pT->Add(h_GenBtagged_pT_TTTo2l2nu);
  if(includeTTBar)h_GenBtagged_pT->Add(h_GenBtagged_pT_TTtoSemiLeptonic);

  TH1F *h_RECOBTagged_HT = new TH1F(*h_RECOBTagged_HT_HT1000to1500);
  h_RECOBTagged_HT->Add(h_RECOBTagged_HT_HT1500to2000);
  h_RECOBTagged_HT->Add(h_RECOBTagged_HT_HT2000toInf);
  if(includeTTBar)h_RECOBTagged_HT->Add(h_RECOBTagged_HT_TTToHadronic);
  if(includeTTBar)h_RECOBTagged_HT->Add(h_RECOBTagged_HT_TTTo2l2nu);
  if(includeTTBar)h_RECOBTagged_HT->Add(h_RECOBTagged_HT_TTtoSemiLeptonic);

  TH1F *h_RECOBTagged_pT = new TH1F(*h_RECOBTagged_pT_HT1000to1500);
  h_RECOBTagged_pT->Add(h_RECOBTagged_pT_HT1500to2000);
  h_RECOBTagged_pT->Add(h_RECOBTagged_pT_HT2000toInf);
  if(includeTTBar)h_RECOBTagged_pT->Add(h_RECOBTagged_pT_TTToHadronic);
  if(includeTTBar)h_RECOBTagged_pT->Add(h_RECOBTagged_pT_TTTo2l2nu);
  if(includeTTBar)h_RECOBTagged_pT->Add(h_RECOBTagged_pT_TTtoSemiLeptonic);

  h_GenBtagged_pT->SetFillColor(kRed);
  h_RECOBTagged_pT->SetFillColor(kBlue);

  h_GenBtagged_HT->SetFillColor(kRed);
  h_RECOBTagged_HT->SetFillColor(kBlue);


  h_GenBtagged_HT_TTToHadronic->Scale(h_TTToHadronic_SF);    
  h_GenBtagged_HT_TTTo2l2nu->Scale(h_TTTo2l2nu_SF);       
  h_GenBtagged_HT_TTtoSemiLeptonic->Scale(h_TTToSemiLeptonic_SF);

  h_GenBtagged_pT_TTToHadronic->Scale(h_TTToHadronic_SF);    
  h_GenBtagged_pT_TTTo2l2nu->Scale(h_TTTo2l2nu_SF);       
  h_GenBtagged_pT_TTtoSemiLeptonic->Scale(h_TTToSemiLeptonic_SF);

  h_RECOBTagged_HT_TTToHadronic->Scale(h_TTToHadronic_SF);    
  h_RECOBTagged_HT_TTTo2l2nu->Scale(h_TTTo2l2nu_SF);       
  h_RECOBTagged_HT_TTtoSemiLeptonic->Scale(h_TTToSemiLeptonic_SF);

  h_RECOBTagged_pT_TTToHadronic->Scale(h_TTToHadronic_SF);    
  h_RECOBTagged_pT_TTTo2l2nu->Scale(h_TTTo2l2nu_SF);       
  h_RECOBTagged_pT_TTtoSemiLeptonic->Scale(h_TTToSemiLeptonic_SF);
  

  if(includeTTBar)h_GenBtagged_HT->Add(h_GenBtagged_HT_TTToHadronic);
  if(includeTTBar)h_GenBtagged_HT->Add(h_GenBtagged_HT_TTTo2l2nu);
  if(includeTTBar)h_GenBtagged_HT->Add(h_GenBtagged_HT_TTtoSemiLeptonic);

  h_nLooseBtag_all->Draw("HIST");
  c1->SaveAs("h_nLooseBtag_all_CRSR.png"); 



  auto rp_bTagEfficiency_pT = new TRatioPlot(h_GenBtagged_pT,h_RECOBTagged_pT);
  //rp_bTagEfficiency_pT->SetTitle("genBTagged AK4 Jets vs RECO tagged AK4 Jets by p_{T}");
  rp_bTagEfficiency_pT->Draw("HIST,E");
  rp_bTagEfficiency_pT->GetLowerRefYaxis()->SetTitle("CR MC / SR MC");
  rp_bTagEfficiency_pT->GetLowerRefGraph()->SetMaximum(2.);
  rp_bTagEfficiency_pT->GetUpperRefYaxis()->SetTitle("Events");
  c1->SaveAs("rp_bTagEfficiency_pT_CRSR.png");  

  auto rp_bTagEfficiency_HT = new TRatioPlot(h_GenBtagged_HT,h_RECOBTagged_HT);
  //rp_bTagEfficiency_HT->SetTitle("genBTagged AK4 Jets vs RECO tagged AK4 Jets by HT");
  rp_bTagEfficiency_HT->Draw("HIST,E");
  rp_bTagEfficiency_HT->GetLowerRefYaxis()->SetTitle("CR MC / SR MC");
  rp_bTagEfficiency_HT->GetLowerRefGraph()->SetMaximum(2.);
  rp_bTagEfficiency_HT->GetUpperRefYaxis()->SetTitle("Events");
  c1->SaveAs("rp_bTagEfficiency_HT_CRSR.png"); 


*/
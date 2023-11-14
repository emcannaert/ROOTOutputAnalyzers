#include <iostream>
#include <string>
#include "TLorentzVector.h"
#include "TRatioPlot.h"
#include "THStack.h"
#include<TStyle.h>
#include <TROOT.h>
#include <TFile.h>
#include <stdio.h>
using namespace std;


//need to write out the histograms here to files 
//open these files in the .py script and then have that write out new histogram files and make plots of the combined bins

// loop over all years and create the combined backround plots with all the nice formatting for each year
// the point of this at time of writing is to get an idea of the systematic uncertainty in signal region and control region
void makeAllNiceSJvsdiSJ_mass_plots_SR_sameDatasets()
{


  //scale factors will be different for same and alt datasets
  /*
  double QCD_1000to1500_SF[4] = {4.60857362, 4.339189275, 4.55806887,  4.64129987}; //TODO, 
  double QCD_1500to2000_SF[4] = {0.6117279713, 0.5735971136,  0.5913499516,  0.6042726685}; //TODO
  double QCD_2000toInf_SF[4] = {0.2321972138,  0.226816329, 0.2216934265,  0.2446761137}; //TODO
  double TTToHadronic_SF[4] = {0.075592, 0.05808655696, 0.06651018525, 0.06588049107}; //TODO
  */
  double QCD_1000to1500_SF[4] = {1.578683216,1.482632755,3.126481451,4.289571744}; //TODO, 
  double QCD_1500to2000_SF[4] = {0.2119142341,0.195224041,0.3197450474,0.4947703875}; //TODO
  double QCD_2000toInf_SF[4] = {0.08568186031,0.07572795371,0.14306915,0.2132134533}; //TODO
  double TTToHadronic_SF[4] = {0.075592,0.05808655696,0.06651018525,0.06588049107}; //TODO
  double TTToSemiLeptonic_SF[4] = {0.05395328118,0.05808655696,0.04264829286,0.04563489275}; //TODO
  double TTToLeptonic_SF[4] = {0.0459517611,0.03401684391,0.03431532926,00.03617828025}; //TODO

  TCanvas *c1 = new TCanvas("c1","",400,20, 1800,1600);

  std::vector<std::string> years = {"2015","2016","2017","2018"};

  int yearCount = 0;                               
  for(auto year = years.begin(); year< years.end(); year++)
  {

    c1->SetRightMargin(0.15);
    c1->SetLeftMargin(0.1);
    c1->SetTopMargin(0.08);
        

    TFile *f1000to1500 = new TFile(("/Users/ethan/Documents/rootFiles/processedRootFilesAlt/QCDMC_HT1000to1500_" + *year +"_processed.root").c_str());
    TFile *f1500to2000 = new TFile(("/Users/ethan/Documents/rootFiles/processedRootFilesAlt/QCDMC_HT1500to2000_" + *year +"_processed.root").c_str());
    TFile *f2000toInf  = new TFile(("/Users/ethan/Documents/rootFiles/processedRootFilesAlt/QCDMC_HT2000toInf_" + *year +"_processed.root").c_str());
    TFile *fTTToHadronic      = new TFile(("/Users/ethan/Documents/rootFiles/processedRootFilesAlt/TTTohadronic_" + *year +"_processed.root").c_str());
    TFile *fTToSemiLeptonic      = new TFile(("/Users/ethan/Documents/rootFiles/processedRootFilesAlt/TTToSemiLeptonic_" + *year +"_processed.root").c_str());
    TFile *fTToLeptonic      = new TFile(("/Users/ethan/Documents/rootFiles/processedRootFilesAlt/TTToLeptonic_" + *year +"_processed.root").c_str());


    std::string _outFname = "/Users/ethan/Documents/rootFiles/statisticalUncertaintyStudyAlt/allBR_expectedCounts_SR_" + *year +  ".root";
    const char * outFname = _outFname.c_str();
    TFile outFile( outFname  ,"RECREATE");


    TH2F *h_MSJ_mass_vs_MdSJ_SR_1000to1500=  (TH2F*)f1000to1500->Get("h_MSJ_mass_vs_MdSJ_SR");
    TH2F *h_MSJ_mass_vs_MdSJ_SR_1500to2000=  (TH2F*)f1500to2000->Get("h_MSJ_mass_vs_MdSJ_SR");
    TH2F *h_MSJ_mass_vs_MdSJ_SR_2000toInf =  (TH2F*)f2000toInf->Get("h_MSJ_mass_vs_MdSJ_SR");
    TH2F *h_MSJ_mass_vs_MdSJ_SR_TTToHadronic     =  (TH2F*)fTTToHadronic->Get("h_MSJ_mass_vs_MdSJ_SR");
    TH2F *h_MSJ_mass_vs_MdSJ_SR_TTToSemiLeptonic     =  (TH2F*)fTToSemiLeptonic->Get("h_MSJ_mass_vs_MdSJ_SR");
    TH2F *h_MSJ_mass_vs_MdSJ_SR_TTToLeptonic     =  (TH2F*)fTToLeptonic->Get("h_MSJ_mass_vs_MdSJ_SR");

    h_MSJ_mass_vs_MdSJ_SR_1000to1500->Scale(QCD_1000to1500_SF[yearCount]);
    h_MSJ_mass_vs_MdSJ_SR_1500to2000->Scale(QCD_1500to2000_SF[yearCount]);
    h_MSJ_mass_vs_MdSJ_SR_2000toInf->Scale(QCD_2000toInf_SF[yearCount]);
    h_MSJ_mass_vs_MdSJ_SR_TTToHadronic->Scale(TTToHadronic_SF[yearCount]);
    h_MSJ_mass_vs_MdSJ_SR_TTToSemiLeptonic->Scale(TTToSemiLeptonic_SF[yearCount]);
    h_MSJ_mass_vs_MdSJ_SR_TTToLeptonic->Scale(TTToLeptonic_SF[yearCount]);



    TH2F *h_allBR = new TH2F(*h_MSJ_mass_vs_MdSJ_SR_1000to1500);
    h_allBR->Add(h_MSJ_mass_vs_MdSJ_SR_1500to2000);
    h_allBR->Add(h_MSJ_mass_vs_MdSJ_SR_2000toInf);
    h_allBR->Add(h_MSJ_mass_vs_MdSJ_SR_TTToHadronic);
    h_allBR->Add(h_MSJ_mass_vs_MdSJ_SR_TTToSemiLeptonic);
    h_allBR->Add(h_MSJ_mass_vs_MdSJ_SR_TTToLeptonic);

    h_allBR->SetTitle( ("Total Expected Background Counts (QCD+TTbar MC) in the Signal Region for "+ *year +  "; diSuperjet Mass (GeV); avg superjet Mass (GeV)").c_str()    );
    h_allBR->GetXaxis()->SetTitleSize(0.025);
    h_allBR->GetYaxis()->SetTitleSize(0.025);

    h_allBR->GetYaxis()->SetTitleOffset(2.05);
    h_allBR->GetXaxis()->SetTitleOffset(1.30);
     gStyle->SetOptStat(0);

    c1->SetLogz(0);

    h_allBR->Draw("colz");
    c1->SaveAs( ("/Users/ethan/Documents/plots/finalPlots/M_SJ_vs_M_diSJ_combined_SR_"+ *year +".png").c_str() ); 
    h_allBR->Write();

    c1->SetLogz();
    h_allBR->Draw("colz");
    c1->SaveAs( ("/Users/ethan/Documents/plots/finalPlots/M_SJ_vs_M_diSJ_combined_SR_"+ *year +"_LOG.png").c_str() ); 

    std::cout << "Finished SR plot for " << *year << std::endl;
    yearCount++;

    f1000to1500->Close();
    f1500to2000->Close();
    f2000toInf->Close();
    fTTToHadronic->Close();
    outFile.Close();
  }


}
void makeAllNiceSJvsdiSJ_mass_plots_CR_sameDatasets()
{
  double QCD_1000to1500_SF[4] = {4.60857362, 4.339189275, 4.55806887,  4.64129987}; //TODO, 
  double QCD_1500to2000_SF[4] = {0.6117279713, 0.5735971136,  0.5913499516,  0.6042726685}; //TODO
  double QCD_2000toInf_SF[4] = {0.2321972138,  0.226816329, 0.2216934265,  0.2446761137}; //TODO
  double TTToHadronic_SF[4] = {0.075592, 0.05808655696, 0.06651018525, 0.06588049107}; //TODO
  double TTToSemiLeptonic_SF[4] = {0.05395328118,0.05808655696,0.04264829286,0.04563489275}; //TODO
  double TTToLeptonic_SF[4] = {0.0459517611,0.03401684391,0.03431532926,00.03617828025}; //TODO

  TCanvas *c1 = new TCanvas("c1","",400,20, 1800,1600);

  std::vector<std::string> years = {"2015","2016","2017","2018"};
  std::vector<std::string> dataFileNames;
  int yearCount = 0;                               
  for(auto year = years.begin(); year< years.end(); year++)
  {

    c1->SetRightMargin(0.15);
    c1->SetLeftMargin(0.1);
    c1->SetTopMargin(0.08);
        
    // need to 
    if (*year == "2015")
    {
      dataFileNames = {"JetHT_dataB-ver2_","JetHT_dataC-HIPM_","JetHT_dataD-HIPM_","JetHT_dataE-HIPM_","JetHT_dataF-HIPM_"};
    }
    else if (*year == "2016")
    {
      dataFileNames = {"JetHT_dataF_", "JetHT_dataG_", "JetHT_dataH_"};
    }
    else if (*year == "2017")
    {
      dataFileNames = {"JetHT_dataB_","JetHT_dataC_","JetHT_dataD_","JetHT_dataE_", "JetHT_dataF_"};
    }
    else if (*year == "2018")
    {
      dataFileNames = {"JetHT_dataA_","JetHT_dataB_","JetHT_dataC_","JetHT_dataD_"};
    }

    TH2F *h_MSJ_mass_vs_MdSJ_SR_data = new TH2F("h_MSJ_mass_vs_MdSJ_SR","Double Tagged Superjet mass vs diSuperjet mass (Signal Region); diSuperjet mass [GeV];superjet mass", 22,1250., 9500, 20, 500, 3500);  /// 375 * 125
    
    for(auto dataFile = dataFileNames.begin();dataFile < dataFileNames.end();dataFile++)
    {
       TFile *fData = new TFile(("/Users/ethan/Documents/rootFiles/processedRootFilesAlt/JetHT_"+ *dataFile+ "_" + *year +"_processed.root").c_str());
      h_MSJ_mass_vs_MdSJ_SR_data->add();


    }


    TFile *f1000to1500 = new TFile(("/Users/ethan/Documents/rootFiles/processedRootFilesAlt/QCDMC_HT1000to1500_" + *year +"_processed.root").c_str());
    TFile *f1500to2000 = new TFile(("/Users/ethan/Documents/rootFiles/processedRootFilesAlt/QCDMC_HT1500to2000_" + *year +"_processed.root").c_str());
    TFile *f2000toInf  = new TFile(("/Users/ethan/Documents/rootFiles/processedRootFilesAlt/QCDMC_HT2000toInf_" + *year +"_processed.root").c_str());
    TFile *fTTToHadronic      = new TFile(("/Users/ethan/Documents/rootFiles/processedRootFilesAlt/TTTohadronic_" + *year +"_processed.root").c_str());
    TFile *fTTToSemiLeptonic      = new TFile(("/Users/ethan/Documents/rootFiles/processedRootFilesAlt/TTToSemiLeptonic_" + *year +"_processed.root").c_str());
    TFile *fTTToLeptonic      = new TFile(("/Users/ethan/Documents/rootFiles/processedRootFilesAlt/TTToLeptonic_" + *year +"_processed.root").c_str());

    std::string _outFname = "/Users/ethan/Documents/rootFiles/statisticalUncertaintyStudyAlt/allBR_expectedCounts_CR_" + *year +  ".root";
    const char * outFname = _outFname.c_str();
    TFile outFile( outFname  ,"RECREATE");


    TH2F *h_MSJ_mass_vs_MdSJ_CR_1000to1500=  (TH2F*)f1000to1500->Get("h_MSJ_mass_vs_MdSJ_CR");

    TH2F *h_MSJ_mass_vs_MdSJ_CR_1500to2000=  (TH2F*)f1500to2000->Get("h_MSJ_mass_vs_MdSJ_CR");
    TH2F *h_MSJ_mass_vs_MdSJ_CR_2000toInf =  (TH2F*)f2000toInf->Get("h_MSJ_mass_vs_MdSJ_CR");
    TH2F *h_MSJ_mass_vs_MdSJ_CR_TTToHadronic     =  (TH2F*)fTTToHadronic->Get("h_MSJ_mass_vs_MdSJ_CR");
    TH2F *h_MSJ_mass_vs_MdSJ_CR_TTToSemiLeptonic     =  (TH2F*)fTTToSemiLeptonic->Get("h_MSJ_mass_vs_MdSJ_CR");
    TH2F *h_MSJ_mass_vs_MdSJ_CR_TTToLeptonic     =  (TH2F*)fTTToLeptonic->Get("h_MSJ_mass_vs_MdSJ_CR");


    h_MSJ_mass_vs_MdSJ_CR_1000to1500->Scale(QCD_1000to1500_SF[yearCount]);
    h_MSJ_mass_vs_MdSJ_CR_1500to2000->Scale(QCD_1500to2000_SF[yearCount]);
    h_MSJ_mass_vs_MdSJ_CR_2000toInf->Scale(QCD_2000toInf_SF[yearCount]);
    h_MSJ_mass_vs_MdSJ_CR_TTToHadronic->Scale(TTToHadronic_SF[yearCount]);
    h_MSJ_mass_vs_MdSJ_CR_TTToSemiLeptonic->Scale(TTToSemiLeptonic_SF[yearCount]);
    h_MSJ_mass_vs_MdSJ_CR_TTToLeptonic->Scale(TTToLeptonic_SF[yearCount]);



    TH2F *h_allBR = new TH2F(*h_MSJ_mass_vs_MdSJ_CR_1000to1500);
    h_allBR->Add(h_MSJ_mass_vs_MdSJ_CR_1500to2000);
    h_allBR->Add(h_MSJ_mass_vs_MdSJ_CR_2000toInf);
    h_allBR->Add(h_MSJ_mass_vs_MdSJ_CR_TTToHadronic);
    h_allBR->Add(h_MSJ_mass_vs_MdSJ_CR_TTToSemiLeptonic);
    h_allBR->Add(h_MSJ_mass_vs_MdSJ_CR_TTToLeptonic);

    h_allBR->SetTitle( ("Total Expected Background Counts (QCD+TTbar MC) in the Control Region for "+ *year +  "; diSuperjet Mass (GeV); avg superjet Mass (GeV)").c_str()    );
    h_allBR->GetXaxis()->SetTitleSize(0.025);
    h_allBR->GetYaxis()->SetTitleSize(0.025);

    h_allBR->GetYaxis()->SetTitleOffset(2.05);
    h_allBR->GetXaxis()->SetTitleOffset(1.30);
     gStyle->SetOptStat(0);

    c1->SetLogz(0);

    h_allBR->Draw("colz");
    c1->SaveAs( ("/Users/ethan/Documents/plots/finalPlots/M_SJ_vs_M_diSJ_combined_CR_"+ *year +".png").c_str() ); 
    h_allBR->Write();

    c1->SetLogz();
    h_allBR->Draw("colz");
    c1->SaveAs( ("/Users/ethan/Documents/plots/finalPlots/M_SJ_vs_M_diSJ_combined_CR_"+ *year +"_LOG.png").c_str() ); 

    std::cout << "Finished CR plot for " << *year << std::endl;
    yearCount++;

    f1000to1500->Close();
    f1500to2000->Close();
    f2000toInf->Close();
    fTTToHadronic->Close();
    outFile.Close();

  }


}

void make_statUncertainty_mass_plots_SR_sameDatasets()
{
  double QCD_1000to1500_SF[4] = {4.60857362, 4.339189275, 4.55806887,  4.64129987}; //TODO, 
  double QCD_1500to2000_SF[4] = {0.6117279713, 0.5735971136,  0.5913499516,  0.6042726685}; //TODO
  double QCD_2000toInf_SF[4] = {0.2321972138,  0.226816329, 0.2216934265,  0.2446761137}; //TODO
  double TTToHadronic_SF[4] = {0.075592, 0.05808655696, 0.06651018525, 0.06588049107}; //TODO
  double TTToSemiLeptonic_SF[4] = {0.05395328118,0.05808655696,0.04264829286,0.04563489275}; //TODO
  double TTToLeptonic_SF[4] = {0.0459517611,0.03401684391,0.03431532926,00.03617828025}; //TODO

  TCanvas *c1 = new TCanvas("c1","",400,20, 1800,1600);



  std::vector<std::string> years = {"2015","2016","2017","2018"};

  int yearCount = 0;                               
  for(auto year = years.begin(); year< years.end(); year++)
  {

    c1->SetRightMargin(0.15);
    c1->SetLeftMargin(0.1);
    c1->SetTopMargin(0.08);
        
    TFile *f1000to1500 = new TFile(("/Users/ethan/Documents/rootFiles/processedRootFilesAlt/QCDMC_HT1000to1500_" + *year +"_processed.root").c_str());
    TFile *f1500to2000 = new TFile(("/Users/ethan/Documents/rootFiles/processedRootFilesAlt/QCDMC_HT1500to2000_" + *year +"_processed.root").c_str());
    TFile *f2000toInf  = new TFile(("/Users/ethan/Documents/rootFiles/processedRootFilesAlt/QCDMC_HT2000toInf_" + *year +"_processed.root").c_str());
    TFile *fTTToHadronic      = new TFile(("/Users/ethan/Documents/rootFiles/processedRootFilesAlt/TTTohadronic_" + *year +"_processed.root").c_str());
    TFile *fTTToSemiLeptonic      = new TFile(("/Users/ethan/Documents/rootFiles/processedRootFilesAlt/TTToSemiLeptonic_" + *year +"_processed.root").c_str());
    TFile *fTTToLeptonic      = new TFile(("/Users/ethan/Documents/rootFiles/processedRootFilesAlt/TTToLeptonic_" + *year +"_processed.root").c_str());

    TH2F *h_MSJ_mass_vs_MdSJ_SR_1000to1500=  (TH2F*)f1000to1500->Get("h_MSJ_mass_vs_MdSJ_SR");

    TH2F *h_MSJ_mass_vs_MdSJ_SR_1500to2000=  (TH2F*)f1500to2000->Get("h_MSJ_mass_vs_MdSJ_SR");
    TH2F *h_MSJ_mass_vs_MdSJ_SR_2000toInf =  (TH2F*)f2000toInf->Get("h_MSJ_mass_vs_MdSJ_SR");
    TH2F *h_MSJ_mass_vs_MdSJ_SR_TTToHadronic     =  (TH2F*)fTTToHadronic->Get("h_MSJ_mass_vs_MdSJ_SR");
    TH2F *h_MSJ_mass_vs_MdSJ_SR_TTToSemiLeptonic     =  (TH2F*)fTTToSemiLeptonic->Get("h_MSJ_mass_vs_MdSJ_SR");
    TH2F *h_MSJ_mass_vs_MdSJ_SR_TTToLeptonic     =  (TH2F*)fTTToLeptonic->Get("h_MSJ_mass_vs_MdSJ_SR");


    h_MSJ_mass_vs_MdSJ_SR_1000to1500->Scale(QCD_1000to1500_SF[yearCount]);
    h_MSJ_mass_vs_MdSJ_SR_1500to2000->Scale(QCD_1500to2000_SF[yearCount]);
    h_MSJ_mass_vs_MdSJ_SR_2000toInf->Scale(QCD_2000toInf_SF[yearCount]);
    h_MSJ_mass_vs_MdSJ_SR_TTToHadronic->Scale(TTToHadronic_SF[yearCount]);
    h_MSJ_mass_vs_MdSJ_SR_TTToSemiLeptonic->Scale(TTToSemiLeptonic_SF[yearCount]);
    h_MSJ_mass_vs_MdSJ_SR_TTToLeptonic->Scale(TTToLeptonic_SF[yearCount]);



    TH2F *h_allBR = new TH2F(*h_MSJ_mass_vs_MdSJ_SR_1000to1500);
    h_allBR->Add(h_MSJ_mass_vs_MdSJ_SR_1500to2000);
    h_allBR->Add(h_MSJ_mass_vs_MdSJ_SR_2000toInf);
    h_allBR->Add(h_MSJ_mass_vs_MdSJ_SR_TTToHadronic);
    h_allBR->Add(h_MSJ_mass_vs_MdSJ_SR_TTToSemiLeptonic);
    h_allBR->Add(h_MSJ_mass_vs_MdSJ_SR_TTToLeptonic);



    h_allBR->SetTitle( ("Expected Stat Uncertainty in the Signal Region for "+ *year +  "; diSuperjet Mass (GeV); avg superjet Mass (GeV)").c_str()    );
    h_allBR->GetXaxis()->SetTitleSize(0.025);
    h_allBR->GetYaxis()->SetTitleSize(0.025);

    h_allBR->GetYaxis()->SetTitleOffset(2.05);
    h_allBR->GetXaxis()->SetTitleOffset(1.30);
     gStyle->SetOptStat(0);
    TH2F *h_allBR_statUncrt = new TH2F(*h_allBR);
    for(int iii = 0;iii<h_allBR_statUncrt->GetNbinsX();iii++)
    {
      for(int jjj=0;jjj < h_allBR_statUncrt->GetNbinsY();jjj++)
      {
        if( h_allBR->GetBinContent(iii,jjj) > 0  )h_allBR_statUncrt->SetBinContent(iii,jjj, 1.0/sqrt(h_allBR->GetBinContent(iii,jjj)));
      }
    }

    c1->SetLogz(0);

    h_allBR_statUncrt->Draw("colz");
    c1->SaveAs( ("/Users/ethan/Documents/plots/statUncertaintyPlotsAlt/M_SJ_vs_M_diSJ_statuUncert_SR_"+ *year +".png").c_str() ); 

    c1->SetLogz();
    h_allBR_statUncrt->Draw("colz");
    c1->SaveAs( ("/Users/ethan/Documents/plots/statUncertaintyPlotsAlt/M_SJ_vs_M_diSJ_statUncert_SR_"+ *year +"_LOG.png").c_str() ); 

    std::cout << "Finished SR stat uncertainty plot for " << *year << std::endl;
    yearCount++;

    f1000to1500->Close();
    f1500to2000->Close();
    f2000toInf->Close();
    fTTToHadronic->Close();

  }


}
void make_statUncertainty_mass_plots_CR_sameDatasets()
{
  double QCD_1000to1500_SF[4] = {4.60857362, 4.339189275, 4.55806887,  4.64129987};  
  double QCD_1500to2000_SF[4] = {0.6117279713, 0.5735971136,  0.5913499516,  0.6042726685};
  double QCD_2000toInf_SF[4] = {0.2321972138,  0.226816329, 0.2216934265,  0.2446761137};
  double TTToHadronic_SF[4] = {0.075592, 0.05808655696, 0.06651018525, 0.06588049107};
  double TTToSemiLeptonic_SF[4] = {0.05395328118,0.05808655696,0.04264829286,0.04563489275}; //TODO
  double TTToLeptonic_SF[4] = {0.0459517611,0.03401684391,0.03431532926,00.03617828025}; //TODO

  TCanvas *c1 = new TCanvas("c1","",400,20, 1800,1600);



  std::vector<std::string> years = {"2015","2016","2017","2018"};

  int yearCount = 0;                               
  for(auto year = years.begin(); year< years.end(); year++)
  {

    c1->SetRightMargin(0.15);
    c1->SetLeftMargin(0.1);
    c1->SetTopMargin(0.08);
        
    TFile *f1000to1500 = new TFile(("/Users/ethan/Documents/rootFiles/processedRootFilesAlt/QCDMC_HT1000to1500_" + *year +"_processed.root").c_str());
    TFile *f1500to2000 = new TFile(("/Users/ethan/Documents/rootFiles/processedRootFilesAlt/QCDMC_HT1500to2000_" + *year +"_processed.root").c_str());
    TFile *f2000toInf  = new TFile(("/Users/ethan/Documents/rootFiles/processedRootFilesAlt/QCDMC_HT2000toInf_" + *year +"_processed.root").c_str());
    TFile *fTTToHadronic      = new TFile(("/Users/ethan/Documents/rootFiles/processedRootFilesAlt/TTTohadronic_" + *year +"_processed.root").c_str());
    TFile *fTTToSemiLeptonic      = new TFile(("/Users/ethan/Documents/rootFiles/processedRootFilesAlt/TTToSemiLeptonic_" + *year +"_processed.root").c_str());
    TFile *fTTToLeptonic      = new TFile(("/Users/ethan/Documents/rootFiles/processedRootFilesAlt/TTToLeptonic_" + *year +"_processed.root").c_str());

    TH2F *h_MSJ_mass_vs_MdSJ_CR_1000to1500=  (TH2F*)f1000to1500->Get("h_MSJ_mass_vs_MdSJ_CR");

    TH2F *h_MSJ_mass_vs_MdSJ_CR_1500to2000=  (TH2F*)f1500to2000->Get("h_MSJ_mass_vs_MdSJ_CR");
    TH2F *h_MSJ_mass_vs_MdSJ_CR_2000toInf =  (TH2F*)f2000toInf->Get("h_MSJ_mass_vs_MdSJ_CR");
    TH2F *h_MSJ_mass_vs_MdSJ_CR_TTToHadronic     =  (TH2F*)fTTToHadronic->Get("h_MSJ_mass_vs_MdSJ_CR");
    TH2F *h_MSJ_mass_vs_MdSJ_CR_TTToSemiLeptonic     =  (TH2F*)fTTToSemiLeptonic->Get("h_MSJ_mass_vs_MdSJ_CR");
    TH2F *h_MSJ_mass_vs_MdSJ_CR_TTToLeptonic     =  (TH2F*)fTTToLeptonic->Get("h_MSJ_mass_vs_MdSJ_CR");



    h_MSJ_mass_vs_MdSJ_CR_1000to1500->Scale(QCD_1000to1500_SF[yearCount]);
    h_MSJ_mass_vs_MdSJ_CR_1500to2000->Scale(QCD_1500to2000_SF[yearCount]);
    h_MSJ_mass_vs_MdSJ_CR_2000toInf->Scale(QCD_2000toInf_SF[yearCount]);
    h_MSJ_mass_vs_MdSJ_CR_TTToHadronic->Scale(TTToHadronic_SF[yearCount]);
    h_MSJ_mass_vs_MdSJ_CR_TTToSemiLeptonic->Scale(TTToSemiLeptonic_SF[yearCount]);
    h_MSJ_mass_vs_MdSJ_CR_TTToLeptonic->Scale(TTToLeptonic_SF[yearCount]);



    TH2F *h_allBR = new TH2F(*h_MSJ_mass_vs_MdSJ_CR_1000to1500);
    h_allBR->Add(h_MSJ_mass_vs_MdSJ_CR_1500to2000);
    h_allBR->Add(h_MSJ_mass_vs_MdSJ_CR_2000toInf);
    h_allBR->Add(h_MSJ_mass_vs_MdSJ_CR_TTToHadronic);
    h_allBR->Add(h_MSJ_mass_vs_MdSJ_CR_TTToSemiLeptonic);
    h_allBR->Add(h_MSJ_mass_vs_MdSJ_CR_TTToLeptonic);



    h_allBR->SetTitle( ("Expected Stat Uncertainty in the Control Region for "+ *year +  "; diSuperjet Mass (GeV); avg superjet Mass (GeV)").c_str()    );
    h_allBR->GetXaxis()->SetTitleSize(0.025);
    h_allBR->GetYaxis()->SetTitleSize(0.025);

    h_allBR->GetYaxis()->SetTitleOffset(2.05);
    h_allBR->GetXaxis()->SetTitleOffset(1.30);
     gStyle->SetOptStat(0);
    TH2F *h_allBR_statUncrt = new TH2F(*h_allBR);
    for(int iii = 0;iii<h_allBR_statUncrt->GetNbinsX();iii++)
    {
      for(int jjj=0;jjj < h_allBR_statUncrt->GetNbinsY();jjj++)
      {
        if( h_allBR->GetBinContent(iii,jjj) > 0  )h_allBR_statUncrt->SetBinContent(iii,jjj, 1.0/sqrt(h_allBR->GetBinContent(iii,jjj)));
      }
    }

    c1->SetLogz(0);

    h_allBR_statUncrt->Draw("colz");
    c1->SaveAs( ("/Users/ethan/Documents/plots/statUncertaintyPlotsAlt/M_SJ_vs_M_diSJ_statuUncert_CR_"+ *year +".png").c_str() ); 

    c1->SetLogz();
    h_allBR_statUncrt->Draw("colz");
    c1->SaveAs( ("/Users/ethan/Documents/plots/statUncertaintyPlotsAlt/M_SJ_vs_M_diSJ_statUncert_CR_"+ *year +"_LOG.png").c_str() ); 

    std::cout << "Finished CR stat uncertainty plot for " << *year << std::endl;
    yearCount++;

    f1000to1500->Close();
    f1500to2000->Close();
    f2000toInf->Close();
    fTTToHadronic->Close();
    fTTToSemiLeptonic->Close();
    fTTToLeptonic->Close();

  }


}

void createFinalSJvsdiSJ_mass()
{
  makeAllNiceSJvsdiSJ_mass_plots_SR_sameDatasets();
  makeAllNiceSJvsdiSJ_mass_plots_CR_sameDatasets();

  make_statUncertainty_mass_plots_SR_sameDatasets();
  make_statUncertainty_mass_plots_CR_sameDatasets();
}


// also want 2D background nice plot
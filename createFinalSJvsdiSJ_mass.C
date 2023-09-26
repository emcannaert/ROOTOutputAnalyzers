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
    TFile *fTTbar      = new TFile(("/Users/ethan/Documents/rootFiles/processedRootFilesAlt/TTTohadronic_" + *year +"_processed.root").c_str());

    std::string _outFname = "/Users/ethan/Documents/rootFiles/statisticalUncertaintyStudyAlt/allBR_expectedCounts_SR_" + *year +  ".root";
    const char * outFname = _outFname.c_str();
    TFile outFile( outFname  ,"RECREATE");


    TH2F *h_MSJ_mass_vs_MdSJ_SR_1000to1500=  (TH2F*)f1000to1500->Get("h_MSJ_mass_vs_MdSJ_SR");
    TH2F *h_MSJ_mass_vs_MdSJ_SR_1500to2000=  (TH2F*)f1500to2000->Get("h_MSJ_mass_vs_MdSJ_SR");
    TH2F *h_MSJ_mass_vs_MdSJ_SR_2000toInf =  (TH2F*)f2000toInf->Get("h_MSJ_mass_vs_MdSJ_SR");
    TH2F *h_MSJ_mass_vs_MdSJ_SR_TTbar     =  (TH2F*)fTTbar->Get("h_MSJ_mass_vs_MdSJ_SR");

    h_MSJ_mass_vs_MdSJ_SR_1000to1500->Scale(QCD_1000to1500_SF[yearCount]);
    h_MSJ_mass_vs_MdSJ_SR_1500to2000->Scale(QCD_1500to2000_SF[yearCount]);
    h_MSJ_mass_vs_MdSJ_SR_2000toInf->Scale(QCD_2000toInf_SF[yearCount]);
    h_MSJ_mass_vs_MdSJ_SR_TTbar->Scale(TTToHadronic_SF[yearCount]);



    TH2F *h_allBR = new TH2F(*h_MSJ_mass_vs_MdSJ_SR_1000to1500);
    h_allBR->Add(h_MSJ_mass_vs_MdSJ_SR_1500to2000);
    h_allBR->Add(h_MSJ_mass_vs_MdSJ_SR_2000toInf);
    h_allBR->Add(h_MSJ_mass_vs_MdSJ_SR_TTbar);

    h_allBR->SetTitle( ("Total Expected Background Counts (QCD+TTbar MC) in the Signal Region for "+ *year +  "; diSuperjet Mass (GeV); avg superjet Mass (GeV)").c_str()    );
    h_allBR->GetXaxis()->SetTitleSize(0.025);
    h_allBR->GetYaxis()->SetTitleSize(0.025);

    h_allBR->GetYaxis()->SetTitleOffset(2.05);
    h_allBR->GetXaxis()->SetTitleOffset(1.30);
     gStyle->SetOptStat(0);

/*

    TLatex latex;
    latex.SetTextSize(0.025);
    latex.SetTextAlign(22);  //align at top


    TText T; T.SetTextFont(30); T.SetTextAlign(22);
    gStyle->SetOptStat(0);

    gPad->Update();
    TPaletteAxis *palette = (TPaletteAxis*)h_allBR->GetListOfFunctions()->FindObject("palette");


    TText *CMSLabel = new TText();
    CMSLabel-> SetNDC();
    CMSLabel -> SetTextFont(1);
    CMSLabel -> SetTextColor(1);
    CMSLabel -> SetTextSize(0.0385);
    CMSLabel -> SetTextAlign(22);
    CMSLabel -> SetTextAngle(0);
    CMSLabel -> DrawText(0.165, 0.895, "CMS");
    CMSLabel->Draw();

    TText *simLabel = new TText();
    simLabel-> SetNDC();
    simLabel -> SetTextFont(52);
    simLabel -> SetTextColor(1);
    simLabel -> SetTextSize(0.024);
    simLabel -> SetTextAlign(22);
    simLabel -> SetTextAngle(0);
    simLabel -> DrawText(0.230, 0.86, "Simulation Preliminary");
    simLabel->Draw();

    TText *fullLumi = new TText();
    fullLumi-> SetNDC();
    fullLumi -> SetTextFont(52);
    fullLumi -> SetTextColor(1);
    fullLumi -> SetTextSize(0.024);
    fullLumi -> SetTextAlign(22);
    fullLumi -> SetTextAngle(0);
    fullLumi -> DrawText(0.230, 0.86, "59.8 fb^{-1}");
    fullLumi->Draw();

    TString lumistuff =  "(13 TeV)";
    latex.SetNDC();
    latex.SetTextAngle(0);
    latex.SetTextColor(kBlack);    
    latex.SetTextFont(42);
    latex.SetTextAlign(31); 
    latex.SetTextSize(0.030);    
    latex.DrawLatex(0.82,0.89,lumistuff);
    */
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
    fTTbar->Close();
    outFile.Close();
  }


}
void makeAllNiceSJvsdiSJ_mass_plots_CR_sameDatasets()
{
  double QCD_1000to1500_SF[4] = {4.60857362, 4.339189275, 4.55806887,  4.64129987}; //TODO, 
  double QCD_1500to2000_SF[4] = {0.6117279713, 0.5735971136,  0.5913499516,  0.6042726685}; //TODO
  double QCD_2000toInf_SF[4] = {0.2321972138,  0.226816329, 0.2216934265,  0.2446761137}; //TODO
  double TTToHadronic_SF[4] = {0.075592, 0.05808655696, 0.06651018525, 0.06588049107}; //TODO

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
    TFile *fTTbar      = new TFile(("/Users/ethan/Documents/rootFiles/processedRootFilesAlt/TTTohadronic_" + *year +"_processed.root").c_str());

    std::string _outFname = "/Users/ethan/Documents/rootFiles/statisticalUncertaintyStudyAlt/allBR_expectedCounts_CR_" + *year +  ".root";
    const char * outFname = _outFname.c_str();
    TFile outFile( outFname  ,"RECREATE");


    TH2F *h_MSJ_mass_vs_MdSJ_CR_1000to1500=  (TH2F*)f1000to1500->Get("h_MSJ_mass_vs_MdSJ_CR");

    TH2F *h_MSJ_mass_vs_MdSJ_CR_1500to2000=  (TH2F*)f1500to2000->Get("h_MSJ_mass_vs_MdSJ_CR");
    TH2F *h_MSJ_mass_vs_MdSJ_CR_2000toInf =  (TH2F*)f2000toInf->Get("h_MSJ_mass_vs_MdSJ_CR");
    TH2F *h_MSJ_mass_vs_MdSJ_CR_TTbar     =  (TH2F*)fTTbar->Get("h_MSJ_mass_vs_MdSJ_CR");

    h_MSJ_mass_vs_MdSJ_CR_1000to1500->Scale(QCD_1000to1500_SF[yearCount]);
    h_MSJ_mass_vs_MdSJ_CR_1500to2000->Scale(QCD_1500to2000_SF[yearCount]);
    h_MSJ_mass_vs_MdSJ_CR_2000toInf->Scale(QCD_2000toInf_SF[yearCount]);
    h_MSJ_mass_vs_MdSJ_CR_TTbar->Scale(TTToHadronic_SF[yearCount]);



    TH2F *h_allBR = new TH2F(*h_MSJ_mass_vs_MdSJ_CR_1000to1500);
    h_allBR->Add(h_MSJ_mass_vs_MdSJ_CR_1500to2000);
    h_allBR->Add(h_MSJ_mass_vs_MdSJ_CR_2000toInf);
    h_allBR->Add(h_MSJ_mass_vs_MdSJ_CR_TTbar);

    h_allBR->SetTitle( ("Total Expected Background Counts (QCD+TTbar MC) in the Control Region for "+ *year +  "; diSuperjet Mass (GeV); avg superjet Mass (GeV)").c_str()    );
    h_allBR->GetXaxis()->SetTitleSize(0.025);
    h_allBR->GetYaxis()->SetTitleSize(0.025);

    h_allBR->GetYaxis()->SetTitleOffset(2.05);
    h_allBR->GetXaxis()->SetTitleOffset(1.30);
     gStyle->SetOptStat(0);

/*

    TLatex latex;
    latex.SetTextSize(0.025);
    latex.SetTextAlign(22);  //align at top


    TText T; T.SetTextFont(30); T.SetTextAlign(22);
    gStyle->SetOptStat(0);

    gPad->Update();
    TPaletteAxis *palette = (TPaletteAxis*)h_allBR->GetListOfFunctions()->FindObject("palette");


    TText *CMSLabel = new TText();
    CMSLabel-> SetNDC();
    CMSLabel -> SetTextFont(1);
    CMSLabel -> SetTextColor(1);
    CMSLabel -> SetTextSize(0.0385);
    CMSLabel -> SetTextAlign(22);
    CMSLabel -> SetTextAngle(0);
    CMSLabel -> DrawText(0.165, 0.895, "CMS");
    CMSLabel->Draw();

    TText *simLabel = new TText();
    simLabel-> SetNDC();
    simLabel -> SetTextFont(52);
    simLabel -> SetTextColor(1);
    simLabel -> SetTextSize(0.024);
    simLabel -> SetTextAlign(22);
    simLabel -> SetTextAngle(0);
    simLabel -> DrawText(0.230, 0.86, "Simulation Preliminary");
    simLabel->Draw();

    TText *fullLumi = new TText();
    fullLumi-> SetNDC();
    fullLumi -> SetTextFont(52);
    fullLumi -> SetTextColor(1);
    fullLumi -> SetTextSize(0.024);
    fullLumi -> SetTextAlign(22);
    fullLumi -> SetTextAngle(0);
    fullLumi -> DrawText(0.230, 0.86, "59.8 fb^{-1}");
    fullLumi->Draw();

    TString lumistuff =  "(13 TeV)";
    latex.SetNDC();
    latex.SetTextAngle(0);
    latex.SetTextColor(kBlack);    
    latex.SetTextFont(42);
    latex.SetTextAlign(31); 
    latex.SetTextSize(0.030);    
    latex.DrawLatex(0.82,0.89,lumistuff);
    */
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
    fTTbar->Close();
    outFile.Close();

  }


}

void make_statUncertainty_mass_plots_SR_sameDatasets()
{
  double QCD_1000to1500_SF[4] = {4.60857362, 4.339189275, 4.55806887,  4.64129987}; //TODO, 
  double QCD_1500to2000_SF[4] = {0.6117279713, 0.5735971136,  0.5913499516,  0.6042726685}; //TODO
  double QCD_2000toInf_SF[4] = {0.2321972138,  0.226816329, 0.2216934265,  0.2446761137}; //TODO
  double TTToHadronic_SF[4] = {0.075592, 0.05808655696, 0.06651018525, 0.06588049107}; //TODO

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
    TFile *fTTbar      = new TFile(("/Users/ethan/Documents/rootFiles/processedRootFilesAlt/TTTohadronic_" + *year +"_processed.root").c_str());

    TH2F *h_MSJ_mass_vs_MdSJ_SR_1000to1500=  (TH2F*)f1000to1500->Get("h_MSJ_mass_vs_MdSJ_SR");

    TH2F *h_MSJ_mass_vs_MdSJ_SR_1500to2000=  (TH2F*)f1500to2000->Get("h_MSJ_mass_vs_MdSJ_SR");
    TH2F *h_MSJ_mass_vs_MdSJ_SR_2000toInf =  (TH2F*)f2000toInf->Get("h_MSJ_mass_vs_MdSJ_SR");
    TH2F *h_MSJ_mass_vs_MdSJ_SR_TTbar     =  (TH2F*)fTTbar->Get("h_MSJ_mass_vs_MdSJ_SR");

    h_MSJ_mass_vs_MdSJ_SR_1000to1500->Scale(QCD_1000to1500_SF[yearCount]);
    h_MSJ_mass_vs_MdSJ_SR_1500to2000->Scale(QCD_1500to2000_SF[yearCount]);
    h_MSJ_mass_vs_MdSJ_SR_2000toInf->Scale(QCD_2000toInf_SF[yearCount]);
    h_MSJ_mass_vs_MdSJ_SR_TTbar->Scale(TTToHadronic_SF[yearCount]);



    TH2F *h_allBR = new TH2F(*h_MSJ_mass_vs_MdSJ_SR_1000to1500);
    h_allBR->Add(h_MSJ_mass_vs_MdSJ_SR_1500to2000);
    h_allBR->Add(h_MSJ_mass_vs_MdSJ_SR_2000toInf);
    h_allBR->Add(h_MSJ_mass_vs_MdSJ_SR_TTbar);



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
    fTTbar->Close();

  }


}
void make_statUncertainty_mass_plots_CR_sameDatasets()
{
  double QCD_1000to1500_SF[4] = {4.60857362, 4.339189275, 4.55806887,  4.64129987}; //TODO, 
  double QCD_1500to2000_SF[4] = {0.6117279713, 0.5735971136,  0.5913499516,  0.6042726685}; //TODO
  double QCD_2000toInf_SF[4] = {0.2321972138,  0.226816329, 0.2216934265,  0.2446761137}; //TODO
  double TTToHadronic_SF[4] = {0.075592, 0.05808655696, 0.06651018525, 0.06588049107}; //TODO

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
    TFile *fTTbar      = new TFile(("/Users/ethan/Documents/rootFiles/processedRootFilesAlt/TTTohadronic_" + *year +"_processed.root").c_str());

    TH2F *h_MSJ_mass_vs_MdSJ_CR_1000to1500=  (TH2F*)f1000to1500->Get("h_MSJ_mass_vs_MdSJ_CR");

    TH2F *h_MSJ_mass_vs_MdSJ_CR_1500to2000=  (TH2F*)f1500to2000->Get("h_MSJ_mass_vs_MdSJ_CR");
    TH2F *h_MSJ_mass_vs_MdSJ_CR_2000toInf =  (TH2F*)f2000toInf->Get("h_MSJ_mass_vs_MdSJ_CR");
    TH2F *h_MSJ_mass_vs_MdSJ_CR_TTbar     =  (TH2F*)fTTbar->Get("h_MSJ_mass_vs_MdSJ_CR");

    h_MSJ_mass_vs_MdSJ_CR_1000to1500->Scale(QCD_1000to1500_SF[yearCount]);
    h_MSJ_mass_vs_MdSJ_CR_1500to2000->Scale(QCD_1500to2000_SF[yearCount]);
    h_MSJ_mass_vs_MdSJ_CR_2000toInf->Scale(QCD_2000toInf_SF[yearCount]);
    h_MSJ_mass_vs_MdSJ_CR_TTbar->Scale(TTToHadronic_SF[yearCount]);



    TH2F *h_allBR = new TH2F(*h_MSJ_mass_vs_MdSJ_CR_1000to1500);
    h_allBR->Add(h_MSJ_mass_vs_MdSJ_CR_1500to2000);
    h_allBR->Add(h_MSJ_mass_vs_MdSJ_CR_2000toInf);
    h_allBR->Add(h_MSJ_mass_vs_MdSJ_CR_TTbar);



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
    fTTbar->Close();

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
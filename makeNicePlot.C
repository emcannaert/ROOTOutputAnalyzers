#include <iostream>
#include <string>
#include "TLorentzVector.h"
#include "TRatioPlot.h"
#include "THStack.h"
#include<TStyle.h>
#include <TROOT.h>
using namespace std;


void make1DGenSJPlot()
{

  //TFile *f1 = new TFile("clustAlgBR_ttbar_processed_.root");
  //TFile *f2 = new TFile("processed_QCD/HT1000to1500/clustAlg_QCD_HT1000to1500_processed.root");
  //TFile *f3 = new TFile("processed_QCD/HT1500to2000/clustAlg_QCD_HT1500to2000_processed.root");
  //TFile *f4 = new TFile("processed_QCD/HT2000toInf/clustAlg_QCD_HT2000toInf_processed.root");
  TFile *f5 = new TFile("/home/ethan/Documents/rootFiles/signalRootFiles/ClusteringAlgorithm_MSuu8TeV-MChi3TeV_cutbased_processed.root");
  TCanvas *c1 = new TCanvas("c1","",400,20, 1600,1300);
  //gPad->SetLogy();

  TH2F *h_SJ1_mass_genParts =  (TH2F*)f5->Get("h_SJ1_mass_genParts");   //QCD 2000 to Inf 
  h_SJ1_mass_genParts->SetTitle("; Superjet 1 Mass (GeV); Events / 150 GeV");
  h_SJ1_mass_genParts->GetXaxis()->SetTitleSize(0.03);
  h_SJ1_mass_genParts->GetYaxis()->SetTitleSize(0.03);

  h_SJ1_mass_genParts->GetYaxis()->SetTitleOffset(1.72);
  h_SJ1_mass_genParts->GetXaxis()->SetTitleOffset(1.30);

  TText T; T.SetTextFont(30); T.SetTextAlign(22);
  gStyle->SetOptStat(0);
  h_SJ1_mass_genParts->Draw("HIST");

  TPaveText *pt = new TPaveText(0.85,0.45,0.60,0.58,"NDC");
  pt->SetTextSize(0.0275);
  pt->SetFillColor(0);
  pt->SetTextAlign(14);
 // pt->AddText("Simulated Signal");
  //pt->AddText("S_{uu} -> chi chi");

  //pt->AddText("H_{T} > 2000 GeV");
  pt->Draw();

/*
 TText *CMSLabel = new TText();
 CMSLabel-> SetNDC();
 CMSLabel -> SetTextFont(1);
 CMSLabel -> SetTextColor(1);
 CMSLabel -> SetTextSize(0.0425);
 CMSLabel -> SetTextAlign(22);
 CMSLabel -> SetTextAngle(0);
 CMSLabel -> DrawText(0.15, 0.93, "CMS");
 CMSLabel->Draw();

 TText *simLabel = new TText();
 simLabel-> SetNDC();
 simLabel -> SetTextFont(52);
 simLabel -> SetTextColor(1);
 simLabel -> SetTextSize(0.028);
 simLabel -> SetTextAlign(22);
 simLabel -> SetTextAngle(0);
 simLabel -> DrawText(0.3425, 0.93, "Simulation Preliminary");
 simLabel->Draw();
*/
 TText *CMSLabel = new TText();
 CMSLabel-> SetNDC();
 CMSLabel -> SetTextFont(1);
 CMSLabel -> SetTextColor(1);
 CMSLabel -> SetTextSize(0.0425);
 CMSLabel -> SetTextAlign(22);
 CMSLabel -> SetTextAngle(0);
 CMSLabel -> DrawText(0.17, 0.875, "CMS");
 CMSLabel->Draw();

 TText *simLabel = new TText();
 simLabel-> SetNDC();
 simLabel -> SetTextFont(52);
 simLabel -> SetTextColor(1);
 simLabel -> SetTextSize(0.028);
 simLabel -> SetTextAlign(22);
 simLabel -> SetTextAngle(0);
 simLabel -> DrawText(0.240, 0.835, "Simulation Preliminary");
 simLabel->Draw();

  const char *longstring = "M_{S_{uu}} = 8 TeV, M_{#chi} = 3 TeV";
  const char *longstring2 = "Simulated S_{uu} #rightarrow #chi #chi";

  TLatex latex;
  latex.SetTextSize(0.025);
  latex.SetTextAlign(22);  //align at top
  latex.DrawLatex(4700,955,longstring);
  latex.DrawLatex(4700,1080,longstring2);

  TString lumistuff =  "(13 TeV)";
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);    
  latex.SetTextFont(42);
  latex.SetTextAlign(31); 
  latex.SetTextSize(0.030);    
  latex.DrawLatex(0.89,0.91,lumistuff);
/*
 TString lumistuff =  "59.83 fb^{-1} (13 TeV)";

  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);    
  latex.SetTextFont(42);
  latex.SetTextAlign(31); 
  latex.SetTextSize(0.045);    
  latex.DrawLatex(0.935,0.92,lumistuff);
*/
 /*
 TText *xlabelSJ = new TText();
 xlabelSJ-> SetNDC();
 //xlabel -> SetTextFont(52);
 xlabelSJ -> SetTextColor(1);
 xlabelSJ -> SetTextSize(0.038);
 xlabelSJ -> SetTextAlign(22);
 xlabelSJ -> SetTextAngle(0);
 xlabelSJ -> DrawText(0.78, 0.03, "Superjet 1 mass");
 xlabelSJ->Draw();

 TText *ylabelSJ = new TText();
 ylabelSJ-> SetNDC();
 //xlabel -> SetTextFont(52);
 ylabelSJ -> SetTextColor(1);
 ylabelSJ -> SetTextSize(0.038);
 ylabelSJ -> SetTextAlign(22);
 ylabelSJ -> SetTextAngle(0);
 ylabelSJ -> DrawText(0.78, 0.03, "Events / 150 GeV");
 ylabelSJ->Draw();
*/
  c1->SaveAs("/home/ethan/Documents/plots/nicePlotsForBOOST/h_SJ1_mass_genParts.png"); 

 
}
void make2DGenSJPlot()
{

  TFile *f5 = new TFile("/home/ethan/Documents/rootFiles/signalRootFiles/ClusteringAlgorithm_MSuu8TeV-MChi3TeV_cutbased_processed.root");
  TCanvas *c1 = new TCanvas("c1","",400,20, 1800,1600);
  //gPad->SetLogy();
  c1->SetRightMargin(0.15);
  c1->SetLeftMargin(0.1);
  c1->SetTopMargin(0.08);

  //c1->SetLeftMargin(0.15);
  //->SetBottomMargin(0.15);
  TH2F *h_MSJ1_vs_MSJ2_gen =  (TH2F*)f5->Get("h_MSJ1_vs_MSJ2_gen");   //QCD 2000 to Inf 
  h_MSJ1_vs_MSJ2_gen->SetTitle("; Superjet 1 Mass (GeV); Superjet 2 Mass (GeV)");
  h_MSJ1_vs_MSJ2_gen->GetXaxis()->SetTitleSize(0.025);
  h_MSJ1_vs_MSJ2_gen->GetYaxis()->SetTitleSize(0.025);

  h_MSJ1_vs_MSJ2_gen->GetYaxis()->SetTitleOffset(2.05);
  h_MSJ1_vs_MSJ2_gen->GetXaxis()->SetTitleOffset(1.30);

  TText T; T.SetTextFont(30); T.SetTextAlign(22);
  gStyle->SetOptStat(0);
  h_MSJ1_vs_MSJ2_gen->Draw("colz");

   gPad->Update();
   TPaletteAxis *palette = (TPaletteAxis*)h_MSJ1_vs_MSJ2_gen->GetListOfFunctions()->FindObject("palette");

/*
   // the following lines move the palette. Choose the values you need for the position.
   palette->SetX1NDC(0.);
   palette->SetX2NDC(0.95);
   //palette->SetY1NDC(0.2);
   //palette->SetY2NDC(0.8);
   gPad->Modified();
   gPad->Update();
  */


  TPaveText *pt = new TPaveText(0.82,0.72,0.57,0.82,"NDC");
  pt->SetTextSize(0.0275);
  pt->SetFillColor(0);
  pt->SetTextAlign(14);
  pt->Draw();

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

  const char *longstring = "M_{S_{uu}} = 8 TeV, M_{#chi} = 3 TeV";
  const char *longstring2 = "Simulated S_{uu} #rightarrow #chi #chi";

  TLatex latex;
  latex.SetTextSize(0.025);
  latex.SetTextAlign(22);  //align at top
  latex.DrawLatex(4750,4750,longstring);
  latex.DrawLatex(4750,5120,longstring2);

  TString lumistuff =  "(13 TeV)";
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);    
  latex.SetTextFont(42);
  latex.SetTextAlign(31); 
  latex.SetTextSize(0.030);    
  latex.DrawLatex(0.89,0.93,lumistuff);
  c1->SaveAs("/home/ethan/Documents/plots/nicePlotsForBOOST/h_MSJ1_vs_MSJ2_gen.png"); 

 
}
void makeZprimeSJMassPlot()
{

  TFile *f5 = new TFile("/home/ethan/Documents/rootFiles/processedRootFiles/ClusteringAlgorithm_generic_output.root");
  TCanvas *c1 = new TCanvas("c1","",400,20, 1800,1600);
  //gPad->SetLogy();
  //c1->SetRightMargin(0.15);
  c1->SetLeftMargin(0.12);
  //c1->SetTopMargin(0.08);

  //c1->SetLeftMargin(0.15);
  //->SetBottomMargin(0.15);
  TH1F *h_MSJ1_vs_MSJ2_gen =  (TH1F*)f5->Get("h_SJ_mass");   //QCD 2000 to Inf 
  h_MSJ1_vs_MSJ2_gen->SetTitle("; Avg Superjet Mass (GeV); Events / 50 GeV");
  h_MSJ1_vs_MSJ2_gen->GetXaxis()->SetTitleSize(0.025);
  h_MSJ1_vs_MSJ2_gen->GetYaxis()->SetTitleSize(0.025);

  h_MSJ1_vs_MSJ2_gen->GetYaxis()->SetTitleOffset(2.05);
  h_MSJ1_vs_MSJ2_gen->GetXaxis()->SetTitleOffset(1.30);

  TText T; T.SetTextFont(30); T.SetTextAlign(22);
  gStyle->SetOptStat(0);
  h_MSJ1_vs_MSJ2_gen->Draw("colz");

  TPaveText *pt = new TPaveText(0.82,0.72,0.57,0.82,"NDC");
  pt->SetTextSize(0.0275);
  pt->SetFillColor(0);
  pt->SetTextAlign(14);
  pt->Draw();

 TText *CMSLabel = new TText();
 CMSLabel-> SetNDC();
 CMSLabel -> SetTextFont(1);
 CMSLabel -> SetTextColor(1);
 CMSLabel -> SetTextSize(0.0385);
 CMSLabel -> SetTextAlign(22);
 CMSLabel -> SetTextAngle(0);
 CMSLabel -> DrawText(0.165, 0.92, "CMS");
 CMSLabel->Draw();

 TText *simLabel = new TText();
 simLabel-> SetNDC();
 simLabel -> SetTextFont(52);
 simLabel -> SetTextColor(1);
 simLabel -> SetTextSize(0.024);
 simLabel -> SetTextAlign(22);
 simLabel -> SetTextAngle(0);
 simLabel -> DrawText(0.315, 0.915, "Simulation Preliminary");
 simLabel->Draw();

  const char *longstring = "M_{Z'} = 3 TeV";
  const char *longstring2 = "Simulated Z' #rightarrow t#bar t";

  TLatex latex;
  latex.SetTextSize(0.03);
  latex.SetTextAlign(22);  //align at top
  latex.DrawLatex(1120,3740,longstring);
  latex.DrawLatex(1100,4000,longstring2);

  TString lumistuff =  "(13 TeV)";
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);    
  latex.SetTextFont(42);
  latex.SetTextAlign(31); 
  latex.SetTextSize(0.030);    
  latex.DrawLatex(0.89,0.91,lumistuff);

  c1->SaveAs("/home/ethan/Documents/plots/nicePlotsForBOOST/Zprime_SJ_mass.png"); 

 
}
void makeCutflowPlot()
{
   TCanvas *c1 = new TCanvas("c1","",400,20, 1800,1600);
   TH1I* h_cutflow = new TH1I("h_cutflow","Events passing initial selection;; Events",6,-0.5,5.5);

  gStyle->SetOptStat(0);

  //4.94066e+06/4.37357e+06/1.14897e+06/162437, 30485.6 passed BJet cut, 1000.95 double tagged.
   h_cutflow->SetBinContent(1,4.94e+06);
   h_cutflow->GetXaxis()->SetBinLabel(1,"total events");
   h_cutflow->SetBinContent(2,4.37e+06);
   h_cutflow->GetXaxis()->SetBinLabel(2,"HT > 1500 GeV");
   h_cutflow->SetBinContent(3,1.15e+06);
   h_cutflow->GetXaxis()->SetBinLabel(3,"nAK8 > 3");
   h_cutflow->SetBinContent(4,162437);
   h_cutflow->GetXaxis()->SetBinLabel(4,"nHeavyAK8 > 2");
   h_cutflow->SetBinContent(5,30486);
   h_cutflow->GetXaxis()->SetBinLabel(5,"nBtags > 0");
   h_cutflow->SetBinContent(6,1001);
   h_cutflow->GetXaxis()->SetBinLabel(6,"SJ substructure");
  gPad->SetLogy();
  h_cutflow->GetYaxis()->SetTitleSize(0.025);

  h_cutflow->GetYaxis()->SetTitleOffset(2.05);
  h_cutflow->Draw("HIST");

 TText *CMSLabel = new TText();
 CMSLabel-> SetNDC();
 CMSLabel -> SetTextFont(1);
 CMSLabel -> SetTextColor(1);
 CMSLabel -> SetTextSize(0.0385);
 CMSLabel -> SetTextAlign(22);
 CMSLabel -> SetTextAngle(0);
 CMSLabel -> DrawText(0.152, 0.92, "CMS");
 CMSLabel->Draw();

 TText *simLabel = new TText();
 simLabel-> SetNDC();
 simLabel -> SetTextFont(52);
 simLabel -> SetTextColor(1);
 simLabel -> SetTextSize(0.024);
 simLabel -> SetTextAlign(22);
 simLabel -> SetTextAngle(0);
 simLabel -> DrawText(0.29, 0.915, "Simulation Preliminary");
 simLabel->Draw();

  const char *longstring = "M_{S_{uu}} = 8 TeV, M_{#chi} = 3 TeV";
  const char *longstring2 = "Simulated S_{uu} #rightarrow #chi #chi";

  TLatex latex;
  latex.SetTextSize(0.025);
  latex.SetTextAlign(22);  //align at top
  latex.DrawLatex(4750,4750,longstring);
  latex.DrawLatex(4750,5120,longstring2);

 TString lumistuff =  "59.83 fb^{-1} (13 TeV)";
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);    
  latex.SetTextFont(42);
  latex.SetTextAlign(31); 
  latex.SetTextSize(0.030);    
  latex.DrawLatex(0.935,0.91,lumistuff);


  c1->SaveAs("/home/ethan/Documents/plots/nicePlotsForBOOST/h_cutflow.png"); 

}

//SJ mass & diSJ mass 1D plots (for 8 TeV or 5 TeV Suu?), an example of a 2D plot

void makeSuu1DPlot5TeV()
{
  TFile *f6 = new TFile("/home/ethan/Documents/rootFiles/signalRootFiles/ClusteringAlgorithm_MSuu5TeV-MChi1p5TeV_cutbased_processed.root");   //need processed 8 TeV Suu and 5 TeV Suu 
  TCanvas *c1 = new TCanvas("c1","",400,20, 1800,1600);
  //gPad->SetLogy();
  //c1->SetRightMargin(0.15);
  c1->SetLeftMargin(0.12);
  //c1->SetTopMargin(0.08);

  //c1->SetLeftMargin(0.15);
  //->SetBottomMargin(0.15);
  TH1F *h_SJ_mass_5TeV =  (TH1F*)f6->Get("h_SJ_mass"); 

  h_SJ_mass_5TeV->Draw("HIST");
  gStyle->SetOptStat(0);
  h_SJ_mass_5TeV->SetTitle(";avg superjet mass [GeV];Events / 125 GeV");
  h_SJ_mass_5TeV->GetYaxis()->SetTitleSize(0.025);
  h_SJ_mass_5TeV->GetXaxis()->SetTitleSize(0.030);
  h_SJ_mass_5TeV->GetYaxis()->SetTitleOffset(2.05);
  h_SJ_mass_5TeV->Draw("HIST");

 TText *CMSLabel = new TText();
 CMSLabel-> SetNDC();
 CMSLabel -> SetTextFont(1);
 CMSLabel -> SetTextColor(1);
 CMSLabel -> SetTextSize(0.0385);
 CMSLabel -> SetTextAlign(22);
 CMSLabel -> SetTextAngle(0);
 CMSLabel -> DrawText(0.152, 0.92, "CMS");
 CMSLabel->Draw();

  TPaveText *pt = new TPaveText(0.85,0.50,0.57,0.62,"NDC");
  pt->SetTextSize(0.0275);
  pt->SetFillColor(0);
  pt->SetTextAlign(14);
  pt->Draw();
  
  const char *longstring = "M_{S_{uu}} = 5 TeV, M_{#chi} = 1.5 TeV";
  const char *longstring2 = "Simulated S_{uu} #rightarrow #chi #chi,";
  TLatex latex;
  latex.SetTextSize(0.025);
  latex.SetTextAlign(22);  //align at top
  latex.DrawLatex(3770,280,longstring2);
  latex.DrawLatex(3770,250,longstring);


 TText *simLabel = new TText();
 simLabel-> SetNDC();
 simLabel -> SetTextFont(52);
 simLabel -> SetTextColor(1);
 simLabel -> SetTextSize(0.024);
 simLabel -> SetTextAlign(22);
 simLabel -> SetTextAngle(0);
 simLabel -> DrawText(0.29, 0.915, "Simulation Preliminary");
 simLabel->Draw();

 TString lumistuff =  "(13 TeV)";
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);    
  latex.SetTextFont(42);
  latex.SetTextAlign(31); 
  latex.SetTextSize(0.030);    
  latex.DrawLatex(0.89,0.91,lumistuff);
  c1->SaveAs("/home/ethan/Documents/plots/nicePlotsForBOOST/h_SJ_mass_5TeV.png"); 

}

void makeSuu1DPlot8TeV()
{
  TFile *f7 = new TFile("/home/ethan/Documents/rootFiles/signalRootFiles/ClusteringAlgorithm_MSuu8TeV-MChi3TeV_cutbased_processed.root");
  TCanvas *c1 = new TCanvas("c1","",400,20, 1800,1600);
  c1->SetLeftMargin(0.12);
  TH1F *h_SJ_mass_8TeV =  (TH1F*)f7->Get("h_SJ_mass");

  h_SJ_mass_8TeV->Draw("HIST");
  gStyle->SetOptStat(0);
  h_SJ_mass_8TeV->SetTitle(";avg superjet mass [GeV];Events / 125 GeV");
  h_SJ_mass_8TeV->GetYaxis()->SetTitleSize(0.025);
  h_SJ_mass_8TeV->GetXaxis()->SetTitleSize(0.030);
  h_SJ_mass_8TeV->GetYaxis()->SetTitleOffset(2.05);
  h_SJ_mass_8TeV->Draw("HIST");

 TText *CMSLabel = new TText();
 CMSLabel-> SetNDC();
 CMSLabel -> SetTextFont(1);
 CMSLabel -> SetTextColor(1);
 CMSLabel -> SetTextSize(0.0385);
 CMSLabel -> SetTextAlign(22);
 CMSLabel -> SetTextAngle(0);
 CMSLabel -> DrawText(0.152, 0.92, "CMS");
 CMSLabel->Draw();

  TPaveText *pt = new TPaveText(0.18,0.60,0.44,0.72,"NDC");
  pt->SetTextSize(0.0275);
  pt->SetFillColor(0);
  pt->SetTextAlign(14);
  pt->Draw();
  
  const char *longstring = "M_{S_{uu}} = 8 TeV, M_{#chi} = 3 TeV";
  const char *longstring2 = "Simulated S_{uu} #rightarrow #chi #chi,";
  TLatex latex;
  latex.SetTextSize(0.025);
  latex.SetTextAlign(22);  //align at top
  latex.DrawLatex(1210,212,longstring2);
  latex.DrawLatex(1200,192,longstring);


 TText *simLabel = new TText();
 simLabel-> SetNDC();
 simLabel -> SetTextFont(52);
 simLabel -> SetTextColor(1);
 simLabel -> SetTextSize(0.024);
 simLabel -> SetTextAlign(22);
 simLabel -> SetTextAngle(0);
 simLabel -> DrawText(0.29, 0.915, "Simulation Preliminary");
 simLabel->Draw();

 TString lumistuff =  "(13 TeV)";
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);    
  latex.SetTextFont(42);
  latex.SetTextAlign(31); 
  latex.SetTextSize(0.030);    
  latex.DrawLatex(0.89,0.91,lumistuff);
  c1->SaveAs("/home/ethan/Documents/plots/nicePlotsForBOOST/h_SJ_mass_8TeV.png"); 

}


void makeSJvsdiSJMassPlot()
{

  TFile *f5 = new TFile("/home/ethan/Documents/rootFiles/signalRootFiles/ClusteringAlgorithm_MSuu5TeV-MChi1p5TeV_cutbased_processed.root");
  TCanvas *c1 = new TCanvas("c1","",400,20, 1800,1600);
  //gPad->SetLogy();
  c1->SetRightMargin(0.15);
  c1->SetLeftMargin(0.1);
  c1->SetTopMargin(0.08);
  double Suu8TeV_chi3TeV_SF = 1.74E-02;
  double Suu5TeV_chi1p5TeV_SF = 1.19E+00/5.;
  //c1->SetLeftMargin(0.15);
  //->SetBottomMargin(0.15);
  TH2F *h_MSJ_mass_vs_MdSJ_DT =  (TH2F*)f5->Get("h_MSJ_mass_vs_MdSJ_DT");   //QCD 2000 to Inf 
  h_MSJ_mass_vs_MdSJ_DT->Scale(Suu5TeV_chi1p5TeV_SF);
  h_MSJ_mass_vs_MdSJ_DT->SetTitle("; diSuperjet Mass (GeV); avg superjet Mass (GeV)");
  h_MSJ_mass_vs_MdSJ_DT->GetXaxis()->SetTitleSize(0.025);
  h_MSJ_mass_vs_MdSJ_DT->GetYaxis()->SetTitleSize(0.025);

  h_MSJ_mass_vs_MdSJ_DT->GetYaxis()->SetTitleOffset(2.05);
  h_MSJ_mass_vs_MdSJ_DT->GetXaxis()->SetTitleOffset(1.30);

  TText T; T.SetTextFont(30); T.SetTextAlign(22);
  gStyle->SetOptStat(0);
  h_MSJ_mass_vs_MdSJ_DT->Draw("colz");

   gPad->Update();
   TPaletteAxis *palette = (TPaletteAxis*)h_MSJ_mass_vs_MdSJ_DT->GetListOfFunctions()->FindObject("palette");

/*
   // the following lines move the palette. Choose the values you need for the position.
   palette->SetX1NDC(0.);
   palette->SetX2NDC(0.95);
   //palette->SetY1NDC(0.2);
   //palette->SetY2NDC(0.8);
   gPad->Modified();
   gPad->Update();
  */


  TPaveText *pt = new TPaveText(0.82,0.72,0.55,0.82,"NDC");
  pt->SetTextSize(0.0275);
  pt->SetFillColor(0);
  pt->SetTextAlign(14);
  pt->Draw();

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

  const char *longstring = "M_{S_{uu}} = 5 TeV, M_{#chi} = 1p5 TeV";
  const char *longstring2 = "Simulated S_{uu} #rightarrow #chi #chi,";

  TLatex latex;
  latex.SetTextSize(0.025);
  latex.SetTextAlign(22);  //align at top
  latex.DrawLatex(7800,4700,longstring);
  latex.DrawLatex(7800,5000,longstring2);

  TString lumistuff =  "59.83 fb^{-1} (13 TeV)";
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);    
  latex.SetTextFont(42);
  latex.SetTextAlign(31); 
  latex.SetTextSize(0.030);    
  latex.DrawLatex(0.83,0.89,lumistuff);
  c1->SaveAs("/home/ethan/Documents/plots/nicePlotsForBOOST/h_MSJ_vs_MdiSJ_Suu5TeV_chi1p5TeV.png"); 

}
void makeSJvsdiSJMassPlot_8TeV()
{

  TFile *f5 = new TFile("/home/ethan/Documents/rootFiles/signalRootFiles/ClusteringAlgorithm_MSuu8TeV-MChi3TeV_cutbased_processed.root");
  TCanvas *c1 = new TCanvas("c1","",400,20, 1800,1600);
  //gPad->SetLogy();
  c1->SetRightMargin(0.15);
  c1->SetLeftMargin(0.1);
  c1->SetTopMargin(0.08);

  double Suu8TeV_chi3TeV_SF = 1.74E-02;
  double Suu5TeV_chi1p5TeV_SF = 1.19E+00/5.;

  //c1->SetLeftMargin(0.15);
  //->SetBottomMargin(0.15);
  TH2F *h_MSJ_mass_vs_MdSJ_DT =  (TH2F*)f5->Get("h_MSJ_mass_vs_MdSJ_DT");   //QCD 2000 to Inf 
  h_MSJ_mass_vs_MdSJ_DT->Scale(Suu8TeV_chi3TeV_SF);
  h_MSJ_mass_vs_MdSJ_DT->SetTitle("; diSuperjet Mass (GeV); avg superjet Mass (GeV)");
  h_MSJ_mass_vs_MdSJ_DT->GetXaxis()->SetTitleSize(0.025);
  h_MSJ_mass_vs_MdSJ_DT->GetYaxis()->SetTitleSize(0.025);

  h_MSJ_mass_vs_MdSJ_DT->GetYaxis()->SetTitleOffset(2.05);
  h_MSJ_mass_vs_MdSJ_DT->GetXaxis()->SetTitleOffset(1.30);

  TText T; T.SetTextFont(30); T.SetTextAlign(22);
  gStyle->SetOptStat(0);
  h_MSJ_mass_vs_MdSJ_DT->Draw("colz");

   gPad->Update();
   TPaletteAxis *palette = (TPaletteAxis*)h_MSJ_mass_vs_MdSJ_DT->GetListOfFunctions()->FindObject("palette");

/*
   // the following lines move the palette. Choose the values you need for the position.
   palette->SetX1NDC(0.);
   palette->SetX2NDC(0.95);
   //palette->SetY1NDC(0.2);
   //palette->SetY2NDC(0.8);
   gPad->Modified();
   gPad->Update();
  */


  TPaveText *pt = new TPaveText(0.82,0.72,0.55,0.82,"NDC");
  pt->SetTextSize(0.0275);
  pt->SetFillColor(0);
  pt->SetTextAlign(14);
  pt->Draw();

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

  const char *longstring = "M_{S_{uu}} = 5 TeV, M_{#chi} = 1p5 TeV";
  const char *longstring2 = "Simulated S_{uu} #rightarrow #chi #chi,";

  TLatex latex;
  latex.SetTextSize(0.025);
  latex.SetTextAlign(22);  //align at top
  latex.DrawLatex(7800,4700,longstring);
  latex.DrawLatex(7800,5000,longstring2);

  TString lumistuff =  "59.83 fb^{-1} (13 TeV)";
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);    
  latex.SetTextFont(42);
  latex.SetTextAlign(31); 
  latex.SetTextSize(0.030);    
  latex.DrawLatex(0.83,0.89,lumistuff);
  c1->SaveAs("/home/ethan/Documents/plots/nicePlotsForBOOST/h_MSJ_vs_MdiSJ_Suu8TeV_chi3TeV.png"); 

 
}
void makeSensitivityPlot8TeV()
{
  //int ncolors = 52;
  //int colors =0;
  TFile *f5 = new TFile("/home/ethan/Documents/rootFiles/processedRootFiles/stackedPlots_output.root");
  TCanvas *c1 = new TCanvas("c1","",400,20, 1800,1600);
  c1->SetRightMargin(0.15);
  c1->SetLeftMargin(0.1);
  c1->SetTopMargin(0.08);

  /*
    double stops[5] = {0.00, 0.34, 0.61, 0.84, 1.00};
    double red[5]   = {1.00, 0.84, 0.61, 0.34, 0.00};
    double green[5] = {1.00, 0.84, 0.61, 0.34, 0.00};
    double blue[5]  = {1.00, 0.84, 0.61, 0.34, 0.00};
*/


  Int_t MyPalette[100];

  Double_t Red[]    = {1.00, 0.84, 0.61, 0.34, 0.00};
  Double_t Green[]  = {1.00, 0.84, 0.61, 0.34, 0.00};
  Double_t Blue[]   = {1.00, 0.84, 0.61, 0.34, 0.00};
  Double_t Length[] = {0.00, 0.34, 0.61, 0.84, 1.00};
  Int_t FI = TColor::CreateGradientColorTable(5, Length, Red, Green, Blue, 100);
  //int npoints = sizeof(stops);
  //int ncontours=999;
  //gStyle->SetNumberContours(ncontours);
  //Int_t FI = TColor::CreateGradientColorTable(npoints, stops, red, green, blue, 100);



  for (int i=0;i<100;i++) MyPalette[i] = FI+i;
  gStyle->SetPalette(100, MyPalette);
  //c1->SetLeftMargin(0.15);
  //->SetBottomMargin(0.15);
  TH2F *h_MSJ_mass_vs_MdSJ_SR_Suu8TeV_chi3Tev_sensitivity =  (TH2F*)f5->Get("h_MSJ_mass_vs_MdSJ_SR_Suu8TeV_chi3Tev_sensitivity");
  h_MSJ_mass_vs_MdSJ_SR_Suu8TeV_chi3Tev_sensitivity->SetTitle("Expected Signal Sensitivity; diSuperjet Mass (GeV); avg superjet Mass (GeV)");
  h_MSJ_mass_vs_MdSJ_SR_Suu8TeV_chi3Tev_sensitivity->GetXaxis()->SetTitleSize(0.025);
  h_MSJ_mass_vs_MdSJ_SR_Suu8TeV_chi3Tev_sensitivity->GetYaxis()->SetTitleSize(0.025);

  h_MSJ_mass_vs_MdSJ_SR_Suu8TeV_chi3Tev_sensitivity->GetYaxis()->SetTitleOffset(2.05);
  h_MSJ_mass_vs_MdSJ_SR_Suu8TeV_chi3Tev_sensitivity->GetXaxis()->SetTitleOffset(1.30);

  //gPad->SetLogz();

  //gStyle->SetPalette(ncolors,colors);

  TText T; T.SetTextFont(30); T.SetTextAlign(22);
  gStyle->SetOptStat(0);
  h_MSJ_mass_vs_MdSJ_SR_Suu8TeV_chi3Tev_sensitivity->Draw("colz");

   gPad->Update();
   TPaletteAxis *palette = (TPaletteAxis*)h_MSJ_mass_vs_MdSJ_SR_Suu8TeV_chi3Tev_sensitivity->GetListOfFunctions()->FindObject("palette");

/*
   // the following lines move the palette. Choose the values you need for the position.
   palette->SetX1NDC(0.);
   palette->SetX2NDC(0.95);
   //palette->SetY1NDC(0.2);
   //palette->SetY2NDC(0.8);
   gPad->Modified();
   gPad->Update();
  */


  TPaveText *pt = new TPaveText(0.15,0.52,0.45,0.72,"NDC");
  pt->SetTextSize(0.0275);
  pt->SetFillColor(0);
  pt->SetTextAlign(14);
  pt->Draw();

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

  const char *longstring = "M_{S_{uu}} = 5 TeV, M_{#chi} = 1.5 TeV,";
  const char *longstring2 = "Simulated S_{uu} #rightarrow #chi #chi,";
  const char *longstring3 = "scale : #frac{nSig}{#sqrt{BR}},";

  TLatex latex;
  latex.SetTextSize(0.025);
  latex.SetTextAlign(22);  //align at top
  latex.DrawLatex(2800,4250,longstring);
  latex.DrawLatex(2800,3800,longstring2);
  latex.DrawLatex(2800,3350,longstring3);

  TString lumistuff =  "(13 TeV)";
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);    
  latex.SetTextFont(42);
  latex.SetTextAlign(31); 
  latex.SetTextSize(0.030);    
  latex.DrawLatex(0.82,0.89,lumistuff);
  c1->SaveAs("/home/ethan/Documents/plots/nicePlotsForBOOST/h_2D_sensitivity_Suu8TeV_chi3TeV.png"); 

 
}
void makeSensitivityPlot5TeV()
{
  int ncolors = 52, colors=0;
  TFile *f5 = new TFile("/home/ethan/Documents/rootFiles/processedRootFiles/stackedPlots_output.root");
  TCanvas *c1 = new TCanvas("c1","",400,20, 1800,1600);
  //gPad->SetLogy();
  c1->SetRightMargin(0.17);
  c1->SetLeftMargin(0.1);
  c1->SetTopMargin(0.08);
  //c1->SetLeftMargin(0.15);
  //->SetBottomMargin(0.15);
/*
  Int_t MyPalette[100];

  Double_t Red[]    = {1.00, 0.84, 0.61, 0.34, 0.00};
  Double_t Green[]  = {1.00, 0.84, 0.61, 0.34, 0.00};
  Double_t Blue[]   = {1.00, 0.84, 0.61, 0.34, 0.00};
  Double_t Length[] = {0.00, 0.34, 0.61, 0.84, 1.00};
  Int_t FI = TColor::CreateGradientColorTable(5, Length, Red, Green, Blue, 100);

  */
  TH2F *h_MSJ_mass_vs_MdSJ_SR_Suu8TeV_chi3Tev_sensitivity =  (TH2F*)f5->Get("h_MSJ_mass_vs_MdSJ_SR_Suu5TeV_chi1p5Tev_sensitivity");
  h_MSJ_mass_vs_MdSJ_SR_Suu8TeV_chi3Tev_sensitivity->SetTitle("; diSuperjet Mass (GeV); avg superjet Mass (GeV);exp. # of signal events / sqrt( multijet + tt exp. events)");
  h_MSJ_mass_vs_MdSJ_SR_Suu8TeV_chi3Tev_sensitivity->GetXaxis()->SetTitleSize(0.025);
  h_MSJ_mass_vs_MdSJ_SR_Suu8TeV_chi3Tev_sensitivity->GetYaxis()->SetTitleSize(0.025);

  h_MSJ_mass_vs_MdSJ_SR_Suu8TeV_chi3Tev_sensitivity->GetYaxis()->SetTitleOffset(2.05);
  h_MSJ_mass_vs_MdSJ_SR_Suu8TeV_chi3Tev_sensitivity->GetXaxis()->SetTitleOffset(1.30);
  h_MSJ_mass_vs_MdSJ_SR_Suu8TeV_chi3Tev_sensitivity->GetZaxis()->SetTitleOffset(1.3);

  //gStyle->SetPalette(ncolors,colors);

  TText T; T.SetTextFont(30); T.SetTextAlign(22);
  gStyle->SetOptStat(0);
  h_MSJ_mass_vs_MdSJ_SR_Suu8TeV_chi3Tev_sensitivity->Draw("colz");

   gPad->Update();
   TPaletteAxis *palette = (TPaletteAxis*)h_MSJ_mass_vs_MdSJ_SR_Suu8TeV_chi3Tev_sensitivity->GetListOfFunctions()->FindObject("palette");





/*
   // the following lines move the palette. Choose the values you need for the position.
   palette->SetX1NDC(0.);
   palette->SetX2NDC(0.95);
   //palette->SetY1NDC(0.2);
   //palette->SetY2NDC(0.8);
   gPad->Modified();
   gPad->Update();
  */

/*
  TPaveText *pt = new TPaveText(0.82,0.62,0.55,0.82,"NDC");
  pt->SetTextSize(0.0275);
  pt->SetFillColor(0);
  pt->SetTextAlign(14);
  pt->Draw();
*/
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

  const char *longstring = "M_{S_{uu}} = 5 TeV, M_{#chi} = 1.5 TeV,";
  const char *longstring2 = "Simulated S_{uu} #rightarrow #chi #chi,";
//  const char *longstring3 = "scale : #frac{nSig}{#sqrt{BR}},";

  TLatex latex;
  latex.SetTextSize(0.025);
  latex.SetTextAlign(22);  //align at top
  latex.DrawLatex(7800,4620,longstring);
  latex.DrawLatex(7800,5000,longstring2);
  //latex.DrawLatex(7800,4100,longstring3);
  TString lumistuff =  "(13 TeV)";
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);    
  latex.SetTextFont(42);
  latex.SetTextAlign(31); 
  latex.SetTextSize(0.030);    
  latex.DrawLatex(0.82,0.89,lumistuff);
  c1->SaveAs("/home/ethan/Documents/plots/nicePlotsForBOOST/h_2D_sensitivity_Suu5TeV_chi1p5TeV.png"); 

 
}



void makeSRBRStackPlot()
{

  TFile *f5 = new TFile("/home/ethan/Documents/rootFiles/processedRootFiles/stackedPlots_output.root");
  TCanvas *c1 = new TCanvas("c1","",400,20, 1800,1600);
  //gPad->SetLogy();
  c1->SetRightMargin(0.15);
  c1->SetLeftMargin(0.1);
  c1->SetTopMargin(0.08);

  c1->SetLeftMargin(0.15);
  //->SetBottomMargin(0.15);
  TH1F *h_SJ_mass_TTbar        =  (TH1F*)f5->Get("h_SJ_mass_TTbar");
  TH1F *h_SJ_mass_QCD_combined =  (TH1F*)f5->Get("h_SJ_mass_QCD_combined");

  TText T; T.SetTextFont(30); T.SetTextAlign(22);
  gStyle->SetOptStat(0);

  THStack *hs_BR_SR = new THStack("hs_BR_SR",";avg superjet Mass (GeV);Events / 100 GeV");
  h_SJ_mass_QCD_combined->SetFillColor(kRed);
  h_SJ_mass_QCD_combined->GetXaxis()->SetTitleSize(0.025);
  h_SJ_mass_TTbar->SetFillColor(kYellow);
  hs_BR_SR->Add(h_SJ_mass_QCD_combined);
  hs_BR_SR->Add(h_SJ_mass_TTbar);
  //hs_BR_SR->SetTitle("MC SR Background Contributions; avg superjet Mass (GeV);Events / 125 GeV");
  //hs_BR_SR->GetXaxis()->SetTitleSize(0.025);
  //hs_BR_SR->GetYaxis()->SetTitleSize(0.025);

  //hs_BR_SR->GetYaxis()->SetTitleOffset(2.05);
  //hs_BR_SR->GetXaxis()->SetTitleOffset(1.30);
  hs_BR_SR->Draw("HIST");


   auto legend6 = new TLegend(0.4,0.25,0.65,0.4);
   legend6->SetHeader("","C"); // option "C" allows to center the header
   legend6->AddEntry(h_SJ_mass_TTbar,"TTToHadronic","f");
   legend6->AddEntry(h_SJ_mass_QCD_combined,"QCD","f");
   legend6->Draw();
/*
  TPaveText *pt = new TPaveText(0.82,0.62,0.55,0.82,"NDC");
  pt->SetTextSize(0.0275);
  pt->SetFillColor(0);
  pt->SetTextAlign(14);
  pt->Draw();
*/
 TText *CMSLabel = new TText();
 CMSLabel-> SetNDC();
 CMSLabel -> SetTextFont(1);
 CMSLabel -> SetTextColor(1);
 CMSLabel -> SetTextSize(0.0385);
 CMSLabel -> SetTextAlign(22);
 CMSLabel -> SetTextAngle(0);
 CMSLabel -> DrawText(0.19, 0.94, "CMS");
 CMSLabel->Draw();

 TText *simLabel = new TText();
 simLabel-> SetNDC();
 simLabel -> SetTextFont(52);
 simLabel -> SetTextColor(1);
 simLabel -> SetTextSize(0.024);
 simLabel -> SetTextAlign(22);
 simLabel -> SetTextAngle(0);
 simLabel -> DrawText(0.33, 0.937, "Simulation Preliminary");
 simLabel->Draw();

  TLatex latex;

  const char *longstring = "SR MC Backgrounds";

  latex.SetTextSize(0.025);
  latex.SetTextAlign(22);  //align at top
  latex.DrawLatex(1680,2400,longstring);
/*

  latex.DrawLatex(7800,5000,longstring2);

*/
  TString lumistuff =  "(13 TeV)";
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);    
  latex.SetTextFont(42);
  latex.SetTextAlign(31); 
  latex.SetTextSize(0.030);    
  latex.DrawLatex(0.82,0.89,lumistuff);
  c1->SaveAs("/home/ethan/Documents/plots/nicePlotsForBOOST/h_SR_BR_stack.png"); 

 
}

void makeCRSignalContaminationPlot()
{

  TFile *f5 = new TFile("/home/ethan/Documents/rootFiles/processedRootFiles/stackedPlots_output.root");
  TCanvas *c1 = new TCanvas("c1","",400,20, 1800,1600);
  //gPad->SetLogy();
  c1->SetRightMargin(0.15);
  c1->SetLeftMargin(0.1);
  c1->SetTopMargin(0.08);

  //c1->SetLeftMargin(0.15);
  //->SetBottomMargin(0.15);
  TH2F *h_MSJ_mass_vs_MdSJ_CR_sig_contamination =  (TH2F*)f5->Get("h_MSJ_mass_vs_MdSJ_CR_sig_contamination");
  h_MSJ_mass_vs_MdSJ_CR_sig_contamination->SetTitle("Expected Signal Contamination; diSuperjet Mass (GeV); avg superjet Mass (GeV)");
  h_MSJ_mass_vs_MdSJ_CR_sig_contamination->GetXaxis()->SetTitleSize(0.025);
  h_MSJ_mass_vs_MdSJ_CR_sig_contamination->GetYaxis()->SetTitleSize(0.025);

  h_MSJ_mass_vs_MdSJ_CR_sig_contamination->GetYaxis()->SetTitleOffset(2.05);
  h_MSJ_mass_vs_MdSJ_CR_sig_contamination->GetXaxis()->SetTitleOffset(1.30);

  TText T; T.SetTextFont(30); T.SetTextAlign(22);
  gStyle->SetOptStat(0);
  h_MSJ_mass_vs_MdSJ_CR_sig_contamination->Draw("colz");

   gPad->Update();
   TPaletteAxis *palette = (TPaletteAxis*)h_MSJ_mass_vs_MdSJ_CR_sig_contamination->GetListOfFunctions()->FindObject("palette");

  TPaveText *pt = new TPaveText(0.82,0.62,0.55,0.82,"NDC");
  pt->SetTextSize(0.0275);
  pt->SetFillColor(0);
  pt->SetTextAlign(14);
  pt->Draw();

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

  const char *longstring = "M_{S_{uu}} = 5 TeV, M_{#chi} = 1.5 TeV,";
  const char *longstring2 = "Simulated S_{uu} #rightarrow #chi #chi,";
  const char *longstring3 = "scale : #frac{nBR + nSig}{nBR}";

  TLatex latex;
  latex.SetTextSize(0.025);
  latex.SetTextAlign(22);  //align at top
  latex.DrawLatex(7800,4520,longstring);
  latex.DrawLatex(7800,5000,longstring2);
  latex.DrawLatex(7800,4100,longstring3);
  TString lumistuff =  "(13 TeV)";
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);    
  latex.SetTextFont(42);
  latex.SetTextAlign(31); 
  latex.SetTextSize(0.030);    
  latex.DrawLatex(0.82,0.89,lumistuff);
  c1->SaveAs("/home/ethan/Documents/plots/nicePlotsForBOOST/h_CR_sigContamination_Suu5TeV_chi1p5TeV.png"); 

 
}

void makeSRNNSensitivityPlot_5TeV()
{

  TFile *f5 = new TFile("/home/ethan/Documents/rootFiles/processedRootFiles/stackedPlots_output.root");
  TCanvas *c1 = new TCanvas("c1","",400,20, 1800,1600);
  //gPad->SetLogy();
  c1->SetRightMargin(0.15);
  c1->SetLeftMargin(0.1);
  c1->SetTopMargin(0.08);

  //c1->SetLeftMargin(0.15);
  //->SetBottomMargin(0.15);
  TH2F *h_MSJ_mass_vs_MdSJ_SR_Suu5TeV_chi1p5Tev_sensitivity =  (TH2F*)f5->Get("h_MSJ_mass_vs_MdSJ_SR_NN_Suu5TeV_chi1p5Tev_sensitivity");
  h_MSJ_mass_vs_MdSJ_SR_Suu5TeV_chi1p5Tev_sensitivity->SetTitle("Expected Signal Sensitivity (NN Approach); diSuperjet Mass (GeV); avg superjet Mass (GeV)");
  h_MSJ_mass_vs_MdSJ_SR_Suu5TeV_chi1p5Tev_sensitivity->GetXaxis()->SetTitleSize(0.025);
  h_MSJ_mass_vs_MdSJ_SR_Suu5TeV_chi1p5Tev_sensitivity->GetYaxis()->SetTitleSize(0.025);

  h_MSJ_mass_vs_MdSJ_SR_Suu5TeV_chi1p5Tev_sensitivity->GetYaxis()->SetTitleOffset(2.05);
  h_MSJ_mass_vs_MdSJ_SR_Suu5TeV_chi1p5Tev_sensitivity->GetXaxis()->SetTitleOffset(1.30);

  TText T; T.SetTextFont(30); T.SetTextAlign(22);
  gStyle->SetOptStat(0);
  h_MSJ_mass_vs_MdSJ_SR_Suu5TeV_chi1p5Tev_sensitivity->Draw("colz");

   gPad->Update();
   TPaletteAxis *palette = (TPaletteAxis*)h_MSJ_mass_vs_MdSJ_SR_Suu5TeV_chi1p5Tev_sensitivity->GetListOfFunctions()->FindObject("palette");

  TPaveText *pt = new TPaveText(0.82,0.62,0.55,0.82,"NDC");
  pt->SetTextSize(0.0275);
  pt->SetFillColor(0);
  pt->SetTextAlign(14);
  pt->Draw();

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

  const char *longstring = "M_{S_{uu}} = 5 TeV, M_{#chi} = 1.5 TeV,";
  const char *longstring2 = "Simulated S_{uu} #rightarrow #chi #chi,";
  const char *longstring3 = "scale : #frac{nSig}{#sqrt{BR}},";

  TLatex latex;
  latex.SetTextSize(0.025);
  latex.SetTextAlign(22);  //align at top
  latex.DrawLatex(7800,4520,longstring);
  latex.DrawLatex(7800,5000,longstring2);
  latex.DrawLatex(7800,4100,longstring3);
  TString lumistuff =  "(13 TeV)";
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);    
  latex.SetTextFont(42);
  latex.SetTextAlign(31); 
  latex.SetTextSize(0.030);    
  latex.DrawLatex(0.82,0.89,lumistuff);
  c1->SaveAs("/home/ethan/Documents/plots/nicePlotsForBOOST/h_2D_sensitivity_NN_Suu5TeV_chi1p5TeV.png"); 

}
void makeSRNNSensitivityPlot_8TeV()
{

  TFile *f5 = new TFile("/home/ethan/Documents/rootFiles/processedRootFiles/stackedPlots_output.root");
  TCanvas *c1 = new TCanvas("c1","",400,20, 1800,1600);
  //gPad->SetLogy();
  c1->SetRightMargin(0.15);
  c1->SetLeftMargin(0.1);
  c1->SetTopMargin(0.08);

  //c1->SetLeftMargin(0.15);
  //->SetBottomMargin(0.15);
  TH2F *h_MSJ_mass_vs_MdSJ_SR_Suu8TeV_chi3Tev_sensitivity =  (TH2F*)f5->Get("h_MSJ_mass_vs_MdSJ_SR_NN_Suu8TeV_chi3Tev_sensitivity");
  h_MSJ_mass_vs_MdSJ_SR_Suu8TeV_chi3Tev_sensitivity->SetTitle("Expected Signal Sensitivity (NN Approach); diSuperjet Mass (GeV); avg superjet Mass (GeV)");
  h_MSJ_mass_vs_MdSJ_SR_Suu8TeV_chi3Tev_sensitivity->GetXaxis()->SetTitleSize(0.025);
  h_MSJ_mass_vs_MdSJ_SR_Suu8TeV_chi3Tev_sensitivity->GetYaxis()->SetTitleSize(0.025);

  h_MSJ_mass_vs_MdSJ_SR_Suu8TeV_chi3Tev_sensitivity->GetYaxis()->SetTitleOffset(2.05);
  h_MSJ_mass_vs_MdSJ_SR_Suu8TeV_chi3Tev_sensitivity->GetXaxis()->SetTitleOffset(1.30);

  TText T; T.SetTextFont(30); T.SetTextAlign(22);
  gStyle->SetOptStat(0);
  h_MSJ_mass_vs_MdSJ_SR_Suu8TeV_chi3Tev_sensitivity->Draw("colz");

   gPad->Update();
   TPaletteAxis *palette = (TPaletteAxis*)h_MSJ_mass_vs_MdSJ_SR_Suu8TeV_chi3Tev_sensitivity->GetListOfFunctions()->FindObject("palette");

  TPaveText *pt = new TPaveText(0.82,0.62,0.55,0.82,"NDC");
  pt->SetTextSize(0.0275);
  pt->SetFillColor(0);
  pt->SetTextAlign(14);
  pt->Draw();

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

  const char *longstring = "M_{S_{uu}} = 8 TeV, M_{#chi} = 3 TeV,";
  const char *longstring2 = "Simulated S_{uu} #rightarrow #chi #chi,";
  const char *longstring3 = "scale : #frac{nSig}{#sqrt{BR}},";

  TLatex latex;
  latex.SetTextSize(0.025);
  latex.SetTextAlign(22);  //align at top
  latex.DrawLatex(7800,4520,longstring);
  latex.DrawLatex(7800,5000,longstring2);
  latex.DrawLatex(7800,4100,longstring3);
  TString lumistuff =  "(13 TeV)";
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);    
  latex.SetTextFont(42);
  latex.SetTextAlign(31); 
  latex.SetTextSize(0.030);    
  latex.DrawLatex(0.82,0.89,lumistuff);
  c1->SaveAs("/home/ethan/Documents/plots/nicePlotsForBOOST/h_2D_sensitivity_NN_Suu8TeV_chi3TeV.png"); 

}
void makeSuu1DPlotMultipleMasses()
{
  TFile *f6 = new TFile("/home/ethan/Documents/rootFiles/signalRootFiles/ClusteringAlgorithm_MSuu4TeV-MChi1TeV_cutbased_processed.root");   //need processed 4 TeV Suu and 1 TeV Suu 
  TFile *f7 = new TFile("/home/ethan/Documents/rootFiles/signalRootFiles/ClusteringAlgorithm_MSuu5TeV-MChi1p5TeV_cutbased_processed.root");   //need processed 6 TeV Suu and 1.5 TeV Suu 
  TFile *f8 = new TFile("/home/ethan/Documents/rootFiles/signalRootFiles/ClusteringAlgorithm_MSuu5TeV-MChi2TeV_cutbased_processed.root");   //need processed 8 TeV Suu and 2 TeV Suu 
  TFile *f9 = new TFile("/home/ethan/Documents/rootFiles/signalRootFiles/ClusteringAlgorithm_MSuu8TeV-MChi3TeV_cutbased_processed.root");   //need processed 8 TeV Suu and 3 TeV Suu 

  TCanvas *c1 = new TCanvas("c1","",400,20, 1800,1600);
  //gPad->SetLogy();
  //c1->SetRightMargin(0.15);
  c1->SetLeftMargin(0.12);
  //c1->SetTopMargin(0.08);

  //c1->SetLeftMargin(0.15);
  //->SetBottomMargin(0.15);
  TH1F *h_SJ_mass_1TeV =  (TH1F*)f6->Get("h_SJ_mass"); 
  TH1F *h_SJ_mass_1p5TeV =  (TH1F*)f7->Get("h_SJ_mass"); 
  TH1F *h_SJ_mass_2TeV =  (TH1F*)f8->Get("h_SJ_mass"); 
  TH1F *h_SJ_mass_3TeV =  (TH1F*)f9->Get("h_SJ_mass"); 

  h_SJ_mass_1TeV->Draw("HIST");
  gStyle->SetOptStat(0);
  h_SJ_mass_1TeV->SetTitle(";avg superjet mass [GeV];Events / 125 GeV");
  h_SJ_mass_1TeV->GetYaxis()->SetTitleSize(0.025);
  h_SJ_mass_1TeV->GetXaxis()->SetTitleSize(0.030);
  h_SJ_mass_1TeV->GetYaxis()->SetTitleOffset(2.05);
  h_SJ_mass_1TeV->GetXaxis()->SetRangeUser(0., 4000.);


  h_SJ_mass_1TeV->SetLineStyle(1);
  h_SJ_mass_1p5TeV->SetLineStyle(4);
  h_SJ_mass_2TeV->SetLineStyle(9);
  h_SJ_mass_3TeV->SetLineStyle(10);

  h_SJ_mass_1TeV->SetLineColor(kOrange);
  h_SJ_mass_1p5TeV->SetLineColor(kGreen);
  h_SJ_mass_2TeV->SetLineColor(kBlue);
  h_SJ_mass_3TeV->SetLineColor(kRed);

  h_SJ_mass_1TeV->SetLineWidth(3);
  h_SJ_mass_1p5TeV->SetLineWidth(7);
  h_SJ_mass_2TeV->SetLineWidth(4);
  h_SJ_mass_3TeV->SetLineWidth(4);

  h_SJ_mass_1TeV->Draw("HIST");
  h_SJ_mass_1p5TeV->Draw("SAME");
  h_SJ_mass_2TeV->Draw("SAME");
  h_SJ_mass_3TeV->Draw("SAME");

   auto legend6 = new TLegend(0.6,0.65,0.85,0.8);
   legend6->SetHeader("","C"); // option "C" allows to center the header
   legend6->AddEntry(h_SJ_mass_1TeV,"M_{S_{uu}}=4 TeV, M_{#chi}=1 TeV","f");
   legend6->AddEntry(h_SJ_mass_1p5TeV,"M_{S_{uu}}=6 TeV, M_{#chi}=1.5 TeV","f");
   legend6->AddEntry(h_SJ_mass_2TeV,"M_{S_{uu}}=8 TeV, M_{#chi}=2 TeV","f");
   legend6->AddEntry(h_SJ_mass_3TeV,"M_{S_{uu}}=8 TeV, M_{#chi}=3 TeV","f");

   legend6->Draw();

 TText *CMSLabel = new TText();
 CMSLabel-> SetNDC();
 CMSLabel -> SetTextFont(1);
 CMSLabel -> SetTextColor(1);
 CMSLabel -> SetTextSize(0.0385);
 CMSLabel -> SetTextAlign(22);
 CMSLabel -> SetTextAngle(0);
 CMSLabel -> DrawText(0.152, 0.92, "CMS");
 CMSLabel->Draw();



/*
  TPaveText *pt = new TPaveText(0.85,0.50,0.57,0.62,"NDC");
  pt->SetTextSize(0.0275);
  pt->SetFillColor(0);
  pt->SetTextAlign(14);
  pt->Draw();
  
  const char *longstring = "M_{S_{uu}} = 5 TeV, M_{#chi} = 1.5 TeV";
  const char *longstring2 = "Simulated S_{uu} #rightarrow #chi #chi,";
  TLatex latex;
  latex.SetTextSize(0.025);
  latex.SetTextAlign(22);  //align at top
  latex.DrawLatex(3770,280,longstring2);
  latex.DrawLatex(3770,250,longstring);
*/
  TLatex latex;

 TText *simLabel = new TText();
 simLabel-> SetNDC();
 simLabel -> SetTextFont(52);
 simLabel -> SetTextColor(1);
 simLabel -> SetTextSize(0.024);
 simLabel -> SetTextAlign(22);
 simLabel -> SetTextAngle(0);
 simLabel -> DrawText(0.29, 0.915, "Simulation Preliminary");
 simLabel->Draw();

 TString lumistuff =  "(13 TeV)";
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);    
  latex.SetTextFont(42);
  latex.SetTextAlign(31); 
  latex.SetTextSize(0.030);    
  latex.DrawLatex(0.89,0.91,lumistuff);
  c1->SaveAs("/home/ethan/Documents/plots/nicePlotsForBOOST/h_SJ_mass_all.png"); 

}
void makeNicePlot()
{
  //make1DGenSJPlot();
  //make2DGenSJPlot();
  //makeZprimeSJMassPlot();
  //makeCutflowPlot();
  //makeSuu1DPlot5TeV();
  //makeSuu1DPlot8TeV();
  //makeSJvsdiSJMassPlot();
  //makeSensitivityPlot5TeV();
  //makeSensitivityPlot8TeV();
  //makeSRBRStackPlot();
  //makeCRSignalContaminationPlot();
  //makeSRNNSensitivityPlot_5TeV();
  //makeSRNNSensitivityPlot_8TeV();
  //makeSJvsdiSJMassPlot_8TeV();
  //makeSJvsdiSJMassPlot();
  makeSuu1DPlotMultipleMasses();
}


// also want 2D background nice plot
#include <iostream>
#include <string>
#include "TLorentzVector.h"
#include "TRatioPlot.h"
#include "THStack.h"
using namespace std;

const char *appendName(std::string plotName)
{
  //std::string sampleName = ;
  const char *outputString = ("M_Suu = 4 TeV, M_chi = 1.5 TeV "+ plotName).c_str();//+" "+plotName).c_str();

  return outputString;
}

void makeSuperimposePlot()
{

  TFile *f1 = new TFile("clustAlgBR_ttbar_processed_.root");
  TFile *f2 = new TFile("processed_QCD/HT1000to1500/clustAlg_QCD_HT1000to1500_processed.root");
  TFile *f3 = new TFile("processed_QCD/HT1500to2000/clustAlg_QCD_HT1500to2000_processed.root");
  TFile *f4 = new TFile("processed_QCD/HT2000toInf/clustAlg_QCD_HT2000toInf_processed.root");
  TFile *f5 = new TFile("clusteringProcessed/ClusteringAlgorithm_Suu7TeV_chi2TeV_ALLDECAY_processed.root");
  TFile outFile("stackPlots_output.root","RECREATE");
  TCanvas *c1 = new TCanvas("c1","",400,20, 1500,1500);
  gPad->SetLogy();



////////////////Change Values Here//////////////////
////////////////////////////////////////////////////
////////////////////////////////////////////////////
  std::string sampleName    = "M_{S_{uu}} = 7 TeV"; 
  std::string sampleName2    = "M_{#chi} = 2 TeV";
  std::string sampleSuuMass = "7TeV";
////////////////////////////////////////////////////
////////////////////////////////////////////////////
////////////////////////////////////////////////////


  const char * sampleNameChar = sampleName.c_str();
  const char * sampleNameChar2 = sampleName2.c_str();

  THStack *hs_superjet_mass = new THStack("hs_superjet_mass",";;Events / 100 GeV");
  hs_superjet_mass->SetMaximum(500.);
  TH1F *h_ttbar_superJet_mass =  (TH1F*)f1->Get("h_superJet_mass");   //ttbar
  h_ttbar_superJet_mass->SetFillColor(kRed);
  hs_superjet_mass->Add(h_ttbar_superJet_mass);

  TH1F *h_QCD_1000to1500_superJet_mass =    (TH1F*)f2->Get("h_superJet_mass");   //qcd 1000to1500
  h_QCD_1000to1500_superJet_mass->SetFillColor(kYellow);
  hs_superjet_mass->Add(h_QCD_1000to1500_superJet_mass);

  TH1F *h_QCD_1500to2000_superJet_mass = (TH1F*)f3->Get("h_superJet_mass");   //qcd 1500to2000
  h_QCD_1500to2000_superJet_mass->SetFillColor(kCyan);
  hs_superjet_mass->Add(h_QCD_1500to2000_superJet_mass);

  TH1F *h_QCD_2000toInf_superJet_mass = (TH1F*)f4->Get("h_superJet_mass");   //qcd 2000toInf
  h_QCD_2000toInf_superJet_mass->SetFillColor(kBlue);
  hs_superjet_mass->Add(h_QCD_2000toInf_superJet_mass);

  TH1F *h_signal_superJet_mass = (TH1F*)f5->Get("h_superJet_mass");   //qcd 2000toInf
  h_signal_superJet_mass->SetFillColor(kOrange);
  h_signal_superJet_mass->SetMarkerStyle(22);
  h_signal_superJet_mass->SetMarkerSize(3);

  TText T; T.SetTextFont(30); T.SetTextAlign(22);
  gStyle->SetOptStat(0);
  hs_superjet_mass->Draw("HIST");
  hs_superjet_mass->GetYaxis()->SetTitleOffset(1.25);

  h_signal_superJet_mass->Draw("SAME");
  TLegend *legend = new TLegend(1.0,0.7,0.55,0.9);
  legend->AddEntry(h_QCD_1000to1500_superJet_mass,"QCD (1000 < H_{T} < 1500 GeV)","f");
  legend->AddEntry(h_QCD_1500to2000_superJet_mass,"QCD (1500 < H_{T} < 2000 GeV)","f");
  legend->AddEntry(h_QCD_2000toInf_superJet_mass,"QCD (2000 GeV < H_{T})","f");
  legend->AddEntry(h_ttbar_superJet_mass,"t#bar{t} Hadronic","f");
  legend->AddEntry(h_signal_superJet_mass,"S_{uu} #rightarrow #chi #chi","p");
  legend->Draw();





/////////////////Nice plot stuff///////////////////////////
///////////////////////////////////////////////////////////



  TPaveText *pt = new TPaveText(0.9,0.55,0.70,0.65,"NDC");
  pt->SetTextSize(0.032);
  pt->SetFillColor(0);
  pt->SetTextAlign(14);
  pt->AddText(sampleNameChar);
  pt->Draw();
  TPaveText *pt2 = new TPaveText(0.9,0.45,0.70,0.55,"NDC");
  pt2->SetTextSize(0.032);
  pt2->SetFillColor(0);
  pt2->SetTextAlign(14);
  pt2->AddText(sampleNameChar2);
  pt2->Draw();

 TText *CMSLabel = new TText();
 CMSLabel-> SetNDC();
 CMSLabel -> SetTextFont(1);
 CMSLabel -> SetTextColor(1);
 CMSLabel -> SetTextSize(0.0425);
 CMSLabel -> SetTextAlign(22);
 CMSLabel -> SetTextAngle(0);
 CMSLabel -> DrawText(0.145, 0.93, "CMS");
 CMSLabel->Draw();

 TText *simLabel = new TText();
 simLabel-> SetNDC();
 simLabel -> SetTextFont(52);
 simLabel -> SetTextColor(1);
 simLabel -> SetTextSize(0.028);
 simLabel -> SetTextAlign(22);
 simLabel -> SetTextAngle(0);
 simLabel -> DrawText(0.3225, 0.93, "Simulation Preliminary");
 simLabel->Draw();

 TString lumistuff =  "59.83 fb^{-1} (13 TeV)";

  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);    
  latex.SetTextFont(42);
  latex.SetTextAlign(31); 
  latex.SetTextSize(0.045);    
  latex.DrawLatex(0.935,0.92,lumistuff);

 TText *xlabelSJ = new TText();
 xlabelSJ-> SetNDC();
 //xlabel -> SetTextFont(52);
 xlabelSJ -> SetTextColor(1);
 xlabelSJ -> SetTextSize(0.038);
 xlabelSJ -> SetTextAlign(22);
 xlabelSJ -> SetTextAngle(0);
 xlabelSJ -> DrawText(0.78, 0.03, "superjet mass [GeV]");
 xlabelSJ->Draw();



/////////////////////////////////////////////////////////////////
  c1->SaveAs(("SJ_mass_superimpose_Suu"+sampleSuuMass+".png").c_str()); 


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  THStack *hs_disuperjet_mass = new THStack("hs_disuperjet_mass",";;Events / 200 GeV");
  hs_disuperjet_mass->SetMaximum(120.);

  TH1F *h_ttbar_diSuperJet_mass = (TH1F*)f1->Get("h_diSuperJet_mass");  //ttbar
  h_ttbar_diSuperJet_mass->SetFillColor(kRed);
  hs_disuperjet_mass->Add(h_ttbar_diSuperJet_mass);

  TH1F *h_QCD_1000to1500diSuperJet_mass = (TH1F*)f2->Get("h_diSuperJet_mass");    //qcd 1000to1500
  h_QCD_1000to1500diSuperJet_mass->SetFillColor(kYellow);
  hs_disuperjet_mass->Add(h_QCD_1000to1500diSuperJet_mass);

  TH1F *h_QCD_1500to2000_diSuperJet_mass = (TH1F*)f3->Get("h_diSuperJet_mass"); //qcd 1500to2000
  h_QCD_1500to2000_diSuperJet_mass->SetFillColor(kCyan);
  hs_disuperjet_mass->Add(h_QCD_1500to2000_diSuperJet_mass);

  TH1F *h_QCD_2000toInf_diSuperJet_mass = (TH1F*)f4->Get("h_diSuperJet_mass"); //qcd 2000toInf
  h_QCD_2000toInf_diSuperJet_mass->SetFillColor(kBlue);
  hs_disuperjet_mass->Add(h_QCD_2000toInf_diSuperJet_mass);

  TH1F *h_signal_diSuperJet_mass = (TH1F*)f5->Get("h_diSuperJet_mass"); //qcd 2000toInf
  h_signal_diSuperJet_mass->SetFillColor(kOrange);
  h_signal_diSuperJet_mass->SetMarkerStyle(22);
  h_signal_diSuperJet_mass->SetMarkerSize(3);

  //hs_disuperjet_mass->Add(h_signal_diSuperJet_mass);
  gStyle->SetOptStat(0);

  hs_disuperjet_mass->Draw("HIST");
  hs_disuperjet_mass->GetYaxis()->SetTitleOffset(1.25);

  h_signal_diSuperJet_mass->Draw("SAME");
  TLegend *legend1 = new TLegend(1.0,0.7,0.55,0.9);
  legend1->AddEntry(h_QCD_1000to1500_superJet_mass,"QCD (1000 < H_{T} < 1500 GeV)","f");
  legend1->AddEntry(h_QCD_1500to2000_superJet_mass,"QCD (1500 < H_{T} < 2000 GeV)","f");
  legend1->AddEntry(h_QCD_2000toInf_superJet_mass,"QCD (2000 GeV < H_{T})","f");
  legend1->AddEntry(h_ttbar_superJet_mass,"t#bar{t} Hadronic","f");
  legend1->AddEntry(h_signal_superJet_mass,"S_{uu} #rightarrow #chi #chi","p");
  legend1->Draw();
  
  pt->Draw();
  pt2->Draw();

   CMSLabel-> SetNDC();
   CMSLabel -> SetTextFont(1);
   CMSLabel -> SetTextColor(1);
   CMSLabel -> SetTextSize(0.0425);
   CMSLabel -> SetTextAlign(22);
   CMSLabel -> SetTextAngle(0);
   CMSLabel -> DrawText(0.145, 0.93, "CMS");
   CMSLabel->Draw();

   simLabel-> SetNDC();
   simLabel -> SetTextFont(52);
   simLabel -> SetTextColor(1);
   simLabel -> SetTextSize(0.028);
   simLabel -> SetTextAlign(22);
   simLabel -> SetTextAngle(0);
   simLabel -> DrawText(0.3225, 0.93, "Simulation Preliminary");
   simLabel->Draw();
   
  latex.DrawLatex(0.935,0.92,lumistuff);

  TText *xlabelDSJ = new TText();
  xlabelDSJ-> SetNDC();
  xlabelDSJ -> SetTextColor(1);
  xlabelDSJ -> SetTextSize(0.038);
  xlabelDSJ -> SetTextAlign(22);
  xlabelDSJ -> SetTextAngle(0);
  xlabelDSJ -> DrawText(0.78, 0.03, "disuperjet mass [GeV]");
  xlabelDSJ->Draw();

  c1->SaveAs(("diSuperjet_mass_superimpose_Suu"+sampleSuuMass+".png").c_str()); 




////////////////////standard technique plot////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  THStack *hs_disuperjet_mass_comb = new THStack("hs_disuperjet_mass_comb",";;Events / 200 GeV");
  hs_disuperjet_mass_comb->SetMaximum(120.);
  TH1F *h_ttbar_diSuperJet_mass_comb = (TH1F*)f1->Get("h_diSuperJet_mass_comb");  //ttbar
  h_ttbar_diSuperJet_mass_comb->SetFillColor(kRed);
  hs_disuperjet_mass_comb->Add(h_ttbar_diSuperJet_mass_comb);
  TH1F *h_QCD_1000to1500diSuperJet_mass_comb = (TH1F*)f2->Get("h_diSuperJet_mass_comb");    //qcd 1000to1500
  h_QCD_1000to1500diSuperJet_mass_comb->SetFillColor(kYellow);
  hs_disuperjet_mass_comb->Add(h_QCD_1000to1500diSuperJet_mass_comb);
  TH1F *h_QCD_1500to2000_diSuperJet_mass_comb = (TH1F*)f3->Get("h_diSuperJet_mass_comb"); //qcd 1500to2000
  h_QCD_1500to2000_diSuperJet_mass_comb->SetFillColor(kCyan);
  hs_disuperjet_mass_comb->Add(h_QCD_1500to2000_diSuperJet_mass_comb);
  TH1F *h_QCD_2000toInf_diSuperJet_mass_comb = (TH1F*)f4->Get("h_diSuperJet_mass_comb"); //qcd 2000toInf
  h_QCD_2000toInf_diSuperJet_mass_comb->SetFillColor(kBlue);
  hs_disuperjet_mass_comb->Add(h_QCD_2000toInf_diSuperJet_mass_comb);
  TH1F *h_signal_diSuperJet_mass_comb = (TH1F*)f5->Get("h_diSuperJet_mass_comb"); //qcd 2000toInf
  h_signal_diSuperJet_mass_comb->SetFillColor(kOrange);
  h_signal_diSuperJet_mass_comb->SetMarkerStyle(22);
  h_signal_diSuperJet_mass_comb->SetMarkerSize(3);

  gStyle->SetOptStat(0);

  hs_disuperjet_mass_comb->Draw("HIST");
  hs_disuperjet_mass_comb->GetYaxis()->SetTitleOffset(1.25);

  h_signal_diSuperJet_mass_comb->Draw("SAME");
  TLegend *legend1_comb = new TLegend(1.0,0.7,0.55,0.9);
  legend1_comb->AddEntry(h_QCD_1000to1500_superJet_mass,"QCD (1000 < H_{T} < 1500 GeV)","f");
  legend1_comb->AddEntry(h_QCD_1500to2000_superJet_mass,"QCD (1500 < H_{T} < 2000 GeV)","f");
  legend1_comb->AddEntry(h_QCD_2000toInf_superJet_mass,"QCD (2000 GeV < H_{T})","f");
  legend1_comb->AddEntry(h_ttbar_superJet_mass,"t#bar{t} Hadronic","f");
  legend1_comb->AddEntry(h_signal_superJet_mass,"S_{uu} #rightarrow #chi #chi","p");
  legend1_comb->Draw();


    pt->Draw();
   pt2->Draw();

   CMSLabel-> SetNDC();
   CMSLabel -> SetTextFont(1);
   CMSLabel -> SetTextColor(1);
   CMSLabel -> SetTextSize(0.0425);
   CMSLabel -> SetTextAlign(22);
   CMSLabel -> SetTextAngle(0);
   CMSLabel -> DrawText(0.145, 0.93, "CMS");
   CMSLabel->Draw();

   simLabel-> SetNDC();
   simLabel -> SetTextFont(52);
   simLabel -> SetTextColor(1);
   simLabel -> SetTextSize(0.028);
   simLabel -> SetTextAlign(22);
   simLabel -> SetTextAngle(0);
   simLabel -> DrawText(0.3225, 0.93, "Simulation Preliminary");
   simLabel->Draw();
   
  latex.DrawLatex(0.935,0.92,lumistuff);
  
  xlabelDSJ-> SetNDC();
  xlabelDSJ -> SetTextColor(1);
  xlabelDSJ -> SetTextSize(0.038);
  xlabelDSJ -> SetTextAlign(22);
  xlabelDSJ -> SetTextAngle(0);
  xlabelDSJ -> DrawText(0.78, 0.03, "disuperjet mass [GeV]");
  xlabelDSJ->Draw();
  c1->SaveAs(("diSuperjet_mass_superimpose_comb_Suu"+sampleSuuMass+".png").c_str()); 


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  THStack *hs_superjet_mass_comb = new THStack("hs_superjet_mass_comb",";;Events / 100 GeV");
  hs_superjet_mass_comb->SetMaximum(500.);
  TH1F *h_ttbar_superJet_mass_comb =  (TH1F*)f1->Get("h_superJet_mass_comb");   //ttbar
  h_ttbar_superJet_mass_comb->SetFillColor(kRed);
  hs_superjet_mass_comb->Add(h_ttbar_superJet_mass_comb);

  TH1F *h_QCD_1000to1500_superJet_mass_comb =    (TH1F*)f2->Get("h_superJet_mass_comb");   //qcd 1000to1500
  h_QCD_1000to1500_superJet_mass_comb->SetFillColor(kYellow);
  hs_superjet_mass_comb->Add(h_QCD_1000to1500_superJet_mass_comb);

  TH1F *h_QCD_1500to2000_superJet_mass_comb = (TH1F*)f3->Get("h_superJet_mass_comb");   //qcd 1500to2000
  h_QCD_1500to2000_superJet_mass_comb->SetFillColor(kCyan);
  hs_superjet_mass_comb->Add(h_QCD_1500to2000_superJet_mass_comb);

  TH1F *h_QCD_2000toInf_superJet_mass_comb = (TH1F*)f4->Get("h_superJet_mass_comb");   //qcd 2000toInf
  h_QCD_2000toInf_superJet_mass_comb->SetFillColor(kBlue);
  hs_superjet_mass_comb->Add(h_QCD_2000toInf_superJet_mass_comb);

  TH1F *h_signal_superJet_mass_comb = (TH1F*)f5->Get("h_superJet_mass_comb");   //qcd 2000toInf
  h_signal_superJet_mass_comb->SetFillColor(kOrange);
  h_signal_superJet_mass_comb->SetMarkerStyle(22);
  h_signal_superJet_mass_comb->SetMarkerSize(3);

   gStyle->SetOptStat(0);

  TText T2; T2.SetTextFont(62); T2.SetTextAlign(22);
  hs_superjet_mass_comb->Draw("HIST");
  hs_superjet_mass_comb->GetYaxis()->SetTitleOffset(1.25);

  h_signal_superJet_mass_comb->Draw("SAME");
  TLegend *legend_comb = new TLegend(1.0,0.7,0.55,0.9);
  legend_comb->AddEntry(h_QCD_1000to1500_superJet_mass,"QCD (1000 < H_{T} < 1500 GeV)","f");
  legend_comb->AddEntry(h_QCD_1500to2000_superJet_mass,"QCD (1500 < H_{T} < 2000 GeV)","f");
  legend_comb->AddEntry(h_QCD_2000toInf_superJet_mass,"QCD (2000 GeV < H_{T})","f");
  legend_comb->AddEntry(h_ttbar_superJet_mass,"t#bar{t} Hadronic","f");
  legend_comb->AddEntry(h_signal_superJet_mass,"S_{uu} #rightarrow #chi #chi","p");

  legend_comb->Draw();

  pt->Draw();
  pt2->Draw();

   CMSLabel-> SetNDC();
   CMSLabel -> SetTextFont(1);
   CMSLabel -> SetTextColor(1);
   CMSLabel -> SetTextSize(0.0425);
   CMSLabel -> SetTextAlign(22);
   CMSLabel -> SetTextAngle(0);
   CMSLabel -> DrawText(0.145, 0.93, "CMS");
   CMSLabel->Draw();

   simLabel-> SetNDC();
   simLabel -> SetTextFont(52);
   simLabel -> SetTextColor(1);
   simLabel -> SetTextSize(0.028);
   simLabel -> SetTextAlign(22);
   simLabel -> SetTextAngle(0);
   simLabel -> DrawText(0.3225, 0.93, "Simulation Preliminary");
   simLabel->Draw();
   
  latex.DrawLatex(0.935,0.92,lumistuff);
  
  xlabelSJ-> SetNDC();
  xlabelSJ -> SetTextColor(1);
  xlabelSJ -> SetTextSize(0.038);
  xlabelSJ -> SetTextAlign(22);
  xlabelSJ -> SetTextAngle(0);
  xlabelSJ -> DrawText(0.78, 0.03, "superjet mass [GeV]");
  xlabelSJ->Draw();
  c1->SaveAs(("SJ_mass_superimpose_comb_Suu"+sampleSuuMass+".png").c_str()); 

/*
////////////////////////////////////////////////////////////////////////////////////////////////////


  THStack *hs_superjet_mass_50 = new THStack("hs_superjet_mass_50",";;Events / 100 GeV");
  hs_superjet_mass_50->SetMaximum(72.);
  TH1F *h_ttbar_superJet_mass_50 =  (TH1F*)f1->Get("h_superJet_mass_50");   //ttbar
  h_ttbar_superJet_mass_50->SetFillColor(kRed);
  hs_superjet_mass_50->Add(h_ttbar_superJet_mass_50);

  TH1F *h_QCD_1000to1500_superJet_mass_50 =    (TH1F*)f2->Get("h_superJet_mass_50");   //qcd 1000to1500
  h_QCD_1000to1500_superJet_mass_50->SetFillColor(kYellow);
  hs_superjet_mass_50->Add(h_QCD_1000to1500_superJet_mass_50);

  TH1F *h_QCD_1500to2000_superJet_mass_50 = (TH1F*)f3->Get("h_superJet_mass_50");   //qcd 1500to2000
  h_QCD_1500to2000_superJet_mass_50->SetFillColor(kCyan);
  hs_superjet_mass_50->Add(h_QCD_1500to2000_superJet_mass_50);

  TH1F *h_QCD_2000toInf_superJet_mass_50 = (TH1F*)f4->Get("h_superJet_mass_50");   //qcd 2000toInf
  h_QCD_2000toInf_superJet_mass_50->SetFillColor(kBlue);
  hs_superjet_mass_50->Add(h_QCD_2000toInf_superJet_mass_50);

  TH1F *h_signal_superJet_mass_50 = (TH1F*)f5->Get("h_superJet_mass_50");   //qcd 2000toInf
  //h_signal_superJet_mass_50->SetFillColor(kOrange);
  h_signal_superJet_mass_50->SetMarkerStyle(22);
  h_signal_superJet_mass_50->SetMarkerSize(3);

   gStyle->SetOptStat(0);

  TText T3; T3.SetTextFont(42); T3.SetTextAlign(22);

  hs_superjet_mass_50->Draw("HIST");
  hs_superjet_mass_50->GetYaxis()->SetTitleOffset(1.25);

  h_signal_superJet_mass_50->Draw("SAME P");

  TLegend *legend3 = new TLegend(1.0,0.7,0.65,0.9);
  legend3->AddEntry(h_QCD_1000to1500_superJet_mass_50,"QCD (HT 1000to1500)","f");
  legend3->AddEntry(h_QCD_1500to2000_superJet_mass_50,"QCD (HT 1500to2000)","f");
  legend3->AddEntry(h_QCD_2000toInf_superJet_mass_50,"QCD (HT 2000toInf)","f");
  legend3->AddEntry(h_ttbar_superJet_mass_50,"TTToHadronic","f");
  legend3->AddEntry(h_signal_superJet_mass_50,"S_{uu} -> Chi Chi","p");
  legend3->Draw();
  pt->Draw();
  pt2->Draw();

   CMSLabel-> SetNDC();
   CMSLabel -> SetTextFont(1);
   CMSLabel -> SetTextColor(1);
   CMSLabel -> SetTextSize(0.0425);
   CMSLabel -> SetTextAlign(22);
   CMSLabel -> SetTextAngle(0);
   CMSLabel -> DrawText(0.145, 0.93, "CMS");
   CMSLabel->Draw();

   simLabel-> SetNDC();
   simLabel -> SetTextFont(52);
   simLabel -> SetTextColor(1);
   simLabel -> SetTextSize(0.028);
   simLabel -> SetTextAlign(22);
   simLabel -> SetTextAngle(0);
   simLabel -> DrawText(0.3225, 0.93, "Simulation Preliminary");
   simLabel->Draw();
   
  latex.DrawLatex(0.935,0.92,lumistuff);
  
  xlabelSJ-> SetNDC();
  xlabelSJ -> SetTextColor(1);
  xlabelSJ -> SetTextSize(0.038);
  xlabelSJ -> SetTextAlign(22);
  xlabelSJ -> SetTextAngle(0);
  xlabelSJ -> DrawText(0.63, 0.03, "superjet mass (SJ AK4 E> 50 GeV) [GeV]");
  xlabelSJ->Draw();
  c1->SaveAs(("SJ_mass_50_superimpose_Suu"+sampleSuuMass+".png").c_str()); 
*/


  outFile.Write();
 
}

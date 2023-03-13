#include <iostream>
#include <string>
#include "TLorentzVector.h"
#include "TRatioPlot.h"
#include "THStack.h"
using namespace std;

void compareBTagScores()
{

   /*
   h_deepFlavour_score
   h_deepFlavour_score_pt1TeV
   h_deepFlavour_score_pt2TeV

   h_deepFlavour_score_trueb
   h_deepFlavour_score_trueb_pt2TeV
   h_deepFlavour_score_trueb_pt1TeV

   h_deepFlavour_score_truec
   h_deepFlavour_score_truec_pt2TeV
   h_deepFlavour_score_truec_pt1TeV

   h_deepFlavour_score_udsg
   h_deepFlavour_score_udsg_pt2TeV
   h_deepFlavour_score_udsg_pt1TeV


  */

  std::cout << "Open Files" << std::endl;
  TFile *f1 = new TFile("/home/ethan/Documents/QCD_HT2000toInf_combined_cutbased_processed_TEST_2018.root");   //need to add these two together
  
  TH1F* h_deepFlavour_score               =      (TH1F*)f1->Get("h_deepFlavour_score");
  TH1F* h_deepFlavour_score_pt1TeV        =      (TH1F*)f1->Get("h_deepFlavour_score_pt1TeV");
  TH1F* h_deepFlavour_score_pt2TeV        =      (TH1F*)f1->Get("h_deepFlavour_score_pt2TeV");

  TH1F* h_deepFlavour_score_trueb                   =      (TH1F*)f1->Get("h_deepFlavour_score_trueb");
  TH1F* h_deepFlavour_score_trueb_pt1TeV            =      (TH1F*)f1->Get("h_deepFlavour_score_trueb_pt1TeV");
  TH1F* h_deepFlavour_score_trueb_pt2TeV            =      (TH1F*)f1->Get("h_deepFlavour_score_trueb_pt2TeV");

  TH1F* h_deepFlavour_score_truec                   =      (TH1F*)f1->Get("h_deepFlavour_score_truec");
  TH1F* h_deepFlavour_score_truec_pt1TeV            =      (TH1F*)f1->Get("h_deepFlavour_score_truec_pt1TeV");
  TH1F* h_deepFlavour_score_truec_pt2TeV            =      (TH1F*)f1->Get("h_deepFlavour_score_truec_pt2TeV");

  TH1F* h_deepFlavour_score_udsg                   =      (TH1F*)f1->Get("h_deepFlavour_score_udsg");
  TH1F* h_deepFlavour_score_udsg_pt1TeV            =      (TH1F*)f1->Get("h_deepFlavour_score_udsg_pt1TeV");
  TH1F* h_deepFlavour_score_udsg_pt2TeV            =      (TH1F*)f1->Get("h_deepFlavour_score_udsg_pt2TeV");



/////////////////////////////////////////all ak4///////////////////////////////////
  h_deepFlavour_score_pt2TeV->Scale(1./h_deepFlavour_score_pt2TeV->Integral());
  h_deepFlavour_score_pt1TeV->Scale(1./h_deepFlavour_score_pt1TeV->Integral());
  h_deepFlavour_score->Scale(1./h_deepFlavour_score->Integral());

  h_deepFlavour_score_pt2TeV->SetLineColor(kRed);
  h_deepFlavour_score_pt2TeV->SetLineWidth(6);

  h_deepFlavour_score_pt1TeV->SetLineColor(kBlue);
  h_deepFlavour_score_pt1TeV->SetLineWidth(6);

  h_deepFlavour_score->SetLineColor(kGreen);
  h_deepFlavour_score->SetLineWidth(6);

/////////////////////////////////////true b ak4////////////////////////////////////////////////
  h_deepFlavour_score_trueb->Scale(1./h_deepFlavour_score_trueb->Integral());
  h_deepFlavour_score_trueb_pt1TeV->Scale(1./h_deepFlavour_score_trueb_pt1TeV->Integral());
  h_deepFlavour_score_trueb_pt2TeV->Scale(1./h_deepFlavour_score_trueb_pt2TeV->Integral());

  h_deepFlavour_score_trueb->SetLineColor(kRed);
  h_deepFlavour_score_trueb->SetLineWidth(6);

  h_deepFlavour_score_trueb_pt1TeV->SetLineColor(kBlue);
  h_deepFlavour_score_trueb_pt1TeV->SetLineWidth(6);

  h_deepFlavour_score_trueb_pt2TeV->SetLineColor(kGreen);
  h_deepFlavour_score_trueb_pt2TeV->SetLineWidth(6);


/////////////////////////////////////true c ak4////////////////////////////////////////////////
  h_deepFlavour_score_truec->Scale(1./h_deepFlavour_score_truec->Integral());
  h_deepFlavour_score_truec_pt1TeV->Scale(1./h_deepFlavour_score_truec_pt1TeV->Integral());
  h_deepFlavour_score_truec_pt2TeV->Scale(1./h_deepFlavour_score_truec_pt2TeV->Integral());

  h_deepFlavour_score_truec->SetLineColor(kRed);
  h_deepFlavour_score_truec->SetLineWidth(6);

  h_deepFlavour_score_truec_pt1TeV->SetLineColor(kBlue);
  h_deepFlavour_score_truec_pt1TeV->SetLineWidth(6);

  h_deepFlavour_score_truec_pt2TeV->SetLineColor(kGreen);
  h_deepFlavour_score_truec_pt2TeV->SetLineWidth(6);


/////////////////////////////////////true udsg ak4////////////////////////////////////////////////
  h_deepFlavour_score_udsg->Scale(1./h_deepFlavour_score_udsg->Integral());
  h_deepFlavour_score_udsg_pt1TeV->Scale(1./h_deepFlavour_score_udsg_pt1TeV->Integral());
  h_deepFlavour_score_udsg_pt2TeV->Scale(1./h_deepFlavour_score_udsg_pt2TeV->Integral());

  h_deepFlavour_score_udsg->SetLineColor(kRed);
  h_deepFlavour_score_udsg->SetLineWidth(6);

  h_deepFlavour_score_udsg_pt1TeV->SetLineColor(kBlue);
  h_deepFlavour_score_udsg_pt1TeV->SetLineWidth(6);

  h_deepFlavour_score_udsg_pt2TeV->SetLineColor(kGreen);
  h_deepFlavour_score_udsg_pt2TeV->SetLineWidth(6);

  TCanvas *c1 = new TCanvas("c1","",400,20, 1500,1500);
  gPad->SetLogy();



/////////////////all ak4 flavours ///////////////////////////////////
  h_deepFlavour_score->Draw();
  h_deepFlavour_score_pt1TeV->Draw("SAME");
  h_deepFlavour_score_pt2TeV->Draw("SAME");
  h_deepFlavour_score->SetStats(0);
  h_deepFlavour_score_pt1TeV->SetStats(0);
  h_deepFlavour_score_pt2TeV->SetStats(0);

  TLegend *legend = new TLegend(1.0,0.8,0.48,0.9);
  legend->AddEntry(h_deepFlavour_score,"All AK4 jets","l");
  legend->AddEntry(h_deepFlavour_score_pt1TeV,"AK4 w/ p_{T} > 1 TeV","l");
  legend->AddEntry(h_deepFlavour_score_pt2TeV,"AK4 w/ p_{T} > 2 TeV","l");
  legend->Draw();
  //gStyle->SetOptStat(0);

  c1->SaveAs("h_deepFlavour_scores.png"); 

/////////////////true b ///////////////////////////////////
  h_deepFlavour_score_trueb->Draw();
  h_deepFlavour_score_trueb_pt1TeV->Draw("SAME");
  h_deepFlavour_score_trueb_pt2TeV->Draw("SAME");
  h_deepFlavour_score_trueb->SetStats(0);
  h_deepFlavour_score_trueb_pt1TeV->SetStats(0);
  h_deepFlavour_score_trueb_pt2TeV->SetStats(0);

  TLegend *legend1 = new TLegend(1.0,0.8,0.48,0.9);
  legend1->AddEntry(h_deepFlavour_score_trueb,"All AK4 jets","l");
  legend1->AddEntry(h_deepFlavour_score_trueb_pt1TeV,"AK4 w/ p_{T} > 1 TeV","l");
  legend1->AddEntry(h_deepFlavour_score_trueb_pt2TeV,"AK4 w/ p_{T} > 2 TeV","l");
  legend1->Draw();
  //gStyle->SetOptStat(0);

  c1->SaveAs("h_deepFlavour_scores_trueb.png"); 


///////////////// true c///////////////////////////////////
  h_deepFlavour_score_truec->Draw();
  h_deepFlavour_score_truec_pt1TeV->Draw("SAME");
  h_deepFlavour_score_truec_pt2TeV->Draw("SAME");
  h_deepFlavour_score_truec->SetStats(0);
  h_deepFlavour_score_truec_pt1TeV->SetStats(0);
  h_deepFlavour_score_truec_pt2TeV->SetStats(0);

  TLegend *legend2 = new TLegend(1.0,0.8,0.48,0.9);
  legend2->AddEntry(h_deepFlavour_score_truec,"All AK4 jets","l");
  legend2->AddEntry(h_deepFlavour_score_truec_pt1TeV,"AK4 w/ p_{T} > 1 TeV","l");
  legend2->AddEntry(h_deepFlavour_score_truec_pt2TeV,"AK4 w/ p_{T} > 2 TeV","l");
  legend2->Draw();
  //gStyle->SetOptStat(0);

  c1->SaveAs("h_deepFlavour_scores_truec.png"); 


///////////////// udsg ///////////////////////////////////
  h_deepFlavour_score_udsg->Draw();
  h_deepFlavour_score_udsg_pt1TeV->Draw("SAME");
  h_deepFlavour_score_udsg_pt2TeV->Draw("SAME");
  h_deepFlavour_score_udsg->SetStats(0);
  h_deepFlavour_score_udsg_pt1TeV->SetStats(0);
  h_deepFlavour_score_udsg_pt2TeV->SetStats(0);

  TLegend *legend3= new TLegend(1.0,0.8,0.48,0.9);
  legend3->AddEntry(h_deepFlavour_score_udsg,"All AK4 jets","l");
  legend3->AddEntry(h_deepFlavour_score_udsg_pt1TeV,"AK4 w/ p_{T} > 1 TeV","l");
  legend3->AddEntry(h_deepFlavour_score_udsg_pt2TeV,"AK4 w/ p_{T} > 2 TeV","l");
  legend3->Draw();
  //gStyle->SetOptStat(0);

  c1->SaveAs("h_deepFlavour_scores_udsg.png"); 






///////////////// compare flavours ///////////////////////////////////


  h_deepFlavour_score_trueb->SetLineColor(kRed);
  h_deepFlavour_score_truec->SetLineColor(kBlue);
  h_deepFlavour_score_udsg->SetLineColor(kGreen);

  h_deepFlavour_score_trueb->Draw();
  h_deepFlavour_score_truec->Draw("SAME");
  h_deepFlavour_score_udsg->Draw("SAME");
  h_deepFlavour_score_trueb->SetStats(0);
  h_deepFlavour_score_truec->SetStats(0);
  h_deepFlavour_score_udsg->SetStats(0);

  TLegend *legend4= new TLegend(1.0,0.8,0.48,0.9);
  legend4->AddEntry(h_deepFlavour_score_trueb,"true b","l");
  legend4->AddEntry(h_deepFlavour_score_truec,"true c","l");
  legend4->AddEntry(h_deepFlavour_score_udsg,"udsg jets","l");
  legend4->Draw();
  //gStyle->SetOptStat(0);

  c1->SaveAs("h_deepFlavour_scores_flavours.png"); 


  ///////////////// compare 1 TeV flavours ///////////////////////////////////


  h_deepFlavour_score_trueb_pt1TeV->SetLineColor(kRed);
  h_deepFlavour_score_truec_pt1TeV->SetLineColor(kBlue);
  h_deepFlavour_score_udsg_pt1TeV->SetLineColor(kGreen);

  h_deepFlavour_score_trueb_pt1TeV->Draw();
  h_deepFlavour_score_truec_pt1TeV->Draw("SAME");
  h_deepFlavour_score_udsg_pt1TeV->Draw("SAME");
  h_deepFlavour_score_trueb_pt1TeV->SetStats(0);
  h_deepFlavour_score_truec_pt1TeV->SetStats(0);
  h_deepFlavour_score_udsg_pt1TeV->SetStats(0);

  TLegend *legend5= new TLegend(1.0,0.8,0.48,0.9);
  legend5->AddEntry(h_deepFlavour_score_trueb_pt1TeV,"true b (p_{T} > 1 TeV)","l");
  legend5->AddEntry(h_deepFlavour_score_truec_pt1TeV,"true c (p_{T} > 1 TeV)","l");
  legend5->AddEntry(h_deepFlavour_score_udsg_pt1TeV,"udsg jets (p_{T} > 1 TeV)","l");
  legend5->Draw();
  //gStyle->SetOptStat(0);

  c1->SaveAs("h_deepFlavour_scores_flavours_1TeV.png"); 

  ///////////////// compare 2 TeV flavours ///////////////////////////////////


  h_deepFlavour_score_trueb_pt2TeV->SetLineColor(kRed);
  h_deepFlavour_score_truec_pt2TeV->SetLineColor(kBlue);
  h_deepFlavour_score_udsg_pt2TeV->SetLineColor(kGreen);

  h_deepFlavour_score_trueb_pt2TeV->Draw();
  h_deepFlavour_score_truec_pt2TeV->Draw("SAME");
  h_deepFlavour_score_udsg_pt2TeV->Draw("SAME");
  h_deepFlavour_score_trueb_pt2TeV->SetStats(0);
  h_deepFlavour_score_truec_pt2TeV->SetStats(0);
  h_deepFlavour_score_udsg_pt2TeV->SetStats(0);

  TLegend *legend6= new TLegend(1.0,0.8,0.48,0.9);
  legend6->AddEntry(h_deepFlavour_score_trueb_pt2TeV,"true b","l");
  legend6->AddEntry(h_deepFlavour_score_truec_pt2TeV,"true c","l");
  legend6->AddEntry(h_deepFlavour_score_udsg_pt2TeV,"udsg jets","l");
  legend6->Draw();
  //gStyle->SetOptStat(0);

  c1->SaveAs("h_deepFlavour_scores_flavours_2TeV.png"); 
}


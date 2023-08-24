void makeNice1DClusteringvsDijetRecoPlots()
{
  TFile *f9 = new TFile("/home/ethan/Documents/rootFiles/signalRootFiles/ClusteringAlgorithm_MSuu5TeV-MChi1p5TeV_cutbased_processed.root");   //need processed 4 TeV Suu and 1 TeV Suu 
  TFile *f6 = new TFile("/home/ethan/Documents/rootFiles/signalRootFiles/ClusteringAlgorithm_MSuu8TeV-MChi3TeV_cutbased_processed.root");   //need processed 8 TeV Suu and 3 TeV Suu 

  TCanvas *c1 = new TCanvas("c1","",400,20, 1800,1600);
  //gPad->SetLogy();
  //c1->SetRightMargin(0.15);
  c1->SetLeftMargin(0.12);
  //c1->SetTopMargin(0.08);

  //c1->SetLeftMargin(0.15);
  //->SetBottomMargin(0.15);
  TH1F *h_SJ_mass_clustering =  (TH1F*)f6->Get("h_SJ_mass_raw_clustering"); 
  TH1F *h_SJ_mass_dijet =  (TH1F*)f6->Get("h_SJ_mass_raw_dijet"); 

  gStyle->SetOptStat(0);
  h_SJ_mass_clustering->SetTitle(";Reconstructed VLQ mass (GeV);Events / 100 GeV");
  h_SJ_mass_clustering->GetYaxis()->SetTitleSize(0.030);
  h_SJ_mass_clustering->GetXaxis()->SetTitleSize(0.030);
  h_SJ_mass_clustering->GetXaxis()->SetTitleOffset(1.45);

  h_SJ_mass_clustering->GetYaxis()->SetTitleOffset(2.05);
  h_SJ_mass_clustering->GetXaxis()->SetRangeUser(0., 4000.);

  h_SJ_mass_clustering->SetLineColor(kBlue);
  h_SJ_mass_dijet->SetLineColor(kRed);


  h_SJ_mass_clustering->SetLineWidth(3);
  h_SJ_mass_dijet->SetLineWidth(3);

  h_SJ_mass_clustering->Draw("HIST");
  h_SJ_mass_dijet->Draw("SAME");


   auto legend6 = new TLegend(0.15,0.65,0.40,0.78);
   //auto legend6 = new TLegend(0.70,0.65,0.85,0.78);

   legend6->SetHeader("","C"); // option "C" allows to center the header
   legend6->AddEntry(h_SJ_mass_clustering,"Jet sorting algorithm","f");
   legend6->AddEntry(h_SJ_mass_dijet,"Simple 4-jet approach","f");


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
  c1->SaveAs("/home/ethan/Documents/plots/nicePlotsForBOOST/h_SJ_mass_raw_Suu8Tev_chi3TeV.png"); 

}
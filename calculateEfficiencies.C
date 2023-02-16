void calculateEfficiencies()
{
  TCanvas *c1 = new TCanvas("c1","",400,20, 1800,1500);
  gStyle->SetOptStat(0);  
  double totEventsSuu[5] = {3829,4222,4296,4218,4570};
  double nDoubleTaggedSuuCut[5] =  {1558,2069,2303,2445,3010};
  double nDoubleTaggedSuuNN[5] =  {1580,1994,2428,2570,2879};

  double tagEff_cutbased[5];
  double tagEff_NN[5];
  for(int iii=0;iii<5;iii++)
  {
    tagEff_cutbased[iii] = nDoubleTaggedSuuCut[iii]/totEventsSuu[iii];
    tagEff_NN[iii]       = nDoubleTaggedSuuNN[iii]/totEventsSuu[iii];
  }
  double massPointsSuu[5] = {4.0,5.0,6.0,7.0,8.0};
  TGraph *h_tagEff_cutbased = new TGraph(5,massPointsSuu,tagEff_cutbased );

  h_tagEff_cutbased->SetTitle("Tagging Efficiency, Cut & NN aproaches");
  h_tagEff_cutbased->GetXaxis()->SetTitle("S_{uu} mass");
  h_tagEff_cutbased->GetYaxis()->SetTitle("nDoubleTagged / nTotal");
  h_tagEff_cutbased->SetMarkerStyle(43);
  h_tagEff_cutbased->SetMarkerSize(8);
  h_tagEff_cutbased->SetMarkerColor(kRed);
  h_tagEff_cutbased->GetYaxis()->SetTitleOffset(1.35);




  TGraph *h_tagEff_NN = new TGraph(5,massPointsSuu,tagEff_NN );
 // h_tagEff_NN->SetMarkerStyle(23);
  //h_tagEff_NN->SetMarkerSize(0);
  h_tagEff_NN->SetTitle("Tagging Efficiency, Cut & NN aproaches");
  h_tagEff_NN->GetXaxis()->SetTitle("S_{uu} mass");
  h_tagEff_NN->GetYaxis()->SetTitle("nDoubleTagged / nTotal");
  h_tagEff_NN->SetMarkerSize(8);
  h_tagEff_NN->SetMarkerStyle(43);
  h_tagEff_NN->SetMarkerColor(kBlue);
  h_tagEff_NN->GetYaxis()->SetTitleOffset(1.35);

  h_tagEff_cutbased->Draw();



  h_tagEff_NN->Draw("SAME, pl");

   auto legend = new TLegend(0.7,0.25,0.85,0.4);
   legend->SetHeader("","C"); // option "C" allows to center the header
   legend->AddEntry(h_tagEff_NN,"NN-based","p");
   legend->AddEntry(h_tagEff_cutbased,"cut-based","p");
   legend->Draw();

  c1->SaveAs("h_signalEfficiencies_by_MSuu.png"); 
}
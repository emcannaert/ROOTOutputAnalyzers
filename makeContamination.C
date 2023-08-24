  
void makeContamination()
{
  double QCD1000to1500_SF = 4.289571744;
  double QCD1500to2000_SF = 0.6042726685;
  double QCD2000toInf_SF = 0.2132134533;
  double TTJets_inclusive_SF = 4.742226033;
  double h_WJetsToLNu_SF = 0.02459688845;
  double h_WJet_QQ_SF = 0.1266526072;
  double h_TTToHadronic_SF = 0.06588049107;
  double h_TTTo2l2nu_SF = 0.03616639075;
  double h_TTToSemiLeptonic_SF = 0.04563489275;

  double Suu8TeV_chi3TeV_SF = 1.74e-02;
  double Suu5TeV_chi1p5TeV_SF = 1.19;
  double Suu6TeV_chi2TeV_SF = 2.20e-01;
  double h_Suu5TeV_chi2TeV_SF = 0.867;
  double h_Suu5TeV_chi1p5TeV_SF = 1.19E+00;
  double h_Suu6TeV_chi2TeV_SF = 2.20E-01;
  double h_Suu4TeV_chi1p5TeV_SF = 2.89E+00;
  double h_Suu8TeV_chi2TeV_SF = 1.93E-02;
  double h_Suu8TeV_chi3TeV_SF = 1.74E-02;
  double h_Suu8TeV_chi1TeV_SF = 2.17E-02;

  TFile *f2 = new TFile("/home/ethan/Documents/rootFiles/processedRootFiles/QCD_HT1500to2000_processed.root");
  TFile *f3 = new TFile("/home/ethan/Documents/rootFiles/processedRootFiles/QCD_HT2000toInf_processed.root");   //need to add these two together
  TFile *f11 = new TFile("/home/ethan/Documents/rootFiles/processedRootFiles/TTToHadronic_processed.root");
  TFile *f12 = new TFile("/home/ethan/Documents/rootFiles/processedRootFiles/JetHT_2018_combined.root");  // data

  TFile *f13 = new TFile("/home/ethan/Documents/rootFiles/signalRootFiles/ClusteringAlgorithm_MSuu8TeV-MChi3TeV_cutbased_processed.root");  // sig MC
  TFile *f14 = new TFile("/home/ethan/Documents/rootFiles/signalRootFiles/ClusteringAlgorithm_MSuu5TeV-MChi1p5TeV_cutbased_processed.root");  // sig MC

  TH2F *h_MSJ_mass_vs_MdSJ_CR_HT1500to2000_TH2        = (TH2F*)f2->Get("h_MSJ_mass_vs_MdSJ_CR");
  TH2F *h_MSJ_mass_vs_MdSJ_CR_HT2000toInf_TH2         = (TH2F*)f3->Get("h_MSJ_mass_vs_MdSJ_CR");
  TH2F *h_MSJ_mass_vs_MdSJ_CR_TTbar               = (TH2F*)f11->Get("h_MSJ_mass_vs_MdSJ_CR");
  TH2F *h_MSJ_mass_vs_MdSJ_CR_Suu5TeV_chi1p5TeV   = (TH2F*)f14->Get("h_MSJ_mass_vs_MdSJ_CR");


  h_MSJ_mass_vs_MdSJ_CR_HT1500to2000_TH2->Scale(QCD1500to2000_SF);
  h_MSJ_mass_vs_MdSJ_CR_HT2000toInf_TH2->Scale(QCD2000toInf_SF);
  h_MSJ_mass_vs_MdSJ_CR_TTbar->Scale(h_TTToHadronic_SF);
  h_MSJ_mass_vs_MdSJ_CR_Suu5TeV_chi1p5TeV->Scale(Suu5TeV_chi1p5TeV_SF);

  std::cout << "Get histograms" << std::endl;
////////////////////////////////////// 1500to2000 /////////////////////////////////////////
  TH2F *h_MSJ_mass_vs_MdSJ_SR_HT1500to2000           =      (TH2F*)f2->Get("h_MSJ_mass_vs_MdSJ_CR");
////////////////////////////////////// 2000toInf /////////////////////////////////////////
  TH2F *h_MSJ_mass_vs_MdSJ_SR_HT2000toInf           =      (TH2F*)f3->Get("h_MSJ_mass_vs_MdSJ_CR");
////////////////////////////////////// TTBar /////////////////////////////////////////
  TH2F *h_MSJ_mass_vs_MdSJ_SR_TTBar                   =      (TH2F*)f11->Get("h_MSJ_mass_vs_MdSJ_CR");
////////////////////////////////////// MSuu 5 TeV, MChi 1.5TeV /////////////////////////////////////////
  TH2F *h_MSJ_mass_vs_MdSJ_SR_Sig                   =      (TH2F*)f14->Get("h_MSJ_mass_vs_MdSJ_CR");


  std::cout << "Scale histograms 1" << std::endl;

  h_MSJ_mass_vs_MdSJ_SR_HT1500to2000->Scale(QCD1500to2000_SF);
  h_MSJ_mass_vs_MdSJ_SR_HT2000toInf->Scale(QCD2000toInf_SF);
  h_MSJ_mass_vs_MdSJ_SR_TTBar->Scale(h_TTToHadronic_SF);
  h_MSJ_mass_vs_MdSJ_SR_Sig->Scale(h_Suu5TeV_chi1p5TeV_SF);

  h_MSJ_mass_vs_MdSJ_SR_Sig->SetStats(0);


////////////////////////////////////////////////////////////////////////////////////////////////////////

  std::cout << "Add and scale histograms" << std::endl;


///////////h_totHT//////////////////////
  TH2F *h_BR = new TH2F(*h_MSJ_mass_vs_MdSJ_SR_HT2000toInf);    //);
  h_BR->Add(h_MSJ_mass_vs_MdSJ_SR_HT1500to2000);
  h_BR->Add(h_MSJ_mass_vs_MdSJ_SR_TTBar);
  h_BR->SetStats(0);

  TH2F *h_BRplusSig = new TH2F(*h_BR);    //);
  h_BRplusSig->Add(h_MSJ_mass_vs_MdSJ_SR_Sig);

  h_BRplusSig->Divide(h_BR);
  h_BRplusSig->SetStats(0);
  TCanvas *c1 = new TCanvas("c1","",400,20, 1500,1500);


  h_BRplusSig->Draw("colz");
  c1->SaveAs("/home/ethan/Documents/plots/h_2D_SigplusBRoverBR_CR.png");

  h_BR->Draw("colz");
  c1->SaveAs("/home/ethan/Documents/plots/h_2D_combined_BR_CR.png");

  h_MSJ_mass_vs_MdSJ_SR_Sig->Draw("colz");
  c1->SaveAs("/home/ethan/Documents/plots/h_MSJ_mass_vs_MdSJ_CR_Sig.png");

   //gPad->SetLogy();



}
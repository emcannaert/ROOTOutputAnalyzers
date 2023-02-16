#include <iostream>
#include <string>
#include "TLorentzVector.h"

using namespace std;


void read_clustAlgBRHist()
{

   int eventnum = 0;
   int nhadevents = 0;
   int nfatjets = 0;
   int raw_nfatjets;
   int tot_nAK4_50,tot_nAK4_70;
   int SJ_nAK4_50[100],SJ_nAK4_70[100];
   double jet_pt[100], jet_eta[100], jet_mass[100], jet_dr[100], raw_jet_mass[100],raw_jet_pt[100],raw_jet_phi[100];
   double jet_beta[100], beta_T[100], AK4_mass_20[100],AK4_mass_30[100],AK4_mass_50[100],AK4_mass_70[100],AK4_mass_100[100],SJ_mass_150[100],SJ_mass_600[100],SJ_mass_800[100],SJ_mass_1000[100];
   double SJ_mass_50[100], SJ_mass_70[100],superJet_mass[100],SJ_AK4_50_mass[100],SJ_AK4_70_mass[100],genSuperJetMass[100];
   double tot_jet_mass,decay_inv_mass, chi_inv_mass;
   int nSuperJets,correctlySortedChi1,correctlySortedChi2;
   int nSuccessfulSorts = 0;
   int jet_ndaughters[100], jet_nAK4[100],jet_nAK4_20[100],jet_nAK4_30[100],jet_nAK4_50[100],jet_nAK4_70[100],SJ_nAK4_150[100],jet_nAK4_150[100],SJ_nAK4_200[100],SJ_nAK4_400[100],SJ_nAK4_600[100],SJ_nAK4_800[100],SJ_nAK4_1000[100];
   int ntotalevents = 0;
   int nAK4;
   double topAK8_dr,WSuuAK8_dr,bSuuAK8_dr,higgsAK8_dr,topWAK8_dr,topbAK8_dr,topAK4_dr,WSuuAK4_dr,bSuuAK4_dr,higgsAK4_dr,topWAK4_dr,topbAK4_dr;
   double AK4_mass[100];
   double chi_dr,topPart_dr,higgs_dr,SuuW_dr,HiggsTop_dr,SuuWb_dr;
   int tot_mpp_AK4;
   double SJ_mass_100[100],AK4_E[500];
   int SJ_nAK4_100[100];
   double totHT = 0;
   int nbtaggedAK4 =0;
   int SJ_nAK4_300[100];
   double genPartChiDaughterMPP_angle[2];
   double genHiggsThrustCos[100], genTopWThrustCos[100], genSuuWThrustCos[100];
   int nfatjet_pre;
   double genTopbThrustCos,genSuubThrustCos,diSuperJet_mass,diSuperJet_mass_100;
   //TFile *f = new TFile("/home/ethan/Documents/ClusteringAlgorithmBR_ttbar_output.root");
   //TFile outFile("/home/ethan/Documents/clustAlgBR_ttbar_processed_4TeVSuu850GeVChi.root","RECREATE");

   //TFile *f = new TFile("/home/ethan/Documents/ClusteringAlgorithmBR_ttbar_NOSORT_output.root");
   //TFile outFile("/home/ethan/Documents/clustAlgBR_ttbar_processed_NOSORT_4TeVSuu850GeVChi.root","RECREATE");


   TFile *f = new TFile("/home/ethan/Documents/ClusteringAlgorithmBR_QCD_output.root");
   TFile outFile("/home/ethan/Documents/ClusteringAlgorithmBR_QCD_processed.root","RECREATE");

   //TFile *f = new TFile("/home/ethan/Documents/ClusteringAlgorithmBR_QCD_NOSORT_output.root");
   //TFile outFile("/home/ethan/Documents/ClusteringAlgorithmBR_QCD_NOSORT_processed.root","RECREATE");


   TCanvas *c1 = new TCanvas("c1","",400,20, 2000,2000);

////////////////////////Change this to go back do diquark! Change the tree
   TTree *t1 = (TTree*)f->Get("clusteringAnalyzerBR/tree");
   const Int_t nentries = t1->GetEntries();

////////////////////////////////////////////////////////////////////////////////////////////////////////

   TH1I* h_nfatjets = new TH1I("h_nfatjets","Number of AK8 Jets; # AK8 Jets",8,-0.5,7.5);
   TH1I* h_nAK4 = new TH1I("h_nAK4","Number of AK4 Jets; # AK8 Jets",20,-0.5,19.5);

   TH1F* h_SJ_AK4_50_mass = new TH1F("h_SJ_AK4_50_mass","Mass of Reclustered AK4 Jets (E_{MPP} >50 GeV);p_{T} [GeV];Events / 10 GeV",80,0.,800);
   TH1F* h_SJ_AK4_70_mass = new TH1F("h_SJ_AK4_70_mass","Mass of Reclustered AK4 Jets (E_{MPP} >70 GeV);p_{T} [GeV]; Events / 10 GeV",80,0.,800);


   TH1F* h_SJ_mass_50 = new TH1F("h_SJ_mass_50","Mass of Reclustered SuperJet (E_{MPP} >50 GeV);p_{T} [GeV]; Events / 50 GeV",50,0.,2500);
   TH1F* h_SJ_mass_70 = new TH1F("h_SJ_mass_70","Mass of Reclustered SuperJet (E_{MPP} >70 GeV);p_{T} [GeV]; Events / 50 GeV",50,0.,2500);
   TH1F* h_AK4_mass = new TH1F("h_AK4_mass","Mass of AK4 Jets;Mass [GeV]",60,0.,600);
   TH1F* h_superJet_mass = new TH1F("h_superJet_mass","Mass of SuperJets; Mass [GeV];Events / 100 GeV",25,0.,2500.);
  
   TH1F* h_jet_mass = new TH1F("h_jet_mass","Mass of AK8 Jets; Mass [GeV]; Events / 30 GeV",40,0.,1200);
   TH1F* h_SJ_mass_100 = new TH1F("h_SJ_mass_100","Mass of SuperJets (E_{MPP}> 100 GeV);Mass [GeV]; Events / 50 GeV",50,0.,2500.);


   TH1F* h_AK4_E = new TH1F("h_AK4_E","Energy of AK4 Jets;Energy [GeV]",100,0.,600.);
   TH1I* h_SJ_nAK4_100 = new TH1I("h_SJ_nAK4_100","Number of AK4 Jets (E_{MPP} > 100 GeV); # AK4 Jets",9,-0.5,8.5);
   TH1I* h_SJ_nAK4_125 = new TH1I("h_SJ_nAK4_125","Number of AK4 Jets (E_{MPP} > 125 GeV); # AK4 Jets",9,-0.5,8.5);
   TH1I* h_SJ_nAK4_150 = new TH1I("h_SJ_nAK4_150","Number of AK4 Jets (E_{MPP} > 150 GeV); # AK4 Jets",9,-0.5,8.5);
   TH1I* h_SJ_nAK4_200 = new TH1I("h_SJ_nAK4_200","Number of AK4 Jets (E_{MPP} > 200 GeV); # AK4 Jets",9,-0.5,8.5);
   TH1I* h_SJ_nAK4_300 = new TH1I("h_SJ_nAK4_300","Number of AK4 Jets (E_{MPP} > 300 GeV); # AK4 Jets",9,-0.5,8.5);
   TH1I* h_SJ_nAK4_400 = new TH1I("h_SJ_nAK4_400","Number of AK4 Jets (E_{MPP} > 400 GeV); # AK4 Jets",9,-0.5,8.5);
   TH1I* h_SJ_nAK4_600 = new TH1I("h_SJ_nAK4_600","Number of AK4 Jets (E_{MPP} > 600 GeV); # AK4 Jets",9,-0.5,8.5);
   TH1I* h_SJ_nAK4_800 = new TH1I("h_SJ_nAK4_800","Number of AK4 Jets (E_{MPP} > 800 GeV); # AK4 Jets",9,-0.5,8.5);
   TH1I* h_SJ_nAK4_1000 = new TH1I("h_SJ_nAK4_1000","Number of AK4 Jets (E_{MPP} > 1000 GeV); # AK4 Jets",9,-0.5,8.5);

   TH1F* h_diSuperJet_mass = new TH1F("h_diSuperJet_mass","diSuperJet Mass;Mass [GeV]; Events / 160 GeV",50,0.,8000.);
   TH1F* h_diSuperJet_mass_100 = new TH1F("h_diSuperJet_mass_100","diSuperJet Mass (E_{MPP}> 100 GeV);Mass [GeV]; Events / 160 GeV",50,0.,8000.);

   TH2F* h_superJet_mass_TH2 = new TH2F("h_superJet_mass_TH2", "SuperJet 1 Mass vs SuperJet 2 Mass [GeV];Events / 160 GeV", 100, 0., 2500., 100., 0., 2500.);
   TH1F* h_diSuperJet_mass_diag = new TH1F("h_diSuperJet_mass_diag","diSuperJet Mass (Along SJ mass diagonal);Mass [GeV]; Events / 50 GeV",50,0.,2500.);

   t1->SetBranchAddress("nfatjets", &nfatjets);   
   t1->SetBranchAddress("nSuperJets", &nSuperJets);   
   t1->SetBranchAddress("tot_nAK4_50", &tot_nAK4_50);               //total #AK4 jets (E>50 GeV) for BOTH superjets
   t1->SetBranchAddress("tot_nAK4_70", &tot_nAK4_70);   

   t1->SetBranchAddress("diSuperJet_mass", &diSuperJet_mass);   
   t1->SetBranchAddress("diSuperJet_mass_100", &diSuperJet_mass_100); 

   t1->SetBranchAddress("nfatjet_pre", &nfatjet_pre); 


   t1->SetBranchAddress("jet_pt", jet_pt);   
   t1->SetBranchAddress("jet_eta", jet_eta);   
   t1->SetBranchAddress("jet_mass", jet_mass);   

   t1->SetBranchAddress("SJ_nAK4_50", SJ_nAK4_50);   
   t1->SetBranchAddress("SJ_nAK4_70", SJ_nAK4_70);   
   t1->SetBranchAddress("SJ_mass_50", SJ_mass_50);   
   t1->SetBranchAddress("SJ_mass_70", SJ_mass_70); 
   t1->SetBranchAddress("SJ_mass_150", SJ_mass_150);

   t1->SetBranchAddress("nbtaggedAK4", &nbtaggedAK4);
   t1->SetBranchAddress("totHT", &totHT);


   t1->SetBranchAddress("SJ_nAK4_300", SJ_nAK4_300);

   t1->SetBranchAddress("SJ_mass_600", SJ_mass_600);
   t1->SetBranchAddress("SJ_mass_800", SJ_mass_800);
   t1->SetBranchAddress("SJ_mass_1000", SJ_mass_1000);

   t1->SetBranchAddress("superJet_mass", superJet_mass);   
   t1->SetBranchAddress("SJ_AK4_50_mass", SJ_AK4_50_mass);   //mass of individual reclustered AK4 jets
   t1->SetBranchAddress("SJ_AK4_70_mass", SJ_AK4_70_mass); 

   
   t1->SetBranchAddress("SJ_nAK4_150", SJ_nAK4_150);   

   t1->SetBranchAddress("SJ_nAK4_200", SJ_nAK4_200);   
   t1->SetBranchAddress("SJ_nAK4_400", SJ_nAK4_400);   
   t1->SetBranchAddress("SJ_nAK4_600", SJ_nAK4_600);   
   t1->SetBranchAddress("SJ_nAK4_800", SJ_nAK4_800);   
   t1->SetBranchAddress("SJ_nAK4_1000", SJ_nAK4_1000);   

   t1->SetBranchAddress("nAK4" , &nAK4); 

   t1->SetBranchAddress("tot_mpp_AK4" , &tot_mpp_AK4); 
   t1->SetBranchAddress("SJ_mass_100", SJ_mass_100);   
   t1->SetBranchAddress("SJ_nAK4_100", SJ_nAK4_100);   
   t1->SetBranchAddress("AK4_E", AK4_E);  
 
   TGraph *h_SJ_mass_versus = new TGraph();
   h_SJ_mass_versus->SetName("h_SJ_mass_versus");
   h_SJ_mass_versus->SetTitle("SuperJet 1 Mass vs SuperJet 2 Mass");
   h_SJ_mass_versus->GetXaxis()->SetTitle("SuperJet 1 Mass [GeV]");
   h_SJ_mass_versus->GetYaxis()->SetTitle("SuperJet 2 Mass [GeV]");
   h_SJ_mass_versus->GetXaxis()->SetLimits(0.0,6000.);
   h_SJ_mass_versus->GetYaxis()->SetLimits(0.0,6000.);
   h_SJ_mass_versus->GetYaxis()->SetTitleOffset(1.5);

   TGraph *h_Mchichi_vs_Mchi_SJ1 = new TGraph();
   h_Mchichi_vs_Mchi_SJ1->SetName("h_Mchichi_vs_Mchi_SJ1");
   h_Mchichi_vs_Mchi_SJ1->SetTitle("M_{chi chi} vs SuperJet 1 M_{chi}");
   h_Mchichi_vs_Mchi_SJ1->GetYaxis()->SetTitle("M_{chi chi} [GeV]");
   h_Mchichi_vs_Mchi_SJ1->GetXaxis()->SetTitle("M_{chi} [GeV]");
   h_Mchichi_vs_Mchi_SJ1->GetYaxis()->SetTitleOffset(1.5);

   TGraph *h_Mchichi_vs_Mchi_SJ2 = new TGraph();
   h_Mchichi_vs_Mchi_SJ2->SetName("h_Mchichi_vs_Mchi_SJ2");
   h_Mchichi_vs_Mchi_SJ2->SetTitle("M_{chi chi} vs SuperJet 2 M_{chi}");
   h_Mchichi_vs_Mchi_SJ2->GetYaxis()->SetTitle("M_{chi chi} [GeV]");
   h_Mchichi_vs_Mchi_SJ2->GetXaxis()->SetTitle("M_{chi} [GeV]");
   h_Mchichi_vs_Mchi_SJ2->GetYaxis()->SetTitleOffset(1.5);

   TGraph *h_Mchichi_vs_Mchi_SJ1_diag = new TGraph();
   h_Mchichi_vs_Mchi_SJ1->SetName("h_Mchichi_vs_Mchi_SJ1_diag");
   h_Mchichi_vs_Mchi_SJ1->SetTitle("M_{chi chi} vs SuperJet 1 M_{chi} (Events Along SJ1/SJ2 Diagonal)");
   h_Mchichi_vs_Mchi_SJ1->GetYaxis()->SetTitle("M_{chi chi} [GeV]");
   h_Mchichi_vs_Mchi_SJ1->GetXaxis()->SetTitle("M_{chi} [GeV]");
   h_Mchichi_vs_Mchi_SJ1->GetYaxis()->SetTitleOffset(1.5);

   TGraph *h_SJ_mass_50_versus = new TGraph();
   h_SJ_mass_50_versus->SetTitle("SuperJet 1 Mass vs SuperJet 2 Mass (MPP AK4 E>50 GeV)");
   h_SJ_mass_50_versus->GetXaxis()->SetTitle("SuperJet 1 Mass");
   h_SJ_mass_50_versus->GetYaxis()->SetTitle("SuperJet 2 Mass");
   h_SJ_mass_50_versus->GetYaxis()->SetTitleOffset(1.5);


   TGraph *h_SJ_mass_70_versus = new TGraph();
   h_SJ_mass_70_versus->SetTitle("SuperJet 1 Mass vs SuperJet 2 Mass (MPP AK4 E>70 GeV)");
   h_SJ_mass_70_versus->GetXaxis()->SetTitle("SuperJet 1 Mass");
   h_SJ_mass_70_versus->GetYaxis()->SetTitle("SuperJet 2 Mass");
   h_SJ_mass_70_versus->GetYaxis()->SetTitleOffset(1.5);

   //h_SJ_mass_versus->SetMinimum(0.);
   //h_AK4_mass_70_vs->SetMaximum(1200.);

   //double ScaleFactor_2000toInf = 0.1195;       //for ttbar
   double ScaleFactor_2000toInf = 0.2895;

   int nevents = 0;int nDiagPoints = 0;
   for (Int_t i=0;i<nentries;i++) 
   {  
      t1->GetEntry(i);

      if((totHT<3000.)||(nbtaggedAK4<2))continue;

      if((SJ_nAK4_200[0]<2)||(SJ_nAK4_200[1]<2) || (nfatjet_pre < 3)|| (SJ_mass_100[0]<500.) || (SJ_mass_100[1]<500.) ) continue;

      ntotalevents++;
      for(int iii = 0;iii<tot_mpp_AK4;iii++)
      {
         h_AK4_E->Fill(AK4_E[tot_mpp_AK4],ScaleFactor_2000toInf);
      }

      h_nfatjets->Fill(nfatjets);

      h_SJ_nAK4_100->Fill(SJ_nAK4_100[0]);
      h_SJ_nAK4_100->Fill(SJ_nAK4_100[1]);

      h_SJ_nAK4_200->Fill(SJ_nAK4_200[0]);
      h_SJ_nAK4_200->Fill(SJ_nAK4_200[1]);

      h_SJ_nAK4_400->Fill(SJ_nAK4_400[0]);
      h_SJ_nAK4_400->Fill(SJ_nAK4_400[1]);

      h_SJ_nAK4_600->Fill(SJ_nAK4_600[0]);
      h_SJ_nAK4_600->Fill(SJ_nAK4_600[1]);

      h_SJ_nAK4_800->Fill(SJ_nAK4_800[0]);
      h_SJ_nAK4_800->Fill(SJ_nAK4_800[1]);

      h_SJ_nAK4_1000->Fill(SJ_nAK4_1000[0]);
      h_SJ_nAK4_1000->Fill(SJ_nAK4_1000[1]);

      for(int iii=0;iii<nfatjets;iii++)
      {
         h_jet_mass->Fill(jet_mass[iii]);
      }
      

      h_diSuperJet_mass->Fill(diSuperJet_mass,ScaleFactor_2000toInf);
      h_diSuperJet_mass_100->Fill(diSuperJet_mass_100,ScaleFactor_2000toInf);
//(diSuperJet_mass_100 < 4000.)
      if( (superJet_mass[0]/superJet_mass[1] > 0.8)&&(superJet_mass[0]/superJet_mass[1] < 1.25) )
      {
         h_diSuperJet_mass_diag->Fill(diSuperJet_mass,ScaleFactor_2000toInf);
         h_Mchichi_vs_Mchi_SJ1_diag->SetPoint(nDiagPoints, superJet_mass[0], diSuperJet_mass);
         nDiagPoints++;
      }
      h_superJet_mass_TH2->Fill(superJet_mass[0],superJet_mass[1],ScaleFactor_2000toInf);

      TRandom3 * ran = new TRandom3(0);
      double rannum = ran->Rndm();
      if(rannum < ScaleFactor_2000toInf) 
      {
         h_SJ_mass_versus->SetPoint(nevents,superJet_mass[0],superJet_mass[1]);
         h_Mchichi_vs_Mchi_SJ1->SetPoint(nevents, superJet_mass[0], diSuperJet_mass);
         h_Mchichi_vs_Mchi_SJ2->SetPoint(nevents, superJet_mass[1], diSuperJet_mass);

      }

      h_superJet_mass->Fill(superJet_mass[0],ScaleFactor_2000toInf);
      h_superJet_mass->Fill(superJet_mass[1],ScaleFactor_2000toInf);

      for(int iii=0; iii<tot_nAK4_50;iii++)
      {
        h_SJ_AK4_50_mass->Fill(SJ_AK4_50_mass[iii],ScaleFactor_2000toInf);
      }
     for(int iii=0; iii<tot_nAK4_70;iii++)
      {
        h_SJ_AK4_70_mass->Fill(SJ_AK4_70_mass[iii],ScaleFactor_2000toInf);
      }
      for(int iii = 0;iii<2;iii++)
      {
        h_SJ_mass_50->Fill(SJ_mass_50[iii],ScaleFactor_2000toInf);
        h_SJ_mass_70->Fill(SJ_mass_70[iii],ScaleFactor_2000toInf);
        h_SJ_mass_100->Fill(SJ_mass_100[iii],ScaleFactor_2000toInf);
      }
      h_nAK4->Fill(nAK4,ScaleFactor_2000toInf);
      for(int iii = 0;iii<nAK4;iii++)
      {
         h_AK4_mass->Fill(AK4_mass[iii],ScaleFactor_2000toInf);
      }

      nevents++;
    }


   //f->Close();

   h_SJ_mass_versus->Draw("AP*");
   c1->SaveAs("clustAlg_QCD_ETASORT/h_SJ_mass_versus.png");  

   h_nfatjets->Draw("HIST");
   c1->SaveAs("clustAlg_QCD_ETASORT/h_nfatjets.png");  


   h_jet_mass->Draw("HIST");
   c1->SaveAs("clustAlg_QCD_ETASORT/h_jet_mass.png");
   
   h_SJ_mass_versus->Write();

   h_superJet_mass_TH2->Draw("colz");
   c1->SaveAs("clustAlg_QCD_ETASORT/h_superJet_mass_TH2.png");  

   h_diSuperJet_mass_diag->Draw();
   c1->SaveAs("clustAlg_QCD_ETASORT/h_diSuperJet_mass_diag.png"); 

   h_Mchichi_vs_Mchi_SJ1->Write();
   h_Mchichi_vs_Mchi_SJ1_diag->Write();
   h_Mchichi_vs_Mchi_SJ2->Write();
   //gPad->SetLogy();

   h_SJ_nAK4_100->Draw("HIST");
   c1->SaveAs("clustAlg_QCD_ETASORT/h_SJ_nAK4_100.png");  
   h_SJ_nAK4_200->Draw("HIST");
   c1->SaveAs("clustAlg_QCD_ETASORT/h_SJ_nAK4_200.png");  
   h_SJ_nAK4_400->Draw("HIST");
   c1->SaveAs("clustAlg_QCD_ETASORT/h_SJ_nAK4_400.png");  
   h_SJ_nAK4_600->Draw("HIST");
   c1->SaveAs("clustAlg_QCD_ETASORT/h_SJ_nAK4_600.png");  
   h_SJ_nAK4_800->Draw("HIST");
   c1->SaveAs("clustAlg_QCD_ETASORT/h_SJ_nAK4_800.png");  
   h_SJ_nAK4_1000->Draw("HIST");
   c1->SaveAs("clustAlg_QCD_ETASORT/h_SJ_nAK4_1000.png");  
   h_superJet_mass->Draw("HIST");
   c1->SaveAs("clustAlg_QCD_ETASORT/h_superJet_mass.png");  

   h_SJ_mass_50_versus->Draw("AP*");
   c1->SaveAs("clustAlg_QCD_ETASORT/h_SJ_mass_50_versus.png"); 

   h_SJ_mass_70_versus->Draw("AP*");
   c1->SaveAs("clustAlg_QCD_ETASORT/h_SJ_mass_70_versus.png"); 

   h_SJ_mass_50->Draw("HIST");
   c1->SaveAs("clustAlg_QCD_ETASORT/h_SJ_mass_50.png");

   h_SJ_mass_70->Draw("HIST");
   c1->SaveAs("clustAlg_QCD_ETASORT/h_SJ_mass_70.png");

   h_SJ_mass_100->Draw("HIST");
   c1->SaveAs("clustAlg_QCD_ETASORT/h_SJ_mass_100.png"); 

   h_SJ_AK4_50_mass->Draw("HIST");
   c1->SaveAs("clustAlg_QCD_ETASORT/h_SJ_AK4_50_mass.png"); 

   h_SJ_AK4_70_mass->Draw("HIST");
   c1->SaveAs("clustAlg_QCD_ETASORT/h_SJ_AK4_70_mass.png");

   h_AK4_mass->Draw("HIST");
   c1->SaveAs("clustAlg_QCD_ETASORT/h_AK4_mass.png");

   outFile.Write();
   outFile.Close();

}


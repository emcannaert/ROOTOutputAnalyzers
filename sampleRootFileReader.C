#include <iostream>
#include <string>
#include "TLorentzVector.h"
using namespace std;


void sampleRootFileReader()
{
   //This file opens up a root file (which is an output file created by running an EDAnalyzer on CMS data), scrolls through all the saved events, imposes some cuts, and fills histograms, and then saves them to a file and prints out a PNG.
   //Initialize variables you'll be using
   int eventnum = 0, nfatjets, nSuperJets;
   double diSuperJet_mass;
   int SJ_nAK4_50[100],SJ_nAK4_70[100];
   double jet_pt[100], jet_eta[100], jet_mass[100],AK4_mass_50[100],AK4_mass_70[100],AK4_mass_100[100],AK4_mass_150[100],SJ_mass_50[100], SJ_mass_70[100],superJet_mass[100],SJ_AK4_50_mass[100],SJ_AK4_70_mass[100],genSuperJetMass[100];
   int jet_nAK4_50[100],jet_nAK4_70[100],jet_nAK4_100[100],jet_nAK4_150[100];
   double SJ_mass_100[100],SJ_mass_125[100],SJ_mass_150[100],SJ_mass_200[100],SJ_mass_300[100],SJ_mass_400[100],SJ_mass_600[100],SJ_mass_800[100],SJ_mass_1000[100],AK4_E[500];
   int SJ_nAK4_100[100], SJ_nAK4_125[100], SJ_nAK4_150[100], SJ_nAK4_200[100], SJ_nAK4_300[100], SJ_nAK4_400[100],SJ_nAK4_600[100],SJ_nAK4_800[100],SJ_nAK4_1000[100];

   TFile *f = new TFile("ClusteringAlgorithm_Suu4TeV_chi500GeV_RATIO_SORT_output.root");     //open up root file you want to read by giving it the path (giving it an absolute path is the most sound way of doing this)
   TFile outFile("clustAlg_Suu4TeV_chi500GeV_processed.root","RECREATE");               //give a name and location for the output root file that you will be creating 

   TCanvas *c1 = new TCanvas("c1","",400,20, 2000,2000);

   TTree *t1 = (TTree*)f->Get("clusteringAnalyzer/tree");                               //this line grabs the tree that is saved to the rootfile (the tree is saved in the folder clusteringAnalyzer)
   const Int_t nentries = t1->GetEntries();                                             //this line gets the number of events saved in the root file


   ///////////////////////////////////Initialize histograms//////////////////////////////////////

   TH1I* h_nfatjets = new TH1I("h_nfatjets","Number of AK8 Jets; # AK8 Jets",8,-0.5,7.5);

   TH1F* h_SJ_AK4_50_mass = new TH1F("h_SJ_AK4_50_mass","Mass of Reclustered AK4 Jets (E_{MPP} >50 GeV);p_{T} [GeV];Events / 20 GeV",40,0.,800);
   TH1F* h_SJ_AK4_70_mass = new TH1F("h_SJ_AK4_70_mass","Mass of Reclustered AK4 Jets (E_{MPP} >70 GeV);p_{T} [GeV]; Events / 20 GeV",40,0.,800);
   TH1F* h_SJ_mass_50 = new TH1F("h_SJ_mass_50","Mass of Reclustered SuperJet (E_{MPP} >50 GeV);p_{T} [GeV]; Events / 50 GeV",50,0.,2500);
   TH1F* h_SJ_mass_70 = new TH1F("h_SJ_mass_70","Mass of Reclustered SuperJet (E_{MPP} >70 GeV);p_{T} [GeV]; Events / 50 GeV",50,0.,2500);
   TH1F* h_diSuperJet_mass = new TH1F("h_diSuperJet_mass","diSuperJet Mass;Mass [GeV]; Events / 200 GeV",50,0.,10000.);

   TH1F* h_superJet_mass = new TH1F("h_superJet_mass","Mass of SuperJets; Mass [GeV];Events / 50 GeV",50,0.,2500.);
   TH1F* h_SJ_mass_100 = new TH1F("h_SJ_mass_100","Mass of SuperJets (E_{MPP}> 100 GeV);Mass [GeV]; Events / 50 GeV",50,0.,2500.);
   TH1F* h_SJ_mass_125 = new TH1F("h_SJ_mass_125","Mass of SuperJets (E_{MPP}> 125 GeV);Mass [GeV]; Events / 50 GeV",50,0.,2500.);
   TH1F* h_SJ_mass_150 = new TH1F("h_SJ_mass_150","Mass of SuperJets (E_{MPP}> 150 GeV);Mass [GeV]; Events / 50 GeV",50,0.,2500.);
   TH1F* h_SJ_mass_200 = new TH1F("h_SJ_mass_200","Mass of SuperJets (E_{MPP}> 200 GeV);Mass [GeV]; Events / 50 GeV",50,0.,2500.);
   TH1F* h_SJ_mass_300 = new TH1F("h_SJ_mass_300","Mass of SuperJets (E_{MPP}> 300 GeV);Mass [GeV]; Events / 50 GeV",50,0.,2500.);
   TH1F* h_SJ_mass_400 = new TH1F("h_SJ_mass_400","Mass of SuperJets (E_{MPP}> 400 GeV);Mass [GeV]; Events / 50 GeV",50,0.,2500.);

   TH1I* h_SJ_nAK4_100 = new TH1I("h_SJ_nAK4_100","Number of AK4 Jets (E_{MPP} > 100 GeV); # AK4 Jets",9,-0.5,8.5);
   TH1I* h_SJ_nAK4_125 = new TH1I("h_SJ_nAK4_125","Number of AK4 Jets (E_{MPP} > 125 GeV); # AK4 Jets",9,-0.5,8.5);
   TH1I* h_SJ_nAK4_150 = new TH1I("h_SJ_nAK4_150","Number of AK4 Jets (E_{MPP} > 150 GeV); # AK4 Jets",9,-0.5,8.5);
   TH1I* h_SJ_nAK4_200 = new TH1I("h_SJ_nAK4_200","Number of AK4 Jets (E_{MPP} > 200 GeV); # AK4 Jets",9,-0.5,8.5);
   TH1I* h_SJ_nAK4_300 = new TH1I("h_SJ_nAK4_300","Number of AK4 Jets (E_{MPP} > 300 GeV); # AK4 Jets",9,-0.5,8.5);
   TH1I* h_SJ_nAK4_400 = new TH1I("h_SJ_nAK4_400","Number of AK4 Jets (E_{MPP} > 400 GeV); # AK4 Jets",9,-0.5,8.5);
   TH1I* h_SJ_nAK4_600 = new TH1I("h_SJ_nAK4_600","Number of AK4 Jets (E_{MPP} > 600 GeV); # AK4 Jets",9,-0.5,8.5);
   TH1I* h_SJ_nAK4_800 = new TH1I("h_SJ_nAK4_800","Number of AK4 Jets (E_{MPP} > 800 GeV); # AK4 Jets",9,-0.5,8.5);
   TH1I* h_SJ_nAK4_1000 = new TH1I("h_SJ_nAK4_1000","Number of AK4 Jets (E_{MPP} > 1000 GeV); # AK4 Jets",9,-0.5,8.5);


   //This is where you establish the mapping between the variables in the root file and the variables you initialized at the top of this file
   //The variable name in quotes is the name of the variable you want from the input root file, the following variable is what you are calling it in this analyzer
   //I make these names the same so I don't confuse myself. Notice that any variable you're saving that is a single value (i.e. not an array) needs an & before the destination variable name

   t1->SetBranchAddress("nfatjets", &nfatjets);   
   t1->SetBranchAddress("nSuperJets", &nSuperJets);      
   t1->SetBranchAddress("diSuperJet_mass", &diSuperJet_mass);   

   t1->SetBranchAddress("jet_pt", jet_pt);   
   t1->SetBranchAddress("jet_eta", jet_eta);   
   t1->SetBranchAddress("jet_mass", jet_mass);   

   t1->SetBranchAddress("SJ_nAK4_50", SJ_nAK4_50);   
   t1->SetBranchAddress("SJ_nAK4_70", SJ_nAK4_70);   
   t1->SetBranchAddress("SJ_mass_50", SJ_mass_50);   
   t1->SetBranchAddress("SJ_mass_70", SJ_mass_70);   
   t1->SetBranchAddress("superJet_mass", superJet_mass);   
   t1->SetBranchAddress("SJ_AK4_50_mass", SJ_AK4_50_mass);   
   t1->SetBranchAddress("SJ_AK4_70_mass", SJ_AK4_70_mass);   

   t1->SetBranchAddress("SJ_mass_100", SJ_mass_100);   
   t1->SetBranchAddress("SJ_mass_125", SJ_mass_125);   
   t1->SetBranchAddress("SJ_mass_150", SJ_mass_150);   
   t1->SetBranchAddress("SJ_mass_200", SJ_mass_200);   
   t1->SetBranchAddress("SJ_mass_300", SJ_mass_300);   
   t1->SetBranchAddress("SJ_mass_400", SJ_mass_400);   
   t1->SetBranchAddress("SJ_mass_600", SJ_mass_600);
   t1->SetBranchAddress("SJ_mass_800", SJ_mass_800);
   t1->SetBranchAddress("SJ_mass_1000", SJ_mass_1000);

   t1->SetBranchAddress("SJ_nAK4_100", SJ_nAK4_100); 
   t1->SetBranchAddress("SJ_nAK4_125", SJ_nAK4_125);   
   t1->SetBranchAddress("SJ_nAK4_150", SJ_nAK4_150);   
   t1->SetBranchAddress("SJ_nAK4_200", SJ_nAK4_200);   
   t1->SetBranchAddress("SJ_nAK4_300", SJ_nAK4_300);   
   t1->SetBranchAddress("SJ_nAK4_400", SJ_nAK4_400);   
   t1->SetBranchAddress("SJ_nAK4_600", SJ_nAK4_600);   
   t1->SetBranchAddress("SJ_nAK4_800", SJ_nAK4_800);   
   t1->SetBranchAddress("SJ_nAK4_1000", SJ_nAK4_1000);   

   //Initialize TGraphs
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


   TGraph *h_SJ_mass_versus = new TGraph();
   h_SJ_mass_versus->GetXaxis()->SetLimits(0.0,6000.);
   h_SJ_mass_versus->GetYaxis()->SetLimits(0.0,6000.);
   h_SJ_mass_versus->SetName("h_SJ_mass_versus");
   h_SJ_mass_versus->SetTitle("SuperJet 1 Mass vs SuperJet 2 Mass");
   h_SJ_mass_versus->GetXaxis()->SetTitle("SuperJet 1 Mass [GeV]");
   h_SJ_mass_versus->GetYaxis()->SetTitle("SuperJet 2 Mass [GeV]");
   h_SJ_mass_versus->GetYaxis()->SetTitleOffset(1.5);



   int nevents = 0;
   for (Int_t i=0;i<nentries;i++)                  // nentries = number of events that you saved histograms for (= number of events that passed your cuts)
   {  
      t1->GetEntry(i);                             //This gets the saved histograms for every event and lets you access them
   

      //fill each histogram with the values from the event
      h_nfatjets->Fill(nfatjets);                     

      h_SJ_nAK4_100->Fill(SJ_nAK4_100[0]);
      h_SJ_nAK4_100->Fill(SJ_nAK4_100[1]);

      h_SJ_nAK4_125->Fill(SJ_nAK4_125[0]);
      h_SJ_nAK4_125->Fill(SJ_nAK4_125[1]);

      h_SJ_nAK4_150->Fill(SJ_nAK4_150[0]);
      h_SJ_nAK4_150->Fill(SJ_nAK4_150[1]);

      h_SJ_nAK4_200->Fill(SJ_nAK4_200[0]);
      h_SJ_nAK4_200->Fill(SJ_nAK4_200[1]);

      h_SJ_nAK4_300->Fill(SJ_nAK4_300[0]);
      h_SJ_nAK4_300->Fill(SJ_nAK4_300[1]);



      //Impose some further cuts to the event and fill more histograms/tgraphs
      if((SJ_nAK4_100[0]<2)||(SJ_nAK4_100[1]<2) || (nfatjets < 2) ) continue;

      h_diSuperJet_mass->Fill(diSuperJet_mass);
      
      h_SJ_mass_versus->SetPoint(nevents,superJet_mass[0],superJet_mass[1]);
      h_Mchichi_vs_Mchi_SJ1->SetPoint(nevents, superJet_mass[0], diSuperJet_mass);
      h_Mchichi_vs_Mchi_SJ2->SetPoint(nevents, superJet_mass[1], diSuperJet_mass);


      for(int iii = 0;iii<nSuperJets;iii++)       //nSuperJets = 2 for every event, so this just loops over each of the possible superjets
      {
        h_superJet_mass->Fill(superJet_mass[iii]);
        h_SJ_mass_50->Fill(SJ_mass_50[iii]);
        h_SJ_mass_70->Fill(SJ_mass_70[iii]);
        h_SJ_mass_100->Fill(SJ_mass_100[iii]);
        h_SJ_mass_125->Fill(SJ_mass_125[iii]);
        h_SJ_mass_150->Fill(SJ_mass_150[iii]);
        h_SJ_mass_200->Fill(SJ_mass_200[iii]);
        h_SJ_mass_300->Fill(SJ_mass_300[iii]);

      }
      nevents++;
    }

   //Print PNGs of selected plots
   h_SJ_mass_versus->Write();          //TGraphs need to be manually written out 
   h_Mchichi_vs_Mchi_SJ1->Write();
   h_Mchichi_vs_Mchi_SJ2->Write();

   h_SJ_mass_versus->Draw("AP*");       //This is a TGraph being plotted, so the Draw options are different than for histograms
   c1->SaveAs("h_SJ_mass_versus.png");  
   h_nfatjets->Draw();
   c1->SaveAs("h_nfatjets.png"); 

  // gPad->SetLogy();                    //sets y axis scale to log

   h_SJ_nAK4_100->Draw("HIST");
   c1->SaveAs("h_SJ_nAK4_100.png"); 
   h_SJ_nAK4_125->Draw("HIST");
   c1->SaveAs("h_SJ_nAK4_125.png");
   h_SJ_nAK4_150->Draw("HIST");
   c1->SaveAs("h_SJ_nAK4_150.png");
   h_SJ_nAK4_200->Draw("HIST");
   c1->SaveAs("h_SJ_nAK4_200.png");
   h_SJ_nAK4_300->Draw("HIST");
   c1->SaveAs("h_SJ_nAK4_300.png");

   h_SJ_mass_50->Draw("HIST");
   c1->SaveAs("h_SJ_mass_50.png");
   h_SJ_mass_70->Draw("HIST");
   c1->SaveAs("h_SJ_mass_70.png");
   h_SJ_mass_100->Draw("HIST");
   c1->SaveAs("h_SJ_mass_100.png"); 
   h_SJ_mass_125->Draw("HIST");
   c1->SaveAs("h_SJ_mass_125.png"); 
   h_SJ_mass_150->Draw("HIST");
   c1->SaveAs("h_SJ_mass_150.png"); afternoon
   h_SJ_mass_200->Draw("HIST");
   c1->SaveAs("h_SJ_mass_200.png"); 
   h_SJ_mass_300->Draw("HIST");
   c1->SaveAs("h_SJ_mass_300.png"); 

   h_superJet_mass->Draw("HIST");
   c1->SaveAs("h_superJet_mass.png"); 

   outFile.Write();                     //write all histograms here to a root file
}


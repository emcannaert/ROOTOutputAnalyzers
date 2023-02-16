#include <iostream>
#include <string>
#include "TLorentzVector.h"

using namespace std;


void makeBackgroundEst()
{
   int eventnum = 0;int nfatjets = 0;int raw_nfatjets;int tot_nAK4_50,tot_nAK4_70;int SJ_nAK4_50[100],SJ_nAK4_70[100];
   double jet_pt[100], jet_eta[100], jet_mass[100], jet_dr[100], raw_jet_mass[100],raw_jet_pt[100],raw_jet_phi[100];
   double jet_beta[100], beta_T[100], AK4_mass_20[100],AK4_mass_30[100],AK4_mass_50[100],AK4_mass_70[100],AK4_mass_100[100],SJ_mass_150[100],SJ_mass_600[100],SJ_mass_800[100],SJ_mass_1000[100];
   double SJ_mass_50[100], SJ_mass_70[100],superJet_mass[100],SJ_AK4_50_mass[100],SJ_AK4_70_mass[100],genSuperJetMass[100];double tot_jet_mass,decay_inv_mass, chi_inv_mass;
   int nSuperJets,correctlySortedChi1,correctlySortedChi2;
   int jet_ndaughters[100], jet_nAK4[100],jet_nAK4_20[100],jet_nAK4_30[100],jet_nAK4_50[100],jet_nAK4_70[100],SJ_nAK4_150[100],jet_nAK4_150[100],SJ_nAK4_200[100],SJ_nAK4_400[100],SJ_nAK4_600[100],SJ_nAK4_800[100],SJ_nAK4_1000[100];
   int ntotalevents = 0;
   int nAK4;
   double AK4_mass[100];
   double SJ_mass_100[100],AK4_E[500];
   int SJ_nAK4_100[100];
   double totHT = 0;
   int nbtaggedAK4 =0;
   int SJ_nAK4_300[100];
   int nfatjet_pre;
   double SJ_mass_300[100];
   double posSJP, negSJP;
   double totMET;
   double diSuperJet_mass, diSuperJet_mass_100;
   double SJ_E[2],SJ_Px[2],SJ_Py[2],SJ_Pz[2];



      ///////////////////to do!//////////////////////////
   //////// change the tree name to match TTrees
   //////// enter in file names/////////////////////////



   //have to multiply these by scale factors  
   double resonance_mass_comb;
   double daughter_mass_comb[100];
   TFile *f = new TFile("/home/ethan/JetHT2018_combined.root");
   TFile outFile("/home/ethan/Documents/backgroundEstimation.root","RECREATE");

   TCanvas *c1 = new TCanvas("c1","",400,20, 2000,2000);
   // run this file four times, once for each of the different 2018 dataset pieces

   //TH1F* h_diSuperJetMass = new TH1F("h_diSuperJetMass","diSuperJet Mass ;Mass [GeV]; Events / 200 GeV",40,0.,8000.);


   TH1F* h_superjetMass_preselect = new TH1F("h_superjetMass","Avg Superjet Mass ;Mass [GeV]; Events / 100 GeV",40,0.,4000);
   TH1F* h_diSuperJetMass_preselect = new TH1F("h_diSuperJetMass","diSuperJet Mass ;Mass [GeV]; Events / 200 GeV",40,0.,8000.);

   TH1F* h_numAntiTagged = new TH1F("h_numAntiTagged","number of anti-tagged events per (near side) mass ;Mass [GeV]; Events / 100 GeV",40,0.,4000);
   TH1F* h_numMistagged  = new TH1F("h_numMistagged","number of mistagged second superjets per (near side) mass bin ;Mass [GeV]; Events / 100 GeV",40,0.,4000);
   TH1F* h_diSuperjet_mass_extrapolated  = new TH1F("h_diSuperjet_mass_extrapolated","diSuperJet mass assuming equal SJ 4-vectors;Mass [GeV]; Events / 200 GeV",40,0.,8000);

   TH1F* h_diSuperjet_mass_extrapolated_up  = new TH1F("h_diSuperjet_mass_extrapolated_up","diSuperJet mass assuming equal SJ 4-vectors (Error up);Mass [GeV]; Events / 200 GeV",40,0.,8000);
   TH1F* h_diSuperjet_mass_extrapolated_down  = new TH1F("h_diSuperjet_mass_extrapolated_down","diSuperJet mass assuming equal SJ 4-vectors (Error down);Mass [GeV]; Events / 200 GeV",40,0.,8000);

   TH1F* h_superjetMass = new TH1F("h_superjetMass","Superjet Mass ;Mass [GeV]; Events / 100 GeV",40,0.,4000);
   TH1F* h_superjetMass_up = new TH1F("h_superjetMass_up","Superjet Mass (Error up) ;Mass [GeV]; Events / 100 GeV",40,0.,4000);
   TH1F* h_superjetMass_down = new TH1F("h_superjetMass_down","Superjet Mass (Error down);Mass [GeV]; Events / 100 GeV",40,0.,4000);


   TGraph *h_diSJ_mass_v_SJ_mass_preselect = new TGraph();
   h_diSJ_mass_v_SJ_mass_preselect->SetName("h_diSJ_mass_v_SJ_mass_preselect");
   h_diSJ_mass_v_SJ_mass_preselect->SetTitle("diSuperJet mass vs Avg SuperJet mass (data after preselection)");
   h_diSJ_mass_v_SJ_mass_preselect->GetXaxis()->SetTitle("diSuperJet mass [GeV]");
   h_diSJ_mass_v_SJ_mass_preselect->GetYaxis()->SetTitle("Avg SuperJet Mass [GeV]");
   h_diSJ_mass_v_SJ_mass_preselect->GetYaxis()->SetTitleOffset(1.5);


   TGraph *h_diSJ_mass_v_SJ_mass = new TGraph();
   h_diSJ_mass_v_SJ_mass->SetName("h_diSJ_mass_v_SJ_mass");
   h_diSJ_mass_v_SJ_mass->SetTitle("diSuperJet mass vs Avg SuperJet mass (data)");
   h_diSJ_mass_v_SJ_mass->GetXaxis()->SetTitle("diSuperJet mass [GeV]");
   h_diSJ_mass_v_SJ_mass->GetYaxis()->SetTitle("SuperJet Mass [GeV]");
   h_diSJ_mass_v_SJ_mass->GetYaxis()->SetTitleOffset(1.5);

   TH2F* h_diSJ_mass_v_SJ_mass_TH2 = new TH2F("h_diSJ_mass_v_SJ_mass", "diSuperJet Mass vs SuperJet Mass;diSuperJet mass [GeV] / 200; Avg SuperJet mass [GeV] / 100 GeV", 40 , 0., 8000., 40., 0., 4000.);
   TH2F* h_diSJ_mass_v_SJ_mass_TH2_up = new TH2F("h_diSJ_mass_v_SJ_mass_TH2_up", "diSuperJet Mass vs SuperJet Mass (Error up);diSuperJet mass [GeV] / 200; Avg SuperJet mass [GeV] / 100 GeV", 40 , 0., 8000., 40., 0., 4000.);
   TH2F* h_diSJ_mass_v_SJ_mass_TH2_down = new TH2F("h_diSJ_mass_v_SJ_mass_TH2_down", "diSuperJet Mass vs SuperJet Mass (Error down);diSuperJet mass [GeV] / 200; Avg SuperJet mass [GeV] / 100 GeV", 40 , 0., 8000., 40., 0., 4000.);

   TFile *f1 = new TFile("/home/ethan/Documents/dataMistagRates_JetHT2018A.root");        //2018A
   TFile *f2 = new TFile("/home/ethan/Documents/dataMistagRates_JetHT2018B.root");        //2018B
   TFile *f3 = new TFile("/home/ethan/Documents/dataMistagRates_JetHT2018C.root");        //2018C
   TFile *f4 = new TFile("/home/ethan/Documents/dataMistagRates_JetHT2018D.root");        //2018D

   TH1F *h_numAntiTagged_2018A =  (TH1F*)f1->Get("h_numAntiTagged");    //2018A
   TH1F *h_numMistagged_2018A  =  (TH1F*)f1->Get("h_numMistagged");     //2018A

   TH1F *h_numAntiTagged_2018B =  (TH1F*)f2->Get("h_numAntiTagged");    //2018B
   TH1F *h_numMistagged_2018B  =  (TH1F*)f2->Get("h_numMistagged");     //2018B

   TH1F *h_numAntiTagged_2018C =  (TH1F*)f3->Get("h_numAntiTagged");    //2018C
   TH1F *h_numMistagged_2018C  =  (TH1F*)f3->Get("h_numMistagged");     //2018C

   TH1F *h_numAntiTagged_2018D =  (TH1F*)f4->Get("h_numAntiTagged");    //2018D
   TH1F *h_numMistagged_2018D  =  (TH1F*)f4->Get("h_numMistagged");     //2018D


   //add together all these histograms
   TH1F *h_numAntiTagged_combined = new TH1F(*h_numAntiTagged_2018A);
   h_numAntiTagged_combined->Add(h_numAntiTagged_2018B);
   h_numAntiTagged_combined->Add(h_numAntiTagged_2018C);
   h_numAntiTagged_combined->Add(h_numAntiTagged_2018D);

   TH1F *h_numMistagged_combined = new TH1F(*h_numMistagged_2018A);
   h_numMistagged_combined->Add(h_numMistagged_2018B);
   h_numMistagged_combined->Add(h_numMistagged_2018C);
   h_numMistagged_combined->Add(h_numMistagged_2018D);

   TTree *t1 = (TTree*)f->Get("clusteringAnalyzerBR/tree");   //need to change this to something relevenet
   const Int_t nentries = t1->GetEntries();

////////////////////////////////////////////////////////////////////////////////////////////////////////
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
   t1->SetBranchAddress("SJ_mass_300", SJ_mass_300);
   t1->SetBranchAddress("SJ_mass_50", SJ_mass_50);
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
   t1->SetBranchAddress("SJ_mass_100", SJ_mass_100);   
   t1->SetBranchAddress("SJ_nAK4_100", SJ_nAK4_100);   
   t1->SetBranchAddress("AK4_E", AK4_E);  
   t1->SetBranchAddress("daughter_mass_comb", daughter_mass_comb);   
   t1->SetBranchAddress("resonance_mass_comb", &resonance_mass_comb);  
   t1->SetBranchAddress("totMET", &totMET); 
   t1->SetBranchAddress("posSJP", &posSJP); 
   t1->SetBranchAddress("negSJP", &negSJP); 

   t1->SetBranchAddress("SJ_E", SJ_E); 
   t1->SetBranchAddress("SJ_Px", SJ_Px); 
   t1->SetBranchAddress("SJ_Py", SJ_Py); 
   t1->SetBranchAddress("SJ_Pz", SJ_Pz); 

   TH1F *h_mistagRate = new TH1F(*h_numMistagged_combined); h_mistagRate->Divide(h_numAntiTagged_combined); h_mistagRate->SetNameTitle("h_mistagRate", "Far superjet mistag rate vs near SJ mass; Near SJ Mass [GeV]; far SJ misTag rate / 100 GeV");
   
   h_mistagRate->Draw("HIST");
   h_mistagRate->Write();
   c1->SaveAs("plotsJetHT/h_mistagRate.png"); 
   h_numMistagged_combined->Draw("HIST");
   h_numMistagged_combined->Write();
   c1->SaveAs("plotsJetHT/h_numMistagged_combined.png");
   h_numAntiTagged_combined->Draw("HIST");
   h_numAntiTagged_combined->Write();
   c1->SaveAs("plotsJetHT/h_numAntiTagged_combined.png");
   //second part -- use calculated mistag rate to select events
   int nEventsPassed = 0;
   int nEventsPreselect = 0;
   int numEventsTagAntiTag = 0;
   int numTaggedSJ = 0;
   int numAntiTaggedSJ = 0;
   int nTaggedTagged = 0;
   int nTaggedAntiTagged = 0;
   int nAntiTaggedTagged = 0;
   int nAntiTaggedAntiTagged = 0;
   int nSJ1_Tagged = 0;
   int nSJ2_Tagged = 0;

   std::cout << "The total number of events is " << nentries << std::endl;
   for (Int_t i=0;i<nentries;i++) 
   {  
      t1->GetEntry(i);
      if( (nbtaggedAK4>1) || (nfatjets < 2) || (totHT < 1500.)     ) continue;   //initial selections 
      if( (superJet_mass[0]/superJet_mass[1] > 1.25)||(superJet_mass[0]/superJet_mass[1] < 0.8)     )continue;

      h_superjetMass_preselect->Fill( ((superJet_mass[0]+superJet_mass[1])/2. ) );
      h_diSuperJetMass_preselect->Fill(diSuperJet_mass);
      h_diSJ_mass_v_SJ_mass_preselect->SetPoint(nEventsPreselect,diSuperJet_mass,( (superJet_mass[0]+superJet_mass[1])/2.)   );
      // other tagging method -> first superjet is tagged, second superjet is antitagged
      //choose random number between 0 and 1; if this is less than mistagging probability, then the second superjet will be "mistagged"
      //apply mistagging rate to this?
      //assume far side momentum equals near side momentum, what is the disuperjet mass?
      if( ((SJ_nAK4_200[0]>=2) && (SJ_mass_100[0]>=400.))) numTaggedSJ++;
      else{numAntiTaggedSJ++;}
      if( ((SJ_nAK4_200[1]>=2) && (SJ_mass_100[1]>=400.))) numTaggedSJ++;
      else{numAntiTaggedSJ++;}

      if(  ((SJ_nAK4_200[0]>=2) && (SJ_mass_100[0]>=400.) ))
      {

         if (  ((SJ_nAK4_200[1]>=2) && (SJ_mass_100[1]>=400.) )) nTaggedTagged++;
         else { nTaggedAntiTagged++;}
         nSJ1_Tagged++;
      }
      if(  ((SJ_nAK4_200[1]>=2) && (SJ_mass_100[1]>=400.) ))
      {

         if (  ((SJ_nAK4_200[0]<2) ||(SJ_mass_100[0]<400.) )) nAntiTaggedTagged++;
         nSJ1_Tagged++;
      }    
      if(  ((SJ_nAK4_200[0]<2) || (SJ_mass_100[0]<400.) ))
      {
         if ( (SJ_nAK4_200[1]<2) || (SJ_mass_100[1]<400.)   )nAntiTaggedAntiTagged++;
      }
  
      if(  ((SJ_nAK4_200[1]>=2) && (SJ_mass_100[1]>=400.) ))
      {
         nSJ2_Tagged++;
      }
      if(  ((SJ_nAK4_200[0]>=2) && (SJ_mass_100[0]>=400.))   &&  ((SJ_nAK4_200[1]<2) || (SJ_mass_100[1]<400.))  )
      {

         int histBin = floor(superJet_mass[0] / 100. ); 
         double error = h_mistagRate->GetBinError(histBin);
         double misTagRate =   h_mistagRate->GetBinContent(histBin);
         double misTagRateUp = h_mistagRate->GetBinContent(histBin) + error;
         double misTagRatedown = h_mistagRate->GetBinContent(histBin) - error;
         if (misTagRatedown < 0)misTagRate = 0;

         TRandom3* rndNum = new TRandom3(0);  
         double  rnd = rndNum->Rndm();;
         double jetMass = sqrt(2)*SJ_E[0];
         //std::cout << misTagRate << " <-mistag rate, rnd -> "<< rnd << std::endl;
         if ( rnd < misTagRate) 
         {
            h_diSuperjet_mass_extrapolated->Fill(jetMass);    
            h_superjetMass->Fill(superJet_mass[0]);    //we are pretending the 4-vectors are the same, so the average superjet mass is just SJ1 mass
            h_diSJ_mass_v_SJ_mass_TH2->Fill(jetMass,superJet_mass[0]);
            h_diSJ_mass_v_SJ_mass->SetPoint(nEventsPassed,jetMass,superJet_mass[0]);
            nEventsPassed++;
         }

         //Error up
         if ( rnd < misTagRateUp) 
         {
            h_diSuperjet_mass_extrapolated_up->Fill(jetMass);    
            h_superjetMass_up->Fill(superJet_mass[0]);    //we are pretending the 4-vectors are the same, so the average superjet mass is just SJ1 mass
            h_diSJ_mass_v_SJ_mass_TH2_up->Fill(jetMass,superJet_mass[0]);
         }
         //Error down
         if ( rnd < misTagRatedown) 
         {
            h_diSuperjet_mass_extrapolated_down->Fill(jetMass);    
            h_superjetMass_down->Fill(superJet_mass[0]);    //we are pretending the 4-vectors are the same, so the average superjet mass is just SJ1 mass
            h_diSJ_mass_v_SJ_mass_TH2_down->Fill(jetMass,superJet_mass[0]);
         }
         numEventsTagAntiTag++;
      } 
      nEventsPreselect++;
   }
   std::cout << "There were " << nEventsPreselect << " events passing pre-selection." << std::endl;
   std::cout << "There were " << numAntiTaggedSJ << " anti-tagged SJs and " << numTaggedSJ << " tagged superjets." << std::endl;
   std::cout << numEventsTagAntiTag << " events have a tagged superjet and an anti-tagged superjet " << std::endl;
   std::cout << "Of the " << nSJ1_Tagged << " events with SJ1 tagged, there were " << nTaggedTagged << " second superjets tagged and " << nTaggedAntiTagged <<" second superjets anti-tagged." << std::endl; 
   std::cout << " and " << nEventsPassed << " events are expected to be mistagged " <<std::endl;
   std::cout << "There are " << nSJ1_Tagged << " events with SJ1 tagged and " << nSJ2_Tagged << " events with SJ2 tagged." << std::endl;
   std::cout << "TT/TA+AT/AA = " << nTaggedTagged << "/" << nTaggedAntiTagged+nAntiTaggedTagged<< "/" << nAntiTaggedAntiTagged<< "/" << std::endl;
   h_superjetMass_preselect->Draw("HIST");
   c1->SaveAs("plotsJetHT/h_superjetMass_preselect.png"); 
   h_diSuperJetMass_preselect->Draw("HIST");
   c1->SaveAs("plotsJetHT/h_diSuperJetMass_preselect.png"); 
   h_diSJ_mass_v_SJ_mass_preselect->Draw("AP*");
   c1->SaveAs("plotsJetHT/h_diSJ_mass_v_SJ_mass_preselect.png"); 

   h_numAntiTagged->Draw("HIST");
   c1->SaveAs("plotsJetHT/h_numAntiTagged.png"); 
   h_superjetMass->Draw("HIST");
   c1->SaveAs("plotsJetHT/h_superjetMass.png"); 
   h_diSuperjet_mass_extrapolated->Draw("HIST");
   c1->SaveAs("plotsJetHT/h_diSuperjet_mass_extrapolated.png"); 
   h_diSJ_mass_v_SJ_mass->Draw("AP*");
   c1->SaveAs("plotsJetHT/h_diSJ_mass_v_SJ_mass.png"); 
   h_diSJ_mass_v_SJ_mass_TH2->Draw("COLZ");
   c1->SaveAs("plotsJetHT/h_diSJ_mass_v_SJ_mass_TH2.png"); 
   
   h_superjetMass->Draw("HIST");
   h_superjetMass_up->Draw("SAME");
   h_superjetMass_down->Draw("SAME");
   c1->SaveAs("plotsJetHT/h_superjetMass_errors.png"); 

   h_diSuperjet_mass_extrapolated->Draw("HIST");
   h_diSuperjet_mass_extrapolated_up->Draw("SAME");
   h_diSuperjet_mass_extrapolated_down->Draw("SAME");
   c1->SaveAs("plotsJetHT/h_diSuperjet_mass_extrapolated_errors.png"); 

   h_diSJ_mass_v_SJ_mass_TH2_up->Draw("COLZ");
   c1->SaveAs("plotsJetHT/h_diSJ_mass_v_SJ_mass_TH2_up.png"); 
   h_diSJ_mass_v_SJ_mass_TH2_down->Draw("COLZ");
   c1->SaveAs("plotsJetHT/h_diSJ_mass_v_SJ_mass_TH2_down.png"); 


   outFile.Write();
   //outFile.Close();

}




//what I have done here 

      // combine together histograms from other script to get overall SJ mistagging rate as a function of near superjet mass
      // make SJ & disuperjet preselect plots
      // look at events here SJ1 is tagged and SJ2 isn't tagged, and apply the mistagging rate to these events to see what would ultimately be tagged
      // assuming the far superjet 4-vector is the same as the near superjet, calculate diSuperjet mass
      // additionally, make avg superjet plots and 2D distributions of SJ mass vs diSuperJet mass
      // how to deal with the errors ... recalculate for +- sigma errors 

      //Get an idea of the differences in yields given the errors on the mistagging rate




   // went to look at the bjet < 2 region, but was seeing that there were event with 8+ misc jets ... is this true? how many AK8 jets per event, add more cases? why is this true with fewer bjets
   // try specifically that bjets < 2 ?
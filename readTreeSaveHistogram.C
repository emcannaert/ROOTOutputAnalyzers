#include <iostream>
#include <string>
#include "TLorentzVector.h"

//notes of things to do next week
// check out the mass combinations for TTbar - are these really not between 150 and 200 Gev? 
// check out the SJ mass ratio, this might be really weird for TTbar and could be used to kill some of this


using namespace std;
void doThings(std::string inFileName, std::string outFileName, std::string dataYear,std::string systematic)
{
   int eventnum = 0;int nhadevents = 0;int nfatjets = 0;int raw_nfatjets;int tot_nAK4_50,tot_nAK4_70;int SJ_nAK4_50[100],SJ_nAK4_70[100];
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
   int SJ_nAK4_300[100];
   int nfatjet_pre;
   double SJ_mass_300[100];
   double AK4_bdisc[100],AK4_DeepJet_disc[100];
   double AK4_pt[100];
   double totMET;
   double diSuperJet_mass, diSuperJet_mass_100;
   double dijetMassOne, dijetMassTwo;
   //have to multiply these by scale factors  
   double daughter_mass_comb[100];
   int nGenBJets_AK4[100], AK4_partonFlavour[100],AK4_HadronFlavour[100];
   int SJ1_decision, SJ2_decision;
   int ntrueInt;
   double PU_eventWeight_up,PU_eventWeight_nom,PU_eventWeight_down;
   double _eventWeightPU,_puWeightDown,_puWeightUp;
   int eventTTbarCRFlag =0;
   
   int nEventsTTbarCR = 0;   
   ////////////////////////////   btag SF variables //////////////////////
   double bTag_eventWeight_up, bTag_eventWeight_nom, bTag_eventWeight_down;
   double diAK8Jet_mass [100];
   double fourAK8JetMass;

std::vector<std::string> systematic_suffices;

   if(systematic == "nom")
   {
      // want to run only once with the 
      systematic_suffices = {""};

   }
   else
   {
      systematic_suffices = {"up","down"};
   }


   const char *_inFilename = inFileName.c_str();
   const char *_outFilename = outFileName.c_str();

   std::cout << "Reading file: " << _inFilename << std::endl;
   TFile *f = new TFile(_inFilename);

   TFile outFile(_outFilename,"RECREATE");

   for(auto systematic_suffix = systematic_suffices.begin(); systematic_suffix < systematic_suffices.end();systematic_suffix++)
   {

      outFile.cd();   // return to outer directory
      gDirectory->mkdir( (systematic+"_"+ *systematic_suffix).c_str()  );   //create directory for this systematic
      outFile.cd( (systematic+"_"+*systematic_suffix).c_str() );   // go inside the systematic directory 


       // need to tunnel into the directory of the infile   JEC_up, nom_ /   skimmedTree_nom / skimmedTree_JER_up

      std::string tree_name;
      std::string folder_name;
      if(systematic == "nom")
      {
         tree_name = systematic;
         folder_name = systematic + "_";
      }
      else
      {
         tree_name = systematic+"_"+*systematic_suffix;
         folder_name = tree_name;
      }

      std::cout << "Looking for tree " << (folder_name+ "/skimmedTree_"+ tree_name ).c_str() << std::endl;

      TTree *t1 = (TTree*)f->Get(   (folder_name+ "/skimmedTree_"+ tree_name ).c_str()    );
      const Int_t nentries = t1->GetEntries();

      double min_x = 0.75;
      double max_x = 1.25;
      if ((inFileName.find("TTbar") != std::string::npos) || ((inFileName.find("TTTohadronic") != std::string::npos)) ) // if this is a ttbar file, make the bounds lower
      {
         min_x = 0.25;
         max_x = 1.8;
      }
      TH1F* h_btagEventWeight_up = new TH1F("h_btagEventWeight_up","b-tagging event weight (up SF value);event weight value; Events / 100 GeV",80,min_x,max_x);
      TH1F* h_btagEventWeight_nom = new TH1F("h_btagEventWeight_nom","b-tagging event weight (nominal SF value);event weight value; Events / 100 GeV",80,min_x,max_x);
      TH1F* h_btagEventWeight_down = new TH1F("h_btagEventWeight_down","b-tagging event weight (down SF value);event weight value; Events / 100 GeV",80,min_x,max_x);

      TH1I* h_ntrueInteractions = new TH1I("h_ntrueInteractions","Number of True Interactions;Number of True Interactions; Events / 100 GeV",100,0,100);

      TH1F* h_PU_weight_up = new TH1F("h_PU_weight_up","Pileup event weight (up value);event weight value; Events / 100 GeV",80,0.6,1.4);
      TH1F* h_PU_weight_nom = new TH1F("h_PU_weight_nom","Pileup event weight (nom value);event weight value; Events / 100 GeV",80,0.6,1.4);
      TH1F* h_PU_weight_down = new TH1F("h_PU_weight_down","Pileup event weight (down value);event weight value; Events / 100 GeV",80,0.6,1.4);



      TGraph * g_PUweight_up_vs_nTrueInt = new TGraph();
      g_PUweight_up_vs_nTrueInt->SetTitle("Pileup Event Weight (up systematic) vs True Number of Event Interactions");
      g_PUweight_up_vs_nTrueInt->SetName("g_PUweight_up_vs_nTrueInt");
      g_PUweight_up_vs_nTrueInt->GetXaxis()->SetTitle("True Number of Interactions");
      g_PUweight_up_vs_nTrueInt->GetYaxis()->SetTitle("Pileup Weight");

      TGraph * g_PUweight_nom_vs_nTrueInt = new TGraph();
      g_PUweight_nom_vs_nTrueInt->SetTitle("Pileup Event Weight (nom systematic) vs True Number of Event Interactions");
      g_PUweight_nom_vs_nTrueInt->SetName("g_PUweight_nom_vs_nTrueInt");
      g_PUweight_nom_vs_nTrueInt->GetXaxis()->SetTitle("True Number of Interactions");
      g_PUweight_nom_vs_nTrueInt->GetYaxis()->SetTitle("Pileup Weight");

      TGraph * g_PUweight_down_vs_nTrueInt = new TGraph();
      g_PUweight_down_vs_nTrueInt->SetTitle("Pileup Event Weight (down systematic) vs True Number of Event Interactions");
      g_PUweight_down_vs_nTrueInt->SetName("g_PUweight_down_vs_nTrueInt");
      g_PUweight_down_vs_nTrueInt->GetXaxis()->SetTitle("True Number of Interactions");
      g_PUweight_down_vs_nTrueInt->GetYaxis()->SetTitle("Pileup Weight");
      //TGraph * g_PUweight_nom_vs_nTrueInt = new TGraph();
      //TGraph * g_PUweight_down_vs_nTrueInt = new TGraph();
      //make TGraph for PU event weight vs ntrue int for the up/down/nom systematics  
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
      t1->SetBranchAddress("SJ_nAK4_300", SJ_nAK4_300);     
      t1->SetBranchAddress("SJ_nAK4_400", SJ_nAK4_400);   
      t1->SetBranchAddress("SJ_nAK4_600", SJ_nAK4_600);   
      t1->SetBranchAddress("SJ_nAK4_800", SJ_nAK4_800);   
      t1->SetBranchAddress("SJ_nAK4_1000", SJ_nAK4_1000);   
      t1->SetBranchAddress("nAK4" , &nAK4); 
      t1->SetBranchAddress("SJ_mass_100", SJ_mass_100);   
      t1->SetBranchAddress("SJ_nAK4_100", SJ_nAK4_100);   
      t1->SetBranchAddress("AK4_E", AK4_E);  
      t1->SetBranchAddress("daughter_mass_comb", daughter_mass_comb);   
      t1->SetBranchAddress("totMET", &totMET); 
      t1->SetBranchAddress("AK4_bdisc", AK4_bdisc); 
      t1->SetBranchAddress("AK4_mass", AK4_mass); 
      t1->SetBranchAddress("SJ1_decision", &SJ1_decision); 
      t1->SetBranchAddress("SJ2_decision", &SJ2_decision); 

      t1->SetBranchAddress("lab_AK4_pt", AK4_pt); 

      t1->SetBranchAddress("dijetMassOne", &dijetMassOne); 
      t1->SetBranchAddress("dijetMassTwo", &dijetMassTwo); 

      t1->SetBranchAddress("nGenBJets_AK4", nGenBJets_AK4); 

      t1->SetBranchAddress("AK4_partonFlavour", AK4_partonFlavour); 
      t1->SetBranchAddress("AK4_hadronFlavour", AK4_HadronFlavour); 
      t1->SetBranchAddress("AK4_DeepJet_disc", AK4_DeepJet_disc); 

      t1->SetBranchAddress("eventTTbarCRFlag", &eventTTbarCRFlag); 

      t1->SetBranchAddress("fourAK8JetMass", &fourAK8JetMass); 
      t1->SetBranchAddress("diAK8Jet_mass", &diAK8Jet_mass); 

      t1->SetBranchAddress("bTag_eventWeight_up", &bTag_eventWeight_up); 
      t1->SetBranchAddress("bTag_eventWeight_nom", &bTag_eventWeight_nom); 
      t1->SetBranchAddress("bTag_eventWeight_down", &bTag_eventWeight_down); 
      
      t1->SetBranchAddress("ntrueInt", &ntrueInt); 
      t1->SetBranchAddress("PU_eventWeight_up", &PU_eventWeight_up); 
      t1->SetBranchAddress("PU_eventWeight_nom", &PU_eventWeight_nom); 
      t1->SetBranchAddress("PU_eventWeight_down", &PU_eventWeight_down); 





      for (Int_t i=0;i<nentries;i++) 
      {  
         t1->GetEntry(i);
         h_btagEventWeight_up->Fill(bTag_eventWeight_up);
         h_btagEventWeight_nom->Fill(bTag_eventWeight_nom);
         h_btagEventWeight_down->Fill(bTag_eventWeight_down);

         g_PUweight_up_vs_nTrueInt->SetPoint(i,ntrueInt,PU_eventWeight_up);
         g_PUweight_nom_vs_nTrueInt->SetPoint(i,ntrueInt,PU_eventWeight_nom);
         g_PUweight_down_vs_nTrueInt->SetPoint(i,ntrueInt,PU_eventWeight_down);

         h_PU_weight_up->Fill(PU_eventWeight_up);
         h_PU_weight_nom->Fill(PU_eventWeight_nom);
         h_PU_weight_down->Fill(PU_eventWeight_down);
         h_ntrueInteractions->Fill(ntrueInt);
      }
      g_PUweight_up_vs_nTrueInt->Write();
      g_PUweight_nom_vs_nTrueInt->Write();
      g_PUweight_down_vs_nTrueInt->Write();

      outFile.Write();
   }

   outFile.Close();
}


void readTreeSaveHistogram()
{
   bool includeTTBar = true;
   bool allHTBins    = true;

   std::vector<std::string> dataYears = {"2015","2016","2017","2018"};
   std::vector<std::string> systematics = {"JER","JEC","nom"};  //TESTING
   if(includeTTBar && allHTBins)  /// make sure you are
   {
      int yearNum = 0;
      for(auto dataYear = dataYears.begin(); dataYear < dataYears.end();dataYear++ )
      {
         for(auto systematic = systematics.begin();systematic<systematics.end();systematic++)
         {
            std::vector<std::string> inFileNames = {
                                                    ("/Users/ethan/Documents/rootFiles/skimmedRootFilesAlt/QCDMC1000to1500_" + *dataYear+ "_" + *systematic + "_SKIMMED.root").c_str(),
                                                    ("/Users/ethan/Documents/rootFiles/skimmedRootFilesAlt/QCDMC1500to2000_"+ *dataYear+ "_" + *systematic + "_SKIMMED.root").c_str(),
                                                     ("/Users/ethan/Documents/rootFiles/skimmedRootFilesAlt/QCDMC2000toInf_"+ *dataYear+ "_" + *systematic + "_SKIMMED.root").c_str(),
                                                     ("/Users/ethan/Documents/rootFiles/skimmedRootFilesAlt/TTTohadronic_"+ *dataYear+ "_" + *systematic + "_SKIMMED.root").c_str()
                                                  };
            std::vector<std::string> outFileNames = {
                                                    ("/Users/ethan/Documents/rootFiles/processedRootFilesAlt/QCDMC_HT1000to1500_"+ *dataYear+ "_" + *systematic + "_PLOTHIST.root").c_str(),
                                                    ("/Users/ethan/Documents/rootFiles/processedRootFilesAlt/QCDMC_HT1500to2000_"+ *dataYear+ "_" + *systematic + "_PLOTHIST.root").c_str(),
                                                     ("/Users/ethan/Documents/rootFiles/processedRootFilesAlt/QCDMC_HT2000toInf_"+ *dataYear+ "_" + *systematic + "_PLOTHIST.root").c_str(),
                                                     ("/Users/ethan/Documents/rootFiles/processedRootFilesAlt/TTToHadronic_"+ *dataYear+ "_" + *systematic + "_PLOTHIST.root").c_str()
                                                  };
            for(unsigned int iii = 0; iii<inFileNames.size(); iii++)
            {
               doThings(inFileNames[iii],outFileNames[iii], *dataYear,*systematic );
            }


            std::cout << "Finished with "<< inFileNames.size() << " files." << std::endl;
            yearNum++;
         }
      }
   }
}


//look at nBtag plots ... 
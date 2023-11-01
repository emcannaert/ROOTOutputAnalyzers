#include <iostream>
#include <string>
#include "TLorentzVector.h"

using namespace std;

void doThings(std::string inFileName, std::string outFileName,std::string year, std::string dataBlock, std::string systematic)
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
   int nbtaggedAK4 =0;
   int SJ_nAK4_300[100];
   int nfatjet_pre;
   double SJ_mass_300[100];
   double posSJP, negSJP;
   double AK4_bdisc[100],AK4_DeepJet_disc[100];
   double AK4_pt[100];
   double totMET;
   double diSuperJet_mass, diSuperJet_mass_100;
   double SJ_E[2],SJ_Px[2],SJ_Py[2],SJ_Pz[2];
   double dijetMassOne, dijetMassTwo;
   //have to multiply these by scale factors  
   double resonance_mass_comb;
   double daughter_mass_comb[100];
   int nGenBJets_AK4[100], AK4_partonFlavour[100],AK4_HadronFlavour[100];
   int SJ1_decision, SJ2_decision;


   std::vector<std::string> systematic_suffices;

   if(systematic == "nom")
   {
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

      TH2F *h_Mjet_vs_pTjet = new TH2F("h_Mjet_vs_pTjet","Jet Mass vs Jet pT; jet p_{T} [GeV];jet mass", 80,0, 4000, 50, 0, 2000);
      
      TH1F* h_numAntiTagged = new TH1F("h_numAntiTagged","number of anti-tagged events per (near side) mass ;Mass [GeV]; Events / 100 GeV",40,0.,4000);
      TH1F* h_numMistagged  = new TH1F("h_numMistagged","number of mistagged second superjets per (near side) mass bin ;Mass [GeV]; Events / 100 GeV",40,0.,4000);
      TH1F* h_totHT  = new TH1F("h_totHT","Total Event HT;H_{T} [GeV]; Events / 200 GeV",50,0.,10000);
      TH1F* h_lead_SJ_mass  = new TH1F("h_lead_SJ_mass","SuperJet Mass;Mass [GeV]; Events / 100 GeV",40,0.,4000);
      TH1F* h_lead_SJ_mass_100  = new TH1F("h_lead_SJ_mass_100","SuperJet Mass (E_{AK4} > 100 GeV);Mass [GeV]; Events / 100 GeV",40,0.,4000);
      TH1F* h_disuperjet_mass  = new TH1F("h_disuperjet_mass","diSuperJet Mass;Mass [GeV]; Events / 200 GeV",50,0.,10000);
      TH1F* h_disuperjet_mass_100  = new TH1F("h_disuperjet_mass_100","diSuperJet Mass (E_{AK4} > 100 GeV);Mass [GeV]; Events / 200 GeV",50,0.,10000);

      TH1I* h_SJ_nAK4_100  = new TH1I("h_SJ_nAK4_100","Number of Reclustered AK4 Jets (E_{COM} > 100 GeV) per SJ ;nAK4 Jets (E_{COM} > 100 GeV); Events",10,-0.5,9.5);
      TH1I* h_SJ_nAK4_200  = new TH1I("h_SJ_nAK4_200","Number of Reclustered AK4 Jets (E_{COM} > 200 GeV) per SJ ;nAK4 Jets (E_{COM} > 200 GeV); Events",10,-0.5,9.5);
      TH1I* h_SJ_nAK4_300  = new TH1I("h_SJ_nAK4_300","Number of Reclustered AK4 Jets (E_{COM} > 300 GeV) per SJ ;nAK4 Jets (E_{COM} > 300 GeV); Events",10,-0.5,9.5);
      TH1I* h_SJ_nAK4_400  = new TH1I("h_SJ_nAK4_400","Number of Reclustered AK4 Jets (E_{COM} > 400 GeV) per SJ ;nAK4 Jets (E_{COM} > 400 GeV); Events",10,-0.5,9.5);
      TH1I* h_nfatjets_pre  = new TH1I("h_nfatjets_pre","Number of AK8 Jets (p_{T} > 500 GeV, M_{PUPPI} > 45 GeV) per Event ;nAK8 Jets; Events",10,-0.5,9.5);
      TH1F* h_avg_dijet_mass  = new TH1F("h_avg_dijet_mass","Average dijet mass (AK4 jets);Mass [GeV]; Events / 100 GeV",50,0.,5000);

      TH1F* h_diSJ_SJ_mass_ratio  = new TH1F("h_diSJ_SJ_mass_ratio","M_{diSJ} / (M_{SJ1} + M_{SJ2})",50,0.,10);
      TH2F *h_MSJ_mass_vs_MdSJ = new TH2F("h_MSJ_mass_vs_MdSJ","Tagged Superjet mass vs diSuperjet mass; diSuperjet mass [GeV];superjet mass", 25,0, 10000, 20, 0, 6000);
      TH2F *h_MSJ_mass_vs_MdSJ_doubleTag = new TH2F("h_MSJ_mass_vs_MdSJ_doubleTag","Avg (double) tagged Superjet mass vs diSuperjet mass; diSuperjet mass [GeV];superjet mass", 25,0, 10000, 20, 0, 6000);


      TH2F *h_MSJ_mass_vs_MdSJ_all = new TH2F("h_MSJ_mass_vs_MdSJ_all","Tagged Superjet mass vs diSuperjet mass - NO PRESELECTION; diSuperjet mass [GeV];superjet mass", 25,0, 10000, 20, 0, 6000);


      TH1F* h_MSJ1_MSJ2_ratio  = new TH1F("h_MSJ1_MSJ2_ratio","(M_{SJ_{1}} - M_{SJ_{2}})/(M_{SJ_{1}} + M_{SJ_{2}});",30,-3.,3.0);
      TH1F* h_MdiSJ_SJ12_ratios  = new TH1F("h_MdiSJ_SJ12_ratios","M_{diSJ} / (M_{SJ_{1}} + M_{SJ_{2}})",25,0.,5.0);

      // control region stuff 
      TH1I* h_SJ_nAK4_100_CR  = new TH1I("h_SJ_nAK4_100_CR","Number of Reclustered AK4 Jets (E_{COM} > 100 GeV) per SJ (Control Region);nAK4 Jets (E_{COM} > 100 GeV); Events",10,-0.5,9.5);
      TH1I* h_SJ_nAK4_200_CR  = new TH1I("h_SJ_nAK4_200_CR","Number of Reclustered AK4 Jets (E_{COM} > 200 GeV) per SJ (Control Region);nAK4 Jets (E_{COM} > 200 GeV); Events",10,-0.5,9.5);
      TH1F* h_SJ_mass_CR  = new TH1F("h_SJ_mass_CR","SuperJet Mass (Control Region) ;Mass [GeV]; Events / 125 GeV",40,0.,5000);
      TH1F* h_disuperjet_mass_CR  = new TH1F("h_disuperjet_mass_CR","diSuperJet Mass (Control Region);Mass [GeV]; Events / 400 GeV",25,0.,10000);
      TH2F *h_MSJ_mass_vs_MdSJ_CR = new TH2F("h_MSJ_mass_vs_MdSJ_CR","Double Tagged Superjet mass vs diSuperjet mass (Control Region); diSuperjet mass [GeV];superjet mass", 22,1250., 9500, 20, 500, 3000);  /// 375 * 125



      // double-tag stuff
      TH1I* h_SJ_nAK4_100_SR  = new TH1I("h_SJ_nAK4_100_SR","Number of Reclustered AK4 Jets (E_{COM} > 100 GeV) per SJ (Control Region);nAK4 Jets (E_{COM} > 100 GeV); Events",10,-0.5,9.5);
      TH1I* h_SJ_nAK4_200_SR = new TH1I("h_SJ_nAK4_200_SR","Number of Reclustered AK4 Jets (E_{COM} > 200 GeV) per SJ (Control Region);nAK4 Jets (E_{COM} > 200 GeV); Events",10,-0.5,9.5);
      TH1F* h_SJ_mass_SR  = new TH1F("h_SJ_mass_SR","SuperJet Mass (Signal Region) ;Mass [GeV]; Events / 125 GeV",40,0.,5000);
      TH1F* h_disuperjet_mass_SR  = new TH1F("h_disuperjet_mass_SR","diSuperJet Mass (Control Region);Mass [GeV]; Events / 400 GeV",25,0.,10000);
      TH2F *h_MSJ_mass_vs_MdSJ_SR = new TH2F("h_MSJ_mass_vs_MdSJ_SR","Double Tagged Superjet mass vs diSuperjet mass (Signal Region); diSuperjet mass [GeV];superjet mass", 22,1250., 9500, 20, 500, 3000);  /// 375 * 125

      TH1I* h_nLooseBTags = new TH1I("h_nLooseBTags","Number of Loosely b-tagged AK4 Jets; Events",10,-0.5,9.5);
      TH1I* h_nMidBTags = new TH1I("h_nMidBTags","Number of Mediumly b-tagged AK4 Jets; Events",10,-0.5,9.5);
      TH1I* h_nTightBTags = new TH1I("h_nTightBTags","Number of Tightly b-tagged AK4 Jets; Events",10,-0.5,9.5);



      /////////////more for verifying the CR //////////////////////////////////////
      TH1F* h_AK8_jet_mass_SR  = new TH1F("h_AK8_jet_mass_SR","AK8 Jet Mass (DT region);Mass [GeV]; Events / 30 5GeV",50,0.,1500);
      TH1F* h_AK8_jet_mass_CR  = new TH1F("h_AK8_jet_mass_CR","AK8 Jet Mass (CR);Mass [GeV]; Events / 30 GeV",50,0.,1500);

      TH1F* h_AK4_jet_mass_SR  = new TH1F("h_AK4_jet_mass_SR","AK4 Jet Mass (DT region);Mass [GeV]; Events / 25 GeV",40,0.,1000);
      TH1F* h_AK4_jet_mass_CR  = new TH1F("h_AK4_jet_mass_CR","AK4 Jet Mass (CR);Mass [GeV]; Events / 25 GeV",40,0.,1000);

      TH1F* h_totHT_SR  = new TH1F("h_totHT_SR","Event H_{T} (DT region);H_{T} [GeV]; Events / 200 5GeV",50,0.,10000);
      TH1F* h_totHT_CR  = new TH1F("h_totHT_CR","Event H_{T} (CR);H_{T} [GeV]; Events / 200 GeV",50,0.,10000);

      TH1I* h_nfatjets_SR = new TH1I("h_nfatjets_SR","Number of AK8 Jets (E_{T} > 300 GeV per Event ;nAK8 Jets; Events",10,-0.5,9.5);
      TH1I* h_nfatjets_CR = new TH1I("h_nfatjets_CR","Number of AK8 Jets (E_{T} > 300 GeV per Event ;nAK8 Jets; Events",10,-0.5,9.5);

      TH1I* h_nAK4_SR = new TH1I("h_nAK4_SR","Number of AK4 Jets (E_{T} > 30 GeV per Event ;nAK8 Jets; Events",30,-0.5,29.5);
      TH1I* h_nAK4_CR = new TH1I("h_nAK4_CR","Number of AK4 Jets (E_{T} > 30 GeV per Event ;nAK8 Jets; Events",30,-0.5,29.5);

      TH1F* h_totHT_All  = new TH1F("h_totHT_All","Event H_{T} (All Events from EDAnalyzer);H_{T} [GeV]; Events / 200 GeV",50,0.,10000);
      TH1F* h_totHT_All1  = new TH1F("h_totHT_All1","Event H_{T} (All Events from EDAnalyzer 1);H_{T} [GeV]; Events / 200 GeV",50,0.,10000);
      TH1F* h_totHT_All2  = new TH1F("h_totHT_All2","Event H_{T} (All Events from EDAnalyzer 2 );H_{T} [GeV]; Events / 200 GeV",50,0.,10000);
      TH1F* h_totHT_All3  = new TH1F("h_totHT_All3","Event H_{T} (All Events from EDAnalyzer 3);H_{T} [GeV]; Events / 200 GeV",50,0.,10000);

      TH1F* h_AK4_DeepJet_disc  = new TH1F("h_AK4_DeepJet_disc","AK4 DeepFlavour bdisc scores;bdisc",25,0.,1.25);
      TH1F* h_AK4_DeepJet_disc_all  = new TH1F("h_AK4_DeepJet_disc_all","AK4 DeepFlavour bdisc scores;bdisc",25,0.,1.25);

      TH1I* h_nAK4 = new TH1I("h_nAK4","Number of AK4 jets;# AK4 jets; Events",20,-0.5,19.5);

      int nAntiTaggedAntiTagged = 0;
      int nAntiTaggedTagged     = 0;
      int nTaggedAntiTagged     = 0;
      int nTaggedTagged         = 0;

      int failedHT = 0;
      int failedbTag = 0;
      int failedRatio = 0;
      int failednAK8 = 0;
      //TCanvas *c1 = new TCanvas("c1","",400,20, 2000,2000);
      // run this file four times, once for each of the different 2018 dataset pieces
      
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

      TTree *t1 = (TTree*)f->Get(   (folder_name+ "/skimmedTree_"+ tree_name ).c_str()    );   //need to change this to something relevenet
      const Int_t nentries = t1->GetEntries();

      //std::cout << t1->GetListOfBranches()->FindObject("AK4_partonFlavour") << std::endl;
      //t1->GetListOfBranches()->Print(); 
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
      t1->SetBranchAddress("resonance_mass_comb", &resonance_mass_comb);  
      t1->SetBranchAddress("totMET", &totMET); 
      t1->SetBranchAddress("posSJP", &posSJP); 
      t1->SetBranchAddress("negSJP", &negSJP); 
      t1->SetBranchAddress("AK4_bdisc", AK4_bdisc); 

      t1->SetBranchAddress("AK4_mass", AK4_mass); 

      t1->SetBranchAddress("SJ1_decision", &SJ1_decision); 
      t1->SetBranchAddress("SJ2_decision", &SJ2_decision); 

      t1->SetBranchAddress("lab_AK4_pt", AK4_pt); 

      t1->SetBranchAddress("dijetMassOne", &dijetMassOne); 
      t1->SetBranchAddress("dijetMassTwo", &dijetMassTwo); 

      t1->SetBranchAddress("SJ_E", SJ_E); 
      t1->SetBranchAddress("SJ_Px", SJ_Px); 
      t1->SetBranchAddress("SJ_Py", SJ_Py); 
      t1->SetBranchAddress("SJ_Pz", SJ_Pz); 
      t1->SetBranchAddress("AK4_DeepJet_disc", AK4_DeepJet_disc); 


      int nControlRegion = 0;
      double looseDeepCSV = 0.1241;
      double medDeepCSV   = 0.4184;
      double tightDeepCSV = 0.7527;
      int passHTandAK8 = 0;

    
      double looseDeepCSV_DeepJet = 0.0490;
      double medDeepCSV_DeepJet   = 0.2783;
      double tightDeepCSV_DeepJet = 0.7100;

      for (Int_t i=0;i<nentries;i++) 
      {  
         t1->GetEntry(i);

         h_MSJ_mass_vs_MdSJ_all->Fill(diSuperJet_mass,(superJet_mass[1]+superJet_mass[0])/2. );

         if ( (totHT < 1500.)    ) continue;
         if( (nfatjets < 3) ) continue;
         if ((nfatjet_pre < 2) && ( (dijetMassOne < 1000. ) || ( dijetMassTwo < 1000.)  ))
         {
            continue;
         } 

         h_nAK4->Fill(nAK4);

         int nTightBTags = 0, nMedBTags = 0, nLooseBtags =0;
         for(int iii = 0;iii< nAK4; iii++)
         {
            h_AK4_DeepJet_disc->Fill(AK4_DeepJet_disc[iii]);
            if (  (AK4_DeepJet_disc[iii] > tightDeepCSV_DeepJet ) && (AK4_pt[iii] > 30.) ) nTightBTags++;
            if ( (AK4_DeepJet_disc[iii] > medDeepCSV_DeepJet ) && (AK4_pt[iii] > 30.))     nMedBTags++;
            if ( (AK4_DeepJet_disc[iii] > looseDeepCSV_DeepJet ) && (AK4_pt[iii] > 30.))   nLooseBtags++;
         }
         h_nTightBTags->Fill(nTightBTags);
         h_nMidBTags->Fill(nMedBTags);
         h_nLooseBTags->Fill(nLooseBtags);


         /// QCD control region 
         if( nTightBTags < 1 ) 
         {

               nControlRegion++;
               h_SJ_nAK4_100_CR->Fill(SJ_nAK4_100[0]);
               h_SJ_nAK4_100_CR->Fill(SJ_nAK4_100[1]);

               h_SJ_nAK4_200_CR->Fill(SJ_nAK4_200[0]);
               h_SJ_nAK4_200_CR->Fill(SJ_nAK4_200[1]);

               h_SJ_mass_CR->Fill( (superJet_mass[0]+superJet_mass[1])/2.    );
               //h_SJ_mass_CR->Fill( superJet_mass[0]    );
               //h_SJ_mass_CR->Fill( superJet_mass[1]    );

               h_disuperjet_mass_CR->Fill(diSuperJet_mass);

               h_nfatjets_CR->Fill(nfatjets);
               for(int iii = 0; iii< nfatjets; iii++)
               {
                  h_AK8_jet_mass_CR->Fill(jet_mass[iii]);
               }
               h_nAK4_CR->Fill(nAK4);
               for(int iii = 0; iii< nAK4; iii++)
               {
                  h_AK4_jet_mass_CR->Fill(AK4_mass[iii]);
               }
               
               if(   (SJ_nAK4_300[0]>=2) && (SJ_mass_100[0]>400.)   )
               {
                  if((SJ_nAK4_300[1]>=2) && (SJ_mass_100[1]>=400.)   )
                  {
                     h_totHT_CR->Fill(totHT);
                     h_MSJ_mass_vs_MdSJ_CR->Fill(diSuperJet_mass,(    superJet_mass[1]+superJet_mass[0])/2    );
                  }

               }
         }
            // don't unblind!!!!!!
         // signal region
         if ( (nLooseBtags > 1)  )
         {
         
            h_SJ_nAK4_100_SR->Fill(SJ_nAK4_100[0]);
            h_SJ_nAK4_100_SR->Fill(SJ_nAK4_100[1]);

            h_SJ_nAK4_200_SR->Fill(SJ_nAK4_200[0]);
            h_SJ_nAK4_200_SR->Fill(SJ_nAK4_200[1]);

            h_SJ_mass_SR->Fill(superJet_mass[0]);
            h_SJ_mass_SR->Fill(superJet_mass[1]);


            h_nfatjets_SR->Fill(nfatjets);
            for(int iii = 0; iii< nfatjets; iii++)
            {
               h_AK8_jet_mass_SR->Fill(jet_mass[iii]);
            }
            h_nAK4_SR->Fill(nAK4);
            for(int iii = 0; iii< nAK4; iii++)
            {
               h_AK4_jet_mass_SR->Fill(AK4_mass[iii]);
            }
            h_totHT_SR->Fill(totHT);

         
            //double tagging CUT BASED
            if(   (SJ_nAK4_300[0]>=2) && (SJ_mass_100[0]>400.)   )
            {
               if((SJ_nAK4_300[1]>=2) && (SJ_mass_100[1]>=400.)   )
               {
                  h_MSJ_mass_vs_MdSJ_doubleTag->Fill( diSuperJet_mass, (superJet_mass[1]+superJet_mass[0]   )/2.   );
               }
            }
            h_disuperjet_mass_SR->Fill(diSuperJet_mass);
            if(   (SJ_nAK4_300[0]>=2) && (SJ_mass_100[0]>400.)   )
            {
               if((SJ_nAK4_300[1]>=2) && (SJ_mass_100[1]>=400.)   )
               {
                  h_MSJ_mass_vs_MdSJ_SR->Fill(diSuperJet_mass,(    superJet_mass[1]+superJet_mass[0])/2    );
               }

         
            }
         }
         outFile.Write();
      }
   }
   outFile.Close();
}


void readTreeData()
{
   std::vector<std::string> years = {"2015","2016","2017","2018"};
   std::vector<std::string> systematics = {"JER","JEC","nom"};  //TESTING
   for(auto year=years.begin();year<years.end();year++)
   {

      for(auto systematic = systematics.begin(); systematic < systematics.end();systematic++ )
      {
         std::vector<std::string> dataBlocks; 
         if(*year == "2015")
         {
            dataBlocks = {"dataB-ver1","dataB-ver2","dataC-HIPM","dataD-HIPM","dataE-HIPM","dataF-HIPM"};
         }
         else if(*year == "2016")
         {
            dataBlocks = {"dataF", "dataG", "dataH"};
         }
         else if(*year == "2017")
         {
            dataBlocks = {"dataB","dataC","dataD","dataE", "dataF"};
         }
         else if(*year == "2018")
         {
            dataBlocks = {"dataA","dataB","dataC","dataD"};
         }
         
         for(dataBlock = dataBlocks.begin();dataBlock < dataBlocks.end();dataBlock++)
         {

            std::string inFileName = "/Users/ethan/Documents/rootFiles/skimmedRootFilesData/JetHT_"+ *dataBlock+"_"+*year+"_SKIMMED.root";
            std::string outFileName = "/Users/ethan/Documents/rootFiles/processedRootFilesData/JetHT_"+ *dataBlock+"_"+*year+"_processed.root";
           
            doThings(inFileName,outFileName,*year,*dataBlock,*systematic);

            std::cout << "Finished with "<< inFileName << std::endl;
         }
      }
   }
}
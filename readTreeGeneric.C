#include <iostream>
#include <string>
#include "TLorentzVector.h"
using namespace std;

double func(double x, double NNdisc, double cutDisc)
{
    double shift = 1450.;
    double scale = 3500.;
    return ( cutDisc*pow(( exp((x-shift)/scale) - exp(-(x-shift)/scale)   )/(exp((x-shift)/scale) + exp(-(x-shift)/scale)),4)  + NNdisc*(1 - pow(( exp((x-shift)/scale) - exp(-(x-shift)/scale)   )/(exp((x-shift)/scale) + exp(-(x-shift)/scale)),4) ) );
}


void readTreeGeneric()
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
   double SJ_mass_300[100], AK4_DeepJet_disc[100];;
   double posSJP, negSJP;
   double totMET;
   double AK4_bdisc[100],SJ1_BEST_scores[100],SJ2_BEST_scores[100];
   double AK4_pt[100];
   double diSuperJet_mass, diSuperJet_mass_100;
   double SJ_E[2],SJ_Px[2],SJ_Py[2],SJ_Pz[2];
   int SJ1_decision, SJ2_decision;
   //have to multiply these by scale factors  
   double resonance_mass_comb;
   double daughter_mass_comb[100];
   double SJ1_mass_genParts,SJ2_mass_genParts;
   std::string sampleStringSuu = "8";
   std::string sampleStringChi = "3";

   //4-1.5, 5-1.5,6-1.5,6-1,6-2,8-1,8-2,8-3



   std::string styleString = "cutbased";

   TFile *f = new TFile( "/home/ethan/Documents/rootFiles/signalRootFiles/ClusteringAlgorithm_Zprime_output.root");
   
   //cut based

   TFile outFile("/home/ethan/Documents/rootFiles/processedRootFiles/ClusteringAlgorithm_generic_output.root","RECREATE");

   double dijetMassOne, dijetMassTwo;

   TTree *t1 = (TTree*)f->Get("clusteringAnalyzerAll/tree");   //need to change this to something relevenet
   const Int_t nentries = t1->GetEntries();


   TH2F *h_Mjet_vs_pTjet = new TH2F("h_Mjet_vs_pTjet","Jet Mass vs Jet pT; jet p_{T} [GeV];jet mass", 80,0, 4000, 50, 0, 2000);

   TH1F* h_SJ_ratio  = new TH1F("h_SJ_mass_ratio","Superjet Mass Ratio;M_{SJ1}/M_{SJ2}; Events",50,-2.5,2.5);
   TH1F* h_diSJ_SJ_mass_ratio  = new TH1F("h_diSJ_SJ_mass_ratio","M_{diSJ} / (M_{SJ1} + M_{SJ2})",50,0.,10);

   TH1F* h_SJ_mass  = new TH1F("h_SJ_mass","Superjet (VLQ) Mass; Events / 125 GeV ",30,0.,1500);
   TH1F* h_disuperjet_mass  = new TH1F("h_disuperjet_mass","diSuperjet (S_{uu}) Mass; Events / 200 GeV ",50,0.,6000);


   TH1F* h_MSJ1_MSJ2_ratio  = new TH1F("h_MSJ1_MSJ2_ratio","(M_{SJ_{1}} - M_{SJ_{2}})/(M_{SJ_{1}} + M_{SJ_{2}});",30,-3.,3.0);
   TH1F* h_MdiSJ_SJ12_ratios  = new TH1F("h_MdiSJ_SJ12_ratios","M_{diSJ} / (M_{SJ_{1}} + M_{SJ_{2}})",25,0.,5.0);
   TH2F *h_MSJ_mass_vs_MdSJ = new TH2F("h_MSJ_mass_vs_MdSJ","Anti-tagged event, tagged Superjet mass vs diSuperjet mass - MC Signal; diSuperjet mass [GeV];superjet mass", 25,0, 10000, 20, 0, 6000);
   TH2F *h_MSJ_mass_vs_MdSJ_DT = new TH2F( "h_MSJ_mass_vs_MdSJ_DT","Avg Double Tagged (Cut-based) Superjet Mass vs diSuperjet mass; diSuperjet mass [GeV];avg superjet (VLQ) mass", 25,0, 6000, 20, 0, 1500);
   TH2F *h_MSJ_mass_vs_MdSJ_DTNN = new TH2F( "h_MSJ_mass_vs_MdSJ_DTNN",("Avg Double Tagged (NN-based) Superjet Mass vs diSuperjet mass - MC Signal (M_{S_{uu}} = "+ sampleStringSuu +", M_{chi} = "+sampleStringChi+ "); diSuperjet mass [GeV];avg superjet (VLQ) mass").c_str(), 25,0, 10000, 20, 0, 6000);

   TH1I* h_NN_categories = new TH1I("h_NN_categories","Superjet NN Categorizations; Events",5,0,5);

   TH1I* h_nLooseBTags = new TH1I("h_nLooseBTags","Number of Loosely b-tagged AK4 Jets; Events",10,-0.5,9.5);
   TH1I* h_nMidBTags = new TH1I("h_nMidBTags","Number of Mediumly b-tagged AK4 Jets; Events",10,-0.5,9.5);
   TH1I* h_nTightBTags = new TH1I("h_nTightBTags","Number of Tightly b-tagged AK4 Jets; Events",10,-0.5,9.5);

      // control region stuff 
   TH1I* h_SJ_nAK4_100_CR  = new TH1I("h_SJ_nAK4_100_CR","Number of Reclustered AK4 Jets (E_{COM} > 100 GeV) per SJ (Control Region);nAK4 Jets (E_{COM} > 100 GeV); Events",10,-0.5,9.5);
   TH1I* h_SJ_nAK4_200_CR  = new TH1I("h_SJ_nAK4_200_CR","Number of Reclustered AK4 Jets (E_{COM} > 200 GeV) per SJ (Control Region);nAK4 Jets (E_{COM} > 200 GeV); Events",10,-0.5,9.5);
   TH1F* h_SJ_mass_CR  = new TH1F("h_SJ_mass_CR","SuperJet Mass (Control Region) ;Mass [GeV]; Events / 100 GeV",40,0.,4000);
   TH1F* h_disuperjet_mass_CR  = new TH1F("h_disuperjet_mass_CR","diSuperJet Mass (Control Region);Mass [GeV]; Events / 200 GeV",50,0.,10000);
   TH2F *h_MSJ_mass_vs_MdSJ_CR = new TH2F("h_MSJ_mass_vs_MdSJ_CR","Double Tagged Superjet mass vs diSuperjet mass (Control Region); diSuperjet mass [GeV];superjet mass", 25,0, 10000, 20, 0, 6000);

   TH1F* h_combinedNNScores  = new TH1F("h_combinedNNScores","Combined NN Scores (quadrature); NN Scores",40,0.,4.0);
   TH1F* h_cutDisc  = new TH1F("h_cutDisc","Cut-Based Discriminator; disc value",40,0.,8.0);
   TH1F* h_totalDisc  = new TH1F("h_totalDisc","Combined NN & CB Discriminator; disc value",40,0.,4.0);

   TH1F* h_SJ1_mass_genParts  = new TH1F("h_SJ1_mass_genParts","Superjet 1 Mass (gen particles); Mass [GeV]",40,0.,6000);
   TH1F* h_SJ2_mass_genParts  = new TH1F("h_SJ2_mass_genParts","Superjet 2 Mass (gen particles); Mass [GeV]",40,0.,6000);
   TH2F *h_MSJ1_vs_MSJ2_gen = new TH2F( "h_MSJ1_vs_MSJ2_gen","Superjet 1 Mass vs Superjet 2 Mass (gen particles);Superjet 1 mass [GeV]; Superjet 2 mass [GeV]", 20,0, 6000, 20, 0, 6000);



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
   t1->SetBranchAddress("AK4_mass", AK4_mass); 
   t1->SetBranchAddress("AK4_bdisc", AK4_bdisc); 

   t1->SetBranchAddress("posSJP", &posSJP); 
   t1->SetBranchAddress("negSJP", &negSJP); 


   t1->SetBranchAddress("SJ1_decision", &SJ1_decision); 
   t1->SetBranchAddress("SJ2_decision", &SJ2_decision); 

   t1->SetBranchAddress("SJ_E", SJ_E); 
   t1->SetBranchAddress("SJ_Px", SJ_Px); 
   t1->SetBranchAddress("SJ_Py", SJ_Py); 
   t1->SetBranchAddress("SJ_Pz", SJ_Pz); 
   t1->SetBranchAddress("lab_AK4_pt", AK4_pt); 
   t1->SetBranchAddress("AK4_DeepJet_disc", AK4_DeepJet_disc); 

   t1->SetBranchAddress("SJ1_BEST_scores", SJ1_BEST_scores); 
   t1->SetBranchAddress("SJ2_BEST_scores", SJ2_BEST_scores); 

   t1->SetBranchAddress("SJ1_mass_genParts", &SJ1_mass_genParts); 
   t1->SetBranchAddress("SJ2_mass_genParts", &SJ2_mass_genParts); 

   
   int totalEvents = 0;
   int nPreselected = 0;
   int nDoubleTagged = 0;

   int nDoubleTaggedNN = 0;
   int nAntiTaggedTagged = 0;
   int nAntiTaggedEvents = 0;

   int passHTandAK8 =0;
   double looseDeepCSV = 0.1241;
   double medDeepCSV   = 0.4184;
   double tightDeepCSV = 0.7527;

   double looseDeepCSV_DeepJet = 0.0490;
   double medDeepCSV_DeepJet   = 0.2783;
   double tightDeepCSV_DeepJet = 0.7100;

   int nControlRegion = 0;
   int nPassPreSelection = 0;
   for (Int_t i=0;i<nentries;i++) 
   {  

      t1->GetEntry(i);
      totalEvents++;
      h_MSJ1_vs_MSJ2_gen->Fill(SJ1_mass_genParts,SJ2_mass_genParts);
      h_SJ1_mass_genParts->Fill(SJ1_mass_genParts);
      h_SJ2_mass_genParts->Fill(SJ2_mass_genParts);
      double cutDisc = ( (SJ_nAK4_300[0]/2.)+ (SJ_mass_100[0]/400.) + (SJ_nAK4_300[1]/2.)+ SJ_mass_100[1]/400.      )/(4);

      //double combinedNNScore = sqrt(pow(SJ1_BEST_scores[0],2)+pow(SJ1_BEST_scores[1],2)+pow(SJ1_BEST_scores[2],2)) + sqrt(pow(SJ2_BEST_scores[0],2)+pow(SJ2_BEST_scores[1],2)+pow(SJ2_BEST_scores[2],2)) ;
      double combinedNNScore =     sqrt( pow( SJ1_BEST_scores[0] + SJ1_BEST_scores[1] + SJ1_BEST_scores[2],2 ) + pow( SJ2_BEST_scores[0] + SJ2_BEST_scores[1] + SJ2_BEST_scores[2],2));

      h_combinedNNScores->Fill(combinedNNScore  );
      h_cutDisc->Fill(cutDisc);
      h_totalDisc->Fill(func(totHT,combinedNNScore,cutDisc));

      /*
      if( (nfatjets < 2) || (totHT < 1500.)     ) continue;

      if ((nfatjet_pre < 2) && ( (dijetMassOne < 1000. ) || ( dijetMassTwo < 1000.)  ))
      {
         continue;
      } 
   */
      int nTightBTags = 0, nMedBTags = 0, nLooseBtags =0;
      for(int iii = 0;iii< nAK4; iii++)
      {
         if ( (AK4_DeepJet_disc[iii] > tightDeepCSV_DeepJet )) nTightBTags++;
         if ( (AK4_DeepJet_disc[iii] > medDeepCSV_DeepJet   )) nMedBTags++;
         if ( (AK4_DeepJet_disc[iii] > looseDeepCSV_DeepJet )) nLooseBtags++;
      }
      h_nTightBTags->Fill(nTightBTags);
      h_nMidBTags->Fill(nMedBTags);
      h_nLooseBTags->Fill(nLooseBtags);

      nPassPreSelection++;

      h_NN_categories->Fill(SJ1_decision);
      h_NN_categories->Fill(SJ2_decision);

      // control region
      if( (nTightBTags < 1) ) 
      {

            h_SJ_nAK4_100_CR->Fill(SJ_nAK4_100[0]);
            h_SJ_nAK4_100_CR->Fill(SJ_nAK4_100[1]);

            h_SJ_nAK4_200_CR->Fill(SJ_nAK4_200[0]);
            h_SJ_nAK4_200_CR->Fill(SJ_nAK4_200[1]);

            h_SJ_mass_CR->Fill(superJet_mass[0]);
            h_SJ_mass_CR->Fill(superJet_mass[1]);

            h_disuperjet_mass_CR->Fill(diSuperJet_mass);
            if(   (SJ_nAK4_300[0]>=2) && (SJ_mass_100[0]>400.)   )
            {
               if((SJ_nAK4_300[1]>=2) && (SJ_mass_100[1]>=400.)   )
               {
                  h_MSJ_mass_vs_MdSJ_CR->Fill(diSuperJet_mass,(    superJet_mass[1]+superJet_mass[0])/2    );
               }

            }
            nControlRegion++;         
      }
      h_MSJ_mass_vs_MdSJ_DT->Fill(diSuperJet_mass,(    superJet_mass[1]+superJet_mass[0])/2    );
      h_disuperjet_mass->Fill(diSuperJet_mass);

      h_MSJ_mass_vs_MdSJ_DT->Fill(diSuperJet_mass,(    superJet_mass[1]+superJet_mass[0])/2    );
      h_SJ_mass->Fill( (superJet_mass[0]+superJet_mass[1])/2.   );

      /*
      //signal region double tagging  CUT BASED
      if ( nTightBTags > 0)
      {
         nPreselected++;

         h_disuperjet_mass->Fill(diSuperJet_mass);
         if(  (SJ_nAK4_300[0]>=2) && (SJ_mass_100[0]>=400.)   )
         {
            if((SJ_nAK4_300[1]>=2) && (SJ_mass_100[1]>=400.)   )
            {
               nDoubleTagged++;
               h_MSJ_mass_vs_MdSJ_DT->Fill(diSuperJet_mass,(    superJet_mass[1]+superJet_mass[0])/2    );
               h_SJ_mass->Fill( (superJet_mass[0]+superJet_mass[1])/2.   );
            }
         }



               // double tagging NN based
         if(  (SJ1_decision<3) && (SJ2_decision<3)  )
         {
               nDoubleTaggedNN++;
               h_MSJ_mass_vs_MdSJ_DTNN->Fill(diSuperJet_mass,(    superJet_mass[1]+superJet_mass[0])/2    );

         }

      }
      */

   }
   outFile.Write();


}





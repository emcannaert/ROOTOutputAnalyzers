#include <iostream>
#include <string>
#include "TLorentzVector.h"

using namespace std;


void readTree()
{
   Float_t SJ_mass,
SJ_mass_25,
SJ_mass_50,
SJ_mass_100,
SJ_mass_150,
SJ_mass_200,
SJ_mass_300,
SJ_nAK4_25,
SJ_nAK4_50,
SJ_nAK4_100,
SJ_nAK4_150,
SJ_nAK4_200,
SJ_nAK4_300,
AK4_m1,
AK4_m2,
AK4_m3,
AK4_m4,
AK4_m12,
AK4_m13,
AK4_m14,
AK4_m23,
AK4_m24,
AK4_m34,
AK4_m123,
AK4_m124,
AK4_m134,
AK4_m234,
AK4_m1234,
AK41_E,
AK42_E,
AK43_E,
AK44_E,
AK4_theta12,
AK4_theta13,
AK4_theta14,
AK4_theta23,
AK4_theta24,
AK4_theta34,
AK41_ndaughters,
AK41_nsubjets,
AK41_thrust,
AK41_sphericity,
AK41_asymmetry,
AK41_isotropy,
AK41_aplanarity,
AK41_FW1,
AK41_FW2,
AK41_FW3,
AK41_FW4,
AK42_ndaughters,
AK42_nsubjets,
AK42_thrust,
AK42_sphericity,
AK42_asymmetry,
AK42_isotropy,
AK42_aplanarity,
AK42_FW1,
AK42_FW2,
AK42_FW3,
AK42_FW4,
AK43_ndaughters,
AK43_nsubjets,
AK43_thrust,
AK43_sphericity,
AK43_asymmetry,
AK43_isotropy,
AK43_aplanarity,
AK43_FW1,
AK43_FW2,
AK43_FW3,
AK43_FW4,
SJ_thrust,
SJ_sphericity,
SJ_asymmetry,
SJ_isotropy,
SJ_aplanarity,
SJ_FW1,
SJ_FW2,
SJ_FW3,
SJ_FW4;

   TFile *f = new TFile("/home/ethan/mergedRootFiles/QCD2000toInf_combined_new.root");
   //TFile outFile("/home/ethan/Documents/clustAlgBR_ttbar_processed_.root","RECREATE");

   //TCanvas *c1 = new TCanvas("c1","",400,20, 2000,2000);

////////////////////////Change this to go back do diquark! Change the tree
   TTree *t1 = (TTree*)f->Get("run/jetTree");
   const Int_t nentries = t1->GetEntries();

////////////////////////////////////////////////////////////////////////////////////////////////////////

        //SJ mass variables
        t1->SetBranchAddress("SJ_mass",&SJ_mass);
        t1->SetBranchAddress("SJ_mass_25",&SJ_mass_25);
        t1->SetBranchAddress("SJ_mass_50",&SJ_mass_50);
        t1->SetBranchAddress("SJ_mass_100",&SJ_mass_100);
        t1->SetBranchAddress("SJ_mass_150",&SJ_mass_150);
        t1->SetBranchAddress("SJ_mass_200",&SJ_mass_200);
        t1->SetBranchAddress("SJ_mass_300",&SJ_mass_300);

        //SJ nAK4 variables
        t1->SetBranchAddress("SJ_nAK4_25",&SJ_nAK4_25);
        t1->SetBranchAddress("SJ_nAK4_50",&SJ_nAK4_50);
        t1->SetBranchAddress("SJ_nAK4_100",&SJ_nAK4_100);
        t1->SetBranchAddress("SJ_nAK4_150",&SJ_nAK4_150);
        t1->SetBranchAddress("SJ_nAK4_200",&SJ_nAK4_200);
        t1->SetBranchAddress("SJ_nAK4_300",&SJ_nAK4_300);

        //softdrop mass???
        //bjet particle percentages
        t1->SetBranchAddress("AK4_m1",&AK4_m1);  
        t1->SetBranchAddress("AK4_m2",&AK4_m2);
        t1->SetBranchAddress("AK4_m3",&AK4_m3);
        t1->SetBranchAddress("AK4_m4",&AK4_m4);

        t1->SetBranchAddress("AK4_m12",&AK4_m12);  
        t1->SetBranchAddress("AK4_m13",&AK4_m13);  
        t1->SetBranchAddress("AK4_m14",&AK4_m14);  
        t1->SetBranchAddress("AK4_m23",&AK4_m23);  
        t1->SetBranchAddress("AK4_m24",&AK4_m24);  
        t1->SetBranchAddress("AK4_m34",&AK4_m34);  

        t1->SetBranchAddress("AK4_m123",&AK4_m123);  
        t1->SetBranchAddress("AK4_m124",&AK4_m124);  
        t1->SetBranchAddress("AK4_m134",&AK4_m134);  
        t1->SetBranchAddress("AK4_m234",&AK4_m234);  

        t1->SetBranchAddress("AK4_m1234",&AK4_m1234);  

        t1->SetBranchAddress("AK41_E",&AK41_E);  
        t1->SetBranchAddress("AK42_E",&AK42_E);  
        t1->SetBranchAddress("AK43_E",&AK43_E);  
        t1->SetBranchAddress("AK44_E",&AK44_E);  

        //reclustered AK4 jet angles
        t1->SetBranchAddress("AK4_theta12",&AK4_theta12);   
        t1->SetBranchAddress("AK4_theta13",&AK4_theta13);
        t1->SetBranchAddress("AK4_theta14",&AK4_theta14);
        t1->SetBranchAddress("AK4_theta23",&AK4_theta23);
        t1->SetBranchAddress("AK4_theta24",&AK4_theta24);
        t1->SetBranchAddress("AK4_theta34",&AK4_theta34);

        //AK4 jet boosted information - boost reclustered AK4 jets into their COM and look at BES variables, ndaughters, nsubjettiness
        t1->SetBranchAddress("AK41_ndaughters",&AK41_ndaughters);
        t1->SetBranchAddress("AK41_nsubjets",&AK41_nsubjets);
        t1->SetBranchAddress("AK41_thrust",&AK41_thrust);
        t1->SetBranchAddress("AK41_sphericity",&AK41_sphericity);
        t1->SetBranchAddress("AK41_asymmetry",&AK41_asymmetry);
        t1->SetBranchAddress("AK41_isotropy",&AK41_isotropy);
        t1->SetBranchAddress("AK41_aplanarity",&AK41_aplanarity);
        t1->SetBranchAddress("AK41_FW1",&AK41_FW1);
        t1->SetBranchAddress("AK41_FW2",&AK41_FW2);
        t1->SetBranchAddress("AK41_FW3",&AK41_FW3);
        t1->SetBranchAddress("AK41_FW4",&AK41_FW4);

        t1->SetBranchAddress("AK42_ndaughters",&AK42_ndaughters);
        t1->SetBranchAddress("AK42_nsubjets",&AK42_nsubjets);
        t1->SetBranchAddress("AK42_thrust",&AK42_thrust);
        t1->SetBranchAddress("AK42_sphericity",&AK42_sphericity);
        t1->SetBranchAddress("AK42_asymmetry",&AK42_asymmetry);
        t1->SetBranchAddress("AK42_isotropy",&AK42_isotropy);
        t1->SetBranchAddress("AK42_aplanarity",&AK42_aplanarity);
        t1->SetBranchAddress("AK42_FW1",&AK42_FW1);
        t1->SetBranchAddress("AK42_FW2",&AK42_FW2);
        t1->SetBranchAddress("AK42_FW3",&AK42_FW3);
        t1->SetBranchAddress("AK42_FW4",&AK42_FW4);

        t1->SetBranchAddress("AK43_ndaughters",&AK43_ndaughters);
        t1->SetBranchAddress("AK43_nsubjets",&AK43_nsubjets);
        t1->SetBranchAddress("AK43_thrust",&AK43_thrust);
        t1->SetBranchAddress("AK43_sphericity",&AK43_sphericity);
        t1->SetBranchAddress("AK43_asymmetry",&AK43_asymmetry);
        t1->SetBranchAddress("AK43_isotropy",&AK43_isotropy);
        t1->SetBranchAddress("AK43_aplanarity",&AK43_aplanarity);
        t1->SetBranchAddress("AK43_FW1",&AK43_FW1);
        t1->SetBranchAddress("AK43_FW2",&AK43_FW2);
        t1->SetBranchAddress("AK43_FW3",&AK43_FW3);
        t1->SetBranchAddress("AK43_FW4",&AK43_FW4);
        //SJ BES variables
        t1->SetBranchAddress("SJ_thrust",&SJ_thrust);
        t1->SetBranchAddress("SJ_sphericity",&SJ_sphericity);
        t1->SetBranchAddress("SJ_asymmetry",&SJ_asymmetry);
        t1->SetBranchAddress("SJ_isotropy",&SJ_isotropy);
        t1->SetBranchAddress("SJ_aplanarity",&SJ_aplanarity);
        t1->SetBranchAddress("SJ_FW1",&SJ_FW1);
        t1->SetBranchAddress("SJ_FW2",&SJ_FW2);
        t1->SetBranchAddress("SJ_FW3",&SJ_FW3);
        t1->SetBranchAddress("SJ_FW4",&SJ_FW4);

   for (Int_t i=0;i<nentries;i++) 
   {  
      t1->GetEntry(i);
      std::vector<Float_t> allVars;
      allVars.push_back(SJ_mass);
      allVars.push_back(SJ_mass_25);
      allVars.push_back(SJ_mass_50);
      allVars.push_back(SJ_mass_100);
      allVars.push_back(SJ_mass_150);
      allVars.push_back(SJ_mass_200);
      allVars.push_back(SJ_mass_300);
      allVars.push_back(SJ_nAK4_25);
      allVars.push_back(SJ_nAK4_50);
      allVars.push_back(SJ_nAK4_100);
      allVars.push_back(SJ_nAK4_150);
      allVars.push_back(SJ_nAK4_200);
      allVars.push_back(SJ_nAK4_300);
      allVars.push_back(AK4_m1);
      allVars.push_back(AK4_m2);
      allVars.push_back(AK4_m3);
      allVars.push_back(AK4_m4);
      allVars.push_back(AK4_m12);
      allVars.push_back(AK4_m13);
      allVars.push_back(AK4_m14);
      allVars.push_back(AK4_m23);
      allVars.push_back(AK4_m24);
      allVars.push_back(AK4_m34);
      allVars.push_back(AK4_m123);
      allVars.push_back(AK4_m124);
      allVars.push_back(AK4_m134);
      allVars.push_back(AK4_m234);
      allVars.push_back(AK4_m1234);
      allVars.push_back(AK41_E);
      allVars.push_back(AK42_E);
      allVars.push_back(AK43_E);
      allVars.push_back(AK44_E);
      allVars.push_back(AK4_theta12);
      allVars.push_back(AK4_theta13);
      allVars.push_back(AK4_theta14);
      allVars.push_back(AK4_theta23);
      allVars.push_back(AK4_theta24);
      allVars.push_back(AK4_theta34);
      allVars.push_back(AK41_ndaughters);
      allVars.push_back(AK41_nsubjets);
      allVars.push_back(AK41_thrust);
      allVars.push_back(AK41_sphericity);
      allVars.push_back(AK41_asymmetry);
      allVars.push_back(AK41_isotropy);
      allVars.push_back(AK41_aplanarity);
      allVars.push_back(AK41_FW1);
      allVars.push_back(AK41_FW2);
      allVars.push_back(AK41_FW3);
      allVars.push_back(AK41_FW4);
      allVars.push_back(AK42_ndaughters);
      allVars.push_back(AK42_nsubjets);
      allVars.push_back(AK42_thrust);
      allVars.push_back(AK42_sphericity);
      allVars.push_back(AK42_asymmetry);
      allVars.push_back(AK42_isotropy);
      allVars.push_back(AK42_aplanarity);
      allVars.push_back(AK42_FW1);
      allVars.push_back(AK42_FW2);
      allVars.push_back(AK42_FW3);
      allVars.push_back(AK42_FW4);
      allVars.push_back(AK43_ndaughters);
      allVars.push_back(AK43_nsubjets);
      allVars.push_back(AK43_thrust);
      allVars.push_back(AK43_sphericity);
      allVars.push_back(AK43_asymmetry);
      allVars.push_back(AK43_isotropy);
      allVars.push_back(AK43_aplanarity);
      allVars.push_back(AK43_FW1);
      allVars.push_back(AK43_FW2);
      allVars.push_back(AK43_FW3);
      allVars.push_back(AK43_FW4);
      allVars.push_back(SJ_thrust);
      allVars.push_back(SJ_sphericity);
      allVars.push_back(SJ_asymmetry);
      allVars.push_back(SJ_isotropy);
      allVars.push_back(SJ_aplanarity);
      allVars.push_back(SJ_FW1);
      allVars.push_back(SJ_FW2);
      allVars.push_back(SJ_FW3);
      allVars.push_back(SJ_FW4);

      int counter =0;
      for ( auto iV = allVars.begin(); iV != allVars.end(); iV++)
      {
         if ( (*iV != *iV ) || ( isinf(*iV)   ) ) std::cout << "Problem with var num " << counter << " , value is " <<  *iV << "/" << std::endl;
         counter++;
      }
   }



   //outFile.Write();
   //outFile.Close();

}


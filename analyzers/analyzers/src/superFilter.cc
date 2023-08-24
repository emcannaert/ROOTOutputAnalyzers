// -*- C++ -*-
//
// Package:    superFilter/superFilter
// Class:      superFilter
// 
/**\class superFilter superFilter.cc superFilter/superFilter/plugins/superFilter.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Ethan Cannaert
//         Created:  Mon, 29 Mar 2021 15:55:02 GMT
//
//


// system include files
// user include files
#include "FWCore/Framework/interface/stream/EDFilter.h"
#include "FWCore/Utilities/interface/StreamID.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Tau.h"

#include <fastjet/JetDefinition.hh>
#include <fastjet/GhostedAreaSpec.hh>
#include <fastjet/PseudoJet.hh>
#include <fastjet/tools/Filter.hh>
#include <fastjet/ClusterSequence.hh>
//#include <fastjet/ActiveAreaSpec.hh>
#include <fastjet/ClusterSequenceArea.hh>

#include <memory>
#include <iostream>
#include <fstream>
#include <vector>
// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
// new includes
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/JetReco/interface/GenJet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/Math/interface/PtEtaPhiMass.h"
#include "DataFormats/Candidate/interface/Candidate.h"

#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"
//#include "PhysicsTools/CandUtils/interface/Thrust.h"
#include <TTree.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TGraph.h>
#include <cmath>
#include "TLorentzVector.h"
#include "TVector3.h"

#include "DataFormats/Candidate/interface/Candidate.h"
#include  "DataFormats/PatCandidates/interface/PackedCandidate.h"

#include <algorithm>   

#include "FWCore/Framework/interface/EDProducer.h"
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
#include <DataFormats/Math/interface/deltaR.h>
#include "FWCore/Utilities/interface/EDGetToken.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include <string>
// class declaration
//

class superFilter : public edm::stream::EDFilter<> {
   public:
      explicit superFilter(const edm::ParameterSet&);
      ~superFilter();
      bool isgoodjet(const float eta, const float NHF,const float NEMF, const size_t NumConst,const float CHF,const int CHM, const float MUF, const float CEMF);
      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
      bool isgoodjet(const float eta, const float NHF,const float NEMF, const size_t NumConst,const float CHF,const int CHM, const float MUF, const float CEMF, int nfatjets);

   private:
      virtual void beginStream(edm::StreamID) override;
      virtual bool filter(edm::Event&, const edm::EventSetup&) override;
      virtual void endStream() override;
      edm::EDGetTokenT<std::vector<pat::Jet>> fatJetToken_;
      edm::EDGetTokenT<std::vector<pat::Jet>> jetToken_;
      edm::EDGetTokenT<edm::TriggerResults> triggerBits_;

      //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
      //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

      // ----------member data ---------------------------
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
superFilter::superFilter(const edm::ParameterSet& iConfig)
{
   //now do what ever initialization is needed
   fatJetToken_ =    consumes<std::vector<pat::Jet>>(iConfig.getParameter<edm::InputTag>("fatJetCollection"));
   triggerBits_ = consumes<edm::TriggerResults>(iConfig.getParameter<edm::InputTag>("bits"));
   jetToken_    = consumes<std::vector<pat::Jet>>(iConfig.getParameter<edm::InputTag>("jetCollection"));
}


superFilter::~superFilter()
{
 
   // do anything here that needs to be done at destruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//
bool superFilter::isgoodjet(const float eta, const float NHF,const float NEMF, const size_t NumConst,const float CHF,const int CHM, const float MUF, const float CEMF)
{
   if( (abs(eta) > 2.5)) return false;

   if ((NHF>0.9) || (NEMF>0.9) || (NumConst<1) || (CHF<0.) || (CHM<0) || (MUF > 0.8) || (CEMF > 0.8)) 
      {
         return false;
      }
   else{ return true;}

}
bool superFilter::isgoodjet(const float eta, const float NHF,const float NEMF, const size_t NumConst,const float CHF,const int CHM, const float MUF, const float CEMF, int nfatjets)
{
   if ( (nfatjets < 2) && (abs(eta) > 2.4) ) return false;
   else if ( (nfatjets >= 2) && (abs(eta) > 1.5) ) return false;

   if ((NHF>0.9) || (NEMF>0.9) || (NumConst<1) || (CHF<0.) || (CHM<0) || (MUF > 0.8) || (CEMF > 0.8)) 
      {
         return false;
      }
   else{ return true;}
}
// ------------ method called on each new Event  ------------
bool superFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
/////////////////Trigger///////////////

   edm::Handle<edm::TriggerResults> triggerBits;
   iEvent.getByToken(triggerBits_, triggerBits);
   const edm::TriggerNames &names = iEvent.triggerNames(*triggerBits);

   bool pass = false;
   std::string trigname= "HLT_PFHT1050_v";
   for (unsigned int i = 0; i < triggerBits->size(); ++i) 
   {
      const std::string name = names.triggerName(i);
      const bool accept = triggerBits->accept(i);
      if ((name.find(trigname) != std::string::npos) &&(accept)) pass =true;
   }

   if(!pass)
   {  
       return false;
   }

   //std::cout << "Pases trigger" << std::endl;
   //calculate HT -> make HT > 1250. GeV


///////////////////////////AK4 jets  && HT
   int nAK4 = 0;
   double totHT = 0;
   double dijetMassOne =0, dijetMassTwo=0;
   edm::Handle<std::vector<pat::Jet> > smallJets;
   iEvent.getByToken(jetToken_, smallJets);
   int nBtaggedAK4 = 0;
   std::vector<TLorentzVector> leadAK4Jets;
   for(auto iJet = smallJets->begin(); iJet != smallJets->end(); iJet++) 
   {  

      //loose WP 0.1522
      if( (iJet->pt()  <30.) || (!(iJet->isPFJet())) || (!isgoodjet(iJet->eta(),iJet->neutralHadronEnergyFraction(), iJet->neutralEmEnergyFraction(),iJet->numberOfDaughters(),iJet->chargedHadronEnergyFraction(),iJet->chargedMultiplicity(),iJet->muonEnergyFraction(),iJet->chargedEmEnergyFraction())) ) continue;
      if(iJet->pt() > 30.)totHT+= abs(iJet->pt() );
      if(nAK4 < 4) leadAK4Jets.push_back(TLorentzVector(iJet->px(),iJet->py(),iJet->pz(),iJet->energy()));
      if( ((iJet->bDiscriminator("pfDeepCSVJetTags:probb") + iJet->bDiscriminator("pfDeepCSVJetTags:probbb") )< 0.4184)||(iJet->pt() < 30.) )continue;
      //loose
      nBtaggedAK4++;
      nAK4++;
   }
   if(nAK4<4)return false;
   double minDeltaRDisc12 = sqrt( pow(leadAK4Jets[0].DeltaR(leadAK4Jets[1]),2) + pow(leadAK4Jets[2].DeltaR(leadAK4Jets[3]),2));
   double minDeltaRDisc13 = sqrt( pow(leadAK4Jets[0].DeltaR(leadAK4Jets[2]),2) + pow(leadAK4Jets[1].DeltaR(leadAK4Jets[3]),2));
   double minDeltaRDisc14 = sqrt( pow(leadAK4Jets[0].DeltaR(leadAK4Jets[3]),2) + pow(leadAK4Jets[1].DeltaR(leadAK4Jets[2]),2));

   if (  abs(std::min(minDeltaRDisc12, std::min(minDeltaRDisc13,minDeltaRDisc14)) -minDeltaRDisc12)<1e-8 )
   {
      //set dijet masses
      dijetMassOne = (leadAK4Jets[0] +leadAK4Jets[1]).M();
      dijetMassTwo = (leadAK4Jets[2] +leadAK4Jets[3]).M();
   }
   else if (  abs(std::min(minDeltaRDisc12, std::min(minDeltaRDisc13,minDeltaRDisc14)) -minDeltaRDisc13)<1e-8 )
   {
      // set dijet masses
      dijetMassOne = (leadAK4Jets[0] +leadAK4Jets[2]).M();
      dijetMassTwo = (leadAK4Jets[1] +leadAK4Jets[3]).M();
   }
   else if (  abs(std::min(minDeltaRDisc12, std::min(minDeltaRDisc13,minDeltaRDisc14)) -minDeltaRDisc14)<1e-8 )
   {
      //set dijet masses
      dijetMassOne = (leadAK4Jets[0] +leadAK4Jets[3]).M();
      dijetMassTwo = (leadAK4Jets[1] +leadAK4Jets[2]).M();
   } 
///////////////////////AK8 jets//////////////////

   edm::Handle<std::vector<pat::Jet> > fatJets;
   iEvent.getByToken(fatJetToken_, fatJets);
   int nfatjets = 0;
   int nfatjet_pre = 0;
   for(auto iJet = fatJets->begin(); iJet != fatJets->end(); iJet++)         ////////Over AK8 Jets
   {
      
      if((iJet->pt() > 500.) && ((iJet->isPFJet())) && (isgoodjet(iJet->eta(),iJet->neutralHadronEnergyFraction(), iJet->neutralEmEnergyFraction(),iJet->numberOfDaughters(),iJet->chargedHadronEnergyFraction(),iJet->chargedMultiplicity(),iJet->muonEnergyFraction(),iJet->chargedEmEnergyFraction())) && (iJet->userFloat("ak8PFJetsPuppiSoftDropMass") > 45.)) nfatjet_pre++;

      if((sqrt(pow(iJet->mass(),2)+pow(iJet->pt(),2)) < 300.) || (!(iJet->isPFJet())) || (!isgoodjet(iJet->eta(),iJet->neutralHadronEnergyFraction(), iJet->neutralEmEnergyFraction(),iJet->numberOfDaughters(),iJet->chargedHadronEnergyFraction(),iJet->chargedMultiplicity(),iJet->muonEnergyFraction(),iJet->chargedEmEnergyFraction(),nfatjets)) || (iJet->mass()< 0.)) continue; //userFloat("ak8PFJetsPuppiSoftDropMass")
      nfatjets++;
   }
	
   if ((totHT < 1500.)|| (nfatjets < 3))  return false;  //btagged jet cuts
   if ((nfatjet_pre < 2) && ( (dijetMassOne < 1000. ) || ( dijetMassTwo < 1000.)  ))
   {
      return false;
   } 

   //if(nBtaggedAK4 < 2)return false;
   return true;

   
}

// ------------ method called once each stream before processing any runs, lumis or events  ------------
void
superFilter::beginStream(edm::StreamID)
{
}

// ------------ method called once each stream after processing all runs, lumis and events  ------------
void
superFilter::endStream() {
}

// ------------ method called when starting to processes a run  ------------
/*
void
superFilter::beginRun(edm::Run const&, edm::EventSetup const&)
{ 
}
*/
 
// ------------ method called when ending the processing of a run  ------------
/*
void
superFilter::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when starting to processes a luminosity block  ------------
/*
void
superFilter::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when ending the processing of a luminosity block  ------------
/*
void
superFilter::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
superFilter::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}
//define this as a plug-in
DEFINE_FWK_MODULE(superFilter);

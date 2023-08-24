////////////////////////////HELP////////////////////////////////
//////////////Test EDAnalyzer to be filled in//////////////


// system include files
#include <fastjet/JetDefinition.hh>
#include <fastjet/GhostedAreaSpec.hh>
#include <fastjet/PseudoJet.hh>
#include <fastjet/tools/Filter.hh>
#include <fastjet/ClusterSequence.hh>
#include <fastjet/ClusterSequenceArea.hh>
#include <memory>
#include <iostream>
#include <fstream>
#include <vector>
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
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
#include "PhysicsTools/CandUtils/interface/Thrust.h"
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
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include <string>
using namespace reco;
typedef math::XYZTLorentzVector LorentzVector;
typedef math::XYZVector Vector;

class skeletonAnalyzer : public edm::EDAnalyzer 
{
public:
   explicit skeletonAnalyzer(const edm::ParameterSet&);
private:
   virtual void analyze(const edm::Event&, const edm::EventSetup&);



   //need to have one "token" for each collection (=classes of reconstructed particles/objects) you want to include
   edm::EDGetTokenT<std::vector<reco::GenParticle>> genPartToken_; 
   edm::EDGetTokenT<std::vector<pat::Jet>> fatJetToken_;
   edm::EDGetTokenT<std::vector<pat::Jet>> jetToken_;

   TTree * tree;

   //define all the =variables here that you will want to use or save later on
   int nAK4 = 0;
   int nAK8 = 0;
   double event_HT = 0;

   double AK8_pt[100], AK8_eta[100], AK8_mass[100];
   double AK4_pt[100], AK4_eta[100], AK4_mass[100];

   int nGenChi = 0;
   int nGenSuu = 0;

   int Suu_pdgid = 9936661;
   int chi_pdgid = 9936662;
};





skeletonAnalyzer::skeletonAnalyzer(const edm::ParameterSet& iConfig)
{
   genPartToken_ = consumes<std::vector<reco::GenParticle>>(iConfig.getParameter<edm::InputTag>("genPartCollection"));
   fatJetToken_ =    consumes<std::vector<pat::Jet>>(iConfig.getParameter<edm::InputTag>("fatJetCollection"));
   jetToken_    = consumes<std::vector<pat::Jet>>(iConfig.getParameter<edm::InputTag>("jetCollection"));

   edm::Service<TFileService> fs;      


   //make a tree and set all the branches that you'll want to save 
   //the way this works for arrays is that you have to tell the tree how many values you want to save per event (for example, AK8_pt saves nAK8 values each event, one for each AK8 jet)
   tree = fs->make<TTree>("tree", "tree");

   tree->Branch("nAK4", &nAK4, "nAK4/I");  //the "/I" in the last part here says that this is an integer. You can get a lot of weird problems if you have confilcting types
   tree->Branch("nAK8", &nAK8, "nAK8/I");
   tree->Branch("event_HT", &event_HT, "event_HT/D");

   tree->Branch("AK8_pt", AK8_pt, "AK8_pt[nAK8]/D");
   tree->Branch("AK8_eta", AK8_eta, "AK8_eta[nAK8]/D");
   tree->Branch("AK8_mass", AK8_mass, "AK8_mass[nAK8]/D");

   tree->Branch("AK4_pt", AK4_pt, "AK4_pt[nAK8]/D");
   tree->Branch("AK4_eta", AK4_eta, "AK4_eta[nAK8]/D");
   tree->Branch("AK4_mass", AK4_mass, "AK4_mass[nAK8]/D");

}



void skeletonAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   //this is where the actual analysis is done - you take the token that was defined earlier and use this to obtain the collections (basically vectors with your physics objects)
   // you can then loop over all the objects in these collections
   //collections of physics objects are generally sorted in decreasing order of pt

///////////////////////Gen Particles//////////////////////////////////

   //these are the two lines that take the collection token and return you your collection vector ( of gen particles here). This vector is 
   edm::Handle<std::vector<reco::GenParticle>> genParticles;
   iEvent.getByToken(genPartToken_, genParticles);

   nGenChi = 0; nGenSuu = 0;
   for (auto iG = genParticles->begin(); iG != genParticles->end(); iG++) 
   {
      if ((abs(iG->pdgId()) == chi_pdgid) && (iG->isLastCopy()))
      {
         std::cout << "Here is a Chi, px/py/pz/E is " << iG->px() << "/" << iG->py() << "/" << iG->pz() << "/" << iG->energy() << std::endl;
         nGenChi++;
      }
      else if ((abs(iG->pdgId()) == Suu_pdgid) && (iG->isLastCopy()))
      {
         std::cout << "Here is an Suu, px/py/pz/E is " << iG->px() << "/" << iG->py() << "/" << iG->pz() << "/" << iG->energy() << std::endl;
         nGenSuu++;
      }
   
   }
////// /////////////////////AK4 Jets////////////////////////////////
  
   edm::Handle<std::vector<pat::Jet> > smallJets;
   iEvent.getByToken(jetToken_, smallJets);
   nAK4 = 0;
   event_HT = 0;
   for(auto iJet = smallJets->begin(); iJet != smallJets->end(); iJet++) 
   {
      if( (iJet->pt() < 30.)|| (abs(iJet->eta()) >2.5)) continue;   //make a cut to AK4 jets, usually jets are only reliable out to |eta| < 2.5 because of detector acceptance
      event_HT+=iJet->pt();
      AK4_mass[nAK4] = iJet->mass();
      AK4_pt[nAK4]   = iJet->pt();
      AK4_eta[nAK4]  = iJet->eta();
      nAK4++;
   }
   
/////////////////////////////AK8 Jets///////////////////////////////

   edm::Handle<std::vector<pat::Jet> > fatJets;
   iEvent.getByToken(fatJetToken_, fatJets);

   nAK8 = 0;
   for(auto iJet = fatJets->begin(); iJet != fatJets->end(); iJet++)         ////////Over AK8 Jets
   {
      if( (iJet->pt() < 100.) || (abs(iJet->eta())> 2.5) ) continue;   //make a cut to AK4 jets
      AK8_mass[nAK8] = iJet->mass();
      AK8_pt[nAK8] = iJet->pt();
      AK8_eta[nAK8] = iJet->eta();
      nAK8++;
   }

   std::cout << "--------------End of event - the HT was " << event_HT << " and there was " << nGenSuu << " Suu and " << nGenChi << " chi's. --------------" << std::endl;


   //here you've reached the end of the event, so this will fill the branches of the tree that are specified.
   tree->Fill();

}   
DEFINE_FWK_MODULE(skeletonAnalyzer);

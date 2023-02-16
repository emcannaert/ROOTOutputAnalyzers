////////////////////////////HELP////////////////////////////////
//////////////Uses new clustering algorithm to capture heavy resonance jet substructure//////////////
////////////////Last updated Feb 23 2021 ////////////////////////////////////////////////////////////


// system include files
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
#include "PhysicsTools/CandUtils/interface/Thrust.h"
//#include "Thrust.h"
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
#include "DataFormats/PatCandidates/interface/MET.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
#include <DataFormats/Math/interface/deltaR.h>
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include <string>
#include "/uscms_data/d3/cannaert/analysis/CMSSW_10_6_20/src/sortJets.h"
using namespace reco;
typedef math::XYZTLorentzVector LorentzVector;
typedef math::XYZVector Vector;

class clusteringAnalyzer : public edm::EDAnalyzer 
{
public:
   explicit clusteringAnalyzer(const edm::ParameterSet&);
private:
   virtual void analyze(const edm::Event&, const edm::EventSetup&);
   double calc_mass(std::vector<TLorentzVector> candSuperJet);
   double calc_mag(double px,double py, double pz);
   double calcMPP(TLorentzVector superJetTLV ); 
   bool isMatchedtoSJ(std::vector<TLorentzVector> superJetTLVs, TLorentzVector candJet); 

   bool isgoodjet(const float eta, const float NHF,const float NEMF, const size_t NumConst,const float CHF,const int CHM, const float MUF, const float CEMF);
   bool isgoodjet(const float eta, const float NHF,const float NEMF, const size_t NumConst,const float CHF,const int CHM, const float MUF, const float CEMF, int nfatjets);
   const reco::Candidate* parse_chain(const reco::Candidate* cand);
   edm::EDGetTokenT<std::vector<reco::GenParticle>> genPartToken_; 
   edm::EDGetTokenT<std::vector<pat::Jet>> fatJetToken_;
   edm::EDGetTokenT<std::vector<pat::Jet>> jetToken_;
   edm::EDGetTokenT<std::vector<pat::MET>> metToken_;

   edm::EDGetTokenT<edm::TriggerResults> triggerBits_;

   TTree * tree;

   int eventnum = 0;
   int nAK4 = 0;
   int nfatjets = 0;
   int raw_nfatjets;
   int tot_nAK4_50,tot_nAK4_70;
   int tot_mpp_AK4 = 0;
   int nbtaggedAK4 = 0;
   int SJ_nAK4_50[100],SJ_nAK4_70[100],SJ_nAK4_100[100],SJ_nAK4_125[100],SJ_nAK4_150[100],SJ_nAK4_200[100],SJ_nAK4_300[100],SJ_nAK4_400[100],SJ_nAK4_600[100],SJ_nAK4_800[100],SJ_nAK4_1000[100];
   double jet_pt[100], jet_eta[100], jet_mass[100], jet_dr[100], raw_jet_mass[100],raw_jet_pt[100],raw_jet_phi[100], jet_thrust_cos[100];
   double SJ_mass_50[100], SJ_mass_70[100],SJ_mass_100[100],superJet_mass[100],SJ_AK4_50_mass[100],SJ_AK4_70_mass[100];
   double SJ_mass_125[100], SJ_mass_150[100], SJ_mass_200[100],SJ_mass_300[100],SJ_mass_400[100],SJ_mass_600[100],SJ_mass_800[100],SJ_mass_1000[100];
   double tot_jet_mass,decay_inv_mass, chi_inv_mass;
   double AK4_mass[100], AK4_E[500], leadAK8_mass[100], genChi_thrust_cos[100], genSuperJetMass[100], genChiCosRecoFrame[100];
   double genHiggsThrustCos[100], genTopWThrustCos[100],genSuuWThrustCos[100];
   double genTopbThrustCos, genSuubThrustCos, event_reco_pt;
   double chi_dr,topPart_dr,higgs_dr,SuuW_dr,HiggsTop_dr,SuuWb_dr;
   double topAK8_dr, WSuuAK8_dr,bSuuAK8_dr,higgsAK8_dr,topWAK8_dr,topbAK8_dr;
   double topAK4_dr, WSuuAK4_dr,bSuuAK4_dr,higgsAK4_dr,topWAK4_dr,topbAK4_dr;
   double genPartChiDaughterMPP_angle[2];
   double genPartBetaCOM = -999.;
   double eventBetaCOM   = -999.;
   double genCOM_eta, genCOM_phi, recoCOM_eta,recoCOM_phi;
   double diSuperJet_mass,diSuperJet_mass_100;
   double btagged_AK4_pt[100];
   double totHT = 0;
   int nfatjet_pre = 0;
   int nGenChi = 2;
   int nonHadFlag = 0;
   double totMET;
   int nhadevents = 0;
   bool _htWb;
   bool _htZt;
   bool _ZtWb;
   bool _WbWb;
   bool _htht;
   bool _ZtZt;
   int nSuperJets;
   int correctlySortedChi1, correctlySortedChi2;
   int jet_ndaughters[100], jet_nAK4[100];

   double SJ_E[2],SJ_Px[2],SJ_Py[2],SJ_Pz[2];


   double posSJP =0;
   double negSJP = 0;
   double daughter_mass_comb[100];
   double resonance_mass_comb;
   int nZtZt = 0, nhtht = 0, nWbWb = 0, nZtWb = 0, nZtht = 0, nhtWb = 0;
};

clusteringAnalyzer::clusteringAnalyzer(const edm::ParameterSet& iConfig)
{
   genPartToken_ = consumes<std::vector<reco::GenParticle>>(iConfig.getParameter<edm::InputTag>("genPartCollection"));
   fatJetToken_ =    consumes<std::vector<pat::Jet>>(iConfig.getParameter<edm::InputTag>("fatJetCollection"));
   triggerBits_ = consumes<edm::TriggerResults>(iConfig.getParameter<edm::InputTag>("bits"));
   jetToken_    = consumes<std::vector<pat::Jet>>(iConfig.getParameter<edm::InputTag>("jetCollection"));
   metToken_    = consumes<std::vector<pat::MET>>(iConfig.getParameter<edm::InputTag>("metCollection"));
   edm::Service<TFileService> fs;      

   tree = fs->make<TTree>("tree", "tree");

   tree->Branch("nfatjets", &nfatjets, "nfatjets/I");
   tree->Branch("nAK4", &nAK4, "nAK4/I");
   tree->Branch("tot_mpp_AK4", &tot_mpp_AK4, "tot_mpp_AK4/I");
   tree->Branch("nGenChi", &nGenChi, "nGenChi/I");
   tree->Branch("nSuperJets", &nSuperJets, "nSuperJets/I");
   tree->Branch("tot_nAK4_50", &tot_nAK4_50, "tot_nAK4_50/I");             //total #AK4 jets (E>50 GeV) for BOTH superjets
   tree->Branch("tot_nAK4_70", &tot_nAK4_70, "tot_nAK4_70/I");
   tree->Branch("genPartBetaCOM",&genPartBetaCOM, "genPartBetaCOM/D");
   tree->Branch("eventBetaCOM",&eventBetaCOM, "eventBetaCOM/D");
   tree->Branch("diSuperJet_mass",&diSuperJet_mass, "diSuperJet_mass/D");
   tree->Branch("diSuperJet_mass_100",&diSuperJet_mass_100, "diSuperJet_mass_100/D");
   tree->Branch("nfatjet_pre",&nfatjet_pre, "nfatjet_pre/I");


   tree->Branch("nbtaggedAK4", &nbtaggedAK4, "nbtaggedAK4/I");
   tree->Branch("btagged_AK4_pt", btagged_AK4_pt, "btagged_AK4_pt[nbtaggedAK4]/D");

   tree->Branch("totHT", &totHT, "totHT/D");
   tree->Branch("nonHadFlag", &nonHadFlag, "nonHadFlag/I");

   tree->Branch("_htWb", &_htWb, "_htWb/O");
   tree->Branch("_htZt", &_htZt, "_htZt/O");
   tree->Branch("_ZtWb", &_ZtWb, "_ZtWb/O");
   tree->Branch("_WbWb", &_WbWb, "_WbWb/O");
   tree->Branch("_htht", &_htht, "_htht/O");
   tree->Branch("_ZtZt", &_ZtZt, "_ZtZt/O");


   tree->Branch("topAK8_dr", &topAK8_dr, "topAK8_dr/D");
   tree->Branch("WSuuAK8_dr", &WSuuAK8_dr, "WSuuAK8_dr/D");
   tree->Branch("bSuuAK8_dr", &bSuuAK8_dr, "bSuuAK8_dr/D");
   tree->Branch("higgsAK8_dr", &higgsAK8_dr, "higgsAK8_dr/D");
   tree->Branch("topWAK8_dr", &topWAK8_dr, "topWAK8_dr/D");
   tree->Branch("topbAK8_dr", &topbAK8_dr, "topbAK8_dr/D");

   tree->Branch("topAK4_dr", &topAK4_dr, "topAK4_dr/D");
   tree->Branch("WSuuAK4_dr", &WSuuAK4_dr, "WSuuAK4_dr/D");
   tree->Branch("bSuuAK4_dr", &bSuuAK4_dr, "bSuuAK4_dr/D");
   tree->Branch("higgsAK4_dr", &higgsAK4_dr, "higgsAK4_dr/D");
   tree->Branch("topWAK4_dr", &topWAK4_dr, "topWAK4_dr/D");
   tree->Branch("topbAK4_dr", &topbAK4_dr, "topbAK4_dr/D");

   tree->Branch("jet_pt", jet_pt, "jet_pt[nfatjets]/D");
   tree->Branch("jet_eta", jet_eta, "jet_eta[nfatjets]/D");
   tree->Branch("jet_mass", jet_mass, "jet_mass[nfatjets]/D");
   tree->Branch("AK4_mass", AK4_mass, "AK4_mass[nAK4]/D");

   tree->Branch("SJ_nAK4_50", SJ_nAK4_50, "SJ_nAK4_50[nSuperJets]/I");
   tree->Branch("SJ_nAK4_70", SJ_nAK4_70, "SJ_nAK4_70[nSuperJets]/I");
   tree->Branch("SJ_nAK4_100", SJ_nAK4_100, "SJ_nAK4_100[nSuperJets]/I");
   tree->Branch("SJ_nAK4_125", SJ_nAK4_125, "SJ_nAK4_125[nSuperJets]/I");
   tree->Branch("SJ_nAK4_150", SJ_nAK4_150, "SJ_nAK4_150[nSuperJets]/I");
   tree->Branch("SJ_nAK4_200", SJ_nAK4_200, "SJ_nAK4_200[nSuperJets]/I");
   tree->Branch("SJ_nAK4_300", SJ_nAK4_300, "SJ_nAK4_300[nSuperJets]/I");
   tree->Branch("SJ_nAK4_400", SJ_nAK4_400, "SJ_nAK4_400[nSuperJets]/I");
   tree->Branch("SJ_nAK4_600", SJ_nAK4_600, "SJ_nAK4_600[nSuperJets]/I");
   tree->Branch("SJ_nAK4_800", SJ_nAK4_800, "SJ_nAK4_800[nSuperJets]/I");
   tree->Branch("SJ_nAK4_1000", SJ_nAK4_1000, "SJ_nAK4_1000[nSuperJets]/I");

   tree->Branch("SJ_mass_50", SJ_mass_50, "SJ_mass_50[nSuperJets]/D");
   tree->Branch("SJ_mass_70", SJ_mass_70, "SJ_mass_70[nSuperJets]/D");
   tree->Branch("SJ_mass_100", SJ_mass_100, "SJ_mass_100[nSuperJets]/D");
   tree->Branch("SJ_mass_125", SJ_mass_125, "SJ_mass_125[nSuperJets]/D");
   tree->Branch("SJ_mass_150", SJ_mass_150, "SJ_mass_150[nSuperJets]/D");
   tree->Branch("SJ_mass_200", SJ_mass_200, "SJ_mass_200[nSuperJets]/D");
   tree->Branch("SJ_mass_300", SJ_mass_300, "SJ_mass_300[nSuperJets]/D");
   tree->Branch("SJ_mass_400", SJ_mass_400, "SJ_mass_400[nSuperJets]/D");
   tree->Branch("SJ_mass_600", SJ_mass_600, "SJ_mass_600[nSuperJets]/D");
   tree->Branch("SJ_mass_800", SJ_mass_800, "SJ_mass_800[nSuperJets]/D");
   tree->Branch("SJ_mass_1000", SJ_mass_1000, "SJ_mass_1000[nSuperJets]/D");

   tree->Branch("superJet_mass", superJet_mass, "superJet_mass[nSuperJets]/D");
   tree->Branch("SJ_AK4_50_mass", SJ_AK4_50_mass, "SJ_AK4_50_mass[tot_nAK4_50]/D");    //mass of individual reclustered AK4 jets
   tree->Branch("SJ_AK4_70_mass", SJ_AK4_70_mass, "SJ_AK4_70_mass[tot_nAK4_70]/D");
   tree->Branch("AK4_E", AK4_E, "AK4_E[tot_mpp_AK4]/D");

   tree->Branch("chi_dr", &chi_dr, "chi_dr/D");
   tree->Branch("topPart_dr", &topPart_dr, "topPart_dr/D");
   tree->Branch("higgs_dr", &higgs_dr, "higgs_dr/D");
   tree->Branch("SuuW_dr", &SuuW_dr, "SuuW_dr/D");
   tree->Branch("HiggsTop_dr", &HiggsTop_dr, "HiggsTop_dr/D");
   tree->Branch("SuuWb_dr", &SuuWb_dr, "SuuWb_dr/D");
   tree->Branch("leadAK8_mass",leadAK8_mass, "leadAK8_mass[nfatjets]/D");
   tree->Branch("genPartChiDaughterMPP_angle",genPartChiDaughterMPP_angle, "genPartChiDaughterMPP_angle[nGenChi]/D");
   tree->Branch("genChi_thrust_cos",genChi_thrust_cos, "genChi_thrust_cos[nGenChi]/D");
   tree->Branch("totMET",&totMET, "totMET/D");

   tree->Branch("genCOM_eta", &genCOM_eta, "genCOM_eta/D");
   tree->Branch("genCOM_phi", &genCOM_phi, "genCOM_phi/D");
   tree->Branch("recoCOM_eta", &recoCOM_eta, "recoCOM_eta/D");
   tree->Branch("recoCOM_phi", &recoCOM_phi, "recoCOM_phi/D");

   tree->Branch("genSuperJetMass",genSuperJetMass, "genSuperJetMass[nGenChi]/D");
   tree->Branch("genChiCosRecoFrame",genChiCosRecoFrame, "genChiCosRecoFrame[nGenChi]/D");   ///nGenChi is just a placeholder for 2!!! 
   tree->Branch("genHiggsThrustCos",genHiggsThrustCos, "genHiggsThrustCos[nGenChi]/D");
   tree->Branch("genTopWThrustCos",genTopWThrustCos, "genTopWThrustCos[nGenChi]/D");
   tree->Branch("genSuuWThrustCos",genSuuWThrustCos, "genSuuWThrustCos[nGenChi]/D");
   tree->Branch("genTopbThrustCos", &genTopbThrustCos, "genTopbThrustCos/D");
   tree->Branch("genSuubThrustCos", &genSuubThrustCos, "genSuubThrustCos/D");
   tree->Branch("event_reco_pt", &event_reco_pt, "event_reco_pt/D");

   tree->Branch("correctlySortedChi1", &correctlySortedChi1, "correctlySortedChi1/I");
   tree->Branch("correctlySortedChi2", &correctlySortedChi2, "correctlySortedChi2/I");
   tree->Branch("jet_thrust_cos", jet_thrust_cos, "jet_thrust_cos[nfatjets]/D");

   tree->Branch("daughter_mass_comb", daughter_mass_comb, "daughter_mass_comb[nSuperJets]/D");
   tree->Branch("resonance_mass_comb", &resonance_mass_comb, "resonance_mass_comb/D");
   tree->Branch("posSJP",&posSJP   );
   tree->Branch("negSJP", &negSJP   );

}


double clusteringAnalyzer::calc_mag(double px,double py, double pz)
{
   return sqrt(pow(px,2)+pow(py,2)+pow(pz,2));
}
const reco::Candidate* clusteringAnalyzer::parse_chain(const reco::Candidate* cand)
{  
   for (unsigned int iii=0; iii<cand->numberOfDaughters(); iii++)
   {
      if(cand->daughter(iii)->pdgId() == cand->pdgId()) return parse_chain(cand->daughter(iii));
   }
   return cand;
}
bool clusteringAnalyzer::isgoodjet(const float eta, const float NHF,const float NEMF, const size_t NumConst,const float CHF,const int CHM, const float MUF, const float CEMF)
{
   if( (abs(eta) > 2.5)) return false;

   if ((NHF>0.9) || (NEMF>0.9) || (NumConst<1) || (CHF<0.) || (CHM<0) || (MUF > 0.8) || (CEMF > 0.8)) 
      {
         return false;
      }
   else{ return true;}

}
bool clusteringAnalyzer::isgoodjet(const float eta, const float NHF,const float NEMF, const size_t NumConst,const float CHF,const int CHM, const float MUF, const float CEMF, int nfatjets)
{
   if ( (nfatjets < 2) &&  (abs(eta) > 2.4) ) return false;
   else if ( (nfatjets >= 2) && (abs(eta) > 1.5) ) return false;

   if ((NHF>0.9) || (NEMF>0.9) || (NumConst<1) || (CHF<0.) || (CHM<0) || (MUF > 0.8) || (CEMF > 0.8)) 
      {
         return false;
      }
   else{ return true;}

}

double clusteringAnalyzer::calcMPP(TLorentzVector superJetTLV ) 
{
   Vector jet_axis(superJetTLV.Px()/superJetTLV.P(),superJetTLV.Py()/superJetTLV.P(),superJetTLV.Pz()/superJetTLV.P());
   double min_pp = 99999999999999.;
   double min_boost = 0.;

   for(int iii=0;iii<10000;iii++)
   {
      TLorentzVector superJetTLV_ = superJetTLV;
      double beta_cand = iii/10000.;
      superJetTLV_.Boost(-beta_cand*jet_axis.X(),-beta_cand*jet_axis.Y(),-beta_cand*jet_axis.Z());
      if(abs( ( superJetTLV_.Px()*superJetTLV.Px()+superJetTLV_.Py()*superJetTLV.Py() +superJetTLV_.Pz()*superJetTLV.Pz() )/superJetTLV.P() ) < min_pp) 
         {
            min_boost = beta_cand; 
            min_pp = abs( ( superJetTLV_.Px()*superJetTLV.Px()+superJetTLV_.Py()*superJetTLV.Py() +superJetTLV_.Pz()*superJetTLV.Pz() )/superJetTLV.P() ) ;
         }
      }
      return min_boost;
}
double clusteringAnalyzer::calc_mass(std::vector<TLorentzVector> candSuperJet)
{
   double px_tot = 0., py_tot = 0., pz_tot= 0.,E_tot = 0.;
   for(auto _iJet = candSuperJet.begin(); _iJet!=candSuperJet.end();_iJet++)
   {
      px_tot+=_iJet->Px();py_tot+=_iJet->Py();pz_tot+=_iJet->Pz();E_tot+=_iJet->E();
   }
   return sqrt(pow(E_tot,2) - pow(px_tot,2) - pow(py_tot,2) - pow(pz_tot,2));
}
bool clusteringAnalyzer::isMatchedtoSJ(std::vector<TLorentzVector> superJetTLVs, TLorentzVector candJet)
{
   for(auto iJet = superJetTLVs.begin(); iJet!=superJetTLVs.end(); iJet++)
   {
      if( abs(candJet.Angle(iJet->Vect())) < 0.001) return true;
   }
   return false;
}
void clusteringAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

   eventnum++;

   /////////////////////AK4 Jets////////////////////////////////
  
  edm::Handle<std::vector<pat::Jet> > smallJets;
   iEvent.getByToken(jetToken_, smallJets);
   nAK4 = 0;

   nbtaggedAK4 = 0;
   totHT = 0;
   for(auto iJet = smallJets->begin(); iJet != smallJets->end(); iJet++) 
   {
      if((iJet->pt() > 30.)&&(abs(iJet->eta()) < 2.5)  )totHT+= abs(iJet->pt() );

      if( (iJet->pt()  <30.) || (!(iJet->isPFJet())) || (!isgoodjet(iJet->eta(),iJet->neutralHadronEnergyFraction(), iJet->neutralEmEnergyFraction(),iJet->numberOfDaughters(),iJet->chargedHadronEnergyFraction(),iJet->chargedMultiplicity(),iJet->muonEnergyFraction(),iJet->chargedEmEnergyFraction())) ) continue;
      if( ((iJet->bDiscriminator("pfDeepCSVJetTags:probb") + iJet->bDiscriminator("pfDeepCSVJetTags:probbb") )< 0.4184)||(iJet->pt() < 30.) )continue;
      //loose
      btagged_AK4_pt[nbtaggedAK4] = iJet->pt();


      nbtaggedAK4++;
      //loose is 0.1241 
   }

 
   ///////////////////////////////////////////////////////////////
   ////////////////////////////MET////////////////////////////////
   ///////////////////////////////////////////////////////////////

   edm::Handle<std::vector<pat::MET> > _totMET;
   iEvent.getByToken(metToken_, _totMET);
   for(auto iMET = _totMET->begin(); iMET != _totMET->end(); iMET++)
   {
      if(iMET->isPFMET())
      {
         totMET = iMET->pt();
      }
   }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////AK8 Jets//////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   std::vector<reco::LeafCandidate> candsBoosted;   
   std::vector<reco::LeafCandidate> candsUnboosted;
   std::vector<fastjet::PseudoJet> superJetOne;        //jets for dot prduct #cos(theta) > 0
   std::vector<fastjet::PseudoJet> superJetTwo;       //jets for dot product #cos(theta) < 0
   std::vector<TLorentzVector> superJetOneLV;        //workaround for weird fastjet bug
   std::vector<TLorentzVector> superJetTwoLV;        //workaround for weird fastjet bug

   edm::Handle<std::vector<pat::Jet> > fatJets;
   iEvent.getByToken(fatJetToken_, fatJets);





   /////////////////////////this is for doing the alternative analysis/////////////////////////


   std::vector<TLorentzVector> negSuperJet_;
   std::vector<TLorentzVector> posSuperJet_;
   std::vector<TLorentzVector> miscJets_;
   for(auto iJet = fatJets->begin(); iJet != fatJets->end(); iJet++)         ////////Over AK8 Jets
   {

      if((sqrt(pow(iJet->mass(),2)+pow(iJet->pt(),2)) < 150.) || (!(iJet->isPFJet())) || (!isgoodjet(iJet->eta(),iJet->neutralHadronEnergyFraction(), iJet->neutralEmEnergyFraction(),iJet->numberOfDaughters(),iJet->chargedHadronEnergyFraction(),iJet->chargedMultiplicity(),iJet->muonEnergyFraction(),iJet->chargedEmEnergyFraction(),nfatjets)) || (iJet->userFloat("ak8PFJetsPuppiSoftDropMass")< 2.)) continue;
      miscJets_.push_back(TLorentzVector(iJet->px(),iJet->py(),iJet->pz(),iJet->energy()));

   }
   if( (miscJets_.size() < 8)&& (miscJets_.size()>0))
   {
      sortJets testing(negSuperJet_,posSuperJet_,miscJets_);
      negSuperJet_ = testing.finalSuperJet1;
      posSuperJet_ = testing.finalSuperJet2;
   }
   TLorentzVector tot_posSuperJet(0,0,0,0);
   TLorentzVector tot_negSuperJet(0,0,0,0);

   for(auto iP = posSuperJet_.begin();iP<posSuperJet_.end();iP++)
   {
      tot_posSuperJet+=*iP;
   }
   for(auto iP = negSuperJet_.begin();iP<negSuperJet_.end();iP++)
   {
      tot_negSuperJet+=*iP;
   }
   daughter_mass_comb[0] = tot_posSuperJet.M();
   daughter_mass_comb[1] = tot_negSuperJet.M();
   TLorentzVector tot_res_LV = tot_posSuperJet + tot_negSuperJet;
   resonance_mass_comb = tot_res_LV.M();
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////Get AK8 jet info in order to get to COM frame and get a vector of all the (good) AK8 jet particles/////////////////////////////////////////////////////////////
   nfatjets = 0;
   nfatjet_pre = 0;
   double tot_jet_px=0,tot_jet_py=0,tot_jet_pz=0, tot_jet_E=0;
   for(auto iJet = fatJets->begin(); iJet != fatJets->end(); iJet++)         ////////Over AK8 Jets
   {

      if((iJet->pt() < 500.) || (!(iJet->isPFJet())) || (!isgoodjet(iJet->eta(),iJet->neutralHadronEnergyFraction(), iJet->neutralEmEnergyFraction(),iJet->numberOfDaughters(),iJet->chargedHadronEnergyFraction(),iJet->chargedMultiplicity(),iJet->muonEnergyFraction(),iJet->chargedEmEnergyFraction())) || (iJet->userFloat("ak8PFJetsPuppiSoftDropMass")< 50.)) nfatjet_pre++;

      if((sqrt(pow(iJet->mass(),2)+pow(iJet->pt(),2)) < 150.) || (!(iJet->isPFJet())) || (!isgoodjet(iJet->eta(),iJet->neutralHadronEnergyFraction(), iJet->neutralEmEnergyFraction(),iJet->numberOfDaughters(),iJet->chargedHadronEnergyFraction(),iJet->chargedMultiplicity(),iJet->muonEnergyFraction(),iJet->chargedEmEnergyFraction(),nfatjets)) || (iJet->userFloat("ak8PFJetsPuppiSoftDropMass")< 2.)) continue;
      if(nfatjets < 2) leadAK8_mass[nfatjets] = iJet->userFloat("ak8PFJetsPuppiSoftDropMass");
      jet_pt[nfatjets] = iJet->pt();
      jet_eta[nfatjets] = iJet->eta();
      jet_mass[nfatjets] = iJet->mass();
      for (unsigned int iii=0; iii<iJet->numberOfDaughters();iii++)   ///////get all jet particles
      {
         const reco::Candidate* iJ = iJet->daughter(iii);
         const pat::PackedCandidate* candJetbegin = (pat::PackedCandidate*) iJ;
         double puppiweight = candJetbegin->puppiWeight();
         candsUnboosted.push_back(LeafCandidate(iJet->daughter(iii)->charge(), Particle::LorentzVector(puppiweight*iJ->px(), puppiweight*iJ->py(), puppiweight*iJ->pz(), puppiweight*iJ->energy())));
         tot_jet_px+=puppiweight*candJetbegin->px();tot_jet_py+=puppiweight*candJetbegin->py();tot_jet_pz+=puppiweight*candJetbegin->pz();tot_jet_E+=puppiweight*candJetbegin->energy();
      }
      nfatjets++;
   }
   event_reco_pt = sqrt(pow(tot_jet_px,2) + pow(tot_jet_py,2));


   double tot_jet_p = sqrt(pow(tot_jet_px,2)+pow(tot_jet_py,2)+pow(tot_jet_pz,2)   ); 
   /////calculate MPP frame boost////////////////////////////////////////////////////////////////////?????///////////////
   

   TVector3 totJetBeta = calcMPP(TLorentzVector(tot_jet_px,tot_jet_py,tot_jet_pz,tot_jet_E))*TVector3(tot_jet_px/tot_jet_p,tot_jet_py/tot_jet_p ,tot_jet_pz/tot_jet_p);

   


   //////////boost all jet particles into MPP frame//////////////////////////////////////////////////////////////////////
   std::vector<fastjet::PseudoJet> candsBoostedPJ;
   double pxCOM = 0,pyCOM=0,pzCOM=0;
   for(auto iC = candsUnboosted.begin();iC != candsUnboosted.end(); iC++)
   {
      TLorentzVector iC_(iC->px(),iC->py(),iC->pz(),iC->energy());
      iC_.Boost(-totJetBeta.X(),-totJetBeta.Y(),-totJetBeta.Z());
      pxCOM+=iC_.Px();pyCOM+=iC_.Py();pzCOM+=iC_.Pz();
      candsBoostedPJ.push_back(  fastjet::PseudoJet(iC_.Px(), iC_.Py(), iC_.Pz(), iC_.E()   ) );

   }

   ///////take all boosted particles in MPP frame and recluster, then sort these AK8 jets


    double R0 = 0.8;
    //fastjet::JetDefinition jet_def0(fastjet::antikt_algorithm, R0);
    fastjet::JetDefinition jet_def0(fastjet::cambridge_algorithm, R0);
    fastjet::ClusterSequence cs_jet0(candsBoostedPJ, jet_def0); 
    std::vector<TLorentzVector> candsBoostedTLV;   


   // shedding particles here -> can change this energy threshold, just changed it from 50. 
   std::vector<fastjet::PseudoJet> jetsFJ_jet0 = fastjet::sorted_by_E(cs_jet0.inclusive_jets(0.));
   double MPP_COM2_px = 0,MPP_COM2_py=0,MPP_COM2_pz =0,MPP_COM2_E = 0;

   for (auto iJet=jetsFJ_jet0.begin(); iJet<jetsFJ_jet0.end(); iJet++)                             
   {   
      if (iJet->constituents().size() > 0)
      {
         for(auto iDaughter = iJet->constituents().begin(); iDaughter != iJet->constituents().end(); iDaughter++)
         {
            candsBoosted.push_back(reco::LeafCandidate(+1, reco::Candidate::LorentzVector(iDaughter->px(), iDaughter->py(), iDaughter->pz(), iDaughter->E())));
            candsBoostedTLV.push_back(TLorentzVector( iDaughter->px(), iDaughter->py(), iDaughter->pz(), iDaughter->E()    ));
         }
      }
      MPP_COM2_px+= iJet->px(); MPP_COM2_py+= iJet->py(); MPP_COM2_pz+=iJet->pz() ; MPP_COM2_E+=iJet->E() ;
   }


    TVector3 MPP_COM2 = TVector3(MPP_COM2_px/MPP_COM2_E,MPP_COM2_py/MPP_COM2_E ,MPP_COM2_pz/MPP_COM2_E);
    std::vector<reco::LeafCandidate> candsBoosted_MPPCOM2;   
    for(auto iPart = candsBoostedTLV.begin(); iPart != candsBoostedTLV.end(); iPart++)
    {
        iPart->Boost(-MPP_COM2.X(), -MPP_COM2.Y(), -MPP_COM2.Z());
        candsBoosted_MPPCOM2.push_back( reco::LeafCandidate(+1, reco::Candidate::LorentzVector( iPart->Px(),iPart->Py(),iPart->Pz(),iPart->E()   ) )       );
    }


    Thrust thrust_(candsBoosted.begin(), candsBoosted.end());                             //thrust axis in COM frame
    math::XYZVector thrustAxis = thrust_.axis();
    TVector3 thrust_vector(thrustAxis.X(),thrustAxis.Y(),thrustAxis.Z());

///////////////////////////get vector of sorted superjets//////////////////////////////////////////////////////   
    std::vector<TLorentzVector> negSuperJet;
    std::vector<TLorentzVector> posSuperJet;
    std::vector<TLorentzVector> miscJets;
    for (auto iJet=jetsFJ_jet0.begin(); iJet<jetsFJ_jet0.end(); iJet++)                             
    {
        TLorentzVector candJet(iJet->px(),iJet->py(),iJet->pz(),iJet->E());
        TVector3 candJet_vec = candJet.Vect();
        double cosAngle = cos(candJet_vec.Angle(thrust_vector));
        if    (cosAngle < -0.80) negSuperJet.push_back(candJet);  
        else if(cosAngle > 0.80) posSuperJet.push_back(candJet);
        else{ miscJets.push_back(candJet); }
    }

   TLorentzVector SJ1(0,0,0,0);
   TLorentzVector SJ2(0,0,0,0);

   if(miscJets.size() > 0)
   {   
      sortJets testing(negSuperJet,posSuperJet,miscJets);
      negSuperJet = testing.finalSuperJet1;
      posSuperJet = testing.finalSuperJet2;

   }
   for(unsigned int iii = 0; iii < negSuperJet.size();iii++)
   {
      SJ2+=negSuperJet[iii];
   }

   for(unsigned int iii = 0; iii < posSuperJet.size();iii++)
   {
      SJ1+=posSuperJet[iii];
   }
   posSJP =SJ1.P();
   negSJP = SJ2.P();


    if( (negSuperJet.size() < 1 ) || (posSuperJet.size()<1)   ) return;
    //get vector of pseudo jet particles for all particles in each superjet, one per superjet
    for (auto iJet=jetsFJ_jet0.begin(); iJet<jetsFJ_jet0.end(); iJet++)                             
    {   
        TLorentzVector candJet(iJet->px(),iJet->py(),iJet->pz(),iJet->E());

        int SJMatch = 0;
        if      (isMatchedtoSJ(posSuperJet,candJet)) SJMatch = 1;
        else if (isMatchedtoSJ(negSuperJet,candJet)) SJMatch = 2;
        else if(SJMatch == 0) std::cout << "Something didn't work... " << std::endl;

        //sort jet particles into either SuperJet 1 or SuperJet 2
        if (iJet->constituents().size() > 0)
        {
            for(auto iJ = iJet->constituents().begin(); iJ != iJet->constituents().end(); iJ++)
            {  
                if     (SJMatch==1)superJetOneLV.push_back(TLorentzVector(iJ->px(),iJ->py(),iJ->pz(),iJ->E()));
                else if(SJMatch==2)superJetTwoLV.push_back(TLorentzVector(iJ->px(),iJ->py(),iJ->pz(),iJ->E()));
            }
         }        
   }

   for(auto iPart = superJetOneLV.begin(); iPart != superJetOneLV.end(); iPart++)
   {
         superJetOne.push_back(fastjet::PseudoJet(iPart->Px(),iPart->Py(),iPart->Pz(),iPart->E()));
   }
   for(auto iPart = superJetTwoLV.begin(); iPart != superJetTwoLV.end(); iPart++)
   {
        superJetTwo.push_back(fastjet::PseudoJet(iPart->Px(),iPart->Py(),iPart->Pz(),iPart->E()));
   }






   double superJetpx,superJetpy,superJetpz,superJetE;
   std::vector<std::vector<fastjet::PseudoJet>> superJets;
   superJets.push_back(superJetOne);
   superJets.push_back(superJetTwo);

   nSuperJets = 0;
   tot_nAK4_70 = 0; 
   tot_nAK4_50 = 0;
   tot_mpp_AK4 = 0;

   double diSuperJet_E = 0, diSuperJet_px = 0,diSuperJet_py = 0,diSuperJet_pz =0;
   double diSuperJet_E_100 = 0, diSuperJet_px_100 = 0,diSuperJet_py_100 = 0,diSuperJet_pz_100 =0;

   for(auto iSJ = superJets.begin();iSJ!= superJets.end();iSJ++)
   {
      superJetpx=0;superJetpy=0;superJetpz=0;superJetE=0;
      for(auto iP = iSJ->begin();iP != iSJ->end();iP++)
      {
         superJetpx+=iP->px();superJetpy+=iP->py();superJetpz+=iP->pz();superJetE +=iP->E();
         diSuperJet_E +=iP->E();diSuperJet_px+=iP->px();diSuperJet_py+=iP->py();diSuperJet_pz+=iP->pz();

      }
      superJet_mass[nSuperJets] = sqrt(pow(superJetE,2)-pow(superJetpx,2)-pow(superJetpy,2)-pow(superJetpz,2));

      SJ_E[nSuperJets] =superJetE;
      SJ_Px[nSuperJets]=superJetpx;
      SJ_Py[nSuperJets]=superJetpy;
      SJ_Pz[nSuperJets]=superJetpz;



      TLorentzVector superJetTLV(superJetpx,superJetpy,superJetpz,superJetE);    //Lorentz vector representing jet axis -> now minimize the parallel momentum
      //try boost to COM, NOT MPP frame 
      double betaMag = sqrt(pow(superJetpx,2)+pow(superJetpy,2)+pow(superJetpz,2))/superJetE;
      std::vector<fastjet::PseudoJet> boostedSuperJetPart;

      //boost particles in SuperJet to MPP frame
      for(auto iP = iSJ->begin();iP != iSJ->end();iP++)
      {
         TLorentzVector iP_(iP->px(),iP->py(),iP->pz(),iP->E());
         iP_.Boost(-betaMag*superJetTLV.Px()/superJetTLV.P(),-betaMag*superJetTLV.Py()/superJetTLV.P(),-betaMag*superJetTLV.Pz()/superJetTLV.P());
         boostedSuperJetPart.push_back(fastjet::PseudoJet(iP_.Px(),iP_.Py(),iP_.Pz(),iP_.E()));
      }
      ///reclustering SuperJet that is now boosted into the MPP frame
      double R = 0.4;
      //fastjet::JetDefinition jet_def(fastjet::antikt_algorithm, R);
      fastjet::JetDefinition jet_def(fastjet::cambridge_algorithm, R);
      fastjet::ClusterSequence cs_jet(boostedSuperJetPart, jet_def); 
      std::vector<fastjet::PseudoJet> jetsFJ_jet = fastjet::sorted_by_E(cs_jet.inclusive_jets(0.0));

      double SJ_50_px = 0, SJ_50_py=0,SJ_50_pz=0,SJ_50_E=0;
      double SJ_70_px = 0, SJ_70_py=0,SJ_70_pz=0,SJ_70_E=0;
      double SJ_100_px = 0, SJ_100_py=0,SJ_100_pz=0,SJ_100_E=0;
      double SJ_125_px = 0, SJ_125_py=0,SJ_125_pz=0,SJ_125_E=0;
      double SJ_150_px = 0, SJ_150_py=0,SJ_150_pz=0,SJ_150_E=0;
      double SJ_200_px = 0, SJ_200_py=0,SJ_200_pz=0,SJ_200_E=0;
      double SJ_300_px = 0, SJ_300_py=0,SJ_300_pz=0,SJ_300_E=0;
      double SJ_400_px = 0, SJ_400_py=0,SJ_400_pz=0,SJ_400_E=0;
      double SJ_600_px = 0, SJ_600_py=0,SJ_600_pz=0,SJ_600_E=0;
      double SJ_800_px = 0, SJ_800_py=0,SJ_800_pz=0,SJ_800_E=0;
      double SJ_1000_px = 0, SJ_1000_py=0,SJ_1000_pz=0,SJ_1000_E=0;

      SJ_nAK4_50[nSuperJets] = 0,  SJ_nAK4_70[nSuperJets] =0,SJ_nAK4_100[nSuperJets] = 0,SJ_nAK4_125[nSuperJets] = 0,SJ_nAK4_150[nSuperJets] = 0,SJ_nAK4_200[nSuperJets] = 0,SJ_nAK4_300[nSuperJets] = 0,SJ_nAK4_400[nSuperJets] = 0,SJ_nAK4_1000[nSuperJets] = 0;
      SJ_nAK4_600[nSuperJets] = 0, SJ_nAK4_800[nSuperJets] = 0;
      for (auto iPJ=jetsFJ_jet.begin(); iPJ<jetsFJ_jet.end(); iPJ++)                             
      {
         AK4_E[tot_mpp_AK4]= iPJ->E();
         if(iPJ->E()>50.)
         {

            SJ_AK4_50_mass[tot_nAK4_50] = iPJ->m();
            SJ_50_px+=iPJ->px();SJ_50_py+=iPJ->py();SJ_50_pz+=iPJ->pz();SJ_50_E+=iPJ->E();
            SJ_nAK4_50[nSuperJets]++;
            tot_nAK4_50++;
         }
         if(iPJ->E()> 70.)
         {
            SJ_AK4_70_mass[tot_nAK4_70] = iPJ->m();
            SJ_70_px+=iPJ->px();SJ_70_py+=iPJ->py();SJ_70_pz+=iPJ->pz();SJ_70_E+=iPJ->E();
            SJ_nAK4_70[nSuperJets]++;
            tot_nAK4_70++;
         }

         if(iPJ->E()>100)
         {
            SJ_100_px+=iPJ->px();SJ_100_py+=iPJ->py();SJ_100_pz+=iPJ->pz();SJ_100_E+=iPJ->E();
            diSuperJet_E_100 +=iPJ->E();diSuperJet_px_100+=iPJ->px();diSuperJet_py_100+=iPJ->py();diSuperJet_pz_100+=iPJ->pz();

            SJ_nAK4_100[nSuperJets]++; 
         }
         if(iPJ->E()>125)
         {
            SJ_125_px+=iPJ->px();SJ_125_py+=iPJ->py();SJ_125_pz+=iPJ->pz();SJ_125_E+=iPJ->E();

            SJ_nAK4_125[nSuperJets]++; 
         }

         if(iPJ->E()>150)
         {
            SJ_150_px+=iPJ->px();SJ_150_py+=iPJ->py();SJ_150_pz+=iPJ->pz();SJ_150_E+=iPJ->E();

            SJ_nAK4_150[nSuperJets]++; 
         }

         if(iPJ->E()>200)
         {
            SJ_200_px+=iPJ->px();SJ_200_py+=iPJ->py();SJ_200_pz+=iPJ->pz();SJ_200_E+=iPJ->E();

            SJ_nAK4_200[nSuperJets]++; 
         }

         if(iPJ->E()>300)
         {
            SJ_300_px+=iPJ->px();SJ_300_py+=iPJ->py();SJ_300_pz+=iPJ->pz();SJ_300_E+=iPJ->E();

            SJ_nAK4_300[nSuperJets]++; 
         }

         if(iPJ->E()>400)
         {
            SJ_400_px+=iPJ->px();SJ_400_py+=iPJ->py();SJ_400_pz+=iPJ->pz();SJ_400_E+=iPJ->E();

            SJ_nAK4_400[nSuperJets]++; 
         }

         if(iPJ->E()>600)
         {
            SJ_600_px+=iPJ->px();SJ_600_py+=iPJ->py();SJ_600_pz+=iPJ->pz();SJ_600_E+=iPJ->E();

            SJ_nAK4_600[nSuperJets]++; 
         }

         if(iPJ->E()>800)
         {
            SJ_800_px+=iPJ->px();SJ_800_py+=iPJ->py();SJ_800_pz+=iPJ->pz();SJ_800_E+=iPJ->E();

            SJ_nAK4_800[nSuperJets]++; 
         }

         if(iPJ->E()>1000)
         {
            SJ_1000_px+=iPJ->px();SJ_1000_py+=iPJ->py();SJ_1000_pz+=iPJ->pz();SJ_1000_E+=iPJ->E();

            SJ_nAK4_1000[nSuperJets]++; 
         }
         tot_mpp_AK4++;
      }
      SJ_mass_50[nSuperJets]= sqrt(pow(SJ_50_E,2)-pow(SJ_50_px,2)-pow(SJ_50_py,2)-pow(SJ_50_pz,2));
      SJ_mass_70[nSuperJets]= sqrt(pow(SJ_70_E,2)-pow(SJ_70_px,2)-pow(SJ_70_py,2)-pow(SJ_70_pz,2));
      SJ_mass_100[nSuperJets]= sqrt(pow(SJ_100_E,2)-pow(SJ_100_px,2)-pow(SJ_100_py,2)-pow(SJ_100_pz,2));
      SJ_mass_125[nSuperJets]= sqrt(pow(SJ_125_E,2)-pow(SJ_125_px,2)-pow(SJ_125_py,2)-pow(SJ_125_pz,2));
      SJ_mass_150[nSuperJets]= sqrt(pow(SJ_150_E,2)-pow(SJ_150_px,2)-pow(SJ_150_py,2)-pow(SJ_150_pz,2));
      SJ_mass_200[nSuperJets]= sqrt(pow(SJ_200_E,2)-pow(SJ_200_px,2)-pow(SJ_200_py,2)-pow(SJ_200_pz,2));
      SJ_mass_300[nSuperJets]= sqrt(pow(SJ_300_E,2)-pow(SJ_300_px,2)-pow(SJ_300_py,2)-pow(SJ_300_pz,2));
      SJ_mass_400[nSuperJets]= sqrt(pow(SJ_400_E,2)-pow(SJ_400_px,2)-pow(SJ_400_py,2)-pow(SJ_400_pz,2));
      SJ_mass_600[nSuperJets]= sqrt(pow(SJ_600_E,2)-pow(SJ_600_px,2)-pow(SJ_600_py,2)-pow(SJ_600_pz,2));
      SJ_mass_800[nSuperJets]= sqrt(pow(SJ_800_E,2)-pow(SJ_800_px,2)-pow(SJ_800_py,2)-pow(SJ_800_pz,2));
      SJ_mass_1000[nSuperJets]= sqrt(pow(SJ_1000_E,2)-pow(SJ_1000_px,2)-pow(SJ_1000_py,2)-pow(SJ_1000_pz,2));

      boostedSuperJetPart.clear();   //shouldn't be needed, just in case
      nSuperJets++; 
   }
   diSuperJet_mass = sqrt(pow(diSuperJet_E,2)-pow(diSuperJet_px,2)-pow(diSuperJet_py,2)-pow(diSuperJet_pz,2));
   diSuperJet_mass_100 = sqrt(pow(diSuperJet_E_100,2)-pow(diSuperJet_px_100,2)-pow(diSuperJet_py_100,2)-pow(diSuperJet_pz_100,2));
   superJetOne.clear();
   superJetTwo.clear();
   tree->Fill();

}   
DEFINE_FWK_MODULE(clusteringAnalyzer);

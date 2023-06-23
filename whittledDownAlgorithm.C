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

   bool _htWb;
   bool _htZt;
   bool _ZtWb;
   bool _WbWb;
   bool _htht;
   bool _ZtZt;
   int nSuperJets;
   int nBadClusters =0;
   int correctlySortedChi1, correctlySortedChi2;
   int jet_ndaughters[100], jet_nAK4[100];
   int nBadPassed = 0;

   int nZtZt = 0, nhtht = 0, nWbWb = 0, nZtWb = 0, nZtht = 0, nhtWb = 0;
};

clusteringAnalyzer::clusteringAnalyzer(const edm::ParameterSet& iConfig)
{
   genPartToken_ = consumes<std::vector<reco::GenParticle>>(iConfig.getParameter<edm::InputTag>("genPartCollection"));
   fatJetToken_ =    consumes<std::vector<pat::Jet>>(iConfig.getParameter<edm::InputTag>("fatJetCollection"));
   triggerBits_ = consumes<edm::TriggerResults>(iConfig.getParameter<edm::InputTag>("bits"));
   jetToken_    = consumes<std::vector<pat::Jet>>(iConfig.getParameter<edm::InputTag>("jetCollection"));
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
      if(abs( ( superJetTLV_.Px()*superJetTLV.Px()+superJetTLV_.Py()*superJetTLV.Py() +superJetTLV_.Pz()*superJetTLV.Py() )/superJetTLV.P() ) < min_pp) 
         {
            min_boost = beta_cand; 
            min_pp = abs( ( superJetTLV_.Px()*superJetTLV.Px()+superJetTLV_.Py()*superJetTLV.Py() +superJetTLV_.Pz()*superJetTLV.Py() )/superJetTLV.P() ) ;
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

void clusteringAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

   eventnum++;

////////////Gen Particles//////////////////////////////////
//////////////////////////////////////////////////////////
   edm::Handle<std::vector<reco::GenParticle>> genParticles;
   iEvent.getByToken(genPartToken_, genParticles);

   int suu_pdgid = 9936661;
   int chi_pdgid = 9936662;
   int nSuu = 0;
   int nChi = 0;
   int nq   = 0;
   int nW   = 0;
   int ntop = 0;
   int nH   = 0;
   int nb   = 0;
   int nhq  = 0;
   int nSuub = 0;
   int nZ    = 0;
   int nZq   = 0;
   int nTopb = 0;
   int nWq   = 0;
   int nhGlu = 0;

   TLorentzVector chi1(0,0,0,0);        //0
   TLorentzVector chi2(0,0,0,0);        //1
   TLorentzVector top(0,0,0,0);         //2
   TLorentzVector W_Suu(0,0,0,0);       //3
   TLorentzVector b_Suu(0,0,0,0);       //4
   TLorentzVector higgs(0,0,0,0);       //5
   TLorentzVector higgs_b1(0,0,0,0);    //6
   TLorentzVector higgs_b2(0,0,0,0);    //7
   TLorentzVector W_Suu_q1(0,0,0,0);    //8
   TLorentzVector W_Suu_q2(0,0,0,0);    //9
   TLorentzVector W_top_q1(0,0,0,0);    //10
   TLorentzVector W_top_q2(0,0,0,0);    //11
   TLorentzVector top_W(0,0,0,0);       //12
   TLorentzVector top_b(0,0,0,0);       //13

   nSuub = 0;
   for (auto iG = genParticles->begin(); iG != genParticles->end(); iG++) 
   {
      if ((abs(iG->pdgId()) == 24) && ((abs(iG->mother()->pdgId()) == chi_pdgid)) ) 
      {
         const reco::Candidate* W_final = parse_chain(iG->clone());
         for (unsigned int iii=0; iii<W_final->numberOfDaughters(); iii++)
         {
            const reco::Candidate* W_daughter = W_final->daughter(iii);
            if(abs(W_daughter->pdgId()) < 6)
            { 
               if     (W_Suu_q1.E() < 0.0000001)W_Suu_q1.SetPxPyPzE(W_daughter->px(),W_daughter->py(),W_daughter->pz(),W_daughter->energy());
               else if(W_Suu_q2.E() < 0.0000001)W_Suu_q2.SetPxPyPzE(W_daughter->px(),W_daughter->py(),W_daughter->pz(),W_daughter->energy());
               nWq++;
            }
         }
         W_Suu.SetPxPyPzE(W_final->px(),W_final->py(),W_final->pz(),W_final->energy());
         nW++;
      }
      else if ( (abs(iG->pdgId()) == 5) && (abs(iG->mother()->pdgId()) == chi_pdgid)  )
      {
         b_Suu.SetPxPyPzE(iG->px(),iG->py(),iG->pz(),iG->energy());
         nSuub++;
      } 

      else if ( (abs(iG->pdgId()) == 6) && ((abs(iG->mother()->pdgId()) == chi_pdgid)) ) 
      {
         const reco::Candidate* t_final = parse_chain(iG->clone());
         for (unsigned int iii=0; iii<t_final->numberOfDaughters(); iii++)
         {
            const reco::Candidate* t_daughter = t_final->daughter(iii);
            if (abs(t_daughter->pdgId())==24) 
            {
               const reco::Candidate* W_final = parse_chain(t_daughter->clone());
               for (unsigned int jjj=0; jjj<W_final->numberOfDaughters(); jjj++)
               {
                  const reco::Candidate* W_daughter = W_final->daughter(jjj);
                  if(abs(W_daughter->pdgId()) < 6)
                  {
                     if     (W_top_q1.E() < 0.0000001)W_top_q1.SetPxPyPzE(W_daughter->px(),W_daughter->py(),W_daughter->pz(),W_daughter->energy());
                     else if(W_top_q2.E() < 0.0000001)W_top_q2.SetPxPyPzE(W_daughter->px(),W_daughter->py(),W_daughter->pz(),W_daughter->energy());
                     nWq++;
                  } 
               }
               top_W.SetPxPyPzE(t_daughter->px(),t_daughter->py(),t_daughter->pz(),t_daughter->energy());
               nW++;
            }
            else if(abs(t_daughter->pdgId())==5) 
            {
               top_b.SetPxPyPzE(t_daughter->px(),t_daughter->py(),t_daughter->pz(),t_daughter->energy());
               nTopb++;
            }
         }
         top.SetPxPyPzE(iG->px(),iG->py(),iG->pz(),iG->energy());
         ntop++;
      }

      else if ( (abs(iG->pdgId()) == 25) && ((abs(iG->mother()->pdgId()) == chi_pdgid)) ) 
      {
         const reco::Candidate* h_final = parse_chain(iG->clone());
         for (unsigned int iii=0; iii<h_final->numberOfDaughters(); iii++)
         {
            const reco::Candidate* h_daughter = h_final->daughter(iii);
            if (abs(h_daughter->pdgId())<6)
            {
               if     (higgs_b1.E() < 0.0000001)higgs_b1.SetPxPyPzE(h_daughter->px(),h_daughter->py(),h_daughter->pz(),h_daughter->energy());
               else if(higgs_b2.E() < 0.0000001)higgs_b2.SetPxPyPzE(h_daughter->px(),h_daughter->py(),h_daughter->pz(),h_daughter->energy());
               nhq++;
            }
            else if (abs(h_daughter->pdgId()) ==24)
            {
               const reco::Candidate* higgsW_final = parse_chain(h_daughter->clone());
               for (unsigned int jjj=0; jjj<higgsW_final->numberOfDaughters(); jjj++)
               {
                  const reco::Candidate* higgsW_daughter = higgsW_final->daughter(jjj);
                  if( (abs(higgsW_daughter->pdgId()) < 6))
                  {
                     nhq++;
                  } 
               }
            }
            else if (abs(h_daughter->pdgId()) ==23)
            {
               const reco::Candidate* higgsZ_final = parse_chain(h_daughter->clone());
               for (unsigned int jjj=0; jjj<higgsZ_final->numberOfDaughters(); jjj++)
               {
                  const reco::Candidate* higgsZ_daughter = higgsZ_final->daughter(jjj);
                  if( (abs(higgsZ_daughter->pdgId()) < 6))
                  {
                     nhq++;
                  } 
               }
            }
            else if (abs(h_daughter->pdgId()) ==21)nhGlu++;

         }
         
         higgs.SetPxPyPzE(iG->px(),iG->py(),iG->pz(),iG->energy());
         nH++;

      }
      else if ( (abs(iG->pdgId()) == 23) && ((abs(iG->mother()->pdgId()) == chi_pdgid)) ) 
      {
         const reco::Candidate* Z_final = parse_chain(iG->clone());

         for (unsigned int jjj=0; jjj<Z_final->numberOfDaughters(); jjj++)
         {
            const reco::Candidate* Z_daughter = Z_final->daughter(jjj);
            if(abs(Z_daughter->pdgId()) < 6)
            {
               nZq++;
            }         
         }
         nZ++;

      }
      else if ((abs(iG->pdgId()) == chi_pdgid) && (iG->isLastCopy()))
      {
         if      (nChi == 0) chi1.SetPxPyPzE(iG->px(),iG->py(),iG->pz(),iG->energy());
         else if (nChi == 1) chi2.SetPxPyPzE(iG->px(),iG->py(),iG->pz(),iG->energy());
         nChi++;
      } 
      else if ((abs(iG->pdgId()) == suu_pdgid) && (iG->isLastCopy())) nSuu++;

   // make sure you're getting fully hadronic events 
      // ntop = 1, nW = 2, nSuub =1, ntopb = 1, nSuu = 1, nChi = 2, nHiggs = 1, nHq = 4, nWq = 4

   //add the "final" gen parts (there are 8 of them) to a vector as LeafCandidates
   std::vector<reco::LeafCandidate> genpartsLC;   
   genpartsLC.push_back(  LeafCandidate(1./3., Particle::LorentzVector(higgs_b1.Px(), higgs_b1.Py(), higgs_b1.Pz(), higgs_b1.E())));
   genpartsLC.push_back(  LeafCandidate(-1./3., Particle::LorentzVector(higgs_b2.Px(), higgs_b2.Py(), higgs_b2.Pz(), higgs_b2.E())));
   genpartsLC.push_back(  LeafCandidate(1./3., Particle::LorentzVector(W_Suu_q1.Px(), W_Suu_q1.Py(), W_Suu_q1.Pz(), W_Suu_q1.E())));
   genpartsLC.push_back(  LeafCandidate(2./3., Particle::LorentzVector(W_Suu_q2.Px(), W_Suu_q2.Py(), W_Suu_q2.Pz(), W_Suu_q2.E())));
   genpartsLC.push_back(  LeafCandidate(1./3., Particle::LorentzVector(W_top_q1.Px(), W_top_q1.Py(), W_top_q1.Pz(), W_top_q1.E())));
   genpartsLC.push_back(  LeafCandidate(2./3., Particle::LorentzVector(W_top_q2.Px(), W_top_q2.Py(), W_top_q2.Pz(), W_top_q2.E())));
   genpartsLC.push_back(  LeafCandidate(-1./3., Particle::LorentzVector(b_Suu.Px(), b_Suu.Py(), b_Suu.Pz(), b_Suu.E())));
   genpartsLC.push_back(  LeafCandidate(-1./3., Particle::LorentzVector(top_b.Px(), top_b.Py(), top_b.Pz(), top_b.E())));

   //////////////////////////find COM of "final" gen particles ///////////////////////////////////
   std::vector<reco::LeafCandidate> genPartsBoosted;   
   std::vector<reco::LeafCandidate> genPartsUnboosted;

   double genPart_px = 0, genPart_py = 0,genPart_pz = 0,genPart_E = 0;
   for(auto iG = genpartsLC.begin();iG<genpartsLC.end();iG++)
   {
      genPart_px+=iG->px();genPart_py+=iG->py();genPart_pz+=iG->pz();genPart_E+=iG->energy();
      genPartsUnboosted.push_back( LeafCandidate(iG->charge(), Particle::LorentzVector(iG->px(), iG->py(), iG->pz(), iG->energy())));
   }

   double genPart_totP = sqrt(pow(genPart_px,2) + pow(genPart_py,2) + pow(genPart_pz,2));
   genPartBetaCOM = genPart_totP/genPart_E;
   TVector3 genPartBeta(genPart_px/genPart_E,genPart_py/genPart_E ,genPart_pz/genPart_E);

   ///////////////with the boost vector in hand, boost all "final" gen particles to the CoM
   for(auto iG = genPartsUnboosted.begin();iG<genPartsUnboosted.end();iG++)
   {
      TLorentzVector iC_(iG->px(),iG->py(),iG->pz(),iG->energy());
      iC_.Boost(-genPartBeta.X(),-genPartBeta.Y(),-genPartBeta.Z());
      genPartsBoosted.push_back(LeafCandidate(iG->charge(), Particle::LorentzVector(iC_.Px(), iC_.Py(), iC_.Pz(), iC_.E())));      
   }   

   /////////////////calculate the thrust axis in boosted frame////////////////////
   Thrust genPartThrust_(genPartsBoosted.begin(), genPartsBoosted.end());
   Vector genPartThrustAxis = genPartThrust_.axis();
   TVector3 genPartThrust_vector(genPartThrustAxis.X(),genPartThrustAxis.Y(),genPartThrustAxis.Z());


   //////////////////boost all your particles to the CoM frame//////////////////////
   chi1.Boost(-genPartBeta.X(),-genPartBeta.Y(),-genPartBeta.Z());
   chi1.Boost(-genPartBeta.X(),-genPartBeta.Y(),-genPartBeta.Z());

   higgs_b1.Boost(-genPartBeta.X(),-genPartBeta.Y(),-genPartBeta.Z());
   higgs_b2.Boost(-genPartBeta.X(),-genPartBeta.Y(),-genPartBeta.Z());
   W_Suu_q1.Boost(-genPartBeta.X(),-genPartBeta.Y(),-genPartBeta.Z());
   W_Suu_q2.Boost(-genPartBeta.X(),-genPartBeta.Y(),-genPartBeta.Z());
   W_top_q1.Boost(-genPartBeta.X(),-genPartBeta.Y(),-genPartBeta.Z());
   W_top_q2.Boost(-genPartBeta.X(),-genPartBeta.Y(),-genPartBeta.Z());
   b_Suu.Boost(-genPartBeta.X(),-genPartBeta.Y(),-genPartBeta.Z());
   top_b.Boost(-genPartBeta.X(),-genPartBeta.Y(),-genPartBeta.Z());

   ///////do for top, h, W's,


   TVector3 higgs_b1_vec = higgs_b1.Vect();
   TVector3 higgs_b2_vec = higgs_b2.Vect();
   TVector3 W_Suu_q1_vec = W_Suu_q1.Vect();
   TVector3 W_Suu_q2_vec = W_Suu_q2.Vect();
   TVector3 W_top_q1_vec = W_top_q1.Vect();
   TVector3 W_top_q2_vec = W_top_q2.Vect();
   TVector3 b_Suu_vec = b_Suu.Vect();
   TVector3 top_b_vec = top_b.Vect();

   ///////////////use the angle between the thrust axis and each gen particle to sort them into one of the two superjets/////////////////////


   tree->Fill();
}   
DEFINE_FWK_MODULE(clusteringAnalyzer);
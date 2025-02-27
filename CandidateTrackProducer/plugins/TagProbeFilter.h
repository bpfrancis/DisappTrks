#include "FWCore/Common/interface/TriggerNames.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Run.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/PackedCandidate.h"
#include "DataFormats/VertexReco/interface/Vertex.h"

#include "RecoEgamma/EgammaTools/interface/ConversionTools.h"

using namespace std;

enum Flavor {ELECTRON, MUON, TAUTOELECTRON, TAUTOMUON};

template<Flavor T>
class TagProbeFilter : public edm::EDFilter {
   public:
      TagProbeFilter (const edm::ParameterSet &);
      ~TagProbeFilter ();

      bool filter (edm::Event &, const edm::EventSetup &);

   private:
      bool passesTrigger (const edm::Event &, const edm::TriggerResults &) const;
      void selectTags (const edm::Event &,
                       const edm::TriggerResults &,
                       const vector<pat::TriggerObjectStandAlone> &,
                       const reco::Vertex &,
                       const vector<pat::Electron> &,
                       const vector<pat::Muon> &,
                       vector<pat::Electron> &,
                       vector<pat::Muon> &);
      void selectProbes (const reco::Vertex &,
                         const vector<reco::Track> &,
                         vector<reco::Track> &);

      bool filterDecision (const vector<pat::Electron>,
                           const vector<pat::Muon>,
                           const pat::MET &,
                           const vector<reco::Track>) const;

      const double getTrackIsolation (const reco::Track &, 
                                      const vector<reco::Track> &, 
                                      const bool, 
                                      const bool, 
                                      const double, 
                                      const double = 1.0e-12) const;

      edm::InputTag triggers_;
      edm::InputTag trigObjs_;
      edm::InputTag vertices_;
      edm::InputTag met_;
      edm::InputTag electrons_;
      edm::InputTag muons_;
      edm::InputTag tracks_;

      vector<string> triggerNames_;
      string dataTakingPeriod_;

      bool is2017_;

      edm::EDGetTokenT<edm::TriggerResults>                   triggersToken_;
      edm::EDGetTokenT<vector<pat::TriggerObjectStandAlone> > trigObjsToken_;
      edm::EDGetTokenT<vector<reco::Vertex> >                 verticesToken_;
      edm::EDGetTokenT<vector<pat::MET> >                     metToken_;
      edm::EDGetTokenT<vector<pat::Electron> >                electronsToken_;
      edm::EDGetTokenT<vector<pat::Muon> >                    muonsToken_;
      edm::EDGetTokenT<vector<reco::Track> >                  tracksToken_;
};

// system include files
#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <regex>
#include <iostream>
#include <bitset>
#include <TH1D.h>
#include <TEfficiency.h>


// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Run.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/ConsumesCollector.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "RecoMuon/TrackingTools/interface/MuonServiceProxy.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

// GEM
#include "SimDataFormats/Track/interface/SimTrackContainer.h"
#include "SimDataFormats/TrackingHit/interface/PSimHitContainer.h"
#include "SimDataFormats/GEMDigiSimLink/interface/GEMDigiSimLink.h"
#include "DataFormats/Common/interface/DetSetVector.h"
#include "DataFormats/Common/interface/DetSetVectorNew.h"
#include "DataFormats/MuonDetId/interface/GEMDetId.h"
#include "DataFormats/GEMDigi/interface/GEMDigi.h"
#include "DataFormats/GEMDigi/interface/GEMDigiCollection.h"
#include "DataFormats/GEMRecHit/interface/GEMRecHitCollection.h"
#include "DataFormats/GEMRecHit/interface/GEMSegmentCollection.h"

#include "Geometry/CommonDetUnit/interface/GeomDet.h"
#include "Geometry/Records/interface/MuonGeometryRecord.h"
#include "Geometry/GEMGeometry/interface/GEMGeometry.h"
#include "Geometry/CommonTopologies/interface/GEMStripTopology.h"

#include "ME0StubFinder/ME0StubFinder/interface/ChamberBeh.h"

#include "ME0StubFinder/ME0StubFinder/interface/ME0SimTrackHitCollection.h"

class ME0StubAnalyzer : public edm::one::EDAnalyzer<edm::one::WatchRuns> {
public:
    explicit ME0StubAnalyzer(const edm::ParameterSet &);
    ~ME0StubAnalyzer();

private:
    virtual void beginJob() override;
    virtual void analyze(const edm::Event &, const edm::EventSetup &) override;
    virtual void endJob() override;
    
    virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
    virtual void endRun(edm::Run const&, edm::EventSetup const&) override;

    bool isSimTrackGood(const SimTrack&);
    std::vector<me0::ME0SimSegment> ME0StubAnalyzer::buildME0SimSegments(
        const std::vector<SimTrack>& simTracks,
        const edm::DetSetVector<GEMDigiSimLink>& links,
        const std::vector<PSimHit>& simHits,
        const GEMGeometry& geometry);
    
private:
    edm::Service<TFileService> fs_;
    edm::ESGetToken<GEMGeometry, MuonGeometryRecord>    gemGeometry_;
    edm::EDGetTokenT<edm::SimTrackContainer>            gemSimTracks_;
    edm::EDGetTokenT<edm::PSimHitContainer>             gemSimHits_;
    edm::EDGetTokenT<GEMDigiCollection>                 gemDigis_;
    edm::EDGetTokenT<edm::DetSetVector<GEMDigiSimLink>> gemLinks_;
    edm::EDGetTokenT<GEMRecHitCollection>               gemRecHits_;
    edm::EDGetTokenT<GEMSegmentCollection>              gemSegments_;

    int ievent = 0;
    int n_offline_effi_total = 0;
    int n_offline_effi_passed = 0;
    int n_offline_purity_total = 0;
    int n_offline_purity_passed = 0;
    int n_st_effi_total = 0;
    int n_st_effi_passed = 0;
    int n_st_purity_total = 0;
    int n_st_purity_passed = 0;

};
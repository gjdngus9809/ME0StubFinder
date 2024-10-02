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
#include <TLatex.h>
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
#include "ME0StubFinder/ME0StubFinder/interface/Subfunc.h"

// typedef std::bitset<192> UInt192;
typedef std::vector<std::vector<UInt192>> ME0ChamberData;

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

private:
    edm::Service<TFileService> fs;
    edm::ESGetToken<GEMGeometry, MuonGeometryRecord>    gemGeometry_;
    edm::EDGetTokenT<edm::SimTrackContainer>            gemSimTracks_;
    edm::EDGetTokenT<edm::PSimHitContainer>             gemSimHits_;
    edm::EDGetTokenT<GEMDigiCollection>                 gemDigis_;
    edm::EDGetTokenT<edm::DetSetVector<GEMDigiSimLink>> gemLinks_;
    edm::EDGetTokenT<GEMRecHitCollection>               gemRecHits_;
    edm::EDGetTokenT<GEMSegmentCollection>              gemSegments_;

    Config config;

    std::vector<double> TrackPt;
    std::vector<float>  TrackSubstrip;
    std::vector<double> TrackBendingAngle;
    std::vector<int>    TrackChamberNr;
    std::vector<int>    TrackiEta;
    std::vector<int>    TrackNLayers;
    std::vector<int>    TrackNHit;
    int NSimTrack;

    std::vector<float>  SegSubstrip;
    std::vector<double> SegBendingAngle;
    std::vector<int>    SegChamberNr;
    std::vector<int>    SegiEta;
    std::vector<int>    SegNLayers;
    std::vector<int>    SegNHit;
    int NOffSeg;

    int ievent = 0;
    int n_offline_effi_total = 0;
    int n_offline_effi_passed = 0;
    int n_offline_purity_total = 0;
    int n_offline_purity_passed = 0;
    int n_st_effi_total = 0;
    int n_st_effi_passed = 0;
    int n_st_purity_total = 0;
    int n_st_purity_passed = 0;

    TH1D* num_seg_per_chamber;
    TH1D* num_seg_per_chamber_offline;
    TH1D* rate_seg_per_eta;
    TH1D* rate_seg_per_bending_angle;
    TH1D* rate_seg_per_chamber_p;
    TH1D* rate_seg_per_chamber_m;
    TH1D* overall_performance;

    TH1D* offline_effi_passed_bending;
    TH1D* offline_effi_total_bending;
    TH1D* offline_effi_passed_eta;
    TH1D* offline_effi_total_eta;
    TH1D* offline_effi_passed_nlayer;
    TH1D* offline_effi_total_nlayer;
    TH1D* offline_effi_mres;
    TH1D* offline_effi_sres;
    TH1D* offline_purity_passed_eta;
    TH1D* offline_purity_total_eta;
    TH1D* offline_purity_passed_bending;
    TH1D* offline_purity_total_bending;
    TH1D* offline_purity_passed_nlayer;
    TH1D* offline_purity_total_nlayer;
    
    TH1D* st_effi_passed_pt;
    TH1D* st_effi_total_pt;
    TH1D* st_effi_passed_eta;
    TH1D* st_effi_total_eta;
    TH1D* st_effi_passed_bending;
    TH1D* st_effi_total_bending;
    TH1D* st_effi_passed_nlayer;
    TH1D* st_effi_total_nlayer;
    TH1D* st_effi_mres;
    TH1D* st_effi_sres;
    TH1D* st_purity_passed_eta;
    TH1D* st_purity_total_eta;
    TH1D* st_purity_passed_bending;
    TH1D* st_purity_total_bending;
    TH1D* st_purity_passed_nlayer;
    TH1D* st_purity_total_nlayer;
};


ME0StubAnalyzer::ME0StubAnalyzer(const edm::ParameterSet &iConfig)
    : gemSimTracks_(consumes<edm::SimTrackContainer>(iConfig.getParameter<edm::InputTag>("gemSimTrackLabel"))),
      gemSimHits_(consumes<edm::PSimHitContainer>(iConfig.getParameter<edm::InputTag>("gemSimHitLabel"))),
      gemRecHits_(consumes<GEMRecHitCollection>(iConfig.getParameter<edm::InputTag>("gemRecHitLabel"))),
      gemSegments_(consumes<GEMSegmentCollection>(iConfig.getParameter<edm::InputTag>("gemSegmentLabel")))
{
    gemGeometry_ = esConsumes<GEMGeometry,MuonGeometryRecord>();
}
ME0StubAnalyzer::~ME0StubAnalyzer() {}

bool ME0StubAnalyzer::isSimTrackGood(const SimTrack& simTrack) {
    const EncodedEventId& eventId = simTrack.eventId();
    if (eventId.event() != 0) return false;
    if (eventId.bunchCrossing() != 0) return false;

    return true;
}

void ME0StubAnalyzer::analyze(const edm::Event &iEvent,
                        const edm::EventSetup &iSetup) {

    const GEMGeometry&                            gemGeometry  = iSetup.getData(gemGeometry_);
    const std::vector<SimTrack>&                  gemSimTracks = iEvent.get(gemSimTracks_);
    const std::vector<PSimHit>&                   gemSimHits   = iEvent.get(gemSimHits_);
    const edm::RangeMap<GEMDetId, edm::OwnVector<GEMRecHit, edm::ClonePolicy<GEMRecHit>>, edm::ClonePolicy<GEMRecHit>>&
                                                  gemRecHits   = iEvent.get(gemRecHits_);
    const edm::RangeMap<GEMDetId, edm::OwnVector<GEMSegment>>&
                                                  gemSegments  = iEvent.get(gemSegments_);
    
    ++ievent;

    TrackPt.clear();
    TrackSubstrip.clear();
    TrackBendingAngle.clear();
    TrackChamberNr.clear();
    TrackiEta.clear();
    TrackNLayers.clear();
    TrackNHit.clear();

    SegSubstrip.clear();
    SegBendingAngle.clear();
    SegChamberNr.clear();
    SegiEta.clear();
    SegNLayers.clear();
    SegNHit.clear();

    // Analyze simTracks
    for (const SimTrack& simTrack : gemSimTracks) {
        if (!isSimTrackGood(simTrack)) continue;
        if (std::abs(simTrack.type()) != 13) continue;

        const EncodedEventId&& eventId = simTrack.eventId();
        const unsigned int trackId = simTrack.trackId();

        std::vector<PSimHit> SimHitCollection;
        std::vector<bool> nlayersHit{false,false,false,false,false,false};
        std::map<int, int> ietaList;
        for (const PSimHit& simHit : gemSimHits) {
            const GEMDetId& simHitGEMId{simHit.detUnitId()};

            if (simHitGEMId.station() != 0) continue;

            if (eventId != simHit.eventId()) continue;
            if (trackId != simHit.trackId()) continue;

            if (std::abs(simHit.particleType()) != 13) continue;
            
            SimHitCollection.push_back(simHit);
            int ieta = simHitGEMId.ieta();
            int layer = simHitGEMId.layer();

            ietaList[ieta]++;
            nlayersHit[layer] = true;
        }

        int nhit = SimHitCollection.size();
        if (nhit < 4) continue;
        
        std::sort(SimHitCollection.begin(), SimHitCollection.end(),
                  [](const PSimHit lhs, const PSimHit rhs) {
                    const GEMDetId lhsGEMId{lhs.detUnitId()};
                    const GEMDetId rhsGEMId{lhs.detUnitId()};
                    return ((int) lhsGEMId.layer()) > ((int) rhsGEMId.layer());});

        const PSimHit& topHit = SimHitCollection.front();
        const PSimHit& botHit = SimHitCollection.back();

        const GEMDetId& topGEMId{topHit.detUnitId()};
        const GEMDetId& botGEMId{botHit.detUnitId()};
        const GEMEtaPartition* topEtaPart = gemGeometry.etaPartition(topGEMId);
        const GEMEtaPartition* botEtaPart = gemGeometry.etaPartition(botGEMId);

        auto topLP = topHit.localPosition();
        auto botLP = botHit.localPosition();

        int topStrip = topEtaPart->strip(topLP)/config.num_or;
        int botStrip = botEtaPart->strip(botLP)/config.num_or;

        int topLayer = topGEMId.layer();
        int botLayer = botGEMId.layer();

        float substrip = (float)(topStrip+botStrip)/2.0f;
        double bendingAngle = (double)(topStrip-botStrip)/(double)(topLayer-botLayer);

        int chamberNr = topGEMId.region()==1? topGEMId.chamber()+17: topGEMId.chamber()-1;
        int ieta = -1;
        int maxCount = -1;
        for (const auto& pair : ietaList) {
            if (pair.second > maxCount) {
                maxCount = pair.second;
                ieta = pair.first;
            }
        }
        
        int nlayers = 0;
        for (bool l : nlayersHit) {if (l) ++nlayers;}

        TrackPt.push_back(simTrack.momentum().Pt());
        TrackSubstrip.push_back(substrip);
        TrackBendingAngle.push_back(bendingAngle);
        TrackChamberNr.push_back(chamberNr);
        TrackiEta.push_back(ieta);
        TrackNLayers.push_back(nlayers);
        TrackNHit.push_back(nhit);
    }
    NSimTrack = TrackSubstrip.size();

    // Analyze offline Segment
    for (const GEMSegment& segment : gemSegments) {
        std::vector<GEMRecHit> RecHitCollection = segment.specificRecHits();

        std::vector<bool> nlayersHit{false,false,false,false,false,false};
        std::map<int, int> ietaList;
        bool isME0Seg = true;
        for (const GEMRecHit& recHit : RecHitCollection) {
            const GEMDetId recHitGEMId{recHit.gemId()};

            if (recHitGEMId.station() != 0) {
                isME0Seg = false;
                continue;
            }
            
            int ieta = recHitGEMId.ieta();
            int layer = recHitGEMId.layer();

            ietaList[ieta]++;
            nlayersHit[layer] = true;
        }
        if (!isME0Seg) continue;
        
        int nhit = RecHitCollection.size();
        if (nhit < 4) continue;

        std::sort(RecHitCollection.begin(), RecHitCollection.end(),
          [](const GEMRecHit& lhs, const GEMRecHit& rhs) {
            const GEMDetId lhsGEMId{lhs.gemId()};
            const GEMDetId rhsGEMId{lhs.gemId()};
            return ((int) lhsGEMId.layer()) > ((int) rhsGEMId.layer());});

        
        const GEMRecHit& topHit = RecHitCollection.front();
        const GEMRecHit& botHit = RecHitCollection.back();

        const GEMDetId& topGEMId{topHit.gemId()};
        const GEMDetId& botGEMId{botHit.gemId()};

        int topStrip = (topHit.firstClusterStrip() + topHit.clusterSize()/2)/2;
        int botStrip = (botHit.firstClusterStrip() + botHit.clusterSize()/2)/2;

        int topLayer = topGEMId.layer();
        int botLayer = botGEMId.layer();

        float substrip = (float)(topStrip+botStrip)/2.0f;
        double bendingAngle = (double)(topStrip-botStrip)/(double)(topLayer-botLayer);

        int chamberNr = topGEMId.region()==1? topGEMId.chamber()+17: topGEMId.chamber()-1;
        int ieta = -1;
        int maxCount = -1;
        for (const auto& pair : ietaList) {
            if (pair.second > maxCount) {
                maxCount = pair.second;
                ieta = pair.first;
            }
        }
        
        int nlayers = 0;
        for (bool l : nlayersHit) {if (l) ++nlayers;}
        

        SegSubstrip.push_back(substrip);
        SegBendingAngle.push_back(bendingAngle);
        SegChamberNr.push_back(chamberNr);
        SegiEta.push_back(ieta);
        SegNLayers.push_back(nlayers);
        SegNHit.push_back(nhit);
    }
    int NOffSeg = SegSubstrip.size();

    // Fill chamber data using rechit
    std::map<int, ME0ChamberData> DataMap;
    for (const GEMRecHit& recHit : gemRecHits) {
        const GEMDetId& recHitGEMId{recHit.gemId()};

        if ((int)recHitGEMId.station() != 0) continue;

        int chamberNr = recHitGEMId.region()==1? recHitGEMId.chamber()+17: recHitGEMId.chamber()-1;

        if (DataMap[chamberNr].empty()) {
            DataMap[chamberNr] 
                = std::vector<std::vector<UInt192>>(8,{UInt192(0),UInt192(0),UInt192(0),UInt192(0),UInt192(0),UInt192(0)});
        }

        int layer = recHitGEMId.layer();
        int ieta = recHitGEMId.ieta();
        int ring = recHitGEMId.ring();
        int region = recHitGEMId.region();

        int firstSbit = recHit.firstClusterStrip()/config.num_or;
        int lastSbit = (recHit.firstClusterStrip()+recHit.clusterSize()-1)/config.num_or;

        std::cout << ring << " " << region << " " << layer << " " << ieta << " " << recHitGEMId.chamber() << std::endl;

        for (int sbit=firstSbit; sbit<=lastSbit; ++sbit) {
            (DataMap[chamberNr].at(ieta-1)).at(layer-1) |= (UInt192(1) << sbit);
        }
    }

    // Find stub per chamber
    std::map<int,std::vector<ME0Stub>> online_segment_chamber; 
    for (const auto& data_pair : DataMap) {
        int chamberNr = data_pair.first;
        auto data = data_pair.second;

        bool isNoneZero = false;
        for (const auto& firstLayer : data) {
            if (firstLayer[0].any()) isNoneZero = true; 
        }
        if (!isNoneZero) continue;

        std::vector<ME0Stub> SegList = process_chamber(data, config);
        
        for (ME0Stub& seg : SegList) {
            if (seg.PatternId() == 0) continue;
            seg.fit(config.max_span);
            if ((seg.EtaPartition() % 2) != 0) seg.SetEtaPartition(seg.EtaPartition()/2 + 1) ;
            else seg.SetEtaPartition(seg.EtaPartition()/2);

            online_segment_chamber[chamberNr].push_back(seg);
        }
    }

    for (const auto& pair : online_segment_chamber) {
        int chamber = pair.first;
        num_seg_per_chamber->Fill((double) pair.second.size());
        for (const auto& seg : pair.second) {
            rate_seg_per_eta->Fill(seg.EtaPartition()+1);
            rate_seg_per_bending_angle->Fill(seg.BendingAngle());
        }
        if (chamber > 18) {
            for (int i=0; i<(int)pair.second.size(); ++i) {
                rate_seg_per_chamber_p->Fill(chamber-18);
            }
        }
        else {
            for (int i=0; i<(int)pair.second.size(); ++i) {
                rate_seg_per_chamber_m->Fill(chamber);
            }
        }
    }
    
    for (int c=1; c<=36; ++c) {
        int n_seg_chamber = 0;
        for (int i=0; i<NOffSeg; ++i) {
            if (c==SegChamberNr[i])
                n_seg_chamber++;
        }
        num_seg_per_chamber_offline->Fill(n_seg_chamber);        
    }

    // Checking efficiency w.r.t. offline segmtents
    std::vector<int> unmatched_offline_index;
    for (int i=0; i<NOffSeg; ++i) {
        float offline_substrip       = SegSubstrip[i];
        double offline_bending_angle = SegBendingAngle[i];
        int offline_chamber          = SegChamberNr[i];
        int offline_ieta             = SegiEta[i];
        int offline_nlayers          = SegNLayers[i];
        int offline_nhit             = SegNHit[i];
        offline_effi_total_bending->Fill(offline_bending_angle);
        offline_effi_total_eta->Fill(offline_ieta+1);
        offline_effi_total_nlayer->Fill(offline_nlayers);
        n_offline_effi_total++;

        bool seg_match = false;
        std::vector<int> seg_matched_index;
        if (online_segment_chamber[offline_chamber].empty()) {
            unmatched_offline_index.push_back(i);
            continue;
        }

        int idx = -1;
        for (const auto& seg : online_segment_chamber[offline_chamber]) {
            idx++;
            if (std::find(seg_matched_index.begin(), 
                          seg_matched_index.end(), idx) != seg_matched_index.end())
                continue;
            float online_substrip = seg.SubStrip()+seg.Strip();
            double online_bending_angle = seg.BendingAngle();
            int online_ieta = seg.EtaPartition();
            int online_id = seg.PatternId();
            int online_hc = seg.HitCount();
            int online_lc = seg.LayerCount();
            int online_quality = seg.Quality();

            if (std::abs(online_ieta - offline_ieta) > 1) continue;
            if (std::abs(online_substrip - offline_substrip) > 5) continue;
            double bending_angle_err = 
                (online_bending_angle == 0)?
                std::abs(offline_bending_angle):
                std::abs((offline_bending_angle - online_bending_angle)/online_bending_angle);
            if (bending_angle_err >= 0.4 && std::abs(online_bending_angle - offline_bending_angle) > 0.6) continue;
            offline_effi_passed_bending->Fill(offline_bending_angle);
            offline_effi_passed_eta->Fill(offline_ieta);
            offline_effi_passed_nlayer->Fill(offline_nlayers);
            n_offline_effi_passed++;
            offline_effi_mres->Fill(offline_bending_angle - online_bending_angle);
            offline_effi_sres->Fill(offline_substrip - online_substrip);
            seg_match = true;
            seg_matched_index.push_back(idx);
            break;
        }
        if (!seg_match) unmatched_offline_index.push_back(i);
    }

    // Checking Purity w.r.t. offline segmtents
    for (const auto& pair : online_segment_chamber) {
        int chamber = pair.first;
        for (const auto& seg : pair.second) {
            float online_substrip = seg.SubStrip()+seg.Strip();
            double online_bending_angle = seg.BendingAngle();
            int online_ieta = seg.EtaPartition();
            // int online_id = seg.PatternId();
            // int online_hc = seg.HitCount();
            int online_lc = seg.LayerCount();
            int online_quality = seg.Quality();
            offline_purity_total_eta->Fill(online_ieta);
            offline_purity_total_bending->Fill(online_bending_angle);
            offline_purity_total_nlayer->Fill(online_lc);
            n_offline_purity_total++;
            for (int i=0; i<NOffSeg; ++i) {
                float offline_substrip       = SegSubstrip[i];
                double offline_bending_angle = SegBendingAngle[i];
                int offline_chamber          = SegChamberNr[i];
                int offline_ieta             = SegiEta[i];
                // int offline_nlayers          = SegNLayers[i];
                // int offline_nhit             = SegNHit[i];

                if (chamber != offline_chamber) continue;
                if (std::abs(online_ieta - offline_ieta) > 1) continue;
                if (std::abs(online_substrip - offline_substrip) > 5) continue;
                double bending_angle_err = 
                    (online_bending_angle == 0)?
                    std::abs(offline_bending_angle):
                    std::abs((offline_bending_angle - online_bending_angle)/online_bending_angle);
                if (bending_angle_err >= 0.4 && std::abs(online_bending_angle - offline_bending_angle) > 0.6) continue;
                offline_purity_passed_eta->Fill(online_ieta);
                offline_purity_passed_bending->Fill(online_bending_angle);
                offline_purity_passed_nlayer->Fill(online_lc);
                n_offline_purity_passed++;
                break;
            }
        }
    }

    // Checking efficiency w.r.t. sim tracks
    std::vector<int> unmatched_st_index;
    for (int i=0; i<NSimTrack; ++i) {
        double st_pt            = TrackPt[i];
        float st_substrip       = TrackSubstrip[i];
        double st_bending_angle = TrackBendingAngle[i];
        int st_chamber          = TrackChamberNr[i];
        int st_ieta             = TrackiEta[i];
        int st_nlayers          = TrackNLayers[i];
        int st_nhit             = TrackNHit[i];
        st_effi_total_pt->Fill(st_pt);
        st_effi_total_bending->Fill(st_bending_angle);
        st_effi_total_eta->Fill(st_ieta+1);
        st_effi_total_nlayer->Fill(st_nlayers);
        n_st_effi_total++;

        bool track_match = false;
        std::vector<int> track_matched_index;
        if (online_segment_chamber[st_chamber].empty()) {
            unmatched_st_index.push_back(i);
            continue;
        }

        int idx = -1;
        for (const auto& seg : online_segment_chamber[st_chamber]) {
            idx++;
            if (std::find(track_matched_index.begin(), 
                          track_matched_index.end(), idx) != track_matched_index.end())
                continue;
            float online_substrip = seg.SubStrip()+seg.Strip();
            double online_bending_angle = seg.BendingAngle();
            int online_ieta = seg.EtaPartition();
            int online_id = seg.PatternId();
            int online_hc = seg.HitCount();
            int online_lc = seg.LayerCount();
            int online_quality = seg.Quality();

            if (std::abs(online_ieta - st_ieta) > 1) continue;
            if (std::abs(online_substrip - st_substrip) > 5) continue;
            double bending_angle_err = 
                (online_bending_angle == 0)?
                std::abs(st_bending_angle):
                std::abs((st_bending_angle - online_bending_angle)/online_bending_angle);
            if (bending_angle_err >= 0.4 && std::abs(online_bending_angle - st_bending_angle) > 0.6) continue;
            st_effi_passed_pt->Fill(st_pt);
            st_effi_passed_bending->Fill(st_bending_angle);
            st_effi_passed_eta->Fill(st_ieta);
            st_effi_passed_nlayer->Fill(st_nlayers);
            n_st_effi_passed++;
            st_effi_mres->Fill(st_bending_angle - online_bending_angle);
            st_effi_sres->Fill(st_substrip - online_substrip);
            track_match = true;
            track_matched_index.push_back(idx);
            break;
        }
        if (!track_match) unmatched_st_index.push_back(i);
    }

    // Checking Purity w.r.t. sim tracks
    for (const auto& pair : online_segment_chamber) {
        int chamber = pair.first;
        for (const auto& seg : pair.second) {
            float online_substrip = seg.SubStrip()+seg.Strip();
            double online_bending_angle = seg.BendingAngle();
            int online_ieta = seg.EtaPartition();
            // int online_id = seg.PatternId();
            // int online_hc = seg.HitCount();
            int online_lc = seg.LayerCount();
            int online_quality = seg.Quality();
            st_purity_total_eta->Fill(online_ieta);
            st_purity_total_bending->Fill(online_bending_angle);
            st_purity_total_nlayer->Fill(online_lc);
            n_st_purity_total++;
            for (int i=0; i<NSimTrack; ++i) {
                float st_substrip       = TrackSubstrip[i];
                double st_bending_angle = TrackBendingAngle[i];
                int st_chamber          = TrackChamberNr[i];
                int st_ieta             = TrackiEta[i];
                // int st_nlayers          = TrackNLayers[i];
                // int st_nhit             = TrackNHit[i];

                if (chamber != st_chamber) continue;
                if (std::abs(online_ieta - st_ieta) > 1) continue;
                if (std::abs(online_substrip - st_substrip) > 5) continue;
                double bending_angle_err = 
                    (online_bending_angle == 0)?
                    std::abs(st_bending_angle):
                    std::abs((st_bending_angle - online_bending_angle)/online_bending_angle);
                if (bending_angle_err >= 0.4 && std::abs(online_bending_angle - st_bending_angle) > 0.6) continue;
                st_purity_passed_eta->Fill(online_ieta);
                st_purity_passed_bending->Fill(online_bending_angle);
                st_purity_passed_nlayer->Fill(online_lc);
                n_st_purity_passed++;
                break;
            }
        }
    }
}

void ME0StubAnalyzer::beginJob() {}
void ME0StubAnalyzer::endJob() {}

void ME0StubAnalyzer::beginRun(const edm::Run& run, const edm::EventSetup& iSetup) {
    // make histograms
    num_seg_per_chamber           = fs->make<TH1D>("num_seg_per_chamber",
                                                   "num_seg_per_chamber",
                                                   13, -0.5, 12.5);
    num_seg_per_chamber_offline   = fs->make<TH1D>("num_seg_per_chamber_offline",
                                                   "num_seg_per_chamber_offline",
                                                   13, -0.5, 12.5);
    rate_seg_per_eta              = fs->make<TH1D>("rate_seg_per_eta",
                                                   "rate_seg_per_eta",
                                                   8, 0.5, 8.5);
    rate_seg_per_bending_angle    = fs->make<TH1D>("rate_seg_per_bending_angle",
                                                   "rate_seg_per_bending_angle",
                                                   200, -10.0, 10.0);
    rate_seg_per_chamber_p        = fs->make<TH1D>("rate_seg_per_chamber_p",
                                                   "rate_seg_per_chamber_p",
                                                   18, 0.5, 18.5);
    rate_seg_per_chamber_m        = fs->make<TH1D>("rate_seg_per_chamber_m",
                                                   "rate_seg_per_chamber_m",
                                                   18, 0.5, 18.5);
    overall_performance           = fs->make<TH1D>("overall_performance",
                                                   "overall_performance",
                                                   8, -0.5, 7.5);
    offline_effi_passed_bending   = fs->make<TH1D>("offline_effi_passed_bending",
                                                   "offline_effi_passed_bending",
                                                   100, -10.0, 10.0);
    offline_effi_total_bending    = fs->make<TH1D>("offline_effi_total_bending",
                                                   "offline_effi_total_bending",
                                                   100, -10.0, 10.0);
    offline_effi_passed_eta       = fs->make<TH1D>("offline_effi_passed_eta",
                                                   "offline_effi_passed_eta",
                                                   8, 0.5, 8.5);
    offline_effi_total_eta        = fs->make<TH1D>("offline_effi_total_eta",
                                                   "offline_effi_total_eta",
                                                   8, 0.5, 8.5);
    offline_effi_passed_nlayer    = fs->make<TH1D>("offline_effi_passed_nlayer",
                                                   "offline_effi_passed_nlayer",
                                                   6, 0.5, 6.5);
    offline_effi_total_nlayer     = fs->make<TH1D>("offline_effi_total_nlayer",
                                                   "offline_effi_total_nlayer",
                                                   6, 0.5, 6.5);
    offline_effi_mres             = fs->make<TH1D>("offline_effi_mres",
                                                   "offline_effi_mres",
                                                   100, -10.0, 10.0);
    offline_effi_sres             = fs->make<TH1D>("offline_effi_sres",
                                                   "offline_effi_sres",
                                                   100, -1.0, 1.0);
    offline_purity_passed_eta     = fs->make<TH1D>("offline_purity_passed_eta",
                                                   "offline_purity_passed_eta",
                                                   8, 0.5, 8.5);
    offline_purity_total_eta      = fs->make<TH1D>("offline_purity_total_eta",
                                                   "offline_purity_total_eta",
                                                   8, 0.5, 8.5);
    offline_purity_passed_bending = fs->make<TH1D>("offline_purity_passed_bending",
                                                   "offline_purity_passed_bending",
                                                   100, -10.0, 10.0);
    offline_purity_total_bending  = fs->make<TH1D>("offline_purity_total_bending",
                                                   "offline_purity_total_bending",
                                                   100, -10.0, 10.0);
    offline_purity_passed_nlayer  = fs->make<TH1D>("offline_purity_passed_nlayer",
                                                   "offline_purity_passed_nlayer",
                                                   6, 0.5, 6.5);
    offline_purity_total_nlayer   = fs->make<TH1D>("offline_purity_total_nlayer",
                                                   "offline_purity_total_nlayer",
                                                   6, 0.5, 6.5);
    float pt_bin[25] = {0.0,1.0,2.0,3.0,4.0,5.0,10.0,15.0,20.0,25.0,30.0,35.0,40.0,45.0,50.0,
                         60.0,70.0,80.0,90.0,100.0,120.0,140.0,160.0,180.0,200.0};
    st_effi_passed_pt             = fs->make<TH1D>("st_effi_passed_pt",
                                                   "st_effi_passed_pt",
                                                   24, pt_bin);
    st_effi_total_pt              = fs->make<TH1D>("st_effi_total_pt",
                                                   "st_effi_total_pt",
                                                   24, pt_bin);
    st_effi_passed_eta            = fs->make<TH1D>("st_effi_passed_eta",
                                                   "st_effi_passed_eta",
                                                   8, 0.5, 8.5);
    st_effi_total_eta             = fs->make<TH1D>("st_effi_total_eta",
                                                   "st_effi_total_eta",
                                                   8, 0.5, 8.5);
    st_effi_passed_bending        = fs->make<TH1D>("st_effi_passed_bending",
                                                   "st_effi_passed_bending",
                                                   100, -10.0, 10.0);
    st_effi_total_bending         = fs->make<TH1D>("st_effi_total_bending",
                                                   "st_effi_total_bending",
                                                   100, -10.0, 10.0);
    st_effi_passed_nlayer         = fs->make<TH1D>("st_effi_passed_nlayer",
                                                   "st_effi_passed_nlayer",
                                                   6, 0.5, 6.5);
    st_effi_total_nlayer          = fs->make<TH1D>("st_effi_total_nlayer",
                                                   "st_effi_total_nlayer",
                                                   6, 0.5, 6.5);
    st_effi_mres                  = fs->make<TH1D>("st_effi_mres",
                                                   "st_effi_mres",
                                                   100, -10.0, 10.0);
    st_effi_sres                  = fs->make<TH1D>("st_effi_sres",
                                                   "st_effi_sres",
                                                   100, -1.0, 1.0);
    st_purity_passed_eta          = fs->make<TH1D>("st_purity_passed_eta",
                                                   "st_purity_passed_eta",
                                                   8, 0.5, 8.5);
    st_purity_total_eta           = fs->make<TH1D>("st_purity_total_eta",
                                                   "st_purity_total_eta",
                                                   8, 0.5, 8.5);
    st_purity_passed_bending      = fs->make<TH1D>("st_purity_passed_bending",
                                                   "st_purity_passed_bending",
                                                   100, -10.0, 10.0);
    st_purity_total_bending       = fs->make<TH1D>("st_purity_total_bending",
                                                   "st_purity_total_bending",
                                                   100, -10.0, 10.0);
    st_purity_passed_nlayer       = fs->make<TH1D>("st_purity_passed_nlayer",
                                                   "st_purity_passed_nlayer",
                                                   6, 0.5, 6.5);
    st_purity_total_nlayer        = fs->make<TH1D>("st_purity_total_nlayer",
                                                   "st_purity_total_nlayer",
                                                   6, 0.5, 6.5);

    // Set config
    config.num_outputs = 10;
    config.cross_part_seg_width = 4;
    config.ghost_width = 10;
    config.max_span = 37;
    config.num_or = 2; 
};
void ME0StubAnalyzer::endRun(const edm::Run& run, const edm::EventSetup& iSetup) {
    overall_performance->SetBinContent(1,n_offline_effi_total);
    overall_performance->SetBinContent(2,n_offline_effi_passed);
    overall_performance->SetBinContent(3,n_offline_purity_total);
    overall_performance->SetBinContent(4,n_offline_purity_passed);
    overall_performance->SetBinContent(5,n_st_effi_total);
    overall_performance->SetBinContent(6,n_st_effi_passed);
    overall_performance->SetBinContent(7,n_st_purity_total);
    overall_performance->SetBinContent(8,n_st_purity_passed);

    double offline_efficiency = (double)n_offline_effi_passed  /(double)n_offline_effi_total;
    double offline_purity     = (double)n_offline_purity_passed/(double)n_offline_purity_total;
    double st_efficiency      = (double)n_st_effi_passed       /(double)n_st_effi_total;
    double st_purity          = (double)n_st_purity_passed     /(double)n_st_purity_total;

    // std::cout << n_offline_effi_total << " " << n_offline_effi_passed << std::endl;
    // std::cout << n_offline_purity_total << " " << n_offline_purity_passed << std::endl;
    // std::cout << n_st_effi_total << " " << n_st_effi_passed << std::endl;
    // std::cout << n_st_purity_total << " " << n_st_purity_passed << std::endl;

    std::cout << "Overall efficiency w.r.t offline segments = " << offline_efficiency << std::endl;
    std::cout << "Overall purity w.r.t offline segments     = " << offline_purity     << std::endl;
    std::cout << "Overall efficiency w.r.t sim tracks       = " << st_efficiency      << std::endl;
    std::cout << "Overall purity w.r.t sim tracks           = " << st_purity          << std::endl;
}

DEFINE_FWK_MODULE(ME0StubAnalyzer);
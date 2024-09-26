#include "ME0StubFinder/ME0StubFinder/plugins/ME0StubBuilder.h"
#include "DataFormats/MuonDetId/interface/GEMDetId.h"
#include "DataFormats/GEMDigi/interface/GEMDigi.h"
#include "Geometry/GEMGeometry/interface/GEMGeometry.h"
#include "Geometry/GEMGeometry/interface/GEMEtaPartition.h"
#include "ME0StubFinder/ME0StubFinder/interface/ChamberBeh.h"

#include "FWCore/Utilities/interface/Exception.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

typedef std::vector<std::vector<UInt192>> ME0ChamberData;

ME0StubBuilder::ME0StubBuilder(const edm::ParameterSet& ps) {}
ME0StubBuilder::~ME0StubBuilder() {}

void ME0StubBuilder::fillDescription(edm::ParameterSetDescription& desc) {
//   desc.add<bool>("enableGE0", true);
//   desc.add<bool>("enableGE12", false);
//   desc.add<std::string>("ge0_name", "GE0SegAlgoRU");
//   desc.add<std::string>("algo_name", "GEMSegmentAlgorithm");

//   edm::ParameterSetDescription ge0AlgoConfigDesc;
//   ge0AlgoConfigDesc.add<bool>("allowWideSegments", true);
//   ge0AlgoConfigDesc.add<bool>("doCollisions", true);
//   ge0AlgoConfigDesc.add<double>("maxChi2Additional", 100);
//   ge0AlgoConfigDesc.add<double>("maxChi2Prune", 50);
//   ge0AlgoConfigDesc.add<double>("maxChi2GoodSeg", 50);
//   ge0AlgoConfigDesc.add<double>("maxPhiSeeds", 0.001096605744)->setComment("Assuming 384 strips");
//   ge0AlgoConfigDesc.add<double>("maxPhiAdditional", 0.001096605744)->setComment("Assuming 384 strips");
//   ge0AlgoConfigDesc.add<double>("maxETASeeds", 0.1)->setComment("Assuming 8 eta partitions");
//   ge0AlgoConfigDesc.add<double>("maxTOFDiff", 25);
//   ge0AlgoConfigDesc.add<bool>("requireCentralBX", true)
//       ->setComment("require that a majority of hits come from central BX");
//   ge0AlgoConfigDesc.add<unsigned int>("minNumberOfHits", 4);
//   ge0AlgoConfigDesc.add<unsigned int>("maxNumberOfHits", 300);
//   ge0AlgoConfigDesc.add<unsigned int>("maxNumberOfHitsPerLayer", 100);
//   desc.add<edm::ParameterSetDescription>("ge0_pset", ge0AlgoConfigDesc);

//   edm::ParameterSetDescription recAlgoConfigDesc;
//   recAlgoConfigDesc.addUntracked<bool>("GEMDebug", false);
//   recAlgoConfigDesc.add<unsigned int>("minHitsPerSegment", 2);
//   recAlgoConfigDesc.add<bool>("preClustering", true)
//       ->setComment("False => all hits in chamber are given to the fitter");
//   recAlgoConfigDesc.add<double>("dXclusBoxMax", 1)->setComment("Clstr Hit dPhi");
//   recAlgoConfigDesc.add<double>("dYclusBoxMax", 5)->setComment("Clstr Hit dEta");
//   recAlgoConfigDesc.add<bool>("preClusteringUseChaining", true)
//       ->setComment("True ==> use Chaining() , False ==> use Clustering() Fnct");
//   recAlgoConfigDesc.add<double>("dPhiChainBoxMax", .02)->setComment("Chain Hit dPhi");
//   recAlgoConfigDesc.add<double>("dEtaChainBoxMax", .05)->setComment("Chain Hit dEta");
//   recAlgoConfigDesc.add<int>("maxRecHitsInCluster", 4)->setComment("Does 4 make sense here?");
//   recAlgoConfigDesc.add<bool>("clusterOnlySameBXRecHits", true)
//       ->setComment("only working for (preClustering && preClusteringUseChaining)");
//   desc.add<edm::ParameterSetDescription>("algo_pset", recAlgoConfigDesc);
}

void ME0StubBuilder::build(const GEMDigiCollection* digis, ME0StubCollection& oc) {
    // edm::LogVerbatim("ME0StubBuilder") << "[ME0StubBuilder::build] Total number of rechits in this event: "
    //                                         << digis->size();
    
    // Let's define the ensemble of GEM devices having the same region, chambers number (phi)
    // different eta partitions and different layers are allowed

    Config config;
    
    std::map<uint32_t, ME0ChamberData> DataMap;
    // Loop on the GEM rechit and select the different GEM Ensemble
    for (auto it = digis->begin(); it != digis->end(); ++it) {
        GEMDetId gemid((*it).first);
        if (gemid.station() != 0) continue;

        uint32_t rawIdMask = 0x1003FFF;
        uint32_t rawId = gemid.rawId() | rawIdMask;

        if (DataMap[rawId].empty()) {
            DataMap[rawId] 
                = std::vector<std::vector<UInt192>>(8,{UInt192(0),UInt192(0),UInt192(0),UInt192(0),UInt192(0),UInt192(0)});
        }
        int layer = gemid.layer();
        int ieta = gemid.ieta();
        for (auto digi = ((*it).second).first; digi != ((*it).second).second; ++digi) {
            int strip = (*digi).strip();
            (DataMap[rawId].at(ieta-1)).at(layer-1) |= (UInt192(1) << (strip/2));
        }
    }

    // Find stub per chamber using DataMap
    for (const auto& data_pair : DataMap) {
        uint32_t rawId = data_pair.first;
        auto data = data_pair.second;

        bool isNoneZero = false;
        for (const auto& etaData : data) {
            if (etaData[0].any()) isNoneZero = true; 
        }
        if (!isNoneZero) continue;

        GEMDetId id(rawId);

        std::vector<ME0Stub> SegList = process_chamber(data, config);

        std::vector<ME0Stub> SegList_processed;
        
        for (ME0Stub& seg : SegList) {
            if (seg.id == 0) continue;
            seg.fit(config.max_span);
            if ((seg.partition % 2) != 0) seg.partition = (seg.partition / 2) + 1;
            else seg.partition = (seg.partition / 2);

            SegList_processed.push_back(seg);
        }

        oc.put(id, SegList_processed.begin(), SegList_processed.end());
    }
}
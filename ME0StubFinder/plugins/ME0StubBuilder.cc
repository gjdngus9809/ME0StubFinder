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

void ME0StubBuilder::fillDescription(edm::ParameterSetDescription& desc) {}

void ME0StubBuilder::build(const GEMDigiCollection* digis, ME0StubCollection& oc) {
    // edm::LogVerbatim("ME0StubBuilder") << "[ME0StubBuilder::build] Total number of rechits in this event: "
    //                                         << digis->size();
    
    // Let's define the ensemble of GEM devices having the same region, chambers number (phi)
    // different eta partitions and different layers are allowed

    Config config;
    config.num_outputs=10;
    config.cross_part_seg_width=4;
    config.ghost_width=10;
    
    std::map<uint32_t, ME0ChamberData> DataMap;
    // Loop on the GEM rechit and select the different GEM Ensemble
    for (auto it = digis->begin(); it != digis->end(); ++it) {
        GEMDetId gemid((*it).first);
        if (gemid.station() != 0) continue;

        uint32_t gemRawId = (gemid.superChamberId()).rawId();

        if (DataMap[gemRawId].empty()) {
            DataMap[gemRawId] 
                = std::vector<std::vector<UInt192>>(8,{UInt192(0),UInt192(0),UInt192(0),UInt192(0),UInt192(0),UInt192(0)});
        }
        int layer = gemid.layer();
        int ieta = gemid.ieta();
        for (auto digi = ((*it).second).first; digi != ((*it).second).second; ++digi) {
            int strip = (*digi).strip();
            (DataMap[gemRawId].at(ieta-1)).at(layer-1) |= (UInt192(1) << (strip/2));
        }
    }

    // Find stub per chamber using DataMap
    for (const auto& data_pair : DataMap) {
        uint32_t rawId = data_pair.first;
        auto data = data_pair.second;

        bool isNoneZero = false;
        for (const auto& etaData : data) {
            for (const auto& ly : etaData) {
                if (ly.any()) {
                    isNoneZero = true;
                    break;
                }
            }
            if (isNoneZero) break;
        }
        if (!isNoneZero) continue;

        GEMDetId id(rawId);

        std::vector<ME0Stub> SegList = process_chamber(data, config);

        std::vector<ME0Stub> SegList_processed;
        
        for (ME0Stub& seg : SegList) {
            if (seg.PatternId() == 0) continue;
            seg.fit(config.max_span);
            if ((seg.EtaPartition() % 2) != 0) seg.SetEtaPartition(seg.EtaPartition()/2 + 1);
            else seg.SetEtaPartition(seg.EtaPartition()/2);

            SegList_processed.push_back(seg);
        }

        for (auto seg : SegList_processed) {
            if (seg.PatternId() != 0) {
                std::cout<<"region="<<id.region()<<", chamber="<<id.chamber()
                          <<", "<<seg<<std::endl;
            }
        }

        oc.put(id, SegList_processed.begin(), SegList_processed.end());
    }
}
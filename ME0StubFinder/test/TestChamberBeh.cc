// system include files
#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <regex>
#include <iostream>
#include <bitset>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "ME0StubFinder/ME0StubFinder/interface/ChamberBeh.h"

typedef std::vector<std::vector<UInt192>> ME0ChamberData;
typedef std::vector<std::vector<std::vector<int>>> ME0ChamberBXData;

class TestChamberBeh : public edm::one::EDAnalyzer<edm::one::WatchRuns> {
public:
    explicit TestChamberBeh(const edm::ParameterSet &);
    ~TestChamberBeh();

private:
  virtual void beginJob() override;
  virtual void analyze(const edm::Event &, const edm::EventSetup &) override;
  virtual void endJob() override;

  virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
  virtual void endRun(edm::Run const&, edm::EventSetup const&) override;

private:
};

TestChamberBeh::TestChamberBeh(const edm::ParameterSet &iConfig) {}
TestChamberBeh::~TestChamberBeh() {}

void TestChamberBeh::analyze(const edm::Event &iEvent,
                        const edm::EventSetup &iSetup) {
    
    ME0ChamberData SingleSC 
            = std::vector<std::vector<UInt192>>(8,std::vector<UInt192>(6,UInt192(0)));
    ME0ChamberBXData bx_data
            = std::vector<std::vector<std::vector<int>>>(8,std::vector<std::vector<int>>(6,std::vector<int>(192,0)));

    SingleSC[0] = {(UInt192(0x0)),
                   (UInt192(0x0)),
                   (UInt192(0x0)),
                   (UInt192(0x0)),
                   (UInt192(0x0)),
                   (UInt192(0x0))};
    SingleSC[1] = {(UInt192(0x0)),
                   (UInt192(0x300000000000)<<128)|(UInt192(0x0000000000000000)<<64)|(UInt192(0x0000000000000000)),
                   (UInt192(0x0)),
                   (UInt192(0x0)),
                   (UInt192(0x0)),
                   (UInt192(0x0))};
    SingleSC[2] = {(UInt192(0x0)),
                   (UInt192(0x0)),
                   (UInt192(0x0)),
                   (UInt192(0x0)),
                   (UInt192(0x0)),
                   (UInt192(0x0))};
    SingleSC[3] = {(UInt192(0x0)),
                   (UInt192(0x0)),
                   (UInt192(0x0)),
                   (UInt192(0x30000000000000)),
                   (UInt192(0x1f)<<128)|(UInt192(0x8000000000000000)<<64)|(UInt192(0x0000000f00000000)),
                   (UInt192(0x7e00000000)<<128)|(UInt192(0x0000000000000000)<<64)|(UInt192(0x003c000000000000))};
    SingleSC[4] = {(UInt192(0x0)),
                   (UInt192(0x1d00000000000)<<64)|(UInt192(0x0000000000000018)),
                   (UInt192(0x0)),
                   (UInt192(0x7800000000)<<64)|(UInt192(0x0000000000078000)),
                   (UInt192(0x20000000000000)<<128)|(UInt192(0x0000000000000000)<<64)|(UInt192(0x00000f0000000000)),
                   (UInt192(0xf00000000)<<64)|(UInt192(0x0006000000000000))};
    SingleSC[5] = {(UInt192(0x1000000)),
                   (UInt192(0xc4000000000000)<<128)|(UInt192(0x0000000000000000)<<64)|(UInt192(0x0000080000000000)),
                   (UInt192(0x1e000000000)<<128)|(UInt192(0x0000000000008000)<<64)|(UInt192(0x000000000000000f)),
                   (UInt192(0xc0003800000000)),
                   (UInt192(0xc0000000000)<<128)|(UInt192(0x0000000000000000)<<64)|(UInt192(0x0000000000000000)),
                   (UInt192(0x600000000000)<<128)|(UInt192(0x00000f0000000080)<<64)|(UInt192(0x0007000000000000))};
    SingleSC[6] = {(UInt192(0x200000000000000)<<128)|(UInt192(0x03e0000000000000)<<64)|(UInt192(0x0000000000000007)),
                   (UInt192(0x33f0000)<<128)|(UInt192(0x0000000000000000)<<64)|(UInt192(0x078000000000f000)),
                   (UInt192(0x78380000000)<<128)|(UInt192(0x0000000000038000)<<64)|(UInt192(0x0000000000000000)),
                   (UInt192(0xe0000e000000700)<<128)|(UInt192(0x0000000000000000)<<64)|(UInt192(0x0000000001800000)),
                   (UInt192(0x18e0000000000)<<128)|(UInt192(0x0700000000000000)<<64)|(UInt192(0x0000000000000000)),
                   (UInt192(0x7bc3fc00000)<<128)|(UInt192(0x0000000000000000)<<64)|(UInt192(0x0000000000000300))};
    SingleSC[7] = {(UInt192(0xe1800000000c000)<<128)|(UInt192(0x000000000000c000)<<64)|(UInt192(0x3800007000000000)),
                   (UInt192(0x1e07ffe0000)<<128)|(UInt192(0x00000000001fff80)<<64)|(UInt192(0x000e000000000000)),
                   (UInt192(0xc00000003800000)<<128)|(UInt192(0x0000000000000000)<<64)|(UInt192(0x000003800c060000)),
                   (UInt192(0x41c70000000000)<<128)|(UInt192(0x0000000000380000)<<64)|(UInt192(0x0000000001c047ff)),
                   (UInt192(0x3f80000000)<<128)|(UInt192(0x0000000000718300)<<64)|(UInt192(0x0000000000000c00)),
                   (UInt192(0x3c0000000003)<<128)|(UInt192(0xf000000060319800)<<64)|(UInt192(0x0fffc00000000000))};
    // for (auto i : SingleSC) {
        // for (auto j : i) {
            // std::cout<<j.to_ullong()<<" ";
        // }
        // std::cout<<std::endl;
    // }
    // std::cout<<std::endl;
     
    Config config;
    config.num_outputs=10;
    config.cross_part_seg_width=4;
    config.ghost_width=10;
    config.ly_thresh_patid = {7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 5, 5, 5, 5, 5, 5, 4};
    config.ly_thresh_eta = {4, 5, 4, 5, 4, 5, 4, 5, 4, 5, 4, 5, 4, 5, 5};

    auto seglist0 = process_chamber(SingleSC,bx_data,config);
    // auto seglist1 = process_chamber(SingleSC,config);
    // auto seglist2 = process_chamber(SingleSC,config);
    // auto seglist3 = process_chamber(SingleSC,config);
    // auto seglist4 = process_chamber(SingleSC,config);
    // auto seglist5 = process_chamber(SingleSC,config);
    // auto seglist6 = process_chamber(SingleSC,config);
    // auto seglist7 = process_chamber(SingleSC,config);
    // auto seglist8 = process_chamber(SingleSC,config);
    // auto seglist9 = process_chamber(SingleSC,config);

    std::cout <<"Final"<< std::endl;
    for (auto seg : seglist0) {
        std::cout <<seg<< std::endl;
    }
}

void TestChamberBeh::beginJob() {}
void TestChamberBeh::endJob() {}
void TestChamberBeh::beginRun(const edm::Run& run, const edm::EventSetup& iSetup) {}
void TestChamberBeh::endRun(const edm::Run& run, const edm::EventSetup& iSetup) {}

DEFINE_FWK_MODULE(TestChamberBeh);
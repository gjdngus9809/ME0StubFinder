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
            = std::vector<std::vector<UInt192>>(8,std::vector<UInt192>(6));

    SingleSC[0] = {(UInt192(0x0)),
                   (UInt192(0x0)),
                   (UInt192(0x0)),
                   (UInt192(0x0)),
                   (UInt192(0x0)),
                   (UInt192(0x0))};
    SingleSC[1] = {(UInt192(0x0)),
                   (UInt192(0x0)),
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
                   (UInt192(0x1c7800000000)<<128)|(UInt192(0x0000000000000000)<<64)|(UInt192(0x0000000000000000)),
                   (UInt192(0x400000000)<<128)|(UInt192(0x0000000000000000)<<64)|(UInt192(0x0000000000000000)),
                   (UInt192(0x100000000000)<<128)|(UInt192(0x0000000000000000)<<64)|(UInt192(0x0000000000000000))};
    SingleSC[4] = {(UInt192(0x0)),
                   (UInt192(0x200000000000)<<128)|(UInt192(0x0000000000000000)<<64)|(UInt192(0x0000000000000000)),
                   (UInt192(0x1c00000000000000)<<128)|(UInt192(0x0000000000000000)<<64)|(UInt192(0x0000000000000000)),
                   (UInt192(0x7ce0000000000000)<<128)|(UInt192(0x0000000000000000)<<64)|(UInt192(0x0000000000000000)),
                   (UInt192(0xe3c0180000000000)<<128)|(UInt192(0x0000000000000000)<<64)|(UInt192(0x0000000000000000)),
                   (UInt192(0x60001ee000000000)<<128)|(UInt192(0x0000000000000000)<<64)|(UInt192(0x0000000000000000))};
    SingleSC[5] = {(UInt192(0x0)),
                   (UInt192(0xc180000018000000)<<128)|(UInt192(0x0000000000000000)<<64)|(UInt192(0x0000000000000000)),
                   (UInt192(0x2000000000)<<128)|(UInt192(0x0000000000000000)<<64)|(UInt192(0x0000000000000000)),
                   (UInt192(0x606000000000)<<128)|(UInt192(0x0000000000000000)<<64)|(UInt192(0x0000000000000000)),
                   (UInt192(0x0)),
                   (UInt192(0x8000000000000)<<128)|(UInt192(0x0000000000000070)<<64)|(UInt192(0x0000000000000000))};
    SingleSC[6] = {(UInt192(0x0)),
                   (UInt192(0x0)),
                   (UInt192(0x0)),
                   (UInt192(0x0)),
                   (UInt192(0x0)),
                   (UInt192(0x0))};
    SingleSC[7] = {(UInt192(0x0)),
                   (UInt192(0x0)),
                   (UInt192(0x0)),
                   (UInt192(0x0)),
                   (UInt192(0x0)),
                   (UInt192(0x0))};
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

    auto seglist0 = process_chamber(SingleSC,config);
    // auto seglist1 = process_chamber(SingleSC,config);
    // auto seglist2 = process_chamber(SingleSC,config);
    // auto seglist3 = process_chamber(SingleSC,config);
    // auto seglist4 = process_chamber(SingleSC,config);
    // auto seglist5 = process_chamber(SingleSC,config);
    // auto seglist6 = process_chamber(SingleSC,config);
    // auto seglist7 = process_chamber(SingleSC,config);
    // auto seglist8 = process_chamber(SingleSC,config);
    // auto seglist9 = process_chamber(SingleSC,config);

    std::cout << "Final" << std::endl;
    for (auto seg : seglist0) {
        std::cout << seg << std::endl;
    }
}

void TestChamberBeh::beginJob() {}
void TestChamberBeh::endJob() {}
void TestChamberBeh::beginRun(const edm::Run& run, const edm::EventSetup& iSetup) {}
void TestChamberBeh::endRun(const edm::Run& run, const edm::EventSetup& iSetup) {}

DEFINE_FWK_MODULE(TestChamberBeh);
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

    SingleSC[2] = {0b1110000000, 0b111000000, 0b11100000, 0b111000, 0b11100, 0b1110};
    // for (auto i : SingleSC) {
        // for (auto j : i) {
            // std::cout<<j.to_ullong()<<" ";
        // }
        // std::cout<<std::endl;
    // }
    // std::cout<<std::endl;
     
    Config config;
    config.ly_thresh = 6;
    config.max_span = 37;
    config.deghost_pre = true;

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

    std::cout << "partition / strip / patId / layer count" << std::endl;
    std::cout << "seg 0 : " << seglist0[0].partition << " " << seglist0[0].strip << " " << seglist0[0].id << " " << seglist0[0].lc << std::endl;
    std::cout << "seg 1 : " << seglist0[1].partition << " " << seglist0[1].strip << " " << seglist0[1].id << " " << seglist0[1].lc << std::endl;
    std::cout << "seg 2 : " << seglist0[2].partition << " " << seglist0[2].strip << " " << seglist0[2].id << " " << seglist0[2].lc << std::endl;
    std::cout << "seg 3 : " << seglist0[3].partition << " " << seglist0[3].strip << " " << seglist0[2].id << " " << seglist0[2].lc << std::endl;
}

void TestChamberBeh::beginJob() {}
void TestChamberBeh::endJob() {}
void TestChamberBeh::beginRun(const edm::Run& run, const edm::EventSetup& iSetup) {}
void TestChamberBeh::endRun(const edm::Run& run, const edm::EventSetup& iSetup) {}

DEFINE_FWK_MODULE(TestChamberBeh);
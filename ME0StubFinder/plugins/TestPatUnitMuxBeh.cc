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

#include "ME0StubFinder/ME0StubFinder/interface/PatUnitMuxBeh.h"

class TestPatUnitMuxBeh : public edm::one::EDAnalyzer<edm::one::WatchRuns> {
public:
    explicit TestPatUnitMuxBeh(const edm::ParameterSet &);
    ~TestPatUnitMuxBeh();

private:
  virtual void beginJob() override;
  virtual void analyze(const edm::Event &, const edm::EventSetup &) override;
  virtual void endJob() override;

  virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
  virtual void endRun(edm::Run const&, edm::EventSetup const&) override;

private:
};

TestPatUnitMuxBeh::TestPatUnitMuxBeh(const edm::ParameterSet &iConfig) {}
TestPatUnitMuxBeh::~TestPatUnitMuxBeh() {}

void TestPatUnitMuxBeh::analyze(const edm::Event &iEvent,
                        const edm::EventSetup &iSetup) {
    /*
	
	*/

    UInt192 u = 0b1000000000000000000;
    std::cout << std::bitset<64>(u.to_ullong()) << std::endl;
	uint64_t a;
	a = parse_data(UInt192(0b1000000000000000000), 10, 37);
    std::cout << std::bitset<64>(a) << std::endl;

    std::cout << (a == (uint64_t)0b100000000000000000000000000) << std::endl;
	
    a = parse_data(UInt192(0b1000000000000000000), 25, 37);
    std::cout << (a == (uint64_t)0b100000000000) << std::endl;

    std::vector<uint64_t> b;
    std::vector<uint64_t> expacted;
    std::vector<UInt192> data;
    bool same;
    data = {0b100000000000000000, 0b1000100000000000000, 0b1000000000000000000, 0b1000000000000000000, 0b1000000000000000000, 0b1000000000000000000};
    b = extract_data_window(data, 8, 37);
    expacted = {134217728, 285212672, 268435456, 268435456, 268435456, 268435456};
    same = true;
    for (int i=0; i<6; ++i) {
        if (b[i] != expacted[i]) 
            same = false;
    } 
    std::cout << same << std::endl;

    data = {0b100000000000000000, 0b1000100000000000000, 0b1000000000000000000, 0b1000000000000000000, 0b1000000000000000000, 0b1000000000000000000};
    b = extract_data_window(data, 20, 37);
    expacted = {32768, 69632, 65536, 65536, 65536, 65536};
    same = true;
    for (int i=0; i<6; ++i) {
        if (b[i] != expacted[i]) 
            same = false;
    } 
    std::cout << same << std::endl;
    
    data = {0b1, 0b1, 0b1, 0b1, 0b1, 0b1};

    Config config;
    config.ly_thresh = 6;
    config.max_span = 37;

    std::vector<Segment> mux = pat_mux(data, 0, config);
    std::cout << mux[0].id << " " << mux[0].lc << " " << mux[0].strip << std::endl;
    std::cout << mux[1].id << " " << mux[1].lc << " " << mux[1].strip << std::endl;
    std::cout << mux[2].id << " " << mux[2].lc << " " << mux[2].strip << std::endl;
    std::cout << mux[4].id << " " << mux[4].lc << " " << mux[4].strip << std::endl;

}

void TestPatUnitMuxBeh::beginJob() {}
void TestPatUnitMuxBeh::endJob() {}
void TestPatUnitMuxBeh::beginRun(const edm::Run& run, const edm::EventSetup& iSetup) {}
void TestPatUnitMuxBeh::endRun(const edm::Run& run, const edm::EventSetup& iSetup) {}

DEFINE_FWK_MODULE(TestPatUnitMuxBeh);
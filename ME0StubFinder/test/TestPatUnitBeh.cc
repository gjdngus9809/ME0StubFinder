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

#include "ME0StubFinder/ME0StubFinder/interface/PatUnitBeh.h"
#include "ME0StubFinder/ME0StubFinder/interface/Mask.h"

class TestPatUnitBeh : public edm::one::EDAnalyzer<edm::one::WatchRuns> {
public:
    explicit TestPatUnitBeh(const edm::ParameterSet &);
    ~TestPatUnitBeh();

private:
  virtual void beginJob() override;
  virtual void analyze(const edm::Event &, const edm::EventSetup &) override;
  virtual void endJob() override;

  virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
  virtual void endRun(edm::Run const&, edm::EventSetup const&) override;

private:
};

TestPatUnitBeh::TestPatUnitBeh(const edm::ParameterSet &iConfig) {}
TestPatUnitBeh::~TestPatUnitBeh() {}

void TestPatUnitBeh::analyze(const edm::Event &iEvent,
                        const edm::EventSetup &iSetup) {
    /*
    test of funtion pat_unit

    ME0Stub pat_unit(const std::vector<uint64_t>& data, 
                 unsigned int strip, 
                 unsigned int ly_tresh, 
                 int partition, 
                 int input_max_span, 
                 int num_or, 
                 bool light_hit_count,
                 bool verbose)
    */
    std::vector<uint64_t> data;
    ME0Stub seg;                       

    data = {0b1000000000000000000, 
            0b1000000000000000000, 
            0b1000000000000000000, 
            0b1000000000000000000,
            0b1000000000000000000, 
            0b1000000000000000000};
    seg = pat_unit(data, (unsigned int)0, (unsigned int)4, 0);
    std::cout << seg.PatternId() << " " << seg.LayerCount() << " / 19 6"<< std::endl; 
    
    data = {0b100000000000000000,
            0b100000000000000000,
            0b100000000000000000,
            0b100000000000000000,
            0b100000000000000000,
            0b100000000000000000};
    seg = pat_unit(data, (unsigned int)0, (unsigned int)4, 0);
    std::cout << seg.PatternId() << " " << seg.LayerCount() << " / 19 6"<< std::endl; 

    data = {0b000100000000000000000, 
            0b001000000000000000000, 
            0b010000000000000000000, 
            0b001000000000000000000, 
            0b100000000000000000000, 
            0b100000000000000000000};
    seg = pat_unit(data, (unsigned int)0, (unsigned int)4, 0);
    std::cout << seg.PatternId() << " " << seg.LayerCount() << " / 18 5"<< std::endl; 

    data = {0b000100000000000000000, 
            0b100000000000000000000, 
            0b100000000000000000000, 
            0b100000000000000000000, 
            0b100000000000000000000,
            0b100000000000000000000};
    seg = pat_unit(data, (unsigned int)0, (unsigned int)4, 0);
    std::cout << seg.PatternId() << " " << seg.LayerCount() << " / 0 0"<< std::endl; 

    /*
    test of funtion get_ly_mask

    Mask get_ly_mask(const patdef_t& ly_pat, int max_span)
    */
    std::vector<uint64_t> m;
    bool same;
    std::bitset<37> x, y;
    
    data = {0b11100000000000000000, 
            0b11100000000000000000, 
            0b11100000000000000000, 
            0b11100000000000000000, 
            0b11100000000000000000, 
            0b11100000000000000000};
    m = get_ly_mask(pat_straight,37).mask;
    same = true;
    for (int i=0; i<6; ++i) {
        if (m[i]!=data[i]) {same = false;}
        x = m[i]; y = data[i];
        std::cout << x << std::endl;
        std::cout << y << std::endl;
        std::cout << std::endl;
    }
    std::cout << same << std::endl;

    data = {0b1111000000000000000, 
            0b1110000000000000000,
            0b1100000000000000000,
            0b11000000000000000000,
            0b111000000000000000000, 
            0b1111000000000000000000};
    m = get_ly_mask(pat_l,37).mask;
    same = true;
    for (int i=0; i<6; ++i) {
        if (m[i]!=data[i]) {same = false;}
        x = m[i]; y = data[i];
        std::cout << x << std::endl;
        std::cout << y << std::endl;
        std::cout << std::endl;
    }
    std::cout << same << std::endl;

    data = {0b1111000000000000000000, 
            0b111000000000000000000, 
            0b11000000000000000000, 
            0b1100000000000000000, 
            0b1110000000000000000, 
            0b1111000000000000000};
    m = get_ly_mask(pat_r,37).mask;
    same = true;
    for (int i=0; i<6; ++i) {
        if (m[i]!=data[i]) {same = false;}
        x = m[i]; y = data[i];
        std::cout << x << std::endl;
        std::cout << y << std::endl;
        std::cout << std::endl;
    }
    std::cout << same << std::endl;
}


void TestPatUnitBeh::beginJob() {}
void TestPatUnitBeh::endJob() {}
void TestPatUnitBeh::beginRun(const edm::Run& run, const edm::EventSetup& iSetup) {}
void TestPatUnitBeh::endRun(const edm::Run& run, const edm::EventSetup& iSetup) {}

DEFINE_FWK_MODULE(TestPatUnitBeh);
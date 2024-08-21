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

#include "ME0StubFinder/ME0StubFinder/interface/Subfunc.h"

class TestSubFunctions : public edm::one::EDAnalyzer<edm::one::WatchRuns> {
public:
    explicit TestSubFunctions(const edm::ParameterSet &);
    ~TestSubFunctions();

private:
  virtual void beginJob() override;
  virtual void analyze(const edm::Event &, const edm::EventSetup &) override;
  virtual void endJob() override;

  virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
  virtual void endRun(edm::Run const&, edm::EventSetup const&) override;

private:
};

TestSubFunctions::TestSubFunctions(const edm::ParameterSet &iConfig) {}
TestSubFunctions::~TestSubFunctions() {}

void TestSubFunctions::analyze(const edm::Event &iEvent,
                        const edm::EventSetup &iSetup) {
    /*
    
    */
    std::vector<hi_lo_t> pat_ly;

    pat_ly = create_pat_ly(-0.4,0.4);
    for (hi_lo_t i : pat_ly) {
        std::cout << i.lo << " " << i.hi << std::endl;
    }
    std::cout << std::endl;

    pat_ly = create_pat_ly(0.2, 0.9);
    for (hi_lo_t i : pat_ly) {
        std::cout << i.lo << " " << i.hi << std::endl;
    }
    std::cout << std::endl;

    pat_ly = create_pat_ly(0.5, 1.2);
    for (hi_lo_t i : pat_ly) {
        std::cout << i.lo << " " << i.hi << std::endl;
    }

    std::vector<int> v{1,9,2,3,5,7,4,17};

    std::sort(v.begin(), v.end(), [](int a, int b){return a>b;});

    for(int i : v) std::cout << i << ' ';
    std::cout << std::endl;
}

void TestSubFunctions::beginJob() {}
void TestSubFunctions::endJob() {}
void TestSubFunctions::beginRun(const edm::Run& run, const edm::EventSetup& iSetup) {}
void TestSubFunctions::endRun(const edm::Run& run, const edm::EventSetup& iSetup) {}

DEFINE_FWK_MODULE(TestSubFunctions);
// system include files
#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <regex>
#include <iostream>

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

class PatUnitBehAnalyzer : public edm::one::EDAnalyzer<edm::one::WatchRuns> {
public:
    explicit PatUnitBehAnalyzer(const edm::ParameterSet &);
    ~PatUnitBehAnalyzer();

private:
  virtual void beginJob() override;
  virtual void analyze(const edm::Event &, const edm::EventSetup &) override;
  virtual void endJob() override;

  virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
  virtual void endRun(edm::Run const&, edm::EventSetup const&) override;

private:
    // int test_pat_unit();
    // int test_get_ly_mask();
};

PatUnitBehAnalyzer::PatUnitBehAnalyzer(const edm::ParameterSet &iConfig) {}
PatUnitBehAnalyzer::~PatUnitBehAnalyzer() {}

int test_pat_unit() {
    std::vector<uint64_t> data;
    data = {0b1000000000000000000, 
            0b1000000000000000000, 
            0b1000000000000000000, 
            0b1000000000000000000,
            0b1000000000000000000, 
            0b1000000000000000000};
    if (pat_unit(data, (unsigned int)0, (unsigned int)4, 0).id == 19) {return 1;}
    if (pat_unit(data, (unsigned int)0, (unsigned int)4, 0).lc == 6)  {return 2;}
    data = {0b100000000000000000,
            0b100000000000000000,
            0b100000000000000000,
            0b100000000000000000,
            0b100000000000000000,
            0b100000000000000000};
    if (pat_unit(data, (unsigned int)0, (unsigned int)4, 0).id == 19) {return 3;}
    if (pat_unit(data, (unsigned int)0, (unsigned int)4, 0).lc == 6)  {return 4;}
    data = {0b000100000000000000000, 
            0b001000000000000000000, 
            0b010000000000000000000, 
            0b001000000000000000000, 
            0b100000000000000000000, 
            0b100000000000000000000};
    if (pat_unit(data, (unsigned int)0, (unsigned int)4, 0).id == 18) {return 5;}
    if (pat_unit(data, (unsigned int)0, (unsigned int)4, 0).lc == 5)  {return 6;}
    data = {0b000100000000000000000, 
            0b100000000000000000000, 
            0b100000000000000000000, 
            0b100000000000000000000, 
            0b100000000000000000000,
            0b100000000000000000000};
    if (pat_unit(data, (unsigned int)0, (unsigned int)4, 0).id == 0) {return 7;}
    if (pat_unit(data, (unsigned int)0, (unsigned int)4, 0).lc == 0)  {return 8;}

    return 0;
}

int test_get_ly_mask() {
    std::vector<uint64_t> data;
    data = {0b11100000000000000000, 
            0b11100000000000000000, 
            0b11100000000000000000, 
            0b11100000000000000000, 
            0b11100000000000000000, 
            0b11100000000000000000};
    if (get_ly_mask(pat_straight,37).mask == data) {return 11;}
    data = {0b1111000000000000000, 
            0b1110000000000000000,
            0b1100000000000000000,
            0b11000000000000000000,
            0b111000000000000000000, 
            0b1111000000000000000000};
    if (get_ly_mask(pat_l,37).mask == data) {return 12;}
    data = {0b1111000000000000000000, 
            0b111000000000000000000, 
            0b11000000000000000000, 
            0b1100000000000000000, 
            0b1110000000000000000, 
            0b1111000000000000000};
    if (get_ly_mask(pat_r,37).mask == data) {return 13;}

    return 0;    
}

void PatUnitBehAnalyzer::analyze(const edm::Event &iEvent,
                        const edm::EventSetup &iSetup) {
    std::cout << test_pat_unit() << std::endl;
    std::cout << test_get_ly_mask() << std::endl;
}

void PatUnitBehAnalyzer::beginJob() {}
void PatUnitBehAnalyzer::endJob() {}
void PatUnitBehAnalyzer::beginRun(const edm::Run& run, const edm::EventSetup& iSetup) {}
void PatUnitBehAnalyzer::endRun(const edm::Run& run, const edm::EventSetup& iSetup) {}

DEFINE_FWK_MODULE(PatUnitBehAnalyzer);
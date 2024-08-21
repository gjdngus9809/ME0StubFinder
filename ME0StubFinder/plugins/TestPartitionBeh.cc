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

#include "ME0StubFinder/ME0StubFinder/interface/PartitionBeh.h"

class TestPartitionBeh : public edm::one::EDAnalyzer<edm::one::WatchRuns> {
public:
    explicit TestPartitionBeh(const edm::ParameterSet &);
    ~TestPartitionBeh();

private:
  virtual void beginJob() override;
  virtual void analyze(const edm::Event &, const edm::EventSetup &) override;
  virtual void endJob() override;

  virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
  virtual void endRun(edm::Run const&, edm::EventSetup const&) override;

private:
};

TestPartitionBeh::TestPartitionBeh(const edm::ParameterSet &iConfig) {}
TestPartitionBeh::~TestPartitionBeh() {}

void TestPartitionBeh::analyze(const edm::Event &iEvent,
                        const edm::EventSetup &iSetup) {
    /*
	
	*/
    
    std::vector<UInt192> data = {0b10000, 0b10000, 0b10000, 0b10000, 0b10000, 0b10000};
    Config config;
    config.ly_thresh = 6;
    config.max_span = 37;
    config.deghost_pre = true;

    std::vector<Segment> mux = process_partition(data, 0, config);
    std::cout << mux[0].id << " " << mux[0].lc << " " << mux[0].strip << std::endl;
    std::cout << mux[1].id << " " << mux[1].lc << " " << mux[1].strip << std::endl;
    std::cout << mux[2].id << " " << mux[2].lc << " " << mux[2].strip << std::endl;
    std::cout << mux[3].id << " " << mux[3].lc << " " << mux[3].strip << std::endl;

    Segment seg1(6, 6, 15, 0, 0);
    Segment seg2(6, 6, 10, 0, 0);
    Segment seg3(6, 6, 7,  0, 0);

    std::cout << is_ghost(seg1, seg1) << " false" << std::endl; //false
    std::cout << is_ghost(seg2, seg1) << " true" << std::endl; //true
    std::cout << is_ghost(seg3, seg1) << " true" << std::endl; //true
    std::cout << is_ghost(seg1, seg3) << " false" << std::endl; //false
    std::cout << std::endl;

    std::vector<Segment> segments;
    for (int i=0; i<24; ++i) {
        segments.push_back(Segment(6, 6, 15, i, 0));
    }

    std::vector<Segment> cancelled = cancel_edges(segments, 8, 2);

    // this should NOT really happen but right now it does...
    // no reason to cancel edges at the left  / right side of chamber
    std::cout << (cancelled[0].id == 0) << std::endl;
    std::cout << (cancelled[1].id == 0) << std::endl;

    // check first edge is cancelled correctly
    std::cout << (cancelled[5].id == 15) << std::endl;
    std::cout << (cancelled[6].id == 0) << std::endl;
    std::cout << (cancelled[7].id == 0) << std::endl;
    std::cout << (cancelled[8].id == 0) << std::endl;
    std::cout << (cancelled[9].id == 0) << std::endl;
    std::cout << (cancelled[10].id == 15) << std::endl;

    // check second edge is cancelled correctly
    std::cout << (cancelled[13].id == 15) << std::endl;
    std::cout << (cancelled[14].id == 0) << std::endl;
    std::cout << (cancelled[15].id == 0) << std::endl;
    std::cout << (cancelled[16].id == 0) << std::endl;
    std::cout << (cancelled[17].id == 0) << std::endl;
    std::cout << (cancelled[18].id == 15) << std::endl;
}

void TestPartitionBeh::beginJob() {}
void TestPartitionBeh::endJob() {}
void TestPartitionBeh::beginRun(const edm::Run& run, const edm::EventSetup& iSetup) {}
void TestPartitionBeh::endRun(const edm::Run& run, const edm::EventSetup& iSetup) {}

DEFINE_FWK_MODULE(TestPartitionBeh);
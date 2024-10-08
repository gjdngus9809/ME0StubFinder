/** \class ME0StubProducer derived by CSCSegmentProducer 
 * Produces a collection of ME0Stub's in ME0. 
 *
 * \author Woohyeon Heo
 */

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/stream/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/Utilities/interface/ESGetToken.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/ParameterSet/interface/ConfigurationDescriptions.h"
#include "FWCore/ParameterSet/interface/ParameterSetDescription.h"

#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/GEMDigi/interface/GEMDigiCollection.h"
#include "DataFormats/GEMRecHit/interface/ME0StubCollection.h"
#include "DataFormats/GEMRecHit/interface/ME0Stub.h"

// #include "RecoLocalMuon/GEMSegment/plugins/GEMSegmentBuilder.h"
#include "ME0StubFinder/ME0StubFinder/plugins/ME0StubBuilder.h"
#include "Geometry/Records/interface/MuonGeometryRecord.h"

class ME0StubProducer : public edm::stream::EDProducer<> {
public:
  /// Constructor
  explicit ME0StubProducer(const edm::ParameterSet&);
  /// Destructor
  ~ME0StubProducer() override {}
  /// Produce the ME0Stub collection
  void produce(edm::Event&, const edm::EventSetup&) override;

  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

private:
  int iev;  // events through
  edm::EDGetTokenT<GEMDigiCollection> theGEMDigiToken;
  std::unique_ptr<ME0StubBuilder> segmentBuilder_;
  edm::ESGetToken<GEMGeometry, MuonGeometryRecord> gemGeomToken_;
};

ME0StubProducer::ME0StubProducer(const edm::ParameterSet& ps) : iev(0) {
  theGEMDigiToken = consumes<GEMDigiCollection>(ps.getParameter<edm::InputTag>("gemDigiLabel"));
  segmentBuilder_ = std::make_unique<ME0StubBuilder>(ps);  // pass on the Parameter Set
  gemGeomToken_ = esConsumes<GEMGeometry, MuonGeometryRecord>();
  // register what this produces
  produces<ME0StubCollection>();
}

void ME0StubProducer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  edm::ParameterSetDescription desc;
  desc.add<edm::InputTag>("gemDigiLabel", edm::InputTag("gemDigis"));
  ME0StubBuilder::fillDescription(desc);
  descriptions.add("me0Stubs", desc);
}

void ME0StubProducer::produce(edm::Event& ev, const edm::EventSetup& setup) {
  LogDebug("ME0StubProducer") << "start producing segments for " << ++iev << "th event with GEM data";

  // get the collection of GEMDigi
  edm::Handle<GEMDigiCollection> gemDigis;
  ev.getByToken(theGEMDigiToken, gemDigis);

  // create empty collection of Segments
  auto oc = std::make_unique<ME0StubCollection>();

  // fill the collection
  segmentBuilder_->build(gemDigis.product(), *oc);  //@@ FILL oc

  // put collection in event
  ev.put(std::move(oc));
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(ME0StubProducer);
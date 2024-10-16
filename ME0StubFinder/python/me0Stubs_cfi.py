import FWCore.ParameterSet.Config as cms

me0Stubs = cms.EDProducer("ME0StubProducer",
    PileUp = cms.int32(200),
    gemDigiLabel = cms.InputTag("simMuonGEMDigis"),
    # gemDigiLabel = cms.InputTag("muonGEMDigis", "simMuonGEMDigis"),
    # std::vector<edm::ParameterSet>
)
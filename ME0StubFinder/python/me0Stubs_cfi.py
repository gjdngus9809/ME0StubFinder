import FWCore.ParameterSet.Config as cms

me0Stubs = cms.EDProducer("ME0StubProducer",
    # Define input
    gemDigiLabel = cms.InputTag("simMuonGEMDigis"),
    # gemDigiLabel = cms.InputTag("muonGEMDigis", "simMuonGEMDigis"),
    # std::vector<edm::ParameterSet>
)
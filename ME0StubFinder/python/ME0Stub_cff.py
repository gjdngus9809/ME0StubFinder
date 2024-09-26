import FWCore.ParameterSet.Config as cms

me0Segments = cms.EDProducer("ME0StubProducer",
    # Define input
    gemDigiLabel = cms.InputTag("simMuonGEMDigis"),
    # Choice of the building algo: 1 Average, 2 RU, ...
    # std::vector<edm::ParameterSet>
)
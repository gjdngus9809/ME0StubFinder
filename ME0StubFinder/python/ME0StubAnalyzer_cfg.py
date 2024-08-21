import FWCore.ParameterSet.Config as cms

process = cms.Process("ME0")

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
#process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.Geometry.GeometryExtended2026D88Reco_cff')
process.load('Configuration.Geometry.GeometryExtended2026D88_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.RawToDigi_cff')
process.load('Configuration.StandardSequences.Reconstruction_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

import FWCore.ParameterSet.VarParsing as VarParsing
options = VarParsing.VarParsing('analysis')

options.maxEvents = -1
options.inputFiles = "step2.root"
options.outputFile = "output.root"
options.parseArguments()

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(options.maxEvents),
    output = cms.optional.untracked.allowed(cms.int32,cms.PSet)
)

# Input source
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring('file:'+options.inputFiles[0]),
#    inputCommands = cms.untracked.vstring(
#      "drop *",
#      "keep *_simMuonGEMDigis__*"
#    ),
    secondaryFileNames = cms.untracked.vstring()
)

process.options = cms.untracked.PSet(
    # FailPath = cms.untracked.vstring(),
    IgnoreCompletely = cms.untracked.vstring(),
    Rethrow = cms.untracked.vstring(),
    # SkipEvent = cms.untracked.vstring(),
    accelerators = cms.untracked.vstring('*'),
    allowUnscheduled = cms.obsolete.untracked.bool,
    canDeleteEarly = cms.untracked.vstring(),
    deleteNonConsumedUnscheduledModules = cms.untracked.bool(True),
    dumpOptions = cms.untracked.bool(False),
    emptyRunLumiMode = cms.obsolete.untracked.string,
    eventSetup = cms.untracked.PSet(
        forceNumberOfConcurrentIOVs = cms.untracked.PSet(
            allowAnyLabel_=cms.required.untracked.uint32
        ),
        numberOfConcurrentIOVs = cms.untracked.uint32(0)
    ),
    fileMode = cms.untracked.string('FULLMERGE'),
    forceEventSetupCacheClearOnNewRun = cms.untracked.bool(False),
    holdsReferencesToDeleteEarly = cms.untracked.VPSet(),
    makeTriggerResults = cms.obsolete.untracked.bool,
    modulesToIgnoreForDeleteEarly = cms.untracked.vstring(),
    numberOfConcurrentLuminosityBlocks = cms.untracked.uint32(0),
    numberOfConcurrentRuns = cms.untracked.uint32(1),
    numberOfStreams = cms.untracked.uint32(0),
    numberOfThreads = cms.untracked.uint32(1),
    printDependencies = cms.untracked.bool(False),
    sizeOfStackForThreadsInKB = cms.optional.untracked.uint32,
    throwIfIllegalParameter = cms.untracked.bool(True),
    wantSummary = cms.untracked.bool(False)
)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('step3 nevts:10'),
    name = cms.untracked.string('Applications'),
    version = cms.untracked.string('$Revision: 1.19 $')
)

process.load("CommonTools.UtilAlgos.TFileService_cfi")
process.TFileService = cms.Service("TFileService",
    fileName = cms.string(options.outputFile)
)
process.ME0StubAnalyzer = cms.EDAnalyzer('ME0StubAnalyzer',
                                        gemSimTrackLabel = cms.InputTag("g4SimHits"),
                                        gemSimHitLabel = cms.InputTag("g4SimHits", "MuonGEMHits"),
                                        # gemDigiLabel = cms.InputTag("simMuonGEMDigis"),
                                        # gemLinkLabel = cms.InputTag("simMuonGEMDigis", "GEM"),
                                        gemRecHitLabel = cms.InputTag("gemRecHits"),
                                        gemSegmentLabel = cms.InputTag("gemSegments"),
                                       )
# Output definition
#process.output = cms.OutputModule("PoolOutputModule",
#    fileName = cms.untracked.string('file:step2.root'),
#    outputCommands=cms.untracked.vstring(
#        'drop *',
#        'keep *_simMuonGEMDigis__*'
#    ),
#    splitLevel = cms.untracked.int32(0)
#)

# Additional output definition

# Other statements
#process.mix.digitizers = cms.PSet(process.theDigitizersValid)
#from Configuration.AlCa.GlobalTag import GlobalTag
#process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:phase1_2023_realistic', '')

# Path and EndPath definitions
#process.raw2digi_step = cms.Path(process.muonGEMDigis*process.tcdsDigis)
process.gemRecHits.gemDigiLabel = cms.InputTag('simMuonGEMDigis')
process.reconstruction_step = cms.Path(process.gemRecHits)
process.segments_step = cms.Path(process.gemSegments)
process.analysis_step = cms.Path(process.ME0StubAnalyzer)
process.endjob_step = cms.EndPath(process.endOfProcess)

process.schedule = cms.Schedule(process.reconstruction_step,
                                process.segments_step,
                                process.analysis_step,
                                process.endjob_step)

from PhysicsTools.PatAlgos.tools.helpers import associatePatAlgosToolsTask
associatePatAlgosToolsTask(process)

# customisation of the process.

# Automatic addition of the customisation function from HLTrigger.Configuration.customizeHLTforMC
# from HLTrigger.Configuration.customizeHLTforMC import customizeHLTforMC 

#call to customisation function customizeHLTforMC imported from HLTrigger.Configuration.customizeHLTforMC
# process = customizeHLTforMC(process)

# End of customisation functions


# Customisation from command line
from FWCore.Modules.logErrorHarvester_cff import customiseLogErrorHarvesterUsingOutputCommands
process = customiseLogErrorHarvesterUsingOutputCommands(process)

# Add early deletion of temporary data products to reduce peak memory need
from Configuration.StandardSequences.earlyDeleteSettings_cff import customiseEarlyDelete
process = customiseEarlyDelete(process)
# End adding early deletion

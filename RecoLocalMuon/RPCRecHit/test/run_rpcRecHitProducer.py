import FWCore.ParameterSet.Config as cms

process = cms.Process('ReDoRecHit')

#process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = "106X_upgrade2018_realistic_v4"

process.maxEvents = cms.untracked.PSet(
                        input = cms.untracked.int32(-1),
                    )
process.load('Configuration.Geometry.GeometryExtended2023D38Reco_cff')
process.load('Configuration.Geometry.GeometryExtended2023D38_cff')

#from RecoLocalMuon.RPCRecHit.rpcRecHits_cfi import rpcRecHits

process.load("Configuration.StandardSequences.MagneticField_cff")

process.load('RecoLocalMuon.Configuration.RecoLocalMuon_cff')
process.dt1DRecHits.dtDigiLabel = cms.InputTag('simMuonDTDigis')
process.rpcRecHits.rpcDigiLabel = cms.InputTag('simMuonRPCDigis')
process.csc2DRecHits.wireDigiTag = cms.InputTag("simMuonCSCDigis","MuonCSCWireDigi")
process.csc2DRecHits.stripDigiTag = cms.InputTag("simMuonCSCDigis","MuonCSCStripDigi")


process.rpcRecHits = cms.EDProducer("RPCRecHitProducer",
               recAlgoConfig = cms.PSet(
                                 iRPCConfig = cms.PSet( # iRPC Algorithm
                                   useAlgorithm = cms.bool(False), # useIRPCAlgorithm: if true - use iRPC Algorithm;
                                   returnOnlyAND = cms.bool(True), # returnOnlyAND: if true algorithm will return only associated clusters;
                                   thrTimeHR = cms.double(2), # [ns] thrTimeHR: threshold for high radius clustering;
                                   thrTimeLR = cms.double(2), # [ns] thrTimeLR: threshold for low radius clustering;
                                   thrDeltaTimeMin = cms.double(-30), # [ns] thrDeltaTimeMin: min delta time threshold for association clusters between HR and LR;
                                   thrDeltaTimeMax = cms.double(30), # [ns] thrDeltaTimeMax: max delta time threshold for association clusters between HR and LR;
                                   signalSpeed = cms.double(19.786302) # [cm/ns] signalSpeed: speed of signal inside strip.
                                 ),
                               ),
               recAlgo = cms.string('RPCRecHitStandardAlgo'),
               rpcDigiLabel = cms.InputTag('simMuonRPCDigis'),
               maskSource = cms.string('File'),
               maskvecfile = cms.FileInPath('RecoLocalMuon/RPCRecHit/data/RPCMaskVec.dat'),
               deadSource = cms.string('File'),
               deadvecfile = cms.FileInPath('RecoLocalMuon/RPCRecHit/data/RPCDeadVec.dat')
             )

# Input source
process.source = cms.Source('PoolSource',
                  fileNames = cms.untracked.vstring('file:/eos/cms/store/group/dpg_rpc/comm_rpc/UpgradePhaseII/iRPCClustering/SingleMu/reco_iRPConeRollSingleMu100_200k_v2/190810_102015/0000/step3_1.root'
#'/store/relval/CMSSW_10_4_0_mtd5/RelValSingleMuFlatPt_0p7to10_pythia8/GEN-SIM-DIGI-RAW/PU25ns_103X_upgrade2023_realistic_v2_2023D35PU200-v1/20000/FB71652F-7303-DF45-BECB-D5F58A9700FD.root'
#'/store/relval/CMSSW_10_4_0_pre2/RelValSingleMuPt2to100_pythia8/GEN-SIM-DIGI-RAW/103X_upgrade2023_realistic_v2_2023D21noPU-v1/20000/FB6F50C4-27E3-8542-929F-6147CFEDA674.root'

#'/store/relval/CMSSW_10_4_0_mtd5/RelValSingleMuFlatPt_0p7to10_pythia8/GEN-SIM-RECO/PU25ns_103X_upgrade2023_realistic_v2_2023D35PU200-v1/20000/FDF42AF3-0213-1341-84B7-D7734E4D7406.root'

)
                 )

# Output
process.out = cms.OutputModule("PoolOutputModule",
                fileName =
                cms.untracked.string('./MC_RPC_RecHit' + '.root'),
                outputCommands = cms.untracked.vstring(
                    'drop *_*_*_*',
                    'keep *_standAloneMuons_*_*',
                    'keep *RPC*_*_*_*',
                    'keep *_csc*_*_*',
                    'keep *_dt*_*_*',
                    'keep *_gem*_*_*',
                    'keep *_me0*_*_*'
)
              )
process.p = cms.Path(process.rpcRecHits )
process.e = cms.EndPath(process.out)

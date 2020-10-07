from WMCore.Configuration import Configuration

config = Configuration()
#General section: In this section, the user specifies generic parameters about the request (e.g. request name). 
config.section_('General')
config.General.requestName ='crab_notimetime1p56_29Sep'


config.General.workArea = 'crab_project_29Sep'
config.General.transferOutputs = True
config.General.transferLogs = False

#JobType section: This section aims to contain all the parameters of the user job type and related configurables (e.g. CMSSW parameter-set configuration file, additional input files, etc.). 
config.section_('JobType')
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'run_rpcRecHitProducer.py'

config.JobType.allowUndistributedCMSSW = True

config.section_('Data')
config.Data.inputDataset = '/RelValSingleMuFlatPt_0p7to10_pythia8/CMSSW_10_4_0_mtd5-PU25ns_103X_upgrade2023_realistic_v2_2023D35PU200-v1/GEN-SIM-RECO'

config.Data.inputDBS = 'global'
config.Data.splitting = 'FileBased'

config.Data.unitsPerJob = 1

config.Data.publication = False
config.JobType.maxMemoryMB = 5000
#config.Data.allowNonValidInputDataset = True

config.section_("Site")
config.Site.storageSite = 'T2_CH_CERN'
#config.Site.whitelist = ['T2_CH_CERN']
config.Data.outLFNDirBase = '/store/group/dpg_rpc/comm_rpc/Run-II/TriggerStudies/'









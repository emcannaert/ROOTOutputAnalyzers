from CRABClient.UserUtilities import config
config = config()
config.General.requestName = 'MC_prod_Suu4TeV_chi1TeV_ALL_DECAYS_MINIAOD_0001'
config.General.workArea = '/uscms_data/d3/cannaert/UL2018_genproduction/totalProcess/Suu4TeV_chi1TeV/CMSSW_10_6_20//src/crab_projects'
config.General.transferOutputs = True
config.JobType.allowUndistributedCMSSW = True
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = '/uscms_data/d3/cannaert/UL2018_genproduction/totalProcess/Suu4TeV_chi1TeV/CMSSW_10_6_20//src/B2G-RunIISummer20UL18MiniAODv2-00001_1_cfg.py'
#config.JobType.maxMemoryMB = 4000
config.Data.inputDataset = '/SuuToChiChi/ecannaer-B2G-RunIISummer20UL18p_Suu4TeV_chi1TeV_ALLDECAYS_TuneCP5_13TeV-pythia8_RECO-30c2008a2fc4ea0206d76ce8a5759bfe/USER'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1
config.Data.totalUnits = -1
config.Data.publication = True
config.Data.inputDBS = 'phys03'
config.Data.publishDBS = 'phys03'
config.Data.outputDatasetTag = 'B2G-RunIISummer20UL18p_Suu4TeV_chi1TeV_ALLDECAYS_TuneCP5_13TeV-pythia8_MINIAOD'
config.Site.storageSite = 'T3_US_FNALLPC'

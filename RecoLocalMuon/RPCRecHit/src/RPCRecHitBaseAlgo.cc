/*
 *  See header file for a description of this class.
 *
 *  \author M. Maggi -- INFN Bari
 */

#include "RecoLocalMuon/RPCRecHit/interface/RPCRecHitBaseAlgo.h"
#include "RecoLocalMuon/RPCRecHit/src/RPCClusterContainer.h"
#include "RecoLocalMuon/RPCRecHit/src/RPCCluster.h"
#include "RecoLocalMuon/RPCRecHit/src/RPCClusterizer.h"
#include "RecoLocalMuon/RPCRecHit/src/RPCClusterizerwithtime.h"
#include "RecoLocalMuon/RPCRecHit/src/RPCMaskReClusterizer.h"

RPCRecHitBaseAlgo::RPCRecHitBaseAlgo(const edm::ParameterSet& config) {
  //  theSync = RPCTTrigSyncFactory::get()->create(config.getParameter<string>("tTrigMode"),
  //config.getParameter<ParameterSet>("tTrigModeConfig"));
}

// Build all hits in the range associated to the layerId, at the 1st step.
edm::OwnVector<RPCRecHit> RPCRecHitBaseAlgo::reconstruct(const RPCRoll& roll,
                                                         const RPCDetId& rpcId,
                                                         const RPCDigiCollection::Range& digiRange,
                                                         const RollMask& mask) {
  edm::OwnVector<RPCRecHit> result;
  edm::OwnVector<RPCRecHit> hits2;

  bool notime=true; 
  if (notime==true){  
//  edm::OwnVector<RPCRecHit> hits2;
  RPCClusterizer clizer;
  RPCClusterContainer tcls = clizer.doAction(digiRange);
  RPCMaskReClusterizer mrclizer;
  RPCClusterContainer cls = mrclizer.doAction(rpcId,tcls,mask);

  for ( auto cl : cls ) {
    LocalError tmpErr;
    LocalPoint point;
    float time = 0, timeErr = -1;

    // Call the compute method
    const bool OK = this->compute(roll, cl, point, tmpErr, time, timeErr);
    if (!OK) continue;

    // Build a new pair of 1D rechit
    const int firstClustStrip = cl.firstStrip();
    const int clusterSize = cl.clusterSize();
    RPCRecHit* recHit = new RPCRecHit(rpcId,cl.bx(),firstClustStrip,clusterSize,point,tmpErr);
    recHit->setTimeAndError(time, timeErr);

    hits2.push_back(recHit);
  }
}
  RPCClusterizerwithtime clizer;
  edm::OwnVector<RPCRecHit> hits;
  RPCClusterContainer tcls = clizer.doAction(digiRange);
  RPCMaskReClusterizer mrclizer;
  RPCClusterContainer cls = mrclizer.doAction(rpcId,tcls,mask);

  for ( auto cl : cls ) {
    LocalError tmpErr;
    LocalPoint point;
    float time = 0, timeErr = -1;

    // Call the compute method
       const bool OK = this->compute(roll, cl, point, tmpErr, time, timeErr);
       if (!OK) continue;
    //
    //             // Build a new pair of 1D rechit
        const int firstClustStrip = cl.firstStrip();
        const int clusterSize = cl.clusterSize();
        RPCRecHit* recHit = new RPCRecHit(rpcId,cl.bx(),firstClustStrip,clusterSize,point,tmpErr);
        recHit->setTimeAndError(time, timeErr);
    
        hits.push_back(recHit);
                                     }

  for ( auto hit2 : hits2 ) {
  for ( auto hit: hits) {
    //std::cout <<  " " << hit.localPosition().x() << std::endl;
  //  std::cout <<  " " << hit2.localPosition().x() << std::endl;
      if (hit.time() != hit2.time() &&  int(hit.localPosition().x()) != int(hit2.localPosition().x())   ) {
       
        result.push_back(hit2);
   }
 }
}

  return result;
}

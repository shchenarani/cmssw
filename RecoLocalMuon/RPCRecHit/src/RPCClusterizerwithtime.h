#ifndef RecoLocalMuon_RPCClusterizerwithtime_h
#define RecoLocalMuon_RPCClusterizerwithtime_h
/** \class RPCClusterizer
 *  \author M. Maggi -- INFN Bari
 */

#include "RPCClusterContainer.h"
#include "RPCCluster.h"
#include "DataFormats/RPCDigi/interface/RPCDigiCollection.h"

class RPCClusterizerwithtime{
 public:
  float thrTime=1.56;
  RPCClusterizerwithtime() {};
  ~RPCClusterizerwithtime() {};
  RPCClusterContainer doAction(const RPCDigiCollection::Range& digiRange);
};
#endif

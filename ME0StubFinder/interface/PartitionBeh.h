#ifndef ME0StubFinder_ME0StubFinder_PartitionBeh_H
#define ME0StubFinder_ME0StubFinder_PartitionBeh_H

#include "ME0StubFinder/ME0StubFinder/interface/Subfunc.h"
#include "ME0StubFinder/ME0StubFinder/interface/PatUnitMuxBeh.h"

bool is_ghost(const ME0Stub& seg,
              const ME0Stub& comp,
              bool check_ids = false,
              bool check_strips = false);
std::vector<ME0Stub> cancel_edges(const std::vector<ME0Stub>& segments,
                                  int group_width = 8,
                                  int ghost_width = 2,
                                  int edge_distance = 2,
                                  bool verbose = false);
std::vector<ME0Stub> process_partition(const std::vector<UInt192>& partition_data,
                                       int partition,
                                       Config& config);


#endif
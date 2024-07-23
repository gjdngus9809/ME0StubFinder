#ifndef MuonAnalysis_ME0StubFinder_PartitionBeh_H
#define MuonAnalysis_ME0StubFinder_PartitionBeh_H

// #include "MuonAnalysis/ME0StubFinder/interface/subfunc.h"
// #include "MuonAnalysis/ME0StubFinder/interface/pat_unit_mux_beh.h"
#include "subfunc.h"
#include "pat_unit_mux_beh.h"
#include <algorithm>

bool is_ghost(const Segment& seg,
              const Segment& comp,
              bool check_ids = false,
              bool check_strips = false);
std::vector<Segment> cancel_edges(const std::vector<Segment>& segments,
                                  int group_width = 8,
                                  int ghost_width = 2,
                                  int edge_distance = 2,
                                  bool verbose = false);
std::vector<Segment> process_partition(const std::vector<UInt192>& partition_data,
                                       int partition,
                                       Config& config);


#endif
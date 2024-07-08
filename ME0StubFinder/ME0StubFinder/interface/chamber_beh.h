#ifndef ME0StubFinder_ME0StubFinder_chamberBeh_H
#define ME0StubFinder_ME0StubFinder_chamberBeh_H

#include <vector>
#include <map>
#include <cstdint>
#include "ME0StubFinder/ME0StubFinder/interface/subfunc.h"

// map<int, vector<vector<uint64_t>>> cross_partition_cancellation(vector<vector<uint64_t>> segments);
std::vector<Segment> cross_partition_cancellation(std::vector<std::vector<Segment>> segments, int cross_part_seg_width);
std::vector<Segment> process_chmaber(std::vector<std::vector<UInt192>> chamber_data, Config config);

#endif
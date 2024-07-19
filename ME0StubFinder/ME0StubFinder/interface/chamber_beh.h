#ifndef ME0StubFinder_ME0StubFinder_ChamberBeh_H
#define ME0StubFinder_ME0StubFinder_ChamberBeh_H

#include "ME0StubFinder/ME0StubFinder/interface/subfunc.h"
#include "ME0StubFinder/ME0StubFinder/interface/partition_beh.h"
#include "ME0StubFinder/ME0StubFinder/interface/segment_sorter.h"
#include <vector>
#include <cstdint>
#include <algorithm>

// map<int, vector<vector<uint64_t>>> cross_partition_cancellation(vector<vector<uint64_t>> segments);
void cross_partition_cancellation(std::vector<std::vector<Segment>>& segments, int cross_part_seg_width);
std::vector<Segment> process_chmaber(const std::vector<std::vector<UInt192>>& chamber_data, Config& config);

#endif
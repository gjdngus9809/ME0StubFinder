#ifndef ME0StubFinder_ME0StubFinder_ChamberBeh_H
#define ME0StubFinder_ME0StubFinder_ChamberBeh_H

#include "ME0StubFinder/ME0StubFinder/interface/Subfunc.h"
#include "ME0StubFinder/ME0StubFinder/interface/PartitionBeh.h"
#include <vector>
#include <cstdint>
#include <algorithm>

// map<int, vector<vector<uint64_t>>> cross_partition_cancellation(vector<vector<uint64_t>> segments);
void cross_partition_cancellation(std::vector<std::vector<ME0Stub>>& segments, int cross_part_seg_width);
std::vector<ME0Stub> process_chamber(const std::vector<std::vector<UInt192>>& chamber_data, Config& config);

#endif
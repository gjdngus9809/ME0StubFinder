#ifndef MuonAnalysis_ME0StubFinder_PatUnitBeh_H
#define MuonAnalysis_ME0StubFinder_PatUnitBeh_H

#include "MuonAnalysis/ME0StubFinder/interface/Subfunc.h"
#include "MuonAnalysis/ME0StubFinder/interface/Mask.h"
#include <cmath>
#include <vector>
#include <cstdint>
#include <algorithm>

std::vector<uint64_t> mask_layer_data(const std::vector<uint64_t>& data, const Mask& mask);
std::vector<float> calculate_centroids(const std::vector<uint64_t>& masked_data);
int calculate_hit_count(const std::vector<uint64_t>& masked_data, bool light = false);
int calculate_layer_count(const std::vector<uint64_t>& masked_data);

Segment pat_unit(const std::vector<uint64_t>& data, 
                 unsigned int strip = 0, 
                 unsigned int ly_tresh = 4, 
                 int partition = -1, 
                 int input_max_span = 37, 
                 int num_or = 2, 
                 bool light_hit_count = true,
                 bool verbose = false);

#endif
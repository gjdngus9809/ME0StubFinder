#ifndef ME0StubFinder_ME0StubFinder_PatUnitBeh_H
#define ME0StubFinder_ME0StubFinder_PatUnitBeh_H

#include "ME0StubFinder/ME0StubFinder/interface/Subfunc.h"
#include "ME0StubFinder/ME0StubFinder/interface/Mask.h"
#include <cmath>
#include <vector>
#include <cstdint>
#include <algorithm>

std::vector<uint64_t> mask_layer_data(const std::vector<uint64_t>& data, const Mask& mask);
std::vector<double> calculate_centroids(const std::vector<uint64_t>& masked_data);
int calculate_hit_count(const std::vector<uint64_t>& masked_data, bool light = false);
int calculate_layer_count(const std::vector<uint64_t>& masked_data);

ME0Stub pat_unit(const std::vector<uint64_t>& data, 
                 int strip = 0, 
                 int partition = -1,
                 int ly_tresh = 4, 
                 int input_max_span = 37,
                 bool skip_centroids = true,
                 int num_or = 2, 
                 bool light_hit_count = true,
                 bool verbose = false);

#endif
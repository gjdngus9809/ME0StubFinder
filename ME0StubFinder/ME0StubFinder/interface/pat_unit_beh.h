#include <cmath>
#include <vector>
#include <cstdint>
#include <algorithm>
#include "ME0StubFinder/ME0StubFinder/interface/subfunc.h"

std::vector<Mask> LAYER_MASK;

std::vector<int> shift_center(const hi_lo_t& ly, int max_span = 37);
uint64_t set_high_bits(const std::vector<int>& lo_hi_pair);
Mask get_ly_mask(const patdef_t& ly_pat, int max_span = 37);
void calculate_global_layer_mask(const std::vector<patdef_t>& patlist, int max_span);
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

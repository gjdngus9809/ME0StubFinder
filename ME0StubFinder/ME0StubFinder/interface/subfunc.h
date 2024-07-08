#ifndef ME0StubFinder_ME0StubFinder_subfunc_H
#define ME0StubFinder_ME0StubFinder_subfunc_H

#include "ME0StubFinder/ME0StubFinder/interface/UInt192.h"
#include <cmath>
#include <vector>
#include <map>
#include <cstdint>
#include <algorithm>
#include <bitset>

// typedef std::bitset<192> UInt192;

struct Config {
    int ly_thresh = 4;
    int max_span = 37;
    int width = 192;
    bool deghost_pre = true;
    bool deghost_post = true;
    int group_width = 8;
    int ghost_width = 1;
    bool x_prt_en = true;
    bool en_non_pointing = false;
    int cross_part_seg_width = 4;
    int num_outputs = 4;
    bool check_ids = false;
    int edge_distance = 2;
    int num_or = 2;
};

class hi_lo_t {
private:
public:
    int hi, lo;
    hi_lo_t(int hi_, int lo_);
};

class patdef_t {
private:
public:
    int id;
    std::vector<hi_lo_t> layers;
    patdef_t(int id_, std::vector<hi_lo_t> layers_);
};

class Mask {
private:
public:
    int id;
    std::vector<uint64_t> mask;
    Mask(int id_, std::vector<uint64_t> mask_);
    std::string to_string() const;
};

class Segment {
private:
public:
    bool ignore_bend = false;
    unsigned int lc, hc, id, strip, partition;
    std::vector<float> centroid;
    float substrip = 0.0;
    float bedn_ang = 0.0;
    unsigned int quality = 0;
    Segment();
    Segment(unsigned int lc_,
            unsigned int hc_,
            unsigned int id_,
            unsigned int strip_,
            unsigned int partition_);
    Segment(unsigned int lc_,
            unsigned int hc_,
            unsigned int id_,
            unsigned int strip_,
            unsigned int partition_,
            std::vector<float>& centroid_);
    void reset();
    void update_quality();
    void fit(int max_span=37);
    std::string to_string() const;
    bool operator==(const Segment& other);
    bool operator>(const Segment& other);
    bool operator<(const Segment& other);
};

hi_lo_t mirror_hi_lo(const hi_lo_t& ly);
patdef_t mirror_patdef(const patdef_t& pat, int id);
std::vector<hi_lo_t> create_pat_ly(float lower, float upper);

int count_ones(uint64_t x);
UInt192 set_bit(int index, UInt192& num1);
UInt192 clear_bit(int index, UInt192 num);
uint64_t ones_bit_mask(int num);
std::vector<int> find_ones(uint64_t& data);
float find_centroid(uint64_t& data);
std::vector<float> llse_fit(const std::vector<float>& x, const std::vector<float>& y);
std::vector<std::vector<Segment>> chunk(const std::vector<Segment>& in_list, int n);
std::map<int,patdef_t> patlist_lut_();

// constexpr std::map<int, patdef_t> PATLIST_LUT = patlist_lut_();

#endif
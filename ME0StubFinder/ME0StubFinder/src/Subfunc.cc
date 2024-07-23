#include "ME0StubFinder/ME0StubFinder/interface/Subfunc.h"

//define structures
hi_lo_t::hi_lo_t(int hi_, int lo_) : hi{hi_}, lo{lo_} {}
patdef_t::patdef_t(int id_, std::vector<hi_lo_t> layers_) : id{id_}, layers{layers_} {}
Mask::Mask(int id_, std::vector<uint64_t> mask_) : id{id_}, mask{mask_} {}
// std::string Mask::to_string() const {}

//define class Segment
Segment::Segment() : lc{0}, hc{0}, id{0}, strip{0}, partition{0} {
    update_quality();
}
Segment::Segment(unsigned int lc_,
                 unsigned int hc_,
                 unsigned int id_,
                 unsigned int strip_,
                 unsigned int partition_) :
                lc{lc_}, hc{hc_}, id{id_}, strip{strip_}, partition{partition_} {
    update_quality();
}
Segment::Segment(unsigned int lc_,
                 unsigned int hc_,
                 unsigned int id_,
                 unsigned int strip_,
                 unsigned int partition_,
                 std::vector<float>& centroid_) :
                lc{lc_}, hc{hc_}, id{id_}, strip{strip_}, partition{partition_}, centroid{centroid_} {
    update_quality();
}
void Segment::reset() {
    lc = 0; hc = 0; id = 0;
    update_quality();
}
void Segment::update_quality() {
    int idmask;
    if (lc) {
        if (ignore_bend) {idmask = 0xfe;}
        else {idmask = 0xff;}
        quality = (lc << 23) | (hc << 17) | ((id & idmask) << 12) | (strip << 4) | partition;
    } else {quality = 0;}
}
void Segment::fit(int max_span) {
    if (id) {
        std::vector<float> tmp;
        for (float cent : centroid) {
            tmp.push_back(cent-(max_span/2+1));
        }
        std::vector<float> x;
        std::vector<float> centroids;
        for (unsigned int i=0; i < tmp.size(); ++i) {
            if (tmp[i] != -1*(max_span/2+1)) {
                x.push_back(i-2.5);
                centroids.push_back(tmp[i]);
            }
        }
        std::vector<float> fit = llse_fit(x, centroids);
        bedn_ang = fit[0];
        substrip = fit[1];
    }
}
// std::string Segment::to_string() const {}
bool Segment::operator==(const Segment& other) {
    if (lc == 0 && other.lc == 0) {return true;}
    return (quality == other.quality);
}
bool Segment::operator>(const Segment& other) {
    return (quality > other.quality);
}
bool Segment::operator<(const Segment& other) {
    return (quality < other.quality);
}
bool Segment::operator>=(const Segment& other) {
    return (quality >= other.quality);
}
bool Segment::operator<=(const Segment& other) {
    return (quality <= other.quality);
}

//define functions to generate patterns
hi_lo_t mirror_hi_lo(const hi_lo_t& ly) {
    hi_lo_t mirrored{-1*(ly.lo), -1*(ly.hi)};
    return mirrored;
}
patdef_t mirror_patdef(const patdef_t& pat, int id) {
    std::vector<hi_lo_t> layers_;
    for (hi_lo_t l : pat.layers) {
        layers_.push_back(mirror_hi_lo(l));
    }
    patdef_t mirrored{id, layers_};
    return mirrored;
}
std::vector<hi_lo_t> create_pat_ly(float lower, float upper) {
    std::vector<hi_lo_t> layer_list;
    float hi, lo;
    int hi_i, lo_i;
    for (int i=0; i<6; ++i) {
        if (i < 3) {
            hi = lower*(i-2.5);
            lo = upper*(i-2.5);
        } else {
            hi = upper*(i-2.5);
            lo = lower*(i-2.5);
        }
        if (abs(hi) < 0.1) {hi = 0.0f;}
        if (abs(lo) < 0.1) {lo = 0.0f;}
        hi_i = std::ceil(hi);
        lo_i = std::floor(lo);
        layer_list.push_back(hi_lo_t{hi_i, lo_i});
    }
    return layer_list;
}
int count_ones(u_int64_t x) {
    int cnt = 0;
    while (x > 0) {
        if (x&1) {
            ++cnt;
        }
        x = (x>>1);
    }
    return cnt;
}
UInt192 set_bit(int index, UInt192 num1 = UInt192(0)) {
    UInt192 num2 = (UInt192(1) << index);
    UInt192 final_v = num1 | num2;
    return final_v;
}
UInt192 clear_bit(int index, UInt192 num) {
    UInt192 bit = UInt192(1) & (num >> index);
    return num^(bit << index);
}
uint64_t one_bit_mask(int num) {
    uint64_t o_mask = 0;
    int bit_num = 0;
    while (num != 0) {
        o_mask |= (1 << bit_num);
        num = (num >> 1);
        ++bit_num;
    }
    return o_mask;
}
std::vector<int> find_ones(uint64_t& data) {
    std::vector<int> ones;
    int cnt = 0;
    while (data > 0) {
        if ((data & 1)) {ones.push_back(cnt+1);}
        data >>= 1;
        ++cnt;
    }
    return ones;
}
float find_centroid(uint64_t& data) {
    std::vector<int> ones = find_ones(data);
    if (!(ones.size())) {return 0.0;}
    int sum = 0;
    for (int n : ones) {sum += n;}
    return sum/ones.size();
}
std::vector<float> llse_fit(const std::vector<float>& x, const std::vector<float>& y) {
    float x_sum = 0;
    float y_sum = 0;
    for (float val : x) {x_sum += val;}
    for (float val : y) {y_sum += val;}
    int n = x.size();
    // linear regression
    float product = 0;
    float squares = 0;
    for (int i=0; i<n; ++i) {
        product += (n*x[i] - x_sum)*(n*y[i] - y_sum);
        squares += (n*x[i] - x_sum)*(n*x[i] - x_sum);
    }

    float m = product/squares;
    float b = (y_sum - m*x_sum)/n;
    std::vector<float> fit = {m, b};
    return fit;
}
std::vector<std::vector<Segment>> chunk(const std::vector<Segment>& in_list, int n) {
    std::vector<std::vector<Segment>> chunks;
    int size = in_list.size();
    for (int i = 0; i < (size + n - 1) / n; ++i) {
        std::vector<Segment> chunk(in_list.begin() + i * n, in_list.begin() + std::min((i + 1) * n, size));
        chunks.push_back(chunk);
    }
    return chunks;
}
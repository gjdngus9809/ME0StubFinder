#include "ME0StubFinder/ME0StubFinder/interface/Subfunc.h"

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
        }
        else {
            hi = upper*(i-2.5);
            lo = lower*(i-2.5);
        }
        if (std::abs(hi) < 0.1) {hi = 0.0f;}
        if (std::abs(lo) < 0.1) {lo = 0.0f;}
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
    return (float)sum/ones.size();
}
std::vector<std::vector<ME0Stub>> chunk(const std::vector<ME0Stub>& in_list, int n) {
    std::vector<std::vector<ME0Stub>> chunks;
    int size = in_list.size();
    for (int i = 0; i < (size + n - 1) / n; ++i) {
        std::vector<ME0Stub> chunk(in_list.begin() + i * n, in_list.begin() + std::min((i + 1) * n, size));
        chunks.push_back(chunk);
    }
    return chunks;
}
void segment_sorter(std::vector<ME0Stub>& segs, int n) {
    std::sort(segs.begin(), segs.end(),
          [](const ME0Stub& lhs, const ME0Stub& rhs) {
            return (lhs.Quality() > rhs.Quality());});
    segs = std::vector<ME0Stub>(segs.begin(), segs.begin() + n);
}
std::vector<ME0Stub> concatVector(const std::vector<std::vector<ME0Stub>>& vec) {
    std::vector<ME0Stub> cat;
    for (auto v : vec) {
        cat.insert(cat.end(), v.begin(), v.end());
    }
    return cat;
}
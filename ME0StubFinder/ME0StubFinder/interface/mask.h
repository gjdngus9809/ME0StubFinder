#ifndef ME0StubFinder_ME0StubFinder_Mask_H
#define ME0StubFinder_ME0StubFinder_Mask_H

#include "ME0StubFinder/ME0StubFinder/interface/subfunc.h"

std::vector<int> shift_center(const hi_lo_t& ly, int max_span) {
    /*

    Patterns are defined as a +hi and -lo around a center point of a pattern.

    e.g. for a pattern 37 strips wide, there is a central strip,
    and 18 strips to the left and right of it.

    This patterns shifts from a +hi and -lo around the central strip, to an offset +hi and -lo.

    e.g. for (hi, lo) = (1, -1) and a window of 37, this will return (17,19)

    */
    int center = std::floor(max_span/2);
    int hi = ly.hi + center;
    int lo = ly.lo + center;
    std::vector<int> out = {lo, hi};
    return out;
}

uint64_t set_high_bits(const std::vector<int>& lo_hi_pair) {
    /*
    Given a high bit and low bit, this function will return a bitmask with all the bits in
    between the high and low set to 1
    */
    int lo = lo_hi_pair[0], hi = lo_hi_pair[1];
    uint64_t out = std::pow(2,(hi-lo+1)) - 1;
    out <<= lo;
    return out;
}

Mask get_ly_mask(const patdef_t& ly_pat, int max_span) {
    /*
    takes in a given layer pattern and returns a list of integer bit masks
    for each layer
    */

    std::vector<std::vector<int>> m_vals;
    std::vector<uint64_t> m_vec;
    
    // for each layer, shift the provided hi and lo values for each layer from
    // pattern definition by center
    for (hi_lo_t ly : ly_pat.layers) {m_vals.push_back(shift_center(ly, max_span));}
    
    // use the high and low indices to determine where the high bits must go for
    // each layer 
    for (std::vector<int> x : m_vals) {m_vec.push_back(set_high_bits(x));}
    
    Mask mask_{ly_pat.id, m_vec};
    return mask_; 
}

patdef_t pat_straight = patdef_t(19, create_pat_ly(-0.4, 0.4));
patdef_t pat_l = patdef_t(18, create_pat_ly(0.2, 0.9));
patdef_t pat_r = mirror_patdef(pat_l, pat_l.id - 1);
patdef_t pat_l2 = patdef_t(16, create_pat_ly(0.5, 1.2));
patdef_t pat_r2 = mirror_patdef(pat_l2, pat_l2.id - 1);
patdef_t pat_l3 = patdef_t(14, create_pat_ly(0.9, 1.7));
patdef_t pat_r3 = mirror_patdef(pat_l3, pat_l3.id - 1);
patdef_t pat_l4 = patdef_t(12, create_pat_ly(1.4, 2.3));
patdef_t pat_r4 = mirror_patdef(pat_l4, pat_l4.id - 1);
patdef_t pat_l5 = patdef_t(10, create_pat_ly(2.0, 3.0));
patdef_t pat_r5 = mirror_patdef(pat_l5, pat_l5.id - 1);
patdef_t pat_l6 = patdef_t(8, create_pat_ly(2.7, 3.8));
patdef_t pat_r6 = mirror_patdef(pat_l6, pat_l6.id - 1);
patdef_t pat_l7 = patdef_t(6, create_pat_ly(3.5, 4.7));
patdef_t pat_r7 = mirror_patdef(pat_l7, pat_l7.id-1);
patdef_t pat_l8 = patdef_t(4, create_pat_ly(4.3, 5.5));
patdef_t pat_r8 = mirror_patdef(pat_l8, pat_l8.id-1);
patdef_t pat_l9 = patdef_t(2, create_pat_ly(5.4, 7.0));
patdef_t pat_r9 = mirror_patdef(pat_l9, pat_l9.id - 1);

const std::vector<Mask> LAYER_MASK
    {get_ly_mask(pat_straight,37),
     get_ly_mask(pat_l,37),
     get_ly_mask(pat_r,37),
     get_ly_mask(pat_l2,37),
     get_ly_mask(pat_r2,37),
     get_ly_mask(pat_l3,37),
     get_ly_mask(pat_r3,37),
     get_ly_mask(pat_l4,37),
     get_ly_mask(pat_r4,37),
     get_ly_mask(pat_l5,37),
     get_ly_mask(pat_r5,37),
     get_ly_mask(pat_l6,37),
     get_ly_mask(pat_r6,37),
     get_ly_mask(pat_l7,37),
     get_ly_mask(pat_r7,37),
     get_ly_mask(pat_l8,37),
     get_ly_mask(pat_r8,37),
     get_ly_mask(pat_l9,37),
     get_ly_mask(pat_r9,37)};


#endif
#include "ME0StubFinder/ME0StubFinder/interface/pat_unit_beh.h"

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

void calculate_global_layer_mask(const std::vector<patdef_t>& patlist, int max_span) {
    // create layer masks for patterns in patlist
    LAYER_MASK.clear();
    for (patdef_t pat : patlist) {
        LAYER_MASK.push_back(get_ly_mask(pat,max_span));
    }
}
std::vector<uint64_t> mask_layer_data(const std::vector<uint64_t>& data, const Mask& mask_) {
    std::vector<uint64_t> out;
    for (int i=0; i<(int)data.size(); ++i) {
        out.push_back(data[i] & mask_.mask[i]);
    }
    return out;
}

std::vector<float> calculate_centroids(const std::vector<uint64_t>& masked_data) {
    std::vector<float> centroids;
    for (uint64_t d : masked_data) {
        centroids.push_back(find_centroid(d));
    }
    return centroids;
}

int calculate_hit_count(std::vector<uint64_t>& masked_data, bool light = false) {
    int tot_hit_count = 0;
    if (light) {
        for (int ly : {0, 5}) {
            int hit_ly = count_ones(masked_data[ly]);
            tot_hit_count += (hit_ly < 7)? hit_ly : 7;
        }
    }
    else {
        for (uint64_t d : masked_data) {
            tot_hit_count += count_ones(d);
        }
    }
    return tot_hit_count;
}
int calculate_layer_count(const std::vector<uint64_t>& masked_data) {
    int ly_count = 0;
    bool not_zero;
    for (uint64_t d : masked_data) {
        not_zero = (bool)d;
        ly_count += not_zero;
    }
    return ly_count;
}

Segment pat_unit(const std::vector<uint64_t>& data, 
                 unsigned int strip, 
                 unsigned int ly_tresh, 
                 int partition, 
                 int input_max_span, 
                 int num_or, 
                 bool light_hit_count,
                 bool verbose) {
    
    // construct the dynamic_patlist (we do not use default PATLIST anymore)
    // for robustness concern, other codes might use PATLIST, so we kept the default PATLIST in subfunc
    // however, this could cause inconsistent issue, becareful! OR find a way to modify PATLIST
    if (LAYER_MASK.empty()) {
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
        std::vector<patdef_t> dynamic_patlist{
            pat_straight,
            pat_l,
            pat_r,
            pat_l2,
            pat_r2,
            pat_l3,
            pat_r3,
            pat_l4,
            pat_r4,
            pat_l5,
            pat_r5,
            pat_l6,
            pat_r6,
            pat_l7,
            pat_r7,
            pat_l8,
            pat_r8,
            pat_l9,
            pat_r9};

        calculate_global_layer_mask(dynamic_patlist, input_max_span);
    }
    /*
    takes in sample data for each layer and returns best segment

    processing pipeline is

    (1) take in 6 layers of raw data
    (2) for the X (~16) patterns available, AND together the raw data with the respective pattern masks
    (3) count the # of hits in each pattern
    (4) calculate the centroids for each pattern
    (5) process segments
    (6) choose the max of all patterns
    (7) apply a layer threshold
    */
    
    // (2)
    // and the layer data with the respective layer mask to
    // determine how many hits are in each layer
    // this yields a map object that can be iterated over to get,
    //    for each of the N patterns, the masked []*6 layer data
    std::vector<std::vector<uint64_t>> masked_data;
    std::vector<int> pids;
    for (const Mask& M : LAYER_MASK) {
        masked_data.push_back(mask_layer_data(data, M));
        pids.push_back(M.id);
    }

    // (3) count # of hits
    // (4) process centroids
    std::vector<unsigned int> hcs;
    std::vector<unsigned int> lcs;
    std::vector<std::vector<float>> centroids;
    for (const std::vector<uint64_t>& x : masked_data) {
        hcs.push_back(calculate_hit_count(x, light_hit_count));
        lcs.push_back(calculate_layer_count(x));
        centroids.push_back(calculate_centroids(x));
    }

    // std::vector<Segment> seg_list;
    // for (int i = 0; i<hcs.size(); ++i) {
        // seg_list.push_back()
    // }
    Segment best{0,0,0,0,0};
    Segment seg{0,0,0,0,0};
    for (int i = 0; i<(int)hcs.size(); ++i) {
        seg.lc = lcs[i]; seg.hc = hcs[i]; seg.id = pids[i]; seg.strip = strip;
        seg.update_quality();
        if (best < seg) {
            best = seg;
            best.centroid = centroids[i];
            best.update_quality();
        }
    }

    if (best.lc < ly_tresh) {best.reset();}

    best.partition = partition;

    // if (verbose) {
        // for (int ly=0; ly<6; ++ly) {
            // for (int bit=0; bit<37; ++bit) {
                // std::cout << std::endl;
            // }
        // }
    // }

    best.hc = 0;
    best.update_quality();

    return best;
}
#include "ME0StubFinder/ME0StubFinder/interface/PatUnitBeh.h"

std::vector<uint64_t> mask_layer_data(const std::vector<uint64_t>& data, const Mask& mask_) {
    std::vector<uint64_t> out;
    for (int i=0; i<(int)data.size(); ++i) {
        out.push_back(data[i] & mask_.mask[i]);
    }
    return out;
}

std::vector<double> calculate_centroids(const std::vector<uint64_t>& masked_data) {
    std::vector<double> centroids;
    for (uint64_t d : masked_data) {
        centroids.push_back(find_centroid(d));
    }
    return centroids;
}

int calculate_hit_count(const std::vector<uint64_t>& masked_data, bool light) {
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
        not_zero =  (d!=0);
        ly_count += (int)not_zero;
    }
    return ly_count;
}

ME0Stub pat_unit(const std::vector<uint64_t>& data, 
                 int strip, 
                 int partition,
                 int ly_tresh, 
                 int input_max_span,
                 bool skip_centroids,
                 int num_or, 
                 bool light_hit_count,
                 bool verbose) {
    
    // construct the dynamic_patlist (we do not use default PATLIST anymore)
    // for robustness concern, other codes might use PATLIST, so we kept the default PATLIST in subfunc
    // however, this could cause inconsistent issue, becareful! OR find a way to modify PATLIST

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
    std::vector<int> hcs;
    std::vector<int> lcs;
    std::vector<std::vector<double>> centroids;
    for (const std::vector<uint64_t>& x : masked_data) {
        hcs.push_back(calculate_hit_count(x, light_hit_count));
        lcs.push_back(calculate_layer_count(x));
        if (skip_centroids) {
            centroids.push_back({0,0,0,0,0,0});
        } 
        else {
            centroids.push_back(calculate_centroids(x));
        }
    }

    // std::vector<ME0Stub> seg_list;
    // for (int i = 0; i<hcs.size(); ++i) {
        // seg_list.push_back()
    // }
    ME0Stub best{0, 0, 0, strip, partition};
    for (int i = 0; i<(int)hcs.size(); ++i) {
        ME0Stub seg{lcs[i], hcs[i], pids[i], strip, partition};
        seg.update_quality();
        if (best.Quality() < seg.Quality()) {
            best = seg;
            best.SetCentroids(centroids[i]);
            best.update_quality();
        }
    }

    if (best.LayerCount() < ly_tresh) {best.reset();}

    /*
    
    for (int ly=0; ly<6; ++ly) {
        for (int bit=0; bit<37; ++bit) {
            std::cout << (0x1 & (data[ly] >> bit));
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    for (int i=0; i<(int)masked_data.size(); ++i) {
        std::cout << "id=" << i+1 << std::endl;
        auto id = masked_data[i];
        for (int ly=0; ly<6; ++ly) {
            for (int bit=0; bit<37; ++bit) {
                std::cout << (0x1 & (id[ly] >> bit));
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    */

    best.SetHitCount(0);
    best.update_quality();

    return best;
}
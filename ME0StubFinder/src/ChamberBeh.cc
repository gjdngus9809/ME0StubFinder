#include "ME0StubFinder/ME0StubFinder/interface/ChamberBeh.h"
#include <algorithm>

void cross_partition_cancellation(std::vector<std::vector<ME0Stub>>& segments, int cross_part_seg_width) {
    ME0Stub seg, seg1, seg2;

    int strip;
    int seg1_max_quality;
    int seg2_max_quality;
    int seg1_max_quality_index;
    int seg2_max_quality_index;
    
    for (int i=1; i<15; i+=2) {
        for (int l=0; l<(int)segments[i].size(); ++l) {
            seg = segments[i][l];
            if (!seg.PatternId()) 
                continue;
            strip = seg.Strip();

            seg1_max_quality = -9999;
            seg2_max_quality = -9999;
            seg1_max_quality_index = -9999;
            seg2_max_quality_index = -9999;

            for (int j=0; j<(int)segments[i-1].size(); ++j) {
                seg1 = segments[i-1][j];
                if (!seg1.PatternId())
                    continue;
                if (abs(strip-seg1.Strip()) <= cross_part_seg_width) {
                    if (seg1.Quality() > seg1_max_quality) {
                        if (seg1_max_quality_index != -9999)
                            (segments[i-1][seg1_max_quality_index]).reset();
                        seg1_max_quality_index = j;
                        seg1_max_quality = seg1.Quality();
                    }
                }
            }
            for (int k=0; k<(int)segments[i+1].size(); ++k) {
                seg2 = segments[i+1][k];
                if (!seg2.PatternId())
                    continue;
                if (std::abs(strip-seg2.Strip()) <= cross_part_seg_width) {
                    if (seg2.Quality() > seg2_max_quality) {
                        if (seg2_max_quality_index != -9999)
                            (segments[i+1][seg2_max_quality_index]).reset();
                        seg2_max_quality_index = k;
                        seg2_max_quality = seg2.Quality();
                    }
                }
            }

            if ((seg1_max_quality_index != -9999) && 
                (seg2_max_quality_index != -9999)) {
                segments[i-1][seg1_max_quality_index].reset();
                segments[i+1][seg2_max_quality_index].reset();
            }
            else if (seg1_max_quality_index != -9999) {
                segments[i][l].reset();
            }
            else if (seg2_max_quality_index != -9999) {
                segments[i][l].reset();
            }
        }
    }
}

std::vector<ME0Stub> process_chamber(const std::vector<std::vector<UInt192>>& chamber_data, Config& config) {
    std::vector<std::vector<ME0Stub>> segments;
    int num_finder = (config.x_prt_en)? 15 : 8;

    std::vector<std::vector<UInt192>> data = std::vector<std::vector<UInt192>>(num_finder,std::vector<UInt192>(6));
    if (config.x_prt_en) {

        for (int finder=0; finder<num_finder; ++finder) {
            // even finders are simple, just take the partition
            if (finder%2 == 0) {
                data[finder] = chamber_data[finder/2];
            }
            // odd finders are the OR of two adjacent partitions
            else {
                data[finder][0] =                               chamber_data[finder/2+1][0];
                data[finder][1] =                               chamber_data[finder/2+1][1];
                data[finder][2] = chamber_data[finder/2][2]  |  chamber_data[finder/2+1][2];
                data[finder][3] = chamber_data[finder/2][3]  |  chamber_data[finder/2+1][3];
                data[finder][4] = chamber_data[finder/2][4]                                ;
                data[finder][5] = chamber_data[finder/2][5]                                ;
            }
        }
    }
    else {data = chamber_data;}

    for (int prt=0; prt<(int)data.size(); ++prt) {
        const std::vector<UInt192>& prt_data = data[prt];
        const std::vector<ME0Stub>& segs = process_partition(prt_data, prt, config);
        segments.push_back(segs);
    }
    if (config.cross_part_seg_width > 0) {
        cross_partition_cancellation(segments, config.cross_part_seg_width);
    }

    // pick the best N outputs from each partition
    for (int i=0; i<(int)segments.size(); ++i){
        // segments[i] = segment_sorter(segments[i], config.num_outputs);
        segment_sorter(segments[i], config.num_outputs);
    }

    // join each 2 partitions and pick the best N outputs from them
    std::vector<std::vector<ME0Stub>> joined_segments;
    for (int i = 1; i<(int)segments.size(); i+=2) {
        std::vector<std::vector<ME0Stub>> seed = {segments[i-1],segments[i]};
        std::vector<ME0Stub> pair = concatVector(seed);
        joined_segments.push_back(pair);
    }
    joined_segments.push_back(segments[14]);
    for (int i=0; i<(int)joined_segments.size(); ++i) {
        // joined_segments[i] = segment_sorter(joined_segments[i], config.num_outputs);
        segment_sorter(joined_segments[i], config.num_outputs);
    }

    // concatenate together all of the segments, sort them, and pick the best N outputs
    std::vector<ME0Stub> concatenated = concatVector(joined_segments);
    // concatenated = segment_sorter(concatenated, config.num_outputs);
    segment_sorter(concatenated, config.num_outputs);

    return concatenated;
}

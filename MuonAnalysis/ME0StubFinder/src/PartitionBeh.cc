#include "MuonAnalysis/ME0StubFinder/interface/PartitionBeh.h"

bool is_ghost(const Segment& seg,
              const Segment& comp,
              bool check_ids,
              bool check_strips) {
    /*
    takes in a segment and a list of segments to ensure that there aren't
    copies of the same data (ID value identical) or mirrors (ID value + 2 or - 2
    from each other)
    */

    bool ghost = (seg.quality < comp.quality) &&
                 (!check_strips || (abs(seg.strip - comp.strip) < 2)) &&
                 (!check_ids || ((seg.id == comp.id) || (seg.id+2 == comp.id) || (seg.id == comp.id+2)));
    return ghost;
}


std::vector<Segment> cancel_edges(const std::vector<Segment>& segments,
                                  int group_width,
                                  int ghost_width,
                                  int edge_distance,
                                  bool verbose) {
    /*
    Takes in a list of SEGMENTS and is designed to perform ghost
    cancellation on the edges of the "groups".

    during segment sorting, an initial step is that the partition is chunked into
    groups of width GROUP_WIDTH. The firmware selects just one segment from each group.

    Since segments can ghost (produce duplicates of the same segment on
    different strips), we do a ghost cancellation before this group filtering process.

    This is done by looking at the edges of the group and zeroing off a segment
    if it is of lower quality than its neighbors. Segments away from the edges
    of the group will not need to be de-duplicated since this is handled by the
    group filtering process itself. This is only needed to prevent duplicates
    from appearing in different groups.

    An implementation that cancels after the filtering is much simpler and less
    resource intensive but comes with the downside that we may lose segments.

    ghost_width = 0 means do not compare
    ghost_width = 1 means look 1 to the left and right
    ghost_width = 2 means look 2 to the left and right

    edge_distance specifies which strips will have ghost cancellation done on them
    edge_distance = 0 means to only look at strips directly on the edges (0 7 8 15 etc)
    edge_distance = 1 means to look one away from the edge (0 1 6 7 8 9 14 15 16 17 etc)

    etc
    */

    std::vector<Segment> canceled_segements = segments;
    std::vector<int> comps;
    bool is_at_edge;
    bool ghost;

    for (int i=0; i < (int)segments.size(); ++i) {
        if (group_width > 0) {is_at_edge = (i%group_width < edge_distance) || ((i%group_width) >= (group_width-edge_distance));}
        else {is_at_edge = true;}

        if (is_at_edge) {
            for (int x = i-ghost_width; x < i; ++x) {
                if (x >= 0) {comps.push_back(x);}
            }
            for (int x = i+1; x < i+ghost_width+1; ++x) {
                if (x < (int)segments.size()) {comps.push_back(x);}
            }

            for (int comp : comps) {
                ghost = is_ghost(segments[i], segments[comp]);
                if (ghost) {
                    canceled_segements[i] = Segment();
                }
            }
            comps.clear();
        }
    }
    
    return canceled_segements;
}

std::vector<Segment> process_partition(const std::vector<UInt192>& partition_data,
                                       int partition,
                                       Config& config) {
    
    /*
    takes in partition data, a group size, and a ghost width to return a
    smaller data set, using ghost edge cancellation and segment quality
    filtering

    NOTE: ghost width denotes the width where we can likely see copies of the
    same segment in the data

    steps: process partition data with pat_mux, perfom edge cancellations,
    divide partition into pieces, take best segment from each piece
    */
    std::vector<Segment> out;
    std::vector<Segment> segments = pat_mux(partition_data, partition, config);

    if (config.deghost_pre) {
        segments = cancel_edges(segments, config.group_width, config.ghost_width, config.edge_distance);
    }
    
    std::vector<std::vector<Segment>> chunked = chunk(segments, config.group_width);
    for (const std::vector<Segment>& seg_v : chunked) {
        Segment max_seg;
        for (const Segment& seg : seg_v) {
            if (max_seg < seg) {max_seg = seg;}
        }
        out.push_back(max_seg);
    }

    if (config.deghost_post) {
        out = cancel_edges(out, 0, 1, 1);
    }

    return out;
}

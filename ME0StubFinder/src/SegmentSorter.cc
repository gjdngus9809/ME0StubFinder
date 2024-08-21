#include "ME0StubFinder/ME0StubFinder/interface/SegmentSorter.h"

void segment_sorter(std::vector<Segment>& segs, int n, int blockSize) {
    std::sort(segs.begin(), segs.end(),
          [](const Segment& lhs, const Segment& rhs) {
            return ((int) lhs.quality) > ((int) rhs.quality);});
    segs = std::vector<Segment>(segs.begin(), segs.begin() + n);
}

std::vector<Segment> concatVector(const std::vector<std::vector<Segment>>& vec) {
    std::vector<Segment> cat;
    for (auto v : vec) {
        cat.insert(cat.end(), v.begin(), v.end());
    }
    return cat;
}

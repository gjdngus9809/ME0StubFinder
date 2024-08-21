#ifndef ME0StubFinder_ME0StubFinder_SegmentSorter_H
#define ME0StubFinder_ME0StubFinder_SegmentSorter_H

#include "ME0StubFinder/ME0StubFinder/interface/Subfunc.h"
#include <vector>

void segment_sorter(std::vector<Segment>& segs, int n, int blockSize); 
std::vector<Segment> concatVector(const std::vector<std::vector<Segment>>& vec);

#endif
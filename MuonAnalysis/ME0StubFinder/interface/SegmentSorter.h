#ifndef MuonAnalysis_ME0StubFinder_SegmentSorter_H
#define MuonAnalysis_ME0StubFinder_SegmentSorter_H

#include "MuonAnalysis/ME0StubFinder/interface/Subfunc.h"
#include <vector>

void insertionSort(std::vector<Segment>& vec, int left, int right);
void merge(std::vector<Segment>& vec, int left, int mid, int right);
void blockSort(std::vector<Segment>& vec, int blockSize);
std::vector<Segment> segment_sorter(const std::vector<Segment>& segs, int n, int blockSize); 

std::vector<Segment> concatVector(const std::vector<std::vector<Segment>>& vec);

#endif
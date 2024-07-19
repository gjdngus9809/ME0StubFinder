#ifndef ME0StubFinder_ME0StubFinder_SegmentSorter_H
#define ME0StubFinder_ME0StubFinder_SegmentSorter_H

#include "ME0StubFinder/ME0StubFinder/interface/subfunc.h"
#include <vector>

void insertionSort(std::vector<Segment>& vec, int left, int right);
void merge(std::vector<Segment>& vec, int left, int mid, int right);
void blockSort(std::vector<Segment>& vec, int blockSize);
std::vector<Segment> segment_sorter(const std::vector<Segment>& segs, int n, int blockSize); 

std::vector<Segment> concatVector(const std::vector<std::vector<Segment>>& vec);

#endif
#include "ME0StubFinder/ME0StubFinder/interface/segment_sorter.h"

// Function to perform insertion sort on a subarray
void insertionSort(std::vector<Segment>& vec, int left, int right) {
    for (int i = left + 1; i <= right; ++i) {
        Segment key = vec[i];
        int j = i - 1;
        while (j >= left && vec[j] > key) {
            vec[j + 1] = vec[j];
            --j;
        }
        vec[j + 1] = key;
    }
}

// Function to merge two sorted subarrays
void merge(std::vector<Segment>& vec, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<Segment> leftArr(n1);
    std::vector<Segment> rightArr(n2);

    for (int i = 0; i < n1; ++i) {
        leftArr[i] = vec[left + i];
    }
    for (int i = 0; i < n2; ++i) {
        rightArr[i] = vec[mid + 1 + i];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            vec[k] = leftArr[i];
            ++i;
        } else {
            vec[k] = rightArr[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        vec[k] = leftArr[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        vec[k] = rightArr[j];
        ++j;
        ++k;
    }
}

// Function to perform block sort on the vector
void blockSort(std::vector<Segment>& vec, int blockSize) {
    int n = vec.size();

    // Sort individual blocks using insertion sort
    for (int i = 0; i < n; i += blockSize) {
        insertionSort(vec, i, std::min(i + blockSize - 1, n - 1));
    }

    // Merge the blocks
    for (int size = blockSize; size < n; size *= 2) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = std::min(left + size - 1, n - 1);
            int right = std::min(left + 2 * size - 1, n - 1);
            if (mid < right) {
                merge(vec, left, mid, right);
            }
        }
    }
}

std::vector<Segment> segment_sorter(const std::vector<Segment>& segs, int n, int blockSize) {
    std::vector<Segment> new_segs = segs;

    blockSort(new_segs, blockSize);

    std::vector<Segment> out(new_segs.end() - n, new_segs.end()); 
    return out;
}

std::vector<Segment> concatVector(const std::vector<std::vector<Segment>>& vec) {
    std::vector<Segment> cat;
    for (auto v : vec) {
        cat.insert(cat.end(), v.begin(), v.end());
    }
    return cat;
}

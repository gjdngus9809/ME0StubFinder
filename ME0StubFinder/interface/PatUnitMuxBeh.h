#ifndef ME0StubFinder_ME0StubFinder_PatUnitMuxBeh_H
#define ME0StubFinder_ME0StubFinder_PatUnitMuxBeh_H

#include "ME0StubFinder/ME0StubFinder/interface/Subfunc.h"
#include "ME0StubFinder/ME0StubFinder/interface/PatUnitBeh.h"
#include <vector>
#include <cstdint>
#include <cmath>

uint64_t parse_data(const UInt192& data, int strip, int max_span);
std::vector<uint64_t> extract_data_window(const std::vector<UInt192>& ly_dat, int strip, int max_span);
std::vector<ME0Stub> pat_mux(const std::vector<UInt192>& partition_data, int partition, Config& config);

#endif
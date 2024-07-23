#ifndef MuonAnalysis_ME0StubFinder_PatUnitMuxBeh_H
#define MuonAnalysis_ME0StubFinder_PatUnitMuxBeh_H

// #include "MuonAnalysis/ME0StubFinder/interface/subfunc.h"
// #include "MuonAnalysis/ME0StubFinder/interface/pat_unit_beh.h"
#include "subfunc.h"
#include "pat_unit_beh.h"

uint64_t parse_data(const UInt192& data, int strip, int max_span);
std::vector<uint64_t> extract_data_window(const std::vector<UInt192>& ly_dat, int strip, int max_span);
std::vector<Segment> pat_mux(const std::vector<UInt192>& partition_data, int partition, Config& config);

#endif
#include "ME0StubFinder/ME0StubFinder/interface/pat_unit_mux_beh.h"

uint64_t parse_data(const UInt192& data, int strip, int max_span) {
    UInt192 data_shifted;
    uint64_t parsed_data;
    if (strip < max_span/2 + 1) {
        data_shifted = data << (max_span/2 -strip);
        parsed_data = (uint64_t)data_shifted & (uint64_t)(pow(2,max_span) - 1);
    }
    else {
        data_shifted = data >> (strip - max_span/2);
        parsed_data = (uint64_t)data_shifted & (uint64_t)(pow(2,max_span) - 1);
    }
    return parsed_data;
}
std::vector<uint64_t> extract_data_window(const std::vector<UInt192>& ly_dat, int strip, int max_span) {
    std::vector<uint64_t> out;
    for (const UInt192& data : ly_dat) {
        out.push_back(parse_data(data,strip,max_span));
    }
    return out;
}
std::vector<Segment> pat_mux(const std::vector<UInt192>& partition_data, int partition, Config& config) {
    std::vector<Segment> out;
    Segment S;
    for (int strip=0; strip<config.width; ++strip) {
        S = pat_unit(extract_data_window(partition_data, strip, config.max_span),
                     strip,
                     config.ly_thresh,
                     partition,
                     config.max_span,
                     config.num_or);
        out.push_back(S);
    }
    return out;
}

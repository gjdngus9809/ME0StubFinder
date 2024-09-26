#ifndef ME0StubFinder_ME0StubFinder_ME0Stub_H
#define ME0StubFinder_ME0StubFinder_ME0Stub_H

#include <vector>
#include <cstdint>
#include <string>

class ME0Stub {
public:
    bool ignore_bend = false;
    int lc, hc, id, strip, partition;
    std::vector<float> centroid;
    float substrip = 0.0;
    float bend_ang = 0.0;
    int quality = 0;
    ME0Stub();
    ME0Stub(int lc_,
            int hc_,
            int id_,
            int strip_,
            int partition_);
    ME0Stub(int lc_,
            int hc_,
            int id_,
            int strip_,
            int partition_,
            std::vector<float>& centroid_);
    ME0Stub* clone() const { return new ME0Stub(*this); }
    void reset();
    void update_quality();
    void fit(int max_span=37);
    // std::string to_string() const;
    bool operator==(const ME0Stub& other);
    bool operator>(const ME0Stub& other);
    bool operator<(const ME0Stub& other);
    bool operator>=(const ME0Stub& other);
    bool operator<=(const ME0Stub& other);
private:
    std::vector<float> llse_fit(const std::vector<float>& x, const std::vector<float>& y);
};

#endif
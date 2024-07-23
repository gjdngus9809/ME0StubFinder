#include "MuonAnalysis/ME0StubFinder/interface/UInt192.h"

// Default constructor
UInt192::UInt192() : low(0), mid(0), high(0) {}

// Constructor from three 64-bit values
UInt192::UInt192(uint64_t low_, uint64_t mid_, uint64_t high_)
    : low(low_), mid(mid_), high(high_) {}

// Constructor from a single uint64_t value
UInt192::UInt192(uint64_t value) : low(value), mid(0), high(0) {}

// Copy constructor
UInt192::UInt192(const UInt192& other)
    : low(other.low), mid(other.mid), high(other.high) {}

// Addition operator
UInt192 UInt192::operator+(const UInt192& other) const {
    UInt192 result;
    uint64_t carry = 0;

    // Add low parts
    result.low = low + other.low;
    if (result.low < low) carry = 1; // Check for overflow

    // Add mid parts with carry
    result.mid = mid + other.mid + carry;
    if (result.mid < mid || (carry && result.mid == mid)) carry = 1;
    else carry = 0;

    // Add high parts with carry
    result.high = high + other.high + carry;

    return result;
}

// Multiplication operator
UInt192 UInt192::operator*(const UInt192& other) const {
    UInt192 result;
    UInt192 temp = *this;

    for (int i = 0; i < 192; ++i) {
        if (other.low & (1ULL << i)) {
            result = result + (temp << i);
        }
    }

    return result;
}

// Bitwise AND operator
UInt192 UInt192::operator&(const UInt192& other) const {
    return UInt192(high & other.high, mid & other.mid, low & other.low);
}

// Bitwise OR operator
UInt192 UInt192::operator|(const UInt192& other) const {
    return UInt192(high | other.high, mid | other.mid, low | other.low);
}

// Bitwise XOR operator
UInt192 UInt192::operator^(const UInt192& other) const {
    return UInt192(high ^ other.high, mid ^ other.mid, low ^ other.low);
}

// Bitwise NOT operator
UInt192 UInt192::operator~() const {
    return UInt192(~high, ~mid, ~low);
}

// Left shift operator
UInt192 UInt192::operator<<(int shift) const {
    if (shift < 0) return *this >> -shift;
    if (shift == 0) return *this;
    if (shift >= 192) return UInt192(0, 0, 0);

    UInt192 result;

    if (shift >= 128) {
        result.high = low << (shift - 128);
    } else if (shift >= 64) {
        result.high = mid << (shift - 64);
        result.mid = low << (shift - 64);
        result.mid |= low >> (128 - shift);
    } else {
        result.high = high << shift;
        result.high |= mid >> (64 - shift);
        result.mid = mid << shift;
        result.mid |= low >> (64 - shift);
        result.low = low << shift;
    }

    return result;
}

// Right shift operator
UInt192 UInt192::operator>>(int shift) const {
    if (shift < 0) return *this << -shift;
    if (shift == 0) return *this;
    if (shift >= 192) return UInt192(0, 0, 0);

    UInt192 result;

    if (shift >= 128) {
        result.low = high >> (shift - 128);
    } else if (shift >= 64) {
        result.low = mid >> (shift - 64);
        result.low |= high << (128 - shift);
        result.mid = high >> (shift - 64);
    } else {
        result.low = low >> shift;
        result.low |= mid << (64 - shift);
        result.mid = mid >> shift;
        result.mid |= high << (64 - shift);
        result.high = high >> shift;
    }

    return result;
}

// Assignment operator
UInt192& UInt192::operator=(const UInt192& other) {
    if (this != &other) {
        low = other.low;
        mid = other.mid;
        high = other.high;
    }
    return *this;
}

// Addition assignment operator
UInt192& UInt192::operator+=(const UInt192& other) {
    *this = *this + other;
    return *this;
}
// Multiplication assignment operator
UInt192& UInt192::operator*=(const UInt192& other) {
    *this = *this * other;
    return *this;
}
// Bitwise AND assignment operator
UInt192& UInt192::operator&=(const UInt192& other) {
    *this = *this & other;
    return *this;
}
// Bitwise OR assignment operator
UInt192& UInt192::operator|=(const UInt192& other) {
    *this = *this | other;
    return *this;
}
// Bitwise XOR assignment operator
UInt192& UInt192::operator^=(const UInt192& other) {
    *this = *this ^ other;
    return *this;
}
// Left shift assignment operator
UInt192& UInt192::operator<<=(const int shift) {
    *this = *this << shift;
    return *this;
}
// Right shift assignment operator
UInt192& UInt192::operator>>=(const int shift) {
    *this = *this >> shift;
    return *this;
}


// Comparison operators
bool UInt192::operator==(const UInt192& other) const {
    return low == other.low && mid == other.mid && high == other.high;
}
bool UInt192::operator!=(const UInt192& other) const {
    return !(*this == other);
}
bool UInt192::operator<(const UInt192& other) const {
    if (high != other.high) return high < other.high;
    if (mid != other.mid) return mid < other.mid;
    return low < other.low;
}
bool UInt192::operator<=(const UInt192& other) const {
    return *this < other || *this == other;
}
bool UInt192::operator>(const UInt192& other) const {
    return !(*this <= other);
}
bool UInt192::operator>=(const UInt192& other) const {
    return !(*this < other);
}

// Comparison operators with uint64_t
bool UInt192::operator==(const uint64_t& other) const {
    return low == other && mid == 0 && high == 0;
}
bool UInt192::operator!=(const uint64_t& other) const {
    return !(*this == other);
}
bool UInt192::operator<(const uint64_t& other) const {
    if (high != 0 || mid != 0) return false;
    return low < other;
}
bool UInt192::operator<=(const uint64_t& other) const {
    return *this < other || *this == other;
}
bool UInt192::operator>(const uint64_t& other) const {
    return !(*this <= other);
}
bool UInt192::operator>=(const uint64_t& other) const {
    return !(*this < other);
}

UInt192::operator bool() const {
    return (high != 0) || (mid != 0) || (low != 0);
}

UInt192::operator uint64_t() const {
    return low;
}

// Stream output operator for printing
std::ostream& operator<<(std::ostream& os, const UInt192& value) {
    if (value.high != 0) os << std::hex << value.high << std::setw(16) << std::setfill('0') << value.mid << std::setw(16) << std::setfill('0') << value.low;
    else if (value.mid != 0) os << std::hex << value.mid << std::setw(16) << std::setfill('0') << value.low;
    else os << std::hex << value.low;
    return os;
}
#ifndef ME0StubFinder_ME0StubFinder_UInt192_H
#define ME0StubFinder_ME0StubFinder_UInt192_H

#include <iostream>
#include <cstdint>
#include <iomanip>

class UInt192 {
private:
    uint64_t low;
    uint64_t mid;
    uint64_t high;

public:
    // Default constructor
    UInt192();

    // Constructor from three 64-bit values
    UInt192(uint64_t high, uint64_t mid, uint64_t low);

    // Constructor from a single uint64_t value
    UInt192(uint64_t value);

    // Copy constructor
    UInt192(const UInt192& other);

    // Addition and Multiplication operator
    UInt192 operator+(const UInt192& other) const;
    UInt192 operator*(const UInt192& other) const;

    // Bitwise operators
    UInt192 operator&(const UInt192& other) const;
    UInt192 operator|(const UInt192& other) const;
    UInt192 operator^(const UInt192& other) const;
    UInt192 operator~() const;
    UInt192 operator<<(int shift) const;
    UInt192 operator>>(int shift) const;

    // Assignment operator
    UInt192& operator=(const UInt192& other);    
    UInt192& operator+=(const UInt192& other);
    UInt192& operator*=(const UInt192& other);
    UInt192& operator&=(const UInt192& other);
    UInt192& operator|=(const UInt192& other);
    UInt192& operator^=(const UInt192& other);
    UInt192& operator<<=(const int shift);
    UInt192& operator>>=(const int shift);

    // Comparison operators
    bool operator==(const UInt192& other) const;
    bool operator!=(const UInt192& other) const;
    bool operator<(const UInt192& other) const;
    bool operator<=(const UInt192& other) const;
    bool operator>(const UInt192& other) const;
    bool operator>=(const UInt192& other) const;

    // Comparison operators with uint64_t
    bool operator==(const uint64_t& other) const;
    bool operator!=(const uint64_t& other) const;
    bool operator<(const uint64_t& other) const;
    bool operator<=(const uint64_t& other) const;
    bool operator>(const uint64_t& other) const;
    bool operator>=(const uint64_t& other) const;

    // bool
    explicit operator bool() const;
    
    // uint64_t
    explicit operator uint64_t() const;

    // Stream output operator for printing
    friend std::ostream& operator<<(std::ostream& os, const UInt192& value);
};

#endif // UINT192_H
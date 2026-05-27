#pragma once

#include <string>
#include <vector>
#include <iostream>

namespace biv {

class LongNumber {
public:
    LongNumber();
    LongNumber(const std::string& str);
    LongNumber(const char* str);
    LongNumber(const LongNumber& other) = default;
    LongNumber& operator=(const LongNumber& other) = default;

    // Comparison operators
    bool operator==(const LongNumber& other) const;
    bool operator!=(const LongNumber& other) const;
    bool operator<(const LongNumber& other) const;
    bool operator>(const LongNumber& other) const;
    bool operator<=(const LongNumber& other) const;
    bool operator>=(const LongNumber& other) const;

    // Arithmetic operators
    LongNumber operator+(const LongNumber& other) const;
    LongNumber operator-(const LongNumber& other) const;
    LongNumber operator*(const LongNumber& other) const;
    LongNumber operator/(const LongNumber& other) const;
    LongNumber operator%(const LongNumber& other) const;

    // Output
    friend std::ostream& operator<<(std::ostream& os, const LongNumber& n);
    std::string toString() const;

private:
    bool negative_;
    std::vector<int> digits_; // digits[0] = least significant digit

    void parse(const std::string& str);
    void trim();
    bool isZero() const;

    // Unsigned helpers (ignore sign)
    static int cmpAbs(const LongNumber& a, const LongNumber& b);
    static LongNumber addAbs(const LongNumber& a, const LongNumber& b);
    static LongNumber subAbs(const LongNumber& a, const LongNumber& b); // |a| >= |b|
    static LongNumber mulAbs(const LongNumber& a, const LongNumber& b);
    static LongNumber divAbs(const LongNumber& a, const LongNumber& b);
    static LongNumber modAbs(const LongNumber& a, const LongNumber& b);
};

} // namespace biv

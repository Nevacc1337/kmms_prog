#include "long_number.hpp"
#include <stdexcept>
#include <algorithm>

namespace biv {

LongNumber::LongNumber() : negative_(false), digits_{0} {}

LongNumber::LongNumber(const char* str) : LongNumber(std::string(str)) {}

LongNumber::LongNumber(const std::string& str) : negative_(false) {
    parse(str);
}

void LongNumber::parse(const std::string& str) {
    digits_.clear();
    if (str.empty()) throw std::invalid_argument("Empty string");

    size_t start = 0;
    if (str[0] == '-') { negative_ = true; start = 1; }
    else if (str[0] == '+') { start = 1; }
    else { negative_ = false; }

    for (size_t i = str.size(); i > start; --i) {
        char c = str[i - 1];
        if (c < '0' || c > '9') throw std::invalid_argument("Invalid character");
        digits_.push_back(c - '0');
    }
    trim();
    if (isZero()) negative_ = false;
}

void LongNumber::trim() {
    while (digits_.size() > 1 && digits_.back() == 0)
        digits_.pop_back();
}

bool LongNumber::isZero() const {
    return digits_.size() == 1 && digits_[0] == 0;
}

std::string LongNumber::toString() const {
    std::string s;
    if (negative_ && !isZero()) s += '-';
    for (int i = (int)digits_.size() - 1; i >= 0; --i)
        s += ('0' + digits_[i]);
    return s;
}

std::ostream& operator<<(std::ostream& os, const LongNumber& n) {
    return os << n.toString();
}

// cmpAbs: -1 if |a|<|b|, 0 if equal, 1 if |a|>|b|
int LongNumber::cmpAbs(const LongNumber& a, const LongNumber& b) {
    if (a.digits_.size() != b.digits_.size())
        return a.digits_.size() < b.digits_.size() ? -1 : 1;
    for (int i = (int)a.digits_.size() - 1; i >= 0; --i) {
        if (a.digits_[i] != b.digits_[i])
            return a.digits_[i] < b.digits_[i] ? -1 : 1;
    }
    return 0;
}

bool LongNumber::operator==(const LongNumber& o) const {
    if (isZero() && o.isZero()) return true;
    return negative_ == o.negative_ && digits_ == o.digits_;
}

bool LongNumber::operator!=(const LongNumber& o) const { return !(*this == o); }

bool LongNumber::operator<(const LongNumber& o) const {
    if (negative_ != o.negative_) return negative_;
    int c = cmpAbs(*this, o);
    return negative_ ? c > 0 : c < 0;
}

bool LongNumber::operator>(const LongNumber& o) const { return o < *this; }
bool LongNumber::operator<=(const LongNumber& o) const { return !(o < *this); }
bool LongNumber::operator>=(const LongNumber& o) const { return !(*this < o); }

// |a| + |b|
LongNumber LongNumber::addAbs(const LongNumber& a, const LongNumber& b) {
    LongNumber result;
    result.digits_.clear();
    int carry = 0;
    size_t n = std::max(a.digits_.size(), b.digits_.size());
    for (size_t i = 0; i < n || carry; ++i) {
        int sum = carry;
        if (i < a.digits_.size()) sum += a.digits_[i];
        if (i < b.digits_.size()) sum += b.digits_[i];
        result.digits_.push_back(sum % 10);
        carry = sum / 10;
    }
    return result;
}

// |a| - |b|, assumes |a| >= |b|
LongNumber LongNumber::subAbs(const LongNumber& a, const LongNumber& b) {
    LongNumber result;
    result.digits_.clear();
    int borrow = 0;
    for (size_t i = 0; i < a.digits_.size(); ++i) {
        int diff = a.digits_[i] - borrow;
        if (i < b.digits_.size()) diff -= b.digits_[i];
        if (diff < 0) { diff += 10; borrow = 1; } else borrow = 0;
        result.digits_.push_back(diff);
    }
    result.trim();
    return result;
}

LongNumber LongNumber::operator+(const LongNumber& o) const {
    LongNumber result;
    if (negative_ == o.negative_) {
        result = addAbs(*this, o);
        result.negative_ = negative_;
    } else {
        int c = cmpAbs(*this, o);
        if (c == 0) return LongNumber("0");
        if (c > 0) { result = subAbs(*this, o); result.negative_ = negative_; }
        else        { result = subAbs(o, *this); result.negative_ = o.negative_; }
    }
    if (result.isZero()) result.negative_ = false;
    return result;
}

LongNumber LongNumber::operator-(const LongNumber& o) const {
    LongNumber neg = o;
    neg.negative_ = !o.negative_;
    if (neg.isZero()) neg.negative_ = false;
    return *this + neg;
}

LongNumber LongNumber::mulAbs(const LongNumber& a, const LongNumber& b) {
    LongNumber result;
    result.digits_.assign(a.digits_.size() + b.digits_.size(), 0);
    for (size_t i = 0; i < a.digits_.size(); ++i) {
        int carry = 0;
        for (size_t j = 0; j < b.digits_.size() || carry; ++j) {
            long long cur = result.digits_[i + j] + carry;
            if (j < b.digits_.size()) cur += (long long)a.digits_[i] * b.digits_[j];
            result.digits_[i + j] = cur % 10;
            carry = cur / 10;
        }
    }
    result.trim();
    return result;
}

LongNumber LongNumber::operator*(const LongNumber& o) const {
    LongNumber result = mulAbs(*this, o);
    result.negative_ = negative_ != o.negative_;
    if (result.isZero()) result.negative_ = false;
    return result;
}

// Long division |a| / |b|
LongNumber LongNumber::divAbs(const LongNumber& a, const LongNumber& b) {
    if (b.isZero()) throw std::runtime_error("Division by zero");
    if (cmpAbs(a, b) < 0) return LongNumber("0");

    LongNumber quotient, current;
    quotient.digits_.assign(a.digits_.size(), 0);
    current.digits_.clear();

    for (int i = (int)a.digits_.size() - 1; i >= 0; --i) {
        // current = current * 10 + a.digits_[i]
        current.digits_.insert(current.digits_.begin(), a.digits_[i]);
        current.trim();

        // Find largest q such that b*q <= current
        int lo = 0, hi = 9, q = 0;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            LongNumber tmp = mulAbs(b, LongNumber(std::to_string(mid)));
            if (cmpAbs(tmp, current) <= 0) { q = mid; lo = mid + 1; }
            else hi = mid - 1;
        }
        quotient.digits_[i] = q;
        LongNumber tmp = mulAbs(b, LongNumber(std::to_string(q)));
        current = subAbs(current, tmp);
    }
    quotient.trim();
    return quotient;
}

LongNumber LongNumber::modAbs(const LongNumber& a, const LongNumber& b) {
    LongNumber q = divAbs(a, b);
    LongNumber prod = mulAbs(q, b);
    return subAbs(a, prod);
}

// Division uses Euclidean division:
//   r = a mod |b| >= 0,   a = q*b + r
// Table from tests:
//   100 /  6 =  16,  100 %  6 = 4
//   100 / -6 = -16,  100 % -6 = 4
//  -100 /  6 = -17, -100 %  6 = 2
//  -100 / -6 =  17, -100 % -6 = 2
// i.e. q = sign(b) * floor(a / |b|)
LongNumber LongNumber::operator/(const LongNumber& o) const {
    if (o.isZero()) throw std::runtime_error("Division by zero");

    // Euclidean quotient: q = floor(|a| / |b|) adjusted by sign
    // If a < 0 and remainder != 0, we need to add 1 to |q| to keep r >= 0
    LongNumber q = divAbs(*this, o);

    if (negative_) {
        // Check if remainder is nonzero
        LongNumber remainder = modAbs(*this, o);
        if (!remainder.isZero()) {
            LongNumber one("1");
            q = addAbs(q, one);
        }
    }

    q.negative_ = negative_ != o.negative_;
    if (q.isZero()) q.negative_ = false;
    return q;
}

LongNumber LongNumber::operator%(const LongNumber& o) const {
    if (o.isZero()) throw std::runtime_error("Division by zero");
    // Euclidean remainder: r = a - q*|b|, r >= 0
    LongNumber q = *this / o;
    // Use absolute value of o for reconstruction: a = q*b + r
    LongNumber prod = q * o;
    LongNumber r = *this - prod;
    // r should be >= 0 already due to Euclidean division
    if (r.negative_) {
        // Shouldn't happen, but safety net
        r.negative_ = false;
    }
    return r;
}

} // namespace biv

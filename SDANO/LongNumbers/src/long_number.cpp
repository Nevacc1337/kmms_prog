#include "long_number.hpp"
#include <stdexcept>
#include <cstring>
#include <algorithm>

using biv::LongNumber;


LongNumber::LongNumber() : numbers(new int[1]{0}), length(1), sign(1) {}

LongNumber::LongNumber(const char* const str) : numbers(nullptr), length(0), sign(1) {
    *this = str;
}

// ОПК
LongNumber::LongNumber(const LongNumber& x)
    : numbers(new int[x.length]), length(x.length), sign(x.sign) {
    for (int i = 0; i < length; ++i)
        numbers[i] = x.numbers[i];
}

// ОПП 
LongNumber::LongNumber(LongNumber&& x)
    : numbers(x.numbers), length(x.length), sign(x.sign) {
    x.numbers = nullptr;
    x.length  = 0;
    x.sign    = 1;
}

LongNumber::~LongNumber() {
    delete[] numbers;
}


// Присваивание из строки
LongNumber& LongNumber::operator=(const char* const str) {
    if (!str || str[0] == '\0')
        throw std::invalid_argument("Empty string");

    int start = 0;
    sign = 1;
    if (str[0] == '-') { sign = -1; start = 1; }
    else if (str[0] == '+') { start = 1; }

    // убрать ведущие нули
    while (str[start] == '0' && str[start + 1] != '\0') ++start;

    int len = get_length(str + start);
    for (int i = start; i < start + len; ++i)
        if (str[i] < '0' || str[i] > '9')
            throw std::invalid_argument("Invalid character");

    delete[] numbers;
    length  = len;
    numbers = new int[length];

    for (int i = 0; i < length; ++i)
        numbers[i] = str[start + length - 1 - i] - '0';

    bool isZero = (length == 1 && numbers[0] == 0);
    if (isZero) sign = 1;

    return *this;
}

LongNumber& LongNumber::operator=(const LongNumber& x) {
    if (this == &x) return *this;
    delete[] numbers;
    length  = x.length;
    sign    = x.sign;
    numbers = new int[length];
    for (int i = 0; i < length; ++i)
        numbers[i] = x.numbers[i];
    return *this;
}

LongNumber& LongNumber::operator=(LongNumber&& x) {
    if (this == &x) return *this;
    delete[] numbers;
    numbers  = x.numbers;
    length   = x.length;
    sign     = x.sign;
    x.numbers = nullptr;
    x.length  = 0;
    x.sign    = 1;
    return *this;
}


int LongNumber::get_length(const char* const str) const noexcept {
    int n = 0;
    while (str[n] != '\0') ++n;
    return n;
}

bool LongNumber::is_negative() const noexcept {
    return sign == -1;
}

// cmpAbs: -1 если |a|<|b|, 0 равны, 1 если |a|>|b|
int LongNumber::cmpAbs(const LongNumber& a, const LongNumber& b) {
    if (a.length != b.length)
        return a.length < b.length ? -1 : 1;
    for (int i = a.length - 1; i >= 0; --i) {
        if (a.numbers[i] != b.numbers[i])
            return a.numbers[i] < b.numbers[i] ? -1 : 1;
    }
    return 0;
}

// |a| + |b|
LongNumber LongNumber::addAbs(const LongNumber& a, const LongNumber& b) {
    int maxLen = std::max(a.length, b.length);
    LongNumber result;
    delete[] result.numbers;
    result.numbers = new int[maxLen + 1]();
    result.length  = maxLen;

    int carry = 0;
    for (int i = 0; i < maxLen || carry; ++i) {
        int sum = carry;
        if (i < a.length) sum += a.numbers[i];
        if (i < b.length) sum += b.numbers[i];
        if (i < maxLen) {
            result.numbers[i] = sum % 10;
        } else {
            // нужен лишний разряд
            int* tmp = new int[result.length + 1];
            for (int j = 0; j < result.length; ++j) tmp[j] = result.numbers[j];
            tmp[result.length] = sum % 10;
            delete[] result.numbers;
            result.numbers = tmp;
            result.length++;
        }
        carry = sum / 10;
    }
    return result;
}

// |a| - |b|, предполагается |a| >= |b|
LongNumber LongNumber::subAbs(const LongNumber& a, const LongNumber& b) {
    LongNumber result;
    delete[] result.numbers;
    result.numbers = new int[a.length]();
    result.length  = a.length;

    int borrow = 0;
    for (int i = 0; i < a.length; ++i) {
        int diff = a.numbers[i] - borrow;
        if (i < b.length) diff -= b.numbers[i];
        if (diff < 0) { diff += 10; borrow = 1; } else borrow = 0;
        result.numbers[i] = diff;
    }
    // убрать ведущие нули
    while (result.length > 1 && result.numbers[result.length - 1] == 0)
        --result.length;
    return result;
}

// |a| * |b|
LongNumber LongNumber::mulAbs(const LongNumber& a, const LongNumber& b) {
    int resLen = a.length + b.length;
    LongNumber result;
    delete[] result.numbers;
    result.numbers = new int[resLen]();
    result.length  = resLen;

    for (int i = 0; i < a.length; ++i) {
        int carry = 0;
        for (int j = 0; j < b.length || carry; ++j) {
            long long cur = result.numbers[i + j] + carry;
            if (j < b.length) cur += (long long)a.numbers[i] * b.numbers[j];
            result.numbers[i + j] = (int)(cur % 10);
            carry = (int)(cur / 10);
        }
    }
    while (result.length > 1 && result.numbers[result.length - 1] == 0)
        --result.length;
    return result;
}

// |a| / |b|
LongNumber LongNumber::divAbs(const LongNumber& a, const LongNumber& b) {
    if (b.length == 1 && b.numbers[0] == 0)
        throw std::runtime_error("Division by zero");
    if (cmpAbs(a, b) < 0) return LongNumber("0");

    LongNumber quotient;
    delete[] quotient.numbers;
    quotient.numbers = new int[a.length]();
    quotient.length  = a.length;

    LongNumber current("0");

    for (int i = a.length - 1; i >= 0; --i) {
        // current = current * 10 + a.numbers[i]
        int* tmp = new int[current.length + 1];
        tmp[0] = a.numbers[i];
        for (int j = 0; j < current.length; ++j) tmp[j + 1] = current.numbers[j];
        delete[] current.numbers;
        current.numbers = tmp;
        current.length++;
        // убрать ведущие нули
        while (current.length > 1 && current.numbers[current.length - 1] == 0)
            --current.length;

        int lo = 0, hi = 9, q = 0;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            char buf[3]; buf[0] = '0' + mid; buf[1] = '\0';
            LongNumber midN(buf);
            LongNumber tmp2 = mulAbs(b, midN);
            if (cmpAbs(tmp2, current) <= 0) { q = mid; lo = mid + 1; }
            else hi = mid - 1;
        }
        quotient.numbers[i] = q;

        char buf[3]; buf[0] = '0' + q; buf[1] = '\0';
        LongNumber qN(buf);
        LongNumber sub = mulAbs(b, qN);
        current = subAbs(current, sub);
    }
    while (quotient.length > 1 && quotient.numbers[quotient.length - 1] == 0)
        --quotient.length;
    return quotient;
}


bool LongNumber::operator==(const LongNumber& x) const {
    bool aZero = (length == 1 && numbers[0] == 0);
    bool bZero = (x.length == 1 && x.numbers[0] == 0);
    if (aZero && bZero) return true;
    if (sign != x.sign) return false;
    if (length != x.length) return false;
    for (int i = 0; i < length; ++i)
        if (numbers[i] != x.numbers[i]) return false;
    return true;
}

bool LongNumber::operator!=(const LongNumber& x) const { return !(*this == x); }

bool LongNumber::operator<(const LongNumber& x) const {
    if (sign != x.sign) return sign < x.sign;
    int c = cmpAbs(*this, x);
    return sign == 1 ? c < 0 : c > 0;
}

bool LongNumber::operator>(const LongNumber& x) const { return x < *this; }


LongNumber LongNumber::operator+(const LongNumber& x) const {
    LongNumber result;
    if (sign == x.sign) {
        result = addAbs(*this, x);
        result.sign = sign;
    } else {
        int c = cmpAbs(*this, x);
        if (c == 0) return LongNumber("0");
        if (c > 0) { result = subAbs(*this, x); result.sign = sign; }
        else       { result = subAbs(x, *this); result.sign = x.sign; }
    }
    if (result.length == 1 && result.numbers[0] == 0) result.sign = 1;
    return result;
}

LongNumber LongNumber::operator-(const LongNumber& x) const {
    LongNumber neg = x;
    neg.sign = (x.length == 1 && x.numbers[0] == 0) ? 1 : -x.sign;
    return *this + neg;
}

LongNumber LongNumber::operator*(const LongNumber& x) const {
    LongNumber result = mulAbs(*this, x);
    result.sign = sign * x.sign;
    if (result.length == 1 && result.numbers[0] == 0) result.sign = 1;
    return result;
}

LongNumber LongNumber::operator/(const LongNumber& x) const {
    if (x.length == 1 && x.numbers[0] == 0)
        throw std::runtime_error("Division by zero");

    LongNumber q = divAbs(*this, x);

    // Евклидово деление: остаток >= 0
    // Если делимое отрицательное и остаток != 0 — прибавить 1 к |q|
    if (sign == -1) {
        LongNumber rem = subAbs(*this, mulAbs(q, x));
        // rem тут по модулю
        bool remZero = (rem.length == 1 && rem.numbers[0] == 0);
        if (!remZero) {
            LongNumber one("1");
            q = addAbs(q, one);
        }
    }

    q.sign = sign * x.sign;
    if (q.length == 1 && q.numbers[0] == 0) q.sign = 1;
    return q;
}

LongNumber LongNumber::operator%(const LongNumber& x) const {
    if (x.length == 1 && x.numbers[0] == 0)
        throw std::runtime_error("Division by zero");
    LongNumber q = *this / x;
    LongNumber r = *this - q * x;
    if (r.sign == -1) r.sign = 1; // евклидов остаток >= 0
    return r;
}


namespace biv {
    std::ostream& operator<<(std::ostream& os, const LongNumber& x) {
        if (x.sign == -1 && !(x.length == 1 && x.numbers[0] == 0))
            os << '-';
        for (int i = x.length - 1; i >= 0; --i)
            os << x.numbers[i];
        return os;
    }
}

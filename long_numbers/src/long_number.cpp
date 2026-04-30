#include "long_number.hpp"

using hatkid::LongNumber;

const LongNumber LongNumber::ZERO{};
const LongNumber LongNumber::ONE{"1"};
		
LongNumber::LongNumber() {
    numbers = new int[1];
    numbers[0] = 0;
    length = 1;
    sign = 0;
}

LongNumber::LongNumber(int num,int len){
    if (num == 0){
        sign = 0;
        length = 1;
        numbers = new int[len];
    } else{
        sign = 1;
        length = len;
        numbers = new int[len];
        
        for (int i = len-1; i >= 0; i--){
            numbers[i] = num % 10;
            num /= 10;
        }
    }
}

LongNumber::LongNumber(const char* const str) {
    length = getLength(str);
    sign = getSign(str);
    numbers = new int[length];
    int t = (sign == -1) ? 1 : 0;
    for (int i = 0; i < length;i++){
        char c = str[i+t];
        numbers[i] = c - '0';
    }
}

LongNumber::LongNumber(const LongNumber& x) {
	length = x.length;
    sign = x.sign;
    numbers = new int[length];

    for (int i = 0; i < length; i++){
        numbers[i] = x.numbers[i];
    }
}

LongNumber::LongNumber(LongNumber&& x) {
    length = x.length;
    sign = x.sign;

    numbers = x.numbers;
    x.numbers = nullptr;
}

LongNumber::~LongNumber() {
    delete[] numbers;
}

LongNumber& LongNumber::operator = (const char* const str) {
    delete[] numbers;
    
    length = getLength(str);
    sign = getSign(str);
    numbers = new int[length];
    int t = (sign == -1) ? 1 : 0;
    for (int i = 0; i < length; i++){
        char c = str[i+t];
        numbers[i] = c - '0';
    }
    return *this;
}

LongNumber& LongNumber::operator = (const LongNumber& x) {
    if (this == &x){
        return *this;
    }
    delete[] numbers;

    length = x.length;
    sign = x.sign;
    numbers = new int[length];
    for (int i = 0; i < length; i++){
        numbers[i] = x.numbers[i];
    }
    return *this;
}

LongNumber& LongNumber::operator = (LongNumber&& x) {
    if (this == &x) return *this;

    delete[] numbers;

	numbers = x.numbers;
    x.numbers = nullptr;

    length = x.length;
    sign = x.sign;
    
    return *this;
}

bool LongNumber::operator == (const LongNumber& x) const {	
    return !compare(*this,x);
}

bool LongNumber::operator != (const LongNumber& x) const {
    return compare(*this,x);
}

bool LongNumber::operator > (const LongNumber& x) const {
    return compare(*this,x) == -1;
}

bool LongNumber::operator < (const LongNumber& x) const {
    return compare(*this,x) == 1;
}

LongNumber LongNumber::operator + (const LongNumber& x) const {
    if (sign == 0) return x;
    if (x.sign == 0) return *this;

    if (sign == x.sign){
        if (absolute(*this) > absolute(x)){
            return add(*this,x);
        } else{
            return add(x,*this);
        }
    }

    LongNumber left = absolute(*this);
    LongNumber right = absolute(x);

    if (left == right){
        return ZERO;
    }
    int resultSign = 0;
    if (left > right){
        resultSign = sign;
    } else{
        resultSign = x.sign;
    }
    
    if (left > right){
        LongNumber result = subtract(left,right);
        result.sign = resultSign;
        return result;
    }
    LongNumber result = subtract(right,left);
    result.sign = resultSign;
    return result;

}

LongNumber LongNumber::operator - (const LongNumber& x) const {

    LongNumber n(x);
    if (n.sign != 0){
        n.sign = -n.sign;
    }
    return *this + n;

}

LongNumber LongNumber::operator * (const LongNumber& x) const {

    if (this == &ZERO or x == ZERO){
        return ZERO;
    }

    int resultSign = sign * x.sign;

	int leftInd = length-1;
    int rightInd = x.length-1;

    LongNumber result;

    LongNumber left = absolute(*this);
    LongNumber right = absolute(x);

    int shift1 = 0;

    for (int i = leftInd; i >= 0; i--){
        int rem = 0;
        LongNumber temp;
        int shift = 0;
        for (int j = rightInd; j >= 0; j--){
            int n = left.numbers[i] * right.numbers[j] + rem;
            rem = n / 10;
            temp = temp + shiftLeft(shift,LongNumber(n % 10,1));
            shift++; 
        }

        if (rem != 0){
            temp = temp + shiftLeft(shift,LongNumber(rem,1));
        }

        result = result + shiftLeft(shift1,temp);

        shift1++;
    }
    result.sign = resultSign;

    return normalize(result);
}

LongNumber LongNumber::operator / (const LongNumber& x) const {

    if (sign == 0){
        return ZERO;
    }

    if (x == ONE){
        return *this;
    }

    int resultSign = sign * x.sign;
    
    if (x == LongNumber{"-1"}){
        LongNumber result{*this};
        result.sign = resultSign;
        return result;
    }

    LongNumber left = absolute(*this);
    LongNumber right = absolute(x);

    if (left < right) {
        return ZERO;
    }

    LongNumber d;
    LongNumber result;

    for (int i = 0; i < left.length; i++){
        
        d = shiftLeft(1,d) + LongNumber{left.numbers[i],1};

        LongNumber r;
        while (d + ONE > right){
            d = d - right;
            r = r + ONE;
        }

        result = shiftLeft(1,result) + r;

    }

    if (d != ZERO and sign == -1){
        result = result + ONE;
    }
    
    if (result != ZERO){
        result.sign = resultSign;
    }
    
    return result;

}

LongNumber LongNumber::operator % (const LongNumber& x) const {

    if (x == ONE){
        return ZERO;
    }

    LongNumber d = *this / x;

    return *this - (d * x);
}

bool LongNumber::isNegative() const noexcept {
	if (sign == -1){
        return true;
    }
    return false;
}

LongNumber LongNumber::absolute(const LongNumber& x) const {
    LongNumber result(x);
    if (x.sign == -1){
        result.sign = 1;
    }
    return result;
}

// ----------------------------------------------------------
// PRIVATE
// ----------------------------------------------------------

LongNumber LongNumber::normalize(const LongNumber& x) const noexcept{
    int resultLength = x.length;
    for (int i = 0; i < x.length; i++){
        if (x.numbers[i] == 0){
            resultLength--;
        } else{
            break;
        }
    }

    if (resultLength == 0){
        return ZERO;
    }

    LongNumber result;
    delete[] result.numbers;
    result.numbers = new int[resultLength];

    int dif = x.length - resultLength;
    
    for (int i = 0; i < resultLength; i++){
        result.numbers[i] = x.numbers[i+dif];
    }

    result.sign = x.sign;
    result.length = resultLength;
    return result;

}

LongNumber LongNumber::shiftLeft(int shiftNum,const LongNumber& x) const noexcept{
    if (shiftNum == 0){
        return x;
    }
    int resultLength = x.length + shiftNum;
    LongNumber result;
    delete[] result.numbers;

    result.numbers = new int[resultLength];

    result.sign = x.sign;
    result.length = resultLength;

    for (int i = 0; i < x.length; i++){
        result.numbers[i] = x.numbers[i];
    }

    for (int i = x.length; i < resultLength;i++){
        result.numbers[i] = 0;
    }

    return result;
}

int LongNumber::getLength(const char* const str) const noexcept {
    int len = 0;
    while (str[len] != '\0'){
        len++;
    }

    if (str[0] == '-'){
        len--;
    }
    return len;
}

int LongNumber::getSign(const char* const str) const noexcept {
    if (str[0] == '-'){
        return -1;
    } else if (str[0] == '0'){
        return 0;
    }
    return 1;
}

int LongNumber::compare(const LongNumber& left, const LongNumber& right) const noexcept{

    if (left.sign != right.sign){
        return (left.sign == -1) ? 1 : -1;
    }

    int result = 0;

    if (left.length > right.length){
        result = -1;
    } else if (left.length < right.length){
        result = 1;
    } else{
        for (int i = 0; i < left.length; i++){
            if (left.numbers[i] > right.numbers[i]){
                result = -1;
                break;
            } else if (left.numbers[i] < right.numbers[i]){
                result = 1;
                break;
            }
        }
    }

    if (left.sign == -1 and result != 0){
        return -(result);
    }

    return result;
}

LongNumber LongNumber::add(const LongNumber& left, const LongNumber& right) const noexcept{
    int* num = new int[left.length];
    int i = left.length - 1;
    int j = right.length - 1;

    int rem = 0;

    while (i >= 0){
        if (j < 0){
            num[i] = ( left.numbers[i] + rem) % 10;
            rem = (left.numbers[i] + rem) / 10;
        } else{
            num[i] = (left.numbers[i] + right.numbers[j] + rem) % 10;
            rem = (left.numbers[i] + right.numbers[j] + rem) / 10;
        }
        i--;
        j--;
    }

    int* resultNum;
    int resultLength = left.length;

    if (rem != 0){
        resultNum = new int[left.length+1];
        resultNum[0] = rem;
        for (int i = 0; i < left.length; i++){
            resultNum[i+1] = num[i];
        }
        resultLength++;
        delete[] num;
    } else{
        resultNum = num; 
    }

    LongNumber result;
    delete[] result.numbers;

    result.numbers = resultNum;
    result.sign = sign;
    result.length = resultLength;
    return result;
    
}

LongNumber LongNumber::subtract(const LongNumber& left, const LongNumber& right) const noexcept{
    
    int* num = new int[left.length];
    int i = left.length - 1;
    int j = right.length - 1;

    bool rem = 0;

    while (i >= 0){
        int up = left.numbers[i] - rem;
        int down = (j < 0) ? 0 : right.numbers[j];
        if (up >= down){
            num[i] = up - down;
            rem = 0;
        } else{
            num[i] = up+10-down;
            rem = 1;
        }
        i--;
        j--;
    }


    int resultLength = left.length;
    for (int i = 0; i < left.length; i++){
        if (num[i] == 0){
            resultLength--;
        } else{
            break;
        }
    }

    if (resultLength == 0){
        return ZERO;
    }
    
    int dif = left.length - resultLength;


    int* resultNum = new int[resultLength];
    for (int i = 0; i < resultLength; i++){
        resultNum[i] = num[i+dif];
    }
    delete[] num;

    LongNumber result;
    delete[] result.numbers;


    result.numbers = resultNum;
    result.length = resultLength;

    return result;
}

// ----------------------------------------------------------
// FRIENDLY
// ----------------------------------------------------------
namespace hatkid {
	std::ostream& operator << (std::ostream &os, const LongNumber& x) {
        if (x.sign == -1){
            os << '-';
        }
	    for (int i = 0; i < x.length; i++){
            os << x.numbers[i];
        }
        return os;
    }
}

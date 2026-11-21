#pragma once
#include <iostream>

namespace biv {
    class LongNumber {
        private:
            int* numbers; 
            int length;
            int sign;     

        public:
            LongNumber();
            LongNumber(const char* const str);
            LongNumber(const LongNumber& x);   
            LongNumber(LongNumber&& x);         

            ~LongNumber();

            LongNumber& operator = (const char* const str);
            LongNumber& operator = (const LongNumber& x);  // ОПК
            LongNumber& operator = (LongNumber&& x);        // ОПП

            bool operator == (const LongNumber& x) const;
            bool operator != (const LongNumber& x) const;
            bool operator >  (const LongNumber& x) const;
            bool operator <  (const LongNumber& x) const;

            LongNumber operator + (const LongNumber& x) const;
            LongNumber operator - (const LongNumber& x) const;
            LongNumber operator * (const LongNumber& x) const;
            LongNumber operator / (const LongNumber& x) const;
            LongNumber operator % (const LongNumber& x) const;

            bool is_negative() const noexcept;

            friend std::ostream& operator << (std::ostream& os, const LongNumber& x);

        private:
            int get_length(const char* const str) const noexcept;

            static int  cmpAbs(const LongNumber& a, const LongNumber& b);
            static LongNumber addAbs(const LongNumber& a, const LongNumber& b);
            static LongNumber subAbs(const LongNumber& a, const LongNumber& b); // |a|>=|b|
            static LongNumber mulAbs(const LongNumber& a, const LongNumber& b);
            static LongNumber divAbs(const LongNumber& a, const LongNumber& b);
    };
}

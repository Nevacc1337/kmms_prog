#pragma once
#include <iostream>

namespace hatkid {
	class LongNumber {
		private:
			int* numbers;
			int length;
			int sign;
		
		public:

            static const LongNumber ZERO;
            static const LongNumber ONE;

			LongNumber();
            LongNumber(int num,int length);
			LongNumber(const char* const str);
			LongNumber(const LongNumber& x);
			LongNumber(LongNumber&& x);
			
			~LongNumber();
			
			LongNumber& operator = (const char* const str);
			LongNumber& operator = (const LongNumber& x);
			LongNumber& operator = (LongNumber&& x);
			
			bool operator == (const LongNumber& x) const;
			bool operator != (const LongNumber& x) const;
			bool operator > (const LongNumber& x) const;
			bool operator < (const LongNumber& x) const;
			
			LongNumber operator + (const LongNumber& x) const;
			LongNumber operator - (const LongNumber& x) const;
			LongNumber operator * (const LongNumber& x) const;
			LongNumber operator / (const LongNumber& x) const;
			LongNumber operator % (const LongNumber& x) const;
			
            LongNumber absolute(const LongNumber& x) const;

            bool isNegative() const noexcept;
			
			friend std::ostream& operator << (std::ostream &os, const LongNumber& x);
			
		private:
            LongNumber normalize(const LongNumber& x) const noexcept;
            LongNumber shiftLeft(int shiftNum, const LongNumber& x) const noexcept;
            LongNumber subtract(const LongNumber& left, const LongNumber& right) const noexcept;
            LongNumber add(const LongNumber& left, const LongNumber& right) const noexcept;
			int getLength(const char* const str) const noexcept;
            int getSign(const char* const str) const noexcept;
            int compare(const LongNumber& left, const LongNumber& right) const noexcept;
	};
}

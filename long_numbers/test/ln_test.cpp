#include <gtest/gtest.h>

#include "long_number.hpp"

const hatkid::LongNumber ONE{"1"};
const hatkid::LongNumber ZERO{};
const hatkid::LongNumber VAL_101{"101"};
const hatkid::LongNumber VAL_99{"99"};
const hatkid::LongNumber VAL_2{"2"};
const hatkid::LongNumber VAL_2_NEG{"-2"};
const hatkid::LongNumber VAL_4{"4"};
const hatkid::LongNumber VAL_4_NEG{"-4"};
const hatkid::LongNumber ONE_NEG{"-1"};
const hatkid::LongNumber VAL_123{"123"};
const hatkid::LongNumber VAL_123_COPY{"123"};
const hatkid::LongNumber VAL_123_NEG{"-123"};
const hatkid::LongNumber VAL_124{"124"};
const hatkid::LongNumber VAL_124_NEG{"-124"};
const hatkid::LongNumber VAL_50{"50"};
const hatkid::LongNumber VAL_50_NEG{"-50"};
const hatkid::LongNumber VAL_100{"100"};
const hatkid::LongNumber VAL_7{"7"};
const hatkid::LongNumber VAL_15{"15"};
const hatkid::LongNumber VAL_15_NEG{"-15"};
const hatkid::LongNumber VAL_7_NEG{"-7"};
const hatkid::LongNumber VAL_3{"3"};
const hatkid::LongNumber VAL_3_NEG{"-3"};


const hatkid::LongNumber BIG_VAL_1{"1233123124213413511351435135215454325215152532452415431"};
const hatkid::LongNumber BIG_VAL_2{"535352454254525325543543543"};
const hatkid::LongNumber MUL_RESULT{"660155490945658807644438211285718376820008214910449744742460003384898437273612033"};
const hatkid::LongNumber DIV_RESULT{"2303385581617495576732590615"};
const hatkid::LongNumber ADD_RESULT{"1233123124213413511351435135750806779469677857995958974"};
const hatkid::LongNumber SUB_RESULT{"1233123124213413511351435134680101870960627206908871888"};
const hatkid::LongNumber REM_RESULT{"416420834276266991006766486"};

// Constructors

TEST(LongNumberTest, DefaultConstructor){
   
    hatkid::LongNumber def;

    EXPECT_FALSE(def.isNegative());
    
    EXPECT_EQ(def,ZERO);

}

TEST(LongNumberTest, StringConstructor){
    hatkid::LongNumber test123("123");
    hatkid::LongNumber test123Neg("-123");
    
    EXPECT_FALSE(test123.isNegative());
    EXPECT_TRUE(test123Neg.isNegative());

    EXPECT_EQ(test123,VAL_123);
    EXPECT_EQ(test123Neg, VAL_123_NEG);

}

TEST(LongNumberTest, CustomConstructor){
    hatkid::LongNumber test1(1,1);
    hatkid::LongNumber test123(123,3);

    EXPECT_EQ(test1,ONE);
    EXPECT_EQ(test123,VAL_123);

}

// Assignments

TEST(LongNumberTest, StringAssigment){
    
    hatkid::LongNumber testZero;
    hatkid::LongNumber test123;
    hatkid::LongNumber test123Neg;

    testZero = "0";
    test123 = "123";
    test123Neg = "-123";

    EXPECT_EQ(testZero, ZERO);
    EXPECT_EQ(test123, VAL_123);
    EXPECT_EQ(test123Neg, VAL_123_NEG);

}

TEST(LongNumberTest, CopyAssigment){

    hatkid::LongNumber testZero;
    hatkid::LongNumber test123;
    hatkid::LongNumber test123Neg;

    testZero = ZERO;
    test123 = VAL_123;
    test123Neg = VAL_123_NEG;

    EXPECT_EQ(testZero, ZERO);
    EXPECT_EQ(test123, VAL_123);
    EXPECT_EQ(test123Neg, VAL_123_NEG);

}

TEST(LongNumberTest, MoveAssigment){

    hatkid::LongNumber test123 = hatkid::LongNumber{"123"};

    EXPECT_EQ(test123, VAL_123);
    
}

// Comparation

TEST(LongNumberTest, ComparationEqual){
    
    EXPECT_TRUE(VAL_123 == VAL_123_COPY);
    EXPECT_FALSE(ONE == ZERO);
    EXPECT_FALSE(VAL_123 == VAL_123_NEG);
    EXPECT_TRUE(ZERO == ZERO);

}

TEST(LongNumberTest, ComparationNotEqual){
    
    EXPECT_FALSE(VAL_123 != VAL_123_COPY);
    EXPECT_TRUE(ONE != ZERO);
    EXPECT_TRUE(VAL_123 != VAL_123_NEG);
    EXPECT_FALSE(ZERO != ZERO);

}

TEST(LongNumberTest, ComparationGreater){

    EXPECT_TRUE(VAL_124 > VAL_123);
    EXPECT_TRUE(VAL_123 > VAL_123_NEG);
    EXPECT_TRUE(ONE > ZERO);
    EXPECT_FALSE(VAL_123 > VAL_123_COPY);
    EXPECT_FALSE(VAL_123_NEG > VAL_123);

}

TEST(LongNumberTest, ComparationLess){

    EXPECT_TRUE(VAL_123_NEG < VAL_123);
    EXPECT_FALSE(VAL_124 <  VAL_123);
    EXPECT_FALSE(ZERO < ZERO);
    EXPECT_FALSE(ONE < ZERO);
    EXPECT_FALSE(ONE < ONE_NEG);
    EXPECT_TRUE(VAL_124_NEG < ZERO);

}

// Operations

TEST(LongNumberTest, AddOperation){

    EXPECT_EQ(ONE + ONE, VAL_2);
    EXPECT_EQ(VAL_99 + VAL_2, VAL_101);
    EXPECT_EQ(ONE + ZERO, ONE);

    EXPECT_EQ(ONE + ONE_NEG, ZERO);
    EXPECT_EQ(VAL_124 + ONE_NEG, VAL_123);
    EXPECT_EQ(VAL_124_NEG + ONE, VAL_123_NEG);
    EXPECT_EQ(VAL_123_NEG + ONE_NEG, VAL_124_NEG);

    EXPECT_EQ(VAL_50 + VAL_50, VAL_100);
    EXPECT_EQ(VAL_50_NEG + VAL_100, VAL_50);

    EXPECT_EQ(BIG_VAL_1 + BIG_VAL_2,ADD_RESULT);

}

TEST(LongNumberTest, SubtractOperation){

    EXPECT_EQ(VAL_4 - VAL_2, VAL_2);
    EXPECT_EQ(VAL_4_NEG - VAL_2_NEG, VAL_2_NEG);

    EXPECT_EQ(VAL_124 - ONE, VAL_123);
    EXPECT_EQ(VAL_124_NEG - ONE_NEG, VAL_123_NEG);
    EXPECT_EQ(VAL_101 - VAL_2, VAL_99);

    EXPECT_EQ(VAL_50 - VAL_100, VAL_50_NEG);

    EXPECT_EQ(BIG_VAL_1 - BIG_VAL_2, SUB_RESULT);

}

TEST(LongNumberTest, MultiplyOperation){
    
    EXPECT_EQ(VAL_2 * VAL_2, VAL_4);
    EXPECT_EQ(VAL_2 * ONE_NEG, VAL_2_NEG);
    EXPECT_EQ(VAL_2 * VAL_2_NEG, VAL_4_NEG);
    EXPECT_EQ(VAL_2_NEG * VAL_2_NEG, VAL_4);

    EXPECT_EQ(VAL_123 * ZERO, ZERO);
    EXPECT_EQ(VAL_124 * ZERO, ZERO);
    EXPECT_EQ(VAL_123_NEG * ZERO, ZERO);
    
    EXPECT_EQ(VAL_2 * VAL_50, VAL_100);

    EXPECT_EQ(BIG_VAL_1 * BIG_VAL_2, MUL_RESULT);

}

TEST (LongNumberTest, DivideOperation){
    
    EXPECT_EQ(VAL_4 / VAL_2, VAL_2);
    EXPECT_EQ(VAL_4 / VAL_2_NEG, VAL_2_NEG);
    EXPECT_EQ(VAL_4_NEG / VAL_2, VAL_2_NEG);
    EXPECT_EQ(VAL_4_NEG / VAL_2_NEG, VAL_2);
    
    EXPECT_EQ(VAL_2 / VAL_4, ZERO);
    EXPECT_EQ(VAL_123 / ONE, VAL_123);
    EXPECT_EQ(VAL_101 / VAL_2, VAL_50);

    EXPECT_EQ(BIG_VAL_1 / BIG_VAL_2, DIV_RESULT);

    EXPECT_EQ(VAL_15 / VAL_4, VAL_3);
    EXPECT_EQ(VAL_15 / VAL_4_NEG, VAL_3_NEG);
    EXPECT_EQ(VAL_15_NEG / VAL_4, VAL_4_NEG);
    EXPECT_EQ(VAL_15_NEG / VAL_4_NEG, VAL_4);

}

TEST(LongNumberTest, ReminderOperation){

    EXPECT_EQ(VAL_101 % VAL_2, ONE);
    EXPECT_EQ(VAL_2 % VAL_4, VAL_2);
    EXPECT_EQ(VAL_123 % ONE, ZERO);

    EXPECT_EQ(BIG_VAL_1 % BIG_VAL_2,REM_RESULT);

    EXPECT_EQ(VAL_7 % VAL_3, ONE);
    EXPECT_EQ(VAL_7_NEG % VAL_3, VAL_2);
    EXPECT_EQ(VAL_7 % VAL_3_NEG, ONE);
    EXPECT_EQ(VAL_7_NEG % VAL_3_NEG, VAL_2);

}

#include <gtest/gtest.h>

#include "vector.hpp"

using biv::Vector;

// --- get_size ---

TEST(VectorTest, SizeInitiallyZero) {
	Vector<int> v;
	EXPECT_EQ(v.get_size(), 0u);
}

TEST(VectorTest, SizeAfterPushBack) {
	Vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	EXPECT_EQ(v.get_size(), 3u);
}

// --- has_item ---

TEST(VectorTest, HasItemEmpty) {
	Vector<int> v;
	EXPECT_FALSE(v.has_item(42));
}

TEST(VectorTest, HasItemPresent) {
	Vector<int> v;
	v.push_back(10);
	v.push_back(20);
	EXPECT_TRUE(v.has_item(10));
	EXPECT_TRUE(v.has_item(20));
}

TEST(VectorTest, HasItemAbsent) {
	Vector<int> v;
	v.push_back(10);
	EXPECT_FALSE(v.has_item(99));
}

// --- push_back ---

TEST(VectorTest, PushBackIncreasesSize) {
	Vector<int> v;
	for (int i = 0; i < 10; ++i) {
		v.push_back(i);
	}
	EXPECT_EQ(v.get_size(), 10u);
}

TEST(VectorTest, PushBackBeyondInitialCapacity) {
	Vector<int> v;
	for (int i = 0; i < 20; ++i) {
		v.push_back(i);
	}
	EXPECT_EQ(v.get_size(), 20u);
	EXPECT_TRUE(v.has_item(19));
}

// --- insert ---

TEST(VectorTest, InsertAtBegin) {
	Vector<int> v;
	v.push_back(2);
	v.push_back(3);
	bool result = v.insert(0, 1);
	EXPECT_TRUE(result);
	EXPECT_EQ(v.get_size(), 3u);
	EXPECT_TRUE(v.has_item(1));
}

TEST(VectorTest, InsertAtEnd) {
	Vector<int> v;
	v.push_back(1);
	v.push_back(2);
	bool result = v.insert(2, 3);
	EXPECT_TRUE(result);
	EXPECT_EQ(v.get_size(), 3u);
	EXPECT_TRUE(v.has_item(3));
}

TEST(VectorTest, InsertInvalidPosition) {
	Vector<int> v;
	v.push_back(1);
	bool result = v.insert(5, 99);
	EXPECT_FALSE(result);
	EXPECT_EQ(v.get_size(), 1u);
}

// --- remove_first ---

TEST(VectorTest, RemoveFirstPresent) {
	Vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	bool result = v.remove_first(2);
	EXPECT_TRUE(result);
	EXPECT_EQ(v.get_size(), 2u);
	EXPECT_FALSE(v.has_item(2));
}

TEST(VectorTest, RemoveFirstAbsent) {
	Vector<int> v;
	v.push_back(1);
	bool result = v.remove_first(99);
	EXPECT_FALSE(result);
	EXPECT_EQ(v.get_size(), 1u);
}

TEST(VectorTest, RemoveFirstOnlyFirst) {
	Vector<int> v;
	v.push_back(5);
	v.push_back(5);
	v.push_back(5);
	bool result = v.remove_first(5);
	EXPECT_TRUE(result);
	EXPECT_EQ(v.get_size(), 2u);
	EXPECT_TRUE(v.has_item(5));
}

TEST(VectorTest, RemoveFromEmpty) {
	Vector<int> v;
	EXPECT_FALSE(v.remove_first(1));
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

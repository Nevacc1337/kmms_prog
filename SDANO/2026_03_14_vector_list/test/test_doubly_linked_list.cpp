#include <gtest/gtest.h>

#include "doubly_linked_list.hpp"

using biv::DoublyLinkedList;

// --- get_size ---

TEST(DLLTest, SizeInitiallyZero) {
	DoublyLinkedList<int> list;
	EXPECT_EQ(list.get_size(), 0u);
}

TEST(DLLTest, SizeAfterPushBack) {
	DoublyLinkedList<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	EXPECT_EQ(list.get_size(), 3u);
}

// --- has_item ---

TEST(DLLTest, HasItemEmpty) {
	DoublyLinkedList<int> list;
	EXPECT_FALSE(list.has_item(1));
}

TEST(DLLTest, HasItemPresent) {
	DoublyLinkedList<int> list;
	list.push_back(10);
	list.push_back(20);
	EXPECT_TRUE(list.has_item(10));
	EXPECT_TRUE(list.has_item(20));
}

TEST(DLLTest, HasItemAbsent) {
	DoublyLinkedList<int> list;
	list.push_back(10);
	EXPECT_FALSE(list.has_item(99));
}

// --- push_back ---

TEST(DLLTest, PushBackMultiple) {
	DoublyLinkedList<int> list;
	for (int i = 0; i < 100; ++i) {
		list.push_back(i);
	}
	EXPECT_EQ(list.get_size(), 100u);
	EXPECT_TRUE(list.has_item(0));
	EXPECT_TRUE(list.has_item(99));
}

// --- remove_first ---

TEST(DLLTest, RemoveFirstPresent) {
	DoublyLinkedList<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	bool result = list.remove_first(2);
	EXPECT_TRUE(result);
	EXPECT_EQ(list.get_size(), 2u);
	EXPECT_FALSE(list.has_item(2));
}

TEST(DLLTest, RemoveFirstAbsent) {
	DoublyLinkedList<int> list;
	list.push_back(1);
	bool result = list.remove_first(99);
	EXPECT_FALSE(result);
	EXPECT_EQ(list.get_size(), 1u);
}

TEST(DLLTest, RemoveFirstHead) {
	DoublyLinkedList<int> list;
	list.push_back(1);
	list.push_back(2);
	bool result = list.remove_first(1);
	EXPECT_TRUE(result);
	EXPECT_EQ(list.get_size(), 1u);
	EXPECT_FALSE(list.has_item(1));
	EXPECT_TRUE(list.has_item(2));
}

TEST(DLLTest, RemoveFirstTail) {
	DoublyLinkedList<int> list;
	list.push_back(1);
	list.push_back(2);
	bool result = list.remove_first(2);
	EXPECT_TRUE(result);
	EXPECT_EQ(list.get_size(), 1u);
	EXPECT_TRUE(list.has_item(1));
}

TEST(DLLTest, RemoveOnlyElement) {
	DoublyLinkedList<int> list;
	list.push_back(42);
	bool result = list.remove_first(42);
	EXPECT_TRUE(result);
	EXPECT_EQ(list.get_size(), 0u);
}

TEST(DLLTest, RemoveFirstOnlyFirstDuplicate) {
	DoublyLinkedList<int> list;
	list.push_back(5);
	list.push_back(5);
	list.push_back(5);
	list.remove_first(5);
	EXPECT_EQ(list.get_size(), 2u);
	EXPECT_TRUE(list.has_item(5));
}

TEST(DLLTest, RemoveFromEmpty) {
	DoublyLinkedList<int> list;
	EXPECT_FALSE(list.remove_first(1));
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

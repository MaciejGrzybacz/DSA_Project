#include <gtest/gtest.h>
#include "src/data_structures/linked_list.h"
#include <string>

// Test fixture for DoublyLinkedList
class DoublyLinkedListTest : public ::testing::Test {
protected:
    DoublyLinkedList<int> intList;
    DoublyLinkedList<std::string> stringList;

    void SetUp() override {
        // Set up is called before every test
        intList.clear();
        stringList.clear();
    }
};

// Constructor and initial state tests
TEST_F(DoublyLinkedListTest, ConstructorCreatesEmptyList) {
    EXPECT_TRUE(intList.empty());
    EXPECT_EQ(intList.size(), 0);
    EXPECT_EQ(intList.begin(), intList.end());
}

// Push and pop tests
TEST_F(DoublyLinkedListTest, PushFrontAndBack) {
    intList.push_front(1);
    EXPECT_EQ(intList.front(), 1);
    EXPECT_EQ(intList.back(), 1);
    EXPECT_EQ(intList.size(), 1);

    intList.push_back(2);
    EXPECT_EQ(intList.front(), 1);
    EXPECT_EQ(intList.back(), 2);
    EXPECT_EQ(intList.size(), 2);

    intList.push_front(0);
    EXPECT_EQ(intList.front(), 0);
    EXPECT_EQ(intList.back(), 2);
    EXPECT_EQ(intList.size(), 3);
}

TEST_F(DoublyLinkedListTest, PopFrontAndBack) {
    intList.push_back(1);
    intList.push_back(2);
    intList.push_back(3);

    intList.pop_front();
    EXPECT_EQ(intList.front(), 2);
    EXPECT_EQ(intList.size(), 2);

    intList.pop_back();
    EXPECT_EQ(intList.back(), 2);
    EXPECT_EQ(intList.size(), 1);

    intList.pop_back();
    EXPECT_TRUE(intList.empty());

    EXPECT_THROW(intList.pop_front(), std::runtime_error);
    EXPECT_THROW(intList.pop_back(), std::runtime_error);
}

// Front and back access tests
TEST_F(DoublyLinkedListTest, FrontAndBackAccess) {
    EXPECT_THROW(intList.front(), std::runtime_error);
    EXPECT_THROW(intList.back(), std::runtime_error);

    intList.push_back(1);
    EXPECT_EQ(intList.front(), 1);
    EXPECT_EQ(intList.back(), 1);

    intList.push_back(2);
    EXPECT_EQ(intList.front(), 1);
    EXPECT_EQ(intList.back(), 2);
}

// Iterator tests
TEST_F(DoublyLinkedListTest, IteratorTraversal) {
    intList.push_back(1);
    intList.push_back(2);
    intList.push_back(3);

    auto it = intList.begin();
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 2);
    ++it;
    EXPECT_EQ(*it, 3);
    --it;
    EXPECT_EQ(*it, 2);
    --it;
    EXPECT_EQ(*it, 1);
    EXPECT_EQ(it, intList.begin());
}

TEST_F(DoublyLinkedListTest, ConstIteratorTraversal) {
    intList.push_back(1);
    intList.push_back(2);
    intList.push_back(3);

    const DoublyLinkedList<int>& constList = intList;
    auto it = constList.begin();
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 2);
    ++it;
    EXPECT_EQ(*it, 3);
    ++it;
    EXPECT_EQ(it, constList.end());
}

// Insert and erase tests
TEST_F(DoublyLinkedListTest, InsertElements) {
    auto it = intList.insert(intList.begin(), 1);
    EXPECT_EQ(*it, 1);
    EXPECT_EQ(intList.size(), 1);

    it = intList.insert(intList.end(), 3);
    EXPECT_EQ(*it, 3);
    EXPECT_EQ(intList.size(), 2);

    it = intList.insert(++intList.begin(), 2);
    EXPECT_EQ(*it, 2);
    EXPECT_EQ(intList.size(), 3);

    EXPECT_EQ(intList.front(), 1);
    EXPECT_EQ(intList.back(), 3);
}

TEST_F(DoublyLinkedListTest, EraseElements) {
    intList.push_back(1);
    intList.push_back(2);
    intList.push_back(3);

    auto it = intList.erase(++intList.begin());
    EXPECT_EQ(*it, 3);
    EXPECT_EQ(intList.size(), 2);

    it = intList.erase(intList.begin());
    EXPECT_EQ(*it, 3);
    EXPECT_EQ(intList.size(), 1);

    it = intList.erase(intList.begin());
    EXPECT_EQ(it, intList.end());
    EXPECT_TRUE(intList.empty());

    EXPECT_THROW(intList.erase(intList.begin()), std::runtime_error);
}

// Clear test
TEST_F(DoublyLinkedListTest, ClearList) {
    intList.push_back(1);
    intList.push_back(2);
    intList.push_back(3);

    intList.clear();
    EXPECT_TRUE(intList.empty());
    EXPECT_EQ(intList.size(), 0);
    EXPECT_EQ(intList.begin(), intList.end());
}

// Copy constructor and assignment operator tests
TEST_F(DoublyLinkedListTest, CopyConstructorAndAssignment) {
    intList.push_back(1);
    intList.push_back(2);
    intList.push_back(3);

    DoublyLinkedList<int> copiedList(intList);
    EXPECT_EQ(copiedList.size(), intList.size());
    EXPECT_TRUE(std::equal(copiedList.begin(), copiedList.end(), intList.begin()));

    DoublyLinkedList<int> assignedList;
    assignedList = intList;
    EXPECT_EQ(assignedList.size(), intList.size());
    EXPECT_TRUE(std::equal(assignedList.begin(), assignedList.end(), intList.begin()));
}

// Move constructor and assignment operator tests
TEST_F(DoublyLinkedListTest, MoveConstructorAndAssignment) {
    intList.push_back(1);
    intList.push_back(2);
    intList.push_back(3);

    DoublyLinkedList<int> movedList(std::move(intList));
    EXPECT_EQ(movedList.size(), 3);
    EXPECT_TRUE(intList.empty());

    DoublyLinkedList<int> assignedList;
    assignedList = std::move(movedList);
    EXPECT_EQ(assignedList.size(), 3);
    EXPECT_TRUE(movedList.empty());
}

// Comparison operator tests
TEST_F(DoublyLinkedListTest, ComparisonOperators) {
    DoublyLinkedList<int> list1, list2;
    list1.push_back(1);
    list1.push_back(2);
    list1.push_back(3);

    list2.push_back(1);
    list2.push_back(2);
    list2.push_back(3);

    EXPECT_TRUE(list1 == list2);
    EXPECT_FALSE(list1 != list2);

    list2.push_back(4);
    EXPECT_FALSE(list1 == list2);
    EXPECT_TRUE(list1 != list2);
}

// Test with non-trivial types
TEST_F(DoublyLinkedListTest, NonTrivialTypes) {
    stringList.push_back("Hello");
    stringList.push_back("World");

    EXPECT_EQ(stringList.size(), 2);
    EXPECT_EQ(stringList.front(), "Hello");
    EXPECT_EQ(stringList.back(), "World");

    auto it = stringList.begin();
    EXPECT_EQ(*it, "Hello");
    ++it;
    EXPECT_EQ(*it, "World");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
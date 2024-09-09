#include <gtest/gtest.h>
#include "src/data_structures/stack.h"
#include <string>

// Test fixture for Stack
class StackTest : public ::testing::Test {
protected:
    Stack<int> intStack;
    Stack<std::string> stringStack;

    void SetUp() override {
        // Set up is called before every test
        while (!intStack.empty()) intStack.pop();
        while (!stringStack.empty()) stringStack.pop();
    }
};

// Constructor and initial state tests
TEST_F(StackTest, ConstructorCreatesEmptyStack) {
    EXPECT_TRUE(intStack.empty());
    EXPECT_EQ(intStack.size(), 0);
}

// Push and pop tests
TEST_F(StackTest, PushAndPop) {
    intStack.push(1);
    EXPECT_EQ(intStack.top(), 1);
    EXPECT_EQ(intStack.size(), 1);

    intStack.push(2);
    EXPECT_EQ(intStack.top(), 2);
    EXPECT_EQ(intStack.size(), 2);

    intStack.pop();
    EXPECT_EQ(intStack.top(), 1);
    EXPECT_EQ(intStack.size(), 1);

    intStack.pop();
    EXPECT_TRUE(intStack.empty());

    EXPECT_THROW(intStack.pop(), std::runtime_error);
}

// Top access test
TEST_F(StackTest, TopAccess) {
    EXPECT_THROW(intStack.top(), std::runtime_error);

    intStack.push(1);
    EXPECT_EQ(intStack.top(), 1);

    intStack.push(2);
    EXPECT_EQ(intStack.top(), 2);
}

// Clear test
TEST_F(StackTest, ClearStack) {
    intStack.push(1);
    intStack.push(2);
    intStack.push(3);

    while (!intStack.empty()) intStack.pop();
    EXPECT_TRUE(intStack.empty());
    EXPECT_EQ(intStack.size(), 0);
}

// Test with non-trivial types
TEST_F(StackTest, NonTrivialTypes) {
    stringStack.push("Hello");
    stringStack.push("World");

    EXPECT_EQ(stringStack.size(), 2);
    EXPECT_EQ(stringStack.top(), "World");

    stringStack.pop();
    EXPECT_EQ(stringStack.top(), "Hello");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
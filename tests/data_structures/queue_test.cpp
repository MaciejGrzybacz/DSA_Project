#include <gtest/gtest.h>
#include "src/data_structures/queue.h"
#include <string>

// Test fixture for Queue
class QueueTest : public ::testing::Test {
protected:
    Queue<int> intQueue;
    Queue<std::string> stringQueue;

    void SetUp() override {
        // Set up is called before every test
        while (!intQueue.empty()) intQueue.dequeue();
        while (!stringQueue.empty()) stringQueue.dequeue();
    }
};

// Constructor and initial state tests
TEST_F(QueueTest, ConstructorCreatesEmptyQueue) {
    EXPECT_TRUE(intQueue.empty());
    EXPECT_EQ(intQueue.size(), 0);
}

// Enqueue and dequeue tests
TEST_F(QueueTest, EnqueueAndDequeue) {
    intQueue.enqueue(1);
    EXPECT_EQ(intQueue.front(), 1);
    EXPECT_EQ(intQueue.size(), 1);

    intQueue.enqueue(2);
    EXPECT_EQ(intQueue.front(), 1);
    EXPECT_EQ(intQueue.size(), 2);

    intQueue.dequeue();
    EXPECT_EQ(intQueue.front(), 2);
    EXPECT_EQ(intQueue.size(), 1);

    intQueue.dequeue();
    EXPECT_TRUE(intQueue.empty());

    EXPECT_THROW(intQueue.dequeue(), std::runtime_error);
}

// Front access test
TEST_F(QueueTest, FrontAccess) {
    EXPECT_THROW(intQueue.front(), std::runtime_error);

    intQueue.enqueue(1);
    EXPECT_EQ(intQueue.front(), 1);

    intQueue.enqueue(2);
    EXPECT_EQ(intQueue.front(), 1);
}

// Clear test
TEST_F(QueueTest, ClearQueue) {
    intQueue.enqueue(1);
    intQueue.enqueue(2);
    intQueue.enqueue(3);

    while (!intQueue.empty()) intQueue.dequeue();
    EXPECT_TRUE(intQueue.empty());
    EXPECT_EQ(intQueue.size(), 0);
}

// Test with non-trivial types
TEST_F(QueueTest, NonTrivialTypes) {
    stringQueue.enqueue("Hello");
    stringQueue.enqueue("World");

    EXPECT_EQ(stringQueue.size(), 2);
    EXPECT_EQ(stringQueue.front(), "Hello");

    stringQueue.dequeue();
    EXPECT_EQ(stringQueue.front(), "World");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
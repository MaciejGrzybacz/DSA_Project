#include <gtest/gtest.h>
#include "src/graph/topological_sort.h"

class TopologicalSortTest : public ::testing::Test {
protected:
    void SetUp() override {
        g = new Graph(5);
        g->addEdge(0, 1);
        g->addEdge(0, 2);
        g->addEdge(1, 3);
        g->addEdge(2, 3);
        g->addEdge(3, 4);
    }

    void TearDown() override {
        delete g;
    }

    Graph* g;
};

TEST_F(TopologicalSortTest, SimpleDAG) {
    std::vector<int> result = g->topologicalSort();
    EXPECT_EQ(result.size(), 5);

    std::vector<int> expected = {0, 1, 2, 3, 4};
    EXPECT_EQ(result, expected);
}

TEST_F(TopologicalSortTest, GraphWithCycle) {
    Graph g2(3);
    g2.addEdge(0, 1);
    g2.addEdge(1, 2);
    g2.addEdge(2, 0);  // This creates a cycle

    std::vector<int> result = g2.topologicalSort();
    EXPECT_TRUE(result.empty());
}

TEST_F(TopologicalSortTest, EmptyGraph) {
    Graph g2(0);
    std::vector<int> result = g2.topologicalSort();
    EXPECT_TRUE(result.empty());
}

TEST_F(TopologicalSortTest, SingleVertexGraph) {
    Graph g2(1);
    std::vector<int> result = g2.topologicalSort();
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], 0);
}


TEST_F(TopologicalSortTest, LargeGraph) {
    Graph g2(1000);
    for (int i = 0; i < 999; ++i) {
        g2.addEdge(i, i+1);
    }
    std::vector<int> result = g2.topologicalSort();
    EXPECT_EQ(result.size(), 1000);

    for (int i = 0; i < 1000; ++i) {
        EXPECT_EQ(result[i], i);
    }
}

TEST_F(TopologicalSortTest, MultipleValidOrderings) {
    Graph g2(4);
    g2.addEdge(0, 2);
    g2.addEdge(1, 2);
    g2.addEdge(2, 3);

    std::vector<int> result = g2.topologicalSort();
    EXPECT_EQ(result.size(), 4);

    EXPECT_TRUE(result[0] == 0 || result[0] == 1);
    EXPECT_TRUE(result[1] == 0 || result[1] == 1);
    EXPECT_NE(result[0], result[1]);
    EXPECT_EQ(result[2], 2);
    EXPECT_EQ(result[3], 3);
}
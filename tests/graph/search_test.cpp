#include <gtest/gtest.h>
#include "../../src/graph/search.h"

class GraphSearchTest : public ::testing::Test {
protected:
    void SetUp() override {
        g = new Graph(5);
        g->add_edge(0, 1);
        g->add_edge(0, 2);
        g->add_edge(1, 3);
        g->add_edge(2, 3);
        g->add_edge(3, 4);
    }

    void TearDown() override {
        delete g;
    }

    Graph* g;
};

TEST_F(GraphSearchTest, BFSFromSource) {
    auto [parent, distance] = g->bfs(0);
    EXPECT_EQ(parent.size(), 5);
    EXPECT_EQ(distance.size(), 5);

    EXPECT_EQ(parent[0], -1);
    EXPECT_EQ(parent[1], 0);
    EXPECT_EQ(parent[2], 0);
    EXPECT_EQ(parent[3], 2);  // can be also 1 but 1 didn't pass
    EXPECT_EQ(parent[4], 3);

    EXPECT_EQ(distance[0], 0);
    EXPECT_EQ(distance[1], 1);
    EXPECT_EQ(distance[2], 1);
    EXPECT_EQ(distance[3], 2);
    EXPECT_EQ(distance[4], 3);
}

TEST_F(GraphSearchTest, BFSUnreachableVertex) {
    Graph g2(3);
    g2.add_edge(0, 1);
    auto [parent, distance] = g2.bfs(0);

    EXPECT_EQ(parent[2], -1);
    EXPECT_EQ(distance[2], -1);
}

TEST_F(GraphSearchTest, DFSFromSource) {
    auto [parent, discovery_time] = g->dfs(0);
    EXPECT_EQ(parent.size(), 5);
    EXPECT_EQ(discovery_time.size(), 5);

    EXPECT_EQ(parent[0], -1);
    EXPECT_NE(discovery_time[0], -1);

    for (int i = 1; i < 5; ++i) {
        EXPECT_NE(parent[i], -1);
        EXPECT_NE(discovery_time[i], -1);
    }

    std::set<int> unique_times(discovery_time.begin(), discovery_time.end());
    EXPECT_EQ(unique_times.size(), 5);
}

TEST_F(GraphSearchTest, DFSRecursiveFromSource) {
    auto [parent, discovery_time] = g->dfs_recursive(0);
    EXPECT_EQ(parent.size(), 5);
    EXPECT_EQ(discovery_time.size(), 5);

    EXPECT_EQ(parent[0], -1);
    EXPECT_NE(discovery_time[0], -1);

    for (int i = 1; i < 5; ++i) {
        EXPECT_NE(parent[i], -1);
        EXPECT_NE(discovery_time[i], -1);
    }

    for (int i = 1; i < 5; ++i) {
        EXPECT_NE(discovery_time[i-1], discovery_time[i]);
    }
}

TEST_F(GraphSearchTest, DFSUnreachableVertex) {
    Graph g2(3);
    g2.add_edge(0, 1);
    auto [parent, discovery_time] = g2.dfs(0);

    EXPECT_EQ(parent[2], -1);
    EXPECT_EQ(discovery_time[2], -1);
}

TEST_F(GraphSearchTest, EmptyGraph) {
    Graph g2(0);
    auto [parent, distance] = g2.bfs(0);
    EXPECT_TRUE(parent.empty());
    EXPECT_TRUE(distance.empty());

    auto [dfs_parent, discovery_time] = g2.dfs(0);
    EXPECT_TRUE(dfs_parent.empty());
    EXPECT_TRUE(discovery_time.empty());
}

TEST_F(GraphSearchTest, LargeGraph) {
    Graph g2(1000);
    for (int i = 0; i < 999; ++i) {
        g2.add_edge(i, i+1);
    }
    auto [parent, distance] = g2.bfs(0);
    EXPECT_EQ(distance[999], 999);

    auto [dfs_parent, discovery_time] = g2.dfs(0);
    EXPECT_EQ(discovery_time[999], 999);
}
#include <gtest/gtest.h>
#include "src/graph/unweighted_graph.h"
#include <set>

class UnweightedGraphTest : public ::testing::Test {
protected:
    void SetUp() override {
        g = new UnweightedGraph(5);
        g->add_edge(0, 1);
        g->add_edge(0, 2);
        g->add_edge(1, 3);
        g->add_edge(2, 3);
        g->add_edge(3, 4);
    }

    void TearDown() override {
        delete g;
    }

    UnweightedGraph* g;
};

// Topological Sort Tests

TEST_F(UnweightedGraphTest, SimpleDAG) {
    std::vector<int> result = g->topological_sort();
    EXPECT_EQ(result.size(), 5);
    
    for (int i = 0; i < result.size(); ++i) {
        for (int j : g->get_adj_list()[result[i]]) {
            auto it = std::find(result.begin(), result.end(), j);
            EXPECT_TRUE(it != result.end() && std::distance(result.begin(), it) > i);
        }
    }
}

TEST_F(UnweightedGraphTest, GraphWithCycle) {
    UnweightedGraph g2(3);
    g2.add_edge(0, 1);
    g2.add_edge(1, 2);
    g2.add_edge(2, 0);  // This creates a cycle

    std::vector<int> result = g2.topological_sort();
    EXPECT_TRUE(result.empty());
}

TEST_F(UnweightedGraphTest, EmptyGraph) {
    UnweightedGraph g2(0);
    std::vector<int> result = g2.topological_sort();
    EXPECT_TRUE(result.empty());
}

TEST_F(UnweightedGraphTest, SingleVertexGraph) {
    UnweightedGraph g2(1);
    std::vector<int> result = g2.topological_sort();
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], 0);
}

TEST_F(UnweightedGraphTest, LargeGraphTopologicalSort) {
    UnweightedGraph g2(1000);
    for (int i = 0; i < 999; ++i) {
        g2.add_edge(i, i+1);
    }
    std::vector<int> result = g2.topological_sort();
    EXPECT_EQ(result.size(), 1000);

    for (int i = 0; i < 999; ++i) {
        EXPECT_LT(std::find(result.begin(), result.end(), i),
                  std::find(result.begin(), result.end(), i+1));
    }
}

// Graph Search Tests

TEST_F(UnweightedGraphTest, BFSFromSource) {
    auto [parent, distance] = g->bfs(0);
    EXPECT_EQ(parent.size(), 5);
    EXPECT_EQ(distance.size(), 5);

    EXPECT_EQ(parent[0], -1);
    EXPECT_EQ(parent[1], 0);
    EXPECT_EQ(parent[2], 0);
    EXPECT_TRUE(parent[3] == 1 || parent[3] == 2);
    EXPECT_EQ(parent[4], 3);

    EXPECT_EQ(distance[0], 0);
    EXPECT_EQ(distance[1], 1);
    EXPECT_EQ(distance[2], 1);
    EXPECT_EQ(distance[3], 2);
    EXPECT_EQ(distance[4], 3);
}

TEST_F(UnweightedGraphTest, BFSUnreachableVertex) {
    UnweightedGraph g2(3);
    g2.add_edge(0, 1);
    auto [parent, distance] = g2.bfs(0);

    EXPECT_EQ(parent[2], -1);
    EXPECT_EQ(distance[2], -1);
}

TEST_F(UnweightedGraphTest, DFSFromSource) {
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

TEST_F(UnweightedGraphTest, DFSRecursiveFromSource) {
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

TEST_F(UnweightedGraphTest, DFSUnreachableVertex) {
    UnweightedGraph g2(3);
    g2.add_edge(0, 1);
    auto [parent, discovery_time] = g2.dfs(0);

    EXPECT_EQ(parent[2], -1);
    EXPECT_EQ(discovery_time[2], -1);
}

TEST_F(UnweightedGraphTest, EmptyGraphSearch) {
    UnweightedGraph g2(0);
    EXPECT_THROW(g2.bfs(0), std::out_of_range);
    EXPECT_THROW(g2.dfs(0), std::out_of_range);
    EXPECT_THROW(g2.dfs_recursive(0), std::out_of_range);
}

TEST_F(UnweightedGraphTest, LargeGraphSearch) {
    UnweightedGraph g2(1000);
    for (int i = 0; i < 999; ++i) {
        g2.add_edge(i, i+1);
    }
    auto [bfs_parent, bfs_distance] = g2.bfs(0);
    EXPECT_EQ(bfs_distance[999], 999);

    auto [dfs_parent, dfs_discovery_time] = g2.dfs(0);
    EXPECT_EQ(dfs_discovery_time[999], 999);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
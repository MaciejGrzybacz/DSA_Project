#include <gtest/gtest.h>
#include "src/graph/mst.h"
#include <algorithm>
#include <random>

class GraphTest : public ::testing::Test {
protected:
    void SetUp() override {}

    void TearDown() override {}
    
    static bool areMSTsEquivalent(const std::vector<MSTGraph::Edge>& mst1,
                           const std::vector<MSTGraph::Edge>& mst2) {
        if (mst1.size() != mst2.size()) return false;

        int totalWeight1 = 0, totalWeight2 = 0;
        for (const auto& edge : mst1) totalWeight1 += edge.w;
        for (const auto& edge : mst2) totalWeight2 += edge.w;

        return totalWeight1 == totalWeight2;
    }
};

TEST_F(GraphTest, SimpleGraphKruskal) {
    MSTGraph g(4);
    g.add_edge(0, 1, 10);
    g.add_edge(0, 2, 6);
    g.add_edge(0, 3, 5);
    g.add_edge(1, 3, 15);
    g.add_edge(2, 3, 4);

    auto mst = g.kruskal_mst();

    ASSERT_EQ(mst.size(), 3);
    int totalWeight = 0;
    for (const auto& edge : mst) totalWeight += edge.w;
    EXPECT_EQ(totalWeight, 19); // 0->1, 2->3, 0->3
}

TEST_F(GraphTest, SimpleGraphPrim) {
    MSTGraph g(4);
    g.add_edge(0, 1, 10);
    g.add_edge(0, 2, 6);
    g.add_edge(0, 3, 5);
    g.add_edge(1, 3, 15);
    g.add_edge(2, 3, 4);

    auto mst = g.prim_mst();

    ASSERT_EQ(mst.size(), 3);
    int totalWeight = 0;
    for (const auto& edge : mst) totalWeight += edge.w;
    EXPECT_EQ(totalWeight, 19); // 0->1, 2->3, 0->3
}

TEST_F(GraphTest, KruskalPrimEquivalence) {
    MSTGraph g(6);
    g.add_edge(0, 1, 4);
    g.add_edge(0, 2, 3);
    g.add_edge(1, 2, 1);
    g.add_edge(1, 3, 2);
    g.add_edge(2, 3, 4);
    g.add_edge(3, 4, 2);
    g.add_edge(4, 5, 6);

    auto mstKruskal = g.kruskal_mst();
    auto mstPrim = g.prim_mst();

    EXPECT_TRUE(areMSTsEquivalent(mstKruskal, mstPrim));
}

TEST_F(GraphTest, DisconnectedGraph) {
    MSTGraph g(5);
    g.add_edge(0, 1, 1);
    g.add_edge(2, 3, 2);
    // Node 4 is disconnected

    auto mstKruskal = g.kruskal_mst();
    auto mstPrim = g.prim_mst();

    ASSERT_EQ(mstKruskal.size(), 0);
    ASSERT_EQ(mstPrim.size(), 0);
    EXPECT_TRUE(areMSTsEquivalent(mstKruskal, mstPrim));
}

TEST_F(GraphTest, LargeGraph) {
    const int NUM_VERTICES = 1000;
    const int NUM_EDGES = 5000;
    const int MAX_WEIGHT = 100;

    MSTGraph g(NUM_VERTICES);
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> vertex_dist(0, NUM_VERTICES - 1);
    std::uniform_int_distribution<> weight_dist(1, MAX_WEIGHT);

    for (int i = 0; i < NUM_EDGES; ++i) {
        int u = vertex_dist(gen);
        int v = vertex_dist(gen);
        int w = weight_dist(gen);
        g.add_edge(u, v, w);
    }

    auto mstKruskal = g.kruskal_mst();
    auto mstPrim = g.prim_mst();

    EXPECT_TRUE(areMSTsEquivalent(mstKruskal, mstPrim));
}
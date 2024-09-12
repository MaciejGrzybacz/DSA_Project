#include <gtest/gtest.h>
#include "src/graph/weighted_graph.h"
#include <algorithm>
#include <random>

class WeightedGraphTest : public ::testing::Test {
protected:
    void SetUp() override {
        g = new WeightedGraph(5);
        g->add_edge(0, 1, 4);
        g->add_edge(0, 2, 1);
        g->add_edge(1, 3, 1);
        g->add_edge(2, 1, 2);
        g->add_edge(2, 3, 5);
        g->add_edge(3, 4, 3);
    }

    void TearDown() override {
        delete g;
    }

    static bool areMSTsEquivalent(const std::vector<WeightedGraph::Edge>& mst1,
                                  const std::vector<WeightedGraph::Edge>& mst2) {
        if (mst1.size() != mst2.size()) return false;

        int totalWeight1 = 0, totalWeight2 = 0;
        for (const auto& edge : mst1) totalWeight1 += edge.w;
        for (const auto& edge : mst2) totalWeight2 += edge.w;

        return totalWeight1 == totalWeight2;
    }

    WeightedGraph* g;
};

// Dijkstra's Algorithm Tests

TEST_F(WeightedGraphTest, SingleSourceAllDestinations) {
    std::vector<int> distances = g->dijkstra(0);
    EXPECT_EQ(distances.size(), 5);
    EXPECT_EQ(distances[0], 0);
    EXPECT_EQ(distances[1], 3);
    EXPECT_EQ(distances[2], 1);
    EXPECT_EQ(distances[3], 4);
    EXPECT_EQ(distances[4], 7);
}

TEST_F(WeightedGraphTest, SingleSourceSingleDestination) {
    EXPECT_EQ(g->dijkstra(0, 4), 7);
    EXPECT_EQ(g->dijkstra(0, 3), 4);
    EXPECT_EQ(g->dijkstra(2, 4), 6);
}

TEST_F(WeightedGraphTest, NoPath) {
    WeightedGraph g2(3);
    g2.add_edge(0, 1, 1);
    // No path to vertex 2
    EXPECT_EQ(g2.dijkstra(0, 2), -1);
}

TEST_F(WeightedGraphTest, SelfLoop) {
    WeightedGraph g2(2);
    g2.add_edge(0, 0, 1);
    g2.add_edge(0, 1, 2);
    EXPECT_EQ(g2.dijkstra(0, 1), 2);
}

TEST_F(WeightedGraphTest, InvalidVertex) {
    EXPECT_THROW(g->dijkstra(0, 5), std::out_of_range);
    EXPECT_THROW(g->dijkstra(5, 0), std::out_of_range);
}

TEST_F(WeightedGraphTest, EmptyGraph) {
    WeightedGraph g2(0);
    EXPECT_THROW(g2.dijkstra(0), std::out_of_range);
}

TEST_F(WeightedGraphTest, LargeGraphDijkstra) {
    WeightedGraph g2(1000);
    for (int i = 0; i < 999; ++i) {
        g2.add_edge(i, i+1, 1);
    }
    EXPECT_EQ(g2.dijkstra(0, 999), 999);
}

// Minimum Spanning Tree Tests

TEST_F(WeightedGraphTest, SimpleGraphKruskal) {
    WeightedGraph g(4);
    g.add_edge(0, 1, 10);
    g.add_edge(0, 2, 6);
    g.add_edge(0, 3, 5);
    g.add_edge(1, 3, 15);
    g.add_edge(2, 3, 4);

    auto mst = g.kruskal_mst();

    ASSERT_EQ(mst.size(), 3);
    int totalWeight = 0;
    for (const auto& edge : mst) totalWeight += edge.w;
    EXPECT_EQ(totalWeight, 19); // 0->3, 2->3, 0->1 or equivalent
}

TEST_F(WeightedGraphTest, SimpleGraphPrim) {
    WeightedGraph g(4);
    g.add_edge(0, 1, 10);
    g.add_edge(0, 2, 6);
    g.add_edge(0, 3, 5);
    g.add_edge(1, 3, 15);
    g.add_edge(2, 3, 4);

    auto mst = g.prim_mst();

    ASSERT_EQ(mst.size(), 3);
    int totalWeight = 0;
    for (const auto& edge : mst) totalWeight += edge.w;
    EXPECT_EQ(totalWeight, 19); // 0->3, 2->3, 0->1 or equivalent
}

TEST_F(WeightedGraphTest, KruskalPrimEquivalence) {
    WeightedGraph g(6);
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

TEST_F(WeightedGraphTest, DisconnectedGraph) {
    WeightedGraph g(5);
    g.add_edge(0, 1, 1);
    g.add_edge(2, 3, 2);
    // Node 4 is disconnected

    auto mstKruskal = g.kruskal_mst();
    auto mstPrim = g.prim_mst();

    // For a disconnected graph, MST algorithms might return partial MST or empty vector
    // Adjust this expectation based on your implementation
    EXPECT_TRUE(mstKruskal.empty() || mstKruskal.size() == 2);
    EXPECT_TRUE(mstPrim.empty() || mstPrim.size() == 2);
}

TEST_F(WeightedGraphTest, LargeGraphMST) {
    const int NUM_VERTICES = 1000;
    const int NUM_EDGES = 5000;
    const int MAX_WEIGHT = 100;

    WeightedGraph g(NUM_VERTICES);

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

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#include <gtest/gtest.h>
#include "src/graph/dijkstra.h"

class GraphTest : public ::testing::Test {
protected:
    void SetUp() override {
        g = new Graph(5);
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

    Graph* g;
};

TEST_F(GraphTest, SingleSourceAllDestinations) {
    std::vector<int> distances = g->dijkstra(0);
    EXPECT_EQ(distances.size(), 5);
    EXPECT_EQ(distances[0], 0);
    EXPECT_EQ(distances[1], 3);
    EXPECT_EQ(distances[2], 1);
    EXPECT_EQ(distances[3], 4);
    EXPECT_EQ(distances[4], 7);
}

TEST_F(GraphTest, SingleSourceSingleDestination) {
    EXPECT_EQ(g->dijkstra(0, 4), 7);
    EXPECT_EQ(g->dijkstra(0, 3), 4);
    EXPECT_EQ(g->dijkstra(2, 4), 6);
}

TEST_F(GraphTest, NoPath) {
    Graph g2(3);
    g2.add_edge(0, 1, 1);
    // Brak ścieżki do wierzchołka 2
    EXPECT_EQ(g2.dijkstra(0, 2), -1);
}

TEST_F(GraphTest, SelfLoop) {
    Graph g2(2);
    g2.add_edge(0, 0, 1);
    g2.add_edge(0, 1, 2);
    EXPECT_EQ(g2.dijkstra(0, 1), 2);
}

TEST_F(GraphTest, InvalidVertex) {
    EXPECT_EQ(g->dijkstra(0, 5), -1);
    EXPECT_EQ(g->dijkstra(5, 0), -1);
}

TEST_F(GraphTest, EmptyGraph) {
    Graph g2(0);
    std::vector<int> distances = g2.dijkstra(0);
    EXPECT_TRUE(distances.empty());
}

TEST_F(GraphTest, LargeGraph) {
    Graph g2(1000);
    for (int i = 0; i < 999; ++i) {
        g2.add_edge(i, i+1, 1);
    }
    EXPECT_EQ(g2.dijkstra(0, 999), 999);
}
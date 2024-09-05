#ifndef DSA_DIJKSTRA_H
#define DSA_DIJKSTRA_H

#include <vector>
#include <climits>
#include <queue>

/**
 * @brief A class representing a weighted directed graph with Dijkstra's algorithm implementation.
 *
 * This class provides a representation of a weighted directed graph using an adjacency list.
 * It includes methods for adding edges to the graph and implementing Dijkstra's algorithm
 * for finding shortest paths in the graph.
 *
 * The graph is represented internally using an adjacency list of Edge structures,
 * which allows for efficient storage and traversal of sparse graphs. Each Edge
 * structure contains the destination vertex and the weight of the edge.
 *
 * The class provides two versions of Dijkstra's algorithm:
 * 1. Finding shortest paths from a start vertex to all other vertices.
 * 2. Finding the shortest path between two specific vertices.
 *
 * @note The graph is zero-indexed, meaning vertex indices range from 0 to size-1.
 * @note This implementation assumes a directed graph. For an undirected graph,
 *       edges should be added in both directions.
 * @note The implementation of Dijkstra's algorithm assumes non-negative edge weights.
 */
class Graph {
private:
    struct Edge {
        int _to;
        int _weight;
    };

    int _size;
    std::vector<std::vector<Edge>> _adjacency_list;

public:
    /**
     * @brief Constructs a Graph object with the specified number of vertices.
     * @param vertices The number of vertices in the graph.
     */
    explicit Graph(int vertices) : _size(vertices), _adjacency_list(vertices) {};

    /**
     * @brief Adds a directed edge to the graph.
     * @param from The index of the source vertex.
     * @param to The index of the destination vertex.
     * @param weight The weight of the edge.
     */
    void add_edge(int from, int to, int weight) {
        _adjacency_list[from].push_back(Edge{to, weight});
    };

    /**
    * @brief Performs Dijkstra's algorithm to find the shortest paths from a start vertex to all other vertices.
    *
    * This method implements Dijkstra's algorithm using a priority queue for efficiency.
    * It computes the shortest path distances from the start vertex to all other vertices in the graph.
    *
    * @param start The index of the starting vertex.
    * @return A vector of integers where the i-th element represents the shortest distance
    *         from the start vertex to vertex i. If a vertex is unreachable, its distance
    *         will be INT_MAX.
    *
    * @note The time complexity of this implementation is O((V + E) * log(V)), where V is the
    *       number of vertices and E is the number of edges in the graph.
    * @note This method assumes that edge weights are non-negative.
    * @note If the graph is empty (no vertices), an empty vector is returned.
    */
    [[nodiscard]] std::vector<int> dijkstra(int start) const;

    /**
     * @brief Performs Dijkstra's algorithm to find the shortest path between two vertices.
     *
     * This method implements Dijkstra's algorithm using a priority queue for efficiency.
     * It computes the shortest path distance from the start vertex to the end vertex.
     *
     * @param start The index of the starting vertex.
     * @param end The index of the ending vertex.
     * @return The shortest distance from start to end. If there's no path between start and end,
     *         or if either start or end is out of range, -1 is returned.
     *
     * @note The time complexity of this implementation is O((V + E) * log(V)) in the worst case,
     *       where V is the number of vertices and E is the number of edges in the graph.
     *       However, it may terminate earlier if the end vertex is reached.
     * @note This method assumes that edge weights are non-negative.
     * @note If start or end is greater than or equal to the number of vertices, -1 is returned.
     */
    [[nodiscard]] int dijkstra(int start, int end) const;
};

#endif //DSA_DIJKSTRA_H
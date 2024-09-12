#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#include <vector>
#include <utility>
#include <limits>

/**
 * @class WeightedGraph
 * @brief A class representing a weighted graph.
 *
 * This class implements a weighted graph using an adjacency list representation.
 * It provides methods for adding weighted edges, finding shortest paths using
 * Dijkstra's algorithm, and finding Minimum Spanning Trees using Kruskal's and
 * Prim's algorithms.
 *
 * @note Vertices are zero-indexed.
 */
class WeightedGraph {
public:
    /**
     * @struct Edge
     * @brief Structure representing an edge in the graph
     */
    struct Edge {
        int u; ///< Source vertex
        int v; ///< Destination vertex
        int w; ///< Weight of the edge

        Edge(int u, int v, int w) : u(u), v(v), w(w) {}

        bool operator<(const Edge& other) const { return w < other.w; }
    };

private:
    int _size; ///< Number of vertices in the graph
    std::vector<std::vector<std::pair<int, int>>> _adjacency_list; ///< Adjacency list representation (vertex, weight)

public:
    /**
     * @brief Construct a new WeightedGraph object
     * @param size Number of vertices in the graph
     */
    explicit WeightedGraph(int size);

    /**
     * @brief Add a weighted edge to the graph
     * @param from Source vertex
     * @param to Destination vertex
     * @param weight Weight of the edge
     * @throw std::out_of_range if either vertex is out of range
     */
    void add_edge(int from, int to, int weight);

    /**
     * @brief Perform Dijkstra's algorithm to find shortest paths from a start vertex
     * @param start Starting vertex
     * @return std::vector<int> Shortest distances from start to all other vertices
     * @throw std::out_of_range if start vertex is out of range
     */
    [[nodiscard]] std::vector<int> dijkstra(int start) const;

    /**
     * @brief Perform Dijkstra's algorithm to find shortest path between two vertices
     * @param start Starting vertex
     * @param end Ending vertex
     * @return int Shortest distance from start to end (-1 if no path exists)
     * @throw std::out_of_range if either vertex is out of range
     */
    [[nodiscard]] int dijkstra(int start, int end) const;

    /**
     * @brief Perform Kruskal's algorithm to find Minimum Spanning Tree
     * @return std::vector<Edge> Edges in the Minimum Spanning Tree
     */
    [[nodiscard]] std::vector<Edge> kruskal_mst() const;

    /**
     * @brief Perform Prim's algorithm to find Minimum Spanning Tree
     * @return std::vector<Edge> Edges in the Minimum Spanning Tree
     */
    [[nodiscard]] std::vector<Edge> prim_mst() const;

    /**
     * @brief Get the number of vertices in the graph
     * @return int Number of vertices
     */
    [[nodiscard]] int size() const { return _size; }

    /**
     * @brief Get the adjacency list representation of the graph
     * @return const std::vector<std::vector<std::pair<int, int>>>& Adjacency list
     */
    [[nodiscard]] const std::vector<std::vector<std::pair<int, int>>>& get_adj_list() const { return _adjacency_list; }
};

#endif // WEIGHTED_GRAPH_H
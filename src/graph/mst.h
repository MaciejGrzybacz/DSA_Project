#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <utility>
#include <algorithm>
#include <queue>
#include <limits>
#include "src/data_structures/union_find.h"


/**
 * @brief A class representing a graph for Minimum Spanning Tree algorithms
 *
 * This class implements a graph structure suitable for MST algorithms such as
 * Kruskal's and Prim's. The graph is represented as an adjacency list, which
 * provides efficient access to neighboring vertices.
 *
 * MSTs have various practical applications including:
 * - Network design (computer, telecommunication, transportation, etc.)
 * - Approximation algorithms for NP-hard problems
 * - Cluster analysis in data mining and machine learning
 * - Image processing (segmentation and registration)
 * - Creating taxonomies in biology and linguistics
 * - Circuit design to minimize wiring
 */
class MSTGraph {
public:
    /**
     * @brief A structure representing an edge in the graph
     */
    struct Edge {
        int u; ///< Source vertex
        int v; ///< Destination vertex
        int w; ///< Weight of the edge

        Edge(int u, int v, int w) : u(u), v(v), w(w) {}
    };

private:
    int _size; ///< Number of vertices in the graph
    std::vector<std::vector<std::pair<int, int>>> adj_list; ///< Adjacency list: vector of (vertex, weight) pairs for each vertex

public:
    /**
     * @brief Construct a new MSTGraph object
     * @param vertices Number of vertices in the graph
     */
    explicit MSTGraph(int vertices);

    /**
     * @brief Add an edge to the graph
     * @param u Source vertex
     * @param v Destination vertex
     * @param w Weight of the edge
     */
    void add_edge(int u, int v, int w);

    /**
     * @brief Kruskal's algorithm to find Minimum Spanning Tree
     * @return Vector of Edges representing the Minimum Spanning Tree
     */
    std::vector<Edge> kruskal_mst();

    /**
     * @brief Prim's algorithm to find Minimum Spanning Tree
     * @return Vector of Edges representing the Minimum Spanning Tree
     */
    std::vector<Edge> prim_mst();

    /**
     * @brief Get the number of vertices in the graph
     * @return Number of vertices
     */
    [[nodiscard]] int size() const { return _size; }

    /**
     * @brief Get the adjacency list of the graph
     * @return Const reference to the adjacency list
     */
    [[nodiscard]] const std::vector<std::vector<std::pair<int, int>>>& get_adj_list() const { return adj_list; }
};

#endif // GRAPH_H
#ifndef UNWEIGHTED_GRAPH_H
#define UNWEIGHTED_GRAPH_H

#include <vector>
#include <queue>
#include <stack>
#include <algorithm>

/**
 * @class UnweightedGraph
 * @brief A class representing an unweighted graph.
 *
 * This class implements an unweighted graph using an adjacency list representation.
 * It provides methods for adding edges, performing graph traversals (BFS and DFS),
 * and topological sorting.
 *
 * @note Vertices are zero-indexed.
 */
class UnweightedGraph {
private:
    int _size; ///< Number of vertices in the graph
    std::vector<std::vector<int>> _adjacency_list; ///< Adjacency list representation

public:
    /**
     * @brief Construct a new UnweightedGraph object
     * @param size Number of vertices in the graph
     */
    explicit UnweightedGraph(int size);

    /**
     * @brief Add an edge to the graph
     * @param from Source vertex
     * @param to Destination vertex
     * @throw std::out_of_range if either vertex is out of range
     */
    void add_edge(int from, int to);

    /**
     * @brief Perform Breadth-First Search (BFS) starting from a given vertex
     * @param start Starting vertex for BFS
     * @return std::pair<std::vector<int>, std::vector<int>> 
     *         First vector: parent of each vertex in BFS tree (-1 for unreachable vertices)
     *         Second vector: distance from start to each vertex (-1 for unreachable vertices)
     * @throw std::out_of_range if start vertex is out of range
     */
    [[nodiscard]] std::pair<std::vector<int>, std::vector<int>> bfs(int start) const;

    /**
     * @brief Perform iterative Depth-First Search (DFS) starting from a given vertex
     * @param start Starting vertex for DFS
     * @return std::pair<std::vector<int>, std::vector<int>> 
     *         First vector: parent of each vertex in DFS tree (-1 for unreachable vertices)
     *         Second vector: discovery time of each vertex (-1 for unreachable vertices)
     * @throw std::out_of_range if start vertex is out of range
     */
    [[nodiscard]] std::pair<std::vector<int>, std::vector<int>> dfs(int start) const;

    /**
     * @brief Perform recursive Depth-First Search (DFS) starting from a given vertex
     * @param start Starting vertex for DFS
     * @return std::pair<std::vector<int>, std::vector<int>> 
     *         First vector: parent of each vertex in DFS tree (-1 for unreachable vertices)
     *         Second vector: discovery time of each vertex (-1 for unreachable vertices)
     * @throw std::out_of_range if start vertex is out of range
     */
    [[nodiscard]] std::pair<std::vector<int>, std::vector<int>> dfs_recursive(int start) const;

    /**
     * @brief Perform topological sorting using Kahn's algorithm
     * @return std::vector<int> Vertices in topological order (empty if graph has a cycle)
     */
    [[nodiscard]] std::vector<int> topological_sort() const;

    /**
     * @brief Get the number of vertices in the graph
     * @return int Number of vertices
     */
    [[nodiscard]] int size() const { return _size; }

    /**
     * @brief Get the adjacency list representation of the graph
     * @return const std::vector<std::vector<int>>& Adjacency list
     */
    [[nodiscard]] const std::vector<std::vector<int>>& get_adj_list() const { return _adjacency_list; }

private:
    /**
     * @brief Helper function for recursive DFS
     * @param v Current vertex
     * @param parent Vector to store parent of each vertex
     * @param discovery_time Vector to store discovery time of each vertex
     * @param time Current time (modified during traversal)
     */
    void dfs_visit(int v, std::vector<int>& parent, std::vector<int>& discovery_time, int& time) const;
};

#endif // UNWEIGHTED_GRAPH_H
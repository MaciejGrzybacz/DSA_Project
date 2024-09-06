#ifndef DSA_PROJECT_SEARCH_H
#define DSA_PROJECT_SEARCH_H

#include <vector>
#include <queue>
#include <stack>

/**
 * @brief A class representing a directed graph and implementing graph search algorithms.
 *
 * This class provides a representation of a directed graph using an adjacency list.
 * It includes methods for adding edges to the graph and performing various graph
 * search algorithms such as Breadth-First Search (BFS) and Depth-First Search (DFS).
 *
 * The graph is represented internally using an adjacency list, which allows for
 * efficient storage and traversal of sparse graphs.
 *
 * @note The graph is zero-indexed, meaning vertex indices range from 0 to size-1.
 * @note This implementation assumes a directed graph. For an undirected graph,
 *       edges should be added in both directions.
 */
class Graph {
private:
    std::vector<std::vector<int>> _adjacency_list;
    int _size;

public:
    /**
     * @brief Constructs a Graph object with the specified number of vertices.
     * @param size The number of vertices in the graph.
     */
    explicit Graph(int size) : _size(size), _adjacency_list(size) {};

    /**
     * @brief Adds a directed edge to the graph.
     * @param from The index of the source vertex.
     * @param to The index of the destination vertex.
     */
    void add_edge(int from, int to) {
        _adjacency_list[from].push_back(to);
    };

    /**
     * @brief Performs a Breadth-First Search (BFS) on the graph.
     *
     * This method implements the BFS algorithm starting from a given vertex.
     * It explores all the vertices in the graph in breadth-first order and
     * computes the shortest path from the start vertex to all other vertices.
     *
     * @param start The index of the starting vertex for BFS.
     * @return A pair of vectors:
     *         - The first vector (parent) contains the parent of each vertex in the BFS tree.
     *           parent[i] is the parent of vertex i in the BFS tree, or -1 if i is unreachable or the start vertex.
     *         - The second vector (distance) contains the shortest distance from the start vertex to each vertex.
     *           distance[i] is the shortest distance from start to vertex i, or -1 if i is unreachable.
     *
     * @note The time complexity of this implementation is O(V + E), where V is the number of vertices
     *       and E is the number of edges in the graph.
     */
    [[nodiscard]] std::pair<std::vector<int>, std::vector<int>> bfs(int start) const;

    /**
     * @brief Performs a Depth-First Search (DFS) on the graph.
     *
     * This method implements the DFS algorithm starting from a given vertex.
     * It explores all the vertices in the graph in depth-first order.
     *
     * @param start The index of the starting vertex for DFS.
     * @return A pair of vectors:
     *         - The first vector (parent) contains the parent of each vertex in the DFS tree.
     *           parent[i] is the parent of vertex i in the DFS tree, or -1 if i is unreachable or the start vertex.
     *         - The second vector (discovery_time) contains the discovery time of each vertex.
     *           discovery_time[i] is the time at which vertex i was first discovered during the DFS,
     *           or -1 if i is unreachable.
     *
     * @note The time complexity of this implementation is O(V + E), where V is the number of vertices
     *       and E is the number of edges in the graph.
     * @note This method uses an iterative approach with a stack to avoid potential stack overflow issues.
     */
    [[nodiscard]] std::pair<std::vector<int>, std::vector<int>> dfs(int start) const;

    /**
    * @brief Performs a recursive Depth-First Search (DFS) on the graph.
    *
    * This method implements the DFS algorithm starting from a given vertex
    * using a recursive approach. It explores all the vertices in the graph
    * in depth-first order.
    *
    * @param start The index of the starting vertex for DFS.
    * @return A pair of vectors:
    *         - The first vector (parent) contains the parent of each vertex in the DFS tree.
    *           parent[i] is the parent of vertex i in the DFS tree, or -1 if i is unreachable or the start vertex.
    *         - The second vector (discovery_time) contains the discovery time of each vertex.
    *           discovery_time[i] is the time at which vertex i was first discovered during the DFS,
    *           or -1 if i is unreachable.
    *
    * @note The time complexity of this implementation is O(V + E), where V is the number of vertices
    *       and E is the number of edges in the graph.
    * @warning This method may cause stack overflow for very large graphs due to its recursive nature.
    *          Consider using the iterative version (dfs) for large graphs.
    */
    [[nodiscard]] std::pair<std::vector<int>, std::vector<int>> dfs_recursive(int start) const;

private:
    /**
     * @brief Helper method for recursive Depth-First Search.
     *
     * This private method is called recursively by dfs_recursive to perform the actual depth-first traversal.
     * It visits a vertex, marks it as discovered, and recursively visits all its unvisited neighbors.
     *
     * @param v The current vertex being visited.
     * @param parent Vector to store the parent of each vertex in the DFS tree.
     * @param discovery_time Vector to store the discovery time of each vertex.
     * @param time Reference to the current time, used for recording discovery times.
     *
     * @note This method modifies the parent and discovery_time vectors in-place.
     * @note The time complexity for a single call is O(E), where E is the number of edges
     *       connected to the current vertex. The overall complexity of the DFS is still O(V + E).
     */
    void dfs_visit(int v, std::vector<int>& parent, std::vector<int>& discovery_time, int& time) const;
};


#endif //DSA_PROJECT_SEARCH_H
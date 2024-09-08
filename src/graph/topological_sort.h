#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <queue>

/**
 * @brief A class representing a directed graph with topological sorting functionality using Kahn's algorithm.
 *
 * This class provides a representation of a directed graph using an adjacency list.
 * It includes methods for adding edges to the graph and performing topological sorting
 * using Kahn's algorithm. The graph is represented internally using an adjacency list,
 * which allows for efficient storage and traversal of sparse graphs.
 *
 * @note The graph is zero-indexed, meaning vertex indices range from 0 to size-1.
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
    explicit Graph(int size);

    /**
     * @brief Adds a directed edge to the graph.
     * @param from The index of the source vertex.
     * @param to The index of the destination vertex.
     */
    void addEdge(int from, int to);

    /**
     * @brief Performs topological sorting of the graph using Kahn's algorithm.
     *
     * This method implements Kahn's algorithm for topological sorting.
     * It uses a queue to keep track of nodes with no incoming edges and
     * systematically removes edges from the graph, adding nodes to the result
     * as they become free of incoming edges.
     *
     * @return A vector of integers representing the vertices in topological order,
     *         or an empty vector if the graph contains a cycle.
     *
     * @note The time complexity of this implementation is O(V + E), where V is the number of vertices
     *       and E is the number of edges in the graph.
     */
    std::vector<int> topologicalSort();
};

#endif // GRAPH_H
#include "weighted_graph.h"
#include <queue>
#include <algorithm>
#include <limits>
#include <stdexcept>
#include "src/data_structures/union_find.h"

WeightedGraph::WeightedGraph(int size) : _size(size), _adjacency_list(size) {}

void WeightedGraph::add_edge(int from, int to, int weight) {
    if (from < 0 || from >= _size || to < 0 || to >= _size) {
        throw std::out_of_range("Vertex index out of range");
    }
    if (weight < 0) {
        throw std::invalid_argument("Edge weight cannot be negative");
    }
    _adjacency_list[from].emplace_back(to, weight);
    _adjacency_list[to].emplace_back(from, weight);
}

std::vector<int> WeightedGraph::dijkstra(int start) const {
    if (start < 0 || start >= _size) {
        throw std::out_of_range("Start vertex index out of range");
    }

    std::vector<int> dist(_size, std::numeric_limits<int>::max());
    std::vector<bool> visited(_size, false);
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;

    pq.push({0, start});
    dist[start] = 0;

    while (!pq.empty()) {
        int current_vertex = pq.top().second;
        pq.pop();

        if (visited[current_vertex]) continue;
        visited[current_vertex] = true;

        for (const auto& [end, d] : _adjacency_list[current_vertex]) {
            if (!visited[end] && dist[current_vertex] + d < dist[end]) {
                dist[end] = dist[current_vertex] + d;
                pq.push({dist[end], end});
            }
        }
    }

    return dist;
}

int WeightedGraph::dijkstra(int start, int end) const {
    if (start < 0 || start >= _size || end < 0 || end >= _size) {
        throw std::out_of_range("Vertex index out of range");
    }

    std::vector<int> dist(_size, std::numeric_limits<int>::max());
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;

    pq.push({0, start});
    dist[start] = 0;

    while (!pq.empty()) {
        int current_vertex = pq.top().second;
        int current_dist = pq.top().first;
        pq.pop();

        if (current_vertex == end) return current_dist;

        if (current_dist > dist[current_vertex]) continue;

        for (const auto& [end_vertex, d] : _adjacency_list[current_vertex]) {
            if (dist[current_vertex] + d < dist[end_vertex]) {
                dist[end_vertex] = dist[current_vertex] + d;
                pq.push({dist[end_vertex], end_vertex});
            }
        }
    }

    return -1; // Path not found
}

std::vector<WeightedGraph::Edge> WeightedGraph::kruskal_mst() const {
    std::vector<Edge> all_edges;
    for (int u = 0; u < _size; ++u) {
        for (const auto& [v, w] : _adjacency_list[u]) {
            if (u < v) { // Avoid duplicate edges to improve efficiency
                all_edges.emplace_back(u, v, w);
            }
        }
    }

    std::vector<Edge> mst;
    UnionFind uf(_size);

    std::sort(all_edges.begin(), all_edges.end());

    for (const auto& edge : all_edges) {
        if (uf.find(edge.u) != uf.find(edge.v)) {
            uf.unite(edge.u, edge.v);
            mst.push_back(edge);
        }
    }

    return mst.size() == _size - 1 ? mst : std::vector<Edge>();
}

std::vector<WeightedGraph::Edge> WeightedGraph::prim_mst() const {
    std::vector<Edge> mst;
    std::vector<bool> visited(_size, false);
    std::vector<int> key(_size, std::numeric_limits<int>::max());
    std::vector<int> parent(_size, -1);

    std::priority_queue<std::pair<int, int>,
            std::vector<std::pair<int, int>>,
            std::greater<>> pq;

    pq.emplace(0, 0);
    key[0] = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;

        if (parent[u] != -1) {
            mst.emplace_back(parent[u], u, key[u]);
        }

        for (const auto& [v, weight] : _adjacency_list[u]) {
            if (!visited[v] && weight < key[v]) {
                parent[v] = u;
                key[v] = weight;
                pq.emplace(key[v], v);
            }
        }
    }

    return mst.size() == _size - 1 ? mst : std::vector<Edge>();
}
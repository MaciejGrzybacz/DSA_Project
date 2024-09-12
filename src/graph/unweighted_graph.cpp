#include "unweighted_graph.h"
#include <queue>
#include <stack>
#include <stdexcept>

UnweightedGraph::UnweightedGraph(int size) : _size(size), _adjacency_list(size) {}

void UnweightedGraph::add_edge(int from, int to) {
    if (from < 0 || from >= _size || to < 0 || to >= _size) {
        throw std::out_of_range("Vertex index out of range");
    }
    _adjacency_list[from].push_back(to);
}

std::pair<std::vector<int>, std::vector<int>> UnweightedGraph::bfs(int start) const {
    if (start < 0 || start >= _size) {
        throw std::out_of_range("Start vertex index out of range");
    }
    std::vector<int> parent(_size, -1), distance(_size, -1);
    std::vector<bool> visited(_size, false);
    std::queue<int> q;

    q.push(start);
    distance[start] = 0;
    visited[start] = true;

    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        for (int neighbour : _adjacency_list[curr]) {
            if (!visited[neighbour]) {
                visited[neighbour] = true;
                distance[neighbour] = distance[curr] + 1;
                parent[neighbour] = curr;
                q.push(neighbour);
            }
        }
    }

    return {parent, distance};
}

std::pair<std::vector<int>, std::vector<int>> UnweightedGraph::dfs(int start) const {
    if (start < 0 || start >= _size) {
        throw std::out_of_range("Start vertex index out of range");
    }
    std::vector<int> parent(_size, -1);
    std::vector<int> discovery_time(_size, -1);
    std::stack<int> s;
    s.push(start);
    int time = 0;

    while (!s.empty()) {
        int curr = s.top();
        s.pop();

        if (discovery_time[curr] == -1) {
            discovery_time[curr] = time++;
            for (int neighbour : _adjacency_list[curr]) {
                if (discovery_time[neighbour] == -1) {
                    parent[neighbour] = curr;
                    s.push(neighbour);
                }
            }
        }
    }

    return {parent, discovery_time};
}

std::pair<std::vector<int>, std::vector<int>> UnweightedGraph::dfs_recursive(int start) const {
    if (start < 0 || start >= _size) {
        throw std::out_of_range("Start vertex index out of range");
    }
    std::vector<int> parent(_size, -1);
    std::vector<int> discovery_time(_size, -1);
    int time = 0;
    dfs_visit(start, parent, discovery_time, time);
    return {parent, discovery_time};
}

void UnweightedGraph::dfs_visit(int v, std::vector<int> &parent, std::vector<int> &discovery_time, int &time) const {
    discovery_time[v] = time++;
    for (int neighbour : _adjacency_list[v]) {
        if (discovery_time[neighbour] == -1) {
            parent[neighbour] = v;
            dfs_visit(neighbour, parent, discovery_time, time);
        }
    }
}

std::vector<int> UnweightedGraph::topological_sort() const {
    std::vector<int> in_degree(_size, 0);
    std::queue<int> q;
    std::vector<int> result;

    for (const auto& v : _adjacency_list) {
        for (int x : v) {
            in_degree[x]++;
        }
    }

    for (int i = 0; i < _size; i++) {
        if (in_degree[i] == 0) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int curr_vertex = q.front();
        q.pop();
        result.push_back(curr_vertex);

        for (int v : _adjacency_list[curr_vertex]) {
            in_degree[v]--;
            if (in_degree[v] == 0) q.push(v);
        }
    }

    if (result.size() == _size) return result;
    return {};
}
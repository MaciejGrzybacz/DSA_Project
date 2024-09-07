#include "topological_sort.h"


Graph::Graph(int size) : _size(size), _adjacency_list(size) {}

void Graph::addEdge(int from, int to) {
    _adjacency_list[from].push_back(to);
}

std::vector<int> Graph::topologicalSort() {
    std::vector<int> in_degree(_size, 0);
    std::queue<int> q;
    std::vector<int> result;

    for(auto v : _adjacency_list)
        for(auto x : v)
            in_degree[x]++;

    for (int i = 0; i < _size; i++) {
        if (in_degree[i] == 0) {
            q.push(i);
        }
    }
    
    while(!q.empty()) {
        int curr_vertex = q.front(); q.pop();
        result.push_back(curr_vertex);

        for(int v : _adjacency_list[curr_vertex]) {
            in_degree[v]--;
            if(in_degree[v] == 0) q.push(v);
        }
    }

    if(result.size() == _size) return result;
    return {};
}

#include "mst.h"

MSTGraph::MSTGraph(int vertices) : _size(vertices), adj_list(vertices) {}

void MSTGraph::add_edge(int u, int v, int w) {
    adj_list[u].emplace_back(v, w);
    adj_list[v].emplace_back(u, w);
}

std::vector<MSTGraph::Edge> MSTGraph::kruskal_mst() {
    std::vector<Edge> all_edges;
    for (int u = 0; u < _size; ++u) {
        for (const auto& [v, w] : adj_list[u]) {
            if (u < v) { 
                all_edges.emplace_back(u, v, w);
            }
        }
    }

    std::vector<Edge> mst;
    UnionFind uf(_size);

    std::sort(all_edges.begin(), all_edges.end(),
              [](const Edge& a, const Edge& b) { return a.w < b.w; });

    for (const auto& edge : all_edges) {
        if (uf.find(edge.u) != uf.find(edge.v)) {
            uf.unite(edge.u, edge.v);
            mst.push_back(edge);
        }
    }

    return mst.size() == _size - 1 ? mst : std::vector<Edge>();
}

std::vector<MSTGraph::Edge> MSTGraph::prim_mst() {
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

        for (const auto& [v, weight] : adj_list[u]) {
            if (!visited[v] && weight < key[v]) {
                parent[v] = u;
                key[v] = weight;
                pq.emplace(key[v], v);
            }
        }
    }

    return mst.size() == _size - 1 ? mst : std::vector<Edge>();
}
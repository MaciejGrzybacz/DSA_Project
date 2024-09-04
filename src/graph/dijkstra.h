#ifndef DSA_DIJKSTRA_H
#define DSA_DIJKSTRA_H

#include <vector>

class Graph {
private:
    struct Edge {
        int _to;
        int _weight;
    };

    int _vertices;
    std::vector<std::vector<Edge>> _adjacency_list;

public:
    explicit Graph(int vertices) : _vertices(vertices), _adjacency_list(vertices) {};

    void add_edge(int from, int to, int weight) {
        _adjacency_list[from].push_back(Edge{to, weight});
    };

    [[nodiscard]] std::vector<int> dijkstra(int start) const;

    [[nodiscard]] int dijkstra(int start, int end) const;
};

#endif //DSA_DIJKSTRA_H

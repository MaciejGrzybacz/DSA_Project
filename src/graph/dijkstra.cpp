#include "dijkstra.h"

std::vector<int> Graph::dijkstra(int start) const {
    if(_size == 0) return {};

    std::vector<int> dist(_size, INT_MAX);
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

int Graph::dijkstra(int start, int end) const {
    if (start >= _size || end >= _size) return -1;

    std::vector<int> dist(_size, INT_MAX);
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

    return -1;
}
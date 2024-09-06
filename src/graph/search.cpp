#include "search.h"

std::pair<std::vector<int>, std::vector<int>> Graph::bfs(int start) const {
    if(_size == 0) return {};
    std::vector<int> parent(_size, -1), distance(_size, -1);
    std::vector<bool> visited(_size, false);
    std::queue<int> q;

    q.push(start);
    distance[start] = 0;

    while(!q.empty()) {
        int curr = q.front(); q.pop();
        for(int neighbour : _adjacency_list[curr]) {
            if(!visited[neighbour]) {
                distance[neighbour] = distance[curr] + 1;
                parent[neighbour] = curr;
                q.push(neighbour);
            }
        }
    }

    return {parent, distance};
}

std::pair<std::vector<int>, std::vector<int>> Graph::dfs(int start) const {
    if(_size == 0) return {};
    std::vector<int> parent(_size, -1);
    std::vector<int> discovery_time(_size, -1);
    std::stack<int> s;
    s.push(start);
    int time = 0;

    while(!s.empty()) {
        int curr = s.top(); s.pop();

        if(discovery_time[curr] == -1) {
            discovery_time[curr] = time++;
            for(int neighbour : _adjacency_list[curr]) {
                if(discovery_time[neighbour] == -1) {
                    parent[neighbour] = curr;
                    s.push(neighbour);
                }
            }
        }
    }

    return {parent, discovery_time};
}

std::pair<std::vector<int>, std::vector<int>> Graph::dfs_recursive(int start) const {
    if(_size == 0) return {};
    std::vector<int> parent(_size, -1);
    std::vector<int> discovery_time(_size, -1);
    int time = 0;
    dfs_visit(start, parent, discovery_time, time);
    return {parent, discovery_time};
}

void Graph::dfs_visit(int v, std::vector<int> &parent, std::vector<int> &discovery_time, int &time) const {
    discovery_time[v] = time++;
    for(int neighbour : _adjacency_list[v]) {
        if(discovery_time[neighbour] == -1) {
            parent[neighbour] = v;
            dfs_visit(neighbour, parent, discovery_time, time);
        }
    }
}

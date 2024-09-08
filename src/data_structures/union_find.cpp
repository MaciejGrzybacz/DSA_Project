#include "union_find.h"

UnionFind::UnionFind(int n) : number_of_sets(n) {
    parent.resize(n);
    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }
}

int UnionFind::find(int x) {
    if(parent[x] == x) return x;
    else {
        int new_parent = find(parent[x]);
        parent[x] = new_parent;
        return new_parent;
    }
}

void UnionFind::unite(int x, int y) {
    int x_root = find(x);
    int y_root = find(y);
    if(x_root != y_root) {
        parent[y_root] = x_root;
        number_of_sets--;
    }
}

bool UnionFind::connected(int x, int y) {
    return find(x) == find(y);
}

int UnionFind::count() const {
    return number_of_sets;
}
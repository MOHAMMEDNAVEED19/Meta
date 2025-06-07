// union_find.cpp
#include <iostream>
#include <vector>

using namespace std;

class UnionFind {
    vector<int> parent, rank;

public:
    UnionFind(int n) {
        parent.resize(n);
        rank.assign(n, 0);
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    int find(int u) {
        if (u != parent[u])
            parent[u] = find(parent[u]);
        return parent[u];
    }

    void unite(int u, int v) {
        int pu = find(u), pv = find(v);
        if (pu == pv) return;
        if (rank[pu] < rank[pv])
            parent[pu] = pv;
        else {
            parent[pv] = pu;
            if (rank[pu] == rank[pv])
                rank[pu]++;
        }
    }

    bool sameGroup(int u, int v) {
        return find(u) == find(v);
    }
};

int main() {
    UnionFind uf(5);
    uf.unite(0, 1);
    uf.unite(2, 3);
    cout << uf.sameGroup(0, 1) << endl; // 1
    cout << uf.sameGroup(1, 2) << endl; // 0
    return 0;
}

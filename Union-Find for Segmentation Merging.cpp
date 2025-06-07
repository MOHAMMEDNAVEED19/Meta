// union_find_segmentation.cpp
#include <iostream>
#include <vector>

using namespace std;

class UnionFind {
    vector<int> parent, rank;

public:
    UnionFind(int n) : parent(n), rank(n, 0) {
        for(int i=0; i<n; i++) parent[i] = i;
    }

    int find(int u) {
        if(u != parent[u])
            parent[u] = find(parent[u]);
        return parent[u];
    }

    void unite(int u, int v) {
        int ru = find(u), rv = find(v);
        if(ru == rv) return;
        if(rank[ru] < rank[rv]) swap(ru, rv);
        parent[rv] = ru;
        if(rank[ru] == rank[rv]) rank[ru]++;
    }
};

int main() {
    UnionFind uf(10);
    uf.unite(1, 2);
    uf.unite(2, 3);
    uf.unite(5, 6);
    cout << "Region 1 and 3 connected? " << (uf.find(1) == uf.find(3)) << endl;
    cout << "Region 1 and 5 connected? " << (uf.find(1) == uf.find(5)) << endl;
    return 0;
}

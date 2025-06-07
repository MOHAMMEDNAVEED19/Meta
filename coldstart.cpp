// cold_start_bfs.cpp
#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

class Graph {
    unordered_map<int, vector<int>> adj;

public:
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); // undirected
    }

    void boostDiscovery(int start) {
        unordered_set<int> visited;
        queue<int> q;
        q.push(start);
        visited.insert(start);

        cout << "Boosting for new creator from node " << start << ":\n";

        while (!q.empty()) {
            int u = q.front(); q.pop();
            cout << "Reach: " << u << endl;
            for (int v : adj[u]) {
                if (!visited.count(v)) {
                    visited.insert(v);
                    q.push(v);
                }
            }
        }
    }
};

int main() {
    Graph g;
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(2, 5);
    g.boostDiscovery(5);
    return 0;
}

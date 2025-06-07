// graph_recommendation.cpp
#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

class Graph {
    unordered_map<int, vector<int>> adj;
    unordered_map<int, double> rank;
    double damping = 0.85;
    int iterations = 20;

public:
    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    void personalizedPageRank(int startNode) {
        unordered_map<int, double> pr, temp;
        for (auto& p : adj) {
            pr[p.first] = (p.first == startNode) ? 1.0 : 0.0;
        }

        for (int i = 0; i < iterations; ++i) {
            temp = pr;
            for (auto& p : adj) {
                int u = p.first;
                double share = temp[u] / adj[u].size();
                for (int v : adj[u]) {
                    pr[v] += damping * share;
                }
                pr[u] = (1 - damping) * ((u == startNode) ? 1.0 : 0.0);
            }
        }

        cout << "Personalized PageRank Scores:\n";
        for (auto& p : pr) {
            cout << "Node " << p.first << ": " << p.second << endl;
        }
    }
};

int main() {
    Graph g;
    g.addEdge(1, 2); g.addEdge(2, 3);
    g.addEdge(3, 4); g.addEdge(4, 1);
    g.personalizedPageRank(1);
    return 0;
}

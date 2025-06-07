// audience_analysis_graph.cpp
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

void bfs(int src, vector<vector<int>>& graph, vector<bool>& visited, vector<int>& community) {
    queue<int> q;
    q.push(src);
    visited[src] = true;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        community.push_back(u);

        for (int v : graph[u]) {
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
}

void detectCommunities(vector<vector<int>>& graph) {
    int n = graph.size();
    vector<bool> visited(n, false);
    vector<vector<int>> communities;

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            vector<int> community;
            bfs(i, graph, visited, community);
            communities.push_back(community);
        }
    }

    for (int i = 0; i < communities.size(); ++i) {
        cout << "Community " << i + 1 << ": ";
        for (int user : communities[i])
            cout << user << " ";
        cout << "\n";
    }
}

int main() {
    vector<vector<int>> graph = {
        {1, 2}, {0, 3}, {0}, {1},       // Community 1
        {5, 6}, {4, 6}, {4, 5},         // Community 2
        {8}, {7}                        // Community 3
    };
    detectCommunities(graph);
    return 0;
}

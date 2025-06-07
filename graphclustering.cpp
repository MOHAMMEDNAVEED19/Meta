// graph_clustering_events.cpp
#include <iostream>
#include <vector>

using namespace std;

void dfs(int u, const vector<vector<int>>& graph, vector<bool>& visited, vector<int>& cluster) {
    visited[u] = true;
    cluster.push_back(u);
    for (int v : graph[u]) {
        if (!visited[v])
            dfs(v, graph, visited, cluster);
    }
}

int main() {
    int n = 6;
    vector<vector<int>> graph = {
        {1, 2}, {0, 2}, {0, 1}, {4}, {3, 5}, {4}  // Two clusters: [0,1,2] and [3,4,5]
    };
    vector<bool> visited(n, false);

    vector<vector<int>> eventClusters;
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            vector<int> cluster;
            dfs(i, graph, visited, cluster);
            eventClusters.push_back(cluster);
        }
    }

    for (int i = 0; i < eventClusters.size(); ++i) {
        cout << "Event Cluster " << i + 1 << ": ";
        for (int node : eventClusters[i])
            cout << node << " ";
        cout << endl;
    }

    return 0;
}

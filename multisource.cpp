// multi_source_bfs_labeling.cpp
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void multiSourceBFS(const vector<vector<int>>& graph, const vector<int>& sources) {
    int n = graph.size();
    vector<int> distance(n, -1);
    queue<int> q;

    for (int src : sources) {
        q.push(src);
        distance[src] = 0;
    }

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : graph[u]) {
            if (distance[v] == -1) {
                distance[v] = distance[u] + 1;
                q.push(v);
            }
        }
    }

    for (int i = 0; i < n; ++i)
        cout << "Node " << i << " reached in " << distance[i] << " steps.\n";
}

int main() {
    vector<vector<int>> graph = {
        {1, 2}, {0, 3}, {0, 4}, {1}, {2, 5}, {4}
    };
    vector<int> sources = {0, 5}; // multiple origin posts
    multiSourceBFS(graph, sources);
    return 0;
}

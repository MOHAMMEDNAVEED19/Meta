// floyd_warshall_tag_propagation.cpp
#include <iostream>
#include <vector>
#include <climits>

using namespace std;

const int INF = 1e9;

void floydWarshall(vector<vector<int>>& graph, int n) {
    vector<vector<int>> dist = graph;

    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];

    cout << "Shortest context-aware tag distances:\n";
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cout << "From " << i << " to " << j << ": " << (dist[i][j] >= INF ? -1 : dist[i][j]) << endl;
}

int main() {
    int n = 4;
    vector<vector<int>> graph = {
        {0, 3, INF, 7},
        {8, 0, 2, INF},
        {5, INF, 0, 1},
        {2, INF, INF, 0}
    };

    floydWarshall(graph, n);
    return 0;
}

#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <iomanip>

using namespace std;

class VideoPageRank {
private:
    const double damping = 0.85;
    const double tolerance = 1e-6;
    int max_iterations = 20;
    
    unordered_map<int, vector<int>> graph; // video -> outgoing links
    unordered_map<int, double> page_rank;
    unordered_map<int, int> out_degree;
    
public:
    void addEdge(int from, int to) {
        graph[from].push_back(to);
        out_degree[from]++;
    }
    
    void computePageRank() {
        unordered_map<int, double> new_rank;
        const double initial_rank = 1.0 / graph.size();
        
        // Initialize ranks
        for (const auto& [video, _] : graph) {
            page_rank[video] = initial_rank;
        }
        
        // Power iteration
        for (int iter = 0; iter < max_iterations; ++iter) {
            double dangling_sum = 0.0;
            
            // Calculate dangling nodes contribution
            for (const auto& [video, _] : graph) {
                if (out_degree[video] == 0) {
                    dangling_sum += page_rank[video];
                }
            }
            
            // Distribute dangling sum and apply damping factor
            for (const auto& [video, _] : graph) {
                new_rank[video] = (1.0 - damping) / graph.size() + 
                                 damping * dangling_sum / graph.size();
            }
            
            // Normal PageRank updates
            for (const auto& [source, targets] : graph) {
                if (out_degree[source] > 0) {
                    double share = page_rank[source] / out_degree[source];
                    for (int target : targets) {
                        new_rank[target] += damping * share;
                    }
                }
            }
            
            // Check convergence
            double diff = 0.0;
            for (const auto& [video, rank] : page_rank) {
                diff += abs(new_rank[video] - rank);
            }
            
            page_rank = new_rank;
            if (diff < tolerance) break;
        }
    }
    
    void printTopVideos(int k = 10) {
        vector<pair<int, double>> ranked_videos(page_rank.begin(), page_rank.end());
        sort(ranked_videos.begin(), ranked_videos.end(), 
             [](const auto& a, const auto& b) { return a.second > b.second; });
        
        cout << "Top " << k << " videos by PageRank:\n";
        for (int i = 0; i < min(k, (int)ranked_videos.size()); ++i) {
            cout << "Video " << ranked_videos[i].first << ": " 
                 << fixed << setprecision(6) << ranked_videos[i].second << endl;
        }
    }
};

int main() {
    VideoPageRank pagerank;
    
    // Build video interaction graph (user shares/video views)
    pagerank.addEdge(1, 2); // Video 1 links to video 2
    pagerank.addEdge(2, 3);
    pagerank.addEdge(3, 1);
    pagerank.addEdge(4, 1);
    pagerank.addEdge(4, 2);
    pagerank.addEdge(4, 3);
    pagerank.addEdge(5, 4);
    pagerank.addEdge(6, 4);
    pagerank.addEdge(7, 4);
    
    pagerank.computePageRank();
    pagerank.printTopVideos();
    
    return 0;
}

#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <limits>

using namespace std;

struct Video {
    int id;
    vector<double> embedding; // Content features (topic, mood, etc.)
};

class VideoClusterer {
private:
    int k;
    vector<Video> videos;
    vector<vector<double>> centroids;
    vector<int> assignments;
    
    double euclideanDistance(const vector<double>& a, const vector<double>& b) {
        double sum = 0.0;
        for (size_t i = 0; i < a.size(); ++i) {
            sum += pow(a[i] - b[i], 2);
        }
        return sqrt(sum);
    }
    
    void initializeCentroids() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(0, videos.size() - 1);
        
        centroids.clear();
        for (int i = 0; i < k; ++i) {
            centroids.push_back(videos[dist(gen)].embedding);
        }
    }
    
    void assignClusters() {
        for (size_t i = 0; i < videos.size(); ++i) {
            double min_dist = numeric_limits<double>::max();
            int best_cluster = 0;
            
            for (int j = 0; j < k; ++j) {
                double dist = euclideanDistance(videos[i].embedding, centroids[j]);
                if (dist < min_dist) {
                    min_dist = dist;
                    best_cluster = j;
                }
            }
            assignments[i] = best_cluster;
        }
    }
    
    void updateCentroids() {
        vector<vector<double>> new_centroids(k, vector<double>(videos[0].embedding.size(), 0.0));
        vector<int> counts(k, 0);
        
        for (size_t i = 0; i < videos.size(); ++i) {
            int cluster = assignments[i];
            for (size_t j = 0; j < videos[i].embedding.size(); ++j) {
                new_centroids[cluster][j] += videos[i].embedding[j];
            }
            counts[cluster]++;
        }
        
        for (int i = 0; i < k; ++i) {
            if (counts[i] > 0) {
                for (size_t j = 0; j < new_centroids[i].size(); ++j) {
                    centroids[i][j] = new_centroids[i][j] / counts[i];
                }
            }
        }
    }
    
public:
    VideoClusterer(int k, const vector<Video>& videos) : k(k), videos(videos) {
        assignments.resize(videos.size());
    }
    
    void cluster(int max_iterations = 100) {
        initializeCentroids();
        
        for (int iter = 0; iter < max_iterations; ++iter) {
            vector<int> old_assignments = assignments;
            
            assignClusters();
            updateCentroids();
            
            // Check for convergence
            if (assignments == old_assignments) {
                break;
            }
        }
    }
    
    vector<vector<Video>> getClusteredVideos() {
        vector<vector<Video>> clusters(k);
        for (size_t i = 0; i < videos.size(); ++i) {
            clusters[assignments[i]].push_back(videos[i]);
        }
        return clusters;
    }
    
    void printClusterSizes() {
        vector<int> sizes(k, 0);
        for (int cluster : assignments) {
            sizes[cluster]++;
        }
        
        cout << "Cluster sizes:\n";
        for (int i = 0; i < k; ++i) {
            cout << "Cluster " << i << ": " << sizes[i] << " videos\n";
        }
    }
};

int main() {
    // Example video data with 3D embeddings (topic, mood, genre)
    vector<Video> videos = {
        {1, {0.8, 0.2, 0.5}},
        {2, {0.6, 0.3, 0.7}},
        {3, {0.1, 0.9, 0.2}},
        {4, {0.2, 0.8, 0.3}},
        {5, {0.7, 0.1, 0.6}},
        {6, {0.9, 0.1, 0.8}},
        {7, {0.3, 0.7, 0.4}},
        {8, {0.4, 0.6, 0.5}},
        {9, {0.5, 0.5, 0.9}},
        {10, {0.1, 0.8, 0.1}}
    };
    
    int k = 3; // Number of clusters
    VideoClusterer clusterer(k, videos);
    clusterer.cluster();
    
    clusterer.printClusterSizes();
    
    // Get clustered videos for diversity sampling
    auto clusters = clusterer.getClusteredVideos();
    
    return 0;
}

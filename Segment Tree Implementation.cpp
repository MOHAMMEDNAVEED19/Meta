#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct EngagementData {
    int likes;
    int comments;
    int shares;
    
    EngagementData operator+(const EngagementData& other) const {
        return {
            likes + other.likes,
            comments + other.comments,
            shares + other.shares
        };
    }
};

class EngagementSegmentTree {
private:
    vector<EngagementData> tree;
    int n;
    
    // Scoring function - adjust weights as needed
    double calculateScore(const EngagementData& data) const {
        const double like_weight = 0.5;
        const double comment_weight = 0.3;
        const double share_weight = 0.2;
        
        return like_weight * data.likes + 
               comment_weight * data.comments + 
               share_weight * data.shares;
    }
    
    void build(const vector<EngagementData>& data, int node, int start, int end) {
        if (start == end) {
            tree[node] = data[start];
        } else {
            int mid = (start + end) / 2;
            build(data, 2 * node + 1, start, mid);
            build(data, 2 * node + 2, mid + 1, end);
            tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
        }
    }
    
    void update(int node, int start, int end, int idx, const EngagementData& diff) {
        if (start == end) {
            tree[node] = tree[node] + diff;
        } else {
            int mid = (start + end) / 2;
            if (idx <= mid) {
                update(2 * node + 1, start, mid, idx, diff);
            } else {
                update(2 * node + 2, mid + 1, end, idx, diff);
            }
            tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
        }
    }
    
    EngagementData query(int node, int start, int end, int l, int r) const {
        if (r < start || end < l) {
            return {0, 0, 0};
        }
        if (l <= start && end <= r) {
            return tree[node];
        }
        int mid = (start + end) / 2;
        return query(2 * node + 1, start, mid, l, r) + 
               query(2 * node + 2, mid + 1, end, l, r);
    }

public:
    EngagementSegmentTree(const vector<EngagementData>& data) {
        n = data.size();
        int height = (int)ceil(log2(n));
        int max_size = 2 * (int)pow(2, height) - 1;
        tree.resize(max_size);
        build(data, 0, 0, n - 1);
    }
    
    void updateEngagement(int idx, const EngagementData& diff) {
        if (idx < 0 || idx >= n) {
            cerr << "Index out of bounds" << endl;
            return;
        }
        update(0, 0, n - 1, idx, diff);
    }
    
    double getScore(int l, int r) const {
        if (l < 0 || r >= n || l > r) {
            cerr << "Invalid range" << endl;
            return 0.0;
        }
        EngagementData data = query(0, 0, n - 1, l, r);
        return calculateScore(data);
    }
    
    vector<pair<int, double>> getTopK(int k) const {
        vector<pair<int, double>> scores;
        for (int i = 0; i < n; ++i) {
            EngagementData data = query(0, 0, n - 1, i, i);
            scores.emplace_back(i, calculateScore(data));
        }
        
        partial_sort(
            scores.begin(),
            scores.begin() + min(k, (int)scores.size()),
            scores.end(),
            [](const auto& a, const auto& b) {
                return a.second > b.second;
            }
        );
        
        if (k < (int)scores.size()) {
            scores.resize(k);
        }
        
        return scores;
    }
};

int main() {
    // Example usage
    vector<EngagementData> videos = {
        {100, 20, 5},   // Video 0
        {50, 30, 10},    // Video 1
        {200, 10, 2},    // Video 2
        {75, 40, 15},    // Video 3
        {150, 25, 8}     // Video 4
    };
    
    EngagementSegmentTree tree(videos);
    
    // Get score for range [1, 3]
    cout << "Combined score for videos 1-3: " << tree.getScore(1, 3) << endl;
    
    // Update engagement for video 2 (+10 likes, +2 comments)
    tree.updateEngagement(2, {10, 2, 0});
    cout << "Updated score for videos 1-3: " << tree.getScore(1, 3) << endl;
    
    // Get top 3 videos
    auto top3 = tree.getTopK(3);
    cout << "\nTop 3 videos by engagement:\n";
    for (const auto& [id, score] : top3) {
        cout << "Video " << id << ": " << score << " points" << endl;
    }
    
    return 0;
}

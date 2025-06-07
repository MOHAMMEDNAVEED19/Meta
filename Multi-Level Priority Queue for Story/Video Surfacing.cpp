// multi_level_priority_queue.cpp
#include <iostream>
#include <queue>
#include <vector>
#include <tuple>

using namespace std;

// (score, freshness, creator_id)
struct Content {
    int id;
    double freshness, reliability, engagement;

    double score() const {
        return 0.4 * freshness + 0.3 * reliability + 0.3 * engagement;
    }

    bool operator<(const Content& other) const {
        return score() < other.score(); // max heap
    }
};

int main() {
    priority_queue<Content> feed;

    // Simulate inserting stories/videos
    feed.push({1, 0.9, 0.8, 0.6});
    feed.push({2, 0.6, 0.95, 0.8});
    feed.push({3, 0.85, 0.7, 0.9});

    cout << "Top surfaced content by score:\n";
    while (!feed.empty()) {
        Content top = feed.top(); feed.pop();
        cout << "Content ID: " << top.id << ", Score: " << top.score() << endl;
    }

    return 0;
}

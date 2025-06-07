// poll_trend.cpp
#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>

using namespace std;

void topPollTrends(const vector<string>& votes, int topK) {
    unordered_map<string, int> freq;
    for (const auto& v : votes)
        freq[v]++;

    priority_queue<pair<int, string>> maxHeap;
    for (const auto& p : freq)
        maxHeap.push({p.second, p.first});

    cout << "Top " << topK << " poll trends:\n";
    for (int i = 0; i < topK && !maxHeap.empty(); ++i) {
        auto [count, option] = maxHeap.top(); maxHeap.pop();
        cout << option << ": " << count << " votes\n";
    }
}

int main() {
    vector<string> votes = {"A", "B", "A", "C", "B", "A", "D", "C", "B", "B"};
    topPollTrends(votes, 2);
    return 0;
}

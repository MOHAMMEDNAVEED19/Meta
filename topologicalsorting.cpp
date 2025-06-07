#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

class ConversationRanker {
private:
    unordered_map<int, vector<int>> graph; // reply_id -> children
    unordered_map<int, int> in_degree;
    unordered_map<int, double> engagement; // reply_id -> engagement score

public:
    void addReply(int reply_id, double engagement_score, int parent_id = -1) {
        engagement[reply_id] = engagement_score;
        if (parent_id != -1) {
            graph[parent_id].push_back(reply_id);
            in_degree[reply_id]++;
        }
    }

    vector<int> topologicalSort() {
        vector<int> result;
        priority_queue<pair<double, int>> pq; // max-heap by engagement

        // Initialize queue with roots (degree 0)
        for (const auto& [id, _] : engagement) {
            if (in_degree[id] == 0) {
                pq.push({engagement[id], id});
            }
        }

        while (!pq.empty()) {
            auto [eng, u] = pq.top();
            pq.pop();
            result.push_back(u);

            for (int v : graph[u]) {
                if (--in_degree[v] == 0) {
                    pq.push({engagement[v], v});
                }
            }
        }

        return result;
    }
};

int main() {
    ConversationRanker ranker;
    
    // Add replies (id, engagement_score, parent_id)
    ranker.addReply(1, 5.0);      // Root comment
    ranker.addReply(2, 3.0, 1);    // Reply to 1
    ranker.addReply(3, 7.0, 1);    // Reply to 1 (more engaging)
    ranker.addReply(4, 2.0, 2);    // Reply to 2
    ranker.addReply(5, 4.0, 3);    // Reply to 3
    
    auto sorted = ranker.topologicalSort();
    
    cout << "Optimal conversation order:\n";
    for (int id : sorted) {
        cout << "Reply " << id << endl;
    }
    
    return 0;
}

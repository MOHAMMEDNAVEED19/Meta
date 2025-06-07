#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <string>
#include <chrono>
#include <ctime>

using namespace std;
using Timestamp = long long;

const int WINDOW_SECONDS = 60; // Sliding window duration

// Trie Node
struct TrieNode {
    unordered_map<char, TrieNode*> children;
    int count = 0;
};

class TrendTracker {
private:
    TrieNode* root;
    
    struct Entry {
        string keyword;
        Timestamp timestamp;
    };

    queue<Entry> slidingWindow;

    Timestamp currentTime() {
        return chrono::duration_cast<chrono::seconds>(
            chrono::system_clock::now().time_since_epoch()
        ).count();
    }

    void insertToTrie(const string& keyword) {
        TrieNode* node = root;
        for (char c : keyword) {
            if (!node->children.count(c))
                node->children[c] = new TrieNode();
            node = node->children[c];
            node->count++;
        }
    }

    void removeFromTrie(const string& keyword) {
        TrieNode* node = root;
        vector<TrieNode*> path;
        for (char c : keyword) {
            if (!node->children.count(c)) return;
            node = node->children[c];
            path.push_back(node);
        }
        for (auto it = path.rbegin(); it != path.rend(); ++it) {
            (*it)->count--;
        }
    }

    void pruneOldEntries() {
        Timestamp now = currentTime();
        while (!slidingWindow.empty() && now - slidingWindow.front().timestamp > WINDOW_SECONDS) {
            removeFromTrie(slidingWindow.front().keyword);
            slidingWindow.pop();
        }
    }

public:
    TrendTracker() {
        root = new TrieNode();
    }

    void addKeyword(const string& keyword) {
        Timestamp now = currentTime();
        slidingWindow.push({keyword, now});
        insertToTrie(keyword);
        pruneOldEntries();
    }

    int getFrequency(const string& prefix) {
        TrieNode* node = root;
        for (char c : prefix) {
            if (!node->children.count(c)) return 0;
            node = node->children[c];
        }
        return node->count;
    }

    ~TrendTracker() {
        // Recursively free trie memory
        function<void(TrieNode*)> deleteTrie = [&](TrieNode* node) {
            for (auto& pair : node->children)
                deleteTrie(pair.second);
            delete node;
        };
        deleteTrie(root);
    }
};

int main() {
    TrendTracker tracker;

    // Simulating real-time keyword insertions
    tracker.addKeyword("ai");
    tracker.addKeyword("ai");
    tracker.addKeyword("chatgpt");
    tracker.addKeyword("chat");
    tracker.addKeyword("chatgpt");

    cout << "Frequency of 'ai': " << tracker.getFrequency("ai") << endl;
    cout << "Frequency of 'chat': " << tracker.getFrequency("chat") << endl;
    cout << "Frequency of 'chatgpt': " << tracker.getFrequency("chatgpt") << endl;

    return 0;
}

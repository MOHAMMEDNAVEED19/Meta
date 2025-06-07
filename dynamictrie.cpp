// dynamic_trie_filter.cpp
#include <iostream>
#include <unordered_map>
using namespace std;

class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    bool isEnd = false;
};

class Trie {
    TrieNode* root;

public:
    Trie() { root = new TrieNode(); }

    void insert(const string& word) {
        TrieNode* node = root;
        for (char c : word) {
            if (!node->children.count(c))
                node->children[c] = new TrieNode();
            node = node->children[c];
        }
        node->isEnd = true;
    }

    bool containsKeyword(const string& text) {
        for (int i = 0; i < text.size(); ++i) {
            TrieNode* node = root;
            for (int j = i; j < text.size(); ++j) {
                char c = text[j];
                if (!node->children.count(c)) break;
                node = node->children[c];
                if (node->isEnd) return true;
            }
        }
        return false;
    }
};

int main() {
    Trie filter;
    filter.insert("bad");
    filter.insert("hate");

    string post = "I really hate spam.";
    cout << (filter.containsKeyword(post) ? "Flagged" : "Clean") << endl;
    return 0;
}

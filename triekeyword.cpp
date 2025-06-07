// trie_keyword_extraction.cpp
#include <iostream>
#include <unordered_map>
using namespace std;

class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    bool isEnd = false;
};

class KeywordTrie {
    TrieNode* root;

public:
    KeywordTrie() { root = new TrieNode(); }

    void insert(const string& word) {
        TrieNode* node = root;
        for (char c : word) {
            if (!node->children.count(c))
                node->children[c] = new TrieNode();
            node = node->children[c];
        }
        node->isEnd = true;
    }

    bool hasKeyword(const string& text) {
        for (int i = 0; i < text.length(); ++i) {
            TrieNode* node = root;
            for (int j = i; j < text.length(); ++j) {
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
    KeywordTrie trie;
    trie.insert("birthday");
    trie.insert("travel");
    trie.insert("graduation");

    string story = "This is a post about my graduation day in 2022.";
    cout << (trie.hasKeyword(story) ? "Keyword Found" : "No Keyword") << endl;
    return 0;
}

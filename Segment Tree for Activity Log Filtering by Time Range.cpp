// segment_tree_activity_logs.cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct SegmentTree {
    vector<int> tree;
    int n;

    SegmentTree(const vector<int>& logs) {
        n = logs.size();
        tree.resize(4 * n);
        build(logs, 0, 0, n - 1);
    }

    void build(const vector<int>& logs, int node, int l, int r) {
        if (l == r) {
            tree[node] = logs[l];
            return;
        }
        int mid = (l + r) / 2;
        build(logs, 2 * node + 1, l, mid);
        build(logs, 2 * node + 2, mid + 1, r);
        tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
    }

    int query(int node, int l, int r, int ql, int qr) {
        if (qr < l || ql > r) return 0;
        if (ql <= l && r <= qr) return tree[node];
        int mid = (l + r) / 2;
        return query(2 * node + 1, l, mid, ql, qr) +
               query(2 * node + 2, mid + 1, r, ql, qr);
    }

    int rangeQuery(int ql, int qr) {
        return query(0, 0, n - 1, ql, qr);
    }
};

int main() {
    vector<int> activityLogs = {1, 0, 1, 1, 0, 1, 0}; // 1: Activity occurred
    SegmentTree segTree(activityLogs);
    cout << "Activities between day 1 and 4: " << segTree.rangeQuery(1, 4) << endl;
    return 0;
}

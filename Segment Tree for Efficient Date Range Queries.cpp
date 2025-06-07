// segment_tree_memories.cpp
#include <iostream>
#include <vector>

using namespace std;

class SegmentTree {
    vector<int> tree;
    int n;

public:
    SegmentTree(const vector<int>& data) {
        n = data.size();
        tree.resize(4 * n);
        build(data, 0, 0, n - 1);
    }

    void build(const vector<int>& data, int node, int l, int r) {
        if (l == r) {
            tree[node] = data[l];
            return;
        }
        int mid = (l + r) / 2;
        build(data, 2 * node + 1, l, mid);
        build(data, 2 * node + 2, mid + 1, r);
        tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
    }

    int query(int node, int l, int r, int ql, int qr) {
        if (qr < l || ql > r) return 0;
        if (ql <= l && r <= qr) return tree[node];
        int mid = (l + r) / 2;
        return query(2 * node + 1, l, mid, ql, qr) +
               query(2 * node + 2, mid + 1, r, ql, qr);
    }

    int dateRangeQuery(int start, int end) {
        return query(0, 0, n - 1, start, end);
    }
};

int main() {
    vector<int> postsByDay = {1, 0, 3, 0, 2, 1, 0}; // #posts per day
    SegmentTree st(postsByDay);
    cout << "Posts from day 1 to 5: " << st.dateRangeQuery(1, 5) << endl;
    return 0;
}

// segment_tree_lazy.cpp
#include <iostream>
#include <vector>

using namespace std;

class SegmentTree {
    vector<int> tree, lazy;
    int n;

public:
    SegmentTree(int size) {
        n = size;
        tree.resize(4 * n);
        lazy.resize(4 * n, 0);
    }

    void updateRange(int l, int r, int val) {
        updateRangeUtil(0, 0, n - 1, l, r, val);
    }

    int queryRange(int l, int r) {
        return queryRangeUtil(0, 0, n - 1, l, r);
    }

private:
    void updateRangeUtil(int idx, int start, int end, int l, int r, int val) {
        if (lazy[idx] != 0) {
            tree[idx] += (end - start + 1) * lazy[idx];
            if (start != end) {
                lazy[2 * idx + 1] += lazy[idx];
                lazy[2 * idx + 2] += lazy[idx];
            }
            lazy[idx] = 0;
        }

        if (start > end || start > r || end < l)
            return;

        if (start >= l && end <= r) {
            tree[idx] += (end - start + 1) * val;
            if (start != end) {
                lazy[2 * idx + 1] += val;
                lazy[2 * idx + 2] += val;
            }
            return;
        }

        int mid = (start + end) / 2;
        updateRangeUtil(2 * idx + 1, start, mid, l, r, val);
        updateRangeUtil(2 * idx + 2, mid + 1, end, l, r, val);
        tree[idx] = tree[2 * idx + 1] + tree[2 * idx + 2];
    }

    int queryRangeUtil(int idx, int start, int end, int l, int r) {
        if (start > end || start > r || end < l)
            return 0;

        if (lazy[idx] != 0) {
            tree[idx] += (end - start + 1) * lazy[idx];
            if (start != end) {
                lazy[2 * idx + 1] += lazy[idx];
                lazy[2 * idx + 2] += lazy[idx];
            }
            lazy[idx] = 0;
        }

        if (start >= l && end <= r)
            return tree[idx];

        int mid = (start + end) / 2;
        return queryRangeUtil(2 * idx + 1, start, mid, l, r) +
               queryRangeUtil(2 * idx + 2, mid + 1, end, l, r);
    }
};

int main() {
    SegmentTree st(10);
    st.updateRange(2, 5, 3); // Add 3 to indices [2, 5]
    st.updateRange(0, 3, 2); // Add 2 to indices [0, 3]
    cout << "Sum of [2, 4]: " << st.queryRange(2, 4) << endl; // Should be 3+3+2 + 3+2 + 2 = 13
    return 0;
}

// convex_hull_rotating_calipers.cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Point {
    double x, y;
    bool operator<(const Point& p) const {
        return x < p.x || (x == p.x && y < p.y);
    }
};

double cross(const Point &O, const Point &A, const Point &B) {
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

vector<Point> convexHull(vector<Point> pts) {
    int n = pts.size(), k = 0;
    vector<Point> hull(2 * n);

    sort(pts.begin(), pts.end());

    for (int i = 0; i < n; ++i) {
        while (k >= 2 && cross(hull[k - 2], hull[k - 1], pts[i]) <= 0) k--;
        hull[k++] = pts[i];
    }
    for (int i = n - 2, t = k + 1; i >= 0; --i) {
        while (k >= t && cross(hull[k - 2], hull[k - 1], pts[i]) <= 0) k--;
        hull[k++] = pts[i];
    }

    hull.resize(k - 1);
    return hull;
}

int main() {
    vector<Point> points = {{0,0},{1,1},{2,2},{2,0},{2,4},{3,3},{4,2}};
    auto hull = convexHull(points);
    cout << "Convex Hull:\n";
    for (auto& p : hull) cout << "(" << p.x << "," << p.y << ")\n";
    return 0;
}

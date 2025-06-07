// highlight_selection_dp.cpp
#include <iostream>
#include <vector>

using namespace std;

int selectHighlights(const vector<int>& weights, const vector<int>& values, int maxWeight) {
    int n = weights.size();
    vector<vector<int>> dp(n + 1, vector<int>(maxWeight + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int w = 0; w <= maxWeight; ++w) {
            if (weights[i - 1] <= w)
                dp[i][w] = max(dp[i - 1][w],
                               dp[i - 1][w - weights[i - 1]] + values[i - 1]);
            else
                dp[i][w] = dp[i - 1][w];
        }
    }
    return dp[n][maxWeight];
}

int main() {
    vector<int> emotionalWeights = {3, 2, 4, 1};  // Time/emotion budget
    vector<int> impactScores = {4, 3, 5, 2};      // Relevance/impact score
    int maxLimit = 5;

    cout << "Max highlight impact: " << selectHighlights(emotionalWeights, impactScores, maxLimit) << endl;
    return 0;
}

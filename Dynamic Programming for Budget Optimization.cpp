// budget_optimization_dp.cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Each campaign has a cost and an expected ROI
struct Campaign {
    int cost;
    int roi;
};

int maximizeROI(vector<Campaign>& campaigns, int budget) {
    int n = campaigns.size();
    vector<int> dp(budget + 1, 0);

    for (const auto& c : campaigns) {
        for (int j = budget; j >= c.cost; --j) {
            dp[j] = max(dp[j], dp[j - c.cost] + c.roi);
        }
    }

    return dp[budget];
}

int main() {
    vector<Campaign> campaigns = {{4, 40}, {3, 50}, {2, 100}, {5, 95}};
    int budget = 8;
    cout << "Max ROI: " << maximizeROI(campaigns, budget) << endl;
    return 0;
}

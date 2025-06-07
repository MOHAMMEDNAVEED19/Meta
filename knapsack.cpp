#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

struct Listing {
    int id;
    double value;  // Purchase likelihood or predicted transaction value
    double weight; // Combined metric of distance and price (normalized)
};

vector<Listing> knapsackPrioritization(const vector<Listing>& listings, int capacity) {
    int n = listings.size();
    
    // DP table: dp[i][w] = max value with first i items and capacity w
    vector<vector<double>> dp(n + 1, vector<double>(capacity + 1, 0.0));
    
    // Build DP table
    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= capacity; w++) {
            if (listings[i-1].weight <= w) {
                dp[i][w] = max(
                    dp[i-1][w], 
                    dp[i-1][w - static_cast<int>(listings[i-1].weight)] + listings[i-1].value
                );
            } else {
                dp[i][w] = dp[i-1][w];
            }
        }
    }
    
    // Backtrack to find selected listings
    vector<Listing> selected;
    int w = capacity;
    for (int i = n; i > 0; i--) {
        if (dp[i][w] != dp[i-1][w]) {
            selected.push_back(listings[i-1]);
            w -= static_cast<int>(listings[i-1].weight);
        }
    }
    
    reverse(selected.begin(), selected.end());
    
    return selected;
}

// Space-optimized version (uses O(C) space)
vector<Listing> knapsackPrioritizationOptimized(const vector<Listing>& listings, int capacity) {
    int n = listings.size();
    vector<double> dp(capacity + 1, 0.0);
    vector<vector<bool>> selected(n + 1, vector<bool>(capacity + 1, false));
    
    for (int i = 1; i <= n; i++) {
        for (int w = capacity; w >= static_cast<int>(listings[i-1].weight); w--) {
            if (dp[w - static_cast<int>(listings[i-1].weight)] + listings[i-1].value > dp[w]) {
                dp[w] = dp[w - static_cast<int>(listings[i-1].weight)] + listings[i-1].value;
                selected[i][w] = true;
            }
        }
    }
    
    // Backtrack to find selected listings
    vector<Listing> result;
    int w = capacity;
    for (int i = n; i > 0; i--) {
        if (selected[i][w]) {
            result.push_back(listings[i-1]);
            w -= static_cast<int>(listings[i-1].weight);
        }
    }
    
    reverse(result.begin(), result.end());
    return result;
}

int main() {
    // Example usage
    vector<Listing> listings = {
        {1, 0.8, 1.2},  // ID, value, weight
        {2, 0.7, 1.0},
        {3, 0.9, 1.5},
        {4, 0.6, 0.8},
        {5, 0.5, 0.5}
    };
    
    int capacity = 3;  // Represents the "budget" (e.g., screen space or attention limit)
    
    auto prioritized = knapsackPrioritization(listings, capacity);
    
    cout << "Selected listings (up to capacity " << capacity << "):\n";
    for (const auto& item : prioritized) {
        cout << "ID: " << item.id 
             << ", Value: " << item.value 
             << ", Weight: " << item.weight << "\n";
    }
    
    return 0;
}

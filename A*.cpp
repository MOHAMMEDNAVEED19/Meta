#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <cmath>
#include <limits>
#include <algorithm>

struct Listing {
    int id;
    double latitude;
    double longitude;
    double relevance; // Combined score of category preference and other factors (0-1)
};

struct Node {
    int listing_id;
    double g_score; // Actual cost from start (distance traveled)
    double f_score; // Estimated total cost (g + heuristic)
    
    bool operator>(const Node& other) const {
        return f_score > other.f_score;
    }
};

class LocationAwareRecommender {
private:
    std::vector<Listing> listings;
    
    // Haversine distance calculation (in km)
    double calculateDistance(double lat1, double lon1, double lat2, double lon2) {
        const double R = 6371.0; // Earth radius in km
        double dLat = (lat2 - lat1) * M_PI / 180.0;
        double dLon = (lon2 - lon1) * M_PI / 180.0;
        
        double a = sin(dLat / 2) * sin(dLat / 2) +
                   cos(lat1 * M_PI / 180.0) * cos(lat2 * M_PI / 180.0) *
                   sin(dLon / 2) * sin(dLon / 2);
        
        double c = 2 * atan2(sqrt(a), sqrt(1 - a));
        return R * c;
    }
    
    // Heuristic function: balances distance and relevance
    double heuristic(double current_dist, double relevance) {
        // Weighting factors - adjust based on your requirements
        const double distance_weight = 0.6;
        const double relevance_weight = 0.4;
        
        // Normalize and combine (lower is better)
        return (distance_weight * current_dist) - (relevance_weight * relevance);
    }

public:
    LocationAwareRecommender(const std::vector<Listing>& listings) : listings(listings) {}
    
    std::vector<int> findRecommendations(double user_lat, double user_lon, 
                                        int max_recommendations = 10, 
                                        double max_radius_km = 5.0) {
        std::priority_queue<Node, std::vector<Node>, std::greater<Node>> open_set;
        std::unordered_map<int, double> g_scores;
        std::vector<int> recommendations;
        
        // Initialize all listings with infinite g_score
        for (const auto& listing : listings) {
            g_scores[listing.id] = std::numeric_limits<double>::infinity();
        }
        
        // Add nearby listings to open set
        for (const auto& listing : listings) {
            double dist = calculateDistance(user_lat, user_lon, 
                                          listing.latitude, listing.longitude);
            
            if (dist <= max_radius_km) {
                double h = heuristic(dist, listing.relevance);
                open_set.push({listing.id, dist, h});
                g_scores[listing.id] = dist;
            }
        }
        
        // A* search
        while (!open_set.empty() && recommendations.size() < max_recommendations) {
            Node current = open_set.top();
            open_set.pop();
            
            // Add to recommendations if we haven't already
            if (std::find(recommendations.begin(), recommendations.end(), current.listing_id) == recommendations.end()) {
                recommendations.push_back(current.listing_id);
            }
        }
        
        return recommendations;
    }
};

int main() {
    // Example listings data
    std::vector<Listing> listings = {
        {1, 37.7749, -122.4194, 0.9},  // San Francisco (high relevance)
        {2, 37.3382, -121.8863, 0.7},   // San Jose
        {3, 37.8044, -122.2712, 0.8},   // Oakland
        {4, 38.5816, -121.4944, 0.6},   // Sacramento (farther but medium relevance)
        {5, 36.7378, -119.7871, 0.5},   // Fresno (far away, low relevance)
        {6, 37.7799, -122.4197, 0.95}, // Very close, very relevant
        {7, 37.7751, -122.4189, 0.85},  // Very close, highly relevant
        {8, 37.7833, -122.4167, 0.75}   // Close, relevant
    };
    
    // User's location (San Francisco)
    double user_lat = 37.7749;
    double user_lon = -122.4194;
    
    LocationAwareRecommender recommender(listings);
    auto recommendations = recommender.findRecommendations(user_lat, user_lon);
    
    std::cout << "Recommended listings (ordered by balanced distance/relevance):\n";
    for (int id : recommendations) {
        auto it = std::find_if(listings.begin(), listings.end(), 
                             [id](const Listing& l) { return l.id == id; });
        if (it != listings.end()) {
            double dist = recommender.calculateDistance(user_lat, user_lon, 
                                                      it->latitude, it->longitude);
            std::cout << "ID: " << it->id 
                      << ", Distance: " << dist << " km"
                      << ", Relevance: " << it->relevance << "\n";
        }
    }
    
    return 0;
}

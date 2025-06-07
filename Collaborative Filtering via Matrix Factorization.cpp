#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

using Matrix = vector<vector<double>>;

class MatrixFactorization {
private:
    Matrix R;      // User-Item ratings
    Matrix P, Q;   // Latent matrices (P: User x K, Q: Item x K)
    int K;         // Latent dimension
    int steps;     // Iterations
    double alpha;  // Learning rate
    double beta;   // Regularization

public:
    MatrixFactorization(const Matrix& ratings, int latent_dim = 2, int iterations = 5000, double lr = 0.01, double reg = 0.02)
        : R(ratings), K(latent_dim), steps(iterations), alpha(lr), beta(reg) {

        int users = R.size();
        int items = R[0].size();

        srand(time(0));
        P = Matrix(users, vector<double>(K));
        Q = Matrix(items, vector<double>(K));

        // Random initialization
        for (int u = 0; u < users; ++u)
            for (int k = 0; k < K; ++k)
                P[u][k] = ((double)rand() / RAND_MAX);

        for (int i = 0; i < items; ++i)
            for (int k = 0; k < K; ++k)
                Q[i][k] = ((double)rand() / RAND_MAX);
    }

    void train() {
        int U = R.size();
        int I = R[0].size();

        for (int step = 0; step < steps; ++step) {
            for (int u = 0; u < U; ++u) {
                for (int i = 0; i < I; ++i) {
                    if (R[u][i] > 0) {
                        double prediction = predict(u, i);
                        double e_ui = R[u][i] - prediction;

                        for (int k = 0; k < K; ++k) {
                            P[u][k] += alpha * (e_ui * Q[i][k] - beta * P[u][k]);
                            Q[i][k] += alpha * (e_ui * P[u][k] - beta * Q[i][k]);
                        }
                    }
                }
            }
        }
    }

    double predict(int user, int item) {
        double dot = 0.0;
        for (int k = 0; k < K; ++k)
            dot += P[user][k] * Q[item][k];
        return dot;
    }

    void printPredictions() {
        int U = R.size();
        int I = R[0].size();
        cout << "\nPredicted Ratings Matrix:\n";
        for (int u = 0; u < U; ++u) {
            for (int i = 0; i < I; ++i) {
                cout << predict(u, i) << "\t";
            }
            cout << endl;
        }
    }
};

int main() {
    // R: User-Thread rating matrix (0 = missing interaction)
    Matrix ratings = {
        {5, 3, 0, 1},
        {4, 0, 0, 1},
        {1, 1, 0, 5},
        {0, 0, 5, 4},
        {0, 1, 5, 4}
    };

    MatrixFactorization model(ratings, 3, 5000, 0.01, 0.02);
    model.train();
    model.printPredictions();

    return 0;
}

#include "question_4.h"
#include "GameLogic.h"

#include "SearchSpace.h"
using namespace std;

const int N_DIGITS = 4;
const int K_MAX = 6;
const int TRIALS = 20;
const int SAMPLE_LIMIT = 100;

// Samples up to 100 elements from S. If S has <= 100 elements, returns S unchanged.
vector<vector<int>> sampleUpTo100(const vector<vector<int>>& S, mt19937& rng) {
    if (S.size() <= 100)
        return S;

    vector<vector<int>> result;
    result.reserve(100);

    uniform_int_distribution<int> dist(0, S.size() - 1);

    for (int i = 0; i < 100; i++)
        result.push_back(S[dist(rng)]);

    return result;
}

// Estimates cost(x, y) using sampling of up to 100 elements from S.
double estimateCostSampled(const vector<int>& x,
    const Feedback& fb,
    const vector<vector<int>>& S,
    mt19937& rng)
{
    vector<vector<int>> sampleS = sampleUpTo100(S, rng);

    int t = 0;
    for (const auto& candidate : sampleS) {
        if (computeFeedback(x, candidate) == fb)
            t++;
    }

    return double(S.size()) * (double(t) / sampleS.size());
}

// Estimates the expected search depth E[cost(x, y)] for guess x using sampling.
double estimateSearchDepthSampled(const vector<int>& x,
    const vector<vector<int>>& S,
    mt19937& rng)
{
    vector<vector<int>> sampleY = sampleUpTo100(S, rng);

    double sumCost = 0.0;

    for (const auto& y : sampleY) {
        Feedback fb = computeFeedback(x, y);
        double estCost = estimateCostSampled(x, fb, S, rng);
        sumCost += estCost;
    }

    return sumCost / sampleY.size();
}

// Chooses the best next guess using the sampling-based strategy.
vector<int> chooseBestGuessSampled(const vector<vector<int>>& S, mt19937& rng)
{
    vector<vector<int>> sampleX = sampleUpTo100(S, rng);

    double bestScore = 1e18;
    vector<int> bestX;

    for (const auto& x : sampleX) {
        double score = estimateSearchDepthSampled(x, S, rng);

        if (score < bestScore) {
            bestScore = score;
            bestX = x;
        }
    }

    return bestX;
}

void question_4() {
    mt19937 rng(random_device{}());

    cout << "=== Question 4: Sampling-Based Strategy ===\n";

    vector<int> results;
    results.reserve(TRIALS);

    for (int t = 0; t < TRIALS; t++) {

        // Generate random secret
        vector<int> secret = generateSecretDigitsDistinct(N_DIGITS, K_MAX, rng);
        cout << "Secret: " << digitsToInt(secret) << "\n";

        SearchSpace fullSpace(N_DIGITS, K_MAX);

        // Full search space
        vector<vector<int>> S = fullSpace.buildFullSearchSpace();

        int guessCount = 0;

        while (true) {
            guessCount++;

            // Choose guess using sampling-based strategy
            vector<int> guess = chooseBestGuessSampled(S, rng);

            // Compute real feedback
            Feedback fb = computeFeedback(guess, secret);

            // Check if solved
            if (fb.bulls == N_DIGITS) {
                cout << "Solved in " << guessCount << " guesses\n";
                results.push_back(guessCount);
                break;
            }

            // Filter search space
            S = filterByFeedback(guess, fb, S);
        }
    }

    // Compute statistics
    sort(results.begin(), results.end());

    double avg = accumulate(results.begin(), results.end(), 0.0) / results.size();
    double median = (results.size() % 2 == 1)
        ? results[results.size() / 2]
        : 0.5 * (results[results.size() / 2 - 1] + results[results.size() / 2]);

    int maximum = results.back();

    cout << "Average: " << avg << "\n";
    cout << "Median:  " << median << "\n";
    cout << "Max:     " << maximum << "\n";
}
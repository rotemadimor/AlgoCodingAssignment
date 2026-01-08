#include "question_4.h"
#include "question_3.h"
#include "question_2.h"
#include "SearchSpace.h"
#include <vector>
#include <random>
#include <algorithm>
#include <climits>
#include <iostream>
#include <numeric>

using namespace std;

const int N_DIGITS = 4;
const int K_MAX = 6;
const int TRIALS = 20;

void question_3() {
    mt19937 rng(random_device{}());   // Random number generator

    cout << "=== Question 3: Minimax Strategy ===\n";

    vector<int> results;
    results.reserve(TRIALS);

    for (int t = 0; t < TRIALS; t++) {

        // Generate a random secret number
        vector<int> secret = generateSecretDigitsDistinct(N_DIGITS, K_MAX, rng);
        cout << "Secret: " << digitsToInt(secret) << "\n";

        SearchSpace fullSpace(N_DIGITS, K_MAX);

        // Build the full search space S
        vector<vector<int>> S = fullSpace.buildFullSearchSpace();

        int guessCount = 0;

        while (true) {
            guessCount++;

            // Choose the best guess using the minimax strategy
            vector<int> guess = chooseBestGuess(S);

            // Compute the real feedback against the secret
            Feedback fb = computeFeedback(guess, secret);

            // If all digits match — solved
            if (fb.bulls == N_DIGITS) {
                cout << "Solved in " << guessCount << " guesses\n";
                results.push_back(guessCount);
                break;
            }

            // Filter S to keep only guesses consistent with the feedback
            S = filterByFeedback(guess, fb, S);
        }
    }

    // Compute average, median, and maximum number of guesses
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


// Chooses the guess x in S that minimizes the worst-case remaining search space.
vector<int> chooseBestGuess(const vector<vector<int>>& S)
{
    int bestDepth = INT_MAX;
    vector<int> bestGuess;

    for (const auto& x : S) {
        int depth = computeDepth(x, S);   // Compute minimax depth for x
        if (depth < bestDepth) {
            bestDepth = depth;
            bestGuess = x;
        }
    }
    return bestGuess;
}


// Filters S to keep only numbers that would produce the same feedback as fb.
vector<vector<int>> filterByFeedback(const vector<int>& guess,
    const Feedback& fb,
    const vector<vector<int>>& S)
{
    vector<vector<int>> filtered;
    filtered.reserve(S.size());

    for (const auto& z : S) {
        Feedback fz = computeFeedback(guess, z);
        if (fz.bulls == fb.bulls && fz.cows == fb.cows)
            filtered.push_back(z);
    }
    return filtered;
}


// Computes the minimax depth for guess x: the worst-case cost over all y in S.
int computeDepth(const vector<int>& x, const vector<vector<int>>& S)
{
    int worst = 0;
    for (const auto& y : S) {
        int cost = computeCost(x, y, S);  // Compute cost(x, y)
        worst = max(worst, cost);         // Track the maximum cost
    }
    return worst;
}


// Computes cost(x, y): how many elements in S remain if x is guessed and y is the secret.
int computeCost(const vector<int>& x, const vector<int>& y, const vector<vector<int>>& S)
{
    Feedback targetFeedback = computeFeedback(x, y);
    int count = 0;

    for (const auto& z : S) {
        Feedback f = computeFeedback(x, z);
        if (f.bulls == targetFeedback.bulls &&
            f.cows == targetFeedback.cows)
        {
            count++;   // z would remain in the search space
        }
    }
    return count;
}
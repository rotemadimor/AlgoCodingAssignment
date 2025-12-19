// ------------------------------------------------------------
// DFSGuessGenerator.h - DFS/backtracking generator for next guess.
// ------------------------------------------------------------

#pragma once
#include <vector>
#include <unordered_set>
#include <random>
#include "question_1.h"


/*
 * Generates the next unused guess that is consistent with all previous
 * (guesses, feedbacks) using digit-by-digit DFS with backtracking.
 *
 * Key goals:
 * - Do NOT store the whole solution set explicitly.
 * - Do NOT repeat guesses.
 * - Be strict: final candidate must satisfy question_1(...)
 */

class DFSGuessGenerator{
public:
    /**
     * Creates a generator for numbers of length nDigits, with digits in [1..kMaxDigit].
     */
    DFSGuessGenerator(int nDigits, int kMaxDigit);

    /**
     * Clears the "already used guesses" set for a fresh game.
     */
    void reset();

    /**
     * Finds the next consistent guess (not used before).
     * Returns:
     * - the guess as an integer (e.g., 1234)
     * - or -1 if no consistent guess exists.
     */
    int nextGuess(const std::vector<int>& guesses,
        const std::vector<Feedback>& feedbacks);

private:
	int nDigits; // Number of digits in each guess.
	int kMaxDigit; // Maximum digit value (digits in [1..kMaxDigit]).
	std::unordered_set<int> usedGuesses; // Set of already used guesses.
	std::mt19937 rng; // Random number generator for digit ordering.

	// DFS with backtracking to build a consistent guess digit-by-digit.
    bool dfsBuild(int pos,
        std::vector<int>& currentDigits,
        const std::vector<std::vector<int>>& prevGuessDigits,
        const std::vector<int>& prevGuessInts,
        const std::vector<Feedback>& feedbacks,
        int& outGuess);

    /**
     * Fast prefix pruning:
     * Checks if the partial prefix (first pos digits) can still match each previous feedback.
     * Uses safe bounds on bulls and total matches (bulls+cows).
     */
    bool prefixFeasible(int pos,
        const std::vector<int>& currentDigits,
        const std::vector<std::vector<int>>& prevGuessDigits,
        const std::vector<Feedback>& feedbacks) const;
};

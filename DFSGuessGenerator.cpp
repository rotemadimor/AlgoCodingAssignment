// ------------------------------------------------------------
// DFSGuessGenerator.cpp - Implementation of DFS/backtracking generator.
// ------------------------------------------------------------

#include "DFSGuessGenerator.h"
#include "GameLogic.h"
#include <algorithm>

static bool digitAlreadyUsed(const std::vector<int>& digits, int pos, int d) {
    for (int i = 0; i < pos; ++i) {
        if (digits[i] == d) return true;
    }
    return false;
}

DFSGuessGenerator::DFSGuessGenerator(int nDigits, int kMaxDigit)
    : nDigits(nDigits),
    kMaxDigit(kMaxDigit),
    rng(std::random_device{}()) {
}

void DFSGuessGenerator::reset() {
    usedGuesses.clear();
}

int DFSGuessGenerator::nextGuess(const std::vector<int>& guesses,const std::vector<Feedback>& feedbacks) {
    // Cache digit vectors for previous guesses once per call.
    std::vector<std::vector<int>> prevGuessDigits;
	// Preallocate space.
    prevGuessDigits.reserve(guesses.size());
	// Convert each previous guess to digit vector.
    for (int g : guesses) {
        prevGuessDigits.push_back(toDigits(g, nDigits));
    }

	// Current guess being built digit-by-digit.
    std::vector<int> currentDigits(nDigits, 0);
    int result = -1;

	// Start DFS/backtracking from position 0.
    if (dfsBuild(0, currentDigits, prevGuessDigits, guesses, feedbacks, result)) {
        usedGuesses.insert(result);
        return result;
    }
	// No consistent guess found.
    return -1;
}

bool DFSGuessGenerator::dfsBuild(int pos,std::vector<int>& currentDigits,
    const std::vector<std::vector<int>>& prevGuessDigits,const std::vector<int>& prevGuessInts,
    const std::vector<Feedback>& feedbacks,int& outGuess) {

	// Base case: full candidate built.
    if (pos == nDigits) {
        const int candidate = digitsToInt(currentDigits);

        // Avoid repeating guesses.
        if (usedGuesses.find(candidate) != usedGuesses.end()) {
            return false;
        }

        // Final strict check against ALL history using question_1.
        // (This guarantees correctness even if prefix pruning is conservative.)
        if (!question_1(candidate,
            const_cast<Feedback*>(feedbacks.data()),
            const_cast<int*>(prevGuessInts.data()),
            static_cast<int>(prevGuessInts.size()))) {
            return false;
        }

        outGuess = candidate;
        return true;
    }

    // Try digits in [1..kMaxDigit_] (shuffled for variability).
    std::vector<int> options;
	// Preallocate space.
    options.reserve(kMaxDigit);
	// Fill options.
    for (int d = 1; d <= kMaxDigit; ++d)
        options.push_back(d);

	// Shuffle options to introduce randomness in the search.
    std::shuffle(options.begin(), options.end(), rng);

    for (int d : options) {
        // Do not allow repeated digits inside the candidate guess.
        if (digitAlreadyUsed(currentDigits, pos, d)) {
            continue;
        }

        currentDigits[pos] = d;

        // Quick prefix pruning before going deeper.
        if (!prefixFeasible(pos + 1, currentDigits, prevGuessDigits, feedbacks)) {
            continue;
        }

        if (dfsBuild(pos + 1, currentDigits, prevGuessDigits, prevGuessInts, feedbacks, outGuess)) {
            return true;
        }
    }

    currentDigits[pos] = 0;
    return false;
}

bool DFSGuessGenerator::prefixFeasible(int pos,const std::vector<int>& currentDigits,
    const std::vector<std::vector<int>>& prevGuessDigits,const std::vector<Feedback>& feedbacks) const {

	// Number of remaining digits to fill.
    const int remaining = nDigits - pos;

    // Frequency for digits 0..9 in the prefix (safe for typical k<=9 tasks).
    int freqPrefix[10] = { 0 };
    for (int i = 0; i < pos; ++i) {
        int d = currentDigits[i];
        if (0 <= d && d <= 9) ++freqPrefix[d];
    }

	// Check each previous guess against its feedback.
    for (size_t j = 0; j < prevGuessDigits.size(); ++j) {
		const auto& g = prevGuessDigits[j]; // Previous guess digits.
		const int targetBulls = feedbacks[j].bulls; // Target bulls for this guess.
		const int targetTotal = feedbacks[j].bulls + feedbacks[j].cows; // Target bulls+cows.

        // Bulls fixed in the prefix.
        int bullsSoFar = 0;
        for (int i = 0; i < pos; ++i) {
            if (currentDigits[i] == g[i]) ++bullsSoFar;
        }

        if (bullsSoFar > targetBulls) return false;
        if (bullsSoFar + remaining < targetBulls) return false;

        // Total matches (bulls+cows) lower bound in the prefix:
        // count common digits between prefix and the whole guess g.
        int freqG[10] = { 0 };
        for (int i = 0; i < nDigits; ++i) {
            int d = g[i];
            if (0 <= d && d <= 9) ++freqG[d];
        }

        int matchesSoFar = 0;
        for (int d = 0; d <= 9; ++d) {
            matchesSoFar += (freqPrefix[d] < freqG[d]) ? freqPrefix[d] : freqG[d];
        }

        if (matchesSoFar > targetTotal) return false;
        if (matchesSoFar + remaining < targetTotal) return false;
    }

    return true;
}
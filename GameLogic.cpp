// ------------------------------------------------------------
// GameLogic.cpp - Implementation of shared game utilities.
// ------------------------------------------------------------

#include "GameLogic.h"
using namespace std;

/**
 * Generates a random secret digit vector of length nDigits, with digits in [1..kMaxDigit].
 */
vector<int> generateSecretDigitsDistinct(int nDigits, int kMaxDigit, std::mt19937& rng) {
    // Build pool [1..k]
    vector<int> pool;
    pool.reserve(kMaxDigit);
    for (int d = 1; d <= kMaxDigit; ++d) {
        pool.push_back(d);
    }

    // Shuffle and take first nDigits (guarantees no repeats)
    shuffle(pool.begin(), pool.end(), rng);

    vector<int> secret;
    secret.reserve(nDigits);
    for (int i = 0; i < nDigits; ++i) {
        secret.push_back(pool[i]);
    }

    return secret;
}

bool operator==(const Feedback& a, const Feedback& b) {
    return (a.bulls == b.bulls) && (a.cows == b.cows);
}

bool operator!=(const Feedback& a, const Feedback& b) {
    return !(a == b);
}

bool isInSearchSpace(const Feedback& guessFeedback, const Feedback& secretFeedback) {
    return ((secretFeedback.bulls + secretFeedback.cows) == (guessFeedback.bulls + guessFeedback.cows));
}

bool isCorrectFeedback(const Feedback& fb, int nDigits) {
    return (fb.bulls == nDigits);
}

int countDigits(int value) {
    // By definition, 0 has 1 digit.
    if (value == 0) {
        return 1;
    }

    // Safety: handle negative input (should not happen in the assignment).
    if (value < 0) {
        value = -value;
    }

    int count = 0;
    while (value > 0) {
        ++count;
        value /= 10;
    }
    return count;
}

std::vector<int> toDigits(int value, int numDigits) {
    std::vector<int> digits(numDigits, 0);

    // Fill from rightmost digit to leftmost digit.
    for (int i = numDigits - 1; i >= 0; --i) {
        digits[i] = value % 10;
        value /= 10;
    }

    return digits;
}

int digitsToInt(const std::vector<int>& digits) {
    int value = 0;
    for (int d : digits) {
        value = value * 10 + d;
    }
    return value;
}

Feedback computeFeedback(const std::vector<int>& a, const std::vector<int>& b) {
	// Initialize feedback counts.
    Feedback result;
    result.bulls = 0;
    result.cows = 0;

    const int n = static_cast<int>(a.size());
    // Assumes b.size() == a.size().

    // Frequency for decimal digits 0..9
    int freqA[10] = { 0 };
    int freqB[10] = { 0 };

    for (int i = 0; i < n; ++i) {
        if (a[i] == b[i]) {
            ++result.bulls;
        }

		// Count digit frequencies for non-bull positions.
        const int da = a[i];
        const int db = b[i];

		// Safety check: only count valid digits.
        if (da >= 0 && da <= 9) ++freqA[da];
        if (db >= 0 && db <= 9) ++freqB[db];
    }

	// Count common digits (cows + bulls).
    int common = 0;
    for (int d = 0; d <= 9; ++d) {
		// Add the minimum frequency of digit d in both numbers.
        common += (freqA[d] < freqB[d]) ? freqA[d] : freqB[d];
    }

	// Cows are common digits minus bulls.
    result.cows = common - result.bulls;
    return result;
}


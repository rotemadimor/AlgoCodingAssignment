// ------------------------------------------------------------
// GameLogic.h - Shared Bulls & Cows utilities and types.
// ------------------------------------------------------------

#pragma once
#include <vector>
#include <random>

using namespace std;
// Maximum digits supported by the assignment constraints.
constexpr int MAX_DIGITS = 6;

/*
 * Feedback for a guess:
 * bulls = correct digit in correct position
 * cows  = correct digit in wrong position
 */
struct Feedback {
    int bulls;
    int cows;
};

bool operator==(const Feedback& a, const Feedback& b);

bool operator!=(const Feedback& a, const Feedback& b);

bool isInSearchSpace(const Feedback& guessFeedback, const Feedback& secretFeedback);

bool isCorrectFeedback(const Feedback& fb, int nDigits);

/**
 * Returns the number of decimal digits in a non-negative integer.
 * Examples: 0 -> 1, 7 -> 1, 1234 -> 4.
 */
int countDigits(int value);

/**
 * Converts a non-negative integer into a vector of its digits (left to right).
 * Example: value=1234, numDigits=4 -> [1,2,3,4]
 *
 * Precondition:
 * - value has exactly numDigits digits (no leading zeros).
 */
std::vector<int> toDigits(int value, int numDigits);

/**
 * Converts a vector of digits (left to right) into an integer.
 * Example: [1,2,3,4] -> 1234
 */
int digitsToInt(const std::vector<int>& digits);

/**
 * Computes Bulls & Cows between two digit vectors of equal length.
 * Bulls: positions where a[i] == b[i]
 * Cows:  common digits not counted as bulls
 */
Feedback computeFeedback(const vector<int>& a,const vector<int>& b);

vector<int> generateSecretDigitsDistinct(int nDigits, int kMaxDigit, mt19937& rng);
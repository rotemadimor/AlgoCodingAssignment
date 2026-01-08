// ------------------------------------------------------------
// question_1.cpp - Question 1 implementation (consistency).
// ------------------------------------------------------------

#include "question_1.h"

bool question_1(int newGuess, Feedback* feedbacks, int* guesses, int n) {
    // If there is no history, any new guess is consistent.
    if (n == 0) {
        return true;
    }

    // Determine digit-length from newGuess (all guesses are expected same length).
    const int numDigits = countDigits(newGuess);

    if (numDigits > MAX_DIGITS) {
        return false;
    }

    const std::vector<int> newDigits = toDigits(newGuess, numDigits);

    // IMPORTANT:
    // Consistency must be checked against *all* previous (guess, feedback) pairs,
    // not only the most recent one. A candidate may match the last feedback but
    // still contradict an earlier feedback, so we must validate every entry.
    for (int i = 0; i < n; ++i) {
        const int prevGuess = guesses[i];

        // If previous guess length differs, newGuess cannot be consistent.
        if (countDigits(prevGuess) != numDigits) {
            return false;
        }

		// Convert previous guess to digit vector.
        const std::vector<int> prevDigits = toDigits(prevGuess, numDigits);
		// Compute feedback between new guess and previous guess.
        const Feedback expected = computeFeedback(newDigits, prevDigits);

		// Compare with recorded feedback.
        if (expected.bulls != feedbacks[i].bulls ||
            expected.cows != feedbacks[i].cows) {
            return false;
        }
    }

    return true;
}


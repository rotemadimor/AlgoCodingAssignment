// ------------------------------------------------------------
// question_2.cpp - Question 2 DFS strategy implementation.
// ------------------------------------------------------------

#include "question_2.h"

/**
 * Computes feedback between an integer guess and a secret digit vector.
 */
 Feedback feedbackAgainstSecret(int guess, const std::vector<int>& secretDigits) {
    const int n = static_cast<int>(secretDigits.size());
    const std::vector<int> guessDigits = toDigits(guess, n);
    return computeFeedback(guessDigits, secretDigits);
}

void question_2() {
	constexpr int N_DIGITS = 4; // Number of digits in each guess/secret.
	constexpr int K_MAX = 6; // Maximum digit value (digits in [1..K_MAX]).
	constexpr int TRIALS = 20; // Number of random games to run.

	std::mt19937 rng(std::random_device{}()); // Random number generator for secret generation.
	std::vector<int> attemptsPerTrial; // Stores attempts per trial.
	attemptsPerTrial.reserve(TRIALS); // Preallocate space.


	// Run TRIALS random games.
    for (int t = 0; t < TRIALS; ++t) {

        const std::vector<int> secretDigits = generateSecretDigitsDistinct(N_DIGITS, K_MAX, rng);
        const int secret = digitsToInt(secretDigits);

		// Initialize DFS guess generator.
        DFSGuessGenerator generator(N_DIGITS, K_MAX);
        generator.reset();

		// History of guesses and feedbacks.
        std::vector<int> guesses;
        std::vector<Feedback> feedbacks;

        int attempts = 0;
        int lastGuess = -1;

		// Main guessing loop.
        while (true) {
			// Get next guess from DFS generator.
            lastGuess = generator.nextGuess(guesses, feedbacks);
            if (lastGuess == -1) {
                // No consistent guess exists (should not happen in valid game setup).
                break;
            }

            ++attempts;

            const Feedback fb = feedbackAgainstSecret(lastGuess, secretDigits);
            guesses.push_back(lastGuess);
            feedbacks.push_back(fb);

            if (fb.bulls == N_DIGITS) {
                break; // solved
            }
        }

        attemptsPerTrial.push_back(attempts);

        // Per-trial control output: secret and last guess (should match when solved).
        std::cout << "trial=" << t
            << " secret=" << secret
            << " lastGuess=" << lastGuess
            << " attempts=" << attempts
            << "\n";
    }

    // Summary stats: mean, median, max.
    int maxAttempts = 0;
    long long sum = 0;
    for (int a : attemptsPerTrial) {
        sum += a;
        if (a > maxAttempts) maxAttempts = a;
    }

	// Compute mean.
    const double mean = static_cast<double>(sum) / attemptsPerTrial.size();

	// Compute median.
    std::vector<int> sorted = attemptsPerTrial;
    std::sort(sorted.begin(), sorted.end());
    double median = 0.0;
    if (sorted.size() % 2 == 1) {
        median = static_cast<double>(sorted[sorted.size() / 2]);
    }
    else {
        const int mid = static_cast<int>(sorted.size() / 2);
        median = (sorted[mid - 1] + sorted[mid]) / 2.0;
    }

    std::cout << "DFS summary: mean=" << mean
        << " median=" << median
        << " max=" << maxAttempts
        << "\n";
}
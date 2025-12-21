// ------------------------------------------------------------
// question_2.h - Question 2 (DFS strategy) entry point.
// ------------------------------------------------------------

#pragma once

static std::vector<int> generateSecretDigitsDistinct(int nDigits, int kMaxDigit, std::mt19937& rng);
static Feedback feedbackAgainstSecret(int guess, const std::vector<int>& secretDigits);

/**
 * Runs Question 2 experiment: DFS strategy (no explicit S storage),
 * 20 random games, prints secret & final guess per game, and summary stats.
 */
void question_2();
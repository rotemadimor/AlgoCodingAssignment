// ------------------------------------------------------------
// question_2.h - Question 2 (DFS strategy) entry point.
// ------------------------------------------------------------

#pragma once
#include "DFSGuessGenerator.h"
#include "GameLogic.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <vector>

using namespace std;


 Feedback feedbackAgainstSecret(int guess, const std::vector<int>& secretDigits);

/**
 * Runs Question 2 experiment: DFS strategy (no explicit S storage),
 * 20 random games, prints secret & final guess per game, and summary stats.
 */
void question_2();
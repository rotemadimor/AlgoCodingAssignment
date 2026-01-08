#pragma once
#include "GameLogic.h"
#include <map>
#include <random>
#include <vector>
using namespace std;
/**
 * Runs Question 3 experiment: BFS strategy (explicit S storage),
 * 20 random games, prints secret & final guess per game, and summary stats.
 */
void question_3();

// Chooses the best next guess according to the minimax strategy
vector<int> chooseBestGuess(const vector<vector<int>>& S);

// Returns all elements in S that are consistent with the feedback for this guess
vector<vector<int>> filterByFeedback(const vector<int>& guess, const Feedback& fb, const vector<vector<int>>& S);

// Computes the minimax depth of guess x over the search space S
int computeDepth(const vector<int>& x, const vector<vector<int>>& S);

// Computes cost(x, y): how many elements in S remain if x is guessed and y is the secret
int computeCost(const vector<int>& x, const vector<int>& y, const vector<vector<int>>& S);


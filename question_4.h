#pragma once
#include "GameLogic.h"
#include "question_3.h"
#include <vector>
#include <random>
#include <climits>
#include <iostream>
#include <numeric>
#include <vector>
#include <random>




Feedback computeFeedback(const vector<int>& a, const vector<int>& b);

// Samples up to 100 elements from S. If S has <= 100 elements, returns S unchanged.
vector<vector<int>> sampleUpTo100(const vector<vector<int>>& S, mt19937& rng);

// Estimates cost(x, y) using sampling of up to 100 elements from S.
double estimateCostSampled(const vector<int>& x, const Feedback& fb, const vector<vector<int>>& S, mt19937& rng);

// Estimates the expected search depth E[cost(x, y)] for guess x using sampling.
double estimateSearchDepthSampled(const vector<int>& x, const vector<vector<int>>& S, mt19937& rng);

// Chooses the best next guess using the sampling-based strategy.
vector<int> chooseBestGuessSampled(const vector<vector<int>>& S, mt19937& rng);

void question_4();
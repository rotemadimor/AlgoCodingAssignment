#pragma once
#include <vector>
#include <map>
#include "GameLogic.h"

using namespace std;

class SearchSpace
{
public:
		/**
	     * Creates a search space for numbers of length nDigits, with digits in [1..kMaxDigit].
	     */
	    SearchSpace(int nDigits, int kMaxDigit);

	    /**
	     * Builds the full search space of all possible digit combinations.
	     */
	    vector<vector<int>> buildFullSearchSpace();

		vector<vector<int>> buildSearchSpaceForGuess(const vector<int>& guess, const vector<int>& secret);

private:
			int nDigits; // Number of digits in each guess.
			int kMaxDigit; // Maximum digit value (digits in [1..kMaxDigit]).
			map<vector<int>, Feedback> graph; // Search space graph (candidates and their feedbacks).

};


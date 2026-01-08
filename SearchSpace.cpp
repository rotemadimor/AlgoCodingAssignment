#include "SearchSpace.h"

SearchSpace::SearchSpace(int nDigits, int kMaxDigit)
{
	this->nDigits = nDigits;
	this->kMaxDigit = kMaxDigit;

}
vector<vector<int>> SearchSpace::buildFullSearchSpace()
{
	vector<vector<int>> searchSpace;

	for (int d1 = 1; d1 <= kMaxDigit; d1++)
		for (int d2 = 1; d2 <= kMaxDigit; d2++)
			if (d2 != d1)
				for (int d3 = 1; d3 <= kMaxDigit; d3++)
					if (d3 != d1 && d3 != d2)
						for (int d4 = 1; d4 <= kMaxDigit; d4++)
							if (d4 != d1 && d4 != d2 && d4 != d3)
								searchSpace.push_back({ d1, d2, d3, d4 });
	return searchSpace;
}

vector<vector<int>> SearchSpace::buildSearchSpaceForGuess(const vector<int>& guess,
	const vector<int>& secret)
{
	vector<vector<int>> searchSpace;
	Feedback secretFeedback = computeFeedback(guess, secret);

	vector<vector<int>> fullSpace = buildFullSearchSpace();
	for (const auto& candidate : fullSpace) {
		Feedback candidateFeedback = computeFeedback(guess, candidate);
		if (isInSearchSpace(candidateFeedback, secretFeedback)) {
			searchSpace.push_back(candidate);
		}
	}

	return searchSpace;
}
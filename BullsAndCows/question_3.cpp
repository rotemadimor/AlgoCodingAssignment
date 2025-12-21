#include "question_3.h"
#include "question_2.h"
#include "question_1.h"
#include "GameLogic.h"

constexpr int N_DIGITS = 4; // Number of digits in each guess/secret.
constexpr int K_MAX = 6; // Maximum digit value (digits in [1..K_MAX]).
constexpr int TRIALS = 20; // Number of random games to run.

map<vector<int>, Feedback> findSearchSpaceForGuess(vector<int> guessDigits, vector<int> secret) {
    map<vector<int>, Feedback> searchSpace;

    mt19937 rng(random_device{}());
    vector<int> guess = generateSecretDigitsDistinct(N_DIGITS, K_MAX, rng);
    Feedback guessFeedback = computeFeedback(guessDigits, secret);

    while (true) {
        Feedback feedback = computeFeedback(guess, secret);

        if (isCorrectFeedback(feedback, N_DIGITS)) { // found the secret
            break;
        }

        if(searchSpace.find(guess) != searchSpace.end()) { // already exists
            rng.seed(rng()); // Re-seed RNG to get different sequences.
            guess = generateSecretDigitsDistinct(N_DIGITS, K_MAX, rng);
            continue;
        }

        if(isInSearchSpace(guessFeedback, feedback)){ // in search space
            searchSpace[guess] = feedback;
        }
        
        rng.seed(rng()); // Re-seed RNG to get different sequences.
        guess = generateSecretDigitsDistinct(N_DIGITS, K_MAX, rng);
    }

    return searchSpace;
}

int findSearchSpaceSizeForGuess(vector<int> guessDigits, vector<int> secret) {
    auto searchSpace = findSearchSpaceForGuess(guessDigits, secret);
    return static_cast<int>(searchSpace.size());
}

int findMaxSizeSearchSpaceForEveryGuess(vector<int> secret) {
    int maxSize = 0;
    mt19937 rng(random_device{}());

    for(int i = 0; i < TRIALS; i++) {
        vector<int> guess = generateSecretDigitsDistinct(N_DIGITS, K_MAX, rng);
        int currentSize = findSearchSpaceSizeForGuess(guess, secret);
        if (currentSize > maxSize) {
            maxSize = currentSize;
        }

        rng.seed(rng()); // Re-seed RNG to get different sequences.
    }

    return maxSize;
}

int findMidSizeSearchSpaceForEveryGuess(vector<int> secret) {
    vector<int> sizes;
    mt19937 rng(random_device{}());

    for(int i = 0; i < TRIALS; i++) {
        vector<int> guess = generateSecretDigitsDistinct(N_DIGITS, K_MAX, rng);
        int currentSize = findSearchSpaceSizeForGuess(guess, secret);
        sizes.push_back(currentSize);

        rng.seed(rng()); // Re-seed RNG to get different sequences.
    }

    sort(sizes.begin(), sizes.end());
    return sizes[sizes.size() / 2];
}

int findMinSizeSearchSpaceForEveryGuess(vector<int> secret) {
    int minSize = INT_MAX;
    mt19937 rng(random_device{}());

    for(int i = 0; i < TRIALS; i++) {
        vector<int> guess = generateSecretDigitsDistinct(N_DIGITS, K_MAX, rng);
        int currentSize = findSearchSpaceSizeForGuess(guess, secret);
        if (currentSize < minSize) {
            minSize = currentSize;
        }

        rng.seed(rng()); // Re-seed RNG to get different sequences.
    }

    return minSize;
}

int findAverageSizeSearchSpaceForEveryGuess(vector<int> secret) {
    int totalSize = 0;
    mt19937 rng(random_device{}());

    for(int i = 0; i < TRIALS; i++) {
        vector<int> guess = generateSecretDigitsDistinct(N_DIGITS, K_MAX, rng);
        int currentSize = findSearchSpaceSizeForGuess(guess, secret);
        totalSize += currentSize;

        rng.seed(rng()); // Re-seed RNG to get different sequences.
    }

    return totalSize / TRIALS;
}
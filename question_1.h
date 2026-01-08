// ------------------------------------------------------------
// question_1.h - Question 1 consistency check interface.
// ------------------------------------------------------------
#pragma once
#include "GameLogic.h"


/**
 * Checks whether newGuess is consistent with previous guesses and feedbacks.
 *
 * Parameters:
 * - newGuess  : candidate integer code
 * - feedbacks : array of Feedback for previous guesses
 * - guesses   : array of previous integer guesses
 * - n         : number of entries in feedbacks/guesses
 *
 * Returns:
 * - true  if for every i, feedback(newGuess, guesses[i]) == feedbacks[i]
 * - false otherwise
 */
bool question_1(int newGuess, Feedback* feedbacks, int* guesses, int n);
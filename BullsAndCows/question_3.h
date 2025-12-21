#pragma once
#include "GameLogic.h"
#include <map>
#include <random>
#include <vector>
using namespace std;


// function that find search space when n = 6, k = 4
map<Feedback, int> findSearchSpace(int n, int k);

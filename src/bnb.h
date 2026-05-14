#pragma once
#include "tsp.h"
#include <vector>

enum Mode { DFS, BFS, LC };

struct Result {
    int bestCost;
    long long nodes;
    double timeMs;
};

Result branchAndBound(const TSPInstance& inst, Mode mode, bool useUB, int timeLimitMs);
#include "nn.h"
#include <vector>
#include <limits>

int nearestNeighbour(const TSPInstance& inst) {
    int n = inst.n;
    std::vector<bool> visited(n, false);

    int current = 0;
    visited[0] = true;
    int cost = 0;

    for (int i = 1; i < n; i++) {
        int next = -1;
        int best = std::numeric_limits<int>::max();

        for (int j = 0; j < n; j++) {
            if (!visited[j] && inst.matrix[current][j] < best) {
                best = inst.matrix[current][j];
                next = j;
            }
        }

        visited[next] = true;
        cost += best;
        current = next;
    }

    cost += inst.matrix[current][0];
    return cost;
}
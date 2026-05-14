#include <iostream>
#include "config.h"
#include "loader.h"
#include "bnb.h"

using namespace std;

void runAll(const TSPInstance& inst, int timeLimit) {
    cout << "\n==== " << inst.name << " (n=" << inst.n << ") ====\n";

    for (int mode = 0; mode < 3; mode++) {
        for (int ub = 0; ub < 2; ub++) {

            Result res = branchAndBound(inst, (Mode)mode, ub, timeLimit);

            string m = (mode == 0 ? "DFS" : mode == 1 ? "BFS" : "LC");

            cout << m
                 << (ub ? " +UB" : " -UB")
                 << " | cost=" << res.bestCost
                 << " | time=" << res.timeMs << " ms"
                 << " | nodes=" << res.nodes
                 << endl;
        }
    }
}

int main() {
    cout << "START PROGRAMU\n";
    Config cfg = loadConfig("config.txt");

    for (const auto& file : cfg.instances) {
        cout << "\nWczytywanie instancji: " << file << endl;

        TSPInstance inst = loadInstance(file);

        cout << "OK, n = " << inst.n << endl;

        runAll(inst, cfg.timeLimitMs);
    }

    return 0;
}
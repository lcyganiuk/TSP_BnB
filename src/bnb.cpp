#include "bnb.h"
#include "nn.h"
#include <queue>
#include <stack>
#include <limits>
#include <chrono>

using namespace std;

struct Node {
    vector<bool> visited;
    int level;
    int cost;
    int current;
};

int lowerBound(const TSPInstance& inst, const Node& node) {
    int lb = node.cost;

    int firstMin = INT_MAX;
    int secondMin = INT_MAX;

    for (int i = 0; i < inst.n; i++) {
        if (!node.visited[i]) {

            int minEdge = INT_MAX;

            for (int j = 0; j < inst.n; j++) {
                if (i != j && (!node.visited[j] || j == 0)) {
                    minEdge = min(minEdge, inst.matrix[i][j]);
                }
            }

            lb += minEdge;

            if (minEdge < firstMin) {
                secondMin = firstMin;
                firstMin = minEdge;
            } else if (minEdge < secondMin) {
                secondMin = minEdge;
            }
        }
    }

    if (firstMin != INT_MAX && secondMin != INT_MAX)
        lb += (firstMin + secondMin) / 2;

    return lb;
}

Result branchAndBound(const TSPInstance& inst, Mode mode, bool useUB, int timeLimitMs) {
    auto start = chrono::high_resolution_clock::now();

    int bestCost = INT_MAX;

    if (useUB) {
        bestCost = nearestNeighbour(inst);
    }

    long long nodes = 0;

    Node root;
    root.visited = vector<bool>(inst.n, false);
    root.visited[0] = true;
    root.level = 1;
    root.cost = 0;
    root.current = 0;

    queue<Node> q;
    stack<Node> s;

    auto cmp = [](const Node& a, const Node& b) {
        return a.cost > b.cost;
    };
    priority_queue<Node, vector<Node>, decltype(cmp)> pq(cmp);

    if (mode == BFS) q.push(root);
    if (mode == DFS) s.push(root);
    if (mode == LC) pq.push(root);

    while (true) {
        auto now = chrono::high_resolution_clock::now();
        if (chrono::duration<double, milli>(now - start).count() > timeLimitMs)
            break;

        Node node;

        if (mode == BFS) {
            if (q.empty()) break;
            node = q.front(); q.pop();
        }
        if (mode == DFS) {
            if (s.empty()) break;
            node = s.top(); s.pop();
        }
        if (mode == LC) {
            if (pq.empty()) break;
            node = pq.top(); pq.pop();
        }

        nodes++;

        if (node.level == inst.n) {
            int total = node.cost + inst.matrix[node.current][0];
            bestCost = min(bestCost, total);
            continue;
        }

        for (int i = 0; i < inst.n; i++) {
            if (!node.visited[i]) {

                Node child = node;
                child.visited[i] = true;
                child.level++;
                child.cost += inst.matrix[node.current][i];
                child.current = i;

                int lb = lowerBound(inst, child);

                if (lb < bestCost) {
                    if (mode == BFS) q.push(child);
                    if (mode == DFS) s.push(child);
                    if (mode == LC) pq.push(child);
                }
            }
        }
    }

    auto end = chrono::high_resolution_clock::now();

    return {
        bestCost,
        nodes,
        chrono::duration<double, milli>(end - start).count()
    };
}
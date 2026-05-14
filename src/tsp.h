#pragma once
#include <vector>
#include <string>

struct TSPInstance {
    std::string name;
    int n;
    std::vector<std::vector<int>> matrix;
};
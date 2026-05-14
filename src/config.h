#pragma once
#include <vector>
#include <string>

struct Config {
    std::vector<std::string> instances;
    int timeLimitMs;
};

Config loadConfig(const std::string& filename);
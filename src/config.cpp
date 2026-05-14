#include "config.h"
#include <fstream>
#include <iostream>

using namespace std;

Config loadConfig(const string& filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "BLAD: Nie mozna otworzyc pliku config: " << filename << endl;
        exit(1);
    }

    Config cfg;

    if (!(file >> cfg.timeLimitMs)) {
        cout << "BLAD: Nie mozna wczytac limitu czasu z config!" << endl;
        exit(1);
    }

    string name;
    while (file >> name) {
        cfg.instances.push_back(name);
    }

    if (cfg.instances.empty()) {
        cout << "BLAD: Brak instancji w config.txt!" << endl;
        exit(1);
    }

    cout << "Wczytano config:" << endl;
    cout << "Limit czasu: " << cfg.timeLimitMs << " ms" << endl;
    cout << "Instancje:" << endl;

    for (auto& i : cfg.instances) {
        cout << " - " << i << endl;
    }

    return cfg;
}
#include "loader.h"
#include <fstream>
#include <sstream>
#include <cmath>
#include <iostream>

#include "tsp.h"

using namespace std;

TSPInstance loadInstance(const string& filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "BLAD: Nie mozna otworzyc pliku instancji: " << filename << endl;
        exit(1);
    }
    TSPInstance inst;
    inst.name = filename;

    string line;
    int n = 0;

    vector<pair<double,double>> coords;

    while (getline(file, line)) {
        if (line.find("DIMENSION") != string::npos) {
            string tmp;
            stringstream ss(line);
            ss >> tmp >> tmp >> n;
        }

        if (line.find("NODE_COORD_SECTION") != string::npos) {
            break;
        }
    }

    if (n > 0) {
        coords.resize(n);

        for (int i = 0; i < n; i++) {
            int id, x, y;
            file >> id >> x >> y;
            coords[id - 1] = {x, y};
        }

        inst.n = n;
        inst.matrix.assign(n, vector<int>(n, 0));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                double dx = coords[i].first - coords[j].first;
                double dy = coords[i].second - coords[j].second;
                inst.matrix[i][j] = (sqrt(dx*dx + dy*dy) + 0.5);
            }
        }

        return inst;
    }

    file.clear();
    file.seekg(0);

    file >> inst.n;
    inst.matrix.resize(inst.n, vector<int>(inst.n));

    for (int i = 0; i < inst.n; i++) {
        for (int j = 0; j < inst.n; j++) {
            file >> inst.matrix[i][j];
        }
    }

    return inst;
}
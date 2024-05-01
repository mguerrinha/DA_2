#ifndef DA_PROJECT_2_TSPMANAGER_H
#define DA_PROJECT_2_TSPMANAGER_H

#include "data_structures/Graph.h"
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>

class TSPManager {
    Graph _TSPSystem;

public:
    TSPManager();

    void load_graph(const std::string &file);

    Graph getTSPSystem();

    double tsp_backtracking();
};

#endif //DA_PROJECT_2_TSPMANAGER_H

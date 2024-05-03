#ifndef DA_PROJECT_2_TSPMANAGER_H
#define DA_PROJECT_2_TSPMANAGER_H

#include "data_structures/Graph.h"
#include "Haversine.h"
#include "Coordinate.h"
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

    void load_coordinates(const std::string &file);

    Graph getTSPSystem();

    double tsp_backtracking(int idx);
};

#endif //DA_PROJECT_2_TSPMANAGER_H

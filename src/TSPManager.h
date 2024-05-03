#ifndef DA_PROJECT_2_TSPMANAGER_H
#define DA_PROJECT_2_TSPMANAGER_H

#include "data_structures/Graph.h"
#include "data_structures/MutablePriorityQueue.h"
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

    Graph getTSPSystem();

    void load_graph(const std::string &file);

    void load_coordinates_medium(const std::string &file, int num_nodes);

    void load_coordinates_real(const std::string &file);

    bool is_not_in_path(const Vertex *node, const std::vector<Vertex*> &path, unsigned int pos);

    void tspBTUtil(const Graph& graph, std::vector<Vertex*> &path, unsigned int pos, double cost, double &min_cost, std::vector<Vertex*> &min_path);

    void tsp_backtracking();

    std::vector<Vertex *> prim(Graph* g);

    double getTourCost(const std::vector<Vertex*>& tour);

    void preorderTraversal(Vertex* root, std::vector<Vertex*>& tour);

    void tsp_triangular_approx();
};

#endif //DA_PROJECT_2_TSPMANAGER_H

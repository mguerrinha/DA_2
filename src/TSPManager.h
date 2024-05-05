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
#include <limits.h>

/**
 * @brief Class representing a system for solving the Travelling Salesperson Problem
 */

class TSPManager {
    /// Graph containing the distances and indices of all vertices
    Graph _TSPSystem;

public:
    /**
     * @brief Default constructor of the TSPManager class
     */
    TSPManager();

    /**
     * @brief Returns the graph that represents this class
     * @return Graph
     */
    Graph getTSPSystem();

    /**
     * @brief Load the information (vertices and edges) about the graph into a csv file
     * Complexity: O(N)
     * @param file
     */
    void load_graph(const std::string &file);

    /**
     * @brief Load the real distances between two vertices using the Haversine formula, reading from a csv file
     * Complexity: O(N)
     * @param file
     * @param num_nodes In this case we have to restrict the number of nodes to be added according to the number desired by the user
     */
    void load_coordinates_medium(const std::string &file, int num_nodes);

    /**
     * @brief Load the real distances between two vertices using the Haversine formula, reading from a csv file
     * Complexity: O(N)
     * @param file
     */
    void load_coordinates_real(const std::string &file);

    /**
     * @brief Checks if a vertex already belongs to a path
     * Complexity: O(N)
     * @param node Vertex to be checked
     * @param path Path needed
     * @param pos Position to iterate to
     * @return True if doesn't belongs to a path, false otherwise
     */
    bool is_not_in_path(const Vertex *node, const std::vector<Vertex*> &path, unsigned int pos);

    /**
     * @brief Test all possible paths to find the optimal solution
     * Complexity: O(N!)
     * @param graph Graph to be used
     * @param path Vector where the order of visited vertices is stored
     * @param pos Current position
     * @param cost Current cost
     * @param min_cost Lowest possible cost
     * @param min_path Path corresponding to the minimum cost
     */
    void tspBTUtil(const Graph& graph, std::vector<Vertex*> &path, unsigned int pos, double cost, double &min_cost, std::vector<Vertex*> &min_path);

    /**
     * @brief Backtracking algorithm to obtain the optimal result for TSP (only for small graphs)
     * Complexity: O(N! + N)
     */
    void tsp_backtracking();

    /**
     * @brief Prim's algorithm
     * Complexity: O(E * logV)
     * @param g Graph to be used
     * @return Minimum cost tree
     */
    std::vector<Vertex *> prim(Graph* g);

    /**
     * @brief Calculates the cost of a given path
     * Complexity: O(N)
     * @param tour Path to be used
     * @return Returns a tour's cost
     */
    double getTourCost(const std::vector<Vertex*>& tour);

    /**
     * @brief "Rebuild" the path using DFS
     * Complexity: O(V + E)
     * @param root Starting vertex
     * @param tour Path to be filled in
     */
    void preorderTraversal(Vertex* root, std::vector<Vertex*>& tour);

    /**
     * @brief Applies the Triangular Approximation Heuristic
     * Complexity: O((E * logV) + 2V + E + 2N)
     */
    void tsp_triangular_approx();

    /**
     * @brief Nearest neighbor heuristic to calculate a non-optimal minimum cost for the TSP
     * Complexity: O(V + N * E + N)
     * @param idx Starting vertex
     */
    void tsp_nearest_neighbour(int idx);
};

#endif //DA_PROJECT_2_TSPMANAGER_H

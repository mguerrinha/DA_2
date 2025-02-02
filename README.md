# Travelling Salesperson Problem (TSP) Manager
## Grade: 12,9/20

This project was conducted in the **second year, second semester** as part of our Algorithm Design course. The objective was to develop a system that solves the **Travelling Salesperson Problem (TSP)** using various algorithms and heuristics, applying them to graph structures representing distances between cities or points of interest.

## Overview

In this project, we developed a TSP Manager in **C++** that models and solves the Travelling Salesperson Problem. The system allows for the calculation of optimal or near-optimal paths that visit a set of vertices (cities, locations) exactly once and return to the starting point. This problem is tackled using both exact algorithms, suitable for small graphs, and approximation heuristics for larger graphs, leveraging concepts such as the Haversine formula for real-world distance calculations.

## Features

### Key Features

- **Graph-Based TSP System**
  - Represents the TSP problem using a graph where vertices represent cities or locations, and edges represent the distances between them.

- **Data Management**
  - Loads vertices and edges from CSV files, with support for real-world coordinates and distance calculations using the Haversine formula.

- **Exact TSP Solutions**
  - Implements a backtracking algorithm to find the optimal solution for small graphs, ensuring the minimum possible travel cost.

- **Approximation Heuristics**
  - **Triangular Approximation:** Constructs a minimum spanning tree and performs a depth-first traversal to approximate a solution.
  - **Christofides Algorithm:** Combines a minimum spanning tree with a minimum-weight perfect matching to find a solution with a guaranteed approximation ratio.
  - **Nearest Neighbor Heuristic:** A greedy approach that builds a tour by repeatedly visiting the nearest unvisited vertex.

- **Path Cost Calculation**
  - Calculates the total cost of a given tour, helping to evaluate and compare different TSP solutions.

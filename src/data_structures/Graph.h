#ifndef DA_PROJECT_2_GRAPH_H
#define DA_PROJECT_2_GRAPH_H

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include "Vertex.h"
#include "Edge.h"

class Vertex;
class Edge;

class Graph {
public:
    [[nodiscard]] Vertex *findVertex(const int &in) const;

    bool addVertex(const int &in);

    bool removeVertex(const int &in);

    [[nodiscard]] bool addEdge(const int &sourc, const int &dest, double dist) const;

    [[nodiscard]] bool removeEdge(const int &source, const int &dest) const;

    std::unordered_map<int, Vertex*> getVertexSet() const;

    bool addBidirectionalEdge(const int &sourc, const int &dest, double dist);

    [[nodiscard]] int findVertexIdx(const int &in) const;

protected:
    std::unordered_map<int, Vertex*> vertexSet;
};

#endif //DA_PROJECT_2_GRAPH_H

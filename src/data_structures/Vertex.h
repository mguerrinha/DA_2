#ifndef DA_PROJECT_2_VERTEX_H
#define DA_PROJECT_2_VERTEX_H

#include "Edge.h"
#include <string>
#include <vector>
#include <iostream>

class Edge;

class Vertex {
public:
    explicit Vertex(int in);

    bool operator<(Vertex & vertex) const;

    [[nodiscard]] int getInfo() const;

    [[nodiscard]] double getDist() const;

    [[nodiscard]] std::vector<Edge *> getAdj() const;

    [[nodiscard]] bool isVisited() const;

    [[nodiscard]] bool isProcessing() const;

    [[nodiscard]] unsigned int getIndegree() const;

    [[nodiscard]] Edge *getPath() const;

    void setDist(double dist);

    [[nodiscard]] std::vector<Edge *> getIncoming() const;

    void setVisited(bool visited);

    void setProcesssing(bool processing);

    void setIndegree(unsigned int indegree);

    void setPath(Edge *path);

    Edge * addEdge(Vertex *dest, double dist);

    Edge* findEdge(Vertex* dest);

    bool removeEdge(int in);

    void removeOutgoingEdges();

protected:
    int info;

    double dist = 0;

    std::vector<Edge *> adj;

    bool visited = false;

    bool processing = false;

    unsigned int indegree{};

    Edge *path = nullptr;

    std::vector<Edge *> incoming;

    void deleteEdge(Edge *edge);
};

#endif //DA_PROJECT_2_VERTEX_H

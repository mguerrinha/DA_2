
#include "Graph.h"

std::unordered_map<int, Vertex*> Graph::getVertexSet() const {
    return vertexSet;
}

Vertex * Graph::findVertex(const int &in) const {
    auto it = vertexSet.find(in);
    return (it != vertexSet.end()) ? it->second : nullptr;
}

bool Graph::addVertex(const int &in) {
    if (findVertex(in) != nullptr)
        return false;
    vertexSet.emplace(in, new Vertex(in));
    return true;
}

bool Graph::addEdge(const int &sourc, const int &dest, double dist) const {

}

bool Graph::removeEdge(const int &sourc, const int &dest) const {

}

bool Graph::addBidirectionalEdge(const int &sourc, const int &dest, double dist) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2, dist);
    v2->addEdge(v1, dist);
    return true;
}

int Graph::findVertexIdx(const int &in) const {

}
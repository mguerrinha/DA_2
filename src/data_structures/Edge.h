#ifndef DA_PROJECT_2_EDGE_H
#define DA_PROJECT_2_EDGE_H

#include "Vertex.h"

class Vertex;

class Edge {
public:
    Edge(Vertex *orig, Vertex *dest, double dist);

    [[nodiscard]] Vertex * getDest() const;

    [[nodiscard]] double getDist() const;

    [[nodiscard]] bool isSelected() const;

    [[nodiscard]] Vertex * getOrig() const;

    [[nodiscard]] Edge * getReverse() const;

    void setSelected(bool selected);

    void setReverse(Edge *reverse);

protected:
    Vertex * dest;

    double dist;

    bool selected = false;

    Vertex *orig;

    Edge *reverse = nullptr;
};

#endif //DA_PROJECT_2_EDGE_H

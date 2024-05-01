#include "Edge.h"

Edge::Edge(Vertex *orig, Vertex *dest, double dist): orig(orig), dest(dest), dist(dist) {}

Vertex * Edge::getDest() const {
    return this->dest;
}

double Edge::getDist() const {
    return this->dist;
}

Vertex * Edge::getOrig() const {
    return this->orig;
}

Edge *Edge::getReverse() const {
    return this->reverse;
}

bool Edge::isSelected() const {
    return this->selected;
}

void Edge::setSelected(bool selected) {
    this->selected = selected;
}

void Edge::setReverse(Edge *reverse) {
    this->reverse = reverse;
}

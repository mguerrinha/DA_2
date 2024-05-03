#include "TSPManager.h"
#include <iomanip>

TSPManager::TSPManager() = default;

void TSPManager::load_graph(const std::string &file) {
    std::ifstream arquivo(file);
    std::string linha;
    getline(arquivo, linha);

    while (std::getline(arquivo, linha)) {
        std::stringstream linhaStream(linha);
        std::string orig, dest, dist;
        if (std::getline(linhaStream, orig, ',')
            && std::getline(linhaStream, dest, ',')
            && std::getline(linhaStream, dist, ',')) {
        _TSPSystem.addVertex(std::stoi(orig));
        _TSPSystem.addVertex(std::stoi(dest));
        _TSPSystem.addBidirectionalEdge(std::stoi(orig), std::stoi(dest), std::stod(dist));
        }
    }
}

void TSPManager::load_coordinates(const std::string &file) {
    std::ifstream arquivo(file);
    std::string linha;
    getline(arquivo, linha);

    while (std::getline(arquivo, linha)) {
        std::stringstream linhaStream(linha);
        std::string idx, longi, lati;
        if (std::getline(linhaStream, idx, ',')
            && std::getline(linhaStream, longi, ',')
            && std::getline(linhaStream, lati, ',')) {
            _TSPSystem.findVertex(stoi(idx))->setCoord(Coordinate{std::stod(lati), std::stod(longi)});
        }
    }
}

Graph TSPManager::getTSPSystem() {
    return _TSPSystem;
}

bool is_not_in_path(const Vertex *node, const std::vector<Vertex*> &path, unsigned int pos) {
    for (unsigned int i = 0; i < pos; ++i) {
        if (path[i] == node) {
            return false;
        }
    }
    return true;
}

void tspBTUtil(const Graph& graph, std::vector<Vertex*> &path, unsigned int pos, double cost, double &min_cost, std::vector<Vertex*> &min_path) {
    if (pos == path.size()) {
        Edge* lastToFirstEdge = path.back()->findEdge(path[0]);
        if (lastToFirstEdge) {
            double current_cost = cost + lastToFirstEdge->getDist();
            if (current_cost < min_cost) {
                min_cost = current_cost;
                min_path = path;
                min_path.push_back(path[0]);
            }
        }
        return;
    }

    Vertex* last = path[pos - 1];
    for (Edge* edge : last->getAdj()) {
        Vertex* next = edge->getDest();
        if (is_not_in_path(next, path, pos) && edge->getDist() > 0) {
            path[pos] = next;
            tspBTUtil(graph, path, pos + 1, cost + edge->getDist(), min_cost, min_path);
        }
    }
}

double TSPManager::tsp_backtracking(int idx) {
    double min_cost = std::numeric_limits<double>::max();
    std::vector<Vertex*> min_path;
    std::vector<Vertex*> tmp_path(_TSPSystem.getVertexSet().size(), nullptr);
    tmp_path[0] = _TSPSystem.findVertex(idx);

    tspBTUtil(_TSPSystem, tmp_path, 1, 0, min_cost, min_path);

    std::cout << "Minimum Cost: " << min_cost << std::endl;
    std::cout << "Path: ";
    int aux = 0;
    for (Vertex* v : min_path) {
        std::cout << v->getInfo();
        aux++;
        if (aux == min_path.size()) continue;
        else {
            std::cout << " -> ";
        }
    }
    std::cout << std::endl;

    return min_cost;
}

/*
A ideia do backtracking para o TSP seria que inicialmente podemos começar em qualquer ponto dado que o grafo é fully-connected, logo pelo que percebi, o min cost será sempre o mesmo
 apenas teres um path diferente, a ideia seria então percorrer os pontos adjacentes ao selecionado conforme vamos guardado o path e o cost atual, até chegarmos ao ponto de início, a ideia
 será todas as possibilidades, por isso depois por recursão (dfs) por exemplo em vez de optarmos inicialmente por x ponto, vamos por y ponto.
*/
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
            _TSPSystem.findVertex(stoi(idx))->setCoord(Coordinate{std::stod(longi), std::stod(lati)});
        }
    }
}

Graph TSPManager::getTSPSystem() {
    return _TSPSystem;
}

bool is_not_in_path(const Vertex *node, const std::vector<Vertex*> &path, unsigned int pos) { // testa se um vertex pertence ao path atual até pos
    for (unsigned int i = 0; i < pos; ++i) {
        if (path[i] == node) {
            return false;
        }
    }
    return true;
}

void tspBTUtil(const Graph& graph, std::vector<Vertex*> &path, unsigned int pos, double cost, double &min_cost, std::vector<Vertex*> &min_path) {
    // quando chega ao final de um path
    if (pos == path.size()) {
        Edge* lastToFirstEdge = path.back()->findEdge(path[0]); // verifica se o último vertex tem ligação direta para o primeiro vertex ( só assim o path é válido)
        if (lastToFirstEdge) { // se existir entra no if
            double current_cost = cost + lastToFirstEdge->getDist(); // soma o cost atual ao cost da última edge necessária
            if (current_cost < min_cost) {
                min_cost = current_cost;
                min_path = path;
                min_path.push_back(path[0]); // adiciona o primeiro vertex para "fechar" o path
            }
        }
        return;
    }

    Vertex* last = path[pos - 1];
    for (Edge* edge : last->getAdj()) {
        Vertex* next = edge->getDest();
        if (is_not_in_path(next, path, pos) && edge->getDist() > 0) {
            path[pos] = next; // adiciona ao path o próximo vertex (adjacente ao anterior)
            tspBTUtil(graph, path, pos + 1, cost + edge->getDist(), min_cost, min_path); // avança para o próximo vertex e assim sucessivamente, até pos == path.size()
        }
    }
}

double TSPManager::tsp_backtracking() { // backtracking testa todas as possibilidades
    double min_cost = std::numeric_limits<double>::max();
    std::vector<Vertex*> min_path;
    std::vector<Vertex*> tmp_path(_TSPSystem.getVertexSet().size(), nullptr);
    tmp_path[0] = _TSPSystem.getVertexSet()[0];

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
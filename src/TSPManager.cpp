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

void TSPManager::tsp_backtracking() { // backtracking testa todas as possibilidades
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
}

std::vector<Vertex *> prim(Graph* g) { // Ao contrário do Kruskal, retira sempre a edge com menor distância que seja adjacente a um dos vertex já selecionados
    if(g == nullptr) return {};

    std::vector<Vertex *> vertices = g->getVertexSet();
    for(Vertex* v : vertices) {
        v->setDist(std::numeric_limits<double>::max());
        v->setVisited(false);
        v->setPath(nullptr);
    }

    MutablePriorityQueue<Vertex> q;

    vertices[0]->setDist(0);
    q.insert(vertices[0]);

    while(!q.empty()) {
        Vertex * v = q.extractMin(); // Extrai o vertex com a mínima distância possível
        v->setVisited(true);

        for(Edge* e : v->getAdj()) {
            Vertex * w = e->getDest();
            if(!w->isVisited() && e->getDist() < w->getDist()) {
                double oldDist = w->getDist(); // Salva distância antiga
                w->setDist(e->getDist()); // Atualiza a distância do vertex
                w->setPath(e);

                if(oldDist == std::numeric_limits<double>::max()) {
                    q.insert(w); // Se a distância fosse infinita, não pertencia à queue
                } else {
                    q.decreaseKey(w); // Pode ou não ganhar prioridade conforme a atualização do seu valor do Dist (maior prioridade se tiver um valor menor)
                }
            }
        }
    }
    // Coleta os vertex pertences à MST
    std::vector<Vertex *> mst;
    for(Vertex* v : vertices) {
        if(v->isVisited()) {
            mst.push_back(v);
        }
    }
    return mst;
}

void TSPManager::tsp_triangular_aprox() {
    std::vector<Vertex*> mst = prim(&_TSPSystem);

}
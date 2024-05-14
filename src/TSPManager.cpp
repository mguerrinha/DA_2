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

void TSPManager::load_coordinates_medium(const std::string &file, int num_nodes) {
    int nodes_needed = 0;
    std::ifstream arquivo(file);
    std::string linha;
    getline(arquivo, linha);

    while (std::getline(arquivo, linha)) {
        std::stringstream linhaStream(linha);
        std::string idx, longi, lati;
        if (std::getline(linhaStream, idx, ',')
            && std::getline(linhaStream, longi, ',')
            && std::getline(linhaStream, lati, ',')) {
            nodes_needed++;
            if (nodes_needed <= num_nodes) {
                _TSPSystem.findVertex(stoi(idx))->setCoord(Coordinate{std::stod(longi), std::stod(lati)});
            } else {
                break;
            }
        }
    }
}

void TSPManager::load_coordinates_real(const std::string &file) {
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

bool TSPManager::is_not_in_path(const Vertex *node, const std::vector<Vertex*> &path, unsigned int pos) { // testa se um vertex pertence ao path atual até pos
    for (unsigned int i = 0; i < pos; ++i) {
        if (path[i] == node) {
            return false;
        }
    }
    return true;
}

void TSPManager::tspBTUtil(const Graph& graph, std::vector<Vertex*> &path, unsigned int pos, double cost, double &min_cost, std::vector<Vertex*> &min_path) {
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

std::vector<Vertex *> TSPManager::prim(Graph* g) { // Ao contrário do Kruskal, retira sempre a edge com menor distância que seja adjacente a um dos vertex já selecionados
    if(g == nullptr) return {};
    std::unordered_map<int, Vertex*> vertices = g->getVertexSet();

    for(auto v : vertices) {
        v.second->setDist(std::numeric_limits<double>::max());
        v.second->setVisited(false);
        v.second->setPath(nullptr);
    }

    MutablePriorityQueue<Vertex> q;

    vertices[0]->setDist(0);
    q.insert(vertices[0]);
    std::vector<Vertex*> mst;
    while (!q.empty()) {
        Vertex *v = q.extractMin(); // Extrai o vertex com a mínima distância possível
        v->setVisited(true);
        mst.push_back(v);

        for (auto w : vertices) {  // Iterar sobre todos os vértices para garantir a verificação completa
            if (v != w.second && !w.second->isVisited()) {  // Evita auto-loop e verifica apenas vértices não visitados
                Edge *e = v->findEdge(w.second);
                double dist = (e != nullptr) ? e->getDist() : Haversine::calculateDistance(v->getCoord(), w.second->getCoord());
                _TSPSystem.addBidirectionalEdge(v->getInfo(), w.first, dist);
                e = v->findEdge(w.second);
                if (dist < w.second->getDist()) {
                    double oldDist = w.second->getDist(); // Salva distância antiga
                    w.second->setDist(dist); // Atualiza a distância do vertex
                    w.second->setPath(e);
                    e->setSelected(true);

                    if (oldDist == std::numeric_limits<double>::max()) {
                        q.insert(w.second); // Se a distância for infinita, não pertence à queue
                    } else {
                        q.decreaseKey(w.second); // Pode ou não ganhar prioridade conforme a atualização do seu valor do Dist (maior prioridade se tiver um valor menor)
                    }
                }
            }
        }
    }
    return mst;
}

double TSPManager::getTourCost(const std::vector<Vertex*>& tour) {
    double totalCost = 0.0;
    for (size_t i = 0; i < tour.size() - 1; ++i) {
        Vertex* current = tour[i];
        Vertex* next = tour[i + 1];
        Edge* edge = current->findEdge(next);
        if (edge) {
            totalCost += edge->getDist();
        } else {
            totalCost += Haversine::calculateDistance(current->getCoord(), next->getCoord());
        }
    }
    return totalCost;
}

void TSPManager::preorderTraversal(Vertex* root, std::vector<Vertex*>& tour) { // Basicamente DFS para reconstruir o path, o path não está a sair corretamente pq está por ordem numérica
    if (root == nullptr || root->isVisited()) return;
    root->setVisited(true);
    tour.push_back(root);

    for (Edge* edge : root->getAdj()) {
        Vertex* child = edge->getDest();
        if (!child->isVisited()) {
            preorderTraversal(child, tour);
        }
    }
}

void TSPManager::tsp_triangular_approx() {
    std::vector<Vertex*> mst = prim(&_TSPSystem);
    std::vector<Vertex*> tour;

    for (Vertex* vertex : mst) {
        vertex->setVisited(false);
    }

    preorderTraversal(mst[0], tour);

    if (!tour.empty()) {
        tour.push_back(tour[0]);
    }

    double tourCost = getTourCost(tour);

    std::cout << "TSP Tour: ";
    int aux = 0;
    for (Vertex* v : tour) {
        std::cout << v->getInfo();
        aux++;
        if (aux == tour.size()) continue;
        else {
            std::cout << " -> ";
        }
    }
    std::cout << std::endl;
    std::cout << "Total Cost of TSP Tour: " << tourCost << std::endl;
}

bool edgeCompare(Edge* a, Edge* b) {
    return a->getDist() < b->getDist();
}

std::vector<Edge*> TSPManager::computeGreedyMWPM(std::vector<std::vector<double>> matrix, const std::vector<Vertex*>& oddVertices) {
    std::vector<Edge*> edges;

    for (int i = 0; i < oddVertices.size(); i++) {
        for (int j = i+1; j < oddVertices.size(); j++) {
            if (matrix[i][j] > 0) {
                edges.push_back(oddVertices[i]->findEdge(oddVertices[j]));
            }
        }
    }

    // Sort edges by weight
    std::sort(edges.begin(), edges.end(), edgeCompare);

    std::vector<Edge*> result;
    for(Edge* e : edges) {
        e->getDest()->setProcesssing(false);
        e->getOrig()->setProcesssing(false);
    }

    // Pick minimum weight edges while ensuring no vertex is matched more than once
    for (Edge* e : edges) {

        if (!e->getOrig()->isProcessing() && !e->getDest()->isProcessing()) {
            result.push_back(e);
            e->setSelected(true);
            e->getDest()->setProcesssing(true);
            e->getOrig()->setProcesssing(true);
        }
    }

    return result;
}

void TSPManager::tsp_christofides_algorithm() {
    for (auto vertex : _TSPSystem.getVertexSet()) {
        vertex.second->setProcesssing(false);
        vertex.second->setVisited(false);
        vertex.second->setDegree(0);
        for (Edge* edge : vertex.second->getAdj()) {
            edge->setSelected(false);
        }
    }

    std::vector<Vertex *> mst = prim(&_TSPSystem);
    mst[0]->setPath(mst.back()->findEdge(mst[0]));
    std::vector<Edge*> edges;
    for (Vertex * v : mst) {
        Edge* edge = v->getPath();
        edge->setSelected(true);
        edges.push_back(edge);
        edge->getOrig()->setDegree(edge->getOrig()->getDegree()+1);
        edge->getDest()->setDegree(edge->getDest()->getDegree()+1);
    }

    std::vector<Vertex *> odd_degree_vertices;
    for (Vertex* vertex : mst) {
        if(vertex->getDegree() % 2 == 1) {
            odd_degree_vertices.push_back(vertex);
        }
    }

    std::vector<std::vector<double>> matrix (odd_degree_vertices.size(), std::vector<double>(odd_degree_vertices.size(), 0));
    for (int row = 0; row < odd_degree_vertices.size(); row++) {
        for (int col = 0; col < odd_degree_vertices.size(); col++) {
            if (row == col) {
                matrix[row][col] = 0;
            }
            else {
                Edge* edge = odd_degree_vertices[row]->findEdge(odd_degree_vertices[col]);
                matrix[row][col] = (edge != nullptr) ? edge->getDist() : Haversine::calculateDistance(odd_degree_vertices[row]->getCoord(), odd_degree_vertices[col]->getCoord());
                _TSPSystem.addBidirectionalEdge(odd_degree_vertices[row]->getInfo(), odd_degree_vertices[col]->getInfo(), matrix[row][col]);
            }
        }
    }

    std::vector<Edge*> edgesaux = computeGreedyMWPM(matrix, odd_degree_vertices);

    for (Edge* edge : edgesaux) {
        edges.push_back(edge);
    }
    for (auto v : _TSPSystem.getVertexSet()) {
        v.second->setVisited(false);
    }
    std::vector<int> path;
    unsigned int n = _TSPSystem.getVertexSet().size();
    Vertex* auxVertex = _TSPSystem.getVertexSet().at(0);
    path.push_back(auxVertex->getInfo());
    n--;
    double totalCost = 0;
    while (n > 0) {
        for (Edge* edge : auxVertex->getAdj()) {
            if (edge->isSelected() && !edge->getDest()->isVisited()) {
                auxVertex = edge->getDest();
                edge->getDest()->setVisited(true);
                path.push_back(edge->getDest()->getInfo());
                totalCost += edge->getDist();
                n--;
            }
        }
    }
    path.push_back(path[0]);
    Edge* e = _TSPSystem.findVertex(path[0])->findEdge(_TSPSystem.findVertex(path.back()));
    totalCost += (e != nullptr) ? e->getDist() : Haversine::calculateDistance(_TSPSystem.findVertex(path[0])->getCoord(), _TSPSystem.findVertex(path.back())->getCoord());

    int aux = 0;
    std::cout << "Path: ";
    for (int v : path) {
        std::cout << v;
        aux++;
        if (aux == path.size()) continue;
        else {
            std::cout << " -> ";
        }
    }
    std::cout << std::endl;
    std::cout << "Total Cost: " << totalCost << std::endl;

}

void TSPManager::tsp_nearest_neighbour(int idx) {
    std::vector<int> path;
    int cnt_num = 0; // incrementado a cada vertex visited
    int num_nodes = _TSPSystem.getVertexSet().size();
    for (auto v : _TSPSystem.getVertexSet()) {
        v.second->setVisited(false);
    }
    Vertex* start_vertex = _TSPSystem.findVertex(idx);
    Vertex* initial_vertex = start_vertex; // salvar o vertex inicial (idx)
    start_vertex->setVisited(true);
    path.push_back(start_vertex->getInfo());
    cnt_num++;
    double totalCost = 0;

    while (cnt_num < num_nodes) { // termina quando todos os vertex forem visitados
        double currentCost = std::numeric_limits<double>::max();
        Edge * currentEdge = nullptr;

        for (Edge* e : start_vertex->getAdj()) {
            if (!e->getDest()->isVisited() && e->getDist() < currentCost) {
                currentCost = e->getDist();
                currentEdge = e;
            }
        }

        if (currentEdge == nullptr) {
            break;
        }

        totalCost += currentCost;
        start_vertex = currentEdge->getDest();
        start_vertex->setVisited(true);
        path.push_back(start_vertex->getInfo());
        cnt_num++;
    }

    int lastIdx = path[(path.size() -1)];
    if (_TSPSystem.findVertex(lastIdx)->findEdge(initial_vertex) == nullptr) {
        std::cout << "No path found." << std::endl;
        return;
    } else {
        totalCost += _TSPSystem.findVertex(lastIdx)->findEdge(initial_vertex)->getDist();
    }
    path.push_back(initial_vertex->getInfo());

    int aux = 0;
    std::cout << "Path: ";
    for (int v : path) {
        std::cout << v;
        aux++;
        if (aux == path.size()) continue;
        else {
            std::cout << " -> ";
        }
    }
    std::cout << std::endl;
    std::cout << "Total Cost: " << totalCost << std::endl;
}

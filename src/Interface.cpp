#include "Interface.h"

Interface::Interface() = default;

TSPManager Interface::_TSPManager;

void Interface::run() {
    bool running = true;
    int choice1, choice2;
    double time_used;
    clock_t start, end;
    std::cout << "Welcome to our TSP system management!" << std::endl;

    while (running) {
        choice1 = displayLoadOptions();
        switch (choice1) {
            case 0:
                std::cout << "Thank you for using our TSP system!" << std::endl;
                running = false;
                break;
            case 1:
                choice2 = displayToyGraphOptions();
                switch (choice2) {
                    case 0:
                        run();
                        break;
                    case 1:
                        _TSPManager.load_graph("../dataset/Toy-Graphs/shipping.csv");
                        break;
                    case 2:
                        _TSPManager.load_graph("../dataset/Toy-Graphs/stadiums.csv");
                        break;
                    case 3:
                        _TSPManager.load_graph("../dataset/Toy-Graphs/tourism.csv");
                        break;
                    default:
                        break;
                }
                chooseMainMenuOptions();
                running = false;
                break;
            case 2:
                choice2 = displayFullyConnectedGraphOptions();
                if (choice2 == 0) {
                    run();
                } else {
                    std::string path = "../dataset/Extra_Fully_Connected_Graphs/edges_" + std::to_string(choice2) + ".csv";
                    _TSPManager.load_graph(path);
                }
                _TSPManager.load_coordinates_medium("../dataset/Extra_Fully_Connected_Graphs/nodes.csv", choice2);
                chooseMainMenuOptions();
                running = false;
                break;
            case 3:
                choice2 = displayRealWorldGraphOptions();
                switch (choice2) {
                    case 0:
                        run();
                        break;
                    case 1:
                        start = clock();
                        _TSPManager.load_graph("../dataset/Real-world Graphs/graph1/edges.csv");
                        _TSPManager.load_coordinates_real("../dataset/Real-world Graph/graph1/nodes.csv");
                        end = clock();
                        time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                        std::cout << "Function takes " << time_used << " seconds to execute." << std::endl;
                        break;
                    case 2:
                        start = clock();
                        _TSPManager.load_graph("../dataset/Real-world Graphs/graph2/edges.csv");
                        _TSPManager.load_coordinates_real("../dataset/Real-world Graph/graph2/nodes.csv");
                        end = clock();
                        time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                        std::cout << "Function takes " << time_used << " seconds to execute." << std::endl;
                        break;
                    case 3:
                        start = clock();
                        _TSPManager.load_graph("../dataset/Real-world Graphs/graph3/edges.csv");
                        _TSPManager.load_coordinates_real("../dataset/Real-world Graph/graph3/nodes.csv");
                        end = clock();
                        time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                        std::cout << "Function takes " << time_used << " seconds to execute." << std::endl;
                        break;
                    default:
                        break;
                }
                chooseMainMenuOptions();
                running = false;
                break;
            default:
                break;
        }
    }
}

int Interface::displayLoadOptions() {
    int option = -1;
    std::string line;
    bool validInput = false;

    while (!validInput) {
        std::cout << "---------- Load Options -------------" << std::endl;
        std::cout << "1 --> Load one of the Toy Graphs." << std::endl;
        std::cout << "2 --> Load one of the Extra-Fully-Connected Graphs." << std::endl;
        std::cout << "3 --> Load one of the Real-word Graphs." << std::endl;
        std::cout << "0 --> Exit." << std::endl;
        std::cout << "Choose one option: ";

        std::getline(std::cin, line);
        std::stringstream in(line);

        if (in >> option && (in.eof() || in.peek() == '\n' || in.peek() == ' ')) {
            if (option >= 0 && option <= 3) {
                validInput = true;
            }
        }

        if (!validInput) {
            std::cout << "Error: Invalid input. Please enter a valid number between 0 and 3." << std::endl;
        }
    }

    return option;
}

int Interface::displayToyGraphOptions() {
    int option = -1;
    std::string line;
    bool validInput = false;

    while (!validInput) {
        std::cout << "---------- Load Options -------------" << std::endl;
        std::cout << "1 --> Load Shipping Graph." << std::endl;
        std::cout << "2 --> Load Stadium Graph." << std::endl;
        std::cout << "3 --> Load Tourism Graph." << std::endl;
        std::cout << "0 --> Return" << std::endl;
        std::cout << "Choose one option: ";

        std::getline(std::cin, line);
        std::stringstream in(line);

        if (in >> option && (in.eof() || in.peek() == '\n' || in.peek() == ' ')) {
            if (option >= 0 && option <= 3) {
                validInput = true;
            }
        }

        if (!validInput) {
            std::cout << "Error: Invalid input. Please enter a valid number between 0 and 3." << std::endl;
        }
    }

    return option;
}

int Interface::displayFullyConnectedGraphOptions() {
    int num_nodes;
    std::string line;
    bool validInput = false;

    while (!validInput) {
        std::cout << "Enter the number of nodes (25, 50, 75, 100, 200, 300, 400, 500, 600, 700, 800, 900) or 0 to return: ";
        std::getline(std::cin, line);
        std::stringstream in(line);

        if (in >> num_nodes && (in.eof() || in.peek() == '\n' || in.peek() == ' ')) {
            if (num_nodes == 0 || (num_nodes % 25 == 0 && num_nodes <= 900)) {
                validInput = true;
            }
        }

        if (!validInput) {
            std::cout << "Error: Invalid input. Please enter a valid number of nodes as specified, or 0 to return." << std::endl;
        }
    }

    return num_nodes;
}

int Interface::displayRealWorldGraphOptions() {
    int option = -1;
    std::string line;
    bool validInput = false;

    while (!validInput) {
        std::cout << "---------- Load Options -------------" << std::endl;
        std::cout << "1 --> Load Graph 1." << std::endl;
        std::cout << "2 --> Load Graph 2." << std::endl;
        std::cout << "3 --> Load Graph 3." << std::endl;
        std::cout << "0 --> Return" << std::endl;
        std::cout << "Choose one option: ";

        std::getline(std::cin, line);
        std::stringstream in(line);

        if (in >> option && (in.eof() || in.peek() == '\n' || in.peek() == ' ')) {
            if (option >= 0 && option <= 3) {
                validInput = true;
            }
        }

        if (!validInput) {
            std::cout << "Error: Invalid input. Please enter a valid number between 0 and 3." << std::endl;
        }
    }

    return option;
}

int Interface::displayMainMenu() {
    int option = -1;
    std::string line;
    bool validInput = false;

    while (!validInput) {
        std::cout << "---------- Main Menu -------------" << std::endl;
        std::cout << "1 --> TSP using Backtracking." << std::endl; // 4.1
        std::cout << "2 --> TSP using Triangular Approximation Heuristic." << std::endl; // 4.2
        std::cout << "3 --> TSP using Christofides Algorithm." << std::endl; // 4.3
        std::cout << "4 --> TSP using Nearest Neighbour Heuristic." << std::endl; // 4.4
        std::cout << "0 --> Exit." << std::endl;
        std::cout << "Choose one option: ";

        std::getline(std::cin, line);
        std::stringstream in(line);

        if (in >> option && (in.eof() || in.peek() == '\n' || in.peek() == ' ')) {
            if (option >= 0 && option <= 4) {
                validInput = true;
            }
        }

        if (!validInput) {
            std::cout << "Error: Invalid input. Please enter a valid number between 0 and 4." << std::endl;
        }
    }

    return option;
}

void Interface::chooseMainMenuOptions() {
    bool running = true;
    int choice, idx_choosed;
    double time_used;
    clock_t start, end;
    while (running) {
        choice = displayMainMenu();
        switch (choice) {
            case 0:
                running = false;
                break;
            case 1:
                start = clock();
                _TSPManager.tsp_backtracking();
                end = clock();
                time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                std::cout << "Function takes " << time_used << " seconds to execute." << std::endl;
                break;
            case 2:
                start = clock();
                _TSPManager.tsp_triangular_approx();
                end = clock();
                time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                std::cout << "Function takes " << time_used << " seconds to execute." << std::endl;
                break;
            case 3:
                start = clock();
                _TSPManager.tsp_christofides_algorithm();
                end = clock();
                time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                std::cout << "Function takes " << time_used << " seconds to execute." << std::endl;
                break;
            case 4:
                std::cout << "Insert the desired index. ";
                std::cin >> idx_choosed;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                start = clock();
                _TSPManager.tsp_nearest_neighbour(idx_choosed);
                end = clock();
                time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                std::cout << "Function takes " << time_used << " seconds to execute." << std::endl;
                break;
            default:
                break;
        }
    }
}

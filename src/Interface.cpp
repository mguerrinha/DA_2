#include "Interface.h"

Interface::Interface() = default;

TSPManager Interface::_TSPManager;

void Interface::run() {
    Graph graph;
    bool running = true;
    std::cout << "Welcome to our TSP system management!" << std::endl;

    while (running) {
        int choice = displayLoadOptions();
        switch (choice) {
            case 0:
                std::cout << "Thank you for using our TSP system!" << std::endl;
                running = false;
                break;
            case 1:
                _TSPManager.load_graph("../dataset/Toy-Graphs/tourism.csv");
                _TSPManager.tsp_backtracking();
                running = false;
                break;
        }
    }
}

int Interface::displayLoadOptions() {
    int option = -1;
    std::string line;
    bool validInput = false;

    while (!validInput) {
        std::cout << "-----------Load Options -------------" << std::endl;
        std::cout << "1 --> Load Toy dataset" << std::endl;
        std::cout << "0 --> Exit" << std::endl;
        std::cout << "Choose one option: ";

        std::getline(std::cin, line);
        std::stringstream in(line);

        if (in >> option && (in.eof() || in.peek() == '\n' || in.peek() == ' ')) {
            if (option >= 0 && option <= 1) {
                validInput = true;
            }
        }

        if (!validInput) {
            std::cout << "Error: Invalid input. Please enter a valid number between 0 and 1." << std::endl;
        }
    }

    return option;
}

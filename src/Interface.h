#ifndef DA_PROJECT_2_INTERFACE_H
#define DA_PROJECT_2_INTERFACE_H

#include "TSPManager.h"

/**
 * @brief Class that allows interaction with the user
 */

class Interface {
public:
    /**
     * @brief Default constructor of the Interface class
     */
    Interface();

    /**
     * @brief Executes the program
     */
    static void run();

private:

    /**
     * @brief Object of the TSPManager class, which contains all the relative information needed for the problem
     */
    static TSPManager _TSPManager;

    /**
     * @brief Menu for choosing the main dataset
     * @return Number corresponding to the desired dataset
     */
    static int displayLoadOptions();

    /**
     * @brief Choose one of the Toy Graphs
     * @return Number corresponding to the desired graph
     */
    static int displayToyGraphOptions();

    /**
     * @brief Choose one of the Fully Connected Graphs
     * @return Number corresponding to the desired graph
     */
    static int displayFullyConnectedGraphOptions();

    /**
     * @brief Choose one of the Real World Graphs
     * @return Number corresponding to the desired graph
     */
    static int displayRealWorldGraphOptions();

    /**
     * @brief The program's main menu
     * @return Number corresponding to the action the user wants to perform
     */
    static int displayMainMenu();

    /**
     * @brief Processes the number selected from the main menu
     */
    static void chooseMainMenuOptions();
};

#endif //DA_PROJECT_2_INTERFACE_H

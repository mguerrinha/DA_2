#ifndef DA_PROJECT_2_INTERFACE_H
#define DA_PROJECT_2_INTERFACE_H

#include "TSPManager.h"

class Interface {
public:
    Interface();

    static void run();

private:

    static TSPManager _TSPManager;

    static int displayLoadOptions();
};

#endif //DA_PROJECT_2_INTERFACE_H

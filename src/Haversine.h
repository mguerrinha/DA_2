#ifndef DA_PROJECT_2_HAVERSINE_H
#define DA_PROJECT_2_HAVERSINE_H

#include <cmath>
#include "Coordinate.h"

/**
 * @brief Class representing the Haversine formula
 */

class Haversine {
public:

    /**
     * @brief Function that converts a value in degrees to radians
     * @param degree degrees to be converted
     * @return Returns the result in radians
     */
    static double toRadians(double degree);

    /**
     * @brief Function that calculates the distance between two points taking into account their coordinates
     * @param coord1 first coordinate
     * @param coord2 second coordinate
     * @return Distance between the two points
     */
    static double calculateDistance(const Coordinate &coord1, const Coordinate &coord2);
};

#endif //DA_PROJECT_2_HAVERSINE_H

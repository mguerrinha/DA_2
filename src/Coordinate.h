#ifndef DA_PROJECT_2_COORDINATE_H
#define DA_PROJECT_2_COORDINATE_H

/**
 * @brief Class that represents the coordinates of a vertex
 */

class Coordinate {
private:
    /// Longitude parameter of a coordinate
    double longitude;

    /// Latitude parameter of a coordinate
    double latitude;

public:
    /**
     * @brief Returns the longitude of a coordinate
     * @return Longitude
     */
    [[nodiscard]] double getLongitude() const;

    /**
     * @brief Returns the latitude of a coordinate
     * @return Latitude
     */
    [[nodiscard]] double getLatitude() const;

    /**
     * @brief Constructor of the Coordinate class
     * @param auxLongitude Longitude parameter of a coordinate
     * @param auxLatitude Latitude parameter of a coordinate
     */
    Coordinate (double auxLongitude, double auxLatitude) : longitude(auxLongitude), latitude(auxLatitude) {};
};

#endif //DA_PROJECT_2_COORDINATE_H

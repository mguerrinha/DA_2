#ifndef DA_PROJECT_2_COORDINATE_H
#define DA_PROJECT_2_COORDINATE_H

class Coordinate {
private:
    double longitude;

    double latitude;

public:
    [[nodiscard]] double getLongitude() const;

    [[nodiscard]] double getLatitude() const;

    Coordinate (double auxLongitude, double auxLatitude) : longitude(auxLongitude), latitude(auxLatitude) {};
};

#endif //DA_PROJECT_2_COORDINATE_H

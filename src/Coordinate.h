#ifndef DA_PROJECT_2_COORDINATE_H
#define DA_PROJECT_2_COORDINATE_H

class Coordinate {
private:
    double latitude;

    double longitude;

public:
    [[nodiscard]] double getLatitude() const;

    [[nodiscard]] double getLongitude() const;

    Coordinate (double auxLatitude, double auxLongitude) : latitude(auxLatitude), longitude(auxLongitude) {};
};

#endif //DA_PROJECT_2_COORDINATE_H

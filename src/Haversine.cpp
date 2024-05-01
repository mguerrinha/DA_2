#include "Haversine.h"

double Haversine::toRadians(double degree) {
    return degree * (M_PI / 180.0);
}

double Haversine::calculateDistance(const Haversine::Coordinates &coord1, const Haversine::Coordinates &coord2) {
    double lat1 = toRadians(coord1.latitude);
    double lon1 = toRadians(coord1.longitude);
    double lat2 = toRadians(coord2.latitude);
    double lon2 = toRadians(coord2.longitude);

    double dlat = lat2 - lat1;
    double dlon = lon2 - lon1;
    double a = sin(dlat / 2.0) * sin(dlat / 2.0) + cos(lat1) * cos(lat2) * sin(dlon / 2.0) * sin(dlon / 2.0);
    double c = 2.0 * atan2(sqrt(a), sqrt(1.0 - a));
    double distance = 6371.0 * c;

    return distance;
}


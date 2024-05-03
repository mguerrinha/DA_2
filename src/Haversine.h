#ifndef DA_PROJECT_2_HAVERSINE_H
#define DA_PROJECT_2_HAVERSINE_H

#include <cmath>
#include "Coordinate.h"

/**
 * @brief Classe que representa a fórmula de Haversine
 */

class Haversine {
public:

    /**
     * @brief Função que converte um valor em graus para radianos
     * @param degree
     * @return Retorna o resultado em radianos
     */
    static double toRadians(double degree);

    /**
     * @brief Função que calcula a distância entre dois pontos tendo em conta as respetivas coordenadas
     * @param coord1
     * @param coord2
     * @return Distância entre os dois pontos
     */
    static double calculateDistance(const Coordinate &coord1, const Coordinate &coord2);
};

#endif //DA_PROJECT_2_HAVERSINE_H

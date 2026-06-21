#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "../estructuras/Grafo.h"
#include <vector>

class Dijkstra {
public:
    static void calcular(Grafo& grafo, int origen);
    static void calcular(
        Grafo& grafo,
        int origen,
        std::vector<int>& distancia,
        std::vector<int>& padre
    );
};

#endif
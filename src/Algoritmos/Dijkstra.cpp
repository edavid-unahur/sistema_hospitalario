#include "Dijkstra.h"
#include <iostream>

using namespace std;

void Dijkstra::calcular(
    Grafo& grafo,
    int origen
) {
    int V = grafo.getCantidadVertices();

    int* distancia = new int[V];
    bool* visitado = new bool[V];

    // Inicialización
    for(int i = 0; i < V; i++) {
        distancia[i] = 999999;
        visitado[i] = false;
    }

    distancia[origen] = 0;

    // Algoritmo
    for(int i = 0; i < V - 1; i++) {
        int u = -1;
        int min = 999999;
        // Buscar vértice no visitado con menor distancia
        for(int j = 0; j < V; j++) {
            if(!visitado[j] && distancia[j] < min) {
                min = distancia[j];
                u = j;
            }
        }
        if(u == -1)
            break;
        visitado[u] = true;

        Arista* actual =
            grafo.getListaAdyacencia(u);

        while(actual != nullptr) {
            int v = actual->destino;
            int peso = actual->peso;
            if(!visitado[v] &&
               distancia[u] + peso < distancia[v]) {
                distancia[v] = distancia[u] + peso;
            }
            actual = actual->sig;
        }
    }

    cout << "\nDistancias desde hospital "
         << origen << ":\n";

    for(int i = 0; i < V; i++) {
        cout << "Hospital "
             << i
             << " -> "
             << distancia[i]
             << endl;
    }

    delete[] distancia;
    delete[] visitado;
}
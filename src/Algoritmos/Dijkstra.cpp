#include "Dijkstra.h"
#include <iostream>
#include <climits>

using namespace std;


void Dijkstra::calcular(Grafo& grafo, int origen) {
    int V = grafo.getCantidadVertices();
    vector<int> distancia;
    vector<int> padre;

    calcular(grafo, origen, distancia, padre);

    cout << "\nDistancias desde hospital "
         << origen << ":\n";

    for (int i = 0; i < V; i++) {
        cout << "Hospital "
             << i
             << " -> "
             << distancia[i]
             << endl;
    }
}








    

void Dijkstra::calcular(Grafo& grafo, int origen, 
    vector<int>& distancia, vector<int>& padre) {
    int V = grafo.getCantidadVertices();

    distancia.assign(V, INT_MAX);
    padre.assign(V, -1);
    vector<bool> visitado(V, false);

    distancia[origen] = 0;

    for (int i = 0; i < V - 1; i++) {
        int u = -1;
        int minDist = INT_MAX;

        for (int j = 0; j < V; j++) {
            if (!visitado[j] && distancia[j] < minDist) {
                minDist = distancia[j];
                u = j;
            }
        }

        if (u == -1) break;
        visitado[u] = true;

        Arista* actual = grafo.getListaAdyacencia(u);
        while (actual != nullptr) {
            int v = actual->destino;
            int peso = actual->peso;

            if (!visitado[v] && distancia[u] != INT_MAX &&
                distancia[u] + peso < distancia[v]) {
                distancia[v] = distancia[u] + peso;
                padre[v] = u;
            }
            actual = actual->sig;
        }
    }
}


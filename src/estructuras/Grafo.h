#ifndef GRAFO_H
#define GRAFO_H

#include "Arista.h"
#include "NodoGrafo.h"

class Grafo {
private:
    int V;
    NodoGrafo** nodos;
    Arista** listaAdy;

public:
    Grafo(int V);
    ~Grafo(); 
     void agregarNodo(
        int indice,
        int codigoHospital
    );
    NodoGrafo* getNodo(int indice);
    void agregarArista(int origen, int destino, int peso);
    void mostrar();
    int getCantidadVertices();
    Arista* getListaAdyacencia(
        int vertice
    );
};

#endif
#include "Grafo.h"
#include <iostream>

using namespace std;

Grafo::Grafo(int cantidadVertices) {
    V = cantidadVertices;

    nodos = new NodoGrafo*[V];
    listaAdy = new Arista*[V];

    for(int i = 0; i < V; i++) {
        nodos[i] = nullptr;
        listaAdy[i] = nullptr;
    }
}


void Grafo::agregarNodo(
    int indice,
    int codigoHospital
) {
    if (indice < 0 || indice >= V) {
        return;
    }
    nodos[indice] =
        new NodoGrafo(
            indice,
            codigoHospital
        );
}


void Grafo::agregarArista(int origen, int destino, int peso) {
    if (origen < 0 || origen >= V || destino < 0 || destino >= V) {
        return;
    }
    Arista* nueva = new Arista(destino, peso);
    nueva->sig = listaAdy[origen];
    listaAdy[origen] = nueva;
}

NodoGrafo* Grafo::getNodo(
    int indice
) {
    if(indice < 0 || indice >= V) {
        return nullptr;
    }

    return nodos[indice];
}

void Grafo::mostrar() {
    for (int i = 0; i < V; i++) {
        cout << "Hospital " << i << ": ";
        Arista* aux = listaAdy[i];

        while (aux != nullptr) {
            cout << "(" << aux->destino << ", " << aux->peso << ") ";
            aux = aux->sig;
        }
        cout << endl;
    }
}

int Grafo::getCantidadVertices() {
    return V;
}

Arista* Grafo::getListaAdyacencia(int vertice) {
    if (vertice < 0 || vertice >= V) {
        return nullptr;
    }
    return listaAdy[vertice];
}


Grafo::~Grafo() {
    for (int i = 0; i < V; i++) {
        Arista* actual = listaAdy[i];

        while (actual != nullptr) {
            Arista* temp = actual;
            actual = actual->sig;
            delete temp;
        }
    }
    for (int i = 0; i < V; i++) {
        delete nodos[i];
    }

    delete[] listaAdy;
    delete[] nodos;
}


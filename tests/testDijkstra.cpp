#include "Grafo.h"
#include "Dijkstra.h"

int main() {

    Grafo g(5);

    g.agregarNodo(0,1001);
    g.agregarNodo(1,1002);
    g.agregarNodo(2,1003);
    g.agregarNodo(3,1004);
    g.agregarNodo(4,1005);

    g.agregarArista(0,1,10);
    g.agregarArista(0,2,3);
    g.agregarArista(2,1,4);
    g.agregarArista(1,3,2);
    g.agregarArista(2,4,2);
    g.agregarArista(4,3,3);

    Dijkstra::calcular(g,0);

    return 0;
}
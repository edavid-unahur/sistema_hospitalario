#include "Grafo.h"

int main() {

    Grafo g(4);

    g.agregarNodo(0,1001);
    g.agregarNodo(1,1002);
    g.agregarNodo(2,1003);
    g.agregarNodo(3,1004);

    g.agregarArista(0,1,10);
    g.agregarArista(0,2,15);
    g.agregarArista(1,3,20);
    g.agregarArista(2,3,5);

    g.mostrar();

    return 0;
}
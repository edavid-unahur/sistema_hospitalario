#ifndef ARISTA_H
#define ARISTA_H

class Arista {
public:
    int destino;
    int peso;
    Arista* sig;

    Arista(int d, int p) {
        destino = d;
        peso = p;
        sig = nullptr;
    }
};

#endif
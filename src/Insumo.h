#ifndef INSUMO_H
#define INSUMO_H

#include <string>
#include <vector>

struct Insumo {
    std::string nombre;
    int peso; // unidad: kg (entero para simplicidad)
    int valor; // utilidad/prioridad

    Insumo() = default;
    Insumo(const std::string &n, int p, int v): nombre(n), peso(p), valor(v) {}
};

#endif // INSUMO_H

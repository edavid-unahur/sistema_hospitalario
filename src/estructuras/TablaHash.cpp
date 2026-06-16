#include "TablaHash.h"
#include <iostream>
#include <stdexcept>

TablaHash::TablaHash(int capacidadInicial)
    : tabla(capacidadInicial)
    , capacidad(capacidadInicial)
    , cantidad(0)
    , factorCargaMax(0.8f)
{}

TablaHash::~TablaHash() {
    for (auto& entrada : tabla)
        if (entrada.ocupado)
            delete entrada.hospital;
}

// ── Función hash ───────────────────────────────────────────
// Trata cada carácter como su valor ASCII
// base 31 (primo) da buena distribución para strings cortos
int TablaHash::hash(const std::string& clave) const {
    int resultado = 0;
    for (const char c : clave)
        resultado = resultado * 31 + static_cast<int>(c);

    if (resultado < 0) resultado = -resultado;

    return resultado % capacidad;
}

// ── Rehash ─────────────────────────────────────────────────
// Se activa cuando factorCarga > 0.8
// Duplica capacidad al siguiente número primo aprox
void TablaHash::rehash() {
    int nuevaCapacidad = capacidad * 2 + 1;  // impar, probablemente primo
    std::vector<Entrada> nuevaTabla(nuevaCapacidad);

    int capacidadAnterior = capacidad;
    capacidad = nuevaCapacidad;

    // reinsertar todos los elementos válidos
    for (int i = 0; i < capacidadAnterior; i++) {
        if (tabla[i].ocupado && !tabla[i].eliminado) {
            int pos = hash(tabla[i].clave);
            int intento = 0;
            while (nuevaTabla[(pos + intento) % capacidad].ocupado)
                intento++;
            int posFinal = (pos + intento) % capacidad;
            nuevaTabla[posFinal].clave    = tabla[i].clave;
            nuevaTabla[posFinal].hospital = tabla[i].hospital;
            nuevaTabla[posFinal].ocupado  = true;
        }
    }

    tabla = std::move(nuevaTabla);
}

// ── Insertar ───────────────────────────────────────────────
void TablaHash::insertar(Hospital* h) {
    if (!h) return;

    if (factorCarga() >= factorCargaMax) rehash();

    std::string clave = h->getCodigoHospital();
    int pos = hash(clave);
    int intento = 0;

    while (intento < capacidad) {
        int idx = (pos + intento) % capacidad;

        // celda libre o marcada como eliminada → insertar acá
        if (!tabla[idx].ocupado || tabla[idx].eliminado) {
            tabla[idx].clave     = clave;
            tabla[idx].hospital  = h;
            tabla[idx].ocupado   = true;
            tabla[idx].eliminado = false;
            cantidad++;
            return;
        }

        // clave duplicada — no insertar
        if (tabla[idx].clave == clave) {
            std::cout << "Hospital " << clave << " ya existe.\n";
            return;
        }

        intento++;
    }

}

// ── Buscar ─────────────────────────────────────────────────
Hospital* TablaHash::buscar(const std::string& codigo) const {
    int pos     = hash(codigo);
    int intento = 0;

    while (intento < capacidad) {
        int idx = (pos + intento) % capacidad;

        if (!tabla[idx].ocupado && !tabla[idx].eliminado)
            return nullptr;   

        if (tabla[idx].ocupado &&
            !tabla[idx].eliminado &&
            tabla[idx].clave == codigo)
            return tabla[idx].hospital;

        intento++;
    }
    return nullptr;
}

// ── Eliminar ───────────────────────────────────────────────
// Usa "tombstone" (eliminado=true) para no romper las cadenas de sondeo
bool TablaHash::eliminar(const std::string& codigo) {
    int pos     = hash(codigo);
    int intento = 0;

    while (intento < capacidad) {
        int idx = (pos + intento) % capacidad;

        if (!tabla[idx].ocupado && !tabla[idx].eliminado)
            return false;   // no encontrado

        if (tabla[idx].ocupado &&
            !tabla[idx].eliminado &&
            tabla[idx].clave == codigo) {
            delete tabla[idx].hospital;
            tabla[idx].hospital  = nullptr;
            tabla[idx].eliminado = true;   // tombstone
            tabla[idx].ocupado   = false;
            cantidad--;
            return true;
        }

        intento++;
    }
    return false;
}

// ── Factor de carga ────────────────────────────────────────
float TablaHash::factorCarga() const {
    return static_cast<float>(cantidad) / static_cast<float>(capacidad);
}

// ── Obtener todos ──────────────────────────────────────────
// Lo usás para listar u ordenar hospitales
std::vector<Hospital*> TablaHash::obtenerTodos() const {
    std::vector<Hospital*> resultado;
    for (const auto& entrada : tabla)
        if (entrada.ocupado && !entrada.eliminado)
            resultado.push_back(entrada.hospital);
    return resultado;
}
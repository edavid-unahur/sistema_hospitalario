#pragma once
#include <vector>
#include <string>
#include "../Hospital.h"

class TablaHash {
private:
    struct Entrada {
        std::string  clave;
        Hospital*    hospital;
        bool         ocupado;    
        bool         eliminado;  

        Entrada() : hospital(nullptr), ocupado(false), eliminado(false) {}
    };

    std::vector<Entrada> tabla;
    int                  capacidad;
    int                  cantidad;
    float                factorCargaMax;  

    int  hash(const std::string& clave)   const;
    void rehash();

public:
    TablaHash(int capacidadInicial = 11); 
    ~TablaHash();

    void      insertar(Hospital* h);
    Hospital* buscar(const std::string& codigo)   const;
    bool      eliminar(const std::string& codigo);
    float     factorCarga()                        const;
    
    std::vector<Hospital*> obtenerTodos() const;
};
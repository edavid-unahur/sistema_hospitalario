#pragma once
#include <string>

class Especialidad {
private:
    std::string codigo;   
    std::string nombre;   

public:
    Especialidad(const std::string& codigo,
                 const std::string& nombre);

    std::string getCodigo() const;
    std::string getNombre() const;

    bool operator==(const Especialidad& otra) const;
};
#include "Especialidad.h"

Especialidad::Especialidad(const std::string& codigo,
    const std::string& nombre) {
    this->codigo = codigo;
    this->nombre = nombre;
}

std::string Especialidad::getCodigo() const {return codigo;}

std::string Especialidad::getNombre() const {return nombre;}

bool Especialidad::operator==(const Especialidad& otra) const {
    return codigo == otra.codigo;
}
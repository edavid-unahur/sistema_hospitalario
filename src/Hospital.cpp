#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "Especialidad.h"
#include "Ciudad.h"
#include "Hospital.h"


Hospital::Hospital( const std::string& codigoHospital,
                    const std::string& nombre,
                    int                capacidadCamas,
                    float              presupuestoAnual,
                    int                personalMedico,
                    Ciudad*            ciudad)
    : codigoHospital(codigoHospital)
    , nombre(nombre)
    , capacidadCamas(capacidadCamas)
    , presupuestoAnual(presupuestoAnual)
    , personalMedico(personalMedico)
    , ciudad(ciudad)
{}

std::string Hospital::getCodigoHospital()   const { return codigoHospital; }
std::string Hospital::getNombre()           const { return nombre; }
std::string Hospital::getCiudad()           const { return ciudad->getNombre(); }
int         Hospital::getCapacidadCamas()   const { return capacidadCamas; }
int         Hospital::getPersonalMedico()   const { return personalMedico; }
float       Hospital::getPresupuestoAnual() const { return presupuestoAnual; }

const std::vector<Especialidad*>& Hospital::getEspecialidades() const {
    return especialidades;
}

bool Hospital::tieneEspecialidad(const std::string& esp) const {
    for (const auto& e : especialidades) {
        if (e != nullptr && e->getCodigo() == esp) return true;
    }
    return false;
}

void Hospital::mostrarInformacion() const {
    std::cout << "Código:      " << codigoHospital << "\n"
              << "Nombre:      " << nombre << "\n"           
              << "Ciudad:      " << ciudad->getNombre() << "\n"
              << "Camas:       " << capacidadCamas << "\n"
              << "Personal:    " << personalMedico << "\n"
              << "Presupuesto: $" << presupuestoAnual << "\n"
              << "Especialidades: ";
    
    // CORRECCIÓN ACÁ: Accedemos al método del objeto apuntado
    for (const auto& e : especialidades) {
        if (e != nullptr) {
            std::cout << e->getNombre() << " "; 
            
        }
    }
    std::cout << "\n----------------------------------------\n";
}

void Hospital::agregarEspecialidad(Especialidad* e) {
    this->especialidades.push_back(e);
}

// parsea "Pediatria,Cardiologia" → vector de strings
static std::vector<std::string> parsearEspecialidades(const std::string& s) {
    std::vector<std::string> resultado;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, ',')) resultado.push_back(item);
    return resultado;
}

bool Hospital::tieneCamasDisponibles()const{
    return (capacidadCamas > 0);
}

void Hospital::liberarCama() {
    capacidadCamas++;
}

void Hospital::ocuparCama() {
    if (capacidadCamas > 0) capacidadCamas--;
}   
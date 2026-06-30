#include "Hospital.h"

Hospital::Hospital() {}

Hospital::Hospital(
    const std::string& codigoHospital,
    const std::string& nombre,
    const std::string& ciudad,
    int capacidadCamas,
    const std::vector<std::string>& especialidades,
    int personalMedico,
    int presupuestoAnual)
    : codigoHospital(codigoHospital)
    , nombre(nombre)
    , ciudad(ciudad)
    , capacidadCamas(capacidadCamas)
    , especialidades(especialidades)
    , personalMedico(personalMedico)
    , presupuestoAnual(presupuestoAnual)
    , camasDisponibles(capacidadCamas)
{}

std::string Hospital::getCodigoHospital()  const { return codigoHospital; }
std::string Hospital::getNombre()          const { return nombre; }
std::string Hospital::getCiudad()          const { return ciudad; }
int         Hospital::getCapacidadCamas()  const { return capacidadCamas; }
int         Hospital::getPersonalMedico()  const { return personalMedico; }
int         Hospital::getPresupuestoAnual()const { return presupuestoAnual; }

const std::vector<std::string>& Hospital::getEspecialidades() const {
    return especialidades;
}

void Hospital::agregarEspecialidad(const std::string& esp) {
    especialidades.push_back(esp);
}

bool Hospital::tieneEspecialidad(const std::string& esp) const {
    for (const auto& e : especialidades)
        if (e == esp) return true;
    return false;
}

void Hospital::mostrarInformacion() const {
    std::cout << "Codigo:      " << codigoHospital << "\n"
              << "Nombre:      " << nombre << "\n"
              << "Ciudad:      " << ciudad << "\n"
              << "Camas:       " << capacidadCamas << "\n"
              << "Personal:    " << personalMedico << "\n"
              << "Presupuesto: $" << presupuestoAnual << "\n"
              << "Especialidades: ";
    for (const auto& e : especialidades)
        std::cout << e << " ";
    std::cout << "\n----------------------------------------\n";
}

bool Hospital::tieneCamasDisponibles() const {
    return camasDisponibles > 0;
}

void Hospital::ocuparCama() {
    if (camasDisponibles > 0) camasDisponibles--;
}

void Hospital::liberarCama() {
    camasDisponibles++;
}

float Hospital::getPorcentajeOcupacion() const {
    int camasOcupadas = capacidadCamas - camasDisponibles;
    return (float)camasOcupadas * 100 / capacidadCamas;
}

bool Hospital::tieneSobrecarga() const {
    return getPorcentajeOcupacion() > 90.0;
}
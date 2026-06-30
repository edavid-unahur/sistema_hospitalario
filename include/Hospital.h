#pragma once
#include <iostream>
#include <string>
#include <vector>

class Hospital {
private:
    std::string codigoHospital;
    std::string nombre;
    std::string ciudad;
    int capacidadCamas;
    std::vector<std::string> especialidades;
    int personalMedico;
    int presupuestoAnual;
    int camasDisponibles;

public:
    Hospital();
    Hospital(
        const std::string& codigoHospital, 
        const std::string& nombre,
        const std::string& ciudad,
        int capacidadCamas,
        const std::vector<std::string>& especialidades,
        int personalMedico,
        int presupuestoAnual
    );

    std::string getCodigoHospital() const;
    std::string getNombre() const;
    std::string getCiudad() const;
    int getCapacidadCamas() const;
    int getPersonalMedico() const;
    int getPresupuestoAnual() const;
    const std::vector<std::string>& getEspecialidades() const;

    void mostrarInformacion() const;
    void agregarEspecialidad(const std::string& esp);
    bool tieneEspecialidad(const std::string& esp) const;
    bool tieneCamasDisponibles() const;
    void ocuparCama();
    void liberarCama();
    float getPorcentajeOcupacion() const;
    bool tieneSobrecarga() const;
};
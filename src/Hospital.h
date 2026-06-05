#pragma once
#include <iostream>
#include <string>
#include <vector>


class Ciudad;
class Especialidad;

class Hospital {
    private:
        std::string codigoHospital;
        std::string nombre;
        int capacidadCamas;
        float presupuestoAnual;
        int personalMedico;
        Ciudad* ciudad;
        std::vector<Especialidad*> especialidades;

    public:
        Hospital();

        Hospital(
            const std::string& codigoHospital, 
            const std::string& nombre, 
            int capacidadCamas, 
            float presupuestoAnual, 
            int personalMedico,
            Ciudad* ciudad
        );
        //Metodos gettes
        std::string getCodigoHospital() const;
        std::string getNombre() const;
        int getCapacidadCamas() const;
        float getPresupuestoAnual() const;
        std::string getCiudad() const;
        int getPersonalMedico() const;
        const std::vector<Especialidad*>& getEspecialidades() const;
        
        //Metodos de logica
        void mostrarInformacion() const;
        void agregarEspecialidad(Especialidad* e);
        bool tieneEspecialidad(const std::string& cod) const;
        bool tieneCamasDisponibles()const;
        void ocuparCama();
        void liberarCama();


};
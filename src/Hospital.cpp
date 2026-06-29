    #include <iostream>
    #include <vector>
    #include <string>
    #include "Especialidad.h"
    #include "Hospital.h"


    Hospital::Hospital( const std::string& codigoHospital,
                        const std::string& nombre,
                        int                capacidadCamas,
                        float              presupuestoAnual,
                        int                personalMedico,
                        const std::string& ciudad)
        : codigoHospital(codigoHospital)
        , nombre(nombre)
        , capacidadCamas(capacidadCamas)
        , presupuestoAnual(presupuestoAnual)
        , personalMedico(personalMedico)
        , ciudad(ciudad)
        , camasDisponibles(10)
    {}

    Hospital::Hospital() {
    }

    std::string Hospital::getCodigoHospital()   const { return codigoHospital; }
    std::string Hospital::getNombre()           const { return nombre; }
    std::string Hospital::getCiudad()           const { return ciudad; }
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
        std::cout << "Codigo:      " << codigoHospital << "\n"
                << "Nombre:      " << nombre << "\n"
                << "Ciudad:      " << ciudad << "\n"
                << "Camas:       " << capacidadCamas << "\n"
                << "Personal:    " << personalMedico << "\n"
                << "Presupuesto: $" << static_cast<long long>(presupuestoAnual) << "\n"
                << "Especialidades: ";

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

    bool Hospital::tieneCamasDisponibles()const{
        return (camasDisponibles > 0);
    }

    void Hospital::liberarCama() {
        camasDisponibles++;
    }

    void Hospital::ocuparCama() {
        if (camasDisponibles > 0) camasDisponibles--;
    }  
    
    float Hospital::getPorcentajeOcupacion() const {

        int camasOcupadas = capacidadCamas - camasDisponibles;
        float porcentaje = (float)camasOcupadas * 100 / capacidadCamas;

        return porcentaje;
    }

    bool Hospital::tieneSobrecarga() const {
        return getPorcentajeOcupacion() > 90.0;

    }
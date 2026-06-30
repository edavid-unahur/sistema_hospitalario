#pragma once

#include <string>
#include <vector>
#include "Hospital.h"
#include "estructuras/TablaHash.h"
#include "estructuras/Grafo.h"
#include "Diagnostico.h"
#include "ambulancia.h"


class SistemaHospitalario {
private:
    TablaHash* tablahospitales;
    Grafo* grafoDerivaciones;
    int cantidadHospitales;
    
    // Mapeo entre código de hospital e índice en el grafo
    std::vector<std::pair<std::string, int>> mapaCodigos;
    std::vector<Insumo> listaInsumos;

    DiagnosticoAVL arbolDiagnosticos;
    
public:
    SistemaHospitalario(int capacidadInicial = 11);
    ~SistemaHospitalario();
    bool mostrarHospital(const std::string& codigoHospital);
    void agregarHospital(
        const std::string& codigo,
        const std::string& nombre,
        const std::string& ciudad,
        int capacidadCamas,
        const std::vector<std::string>& especialidades,
        int personalMedico,
        int presupuestoAnual
    );
    bool eliminarHospital(const std::string& codigoHospital);
    std::string obtenerHospitalMasCercano(const std::string& codigoHospital);
    void listarPorCapacidad(bool descendente = true);
    void listarPorPersonalMedico(bool descendente = true);
    void listarPorPresupuesto(bool descendente = true);
    void buscarPorEspecialidad(const std::string& codigoEspecialidad);
    std::vector<std::string> calcularRutaOptima(
        const std::string& codigoOrigen,
        const std::string& codigoDestino
    );
    void agregarDerivacion(
        const std::string& codigoOrigen,
        const std::string& codigoDestino,
        int tiempoMinutos
    );
    std::vector<Hospital*> obtenerTodosHospitales() const;
    std::vector<Hospital*> obtenerHospitalesOrdenadosPorCapacidad(bool descendente = true) const;
    std::vector<Hospital*> obtenerHospitalesOrdenadosPorPersonal(bool descendente = true) const;
    std::vector<Hospital*> obtenerHospitalesOrdenadosPorPresupuesto(bool descendente = true) const;
    std::vector<Hospital*> obtenerHospitalesPorEspecialidad(const std::string& codigoEspecialidad) const;
    void agregarEspecialidadAHospital(const std::string& codigoHospital,
                                   const std::string& especialidad);


    void registrarDiagnostico(const std::string& codigo);
    void eliminarDiagnostico(const std::string& codigo); // ◄ ESTA ES LA QUE FALTA
    void listarDiagnosticos();
    void mostrarDiagnosticoMasFrecuente();
    void mostrarEstadisticasArbol();

    int getCantidadHospitales() const;
    float getFactorCargaTabla() const;
    void listarTodos();

    void cargarInsumosPorDefecto();
    void ejecutarBacktrackingPuro(int capacidad);
    void ejecutarBranchAndBound(int capacidad);
    void compararAlgoritmos(int capacidad);

    std::vector<Hospital> getHospitalesSobrecargados();
    void cargarHospitales(const std::string& ruta);
    void cargarDerivaciones(const std::string& ruta);
};

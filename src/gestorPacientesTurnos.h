#ifndef GESTORPACIENTESTURNOS_H
#define GESTORPACIENTESTURNOS_H
#include <iostream>
using namespace std;
#include <vector>
#include "Paciente.h"
#include "Turno.h"

class GestorPacientesTurnos {
private:
    vector<Paciente> pacientes;
    vector<Turno> turnos;
    vector<Paciente> pacientesPorDni;
    vector<Turno> turnosPorMedicoId;
    vector<Turno> turnosPorPacienteId;
    vector<Turno> turnosPorFecha;

    bool turnosPorFechaOrdenados = false;
    bool turnosPorMedicoOrdenados = false;
    bool pacientesPorDniOrdenados = false;
    bool turnosPorPacienteIdOrdenados = false;

public:
    GestorPacientesTurnos();

    void cargarPacientes(string nombreArchivo);
    void cargarTurnos(string nombreArchivo);

    //Punto 3
    vector<Turno> getTurnosPorDni(int dni);
    int buscarPrimerTurnoDNI(int dni);
    void inicializarTurnosPorPacienteId();
    int getPacienteIdPorDni(int dni);
    void inicializarPacientesPorDni();

    //Punto 4
    vector<Turno> getTurnosEnRangoDeFecha(int fechaInicio, int fechaFin, string hospitalId);
    int buscarPrimerTurnoDentroDeRango(int fechaInicio, int fechaFin);
    void inicializarTurnosPorFecha();

    //Punto 5
    vector<Turno> getTurnosPorMedicoId(int medicoId);
    int buscarPrimerTurnoMedico(int medicoId);
    void inicializarTurnosPorMedico();

    // Métodos de ordenamiento Turnos
    vector<Turno> mergeSortTurnosPorMedicoId(vector<Turno>& turnos);
    vector<Turno> mergeTurnosPorMedicoId(vector<Turno>& izquierda, vector<Turno>& derecha);
    vector<Turno> mergeSortTurnosPorFecha(vector<Turno>& turnos);
    vector<Turno> mergeTurnosPorFecha(vector<Turno>& izquierda, vector<Turno>& derecha);
    vector<Turno> mergeSortTurnosPorPacienteId(vector<Turno>& turnos);
    vector<Turno> mergeTurnosPorPacienteId(vector<Turno>& izquierda, vector<Turno>& derecha);

    // Métodos de ordenamiento Pacientes
    vector<Paciente> mergeSortPacientesPorDni(vector<Paciente>& pacientes);
    vector<Paciente> mergePacientesPorDni(vector<Paciente>& izquierda, vector<Paciente>& derecha);
};

#endif
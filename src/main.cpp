#include <iostream>
#include <string>
using namespace std;
#include "Paciente.h"
#include "Turno.h"
#include "gestorPacientesTurnos.h"

int main() {

    GestorPacientesTurnos gestor;

    gestor.cargarPacientes("pacientes.txt");
    gestor.cargarTurnos("turnos.txt");
    for (Turno turno : gestor.getTurnosEnRangoDeFecha(20250610, 20250620, "HIT")) {
        cout << "Paciente ID: " << turno.getPacienteId() << ", Fecha: " << turno.getFechaTurno() << endl;
    }

    return 0;
}
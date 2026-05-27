#include <iostream>
using namespace std;
#include <string>
#include <vector>
#include "Paciente.h"
#include "Turno.h"

class GestorPacientesTurnos {
private:
    vector<Paciente> pacientes;
    vector<Turno> turnos;

public:
    void cargarPacientes();
    void cargarTurnos();
};
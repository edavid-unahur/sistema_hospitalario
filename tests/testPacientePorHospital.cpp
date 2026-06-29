#include <iostream>
#include <vector>
#include "GestorPacientesTurnos.h"
using namespace std;

int main() {

    GestorPacientesTurnos gestor;

    gestor.cargarPacientes("pacientes.txt");

    vector<pair<string,int>> resultado =
        gestor.getCantPacientesAtendidosPorHospital( 20250101, 20251231 );

    cout << "Pacientes atendidos por hospital:" << endl;

    for (pair<string,int> dato : resultado) {

        cout << dato.first
             << " -> "
             << dato.second
             << " pacientes"
             << endl;
    }

    return 0;
}
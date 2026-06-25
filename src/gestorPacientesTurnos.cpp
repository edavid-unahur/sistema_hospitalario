#include<ios>
#include<fstream>
using namespace std;
#include "gestorPacientesTurnos.h"
#include "Paciente.h"
#include "Turno.h"

GestorPacientesTurnos::GestorPacientesTurnos() {

}

void GestorPacientesTurnos::cargarPacientes(string nombreArchivo) {
    string codigoHosp;
    int pacId;
    int DNI;
    int fechaIn;
    string diag;
    int prio;
    float peso;
    ifstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo: " << nombreArchivo << endl;
        return;
    }

    while (archivo >> codigoHosp >> pacId >> DNI >> fechaIn >> diag >> prio >> peso){
        
        Paciente paciente( codigoHosp, pacId, DNI, fechaIn, diag, prio, peso);
        
        pacientes.push_back(paciente);
    }

    cout << "Pacientes cargados: " << pacientes.size() << endl;

    archivo.close();
}

void GestorPacientesTurnos::cargarTurnos(string nombreArchivo) {
    string codigoHosp; 
    int turId; 
    int pacId; 
    int medId; 
    int fechaTur; 
    string espec; 
    int duracion; 
    ifstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo: " << nombreArchivo << endl;
        return;
    }

    while (archivo >> codigoHosp >> turId >> pacId >> medId >> fechaTur >> espec >> duracion) {

        Turno turno(codigoHosp, turId, pacId, medId, fechaTur, espec, duracion);
        
        turnos.push_back(turno);
    }
    archivo.close();
}


// 1

// recorre pacientes en lugar de turnos contemplando emergencias, pacientes que no se presentaron a su turno, etc.
// preguntar si se puede repetir la persona, si no agregar filtro


vector<pair<string,int>> GestorPacientesTurnos::getCantPacientesAtendidosPorHospital(int fechaInicio, int fechaFin) {
    int pos = buscarPrimerPacienteDentroDeRango(fechaInicio, fechaFin);
    vector<pair<string,int>> resultado;

    if (pos == -1) {
        return resultado;
    }

    while (
        pos < (int)pacientesPorFechaIngreso.size() &&
        pacientesPorFechaIngreso[pos].getFechaIngreso() <= fechaFin
    ) {

        string hospital = pacientesPorFechaIngreso[pos].getCodigoHospital();
        bool encontrado = false;

        for ( size_t i = 0; i < resultado.size(); i++){
            if (resultado[i].first == hospital) {
                resultado[i].second++;
                encontrado = true;
                break;
            }
        }

        if (!encontrado) {
            resultado.push_back(make_pair(hospital, 1));
        }

        pos++; 

    }

    return resultado;
}

int GestorPacientesTurnos::buscarPrimerPacienteDentroDeRango(int fechaInicio, int fechaFin) {
    inicializarPacientesPorFechaIngreso();

    int izq = 0;
    int der = pacientesPorFechaIngreso.size() - 1;

    int resultado = -1;

    while (izq <= der) {

        int medio = (izq + der) / 2;

        if (pacientesPorFechaIngreso[medio].getFechaIngreso() >= fechaInicio) {

            if (pacientesPorFechaIngreso[medio].getFechaIngreso() <= fechaFin) {
                resultado = medio;
            }

            der = medio - 1;
        }
        else {

            izq = medio + 1;
        }
    }

    return resultado;
}

void GestorPacientesTurnos::inicializarPacientesPorFechaIngreso() {

    if (pacientesPorFechaIngresoOrdenados) {
        return;
    }

    pacientesPorFechaIngreso = pacientes;

    pacientesPorFechaIngreso = mergeSortPacientesPorFechaIngreso(pacientesPorFechaIngreso);

    pacientesPorFechaIngresoOrdenados = true;
}

//2

//3

vector<Turno> GestorPacientesTurnos::getTurnosPorDni(int dni) {
    vector<Turno> turnosPaciente;

    int pos = buscarPrimerTurnoDNI(dni);

    if (pos == -1) {
        return turnosPaciente;
    }

    while (
        pos < (int)turnosPorPacienteId.size() &&
        turnosPorPacienteId[pos].getPacienteId() == getPacienteIdPorDni(dni)
    ) {

        turnosPaciente.push_back(
            turnosPorPacienteId[pos]
        );

        pos++;
    }

    return turnosPaciente;
}

int GestorPacientesTurnos::buscarPrimerTurnoDNI(int dni) {
    inicializarTurnosPorPacienteId();

    int pacienteId = getPacienteIdPorDni(dni); 
    int izq = 0;
    int der = turnosPorPacienteId.size() - 1;

    int resultado = -1;

    while (izq <= der) {

        int medio = (izq + der) / 2;

        if (turnosPorPacienteId[medio].getPacienteId() >= pacienteId) {

            if (turnosPorPacienteId[medio].getPacienteId() == pacienteId) {
                resultado = medio;
            }

            der = medio - 1;
        }
        else {

            izq = medio + 1;
        }
    }

    return resultado;
}

void GestorPacientesTurnos::inicializarTurnosPorPacienteId() {

    if (turnosPorPacienteIdOrdenados) {
        return;
    }

    turnosPorPacienteId = turnos;

    turnosPorPacienteId = mergeSortTurnosPorPacienteId(turnosPorPacienteId);

    turnosPorPacienteIdOrdenados = true;
}

// Metodo para obtener el ID del paciente a partir del DNI utilizando búsqueda binaria(punto 3)

int GestorPacientesTurnos::getPacienteIdPorDni(int dni) {
    
    inicializarPacientesPorDni();
    int izq = 0;
    int der = pacientesPorDni.size() - 1;

    int resultado = -1;

    while (izq <= der) {

        int medio = (izq + der) / 2;

        if (pacientesPorDni[medio].getDni() >= dni) {

            if (pacientesPorDni[medio].getDni() == dni) {
                resultado = pacientesPorDni[medio].getPacienteId();
            }

            der = medio - 1;
        }
        else {

            izq = medio + 1;
        }
    }
    return resultado;
}

void GestorPacientesTurnos::inicializarPacientesPorDni() {

    if (pacientesPorDniOrdenados) {
        return;
    }

    pacientesPorDni = pacientes;

    pacientesPorDni = mergeSortPacientesPorDni(pacientesPorDni);

    pacientesPorDniOrdenados = true;
}

/* 4. Implementar una cola de prioridad (min-heap) para gestionar la lista de espera de 
pacientes según su nivel de prioridad y fecha de ingreso. 
Deben poder realizarse: 
-operaciones de inserción
-extracción del más prioritario  
-actualización de prioridad. 
Asumo que:
-insercion: insertaa ordenado por prioridad y fecha de ingreso
-extraccion: extrae el primero en la cola y corre el lugar de los siguientes
-actualizacion: buscar paciente por id, actualizar prioridad, reordenar la cola

*/

//5

vector<Turno> GestorPacientesTurnos::getTurnosPorMedicoId(int medicoId) {

    vector<Turno> resultado;

    int pos = buscarPrimerTurnoMedico(medicoId);

    if (pos == -1) {
        return resultado;
    }

    while (
        pos < (int)turnosPorMedicoId.size() &&
        turnosPorMedicoId[pos].getMedicoId() == medicoId
    ) {

        resultado.push_back(
            turnosPorMedicoId[pos]
        );

        pos++;
    }

    return mergeSortTurnosPorFecha(resultado);
}

int GestorPacientesTurnos::buscarPrimerTurnoMedico(int medicoId) {

    inicializarTurnosPorMedico();

    int izq = 0;
    int der = turnosPorMedicoId.size() - 1;

    int resultado = -1;

    while (izq <= der) {

        int medio = (izq + der) / 2;

        if (turnosPorMedicoId[medio].getMedicoId() >= medicoId) {

            if (turnosPorMedicoId[medio].getMedicoId() == medicoId) {
                resultado = medio;
            }

            der = medio - 1;
        }
        else {

            izq = medio + 1;
        }
    }

    return resultado;
}

void  GestorPacientesTurnos::inicializarTurnosPorMedico() {

    if (turnosPorMedicoOrdenados) {
        return;
    }

    turnosPorMedicoId = turnos;

    turnosPorMedicoId = mergeSortTurnosPorMedicoId(turnosPorMedicoId);

    turnosPorMedicoOrdenados = true;
}

//Metodos de ordenamiento de turnos por medicoId, fecha y pacienteId

vector<Turno> GestorPacientesTurnos::mergeSortTurnosPorMedicoId(vector<Turno>& turnos) {

    if (turnos.size() <= 1) {
        return turnos;
    }

    int medio = turnos.size() / 2;
    vector<Turno> izquierda(turnos.begin(), turnos.begin() + medio);
    vector<Turno> derecha(turnos.begin() + medio, turnos.end());

    izquierda = mergeSortTurnosPorMedicoId(izquierda);
    derecha = mergeSortTurnosPorMedicoId(derecha);

    return mergeTurnosPorMedicoId(izquierda, derecha);
}

vector<Turno> GestorPacientesTurnos::mergeTurnosPorMedicoId(vector<Turno>& izquierda, vector<Turno>& derecha) {
    vector<Turno> resultado;
    size_t i = 0, j = 0;

    while (i < izquierda.size() && j < derecha.size()) {
        if (izquierda[i].getMedicoId() < derecha[j].getMedicoId()) {
            resultado.push_back(izquierda[i]);
            i++;
        } else {
            resultado.push_back(derecha[j]);
            j++;
        }
    }

    while (i < izquierda.size()) {
        resultado.push_back(izquierda[i]);
        i++;
    }

    while (j < derecha.size()) {
        resultado.push_back(derecha[j]);
        j++;
    }

    return resultado;
}

vector<Turno> GestorPacientesTurnos::mergeSortTurnosPorFecha(vector<Turno>& turnos) {

    if (turnos.size() <= 1) {
        return turnos;
    }

    int medio = turnos.size() / 2;
    vector<Turno> izquierda(turnos.begin(), turnos.begin() + medio);
    vector<Turno> derecha(turnos.begin() + medio, turnos.end());

    izquierda = mergeSortTurnosPorFecha(izquierda);
    derecha = mergeSortTurnosPorFecha(derecha);

    return mergeTurnosPorFecha(izquierda, derecha);
}

vector<Turno> GestorPacientesTurnos::mergeTurnosPorFecha(vector<Turno>& izquierda, vector<Turno>& derecha) {
    vector<Turno> resultado;
    size_t i = 0, j = 0;

    while (i < izquierda.size() && j < derecha.size()) {
        if (izquierda[i].getFechaTurno() < derecha[j].getFechaTurno()) {
            resultado.push_back(izquierda[i]);
            i++;
        } else {
            resultado.push_back(derecha[j]);
            j++;
        }
    }

    while (i < izquierda.size()) {
        resultado.push_back(izquierda[i]);
        i++;
    }

    while (j < derecha.size()) {
        resultado.push_back(derecha[j]);
        j++;
    }

    return resultado;
}

vector<Turno> GestorPacientesTurnos::mergeSortTurnosPorPacienteId(vector<Turno>& turnos) {

    if (turnos.size() <= 1) {
        return turnos;
    }

    int medio = turnos.size() / 2;
    vector<Turno> izquierda(turnos.begin(), turnos.begin() + medio);
    vector<Turno> derecha(turnos.begin() + medio, turnos.end());

    izquierda = mergeSortTurnosPorPacienteId(izquierda);
    derecha = mergeSortTurnosPorPacienteId(derecha);

    return mergeTurnosPorPacienteId(izquierda, derecha);
}

vector<Turno> GestorPacientesTurnos::mergeTurnosPorPacienteId(vector<Turno>& izquierda, vector<Turno>& derecha) {
    vector<Turno> resultado;
    size_t i = 0, j = 0;

    while (i < izquierda.size() && j < derecha.size()) {
        if (izquierda[i].getPacienteId() < derecha[j].getPacienteId()) {
            resultado.push_back(izquierda[i]);
            i++;
        } else {
            resultado.push_back(derecha[j]);
            j++;
        }
    }

    while (i < izquierda.size()) {
        resultado.push_back(izquierda[i]);
        i++;
    }

    while (j < derecha.size()) {
        resultado.push_back(derecha[j]);
        j++;
    }

    return resultado;
}

// Metodos de ordenamiento de Pacientes por DNI

vector<Paciente> GestorPacientesTurnos::mergeSortPacientesPorDni(vector<Paciente>& pacientes) {

    if (pacientes.size() <= 1) {
        return pacientes;
    }

    int medio = pacientes.size() / 2;
    vector<Paciente> izquierda(pacientes.begin(), pacientes.begin() + medio);
    vector<Paciente> derecha(pacientes.begin() + medio, pacientes.end());

    izquierda = mergeSortPacientesPorDni(izquierda);
    derecha = mergeSortPacientesPorDni(derecha);

    return mergePacientesPorDni(izquierda, derecha);
}

vector<Paciente> GestorPacientesTurnos::mergePacientesPorDni(vector<Paciente>& izquierda, vector<Paciente>& derecha) {

    vector<Paciente> resultado;
    size_t i = 0, j = 0;

    while (i < izquierda.size() && j < derecha.size()) {
        if (izquierda[i].getDni() < derecha[j].getDni()) {
            resultado.push_back(izquierda[i]);
            i++;
        } else {
            resultado.push_back(derecha[j]);
            j++;
        }
    }

    while (i < izquierda.size()) {
        resultado.push_back(izquierda[i]);
        i++;
    }

    while (j < derecha.size()) {
        resultado.push_back(derecha[j]);
        j++;
    }

    return resultado;
}

vector<Paciente> GestorPacientesTurnos::mergeSortPacientesPorFechaIngreso(vector<Paciente>& pacientes) {

    if (pacientes.size() <= 1) {
        return pacientes;
    }

    int medio = pacientes.size() / 2;
    vector<Paciente> izquierda(pacientes.begin(), pacientes.begin() + medio);
    vector<Paciente> derecha(pacientes.begin() + medio, pacientes.end());

    izquierda = mergeSortPacientesPorDni(izquierda);
    derecha = mergeSortPacientesPorDni(derecha);

    return mergePacientesPorDni(izquierda, derecha);
}

vector<Paciente> GestorPacientesTurnos::mergePacientesPorFechaIngreso(vector<Paciente>& izquierda, vector<Paciente>& derecha) {
    
    vector<Paciente> resultado;
    size_t i = 0, j = 0;

    while (i < izquierda.size() && j < derecha.size()) {
        if (izquierda[i].getFechaIngreso() < derecha[j].getFechaIngreso()) {
            resultado.push_back(izquierda[i]);
            i++;
        } else {
            resultado.push_back(derecha[j]);
            j++;
        }
    }

    while (i < izquierda.size()) {
        resultado.push_back(izquierda[i]);
        i++;
    }

    while (j < derecha.size()) {
        resultado.push_back(derecha[j]);
        j++;
    }

    return resultado;
}
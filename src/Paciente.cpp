#include <iostream>
#include "Paciente.h"
using namespace std;

Paciente::Paciente(
    string codigoHosp,
    int pacId,
    int DNI,
    int fechaIng,
    string diag,
    int prio,
    float peso
){
    codigoHospital = codigoHosp;
    pacienteId = pacId;
    dni = DNI;
    fechaIngreso = fechaIng;
    diagnostico = diag;
    prioridad = prio;
    pesoKg = peso;
}

// Getters
string Paciente::getCodigoHospital() {
    return codigoHospital;
}

int Paciente::getPacienteId() {
    return pacienteId;
}

int Paciente::getDni() {
    return dni;
}

int Paciente::getFechaIngreso() {
    return fechaIngreso;
}

string Paciente::getDiagnostico() {
    return diagnostico;
}

int Paciente::getPrioridad() {
    return prioridad;
}

float Paciente::getPesoKg() {
    return pesoKg;
}

// Setters
void Paciente::setCodigoHospital(string codigoHospitalNuevo) {
    codigoHospital = codigoHospitalNuevo;
}

void Paciente::setPacienteId(int pacienteIdNuevo) {
    pacienteId = pacienteIdNuevo;
}

void Paciente::setDni(int dniNuevo) {
    dni = dniNuevo;
}

void Paciente::setFechaIngreso(int fechaIngresoNueva) {
    fechaIngreso = fechaIngresoNueva;
}

void Paciente::setDiagnostico(string diagnosticoNuevo) {
    diagnostico = diagnosticoNuevo;
}

void Paciente::setPrioridad(int prioridadNueva) {
    prioridad = prioridadNueva;
}

void Paciente::setPesoKg(float pesoNuevo) {
    pesoKg = pesoNuevo;
}
#include <iostream>
#include "Turno.h"
using namespace std;

// Constructor
Turno::Turno(
    string codigoHosp, 
    int turId, 
    int pacId, 
    int medId, 
    int fechaTur, 
    string espec, 
    int duracion
){
    codigoHospital = codigoHosp;
    turnoId = turId;
    pacienteId = pacId;
    medicoId = medId;
    fechaTurno = fechaTur;
    especialidad = espec;
    duracionMinutos = duracion;
}


// Getters
string Turno::getCodigoHospital() {
    return codigoHospital;
}

int Turno::getTurnoId() {
    return turnoId;
}

int Turno::getPacienteId() {
    return pacienteId;
}

int Turno::getMedicoId() {
    return medicoId;
}

int Turno::getFechaTurno() {
    return fechaTurno;
}

string Turno::getEspecialidad() {
    return especialidad;
}

int Turno::getDuracionMinutos() {
    return duracionMinutos;
}

// Setters
void Turno::setCodigoHospital(string codigoHospitalNuevo) {
    codigoHospital = codigoHospitalNuevo;
}

void Turno::setTurnoId(int turnoIdNuevo) {
    turnoId = turnoIdNuevo;
}

void Turno::setPacienteId(int pacienteIdNuevo) {
    pacienteId = pacienteIdNuevo;
}

void Turno::setMedicoId(int medicoIdNuevo) {
    medicoId = medicoIdNuevo;
}

void Turno::setFechaTurno(int fechaTurnoNuevo) {
    fechaTurno = fechaTurnoNuevo;
}

void Turno::setEspecialidad(string especialidadNueva) {
    especialidad = especialidadNueva;
}

void Turno::setDuracionMinutos(int duracionMinutosNueva) {
    duracionMinutos = duracionMinutosNueva;
}


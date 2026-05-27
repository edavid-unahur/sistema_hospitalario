#include <iostream>
#include <string>
#include "Turno.h"
using namespace std;


Turno::Turno(
    string codigoHospital, 
    int turnoId, 
    int pacienteId, 
    int medicoId, 
    int fechaTurno, 
    string especialidad, 
    int duracionMinutos
){
    this->codigoHospital = codigoHospital;
    this->turnoId = turnoId;
    this->pacienteId = pacienteId;
    this->medicoId = medicoId;
    this->fechaTurno = fechaTurno;
    this->especialidad = especialidad;
    this->duracionMinutos = duracionMinutos;
}

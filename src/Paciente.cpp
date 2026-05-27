#include <iostream>
#include <string>
#include "Paciente.h"
using namespace std;

Paciente::Paciente(
    string codigoHospital,
    int pacienteId,
    int dni,
    string fechaIngreso,
    string diagnostico,
    int prioridad,
    float pesoKg
){
    this->codigoHospital = codigoHospital;
    this->pacienteId = pacienteId;
    this->dni = dni;
    this->fechaIngreso = fechaIngreso;
    this->diagnostico = diagnostico;
    this->prioridad = prioridad;
    this->pesoKg = pesoKg;
}
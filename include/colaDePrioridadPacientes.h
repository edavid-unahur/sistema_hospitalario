#ifndef COLA_DE_PRIORIDAD_PACIENTES_H
#define COLA_DE_PRIORIDAD_PACIENTES_H
#include <iostream>
using namespace std;
#include <vector>
#include "Paciente.h"

class ColaPrioridadPacientes {
    private:
        vector<Paciente> heap;

    public:
        ColaPrioridadPacientes();
        bool estaVacia();
        void insertar(Paciente paciente);
        Paciente extraerMasPrioritario();
        void actualizarPrioridad(int pacienteId, int nuevaPrioridad);
        void acomodarInsercion(int index);
        void acomodarExtraccion(int index);
        bool tieneMayorPrioridad(Paciente paciente1, Paciente paciente2);

};

#endif
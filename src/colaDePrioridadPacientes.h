#ifndef COLA_DE_PRIORIDAD_PACIENTES_H
#define COLA_DE_PRIORIDAD_PACIENTES_H
#include <iostream>
using namespace std;
#include <vector>
#include "Paciente.h"

class colaPrioridadPacientes {
    private:
        vector<Paciente> heap;

    public:
        void insertar(Paciente paciente);
        Paciente extraerMasPrioritario();
        void actualizarPrioridad(int pacienteId, int nuevaPrioridad);
        void auxInsertar(int index);
        void auxExtraer(int index);

};

#endif
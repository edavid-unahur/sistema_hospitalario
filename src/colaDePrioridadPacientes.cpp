#include<ios>
#include<fstream>
using namespace std;
#include "colaDePrioridadPacientes.h"
#include "Paciente.h"

colaPrioridadPacientes::colaPrioridadPacientes() {}
bool colaPrioridadPacientes::tieneMayorPrioridad(Paciente paciente1, Paciente paciente2) {
    if (paciente1.getPrioridad() > paciente2.getPrioridad()) {
        return true;
    } 
    
    if (paciente1.getPrioridad() < paciente2.getPrioridad()) {
        return false;
    } 
        
    return paciente1.getFechaIngreso() < paciente2.getFechaIngreso();;

}

void colaPrioridadPacientes::insertar(Paciente paciente) {
    heap.push_back(paciente);
    acomodarInsercion(heap.size() - 1);
}

void colaPrioridadPacientes::acomodarInsercion(int posInsertar) {
    if (posInsertar == 0) {
        return;
    }

    int padre = (posInsertar - 1) / 2;

    if (tieneMayorPrioridad(heap[posInsertar], heap[padre])) {
        Paciente aux = heap[posInsertar];
        heap[posInsertar] = heap[padre];
        heap[padre] = aux;
        acomodarInsercion(padre);
    }
}

Paciente colaPrioridadPacientes::extraerMasPrioritario() {
    Paciente salida = heap[0];

    heap[0] = heap[heap.size() - 1];
    heap.pop_back();
    acomodarExtraccion(0);
    return salida;    

}

void colaPrioridadPacientes::acomodarExtraccion(int posExtraer) {
    int hijoIzq = 2 * posExtraer + 1;
    int hijoDer = 2 * posExtraer + 2;
    int aAcomodar = posExtraer;

    if (heap.empty()) {
        cout << "Error: la cola de prioridad está vacía." << endl;
        return;
    }

    if (hijoIzq < heap.size() && tieneMayorPrioridad(heap[hijoIzq], heap[aAcomodar])) {
        aAcomodar = hijoIzq;
    }

    if (hijoDer < heap.size() && tieneMayorPrioridad(heap[hijoDer], heap[aAcomodar])) {
        aAcomodar = hijoDer;
    }

    if (aAcomodar != posExtraer) {
        Paciente aux = heap[posExtraer];
        heap[posExtraer] = heap[aAcomodar];
        heap[aAcomodar] = aux;
        acomodarExtraccion(aAcomodar);
    }
}

void colaPrioridadPacientes::actualizarPrioridad(int pacienteId, int nuevaPrioridad) {

    for (int i = 0; i < heap.size(); i++) {
        if (heap[i].getPacienteId() == pacienteId) {

            int prioridadAnterior = heap[i].getPrioridad();
            heap[i].setPrioridad(nuevaPrioridad);
        
            if (nuevaPrioridad > prioridadAnterior) {
            acomodarInsercion(i);
            } else if (nuevaPrioridad < prioridadAnterior) {
            acomodarExtraccion(i);
            }
            break;
        }
      
    }
}
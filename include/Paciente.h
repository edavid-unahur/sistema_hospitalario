#ifndef PACIENTE_H
#define PACIENTE_H
#include <iostream>
using namespace std;

class Paciente {
    private:
        string codigoHospital;
        int pacienteId;
        int dni;
        int fechaIngreso;
        string diagnostico;
        int prioridad;
        float pesoKg;

    public:
        Paciente(
            string codigoHosp,
            int pacId,
            int DNI,
            int fechaIng,
            string diag,
            int prio,
            float peso
        );

    //getters
    string getCodigoHospital();
    int getPacienteId();
    int getDni();
    int getFechaIngreso();
    string getDiagnostico();
    int getPrioridad();
    float getPesoKg();

    //setters
    void setCodigoHospital(string codigoHospitalNuevo);
    void setPacienteId(int pacienteIdNuevo);
    void setDni(int dniNuevo);
    void setFechaIngreso(int fechaIngresoNueva);
    void setDiagnostico(string diagnosticoNuevo);
    void setPrioridad(int prioridadNueva);
    void setPesoKg(float pesoNuevo);
};

#endif
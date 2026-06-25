#ifndef TURNO_H
#define TURNO_H
#include<iostream>
using namespace std;

class Turno {
    private:
        string codigoHospital;
        int turnoId;
        int pacienteId;
        int medicoId;
        int fechaTurno; // Formato: AAAAMMDD
        string especialidad;
        int duracionMinutos;
    public:
        Turno(
            string codigoHosp, 
            int turId, 
            int pacId, 
            int medId, 
            int fechaTur, 
            string espec, 
            int duracion
        ); 

    //getters
    string getCodigoHospital();
    int getTurnoId();
    int getPacienteId();
    int getMedicoId();
    int getFechaTurno();
    string getEspecialidad();
    int getDuracionMinutos();

    //setters
    void setCodigoHospital(string codigoHospitalNuevo);
    void setTurnoId(int turnoIdNuevo);
    void setPacienteId(int pacienteIdNuevo);
    void setMedicoId(int medicoIdNuevo);
    void setFechaTurno(int fechaTurnoNuevo);
    void setEspecialidad(string especialidadNueva);
    void setDuracionMinutos(int duracionMinutosNueva);
};

#endif
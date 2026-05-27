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
            string codigoHospital, 
            int turnoId, 
            int pacienteId, 
            int medicoId, 
            int fechaTurno, 
            string especialidad, 
            int duracionMinutos
        ); 

};
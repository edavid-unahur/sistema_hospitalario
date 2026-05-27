#include <iostream>
using namespace std;
#include <string>

class Paciente {
private:
    string codigoHospital;
    int pacienteId;
    int dni;
    string fechaIngreso;
    string diagnostico;
    int prioridad;
    float pesoKg;

public:
    Paciente(
        string codigoHospital,
        int pacienteId,
        int dni,
        string fechaIngreso,
        string diagnostico,
        int prioridad,
        float pesoKg
    );
};

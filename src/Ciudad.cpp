#include <iostream>
#include "Ciudad.h"
using namespace std;


void Ciudad::agregarHospital(Hospital* hospital) {
    hospitales.push_back(hospital);
}

void Ciudad::mostrarInformacion() {
    cout << "Ciudad: " << nombre << ", País: " << pais << std::endl;
}

void Ciudad::mostrarHospitales(){
    for (const auto& hospital : hospitales) {
        cout << "Hospital: " << hospital->getNombre() << " " 
        << hospital->getCodigo() << ", Capacidad: " 
        << hospital->getCapacidad() << endl;
    }
}
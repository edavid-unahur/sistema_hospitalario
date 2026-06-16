#include "Ciudad.h"
#include "Hospital.h"
#include <iostream>

using namespace std;

Ciudad::Ciudad(
    string codigoCiudad,
    string nombre,
    string pais
) {
    this->codigoCiudad = codigoCiudad;
    this->nombre = nombre;
    this->pais = pais;
}

string Ciudad::getCodigoCiudad() const {return codigoCiudad;}

string Ciudad::getNombre() const {return nombre;}

string Ciudad::getPais() const {return pais;}

void Ciudad::agregarHospital(Hospital* hospital) {
    hospitales.push_back(hospital);
}

void Ciudad::mostrarInformacion() {
    cout << "Ciudad: "
         << nombre
         << " - Pais: "
         << pais
         << endl;
}

void Ciudad::mostrarHospitales() {
    cout << "\nHospitales de "
         << nombre
         << ":\n";
    for (Hospital* hospital : hospitales) {
        if(hospital != nullptr) {
            cout
                << hospital->getCodigoHospital()
                << " - "
                << hospital->getNombre()
                << endl;
        }
    }
}
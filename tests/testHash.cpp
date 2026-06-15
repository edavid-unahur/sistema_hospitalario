#include "../estructuras/TablaHash.h"
#include "../Hospital.h"
#include "../Ciudad.h"
#include "../Especialidad.h"

#include <iostream>

using namespace std;

int main() {

    Ciudad* c1 =
        new Ciudad(
            "C001",
            "Buenos Aires",
            "Argentina"
        );

    Especialidad* cardiologia =
        new Especialidad(
            "ESP01",
            "Cardiologia"
        );

    Especialidad* pediatria =
        new Especialidad(
            "ESP02",
            "Pediatria"
        );

    TablaHash tabla;

    Hospital* h1 =
        new Hospital(
            "HGA",
            "Hospital General",
            100,
            500000,
            50,
            c1
        );

    h1->agregarEspecialidad(cardiologia);
    h1->agregarEspecialidad(pediatria);

    tabla.insertar(h1);

    Hospital* encontrado =
        tabla.buscar("HGA");

    if(encontrado != nullptr) {

        cout << "Hospital encontrado\n\n";

        encontrado->mostrarInformacion();
    }

    return 0;
}
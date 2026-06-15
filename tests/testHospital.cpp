#include "Hospital.h"
#include "Ciudad.h"
#include "Especialidad.h"

int main() {

    Ciudad* ciudad =
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

    Hospital* hospital =
        new Hospital(
            "HGA",
            "Hospital General",
            100,
            500000,
            50,
            ciudad
        );

    hospital->agregarEspecialidad(cardiologia);
    hospital->agregarEspecialidad(pediatria);

    hospital->mostrarInformacion();

    return 0;
}
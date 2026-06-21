#include "../src/Hospital.h"
#include "../src/Especialidad.h"

int main() {


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
            "Buenos Aires"
        );

    hospital->agregarEspecialidad(cardiologia);
    hospital->agregarEspecialidad(pediatria);

    hospital->mostrarInformacion();

    return 0;
}
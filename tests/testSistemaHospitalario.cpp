#include <iostream>
#include <string>
#include <vector>

#include "../src/SistemaHospitalario.h"
#include "../src/Especialidad.h"

int main() {
    SistemaHospitalario sistema;

    bool ok = true;

    // ─────────────────────────────────────────────
    // HOSPITALES
    // ─────────────────────────────────────────────
    sistema.agregarHospital("HGA", "Hospital Garrahan", "CABA",     500, 80, 15000000);
    sistema.agregarHospital("HIT", "Hospital Italiano", "Cordoba",  300, 40, 9000000);
    sistema.agregarHospital("HMD", "Hospital Medico",   "La Plata", 400, 60, 12000000);

    auto hospitales = sistema.obtenerTodosHospitales();
    if (hospitales.size() != 3) {
        ok = false;
        std::cout << "Fallo: hospitales iniciales\n";
    }

    // ─────────────────────────────────────────────
    // ESPECIALIDADES
    // ─────────────────────────────────────────────
    Especialidad* cardio       = new Especialidad("ESP01", "Cardiologia");
    Especialidad* pediatria    = new Especialidad("ESP02", "Pediatria");
    Especialidad* traumatologia = new Especialidad("ESP03", "Traumatologia");

    sistema.agregarEspecialidadAHospital("HGA", cardio);
    sistema.agregarEspecialidadAHospital("HGA", pediatria);
    sistema.agregarEspecialidadAHospital("HIT", cardio);
    sistema.agregarEspecialidadAHospital("HMD", traumatologia);

    // ─────────────────────────────────────────────
    // CANTIDAD
    // ─────────────────────────────────────────────
    if (sistema.getCantidadHospitales() != 3) {
        ok = false;
        std::cout << "Fallo: cantidad esperada 3\n";
    }

    auto todos = sistema.obtenerTodosHospitales();
    if (todos.size() != 3) {
        ok = false;
        std::cout << "Fallo: cantidad de hospitales devueltos\n";
    }

    // ─────────────────────────────────────────────
    // ORDENAMIENTO
    // ─────────────────────────────────────────────
    auto porCapacidad = sistema.obtenerHospitalesOrdenadosPorCapacidad(true);
    if (porCapacidad.empty() || porCapacidad.front()->getCodigoHospital() != "HGA") {
        ok = false;
        std::cout << "Fallo: orden por capacidad\n";
    }

    auto porPersonal = sistema.obtenerHospitalesOrdenadosPorPersonal(false);
    if (porPersonal.size() != 3 || porPersonal.front()->getCodigoHospital() != "HIT") {
        ok = false;
        std::cout << "Fallo: orden por personal\n";
    }

    auto porPresupuesto = sistema.obtenerHospitalesOrdenadosPorPresupuesto(true);
    if (porPresupuesto.empty() || porPresupuesto.front()->getCodigoHospital() != "HGA") {
        ok = false;
        std::cout << "Fallo: orden por presupuesto\n";
    }

    // ─────────────────────────────────────────────
    // MOSTRAR
    // ─────────────────────────────────────────────
    if (!sistema.mostrarHospital("HGA")) {
        ok = false;
        std::cout << "Fallo: mostrarHospital\n";
    }

    // ─────────────────────────────────────────────
    // DERIVACIONES Y DIJKSTRA
    // ─────────────────────────────────────────────
    sistema.agregarDerivacion("HGA", "HIT", 20);
    sistema.agregarDerivacion("HGA", "HMD", 10);
    sistema.agregarDerivacion("HMD", "HIT", 5);

    auto ruta = sistema.calcularRutaOptima("HGA", "HIT");
    if (ruta.size() < 2 || ruta.front() != "HGA" || ruta.back() != "HIT") {
        ok = false;
        std::cout << "Fallo: ruta optima\n";
    }

    // ─────────────────────────────────────────────
    // BUSQUEDA POR ESPECIALIDAD
    // ─────────────────────────────────────────────
    auto porEspecialidad = sistema.obtenerHospitalesPorEspecialidad("ESP01");
    if (porEspecialidad.size() != 2) {
        ok = false;
        std::cout << "Fallo: busqueda por especialidad Cardiologia\n";
    } else {
        bool todosCorrectos = true;
        for (auto* hospital : porEspecialidad) {
            if (!hospital->tieneEspecialidad("ESP01")) {
                todosCorrectos = false;
                break;
            }
        }
        if (!todosCorrectos) {
            ok = false;
            std::cout << "Fallo: resultados de especialidad incorrectos\n";
        }
    }

    auto porEspecialidadInexistente = sistema.obtenerHospitalesPorEspecialidad("ESP99");
    if (!porEspecialidadInexistente.empty()) {
        ok = false;
        std::cout << "Fallo: especialidad inexistente\n";
    }

    // ─────────────────────────────────────────────
    // FACTOR DE CARGA
    // ─────────────────────────────────────────────
    if (sistema.getFactorCargaTabla() < 0.0f) {
        ok = false;
        std::cout << "Fallo: factor de carga\n";
    }

    // ─────────────────────────────────────────────
    // ELIMINAR
    // ─────────────────────────────────────────────
    bool eliminado = sistema.eliminarHospital("HIT");
    if (!eliminado || sistema.getCantidadHospitales() != 2) {
        ok = false;
        std::cout << "Fallo: eliminacion de hospital\n";
    }

    // ─────────────────────────────────────────────
    // RESULTADO
    // ─────────────────────────────────────────────
    if (ok) {
        std::cout << "Pruebas del punto A completadas correctamente.\n";
    } else {
        std::cout << "Hay errores en las pruebas del punto A.\n";
    }

    delete cardio;
    delete pediatria;
    delete traumatologia;

    return ok ? 0 : 1;
}
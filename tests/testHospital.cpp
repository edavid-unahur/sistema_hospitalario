#include <iostream>
#include "Hospital.h"
#include "SistemaHospitalario.h"

int main() {

    SistemaHospitalario sistema;

    std::cout << "=== TEST PUNTO A1 - GESTION DE HOSPITALES ===\n\n";

    // ── Cargar desde archivo ──────────────────────────────
    std::cout << "--- Cargando hospitales desde archivo ---\n";
    sistema.cargarHospitales("data/input/hospitales.txt");
    std::cout << "\n";

    // ── Mostrar hospital existente ────────────────────────
    std::cout << "--- Mostrar hospital existente (H001) ---\n";
    sistema.mostrarHospital("H001");
    std::cout << "\n";

    // ── Mostrar hospital inexistente ──────────────────────
    std::cout << "--- Mostrar hospital inexistente (XYZ) ---\n";
    sistema.mostrarHospital("XYZ");
    std::cout << "\n";

    // ── Agregar hospital manualmente ──────────────────────
    std::cout << "--- Agregar hospital nuevo (HCO) ---\n";
    sistema.agregarHospital("HCO", "HospitalCordoba", "Cordoba", 200, {}, 100, 5000000);
    std::cout << "\n";

    // ── Agregar hospital duplicado ────────────────────────
    std::cout << "--- Agregar hospital duplicado (H001) ---\n";
    sistema.agregarHospital("H001", "Duplicado", "BuenosAires", 100, {}, 50, 1000000);
    std::cout << "\n";

    // ── Eliminar hospital existente ───────────────────────
    std::cout << "--- Eliminar hospital existente (HCO) ---\n";
    sistema.eliminarHospital("HCO");
    std::cout << "\n";

    // ── Eliminar hospital inexistente ─────────────────────
    std::cout << "--- Eliminar hospital inexistente (HCO) ---\n";
    sistema.eliminarHospital("HCO");
    std::cout << "\n";

    // ── Listar por capacidad ──────────────────────────────
    std::cout << "--- Listar por capacidad de camas (descendente) ---\n";
    sistema.listarPorCapacidad(true);

    // ── Buscar por especialidad ───────────────────────────
    std::cout << "--- Buscar hospitales con especialidad 'Cardiologia' ---\n";
    sistema.buscarPorEspecialidad("Cardiologia");
    std::cout << "\n";


    sistema.cargarDerivaciones("data/input/derivaciones.txt");
    // ── Ruta optima exitosa ───────────────────────────────────
    std::cout << "--- Calcular ruta optima H001 -> H092 (con conexion) ---\n";
    sistema.calcularRutaOptima("H001", "H092");

    // ── Ruta sin conexion (caso borde) ────────────────────────
    std::cout << "--- Calcular ruta optima H001 -> H002 (sin conexion, caso esperado) ---\n";
    sistema.calcularRutaOptima("H001", "H002");

    return 0;
}
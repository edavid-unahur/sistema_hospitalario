#include <iostream>
#include <limits>
#include <string>
#include "SistemaHospitalario.h" // ◄ ACTIVADO: Conexión con tu lógica central

using namespace std;

void limpiarBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Función para limpiar la pantalla según el sistema operativo
void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear"); // Por si algún día lo corres en Linux/macOS
    #endif
}

// Función para congelar la pantalla hasta que el usuario decida continuar
void pausarYContinuar() {
    cout << "\n🔹 Presione ENTER para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get(); // Espera el Enter
}

// ◄ MODIFICADO: Recibe la instancia de tu sistema por referencia
void menuDiagnosticos(SistemaHospitalario& sistema) {
    int opcion = -1;
    string codigoDiag;

    while (opcion != 0) {
        limpiarPantalla();
        
        cout << "====================================================\n";
        cout << "  Modulo C: Gestion de Diagnosticos (BST / AVL)     \n";
        cout << "====================================================\n";
        cout << "  1. Insertar nuevo diagnostico\n";
        cout << "  2. Incrementar frecuencia de diagnostico existente\n";
        cout << "  3. Listar diagnosticos por frecuencia (Inorder)\n";
        cout << "  4. Ver el diagnostico mas frecuente\n";
        cout << "  5. Eliminar un diagnostico\n";
        cout << "  6. Ver altura del arbol y estado de balance\n";
        cout << "  0. Volver al menu principal\n";
        cout << "====================================================\n";
        cout << "Ingrese una opcion: ";
        
        if (!(cin >> opcion)) {
            limpiarBuffer();
            cout << "⚠️ Entrada invalida. Ingrese un numero.\n";
            pausarYContinuar();
            continue;
        }

        // Si elige salir, no pausamos ni procesamos
        if (opcion == 0) break;

        // Limpiamos la pantalla para mostrar el resultado de la acción de forma limpia
        limpiarPantalla();

        switch (opcion) {
            case 1:
            case 2:
                cout << "▶ [INSERTAR / INCREMENTAR DIAGNOSTICO]\n\n";
                cout << "Ingrese el codigo o nombre del diagnostico: ";
                cin >> codigoDiag;
                cout << "\n";
                sistema.registrarDiagnostico(codigoDiag);
                break;
            case 3:
                cout << "▶ [LISTADO INORDER DE DIAGNOSTICOS]\n";
                sistema.listarDiagnosticos();
                break;
            case 4:
                cout << "▶ [DIAGNOSTICO MAS FRECUENTE]\n";
                sistema.mostrarDiagnosticoMasFrecuente();
                break;
            case 5:
                cout << "▶ [ELIMINAR DIAGNOSTICO]\n\n";
                cout << "Ingrese el codigo del diagnostico a eliminar: ";
                cin >> codigoDiag;
                cout << "\n";
                sistema.eliminarDiagnostico(codigoDiag);
                break;
            case 6:
                cout << "▶ [ESTADISTICAS DE LA ESTRUCTURA]\n";
                sistema.mostrarEstadisticasArbol();
                break;
            default:
                cout << "⚠️ Opcion no valida. Intente nuevamente.\n";
        }

        pausarYContinuar(); // Esperamos a que el usuario lea el resultado
    }
}
// ── SUBMENÚ: MÓDULO D (OPTIMIZACIÓN DE INSUMOS) ──
void menuInsumos(SistemaHospitalario& sistema) {
    int opcion = -1;
    int capacidad;

    while (opcion != 0) {
        limpiarPantalla();
        cout << "====================================================\n";
        cout << "  Modulo D: Optimizacion de Insumos (Backtracking)  \n";
        cout << "====================================================\n";
        cout << "  1. Cargar lista de insumos de prueba\n";
        cout << "  2. Ejecutar Optimizacion (Backtracking Puro)\n";
        cout << "  3. Ejecutar Optimizacion (Branch & Bound)\n";
        cout << "  4. Comparar nodos explorados (Puro vs Poda)\n";
        cout << "  0. Volver al menu principal\n";
        cout << "====================================================\n";
        cout << "Ingrese una opcion: ";
        
        if (!(cin >> opcion)) {
            limpiarBuffer();
            cout << "⚠️ Entrada invalida. Ingrese un numero.\n";
            pausarYContinuar();
            continue;
        }

        if (opcion == 0) break;

        limpiarPantalla();

        switch (opcion) {
            case 1:
                cout << "▶ [CARGANDO INSUMOS]\n\n";
                sistema.cargarInsumosPorDefecto();
                break;
            case 2:
                cout << "▶ [EJECUCCION: BACKTRACKING PURO]\n\n";
                cout << "Ingrese la capacidad maxima de la ambulancia (en kg): ";
                if (cin >> capacidad) {
                    sistema.ejecutarBacktrackingPuro(capacidad);
                } else {
                    limpiarBuffer();
                    cout << "⚠️ Capacidad invalida.\n";
                }
                break;
            case 3:
                cout << "▶ [EJECUCCION: BRANCH & BOUND (CON PODA)]\n\n";
                cout << "Ingrese la capacidad maxima de la ambulancia (en kg): ";
                if (cin >> capacidad) {
                    sistema.ejecutarBranchAndBound(capacidad);
                } else {
                    limpiarBuffer();
                    cout << "⚠️ Capacidad invalida.\n";
                }
                break;
            case 4:
                cout << "▶ [ESTUDIO COMPARATIVO DE RENDIMIENTO]\n\n";
                cout << "Ingrese la capacidad maxima para la prueba (en kg): ";
                if (cin >> capacidad) {
                    sistema.compararAlgoritmos(capacidad);
                } else {
                    limpiarBuffer();
                    cout << "⚠️ Capacidad invalida.\n";
                }
                break;
            default:
                cout << "⚠️ Opcion no valida. Intente nuevamente.\n";
        }

        pausarYContinuar();
    }
}
// ── FUNCIÓN PRINCIPAL: MENÚ DE ENTRADA AL SISTEMA ──
int main() {
    SistemaHospitalario sistema; // Instancia real compartida por todo el flujo [cite: 483]

    int opcion = -1;
    while (opcion != 0) {
        limpiarPantalla();
        cout << "====================================================\n";
        cout << "       SISTEMA DE GESTION HOSPITALARIA (UNAHUR)     \n";
        cout << "====================================================\n";
        cout << "  1. Cargar datos desde archivos (Modulo A y B)\n";
        cout << "  2. Modulo A: Gestion de Hospitales\n";
        cout << "  3. Modulo B: Pacientes y Turnos\n";
        cout << "  4. Modulo C: Arbol de Diagnosticos\n";
        cout << "  5. Modulo D: Optimizacion de Insumos\n";
        cout << "  0. Salir del programa\n";
        cout << "====================================================\n";
        cout << "Ingrese una opcion: ";

        if (!(cin >> opcion)) {
            limpiarBuffer();
            cout << "⚠️ Entrada invalida. Ingrese un numero.\n";
            pausarYContinuar();
            continue;
        }

        switch (opcion) {
            case 1:
                limpiarPantalla();
                cout << "▶ [CARGANDO DATOS GENERALES]\n\n";
                cout << "[Simulando lectura de hospitales.txt, pacientes.txt, etc...]\n";
                // Aquí se engancharán los métodos de tus compañeros en el futuro
                pausarYContinuar();
                break;
            case 2:
                limpiarPantalla();
                cout << "▶ [MODULO A: GESTION DE HOSPITALES]\n\n";
                cout << "Espacio reservado para los flujos de Hospitales (Dijkstra/Hash).\n";
                pausarYContinuar();
                break;
            case 3:
                limpiarPantalla();
                cout << "▶ [MODULO B: PACIENTES Y TURNOS]\n\n";
                cout << "Espacio reservado para los flujos de Pacientes (Min-Heap/MergeSort).\n";
                pausarYContinuar();
                break;
            case 4:
                menuDiagnosticos(sistema); // Abre tu submódulo C pasándole el sistema activo [cite: 496]
                break;
            case 5:
                menuInsumos(sistema); // Abre tu submódulo D pasándole el sistema activo [cite: 498]
                break;
            case 0:
                limpiarPantalla();
                cout << "====================================================\n";
                cout << "  Saliendo del sistema de forma segura. ¡Exitos!    \n";
                cout << "====================================================\n";
                break;
            default:
                cout << "⚠️ Opcion no valida. Intente nuevamente.\n";
                pausarYContinuar();
        }
    }

    return 0;
}
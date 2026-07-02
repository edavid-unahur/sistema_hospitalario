#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include "SistemaHospitalario.h"
#include "gestorPacientesTurnos.h"
#include "Paciente.h"
#include "Turno.h"

using namespace std;

void limpiarBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pausarYContinuar() {
    cout << "\nPresione ENTER para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

/* =========================================================================
   DEFENSA TEÓRICA - MÓDULO A: GESTIÓN DE HOSPITALES
   -------------------------------------------------------------------------
   1. TABLA HASH PROPIA:
      - Estructura: Direccionamiento abierto con sondeo lineal.
      - Función Hash: Hashing polinomial (base 31). Trata los caracteres del
        código de hospital como coeficientes. Ej: hash("H001") = (H*31^3 + 0*31^2 + 0*31^1 + 1) % Capacidad.
        La base 31 es un número primo que genera una excelente distribución para strings cortos.
      - Factor de Carga: Limitado a un máximo de 0.8. Si supera este umbral,
        se dispara el método rehash() duplicando la capacidad al siguiente impar/primo,
        reduciendo la probabilidad de colisiones y manteniendo búsquedas O(1) promedio.
   2. CAMINO MÍNIMO (DIJKSTRA):
      - Representación del Grafo: Lista de adyacencia (mediante vector de Aristas en cada NodoGrafo).
      - Complejidad: O(V^2) en la versión básica, ideal para el tamaño moderado de la red de hospitales.
        Garantiza encontrar la ruta con menor tiempo de traslado entre dos establecimientos de salud.
   ========================================================================= */

void menuHospitales(SistemaHospitalario& sistema, GestorPacientesTurnos& gestor) {
    int opcion = -1;
    string codigo, nombre, ciudad, esp;
    int camas, personal, presupuesto;

    while (opcion != 0) {
        limpiarPantalla();
        cout << "====================================================\n";
        cout << "  Modulo A: Gestion de Hospitales (Hash & Dijkstra) \n";
        cout << "====================================================\n";
        cout << "  1. Mostrar informacion de un hospital por codigo\n";
        cout << "  2. Agregar un nuevo hospital al sistema\n";
        cout << "  3. Eliminar un hospital existente\n";
        cout << "  4. Listar hospitales por criterio (Camas, Personal, Presupuesto)\n";
        cout << "  5. Calcular ruta optima de derivacion (Dijkstra)\n";
        cout << "  6. Buscar hospitales por especialidad (ordenados por camas libres)\n";
        cout << "  0. Volver al menu principal\n";
        cout << "====================================================\n";
        cout << "Ingrese una opcion: ";

        if (!(cin >> opcion)) {
            limpiarBuffer();
            cout << "[!] Entrada invalida. Ingrese un numero.\n";
            pausarYContinuar();
            continue;
        }

        if (opcion == 0) break;
        limpiarPantalla();

        switch (opcion) {
            case 1:
                cout << "> [MOSTRAR INFORMACION HOSPITAL]\n\n";
                cout << "Ingrese el codigo de hospital (ej: H001): ";
                cin >> codigo;
                cout << "\n";
                sistema.mostrarHospital(codigo);
                break;
            case 2:
                cout << "> [AGREGAR NUEVO HOSPITAL]\n\n";
                cout << "Codigo (ej: HCO): "; cin >> codigo;
                cout << "Nombre: "; cin >> nombre;
                cout << "Ciudad: "; cin >> ciudad;
                cout << "Capacidad de Camas: "; cin >> camas;
                cout << "Personal Medico: "; cin >> personal;
                cout << "Presupuesto Anual ($): "; cin >> presupuesto;
                sistema.agregarHospital(codigo, nombre, ciudad, camas, {}, personal, presupuesto);
                break;
            case 3:
                cout << "> [ELIMINAR HOSPITAL]\n\n";
                cout << "Ingrese el codigo del hospital a eliminar: ";
                cin >> codigo;
                cout << "\n";
                {
                    std::string masCercano = sistema.obtenerHospitalMasCercano(codigo);
                    if (sistema.eliminarHospital(codigo)) {
                        if (!masCercano.empty()) {
                            cout << "[HOSPITAL] El hospital mas cercano disponible para reasignar es: " << masCercano << "\n";
                            gestor.reasignarPacientes(codigo, masCercano);
                        } else {
                            cout << "[!] No se encontraron otros hospitales para derivar pacientes.\n";
                        }
                    }
                }
                break;
            case 4: {
                int criterio = -1;
                cout << "> [LISTAR HOSPITALES POR CRITERIO]\n\n";
                cout << "1. Capacidad de Camas\n";
                cout << "2. Cantidad de Personal Medico\n";
                cout << "3. Presupuesto Anual\n";
                cout << "Seleccione una opcion: ";
                cin >> criterio;
                if (criterio == 1) sistema.listarPorCapacidad(true);
                else if (criterio == 2) sistema.listarPorPersonalMedico(true);
                else if (criterio == 3) sistema.listarPorPresupuesto(true);
                else cout << "[!] Criterio invalido.\n";
                break;
            }
            case 5:
                cout << "> [CALCULAR RUTA OPTIMA - DIJKSTRA]\n\n";
                cout << "Ingrese codigo del hospital Origen (ej: H001): "; cin >> codigo;
                cout << "Ingrese codigo del hospital Destino (ej: H092): "; cin >> nombre;
                sistema.calcularRutaOptima(codigo, nombre);
                break;
            case 6:
                cout << "> [BUSCAR HOSPTIALES POR ESPECIALIDAD]\n\n";
                cout << "Ingrese la especialidad (ej: Cardiologia): ";
                cin >> esp;
                sistema.buscarPorEspecialidad(esp);
                break;
            default:
                cout << "[!] Opcion no valida. Intente nuevamente.\n";
        }
        pausarYContinuar();
    }
}

/* =========================================================================
   DEFENSA TEÓRICA - MÓDULO B: PACIENTES Y TURNOS
   -------------------------------------------------------------------------
   1. COLA DE PRIORIDAD (MIN-HEAP):
      - Implementación: Basado en un vector que simula un árbol binario.
      - Fórmulas de Navegación:
        - Hijo izquierdo de i: 2i + 1
        - Hijo derecho de i: 2i + 2
        - Padre de i: (i - 1) / 2
      - Prioridad de Paciente: 1 (máxima urgencia/crítico) al 5 (leve).
        En caso de igual nivel de prioridad, se desempata por la fecha de ingreso
        (menor fecha de ingreso/más antiguo primero), garantizando equidad (FIFO).
      - Complejidades: Inserción O(log N), Extracción del mínimo O(log N).
   2. ORDENAMIENTO (MERGE SORT):
      - Algoritmo: Divide y Conquistar. Divide el vector a la mitad de forma recursiva
        y luego fusiona (merge) las partes ordenadas.
      - Complejidad: O(N log N) en peor, mejor y caso promedio, lo cual es óptimo
        para ordenamiento por comparaciones. Requiere O(N) espacio adicional para fusionar.
   ========================================================================= */

void menuPacientes(GestorPacientesTurnos& gestor, SistemaHospitalario& sistema) {
    int opcion = -1;
    int fIni, fFin, dni, medId;

    while (opcion != 0) {
        limpiarPantalla();
        cout << "====================================================\n";
        cout << "  Modulo B: Pacientes y Turnos (Heap & MergeSort)   \n";
        cout << "====================================================\n";
        cout << "  1. Calcular total de pacientes atendidos por hospital en rango de fechas\n";
        cout << "  2. Detectar hospitales con sobrecarga (Ocupacion > 90%)\n";
        cout << "  3. Buscar todos los turnos de un paciente por DNI\n";
        cout << "  4. Operaciones de Cola de Prioridad de Espera (Heap)\n";
        cout << "  5. Listar turnos de un medico por ID (orden cronologico)\n";
        cout << "  0. Volver al menu principal\n";
        cout << "====================================================\n";
        cout << "Ingrese una opcion: ";

        if (!(cin >> opcion)) {
            limpiarBuffer();
            cout << "[!] Entrada invalida. Ingrese un numero.\n";
            pausarYContinuar();
            continue;
        }

        if (opcion == 0) break;
        limpiarPantalla();

        switch (opcion) {
            case 1:
                cout << "> [PACIENTES ATENDIDOS POR RANGO DE FECHAS]\n\n";
                cout << "Ingrese fecha de inicio (AAAAMMDD, ej: 20250101): "; cin >> fIni;
                cout << "Ingrese fecha de fin (AAAAMMDD, ej: 20251231):    "; cin >> fFin;
                {
                    gestor.inicializarPacientesPorFechaIngreso();
                    auto resultado = gestor.getCantPacientesAtendidosPorHospital(fIni, fFin);
                    cout << "\nResultados:\n";
                    if (resultado.empty()) {
                        cout << "No hay pacientes atendidos en ese rango de fechas.\n";
                    } else {
                        for (auto& par : resultado) {
                            cout << "Hospital: " << par.first << " --> Pacientes: " << par.second << "\n";
                        }
                    }
                }
                break;
            case 2:
                {
                    cout << "> [DETECTAR SOBRECARGA EN HOSPITALES]\n\n";
                    cout << "1. Ver estado de sobrecarga actual (Ocupacion > 90%)\n";
                    cout << "2. Detectar sobrecarga por ingresos semanales (> X en una semana)\n";
                    cout << "3. Simular sobrecarga en un hospital de prueba\n";
                    cout << "Seleccione una opcion: ";
                    int sobOpc = 1;
                    if (cin >> sobOpc) {
                        if (sobOpc == 3) {
                            string hCode;
                            cout << "Ingrese codigo de hospital para simular ocupacion (ej: H001): ";
                            cin >> hCode;
                            auto listHosp = sistema.obtenerTodosHospitales();
                            Hospital* hTarget = nullptr;
                            for (auto* h : listHosp) {
                                if (h->getCodigoHospital() == hCode) {
                                    hTarget = h;
                                    break;
                                }
                            }
                            if (hTarget) {
                                int target = hTarget->getCapacidadCamas() * 0.95;
                                for (int i = 0; i < target; i++) {
                                    hTarget->ocuparCama();
                                }
                                cout << "[OK] Se ocuparon " << target << " camas en el hospital " << hCode 
                                     << " (ocupacion simulada al: " << hTarget->getPorcentajeOcupacion() << "%).\n";
                            } else {
                                cout << "[!] Hospital no encontrado.\n";
                            }
                        } else if (sobOpc == 2) {
                            int limite;
                            cout << "Ingrese cantidad de ingresos limite por semana (ej: 2): ";
                            cin >> limite;
                            auto result = gestor.detectarSobrecargaIngresos(limite);
                            cout << "\nHospitales con mas de " << limite << " ingresos en una semana:\n";
                            if (result.empty()) {
                                cout << "No se detectaron hospitales con esta sobrecarga.\n";
                            } else {
                                for (const auto& code : result) {
                                    cout << " - Hospital: " << code << " [!] (SOBRECARGADO)\n";
                                }
                            }
                        } else {
                            sistema.getHospitalesSobrecargados();
                        }
                    } else {
                        limpiarBuffer();
                    }
                }
                break;
            case 3:
                cout << "> [BUSCAR TURNOS DE PACIENTE POR DNI]\n\n";
                cout << "Ingrese DNI del paciente: "; cin >> dni;
                {
                    gestor.inicializarPacientesPorDni();
                    gestor.inicializarTurnosPorPacienteId();
                    auto turnos = gestor.getTurnosPorDni(dni);
                    cout << "\nTurnos registrados para DNI " << dni << ":\n";
                    if (turnos.empty()) {
                        cout << "No se encontraron turnos para el DNI ingresado.\n";
                    } else {
                        for (auto& t : turnos) {
                            cout << " - ID Turno: " << t.getTurnoId() 
                                 << " | Especialidad: " << t.getEspecialidad() 
                                 << " | Fecha: " << t.getFechaTurno() 
                                 << " | Medico ID: " << t.getMedicoId() << "\n";
                        }
                    }
                }
                break;
            case 4: {
                int subOpc = -1;
                while (subOpc != 0) {
                    limpiarPantalla();
                    cout << "====================================================\n";
                    cout << "  Cola de Prioridad (Min-Heap) de Lista de Espera   \n";
                    cout << "====================================================\n";
                    cout << "  1. Poblar cola de prioridad con pacientes de archivos\n";
                    cout << "  2. Atender al paciente mas urgente (Extraccion Heap)\n";
                    cout << "  3. Cambiar prioridad de un paciente por su ID\n";
                    cout << "  4. Agregar nuevo paciente a la lista de espera\n";
                    cout << "  0. Volver al menu de Pacientes\n";
                    cout << "====================================================\n";
                    cout << "Ingrese una opcion: ";
                    if (cin >> subOpc) {
                        limpiarPantalla();
                        if (subOpc == 1) {
                            gestor.cargarPacientesEnCola();
                            cout << "[OK] Cola de prioridad inicializada con los pacientes cargados en memoria.\n";
                            pausarYContinuar();
                        } else if (subOpc == 2) {
                            try {
                                Paciente p = gestor.atenderPacienteMasUrgente();
                                cout << "[HOSPITAL] Atendiendo paciente mas prioritario:\n";
                                cout << " - ID Paciente: " << p.getPacienteId() << "\n";
                                cout << " - DNI:         " << p.getDni() << "\n";
                                cout << " - Prioridad:   " << p.getPrioridad() << " (1:Critico, 5:Leve)\n";
                                cout << " - Ingreso:     " << p.getFechaIngreso() << "\n";
                                cout << " - Diagnostico: " << p.getDiagnostico() << "\n";
                            } catch (const exception& e) {
                                cout << "[!] " << e.what() << "\n";
                            }
                            pausarYContinuar();
                        } else if (subOpc == 3) {
                            int pacId, nuevaPrio;
                            cout << "Ingrese ID del paciente: "; cin >> pacId;
                            cout << "Ingrese nueva prioridad (1-5): "; cin >> nuevaPrio;
                            gestor.cambiarPrioridadPaciente(pacId, nuevaPrio);
                            cout << "[OK] Prioridad del paciente " << pacId << " actualizada en el heap.\n";
                            pausarYContinuar();
                        } else if (subOpc == 4) {
                            string hCode, diag;
                            int pacId, pDni, fIng, prio;
                            float peso;
                            cout << "Ingrese codigo de Hospital: "; cin >> hCode;
                            cout << "Ingrese ID Paciente: "; cin >> pacId;
                            cout << "Ingrese DNI Paciente: "; cin >> pDni;
                            cout << "Ingrese Fecha Ingreso (AAAAMMDD): "; cin >> fIng;
                            cout << "Ingrese Diagnostico: "; cin >> diag;
                            cout << "Ingrese Prioridad (1-5): "; cin >> prio;
                            cout << "Ingrese Peso (kg): "; cin >> peso;
                            Paciente nuevoP(hCode, pacId, pDni, fIng, diag, prio, peso);
                            gestor.agregarPacienteAListaEspera(nuevoP);
                            cout << "[OK] Paciente agregado exitosamente a la cola de prioridad.\n";
                            pausarYContinuar();
                        }
                    } else {
                        limpiarBuffer();
                    }
                }
                break;
            }
            case 5:
                cout << "> [LISTAR TURNOS DE MEDICO - MERGESORT]\n\n";
                cout << "Ingrese ID del Medico: "; cin >> medId;
                {
                    gestor.inicializarTurnosPorMedico();
                    auto turnos = gestor.getTurnosPorMedicoId(medId);
                    cout << "\nTurnos cronologicos del Medico ID " << medId << ":\n";
                    if (turnos.empty()) {
                        cout << "No hay turnos registrados para este medico.\n";
                    } else {
                        for (auto& t : turnos) {
                            cout << " - ID Turno: " << t.getTurnoId() 
                                 << " | Fecha: " << t.getFechaTurno() 
                                 << " | Especialidad: " << t.getEspecialidad() 
                                 << " | Paciente ID: " << t.getPacienteId() << "\n";
                        }
                    }
                }
                break;
            default:
                cout << "[!] Opcion no valida. Intente nuevamente.\n";
        }
        if (opcion != 4) pausarYContinuar();
    }
}

/* =========================================================================
   DEFENSA TEÓRICA - MÓDULO C: ÁRBOL DE DIAGNÓSTICOS (AVL)
   -------------------------------------------------------------------------
   1. ÁRBOL AVL:
      - Definición: Árbol binario de búsqueda auto-balanceado.
      - Factor de Balance: Altura(Subárbol Izquierdo) - Altura(Subárbol Derecho).
        Debe mantenerse siempre en el rango [-1, 0, 1] en cada nodo.
      - Rotaciones de Rebalanceo:
        - Izquierda-Izquierda (Simple Derecha): Disparado por inserción en subárbol izquierdo de hijo izquierdo.
        - Derecha-Derecha (Simple Izquierda): Disparado por inserción en subárbol derecho de hijo derecho.
        - Izquierda-Derecha (Doble Derecha): Rotación izquierda sobre hijo izquierdo, luego derecha sobre raíz.
        - Derecha-Izquierda (Doble Izquierda): Rotación derecha sobre hijo derecho, luego izquierda sobre raíz.
      - Complejidad: Búsqueda, inserción y eliminación son O(log N) garantizadas.
        Previene la degradación a lista lineal (O(N)) que puede ocurrir en un BST estándar.
   ========================================================================= */

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
            cout << "[!] Entrada invalida. Ingrese un numero.\n";
            pausarYContinuar();
            continue;
        }

        if (opcion == 0) break;
        limpiarPantalla();

        switch (opcion) {
            case 1:
            case 2:
                cout << "> [INSERTAR / INCREMENTAR DIAGNOSTICO]\n\n";
                cout << "Ingrese el codigo o nombre del diagnostico: ";
                cin >> codigoDiag;
                cout << "\n";
                sistema.registrarDiagnostico(codigoDiag);
                break;
            case 3:
                cout << "> [LISTADO INORDER DE DIAGNOSTICOS]\n";
                sistema.listarDiagnosticos();
                break;
            case 4:
                cout << "> [DIAGNOSTICO MAS FRECUENTE]\n";
                sistema.mostrarDiagnosticoMasFrecuente();
                break;
            case 5:
                cout << "> [ELIMINAR DIAGNOSTICO]\n\n";
                cout << "Ingrese el codigo del diagnostico a eliminar: ";
                cin >> codigoDiag;
                cout << "\n";
                sistema.eliminarDiagnostico(codigoDiag);
                break;
            case 6:
                cout << "> [ESTADISTICAS DE LA ESTRUCTURA]\n";
                sistema.mostrarEstadisticasArbol();
                break;
            default:
                cout << "[!] Opcion no valida. Intente nuevamente.\n";
        }
        pausarYContinuar();
    }
}

/* =========================================================================
   DEFENSA TEÓRICA - MÓDULO D: OPTIMIZACIÓN DE INSUMOS
   -------------------------------------------------------------------------
   1. BACKTRACKING PURO:
      - Lógica: Búsqueda exhaustiva recursiva sistemática en todo el árbol de decisiones.
        Explora la inclusión y exclusión de cada insumo.
      - Complejidad: O(2^N). El espacio de búsqueda crece exponencialmente, haciéndose
        inviable para N grandes (N > 25) sin poda.
   2. BRANCH & BOUND (BT CON PODA):
      - Lógica: Estima una cota superior (upper bound) de valor máximo que se podría obtener
        en las ramas restantes a través de un algoritmo codicioso (Greedy Fractional Knapsack).
        Si el bound estimado es menor o igual al mejor valor óptimo actual, se poda la rama de inmediato.
      - Complejidad: Mantiene O(2^N) en peor caso, pero reduce drásticamente el espacio de
        búsqueda en promedio (explorando hasta un 99% menos de nodos).
   ========================================================================= */

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
            cout << "[!] Entrada invalida. Ingrese un numero.\n";
            pausarYContinuar();
            continue;
        }

        if (opcion == 0) break;
        limpiarPantalla();

        switch (opcion) {
            case 1:
                cout << "> [CARGANDO INSUMOS]\n\n";
                sistema.cargarInsumosPorDefecto();
                break;
            case 2:
                cout << "> [EJECUCCION: BACKTRACKING PURO]\n\n";
                cout << "Ingrese la capacidad maxima de la ambulancia (en kg): ";
                if (cin >> capacidad) {
                    sistema.ejecutarBacktrackingPuro(capacidad);
                } else {
                    limpiarBuffer();
                    cout << "[!] Capacidad invalida.\n";
                }
                break;
            case 3:
                cout << "> [EJECUCCION: BRANCH & BOUND (CON PODA)]\n\n";
                cout << "Ingrese la capacidad maxima de la ambulancia (en kg): ";
                if (cin >> capacidad) {
                    sistema.ejecutarBranchAndBound(capacidad);
                } else {
                    limpiarBuffer();
                    cout << "[!] Capacidad invalida.\n";
                }
                break;
            case 4:
                cout << "> [ESTUDIO COMPARATIVO DE RENDIMIENTO]\n\n";
                cout << "Ingrese la capacidad maxima para la prueba (en kg): ";
                if (cin >> capacidad) {
                    sistema.compararAlgoritmos(capacidad);
                } else {
                    limpiarBuffer();
                    cout << "[!] Capacidad invalida.\n";
                }
                break;
            default:
                cout << "[!] Opcion no valida. Intente nuevamente.\n";
        }
        pausarYContinuar();
    }
}

int main() {
    SistemaHospitalario sistema;
    GestorPacientesTurnos gestor;

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
            cout << "[!] Entrada invalida. Ingrese un numero.\n";
            pausarYContinuar();
            continue;
        }

        switch (opcion) {
            case 1:
                limpiarPantalla();
                cout << "> [CARGANDO DATOS GENERALES DESDE ARCHIVOS]\n\n";
                cout << "Cargando hospitales.txt...\n";
                sistema.cargarHospitales("data/input/hospitales.txt");
                cout << "Cargando derivaciones.txt...\n";
                sistema.cargarDerivaciones("data/input/derivaciones.txt");
                cout << "Cargando pacientes.txt...\n";
                gestor.cargarPacientes("data/input/pacientes.txt");
                cout << "Cargando turnos.txt...\n";
                gestor.cargarTurnos("data/input/turnos.txt");
                cout << "\n[OK] Todos los archivos de entrada se cargaron exitosamente.\n";
                pausarYContinuar();
                break;
            case 2:
                menuHospitales(sistema, gestor);
                break;
            case 3:
                menuPacientes(gestor, sistema);
                break;
            case 4:
                menuDiagnosticos(sistema);
                break;
            case 5:
                menuInsumos(sistema);
                break;
            case 0:
                limpiarPantalla();
                cout << "====================================================\n";
                cout << "  Saliendo del sistema de forma segura. ¡Exitos!    \n";
                cout << "====================================================\n";
                break;
            default:
                cout << "[!] Opcion no valida. Intente nuevamente.\n";
                pausarYContinuar();
        }
    }
    return 0;
}
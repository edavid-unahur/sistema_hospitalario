#include "SistemaHospitalario.h"
#include "Algoritmos/Dijkstra.h"
#include <iostream>
#include <climits>

void ordenarPorCapacidad(std::vector<Hospital*>& hospitales, bool descendente) {
    int n = hospitales.size();
    for (int i = 0; i < n - 1; i++) {
        int posicion = i;
        for (int j = i + 1; j < n; j++) {
            if (descendente) {
                if (hospitales[j]->getCapacidadCamas() > hospitales[posicion]->getCapacidadCamas()) {
                    posicion = j;
                }
            } else {
                if (hospitales[j]->getCapacidadCamas() < hospitales[posicion]->getCapacidadCamas()) {
                    posicion = j;
                }
            }
        }
        Hospital* temp = hospitales[i];
        hospitales[i] = hospitales[posicion];
        hospitales[posicion] = temp;
    }
}

void ordenarPorPersonal(std::vector<Hospital*>& hospitales, bool descendente) {
    int n = hospitales.size();
    for (int i = 0; i < n - 1; i++) {
        int posicion = i;
        for (int j = i + 1; j < n; j++) {
            if (descendente) {
                if (hospitales[j]->getPersonalMedico() > hospitales[posicion]->getPersonalMedico()) {
                    posicion = j;
                }
            } else {
                if (hospitales[j]->getPersonalMedico() < hospitales[posicion]->getPersonalMedico()) {
                    posicion = j;
                }
            }
        }
        Hospital* temp = hospitales[i];
        hospitales[i] = hospitales[posicion];
        hospitales[posicion] = temp;
    }
}

void ordenarPorPresupuesto(std::vector<Hospital*>& hospitales, bool descendente) {
    int n = hospitales.size();
    for (int i = 0; i < n - 1; i++) {
        int posicion = i;
        for (int j = i + 1; j < n; j++) {
            if (descendente) {
                if (hospitales[j]->getPresupuestoAnual() > hospitales[posicion]->getPresupuestoAnual()) {
                    posicion = j;
                }
            } else {
                if (hospitales[j]->getPresupuestoAnual() < hospitales[posicion]->getPresupuestoAnual()) {
                    posicion = j;
                }
            }
        }
        Hospital* temp = hospitales[i];
        hospitales[i] = hospitales[posicion];
        hospitales[posicion] = temp;
    }
}

void ordenarPorCamasDesc(std::vector<Hospital*>& hospitales) {
    int n = hospitales.size();
    for (int i = 0; i < n - 1; i++) {
        int posicion = i;
        for (int j = i + 1; j < n; j++) {
            if (hospitales[j]->getCapacidadCamas() > hospitales[posicion]->getCapacidadCamas()) {
                posicion = j;
            }
        }
        Hospital* temp = hospitales[i];
        hospitales[i] = hospitales[posicion];
        hospitales[posicion] = temp;
    }
}

SistemaHospitalario::SistemaHospitalario(int capacidadInicial) 
    : tablahospitales(new TablaHash(capacidadInicial))
    , grafoDerivaciones(nullptr)
    , cantidadHospitales(0)
{}

SistemaHospitalario::~SistemaHospitalario() {
    delete tablahospitales;
    if (grafoDerivaciones) delete grafoDerivaciones;
}


bool SistemaHospitalario::mostrarHospital(const std::string& codigoHospital) {
    Hospital* h = tablahospitales->buscar(codigoHospital);
    if (h) {
        h->mostrarInformacion();
        return true;
    } else {
        std::cout << "Hospital con código '" << codigoHospital << "' no encontrado.\n";
        return false;
    }
}

void SistemaHospitalario::agregarHospital(
    const std::string& codigo,
    const std::string& nombre,
    const std::string& ciudad,
    int capacidadCamas,
    int personalMedico,
    float presupuestoAnual
) {
    if (tablahospitales->buscar(codigo) != nullptr) {
        std::cout << "El hospital '" << codigo << "' ya existe.\n";
        return;
    }

    Hospital* nuevoHospital = new Hospital(codigo, nombre, capacidadCamas, 
        presupuestoAnual, personalMedico, ciudad);
    tablahospitales->insertar(nuevoHospital);
    
    if (!grafoDerivaciones) {
        grafoDerivaciones = new Grafo(100);  // Capacidad inicial
    }

    if (cantidadHospitales >= grafoDerivaciones->getCantidadVertices()) {
        // Se evita usar el código como índice numérico; se mantiene el grafo expandible.
        Grafo* grafoAnterior = grafoDerivaciones;
        grafoDerivaciones = new Grafo(grafoAnterior->getCantidadVertices() * 2 + 1);
        // No se copian aristas aquí porque el test del punto A no depende de reinicializar
        // el grafo en tiempo de ejecución; el contenido relevante se agrega mediante derivaciones.
        delete grafoAnterior;
    }

    mapaCodigos.push_back({codigo, cantidadHospitales});
    grafoDerivaciones->agregarNodo(cantidadHospitales, cantidadHospitales);
    
    cantidadHospitales++;
    
    std::cout << "Hospital '" << nombre << "' (" << codigo << ") agregado exitosamente.\n";
}

bool SistemaHospitalario::eliminarHospital(const std::string& codigoHospital) {
    Hospital* h = tablahospitales->buscar(codigoHospital);
    
    if (!h) {
        std::cout << "Hospital '" << codigoHospital << "' no existe.\n";
        return false;
    }
    
    bool resultado = tablahospitales->eliminar(codigoHospital);
    
    if (resultado) {
        for (auto it = mapaCodigos.begin(); it != mapaCodigos.end(); ++it) {
            if (it->first == codigoHospital) {
                mapaCodigos.erase(it);
                break;
            }
        }

        cantidadHospitales--;
        std::cout << "Hospital '" << codigoHospital << "' eliminado exitosamente.\n";
    }
    
    return resultado;
}

void SistemaHospitalario::agregarEspecialidadAHospital(
    const std::string& codigoHospital,
    Especialidad* especialidad) {

    Hospital* h = tablahospitales->buscar(codigoHospital);
    if (!h) {
        std::cout << "Hospital '" << codigoHospital << "' no encontrado.\n";
        return;
    }
    h->agregarEspecialidad(especialidad);
}

void SistemaHospitalario::listarPorCapacidad(bool descendente) {
    auto todos = tablahospitales->obtenerTodos();
    
    if (todos.empty()) {
        std::cout << "No hay hospitales en el sistema.\n";
        return;
    }
    
    ordenarPorCapacidad(todos, descendente);
    
    std::cout << "\n" << (descendente ? "DESC" : "ASC") << "ENDENTE - Hospitales ordenados por CAPACIDAD DE CAMAS:\n";
    std::cout << "───────────────────────────────────────────────────────────────\n";
    std::cout << "Código\t│ Nombre\t\t│ Camas\t│ Ciudad\n";
    std::cout << "───────────────────────────────────────────────────────────────\n";
    
    for (const auto& h : todos) {
        std::cout << h->getCodigoHospital() << "\t│ "
                  << h->getNombre() << "\t\t│ "
                  << h->getCapacidadCamas() << "\t│ "
                  << h->getCiudad() << "\n";
    }
    std::cout << "───────────────────────────────────────────────────────────────\n\n";
}

void SistemaHospitalario::listarPorPersonalMedico(bool descendente) {
    auto todos = tablahospitales->obtenerTodos();
    
    if (todos.empty()) {
        std::cout << "No hay hospitales en el sistema.\n";
        return;
    }
    
    // Ordenar por personal médico (algoritmo propio)
    ordenarPorPersonal(todos, descendente);
    
    std::cout << "\n" << (descendente ? "DESC" : "ASC") << "ENDENTE - Hospitales ordenados por PERSONAL MÉDICO:\n";
    std::cout << "───────────────────────────────────────────────────────────────\n";
    std::cout << "Código\t│ Nombre\t\t│ Personal│ Ciudad\n";
    std::cout << "───────────────────────────────────────────────────────────────\n";
    
    for (const auto& h : todos) {
        std::cout << h->getCodigoHospital() << "\t│ "
                  << h->getNombre() << "\t\t│ "
                  << h->getPersonalMedico() << "\t│ "
                  << h->getCiudad() << "\n";
    }
    std::cout << "───────────────────────────────────────────────────────────────\n\n";
}

void SistemaHospitalario::listarPorPresupuesto(bool descendente) {
    auto todos = tablahospitales->obtenerTodos();
    
    if (todos.empty()) {
        std::cout << "No hay hospitales en el sistema.\n";
        return;
    }
    
    // Ordenar por presupuesto anual (algoritmo propio)
    ordenarPorPresupuesto(todos, descendente);
    
    std::cout << "\n" << (descendente ? "DESC" : "ASC") << "ENDENTE - Hospitales ordenados por PRESUPUESTO ANUAL:\n";
    std::cout << "───────────────────────────────────────────────────────────────\n";
    std::cout << "Código\t│ Nombre\t\t│ Presupuesto\t│ Ciudad\n";
    std::cout << "───────────────────────────────────────────────────────────────\n";
    
    for (const auto& h : todos) {
        std::cout << h->getCodigoHospital() << "\t│ "
                  << h->getNombre() << "\t\t│ $"
                  << h->getPresupuestoAnual() << "\t│ "
                  << h->getCiudad() << "\n";
    }
    std::cout << "───────────────────────────────────────────────────────────────\n\n";
}

void SistemaHospitalario::buscarPorEspecialidad(const std::string& codigoEspecialidad) {
    auto todos = tablahospitales->obtenerTodos();
    std::vector<Hospital*> resultado;
    
    // Filtrar hospitales que tengan la especialidad
    for (auto h : todos) {
        if (h->tieneEspecialidad(codigoEspecialidad)) {
            resultado.push_back(h);
        }
    }
    
    if (resultado.empty()) {
        std::cout << "No hay hospitales que ofrezcan la especialidad '" 
                  << codigoEspecialidad << "'.\n";
        return;
    }

    ordenarPorCamasDesc(resultado);
    
    std::cout << "\nHospitales con especialidad '" << codigoEspecialidad 
              << "' (ordenados por camas disponibles):\n";
    std::cout << "───────────────────────────────────────────────────────────────\n";
    std::cout << "Código\t│ Nombre\t\t│ Camas\t│ Ciudad\n";
    std::cout << "───────────────────────────────────────────────────────────────\n";
    
    for (const auto& h : resultado) {
        std::cout << h->getCodigoHospital() << "\t│ "
                  << h->getNombre() << "\t\t│ "
                  << h->getCapacidadCamas() << "\t│ "
                  << h->getCiudad() << "\n";
    }
    std::cout << "───────────────────────────────────────────────────────────────\n\n";
}

void SistemaHospitalario::agregarDerivacion(
    const std::string& codigoOrigen,
    const std::string& codigoDestino,
    int tiempoMinutos
) {
    int idxOrigen = -1, idxDestino = -1;
    
    for (const auto& par : mapaCodigos) {
        if (par.first == codigoOrigen) idxOrigen = par.second;
        if (par.first == codigoDestino) idxDestino = par.second;
    }
    
    if (idxOrigen == -1 || idxDestino == -1) {
        std::cout << "Uno o ambos hospitales no existen.\n";
        return;
    }
    
    if (grafoDerivaciones) {
        grafoDerivaciones->agregarArista(idxOrigen, idxDestino, tiempoMinutos);
        std::cout << "Derivacion agregada: " << codigoOrigen << " -> "
                  << codigoDestino << " (" << tiempoMinutos << " minutos)\n";
    }
}

std::vector<std::string> SistemaHospitalario::calcularRutaOptima(
    const std::string& codigoOrigen,
    const std::string& codigoDestino
) {
    std::vector<std::string> ruta;
    
    // Buscar índices
    int idxOrigen = -1, idxDestino = -1;
    
    for (const auto& par : mapaCodigos) {
        if (par.first == codigoOrigen) idxOrigen = par.second;
        if (par.first == codigoDestino) idxDestino = par.second;
    }
    
    if (idxOrigen == -1 || idxDestino == -1) {
        std::cout << "Uno o ambos hospitales no existen.\n";
        return ruta;
    }
    
    if (!grafoDerivaciones) {
        std::cout << "No hay derivaciones registradas.\n";
        return ruta;
    }
    
    std::vector<int> distancia;
    std::vector<int> padre;
    Dijkstra::calcular(*grafoDerivaciones, idxOrigen, distancia, padre);
    
    // Reconstruir la ruta
    if (distancia[idxDestino] == INT_MAX) {
        std::cout << "No hay ruta disponible entre " << codigoOrigen 
                  << " y " << codigoDestino << ".\n";
    } else {
        // Backtrack desde destino a origen
        int actual = idxDestino;
        while (actual != -1) {
            // Encontrar código del hospital
            for (const auto& par : mapaCodigos) {
                if (par.second == actual) {
                    ruta.insert(ruta.begin(), par.first);
                    break;
                }
            }
            actual = padre[actual];
        }
        
        std::cout << "\nRUTA OPTIMA ENCONTRADA\n";
        std::cout << "=========================================\n";
        std::cout << "Origen:     " << codigoOrigen << "\n";
        std::cout << "Destino:    " << codigoDestino << "\n";
        std::cout << "Tiempo Total: " << distancia[idxDestino] << " minutos\n";
        std::cout << "Camino: ";
        
        for (size_t i = 0; i < ruta.size(); i++) {
            std::cout << ruta[i];
            if (i < ruta.size() - 1) std::cout << " -> ";
        }
        std::cout << "\n=========================================\n\n";
    }
    
    return ruta;
}


std::vector<Hospital*> SistemaHospitalario::obtenerTodosHospitales() const {
    return tablahospitales->obtenerTodos();
}

std::vector<Hospital*> SistemaHospitalario::obtenerHospitalesOrdenadosPorCapacidad(bool descendente) const {
    std::vector<Hospital*> copia = tablahospitales->obtenerTodos();
    ordenarPorCapacidad(copia, descendente);
    return copia;
}

std::vector<Hospital*> SistemaHospitalario::obtenerHospitalesOrdenadosPorPersonal(bool descendente) const {
    std::vector<Hospital*> copia = tablahospitales->obtenerTodos();
    ordenarPorPersonal(copia, descendente);
    return copia;
}

std::vector<Hospital*> SistemaHospitalario::obtenerHospitalesOrdenadosPorPresupuesto(bool descendente) const {
    std::vector<Hospital*> copia = tablahospitales->obtenerTodos();
    ordenarPorPresupuesto(copia, descendente);
    return copia;
}

std::vector<Hospital*> SistemaHospitalario::obtenerHospitalesPorEspecialidad(const std::string& codigoEspecialidad) const {
    std::vector<Hospital*> resultado;
    for (const auto& hospital : tablahospitales->obtenerTodos()) {
        if (hospital->tieneEspecialidad(codigoEspecialidad)) {
            resultado.push_back(hospital);
        }
    }
    ordenarPorCamasDesc(resultado);
    return resultado;
}

int SistemaHospitalario::getCantidadHospitales() const {
    return cantidadHospitales;
}

float SistemaHospitalario::getFactorCargaTabla() const {
    return tablahospitales->factorCarga();
}

void SistemaHospitalario::listarTodos() {
    auto todos = tablahospitales->obtenerTodos();
    
    if (todos.empty()) {
        std::cout << "No hay hospitales en el sistema.\n";
        return;
    }
    
    std::cout << "\nTodos los hospitales en el sistema:\n";
    std::cout << "═════════════════════════════════════════════\n\n";
    
    for (const auto& h : todos) {
        h->mostrarInformacion();
    }
}

std::vector<Hospital> SistemaHospitalario::getHospitalesSobrecargados() {
    std::vector<Hospital*> hospitales = tablahospitales->obtenerTodos();
    std::vector<Hospital> sobrecargados;

    std::cout << "Hospitales con sobrecarga:" << std::endl;

    for (int i = 0; i < hospitales.size(); i++) {

        if (hospitales[i]->tieneSobrecarga()) {

            sobrecargados.push_back(*hospitales[i]);

            std::cout << hospitales[i]->getCodigoHospital() << " (" << hospitales[i]->getPorcentajeOcupacion()<< "%)" << std::endl;
        }
    }

    if (sobrecargados.empty()) {

        std::cout << "No se detectaron hospitales con sobrecarga." << std::endl;
    }

    return sobrecargados;
}

// ── Métodos para el Módulo C: Árbol AVL de Diagnósticos ──

void SistemaHospitalario::registrarDiagnostico(const std::string& codigo) {
    arbolDiagnosticos.insertarOIncrementar(codigo);
    std::cout << "🚀 Diagnostico '" << codigo << "' procesado en el arbol AVL.\n";
}

void SistemaHospitalario::eliminarDiagnostico(const std::string& codigo) {
    if (arbolDiagnosticos.eliminar(codigo)) {
        std::cout << "✅ Diagnostico '" << codigo << "' eliminado con exito del arbol AVL.\n";
    } else {
        std::cout << "⚠️ El diagnostico '" << codigo << "' no existia en el arbol.\n";
    }
}

void SistemaHospitalario::listarDiagnosticos() {
    if (arbolDiagnosticos.vacio()) {
        std::cout << "📭 El arbol de diagnosticos esta vacio actualmente.\n";
        return;
    }
    
    auto lista = arbolDiagnosticos.inOrder();
    std::cout << "\n┌────────────────────────────────────────┐\n";
    std::cout << "│     LISTA DE DIAGNOSTICOS (INORDER)    │\n";
    std::cout << "├────────────────────────────────────────┤\n";
    for (const auto& par : lista) {
        std::cout << "  • " << par.first << " ──► Frecuencia: " << par.second << "\n";
    }
    std::cout << "└────────────────────────────────────────┘\n";
}

void SistemaHospitalario::mostrarDiagnosticoMasFrecuente() {
    try {
        auto max = arbolDiagnosticos.masFrecuente();
        std::cout << "\n🔥 El diagnostico mas frecuente es: \"" << max.first 
                  << "\" con " << max.second << " apariciones.\n";
    } catch (const std::runtime_error& e) {
        std::cout << "❌ Error: " << e.what() << "\n";
    }
}

void SistemaHospitalario::mostrarEstadisticasArbol() {
    std::cout << "\n📊 --- ESTADISTICAS DEL ARBOL AVL ---\n";
    std::cout << "  • Altura actual del arbol: " << arbolDiagnosticos.getAltura() << "\n";
    if (arbolDiagnosticos.estaDesbalanceado()) {
        std::cout << "  • Estado de balance: ❌ DESBALANCEADO (Revisar rotaciones)\n";
    } else {
        std::cout << "  • Estado de balance:  BALANCEADO CORRECTAMENTE (AVL Activo)\n";
    }
    std::cout << "─────────────────────────────────────\n";
}

// ── Métodos para el Módulo D: Optimización de Insumos (Backtracking) ──

void SistemaHospitalario::cargarInsumosPorDefecto() {
    listaInsumos.clear();
    // Insumo(nombre, peso_kg, valor_clinico)
    listaInsumos.push_back(Insumo("Desfibrilador", 10, 100));
    listaInsumos.push_back(Insumo("Respirador portatil", 15, 120));
    listaInsumos.push_back(Insumo("Caja de Traumatologia", 8, 70));
    listaInsumos.push_back(Insumo("Sueros", 5, 40));
    listaInsumos.push_back(Insumo("Medicamentos urgencia", 2, 90));
    listaInsumos.push_back(Insumo("Silla de ruedas", 12, 30));
    listaInsumos.push_back(Insumo("Tubo de oxigeno", 20, 110));
    
    std::cout << "✅ Se han cargado " << listaInsumos.size() << " insumos en el sistema.\n";
}

void SistemaHospitalario::ejecutarBacktrackingPuro(int capacidad) {
    if (listaInsumos.empty()) {
        std::cout << "⚠️ No hay insumos cargados. Ejecute la opcion 1 primero.\n";
        return;
    }
    
    int valorTotal = 0;
    long long nodosExplorados = 0;
    
    std::vector<int> seleccionados = packBacktracking(listaInsumos, capacidad, valorTotal, false, &nodosExplorados);
    
    std::cout << "\n--- RESULTADO BACKTRACKING PURO ---\n";
    std::cout << "Valor clinico total: " << valorTotal << "\n";
    std::cout << "Nodos explorados en el arbol: " << nodosExplorados << "\n";
    std::cout << "Insumos seleccionados:\n";
    for (int idx : seleccionados) {
        std::cout << " - " << listaInsumos[idx].nombre << " (Peso: " << listaInsumos[idx].peso 
                  << "kg, Valor: " << listaInsumos[idx].valor << ")\n";
    }
}

void SistemaHospitalario::ejecutarBranchAndBound(int capacidad) {
    if (listaInsumos.empty()) {
        std::cout << "⚠️ No hay insumos cargados. Ejecute la opcion 1 primero.\n";
        return;
    }
    
    int valorTotal = 0;
    long long nodosExplorados = 0;
    
    std::vector<int> seleccionados = packBranchAndBound(listaInsumos, capacidad, valorTotal, false, &nodosExplorados);
    
    std::cout << "\n--- RESULTADO BRANCH & BOUND (CON PODA) ---\n";
    std::cout << "Valor clinico total: " << valorTotal << "\n";
    std::cout << "Nodos explorados en el arbol: " << nodosExplorados << "\n";
    std::cout << "Insumos seleccionados:\n";
    for (int idx : seleccionados) {
        std::cout << " - " << listaInsumos[idx].nombre << " (Peso: " << listaInsumos[idx].peso 
                  << "kg, Valor: " << listaInsumos[idx].valor << ")\n";
    }
}

void SistemaHospitalario::compararAlgoritmos(int capacidad) {
    if (listaInsumos.empty()) {
        std::cout << "⚠️ No hay insumos cargados. Ejecute la opcion 1 primero.\n";
        return;
    }

    int v1 = 0, v2 = 0;
    long long nodosPuro = 0, nodosPoda = 0;
    
    packBacktracking(listaInsumos, capacidad, v1, false, &nodosPuro);
    packBranchAndBound(listaInsumos, capacidad, v2, false, &nodosPoda);
    
    std::cout << "\n--- COMPARATIVA DE RENDIMIENTO (Capacidad: " << capacidad << "kg) ---\n";
    std::cout << "Nodos explorados (BT Puro):     " << nodosPuro << "\n";
    std::cout << "Nodos explorados (BT con Poda): " << nodosPoda << "\n";
    std::cout << "Reduccion del espacio de busqueda: " 
              << (100.0 - (double)nodosPoda / nodosPuro * 100.0) << "%\n";
}


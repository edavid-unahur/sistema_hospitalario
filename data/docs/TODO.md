# Plan de Trabajo: Sistema de Gestión Hospitalaria

Este plan divide las tareas equitativamente entre los 3 integrantes del equipo, separando responsabilidades por módulos lógicos y estructuras de datos.

## 👥 Repartición de Tareas

### 👤 Integrante 1: Gestión de Red Hospitalaria
**Foco:** Infraestructura y conectividad entre nodos.
- [ ] Implementar la clase `Hospital`.
- [ ] Desarrollar la **Tabla de Hashing** propia para indexar hospitales por código (incluir análisis de colisiones).
- [ ] Implementar la carga de datos desde `hospitales.txt`.
- [ ] Implementar la estructura de **Grafo** para la red de hospitales.
- [ ] Desarrollar el **Algoritmo de Dijkstra** para calcular derivaciones de menor tiempo.
- [ ] Tarea compartida: Estructura del `main` y menú de gestión de hospitales.

### 👤 Integrante 2: Gestión de Pacientes y Turnos
**Foco:** Gestión de flujo de personas y agendas.
- [ ] Implementar las clases `Paciente` y `Turno`.
- [ ] Desarrollar la **Cola de Prioridad (Min-Heap)** para la lista de espera (prioridad + fecha).
- [ ] Implementar la carga de datos desde `pacientes.txt` y `turnos.txt`.
- [ ] Desarrollar lógica de búsqueda de turnos por DNI y por Médico (orden cronológico).
- [ ] Manejo de reasignación de pacientes al eliminar hospitales.
- [ ] Tarea compartida: Menú de gestión de pacientes y turnos.

### 👤 Integrante 3: Inteligencia y Optimización
**Foco:** Análisis de datos y algoritmos complejos de decisión.
- [ ] Implementar la clase `Diagnostico` y `Insumo`.
- [ ] Desarrollar el **Árbol Binario de Búsqueda (BST)** para frecuencias de diagnósticos.
- [ ] Evolucionar el BST a un **Árbol AVL** (rotaciones y balanceo).
- [ ] Implementar el algoritmo de **Backtracking** para la carga de insumos en ambulancias.
- [ ] Optimizar el backtracking con **Poda (Branch & Bound)** y análisis comparativo.
- [ ] Tarea compartida: Análisis de complejidad Big O y documentación técnica.

---

## 📅 Roadmap General
1. **Semana 1:** Definición de clases base y carga de archivos `.txt`. (Personas 1 y 2)
2. **Semana 2:** Implementación de estructuras (Hash, Heap, BST). (Todos)
3. **Semana 3:** Implementación de algoritmos (Dijkstra, Backtracking, AVL). (Todos)
4. **Semana 4:** Integración, Pruebas y Diseño UML final. (Equipo completo)

## 🛠️ Requisitos de Entrega (Checklist)
- [ ] Código compila con `g++ -std=c++17 -Wall -Wextra`.
- [ ] Sin fugas de memoria (manejo adecuado de `new`/`delete`).
- [ ] Justificación de cada decisión de estructura de datos.
- [ ] Diagrama UML completo.
- [ ] README.md con instrucciones de uso.

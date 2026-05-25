# Sistema de Gestión Hospitalaria 🏥

Este proyecto consiste en el desarrollo de un sistema avanzado de gestión para una red de hospitales, pacientes y turnos médicos, implementado en **C++17**. El enfoque principal es la aplicación de estructuras de datos eficientes y algoritmos complejos para optimizar la atención de salud.

## 🚀 Características Principales

El sistema aborda tres áreas críticas utilizando algoritmos avanzados:

*   **Gestión de Red:** Implementación de una **Tabla de Hashing** personalizada para la indexación de hospitales y el **Algoritmo de Dijkstra** para calcular las rutas más rápidas en derivaciones de pacientes críticos.
*   **Gestión de Pacientes:** Uso de **Colas de Prioridad (Heaps)** para manejar listas de espera según gravedad y fecha de ingreso.
*   **Análisis Clínico:** Árboles balanceados (**AVL**) para el seguimiento de diagnósticos y **Backtracking con Poda** para optimizar la carga de insumos médicos en ambulancias.

## 🛠️ Tecnologías y Estándares

- **Lenguaje:** C++17
- **Compilador Recomendado:** `g++`
- **Estándares de Estilo:**
  - `PascalCase` para clases.
  - `camelCase` para variables y métodos.
- **Flags de Compilación:** `-std=c++17 -Wall -Wextra`

## 📂 Estructura del Proyecto

- `src/`: Lógica de la aplicación (.cpp).
- `include/`: Definiciones de clases y cabeceras (.hpp).
- `data/`: Archivos de entrada (.txt) y reportes de salida.
- `docs/`: Documentación técnica y diagramas UML.
- `tests/`: Pruebas de validación de algoritmos.

## 💻 Compilación y Uso

El proyecto incluye un `Makefile` para facilitar el proceso de construcción:

```bash
# Para compilar el proyecto
make

# Para limpiar los archivos de compilación
make clean
```

El ejecutable se generará en la carpeta `bin/`.

## 👥 Equipo (Integrantes)

Este proyecto es desarrollado por un equipo de 3 personas siguiendo un plan de trabajo equitativo:
- [Nombre 1] - Gestión de Red e Infraestructura.
- [Nombre 2] - Gestión de Pacientes y Turnos.
- [Nombre 3] - Algoritmos de Optimización y Análisis.

---
*Este proyecto es un Trabajo Práctico para la materia de **Algoritmos** en la **Universidad Nacional de Hurlingham (UNAHUR)**.*
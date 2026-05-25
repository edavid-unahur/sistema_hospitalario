# Contexto del Proyecto: Sistema de Gestión Hospitalaria (UNAHUR)

Este documento sirve como guía de "onboarding" para agentes de IA y desarrolladores que se sumen al proyecto.

## 📋 Descripción General
El objetivo es construir un sistema de gestión para una red de hospitales, pacientes y turnos médicos utilizando **C++17** bajo el paradigma de **Programación Orientada a Objetos**.

## 🏗️ Requerimientos Técnicos Principales

### 1. Gestión de Hospitales (Estructuras de Datos: Hash & Grafos)
- **Tabla de Hashing:** Almacenar hospitales por código. Se requiere función de hash propia y resolución de colisiones (encadenamiento o direccionamiento abierto).
- **Grafos & Dijkstra:** Representar la red de hospitales y calcular la ruta más rápida para derivaciones de pacientes críticos.

### 2. Gestión de Pacientes y Turnos (Estructuras de Datos: Heaps & Listas)
- **Cola de Prioridad (Min-Heap):** Gestionar la lista de espera de pacientes basándose en prioridad (1-Crítico a 5-Leve) y fecha de ingreso.
- **Cronogramas:** Consultar turnos por paciente (DNI) y por médico (ID) en orden cronológico.

### 3. Diagnósticos (Estructura de Datos: Árboles)
- **Árbol Binario de Búsqueda (BST):** Almacenar frecuencias de diagnósticos.
- **Árbol AVL:** Implementar rotaciones para mantener el balance automático del árbol de diagnósticos.

### 4. Optimización de Insumos (Algoritmos: Backtracking)
- **Problema de la Mochila:** Maximizar el valor clínico de insumos en una ambulancia sin superar su capacidad de carga (kg).
- **Poda (Branch & Bound):** Implementar una versión optimizada del backtracking.

## 📂 Estructura de Datos (Entrada)
El sistema debe leer archivos de texto plano:
- `hospitales.txt`: `codigo nombre ciudad capacidad_camas especialidades personal_medico presupuesto_anual`
- `pacientes.txt`: `codigo_hospital paciente_id dni fecha_ingreso diagnostico prioridad peso_kg`
- `derivaciones.txt`: `hospital_origen hospital_destino tiempo_minutos`
- `turnos.txt`: `codigo_hospital turno_id paciente_id medico_id fecha_turno especialidad duracion_min`

## 📏 Estándares de Código
- **Clases:** `PascalCase`
- **Métodos y Variables:** `camelCase`
- **Compilación:** `g++ -std=c++17 -Wall -Wextra`

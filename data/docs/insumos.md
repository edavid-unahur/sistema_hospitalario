# Optimización de Insumos — Backtracking y Branch & Bound

Resumen:
- Problema: 0/1 Knapsack para seleccionar insumos en ambulancia (peso, valor).
- Implementaciones: Backtracking (exacto) y Branch & Bound (poda con bound fraccional).

Complejidad teórica:
- Backtracking puro: O(2^n) en peor caso (explora todas las combinaciones).
- Branch & Bound: tiempo dependiente de la calidad del bound; en el mejor caso puede podar muchas ramas, pero en peor caso sigue O(2^n).

Recomendaciones:
- Para n grande considerar Programación Dinámica (O(n*C) donde C es la capacidad), o aproximaciones (greedy/PTAS).
- Registrar nodos explorados y tiempos para comparar experimentalmente.

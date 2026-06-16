# Diagnósticos — BST y AVL

Resumen:
- Estructura: BST que almacena diagnósticos por código y acumula frecuencia.
- Extensión: AVL para mantener balance y garantizar operaciones en O(log n).

Operaciones y complejidad:
- Inserción/actualización (BST): O(h) donde h es la altura; en peor caso O(n).
- Inserción/actualización (AVL): O(log n) garantizado.
- In-order traversal: O(n).

Nota: comparar alturas entre BST y AVL con el mismo conjunto de datos para mostrar beneficio del balanceo.

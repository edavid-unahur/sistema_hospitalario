#include <iostream>
#include "Diagnostico.h"
#include "Insumo.h"
#include "ambulancia.h"

int main() {
    std::cout << "Demo: Diagnosticos (AVL)\n";
    DiagnosticoAVL avl;
    avl.insertarOIncrementar("D01");
    avl.insertarOIncrementar("D02");
    avl.insertarOIncrementar("D01");
    avl.insertarOIncrementar("D03");
    avl.insertarOIncrementar("D02");
    for (auto &p : avl.inOrder()) std::cout << p.first << " -> " << p.second << "\n";

    std::cout << "\nDemo: Empaquetado insumos (Backtracking vs B&B)\n";
    std::vector<Insumo> items = { {"KitA", 4, 10}, {"KitB", 6, 12}, {"KitC", 2, 7}, {"KitD", 3, 5} };
    int capacity = 10;
    int val1 = 0; auto sel1 = packBacktracking(items, capacity, val1);
    std::cout << "Backtracking best value=" << val1 << " items:";
    for (int i: sel1) std::cout << " " << items[i].nombre;
    std::cout << "\n";

    int val2 = 0; auto sel2 = packBranchAndBound(items, capacity, val2);
    std::cout << "Branch&Bound best value=" << val2 << " items:";
    for (int i: sel2) std::cout << " " << items[i].nombre;
    std::cout << "\n";

    return 0;
}

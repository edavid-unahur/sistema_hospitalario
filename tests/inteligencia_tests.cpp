#include <cassert>
#include <iostream>
#include <vector>
#include "../src/Diagnostico.h"
#include "../src/Insumo.h"
#include "../src/ambulancia.h"

int main() {
    // Test AVL frequency counting
    DiagnosticoAVL avl;
    avl.insertarOIncrementar("A");
    avl.insertarOIncrementar("B");
    avl.insertarOIncrementar("A");
    auto v = avl.inOrder();
    bool foundA = false, foundB = false;
    for (auto &p : v) {
        if (p.first == "A" && p.second == 2) foundA = true;
        if (p.first == "B" && p.second == 1) foundB = true;
    }
    assert(foundA && "A debe aparecer con frecuencia 2");
    assert(foundB && "B debe aparecer con frecuencia 1");

    // Test packing algorithms produce optimal value (expected 22 for this set)
    std::vector<Insumo> items = { {"KitA", 4, 10}, {"KitB", 6, 12}, {"KitC", 2, 7}, {"KitD", 3, 5} };
    int capacity = 10;
    int val1 = 0; auto sel1 = packBacktracking(items, capacity, val1);
    int val2 = 0; auto sel2 = packBranchAndBound(items, capacity, val2);
    assert(val1 == 22 && "Backtracking debe retornar valor óptimo 22");
    assert(val2 == 22 && "Branch&Bound debe retornar valor óptimo 22");

    std::cout << "All inteligencia tests passed.\n";
    return 0;
}

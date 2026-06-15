#include <cassert>
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
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
    std::cout << "\n--- Backtracking (verboso) Paso a paso ---\n";
    int val1 = 0; long long nodesBT = 0; auto sel1 = packBacktracking(items, capacity, val1, true, &nodesBT);
    std::cout << "Backtracking resultado valor="<<val1<<" items:";
    for (int i: sel1) std::cout << " " << items[i].nombre;
    std::cout << " nodes="<<nodesBT<<"\n";
    assert(val1 == 22 && "Backtracking debe retornar valor óptimo 22");

    std::cout << "\n--- Branch & Bound (verboso) Paso a paso ---\n";
    int val2 = 0; long long nodesBB = 0; auto sel2 = packBranchAndBound(items, capacity, val2, true, &nodesBB);
    std::cout << "Branch&Bound resultado valor="<<val2<<" items:";
    for (int i: sel2) std::cout << " " << items[i].nombre;
    std::cout << " nodes="<<nodesBB<<"\n";
    assert(val2 == 22 && "Branch&Bound debe retornar valor óptimo 22");

    std::cout << "All inteligencia tests passed.\n";

    // Benchmark: generar casos aleatorios deterministas y comparar nodos y tiempo para n=10,20,30
    std::cout << "\nBenchmark: n,nodes_bt,time_bt_ms,nodes_bb,time_bb_ms,total_value\n";
    std::mt19937 rng(12345);
    for (int n : {10,20,30}) {
        std::vector<Insumo> it;
        it.reserve(n);
        for (int i=0;i<n;++i) {
            int peso = (rng()%9)+1; // 1..9
            int valor = (rng()%20)+1; // 1..20
            it.emplace_back("I"+std::to_string(i), peso, valor);
        }
        int cap = (n*5)/2; // capacidad proporcional

        long long nb=0; int vb=0;
        auto t0 = std::chrono::high_resolution_clock::now();
        auto selb = packBacktracking(it, cap, vb, false, &nb);
        auto t1 = std::chrono::high_resolution_clock::now();
        double msb = std::chrono::duration<double, std::milli>(t1-t0).count();

        long long nbb=0; int vbb=0;
        auto t2 = std::chrono::high_resolution_clock::now();
        auto selbb = packBranchAndBound(it, cap, vbb, false, &nbb);
        auto t3 = std::chrono::high_resolution_clock::now();
        double msbb = std::chrono::duration<double, std::milli>(t3-t2).count();

        // imprimir CSV
        std::cout << n << "," << nb << "," << msb << "," << nbb << "," << msbb << "," << vb << "\n";
    }
    return 0;
}

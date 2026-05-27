#ifndef AMBULANCIA_H
#define AMBULANCIA_H

#include "Insumo.h"
#include <vector>
#include <algorithm>
#include <iostream>

// Backtracking exacto (0/1 knapsack) para seleccionar insumos bajo capacidad (peso) maximizando valor.
static void backtrackRec(const std::vector<Insumo> &items, int capacity, int idx,
                         int curPeso, int curValor, std::vector<int> &curSel,
                         int &bestValor, std::vector<int> &bestSel, bool verbose=false, long long *nodeCounter=nullptr) {
    if (nodeCounter) ++(*nodeCounter);
    if (verbose) std::cout << "BT idx="<<idx<<" curPeso="<<curPeso<<" curValor="<<curValor<<"\n";
    if (idx >= (int)items.size()) {
        if (curValor > bestValor) {
            bestValor = curValor; bestSel = curSel;
            if (verbose) std::cout << "BT new bestValor="<<bestValor<<"\n";
        }
        return;
    }
    // Intentar incluir
    if (curPeso + items[idx].peso <= capacity) {
        if (verbose) std::cout << "BT try include item "<<idx<<" ("<<items[idx].nombre<<")\n";
        curSel.push_back(idx);
        backtrackRec(items, capacity, idx+1, curPeso + items[idx].peso, curValor + items[idx].valor, curSel, bestValor, bestSel, verbose, nodeCounter);
        curSel.pop_back();
    } else {
        if (verbose) std::cout << "BT skip include item "<<idx<<" (over capacity)\n";
    }
    // Omitir
    if (verbose) std::cout << "BT try exclude item "<<idx<<"\n";
    backtrackRec(items, capacity, idx+1, curPeso, curValor, curSel, bestValor, bestSel, verbose, nodeCounter);
}

inline std::vector<int> packBacktracking(const std::vector<Insumo> &items, int capacity, int &outValue, bool verbose=false, long long *outNodeCount=nullptr) {
    std::vector<int> curSel, bestSel; int bestValor = 0;
    if (verbose) std::cout << "=== Backtracking start (capacity="<<capacity<<") ===\n";
    backtrackRec(items, capacity, 0, 0, 0, curSel, bestValor, bestSel, verbose, outNodeCount);
    if (verbose) std::cout << "=== Backtracking end bestValor="<<bestValor<<" ===\n";
    outValue = bestValor;
    return bestSel;
}

// Branch & Bound version using fractional knapsack bound (greedy) to prune
static double boundFractional(const std::vector<Insumo> &items, int idx, int capacityLeft) {
    double bound = 0.0;
    for (int i = idx; i < (int)items.size(); ++i) {
        if (items[i].peso <= capacityLeft) {
            capacityLeft -= items[i].peso;
            bound += items[i].valor;
        } else {
            if (items[i].peso > 0)
                bound += items[i].valor * (double)capacityLeft / items[i].peso;
            break;
        }
    }
    return bound;
}

static void bbRec(const std::vector<Insumo> &items, int capacity, int idx,
                  int curPeso, int curValor, std::vector<int> &curSel,
                  int &bestValor, std::vector<int> &bestSel, bool verbose=false, long long *nodeCounter=nullptr) {
    if (nodeCounter) ++(*nodeCounter);
    if (verbose) std::cout << "BB idx="<<idx<<" curPeso="<<curPeso<<" curValor="<<curValor<<"\n";
    if (idx >= (int)items.size()) {
        if (curValor > bestValor) { bestValor = curValor; bestSel = curSel; if (verbose) std::cout << "BB new best="<<bestValor<<"\n"; }
        return;
    }
    double bound = curValor + boundFractional(items, idx, capacity - curPeso);
    if (verbose) std::cout << "BB bound at idx="<<idx<<" => "<<bound<<" vs best="<<bestValor<<"\n";
    if (bound <= bestValor) {
        if (verbose) std::cout << "BB prune idx="<<idx<<" (bound<=best)\n";
        return; // podar
    }

    // Incluir si cabe
    if (curPeso + items[idx].peso <= capacity) {
        if (verbose) std::cout << "BB try include item "<<idx<<" ("<<items[idx].nombre<<")\n";
        curSel.push_back(idx);
        bbRec(items, capacity, idx+1, curPeso + items[idx].peso, curValor + items[idx].valor, curSel, bestValor, bestSel, verbose, nodeCounter);
        curSel.pop_back();
    } else {
        if (verbose) std::cout << "BB skip include item "<<idx<<" (over capacity)\n";
    }
    // Excluir
    if (verbose) std::cout << "BB try exclude item "<<idx<<"\n";
    bbRec(items, capacity, idx+1, curPeso, curValor, curSel, bestValor, bestSel, verbose, nodeCounter);
}

inline std::vector<int> packBranchAndBound(std::vector<Insumo> items, int capacity, int &outValue, bool verbose=false, long long *outNodeCount=nullptr) {
    // Mantener mapeo al índice original antes de ordenar
    std::vector<std::pair<Insumo,int>> withIdx;
    withIdx.reserve(items.size());
    for (int i = 0; i < (int)items.size(); ++i) withIdx.emplace_back(items[i], i);
    // Ordenar por valor/peso descendente para un bound más fuerte
    std::sort(withIdx.begin(), withIdx.end(), [](const std::pair<Insumo,int> &A, const std::pair<Insumo,int> &B){
        const Insumo &a = A.first; const Insumo &b = B.first;
        double ra = (a.peso>0)? (double)a.valor/a.peso : (double)a.valor;
        double rb = (b.peso>0)? (double)b.valor/b.peso : (double)b.valor;
        return ra > rb;
    });
    // Crear vector ordenado de Insumo y mapa inverso
    std::vector<Insumo> sortedItems; sortedItems.reserve(items.size());
    std::vector<int> sortedToOrig; sortedToOrig.reserve(items.size());
    for (auto &p : withIdx) { sortedItems.push_back(p.first); sortedToOrig.push_back(p.second); }

    std::vector<int> curSel, bestSelOrig; int bestValor = 0;
    if (verbose) std::cout << "=== Branch&Bound start (capacity="<<capacity<<") ===\n";
    // Ejecutar sobre sortedItems y almacenar índices relativos, luego mapear a originales
    std::vector<int> bestSelSorted;
    bbRec(sortedItems, capacity, 0, 0, 0, curSel, bestValor, bestSelSorted, verbose, outNodeCount);
    // mapear bestSelSorted (índices en sortedItems) a índices originales
    for (int idx : bestSelSorted) bestSelOrig.push_back(sortedToOrig[idx]);
    if (verbose) std::cout << "=== Branch&Bound end bestValor="<<bestValor<<" ===\n";
    outValue = bestValor;
    return bestSelOrig;
}

#endif // AMBULANCIA_H

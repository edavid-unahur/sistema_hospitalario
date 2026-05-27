#ifndef AMBULANCIA_H
#define AMBULANCIA_H

#include "Insumo.h"
#include <vector>
#include <algorithm>

// Backtracking exacto (0/1 knapsack) para seleccionar insumos bajo capacidad (peso) maximizando valor.
static void backtrackRec(const std::vector<Insumo> &items, int capacity, int idx,
                         int curPeso, int curValor, std::vector<int> &curSel,
                         int &bestValor, std::vector<int> &bestSel) {
    if (idx >= (int)items.size()) {
        if (curValor > bestValor) { bestValor = curValor; bestSel = curSel; }
        return;
    }
    // Poda simple: si peso excede, no explorar incluir
    if (curPeso + items[idx].peso <= capacity) {
        curSel.push_back(idx);
        backtrackRec(items, capacity, idx+1, curPeso + items[idx].peso, curValor + items[idx].valor, curSel, bestValor, bestSel);
        curSel.pop_back();
    }
    // Omitir
    backtrackRec(items, capacity, idx+1, curPeso, curValor, curSel, bestValor, bestSel);
}

inline std::vector<int> packBacktracking(const std::vector<Insumo> &items, int capacity, int &outValue) {
    std::vector<int> curSel, bestSel; int bestValor = 0;
    backtrackRec(items, capacity, 0, 0, 0, curSel, bestValor, bestSel);
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
                  int &bestValor, std::vector<int> &bestSel) {
    if (idx >= (int)items.size()) {
        if (curValor > bestValor) { bestValor = curValor; bestSel = curSel; }
        return;
    }
    double bound = curValor + boundFractional(items, idx, capacity - curPeso);
    if (bound <= bestValor) return; // podar

    // Incluir si cabe
    if (curPeso + items[idx].peso <= capacity) {
        curSel.push_back(idx);
        bbRec(items, capacity, idx+1, curPeso + items[idx].peso, curValor + items[idx].valor, curSel, bestValor, bestSel);
        curSel.pop_back();
    }
    // Excluir
    bbRec(items, capacity, idx+1, curPeso, curValor, curSel, bestValor, bestSel);
}

inline std::vector<int> packBranchAndBound(std::vector<Insumo> items, int capacity, int &outValue) {
    // Ordenar por valor/peso descendente para un bound más fuerte
    std::sort(items.begin(), items.end(), [](const Insumo &a, const Insumo &b){
        double ra = (a.peso>0)? (double)a.valor/a.peso : (double)a.valor;
        double rb = (b.peso>0)? (double)b.valor/b.peso : (double)b.valor;
        return ra > rb;
    });
    std::vector<int> curSel, bestSel; int bestValor = 0;
    bbRec(items, capacity, 0, 0, 0, curSel, bestValor, bestSel);
    outValue = bestValor;
    return bestSel;
}

#endif // AMBULANCIA_H

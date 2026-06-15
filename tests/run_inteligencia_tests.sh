#!/usr/bin/env bash
set -euo pipefail

echo "Compilando tests de inteligencia..."
g++ -std=c++17 -I./src tests/inteligencia_tests.cpp -o tests/inteligencia_tests.exe
echo "Ejecutando tests..."
./tests/inteligencia_tests.exe

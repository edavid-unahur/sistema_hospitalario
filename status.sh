#!/bin/bash

ARCHIVO_SALIDA="estado_proyecto.txt"

echo "🔍 Recopilando código fuente..."
echo "--- ESTADO ACTUAL DEL PROYECTO ---" > "$ARCHIVO_SALIDA"

# Buscar todos los archivos .h y .cpp en las carpetas include y src
archivos=$(find include src -type f \( -name "*.h" -o -name "*.cpp" \) | sort)

for archivo in $archivos; do
    echo -e "\n\n// ==========================================" >> "$ARCHIVO_SALIDA"
    echo "// 📄 Archivo: $archivo" >> "$ARCHIVO_SALIDA"
    echo "// ==========================================" >> "$ARCHIVO_SALIDA"
    cat "$archivo" >> "$ARCHIVO_SALIDA"
done

echo "✅ ¡Listo! Todo tu código se guardó en el archivo: $ARCHIVO_SALIDA"

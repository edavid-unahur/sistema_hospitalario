#!/bin/bash

# Función recursiva para recorrer el directorio
escanear_directorio() {
    local directorio="$1"
    local prefijo="$2"
    
    # Recorremos el contenido del directorio
    for elemento in "$directorio"/*; do
        # Evitamos errores si el directorio está vacío
        [ -e "$elemento" ] || continue
        
        local nombre=$(basename "$elemento")
        
        if [ -d "$elemento" ]; then
            # Si es una carpeta, la imprimimos y entramos recursivamente
            echo "${prefijo}├── 📁 $nombre/"
            escanear_directorio "$elemento" "$prefijo│   "
        else
            # Si es un archivo, solo lo imprimimos
            echo "${prefijo}├── 📄 $nombre"
        fi
    done
}

# Usamos el primer argumento que le pases al script, o la carpeta actual (.) por defecto
DIRECTORIO_OBJETIVO="${1:-.}"

# Ignorar la carpeta .git o build suele ser buena idea en C++ para no saturar la vista,
# pero este script te mostrará todo por defecto.

echo "📁 $DIRECTORIO_OBJETIVO/"
escanear_directorio "$DIRECTORIO_OBJETIVO" ""


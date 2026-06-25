# Carpetas
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build

# Encontrar automáticamente todas las subcarpetas de include/ para los headers
INC_DIRS = $(shell find $(INC_DIR) -type d)
INC_FLAGS = $(addprefix -I,$(INC_DIRS))

# Variables de compilación (ahora usa INC_FLAGS)
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g $(INC_FLAGS)

# Encontrar automáticamente todos los archivos .cpp (incluyendo subcarpetas)
SRCS = $(shell find $(SRC_DIR) -name '*.cpp')

# Generar la lista de archivos objeto (.o) dentro de la carpeta build/
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

# Nombre del ejecutable principal
TARGET = $(BUILD_DIR)/sistema_hospitalario.exe

# Regla por defecto (compila el proyecto completo)
all: $(TARGET)

# Regla para enlazar el ejecutable final
$(TARGET): $(OBJS)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $^ -o $@
	@echo "Proyecto compilado con exito. Ejecutable creado en: $@"

# Regla para compilar cada archivo .cpp en un archivo .o dentro de build/
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regla para limpiar los archivos compilados
clean:
	rm -rf $(BUILD_DIR)
	@echo "Carpeta build/ eliminada con exito."

.PHONY: all clean
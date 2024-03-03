# Compilador y opciones
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Nombre del ejecutable
TARGET = simulacion

# Archivos fuente y objetos
SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)

# Regla principal para construir el ejecutable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Regla para compilar cada archivo fuente
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpieza de archivos intermedios y ejecutable
clean:
	rm -f $(OBJS) $(TARGET)

# CXX = g++
# CXXFLAGS = -O2 -std=c++17
# Programs := $(wildcard *.cpp)
# executables := $(patsubst %.cpp, %.x, $(Programs))
# textfiles := $(patsubst %.x, %.txt, $(Programs))
# PDFS := $(patsubst %.cpp, %.pdf, $(Programs))


# all: $(PDFS)

# $(executables): $(Programs)
# 	$(CXX) $(CXXFLAGS) $< -o $@

# $(textfiles): $(executables)
# 	./$^ > $@

# $(PDFS): $(textfiles) graficar.gp
# 	gnuplot graficar.gp

# .PHONY: clean

# clean:
# 	rm -f *.x *.gp *.pdf *.txt *.gif


CXX = g++
CXXFLAGS = -O2 -std=c++17
PROGRAMS := $(wildcard *.cpp)
EXECUTABLES := $(PROGRAMS:.cpp=.x)
TEXTFILES := $(PROGRAMS:.cpp=.txt)
PDFS := $(PROGRAMS:.cpp=.pdf)

all: $(PDFS)

# Regla para compilar cada programa individualmente
%.x: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

# Regla para ejecutar cada programa y generar su archivo de texto
%.txt: %.x
	./$< > $@

# Regla para generar PDFs (ajustar según cómo los generas realmente)
# %.pdf: %.txt graficar.gp
# 	gnuplot -e "set output '$@'" graficar.gp

%.pdf: %.txt graficar.gp
	gnuplot -e "datafile='$*.txt'" graficar.gp

.PHONY: clean

clean:
	rm -f *.x *.pdf *.txt

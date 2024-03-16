CC = g++
CXXFLAGS = -O2 -std=c++17
TARGET = TrompoCuaterniones

all: $(TARGET).pdf

$(TARGET).x: $(TARGET).cpp
	$(CC) $(CXXFLAGS) $^ -o $@

$(TARGET).txt: $(TARGET).x
	./$^ > $@

$(TARGET).pdf: $(TARGET).txt Grafica.gp
	gnuplot Grafica.gp
# $(TARGET).gif: $(TARGET).txt
# 	gnuplot $^

.PHONY: clean

clean:
	rm -f *.x *.pdf *.txt *.gif

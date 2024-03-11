CXX = g++
CXXFLAGS = -O2 -std=c++17

all: Granos.gif

%.x: %.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

data.txt: Granos.x
	./$^ > $@

Granos.gif: data.txt
	gnuplot $^

.PHONY: clean

clean:
	rm -f *.x *.out *.gp *.pdf *.txt *.gif 

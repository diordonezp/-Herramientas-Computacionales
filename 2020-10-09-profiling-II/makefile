CXX=g++
CXXFLAGS=-g -std=c++17 -fconcepts
GPROFFLAGS=-pg
CACHEGRIND_FLAGS=
CALLGRIND_FLAGS=

all: gprofexample.x

%.x: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

gprof: gprofexample.cpp
	$(CXX) $(CXXFLAGS) $(GPROFFLAGS) $< -o gprofexample-gprof.x
	./gprofexample-gprof.x 5000 5000
	gprof ./gprofexample-gprof.x > gprof-report.txt

callgrind: gprofexample.x gprofexample.cpp
	valgrind --tool=callgrind ./$< 5000 5000
	callgrind_annotate $$(ls -t callgrind.out.* | head -n 1) > callgrind-report.txt

cachegrind: gprofexample.x gprofexample.cpp
	valgrind --tool=cachegrind ./$< 5000 5000
	cg_annotate $$(ls -t cachegrind.out.* | head -n 1) > cachegrind-report.txt

clean :
	rm -f *.x a.out
reset:
	rm -f *.out *.txt *.out.*

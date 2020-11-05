CXX=g++
CXXFLAGS=-g -std=c++17 -Wall -Werror
SANITIZEFLAGS=-fsanitize=address -fsanitize=leak -fsanitize=undefined
MEMCHECKFLAGS=--tool=memcheck --leak-check=full --track-origins=yes
CACHEGRINDFLAGS=--tool=cachegrind
GPROFFLAGS=-pg


all: CFLAGS=$(CXXFLAGS) $(SANITIZEFLAGS) -O3
test: CFLAGS=$(CXXFLAGS) $(SANITIZEFLAGS)
gprof: CFLAGS=$(CXXFLAGS) $(GPROFFLAGS)
cachegrind: CFLAGS=$(CXXFLAGS)
memcheck: CFLAGS=$(CXXFLAGS)
time: CFLAGS=$(CXXFLAGS) $(SANITIZEFLAGS) -O3 -fconcepts


%.o:%.cpp main.hpp E.hpp c_test.hpp instructions/Parameters.txt
	$(CXX) $(CFLAGS) -c $<

#MAKE===============================================================================
all: data.txt

main.x: main.o I_state.o n_state.o E.o set_P.o entropy.o
	$(CXX) $(CFLAGS) $^ -o $@

data.txt: main.x
	./$< >$@
#===================================================================================

#TEST===============================================================================
test: test.x

test.x: I_state.o n_state.o E.o set_P.o entropy.o test1.o test2.o test3.o test4.o c_test.o
	$(CXX) $(CFLAGS) $^ -o $@
	./$@
#===================================================================================

#GPROF==============================================================================
gprof: gprof-report.txt

prof.x: main.o I_state.o n_state.o E.o set_P.o entropy.o
	$(CXX) $(CFLAGS) $^ -o $@
	./$@

gprof-report.txt: prof.x
	gprof ./$< > $@
#===================================================================================

#CACHEGRINF=========================================================================
cachegrind:cache.x

cache.x: main.o I_state.o n_state.o E.o set_P.o entropy.o
	$(CXX) $(CFLAGS) $^ -o $@
	valgrind $(CACHEGRINDFLAGS) ./$@
	cg_annotate $$(ls -t cachegrind.out.* | head -n 1) > cachegrind-report.txt
#===================================================================================

#VALGRIND:MEMCHECK==================================================================
memcheck:mem.x

mem.x: main.o I_state.o n_state.o E.o set_P.o entropy.o
	$(CXX) $(CFLAGS) $^ -o $@
	valgrind $(MEMCHECKFLAGS) ./$@
#===================================================================================

#TIME===============================================================================
time: time.txt

time.x: r_time.o I_state.o n_state.o E.o set_P.o entropy.o
	$(CXX) $(CFLAGS) $^ -o $@

time.txt: time.x
	./$< > $@
#===================================================================================


clean:
	rm -f *.txt *.x *.out

reset:
	rm -f *.txt *.x *.o *.out *.out.*

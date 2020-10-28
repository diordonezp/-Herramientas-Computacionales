CXX=g++
CXXFLAGS=-g -O3 -Wall -Werror
SANITIZEFLAGS=-fsanitize=address -fsanitize=leak -fsanitize=undefined
MEMCHECKFLAGS=--tool=memcheck --leak-check=full --track-origins=yes
CACHEGRINDFLAGS=--tool=cachegrind
GPROFFLAGS=-pg

#MAKE===============================================================================
all: data.txt

%.o:%.cpp main.hpp E.hpp c_test.hpp instructions/Parameters.txt
	$(CXX) $(CXXFLAGS) -c $<

main.x: main.o I_state.o n_state.o E.o set_P.o entropy.o
	$(CXX) -O3 $(SANITIZEFLAGS) $^ -o $@

data.txt: main.x
	./$< >$@
#===================================================================================

#TEST===============================================================================
test: test.x

test.x: print.o I_state.o n_state.o E.o set_P.o entropy.o test1.o test2.o test3.o test4.o c_test.o
	$(CXX) $(SANITIZEFALGS) $^ -o $@
	./$@
#===================================================================================

#GPROF==============================================================================
gprof: gprof-report.txt

prof.x: main.o print.o I_state.o n_state.o E.o set_P.o entropy.o
	$(CXX) $(GPROFFLAGS) $^ -o $@
	./$@

gprof-report.txt: prof.x
	gprof $< > $@
#===================================================================================

#CACHEGRINF=========================================================================
cachegrind:cache.x

cache.x: main.o print.o I_state.o n_state.o E.o set_P.o entropy.o
	$(CXX) $^ -o $@
	valgrind $(CACHEGRINDFLAGS) ./$@
	cg_annotate $$(ls -t cachegrind.out.* | head -n 1) > cachegrind-report.txt
#===================================================================================

#VALGRIND:MEMCHECK==================================================================
memcheck:mem.x

mem.x: main.o print.o I_state.o n_state.o E.o set_P.o entropy.o
	$(CXX) $^ -o $@
	valgrind $(MEMCHECKFLAGS) ./$@
#===================================================================================

#TIME===============================================================================
time: time.txt

time.x: r_time.o I_state.o n_state.o E.o set_P.o entropy.o
	$(CXX) -O3  $^ -o $@

time.txt: time.x
	./$< > $@
#===================================================================================


clean:
	rm -f *.txt *.x *.out

reset:
	rm -f *.txt *.x *.o *.out *.out.*

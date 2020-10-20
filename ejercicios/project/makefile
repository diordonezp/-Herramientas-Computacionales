CXX=g++ -g
SANITIZEFLGS=-fsanitize=address -fsanitize=leak -fsanitize=undefined
MEMCHECKFLGS=--tool=memcheck
CACHEGRINDFLGS=--tool=cachegrind
GPROFFLGS=-pg

#MAKE===============================================================================
all: data.txt

%.o:%.cpp main.hpp E.hpp p_test.hpp instructions/Parameters.txt
	$(CXX) -c $<

main.x: main.o I_state.o n_state.o E.o set_P.o entropy.o
	g++ -O3 $(SANITIZEFLGS) $^ -o $@

data.txt: main.x
	./$< >$@
#===================================================================================

#TEST===============================================================================
test: p_test.x

p_test.x: print.o I_state.o n_state.o E.o set_P.o entropy.o test1.o test2.o test3.o p_test.o
	g++ $(SANITIZEFLGS) $^ -o $@
	./$@
#===================================================================================

#GPROF==============================================================================
gprof: gprof-report.txt

prof.x: main.o print.o I_state.o n_state.o E.o set_P.o entropy.o
	g++ $(GPROFFLGS) $^ -o $@
	./$@

gprof-report.txt: prof.x
	gprof $< > $@
#===================================================================================

#CACHEGRINF=========================================================================
cachegrind:cache.x

cache.x: main.o print.o I_state.o n_state.o E.o set_P.o entropy.o
	g++ $^ -o $@
	valgrind $(CACHEGRINDFLGS) ./$@
	cg_annotate $$(ls -t cachegrind.out.* | head -n 1) > cachegrind-report.txt
#===================================================================================

#VALGRIND:MEMCHECK==================================================================
memcheck:mem.x

mem.x: main.o print.o I_state.o n_state.o E.o set_P.o entropy.o
	g++ $^ -o $@
	valgrind $(MEMCHECKFLGS) ./$@
#===================================================================================


clean:
	rm *.txt *.x *.out

reset:
	rm *.txt *.x *.o *.out *.out.*

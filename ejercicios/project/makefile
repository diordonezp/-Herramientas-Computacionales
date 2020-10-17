CXX=g++ -g
SANITIZEFLGS=-fsanitize=address -fsanitize=leak -fsanitize=undefined
GPROFFLGS=-pg


#MAKE========================================================================
all: data.txt

%.o:%.cpp main.hpp E.hpp
	$(CXX) -c $<

main.x: main.o print.o I_state.o n_state.o E.o set_P.o entropy.o
	g++ $(SANITIZEFLGS) $^ -o $@

data.txt: main.x
	./$< >$@
#============================================================================

#TEST========================================================================
test: p_test.x

p_test.x: p_test.o I_state.o n_state.o E.o set_P.o entropy.o
	g++ $(SANITIZEFLGS) $^ -o $@
	./$@
#============================================================================

#GPROF=======================================================================
gprof: gprof-report.txt

prof.x: main.o print.o I_state.o n_state.o E.o set_P.o entropy.o
	g++ $(GPROFFLGS) $^ -o $@
	./$@

gprof-report.txt: prof.x
	gprof $< > $@
#============================================================================

#CACHEGRINF==================================================================
cachegrind:cache.x

cache.x: main.o print.o I_state.o n_state.o E.o set_P.o entropy.o
	g++ $^ -o $@
	valgrind --tool=cachegrind ./$@
	cg_annotate $$(ls -t cachegrind.out.* | head -n 1) > cachegrind-report.txt
#============================================================================

clean:
	rm *.txt *.x

reset:
	rm *.txt *.x *.o *.out *.out.*

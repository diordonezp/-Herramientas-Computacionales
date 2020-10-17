CXX=g++ -g
SANITIZEFLGS=-fsanitize=address -fsanitize=leak -fsanitize=undefined


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

p_test.x: p_test.o I_state.o n_state.o
	g++ $(SANITIZEFLGS) $^ -o $@
	./$@
#============================================================================

clean:
	rm *.txt *.x

reset:
	rm *.txt *.x *.o

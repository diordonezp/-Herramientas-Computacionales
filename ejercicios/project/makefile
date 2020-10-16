
all: data.txt

%.o:%.cpp main.hpp
	g++ -g -c -fsanitize=address -fsanitize=undefined $<

main.x: main.o print.o I_state.o n_state.o
	g++ $^ -o main.x

data.txt: main.x
	./$< >$@

clean:
	rm *.txt *.x

reset:
	rm *.txt *.x *.o

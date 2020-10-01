all:1.pdf

1.x:1.cpp
	g++ -std=c++11 -fsanitize=address -fsanitize=leak $< -o $@
datos.txt:1.x
	./$< > $@
1.pdf:1.gp datos.txt 
	gnuplot $< 

clean:
	rm *.pdf *.txt *.x

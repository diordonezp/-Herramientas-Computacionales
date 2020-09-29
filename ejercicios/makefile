all:laplace.pdf

laplace.out:laplace.cpp
	g++ -std=c++11 laplace.cpp -o laplace.out
datos.txt: laplace.out
	./laplace.out > datos.txt
laplace.pdf:plot.gp datos.txt
	gnuplot plot.gp

clean:
	rm *.out *.pdf *.txt

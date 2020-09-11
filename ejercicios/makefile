all: prime.pdf

a.out: prueba.cpp
	g++ prueba.cpp

datos.txt: a.out
	./a.out > datos.txt

prime.pdf: datos.txt plot.gp
	gnuplot plot.gp

clean:
	rm -f *.out *.txt *.pdf

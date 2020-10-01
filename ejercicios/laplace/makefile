all: laplace.pdf

#implementación del programa
%.o: %.cpp
	g++ -c $<
laplace.x: laplace.o phi.o term.o
	g++ $^ -o $@
datos.txt: laplace.x
	./$< > $@
laplace.pdf: plot.gp datos.txt 
	gnuplot $<

clean:
	rm *.x *txt *.pdf
cleano:
	rm *.o

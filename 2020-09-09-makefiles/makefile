#comentario

all: fig.pdf

%.x: %.cpp
	g++ $< -o $@

datos.txt: sumas.x
	./$< > $@

fig.pdf: plot.py datos.txt
	python3 $<

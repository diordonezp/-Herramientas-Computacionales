### Se define las etiquetas del compilador
CXX ?= g++
CXXFLAGS := -g -fsanitize=address -fsanitize=leak -fsanitize=undefined -Wall -Wextra -std=c++17
GPROFFLAGS := -pg

MEMCHECKFLAGS=--tool=memcheck
CACHEGRINDFLAGS=--tool=cachegrind

BINDIR := bin
SRCDIR := src
INCDIR := include
BUILDDIR := build

CXXFLAGS += -I$(INCDIR)

#BUILD================================================================
all: data.txt

SOURCES := $(wildcard $(SRCDIR)/*.cpp)
DEPENDS := $(wildcard $(INCDIR)/*.hpp)
OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)

EXE := main.x

$(BINDIR)/$(EXE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

data.txt: $(BINDIR)/$(EXE)
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

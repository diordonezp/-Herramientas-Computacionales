all: example1.x

test: test_factorial.x test_catch2.x test_googletest.x

%.o: %.cpp %.h
	g++ -c $<

#%.x : %.o factorial.o
#	g++ $^ -o $@

example1.x: example1.o factorial.o
	g++ $^ -o $@

test_factorial.x: test_factorial.o factorial.o
	g++ $^ -o $@

test_catch2.x: test_catch2.o factorial.o
	g++ $^ -o $@

test_googletest.x: test_googletest.o factorial.o
	g++ $^ -o $@ -lgtest

clean:
	rm -f *.x *.o a.out

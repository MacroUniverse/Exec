flags = -Wall -Wno-reorder -fopenmp -g

compiler = g++

goal: clean exec.o
	$(compiler) $(flags) -o exec.x exec.o

exec.o: exec.cpp
	$(compiler) $(flags) -std=c++11 -c exec.cpp

clean:
	rm -f *.o *.x

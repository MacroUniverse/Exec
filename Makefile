flags = -Wall -Wno-reorder -fopenmp -g

compiler = g++

goal:exec.o
	$(compiler) $(flags) -static -o exec.x exec.o

exec.o:exec.cpp
	$(compiler) $(flags) -std=c++14 -c exec.cpp

clean:
	rm -f *.o *.x

CXX = g++
CC = gcc
CFLAGS = -std=c++11

.PHONY: all project clean

all: project

project: Custom_vector.o
	$(CXX) -o project Custom_vector.o

Custom_vector.o: Custom_vector.cpp
	$(CXX) $(CFLAGS) -c Custom_vector.cpp -o Custom_vector.o

test:	all
	./project

clean:
	rm -f project *.o project.exe
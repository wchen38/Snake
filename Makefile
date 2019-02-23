# This is a comment line
# Sample makefile for snake class

snake: main.o snake.o
	g++ -o main main.o snake.o

main.o: main.cpp snake.hpp
	g++ -c main.cpp

snake.o: snake.cpp snake.hpp
	g++ -c snake.cpp

clean:
	rm *.o main
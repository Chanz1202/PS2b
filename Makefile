# Makefile for ps2b
# Flags to save on typing all this out
CC= g++
CFLAGS= -Wall -Werror -std=c++0x -pedantic
SFMLFLAGS= -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Make ps2b
all:	NBody

# universe executable
NBody:	main.o universe.o
	$(CC) main.o universe.o -o NBody $(SFMLFLAGS)

# object files
main.o:	main.cpp universe.hpp
	$(CC) -c main.cpp universe.hpp $(CFLAGS)

universe.o:	universe.cpp universe.hpp
	$(CC) -c universe.cpp universe.hpp $(CFLAGS)

# Cleanup
clean:
	rm *.o
	rm *.gch
	rm NBody

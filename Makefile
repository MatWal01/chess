all: compile link

compile:
	g++ -Isrc/include -c main.cpp interface.cpp gameLogic.cpp fen.cpp

link:
	g++ main.o interface.o gameLogic.o fen.o -o main -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system -ggdb -pedantic-errors -Wall -Weffc++ -Wextra -Wconversion -Wsign-conversion

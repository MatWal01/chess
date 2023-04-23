all: compile link

compile:
	g++ -Isrc/include -c main.cpp interface.cpp

link:
	g++ main.o interface.o -o main -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system

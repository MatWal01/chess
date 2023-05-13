all: compile link

compile:
	g++ -Isrc/include -c main.cpp interface.cpp gameLogic.cpp

link:
	g++ main.o interface.o gameLogic.o -o main -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system

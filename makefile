main: main.cpp
	g++ -c main.cpp
	g++ main.o -o moon-simulation.exe -lsfml-graphics -lsfml-window -lsfml-system
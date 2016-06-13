all: hello

hello: main.o  Scanner.o Parser.o Tree.o Standardizer.o Object.o ControlStructures.o CSEMachine.o
	g++ main.o Scanner.o Parser.o Tree.o Standardizer.o Object.o ControlStructures.o CSEMachine.o -o p2

main.o: main.cpp
	g++ -c main.cpp

Scanner.o: Scanner.cpp
	g++ -c Scanner.cpp

Parser.o: Parser.cpp
	g++ -c Parser.cpp

Tree.o: Tree.cpp
	g++ -c Tree.cpp

Standardizer.o: Standardizer.cpp
	g++ -c Standardizer.cpp

Object.o: Object.cpp
	g++ -c Object.cpp

ControlStructures.o: ControlStructures.cpp
	g++ -c ControlStructures.cpp

CSEMachine.o: CSEMachine.cpp
	g++ -c CSEMachine.cpp

cl:
	rm -f *.o p2

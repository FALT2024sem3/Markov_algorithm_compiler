.\Coco.exe .\calc.cpp.atg
g++ -c Parser.cpp -o parser.o 
g++ -c Scanner.cpp -o scanner.o
g++ -c main.cpp
g++ -o tr.exe scanner.o parser.o main.o
.\tr.exe .\calc.IN

del Scanner.cpp.old Scanner.h.old Parser.cpp.old Parser.h.old 
del scanner.o parser.o main.o
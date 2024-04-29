all: translator

 translator: Coco scanner.o parser.o main.o
 g++ -o tr.exe scanner.o parser.o main.o

 main.o: main.cpp
 g++ -c main.cpp

 scanner.o: Scanner.cpp Scanner.h
 g++ -c Scanner.cpp -o scanner.o

 parser.o: Parser.cpp Parser.h
 g++ -c Parser.cpp -o parser.o

 Coco: expr.atg
 coco expr.atg

 clean:
 del Scanner.cpp Scanner.h Parser.cpp Parser.h 
 del Scanner.cpp.old Scanner.h.old Parser.cpp.old Parser.h.old 
 del scanner.o parser.o main.o
 del translator
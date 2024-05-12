.\syntax_tree\Coco.exe .\syntax_tree\Markov_algo.cpp.atg
g++ -c .\syntax_tree\Parser.cpp -o parser.o 
g++ -c .\syntax_tree\Scanner.cpp -o scanner.o
g++ -c main.cpp
g++ -o tr.exe scanner.o parser.o main.o
.\tr.exe .\Markov.IN

del .\syntax_tree\Scanner.cpp.old .\syntax_tree\Scanner.h.old .\syntax_tree\Parser.cpp.old .\syntax_tree\Parser.h.old 
del scanner.o parser.o main.o
#include <iostream>
#include <wchar.h>
#include <string>
#include <vector>
#include "get_AST.h"
#include "Scanner.h"
#include "Parser.h"

main()
{
    try
    {
        wchar_t string[200] = L"C:/Users/kapji/DocumentsW/projects/Markov_algorithm_compiler/MARKOV.IN";
        wchar_t *file = string;
        ParseTree::AST *ast = new ParseTree::AST;

        Scanner *scanner = new Scanner(file);
        Parser *parser = new Parser(scanner, ast);
        parser->Parse();

        delete parser;
        delete scanner;
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

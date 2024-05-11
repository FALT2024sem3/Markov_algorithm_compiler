#include <iostream>
#include <wchar.h>
#include <string>
#include <vector>
#include "get_AST/get_AST.h"
#include "syntax_tree/Parser.h"
#include "syntax_tree/Scanner.h"

int main()
{
        try
        {
                wchar_t string[100] = L"C:\\Qt\\Markov_Algorythm\\Markov_algorithm_compiler\\Markov.IN";
                wchar_t *file  = string;
                ParseTree::AST* ast = new ParseTree::AST;

                Scanner *scanner = new Scanner(file);
                Parser *parser   = new Parser(scanner, ast);
                parser->Parse();

                delete parser;
                delete scanner;
        }
        catch (const std::runtime_error &e)
        {
                std::cerr << "Error: " << e.what() << std::endl;
        }
        return 0;
}

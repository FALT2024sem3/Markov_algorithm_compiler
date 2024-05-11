#include <iostream>
#include <wchar.h>
#include <string>
#include <vector>
#include "tree_creation.h"
#include "get_AST.h"

main()
{
        try
        {
                wchar_t string[20] = L"MARKOV.IN";
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
}

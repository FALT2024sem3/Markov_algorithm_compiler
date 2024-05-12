#include "build_AST.h"
#include "Scanner.h"
#include "Parser.h"

ParseTree::AST* build_AST(std::string file_name)
{
    std::wstring widestr = std::wstring(file_name.begin(), file_name.end());
    const wchar_t* file = widestr.c_str();
    // wchar_t string[200] = L""C:\\Qt\\Markov_Algorythm\\Markov_algorithm_compiler\\Markov.IN"";
    // wchar_t *file  = string;
    ParseTree::AST* ast = new ParseTree::AST;

    Scanner *scanner = new Scanner(file);
    Parser *parser   = new Parser(scanner, ast);
    parser->Parse();

    delete parser;
    delete scanner;

    return ast;
    /*    catch (const std::runtime_error &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }*/
}

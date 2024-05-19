#include "build_AST.h"

ParseTree::AST* build_AST(std::string file_name)
{
    try
    {
        std::wstring widestr = std::wstring(file_name.begin(), file_name.end());
        const wchar_t* file = widestr.c_str();
        ParseTree::AST* ast = new ParseTree::AST;

    Scanner *scanner = new Scanner(file);
    Parser *parser   = new Parser(scanner, ast);
    parser->Parse();


    delete parser;
    delete scanner;

    return ast;
    }
    catch (const std::runtime_error &e)
    {
        ParseTree::AST* ast = new ParseTree::AST;
        std::cerr << "Error: " << e.what() << std::endl;
        return ast;
    }
}

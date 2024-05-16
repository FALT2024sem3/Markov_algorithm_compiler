#include "build_AST.h"
#include "Scanner.h"
#include "Parser.h"
#include "MyException.h"

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

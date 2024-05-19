#ifndef BUILD_AST_H
#define BUILD_AST_H

#include "Scanner.h"
#include "Parser.h"
#include "MyException.h"
#include "AST.h"

ParseTree::AST* build_AST(std::string file_name);

#endif // BUILD_AST_H

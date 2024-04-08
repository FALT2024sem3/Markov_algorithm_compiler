#include <iostream>
#include <wchar.h>
#include "Parser.h"
#include "Scanner.h"
#include "AST.h"
#include <string>
#include <vector>

void TreeTraversal(const std::vector<ParseTree::Stat*>& st){ // обход нашего дерева
        std::wcout<<st.size()<<std::endl;
        std::wcout<<"{"<<std::endl;
        
        for (size_t i = 0; i < st.size(); i++)
        {
                if (st[i]->Type == ParseTree::NodeType::BinExpr){ // вывод бинарных выражений
                        std::wcout<<(dynamic_cast<ParseTree::BinExpr*>(st[i]))->GetLeftExpr()<<' '<<(dynamic_cast<ParseTree::BinExpr*>(st[i]))->GetRightExpr()<<std::endl; 
                }
                if (st[i]->Type == ParseTree::NodeType::Block){   // вывод блока
                        TreeTraversal(dynamic_cast<ParseTree::Block*>(st[i])->Getstats());
                }
                if (st[i]->Type == ParseTree::NodeType::If){      // вывод конструкции if
                        std::wcout << std::endl;
                        std::wcout << "IF: " << std::endl;
                        switch (dynamic_cast<ParseTree::If*>(st[i])->GetSinglExpr().GetOp())
                        {
                        case ParseTree::Operator::EXIST:
                                std::wcout << "?" << ' ';
                                break;
                        
                        case ParseTree::Operator::NOTEXIST:
                                std::wcout << "!?" << ' ';
                                break;
                        }
                        std::wcout << (dynamic_cast<ParseTree::If*>(st[i]))->GetSinglExpr().GetExpr() <<std::endl;
                        TreeTraversal(dynamic_cast<ParseTree::If*>(st[i])->GetBlock()->Getstats());
                        std::wcout << "ENDIF" << std::endl;
                        std::wcout << std::endl;
                }
        }
        std::wcout<<"}"<<std::endl;

};
 
main(int argc, char *argv[])
{
        if (argc == 2)
        {
                
                wchar_t *file  = coco_string_create(argv[1]);
 
                Scanner *scanner = new Scanner(file);
                Parser *parser   = new Parser(scanner);
                parser->Parse();

                TreeTraversal(ParseTree::AST::Root.Getstats());
 
                delete parser;
                delete scanner;
                delete file;
 
                return 0;
        }

        
        else
        {
                std::cout << "Use: translator filename" << std::endl;
                return 1;
        }
}
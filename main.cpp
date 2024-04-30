#include <iostream>
#include <wchar.h>
#include "Parser.h"
#include "Scanner.h"
#include "AST.h"
#include <string>
#include <vector>

void TreeTraversal(const std::vector<ParseTree::Stat*>& st){ // обход нашего дерева
        std::wcout<<"{"<<std::endl;
        
        for (size_t i = 0; i < st.size(); i++)
        {
                if (st[i]->Type == ParseTree::NodeType::BinExpr){ // вывод бинарных выражений
                        std::wcout<<(dynamic_cast<ParseTree::BinExpr*>(st[i]))->GetLeftExpr()<<' '<<(dynamic_cast<ParseTree::BinExpr*>(st[i]))->GetRightExpr()<<std::endl; 
                }
                if (st[i]->Type == ParseTree::NodeType::Block){   // вывод блока
                        TreeTraversal(dynamic_cast<ParseTree::Block*>(st[i])->Getstats());
                }
                if (st[i]->Type == ParseTree::NodeType::Link){
                        std::wcout<<(dynamic_cast<ParseTree::Link*>(st[i]))->GetName()<<':'<<std::endl;
                }
                if (st[i]->Type == ParseTree::NodeType::Goto){
                        std::wcout<<"GOTO: "<<(dynamic_cast<ParseTree::Goto*>(st[i]))->GetLink()<<std::endl;
                }
                if (st[i]->Type == ParseTree::NodeType::IfElse){      // вывод конструкции ifelse
                        std::cout<<(dynamic_cast<ParseTree::IfElse*>(st[i]))->GetCond().size()<<std::endl;
                        std::cout<<"IF"<<std::endl;
                        std::vector<ParseTree::Expr*> vec = (dynamic_cast<ParseTree::IfElse*>(st[i]))->GetCond();

                        for (auto i : vec){
                                if (i->Type == ParseTree::NodeType::SinglExpr){
                                        if ((dynamic_cast<ParseTree::SinglExpr*>(i))->GetOp() == ParseTree::Operator::NOT)
                                                std::wcout << "not ";                
                                        std::wcout<<(dynamic_cast<ParseTree::SinglExpr*>(i))->GetExpr()<<" ";
                                }
                                if (i->Type == ParseTree::NodeType::BinLogOp){

                                        if ((dynamic_cast<ParseTree::BinLogOp*>(i))->GetTypeLogOp() == ParseTree::Operator::AND)
                                                std::wcout<<"AND"<<' ';
                                        if ((dynamic_cast<ParseTree::BinLogOp*>(i))->GetTypeLogOp() == ParseTree::Operator::OR)
                                                std::wcout<<"OR"<<' ';
                                }
                        }

                        TreeTraversal((dynamic_cast<ParseTree::IfElse*>(st[i]))->GetIfBlock()->Getstats());
                        TreeTraversal((dynamic_cast<ParseTree::IfElse*>(st[i]))->GetElseBlock()->Getstats());

                        std::cout<<"ENDIF"<<std::endl;
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
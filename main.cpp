#include <iostream>
#include <wchar.h>
#include "Parser.h"
#include "Scanner.h"
#include <string>
#include <vector>
#include "get_AST.h"

// #define GETONLYROOT

void Condition_Tree_Traversal(ParseTree::Expr* root){// функция обхода дерева условия
        if (root->Type == ParseTree::NodeType::SinglExpr){
                std::wcout << dynamic_cast<ParseTree::SinglExpr*>(root)->GetExpr() << ' ';
        }
        if (root->Type == ParseTree::NodeType::BinLogOp){
                ParseTree::BinLogOp* BinEx = dynamic_cast<ParseTree::BinLogOp*>(root);
                #ifndef GETONLYROOT        
                Condition_Tree_Traversal(BinEx->GetLeftOp());
                #endif
                if (BinEx->GetTypeLogOp() == ParseTree::TypeOfLogicOp::AND)
                        std::wcout << "AND" << ' ';
                if (BinEx->GetTypeLogOp() == ParseTree::TypeOfLogicOp::OR)
                        std::wcout << "OR" << ' ';
                #ifndef GETONLYROOT        
                Condition_Tree_Traversal(BinEx->GetRighttOp());
                #endif
        }
        if (root->Type == ParseTree::NodeType::SinglLogOp){
                ParseTree::SinglLogOp* SinglEx = dynamic_cast<ParseTree::SinglLogOp*>(root);
                std::wcout << "!" << ' ';
                #ifndef GETONLYROOT        
                Condition_Tree_Traversal(SinglEx->GetOp());
                #endif
        }
}

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
                        std::cout<<"IF"<<std::endl;
                        ParseTree::Expr* Condition = (dynamic_cast<ParseTree::IfElse*>(st[i]))->GetCond();

                        Condition_Tree_Traversal(Condition); // обход дерева условия

                        TreeTraversal((dynamic_cast<ParseTree::IfElse*>(st[i]))->GetIfBlock()->Getstats()); // обход блока if
                        TreeTraversal((dynamic_cast<ParseTree::IfElse*>(st[i]))->GetElseBlock()->Getstats()); // обход блока else

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

                // QStandardItemModel model;
                //QStandardItem *parent_item = model.invisibleRootItem();

                //get_AST(ParseTree::AST::Root.Getstats(), parent_item);
                //printItems(parent_item, 0);
                std::cout << "End of the main";
 
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

#include "syntax_tree/Parser.h"
#include "syntax_tree/Scanner.h"
#include "syntax_tree/AST.h"
#include <memory>

// #define GETONLYROOT

void Condition_Tree_Traversal(std::shared_ptr<ParseTree::Expr> root){// функция обхода дерева условия
        if (root->Type == ParseTree::NodeType::SinglExpr){
                std::wcout << std::dynamic_pointer_cast<ParseTree::SinglExpr>(root)->GetExpr() << ' ';
        }
        if (root->Type == ParseTree::NodeType::BinLogOp){
                std::shared_ptr<ParseTree::BinLogOp> BinEx = std::dynamic_pointer_cast<ParseTree::BinLogOp>(root);
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
                std::shared_ptr<ParseTree::SinglLogOp> SinglEx = std::dynamic_pointer_cast<ParseTree::SinglLogOp>(root);
                std::wcout << "!" << ' ';
                #ifndef GETONLYROOT        
                Condition_Tree_Traversal(SinglEx->GetOp());
                #endif
        }
}

void TreeTraversal(const std::vector<std::shared_ptr<ParseTree::Stat>>& st){ // обход нашего дерева
        std::wcout<<"{"<<std::endl;
        
        for (size_t i = 0; i < st.size(); i++)
        {
                if (st[i]->Type == ParseTree::NodeType::BinExpr){ // вывод бинарных выражений
                        std::wcout<<(std::dynamic_pointer_cast<ParseTree::BinExpr>(st[i]))->GetLeftExpr()<<' '<<(std::dynamic_pointer_cast<ParseTree::BinExpr>(st[i]))->GetRightExpr()<<std::endl; 
                }
                if (st[i]->Type == ParseTree::NodeType::Block){   // вывод блока
                        TreeTraversal(std::dynamic_pointer_cast<ParseTree::Block>(st[i])->Getstats());
                }
                if (st[i]->Type == ParseTree::NodeType::Link){
                        std::wcout<<(std::dynamic_pointer_cast<ParseTree::Link>(st[i]))->GetName()<<':'<<std::endl;
                }
                if (st[i]->Type == ParseTree::NodeType::Goto){
                        std::wcout<<"GOTO: "<<(std::dynamic_pointer_cast<ParseTree::Goto>(st[i]))->GetLink()<<std::endl;
                }
                if (st[i]->Type == ParseTree::NodeType::IfElse){      // вывод конструкции ifelse
                        std::cout<<"IF"<<std::endl;
                        std::shared_ptr<ParseTree::Expr> Condition = (std::dynamic_pointer_cast<ParseTree::IfElse>(st[i]))->GetCond();

                        Condition_Tree_Traversal(Condition); // обход дерева условия

                        TreeTraversal((std::dynamic_pointer_cast<ParseTree::IfElse>(st[i]))->GetIfBlock()->Getstats()); // обход блока if
                        TreeTraversal((std::dynamic_pointer_cast<ParseTree::IfElse>(st[i]))->GetElseBlock()->Getstats()); // обход блока else

                        std::cout<<"ENDIF"<<std::endl;
                }
        }
        std::wcout<<"}"<<std::endl;

};

void tree_creation(wchar_t string[20]){
        // wchar_t *string_pointer;
        // wchar_t string[20] = L"MARKOV.IN";
        wchar_t *file  = string;
        ParseTree::AST* ast = new ParseTree::AST;

        Scanner *scanner = new Scanner(file);
        Parser *parser   = new Parser(scanner, ast);
        parser->Parse();

        TreeTraversal(ast->GetRoot()->Getstats());

        delete parser;
        delete scanner;
}
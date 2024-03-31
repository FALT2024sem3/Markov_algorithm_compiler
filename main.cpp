#include <iostream>
#include <wchar.h>
#include "Parser.h"
#include "Scanner.h"
#include "AST.h"
#include <string>
#include <vector>

void TreeTraversal(const std::vector<ParseTree::Stat*>& st){
        std::wcout<<st.size()<<std::endl;
        for (size_t i = 0; i < st.size(); i++)
        {
                std::cout<<"IN"<<std::endl;
                if (*(st[i]->Type) == ParseTree::NodeType::BinExpr){
                        std::wcout<<(dynamic_cast<ParseTree::BinExpr*>(st[i]))->GetLeftExpr()<<' '<<(dynamic_cast<ParseTree::BinExpr*>(st[i]))->GetRightExpr()<<std::endl; 
                }
                if (*(st[i]->Type) == ParseTree::NodeType::Block){
                        std::cout<<"a"<<std::endl;
                        // ParseTree::Block*  v = dynamic_cast<ParseTree::Block*>(st[i]);
                        TreeTraversal(dynamic_cast<ParseTree::Block*>(st[i])->Getstats());
                }
        }
        
};
 
main(int argc, char *argv[])
{
        if (argc == 2)
        {
                
                wchar_t *file  = coco_string_create(argv[1]);
 
                Scanner *scanner = new Scanner(file);
                Parser *parser   = new Parser(scanner);
                parser->Parse();

                // if (*(ParseTree::AST::Root.Type) == ParseTree::NodeType::Block)
                //         cout<<"YAPPI"<<endl;
                // if (*(ParseTree::AST::Root.Getstats()[0]->Type) == ParseTree::NodeType::BinExpr){
                // }

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
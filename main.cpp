#include <iostream>
#include <wchar.h>
#include "Parser.h"
#include "Scanner.h"
#include "AST.h"
#include <string>
#include <vector>

 
using namespace std;

void TreeGo(const std::vector<ParseTree::Stat*>& st){
        wcout<<st.size()<<endl;
        for (size_t i = 0; i < st.size(); i++)
        {
                cout<<"IN"<<endl;
                if (*(st[i]->Type) == ParseTree::NodeType::BinExpr){
                        wcout<<(dynamic_cast<ParseTree::BinExpr*>(st[i]))->GetLeftExpr()<<' '<<(dynamic_cast<ParseTree::BinExpr*>(st[i]))->GetRightExpr()<<endl; 
                }
                if (*(st[i]->Type) == ParseTree::NodeType::Block){
                        cout<<"a"<<endl;
                        // ParseTree::Block*  v = dynamic_cast<ParseTree::Block*>(st[i]);
                        TreeGo(dynamic_cast<ParseTree::Block*>(st[i])->Getstats());
                }
        }
        
};
 
main(int argc, char *argv[])
{
        try{
        if (argc == 2)
        {
                
                wchar_t *file  = coco_string_create(argv[1]);
 
                Scanner *scanner = new Scanner(file);
                Parser *parser   = new Parser(scanner);
                parser->Parse();

                // for (size_t i = 0; i < Parser::SintaxTree::terms.size(); i++)
                // {
                //         if (*(dynamic_cast<Parser::Binexpr*>(Parser::SintaxTree::terms[i]))->type == Parser::NodeType::binExpr)
                //                 wcout<<*(dynamic_cast<Parser::Binexpr*>(Parser::SintaxTree::terms[i]))->left<<L" "<<*(dynamic_cast<Parser::Binexpr*>(Parser::SintaxTree::terms[i]))->right<<endl;
                //         // wcout<<(dynamic_cast<Parser::term*>(Parser::SyntaxTree::children_of_root[i]))->right;
                // }

                if (*(ParseTree::AST::Root.Type) == ParseTree::NodeType::Block)
                        cout<<"YAPPI"<<endl;
                if (*(ParseTree::AST::Root.Getstats()[0]->Type) == ParseTree::NodeType::BinExpr){
                        // cout<<"AAAAAA"<<endl;
                }
                // cout<<ParseTree::AST::Root.Getstats().size();
                TreeGo(ParseTree::AST::Root.Getstats());
 
                delete parser;
                delete scanner;
                delete file;
 
                return 0;
        }

        
        else
        {
                cout << "Use: translator filename" << endl;
                return 1;
        }}
        catch(...){
                cout<<"qwe"<<endl;
        }
}
#ifndef AST_H
#define AST_H

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>


namespace ParseTree
{

enum class Operator{ SUB };
enum class NodeType{ StringValueLiteral, BinExpr, UnaryExpr, Block, If };

class Node{
    virtual const char* getMsg() { return "ParentClass"; }
public:
    NodeType* Type;
};

//---------------------Expressions--------------------//

class Expr : public Node{};


class UnaryExpr : public Expr{
    Operator* op;
    std::wstring* e;
public:
    std::wstring GetExpr(){ return *e; }
    Operator GetOp(){ return *op; }
    UnaryExpr(){}

    UnaryExpr (Operator* x, std::wstring* y) { op = x; e = y; this->Type = new NodeType(NodeType::UnaryExpr);}
};

//---------------------Statements--------------------//

class Stat : public Node{
    virtual const char* getMsg() { return "StatClass"; }
};

class BinExpr : public Stat{
private:
    Operator* op;
    std::wstring* left;
    std::wstring* right;
public:
    BinExpr(){}
    BinExpr(std::wstring* f1, Operator* o, std::wstring* f2) { op = o; left = f1; right = f2; this->Type = new NodeType(NodeType::BinExpr);}

    std::wstring GetLeftExpr(){ return *left; }
    std::wstring GetRightExpr(){ return *right; }
    Operator GetOp(){ return *op; }
    
};

class If : public Stat {
public:
    UnaryExpr* cond;
    Stat* stat;
    If (UnaryExpr* e, Stat* s) { cond = e; stat = s; this->Type = new NodeType(NodeType::If); }
};

class Block : public Stat {
    std::vector<Stat*>* stats;
public:
    std::vector<Stat*> Getstats(){ return *stats; }
    Block(){ this->Type = new NodeType(NodeType::Block); stats = new std::vector<Stat*>;}
    void add (Stat* s) { stats->push_back(s); }
};

class AST{
public:
    inline static Block Root;    
};
} // namespace ParseTree

#endif
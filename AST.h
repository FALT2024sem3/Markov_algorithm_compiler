#ifndef AST_H
#define AST_H

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>

namespace ParseTree
{

enum class Operator{ SUB, EXIST, NOTEXIST };
enum class NodeType{ BinExpr, UnaryExpr, Block, If };

class Node{                    // базовый класс, от которого наследуются все остальные
    virtual const char* getMsg() { return "ParentClass"; }
public:
    NodeType Type;
};

//---------------------Expressions--------------------//

class Expr : public Node{};

class SinglExpr : public Expr{ // для выражений вида: ?"abc" или !?"abc", используемых в if 
    Operator op;
    std::wstring e;
public:
    std::wstring GetExpr(){ return e; }
    Operator GetOp(){ return op; }
    SinglExpr(){}

    SinglExpr (Operator x, std::wstring y) { op = x; e = y; this->Type = NodeType::UnaryExpr;}
};

//---------------------Statements--------------------//

class Stat : public Node{
    virtual const char* getMsg() { return "StatClass"; }
};

class BinExpr : public Stat{   // для выражений вида: "abc"->"def", по сути это наши замены
private:
    Operator op;
    std::wstring left;
    std::wstring right;
public:
    BinExpr(){}
    BinExpr(std::wstring f1, Operator o, std::wstring f2) { op = o; left = f1; right = f2; this->Type = NodeType::BinExpr;}

    std::wstring GetLeftExpr(){ return left; }
    std::wstring GetRightExpr(){ return right; }
    Operator GetOp(){ return op; }
    
};

class Block : public Stat {    // блок, который хранит все остальный конструкции
    std::vector<Stat*> stats;
public:
    std::vector<Stat*> Getstats(){ return stats; }
    Block(){ this->Type = NodeType::Block;}
    void add (Stat* s) { stats.push_back(s); }
};



class If : public Stat {       // конструкция блока if
    SinglExpr cond;
    Block* block;
public:
    SinglExpr GetSinglExpr(){ return cond; }
    Block* GetBlock() { return block; }
    If (){ this->Type = NodeType::If; }
    If (SinglExpr e,Block* s) { cond = e; block = s; this->Type = NodeType::If; }
};


class AST{                     // класс для работы с нашим AST деревом, хранит самый верхний уровень вложенности 
public:
    inline static Block Root;    
};
} // namespace ParseTree

#endif
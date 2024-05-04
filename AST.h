#ifndef AST_H
#define AST_H

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>

namespace ParseTree
{

enum class Operator{ SUB, EXIST, NOT, AND, OR };
enum class NodeType{ BinExpr, UnaryExpr, Block, If, IfElse, LogOp };

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

    const char* getMsg() override { return "Single Expresion"; }
public:
    std::wstring GetExpr(){ return e; }
    Operator GetOp(){ return op; }

    SinglExpr(){}
    SinglExpr(const SinglExpr& s) { op = s.op; e = s.e ; this->Type = NodeType::UnaryExpr;}
    SinglExpr (Operator x, std::wstring y) { op = x; e = y; this->Type = NodeType::UnaryExpr;}
};

//---------------------Statements--------------------//

class Stat : public Node{
    virtual const char* getMsg() override { return "StatClass"; }
};

class BinExpr : public Stat{   // для выражений вида: "abc"->"def", по сути это наши замены
private:
    Operator op;
    std::wstring left;
    std::wstring right;

    const char* getMsg() override { return "Binary Expresion"; }
public:
    BinExpr(){}
    BinExpr(std::wstring f1, Operator o, std::wstring f2) { op = o; left = f1; right = f2; this->Type = NodeType::BinExpr;}

    std::wstring GetLeftExpr(){ return left; }
    std::wstring GetRightExpr(){ return right; }
    Operator GetOp(){ return op; }
    
};

class Block : public Stat {    // блок, который хранит все остальный конструкции
    std::vector<Stat*> stats;

    const char* getMsg() override { return "Block"; }
public:
    std::vector<Stat*> Getstats(){ return stats; }
    Block(){ this->Type = NodeType::Block;}
    void add (Stat* s) { stats.push_back(s); }
};



class LogOp : public Expr{
    Operator op;

    const char* getMsg() override { return "Logic Operator"; }
public:
    Operator GetLogOp() { return op; }

    LogOp(){}
    LogOp(const LogOp& l) { this->op = l.op; this->Type = NodeType::LogOp; }
    LogOp(Operator op){ this->op = op; this->Type = NodeType::LogOp; }
};

class IfElse : public Stat {       // конструкция блока if
    std::vector<Expr*> Cond;
    Block* IfBlock;
    Block* ElseBlock;

    const char* getMsg() override { return "If Else"; }
public:
    void AddCond(Expr* e) { Cond.push_back(e); }
    std::vector<Expr*> GetCond(){ return Cond; }
    Block* GetIfBlock() { return IfBlock; }
    Block* GetElseBlock() { return ElseBlock; }
    IfElse (){ this->Type = NodeType::If; }
    IfElse (std::vector<Expr*> e,Block* s1, Block* s2) { Cond = e; IfBlock = s1; ElseBlock = s2; this->Type = NodeType::IfElse; }
};


class AST{                     // класс для работы с нашим AST деревом, хранит самый верхний уровень вложенности 
public:
    inline static Block Root;    
};
} // namespace ParseTree

#endif

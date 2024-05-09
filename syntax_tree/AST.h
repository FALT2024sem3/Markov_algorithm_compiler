#ifndef AST_H
#define AST_H

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

namespace ParseTree
{

    enum class Operator
    {
        SUB
    };
    enum class NodeType
    {
        BinExpr,
        SinglExpr,
        Block,
        If,
        IfElse,
        BinLogOp,
        SinglLogOp,
        Link,
        Goto
    };
    enum class TypeOfLogicOp
    {
        AND,
        OR,
        NOT
    };

    class Node
    { // базовый класс, от которого наследуются все остальные
        virtual const char *getMsg() { return "ParentClass"; }

    public:
        NodeType Type;
    };

    //---------------------Expressions--------------------//

    class Expr : public Node
    {
    };

    class SinglExpr : public Expr
    { // для выражений вида: "abc" или "abc", используемых в if
        std::wstring e;

    public:
        std::wstring GetExpr() { return e; }
        SinglExpr() {}
        SinglExpr(const SinglExpr &s)
        {
            e = s.e;
            this->Type = NodeType::SinglExpr;
        }
        SinglExpr(std::wstring y)
        {
            e = y;
            this->Type = NodeType::SinglExpr;
        }
    };

    class BinLogOp : public Expr
    { // для or и and
        Expr *LeftOp;
        Expr *RigthOp;
        TypeOfLogicOp LogType;

    public:
        Expr *GetLeftOp() { return this->LeftOp; }
        Expr *GetRighttOp() { return this->RigthOp; }
        TypeOfLogicOp GetTypeLogOp() { return LogType; }
        BinLogOp() {}
        BinLogOp(Expr *l, TypeOfLogicOp tp, Expr *r)
        {
            this->LeftOp = l;
            this->RigthOp = r;
            this->LogType = tp;
            this->Type = NodeType::BinLogOp;
        }
    };

    class SinglLogOp : public Expr
    { // для not
        Expr *Op;
        TypeOfLogicOp LogType;

    public:
        Expr *GetOp() { return this->Op; }
        TypeOfLogicOp GetTypeLogOp() { return LogType; }
        SinglLogOp() {}
        SinglLogOp(Expr *o, TypeOfLogicOp tp)
        {
            this->Op = o;
            this->LogType = tp;
            this->Type = NodeType::SinglLogOp;
        }
    };

    //---------------------Statements--------------------//

    class Stat : public Node
    {
        virtual const char *getMsg() { return "StatClass"; }
    };

    class BinExpr : public Stat
    { // для выражений вида: "abc"->"def", по сути это наши замены
    private:
        Operator op;
        std::wstring left;
        std::wstring right;

    public:
        BinExpr() {}
        BinExpr(std::wstring f1, Operator o, std::wstring f2)
        {
            op = o;
            left = f1;
            right = f2;
            this->Type = NodeType::BinExpr;
        }

        std::wstring GetLeftExpr() { return left; }
        std::wstring GetRightExpr() { return right; }
        Operator GetOp() { return op; }
    };

    class Block : public Stat
    { // блок, который хранит все остальный конструкции
        std::vector<Stat *> stats;

    public:
        std::vector<Stat *> Getstats() { return stats; }
        Block() { this->Type = NodeType::Block; }
        void add(Stat *s) { stats.push_back(s); }
    };

    class Link : public Stat
    {
        std::wstring name;

    public:
        Link() {}
        std::wstring GetName() { return name; }
        void SetName(std::wstring n) { name = n; }
        Link(const Link &ln)
        {
            name = ln.name;
            Type = NodeType::Link;
        }
        Link(std::wstring nm)
        {
            name = nm;
            Type = NodeType::Link;
        }
    };

    class Goto : public Stat
    {
        std::wstring link;

    public:
        Goto() {}
        std::wstring GetLink() { return link; }
        void SetLink(std::wstring n) { link = n; }
        Goto(const Goto &gt)
        {
            link = gt.link;
            Type = NodeType::Goto;
        }
        Goto(std::wstring ln)
        {
            link = ln;
            Type = NodeType::Goto;
        }
    };

    class IfElse : public Stat
    { // конструкция блока if
        Expr *Cond;
        Block *IfBlock;
        Block *ElseBlock;

    public:
        Expr *GetCond() { return Cond; }
        Block *GetIfBlock() { return IfBlock; }
        Block *GetElseBlock() { return ElseBlock; }
        IfElse() { this->Type = NodeType::If; }
        IfElse(Expr *e, Block *s1, Block *s2)
        {
            Cond = e;
            IfBlock = s1;
            ElseBlock = s2;
            this->Type = NodeType::IfElse;
        }
    };

    class AST
    { // класс для работы с нашим AST деревом, хранит самый верхний уровень вложенности
        Block *Root;
        std::unordered_map<std::wstring, int> TableOfLink;

    public:
        AST()
        {
            Root = new ParseTree::Block;
        }
        Block *GetRoot()
        {
            return Root;
        }
        void SetNewLink(const std::wstring& str){ 
            TableOfLink[str] = 0; 
        }
        auto& GetTableOfLink(){ return TableOfLink; }
    };

} // namespace ParseTree

#endif
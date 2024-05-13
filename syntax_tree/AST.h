#ifndef AST_H
#define AST_H

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <locale>
#include <codecvt>
#include <unordered_map>
#include <memory>

namespace ParseTree
{

    enum class Operator
    {
        SUB
    };
    enum class NodeType
    { // Типы всех возможных узлов
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
    { // Типы логических операторов
        AND,
        OR,
        NOT
    };

    class Node
    { // базовый класс, от которого наследуются все остальные
        virtual const char *getMsg() { return "ParentClass"; }

    public:
        // Тип узла
        NodeType Type;
    };

    //------------------------Expressions-------------------------//

    class Expr : public Node
    {
    };

    class SinglExpr : public Expr
    {                   // для выражений вида: "abc" или "abc", используемых в if
        std::wstring e; // Подстрока для проверки наличия в исходной строке

    public:
        std::wstring GetExpr() { return e; } // Получить подстроку
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
    {                                             // для or и and
        std::shared_ptr<ParseTree::Expr> LeftOp;  // Левый операнд
        std::shared_ptr<ParseTree::Expr> RigthOp; // Правый операнд
        TypeOfLogicOp LogType;                    // Тип логической операции

    public:
        std::shared_ptr<ParseTree::Expr> GetLeftOp() { return this->LeftOp; }    // Получить Левый операнд
        std::shared_ptr<ParseTree::Expr> GetRighttOp() { return this->RigthOp; } // Получить Правый операнд
        TypeOfLogicOp GetTypeLogOp() { return LogType; }                         // Получить Тип логической операции
        BinLogOp() {}
        BinLogOp(std::shared_ptr<ParseTree::Expr> l, TypeOfLogicOp tp, std::shared_ptr<ParseTree::Expr> r)
        {
            this->LeftOp = l;
            this->RigthOp = r;
            this->LogType = tp;
            this->Type = NodeType::BinLogOp;
        }
    };

    class SinglLogOp : public Expr
    {                                        // для not
        std::shared_ptr<ParseTree::Expr> Op; // Операнд
        TypeOfLogicOp LogType;               // Тип логической операции

    public:
        std::shared_ptr<ParseTree::Expr> GetOp() { return this->Op; } // Получить операнд
        TypeOfLogicOp GetTypeLogOp() { return LogType; }              // Получить тип логической операции
        SinglLogOp() {}
        SinglLogOp(std::shared_ptr<ParseTree::Expr> o, TypeOfLogicOp tp)
        {
            this->Op = o;
            this->LogType = tp;
            this->Type = NodeType::SinglLogOp;
        }
    };

    //-------------------------Statements-------------------------//

    class Stat : public Node
    {
        virtual const char *getMsg() { return "StatClass"; }
    };

    class BinExpr : public Stat
    { // для выражений вида: "abc"->"def", по сути это наши замены
    private:
        Operator op;        // Оператор
        std::wstring left;  // Левый операнд
        std::wstring right; // Правый операнд

    public:
        BinExpr() {}
        BinExpr(std::wstring f1, Operator o, std::wstring f2)
        {
            op = o;
            left = f1;
            right = f2;
            this->Type = NodeType::BinExpr;
        }

        std::wstring GetLeftExpr() { return left; }   // Получить левый операнд
        std::wstring GetRightExpr() { return right; } // Получить правый операнд
        Operator GetOp() { return op; }               // Получить оператор
    };

    class Block : public Stat
    { // блок, который хранит все остальный конструкции
        std::vector<std::shared_ptr<ParseTree::Stat>> stats;

    public:
        std::vector<std::shared_ptr<ParseTree::Stat>> Getstats() { return stats; } // Получить блок
        Block() { this->Type = NodeType::Block; }
        void add(std::shared_ptr<ParseTree::Stat> s) { stats.push_back(s); } // Добавить что-то в блок
    };

    class Link : public Stat
    {
        std::wstring name; // Имя метки

    public:
        Link() {}
        std::wstring GetName() { return name; }    // Получить имя метки
        void SetName(std::wstring n) { name = n; } // Установить имя метки
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
        std::wstring link; // Имя прыжка

    public:
        Goto() {}
        std::wstring GetLink() { return link; }    // Получить имя прыжка
        void SetLink(std::wstring n) { link = n; } // Установить имя прыжка
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
    {                                                // конструкция блока if
        std::shared_ptr<ParseTree::Expr> Cond;       // Условие блока If
        std::shared_ptr<ParseTree::Block> IfBlock;   // Блок If
        std::shared_ptr<ParseTree::Block> ElseBlock; // Блок Else

    public:
        std::shared_ptr<ParseTree::Expr> GetCond() { return Cond; }            // Получить условие
        std::shared_ptr<ParseTree::Block> GetIfBlock() { return IfBlock; }     // Получить блок If
        std::shared_ptr<ParseTree::Block> GetElseBlock() { return ElseBlock; } // Получить блок Else
        IfElse() { this->Type = NodeType::If; }
        IfElse(std::shared_ptr<ParseTree::Expr> e, std::shared_ptr<ParseTree::Block> s1, std::shared_ptr<ParseTree::Block> s2)
        {
            Cond = e;
            IfBlock = s1;
            ElseBlock = s2;
            this->Type = NodeType::IfElse;
        }
    };

    class AST
    {                                                      // класс для работы с нашим AST деревом, хранит самый верхний уровень вложенности
        std::shared_ptr<ParseTree::Block> Root;            // корень дерева
        std::unordered_map<std::wstring, int> TableOfLink; // метки
        std::vector<std::wstring> TableOfGoto;             // переходы к меткам
        void CheckOfLinks()
        { // проеверяем соответствие меток и переходов(goto)
            for (size_t i = 0; i < TableOfGoto.size(); i++)
            {
                auto it = TableOfLink.find(TableOfGoto[i]);
                if (it == TableOfLink.end())
                { // нашли несоответствие, кидаем ошибку
                    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
                    std::string narrow = converter.to_bytes(TableOfGoto[i]);

                    std::string str = "Unknown link " + narrow;

                    throw(std::runtime_error(str));
                }
            }
        }

    public:
        AST()
        {
            Root = std::make_shared<ParseTree::Block>();
        }
        std::shared_ptr<ParseTree::Block> GetRoot() // Возвращаем корень дерева
        {
            CheckOfLinks();
            return Root;
        }
        void SetNewLink(const std::wstring &str) // Установить новую метку
        {
            TableOfLink[str] = 0;
        }
        void SetNewGoto(const std::wstring &str) // Установить новый прыжок
        {
            TableOfGoto.push_back(str);
        }
    };

} // namespace ParseTree

#endif
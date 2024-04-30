

#if !defined(COCO_PARSER_H__)
#define COCO_PARSER_H__

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include "AST.h"


#include "Scanner.h"



class Errors {
public:
	int count;			// number of errors detected

	Errors();
	void SynErr(int line, int col, int n);
	void Error(int line, int col, const wchar_t *s);
	void Warning(int line, int col, const wchar_t *s);
	void Warning(const wchar_t *s);
	void Exception(const wchar_t *s);

}; // Errors

class Parser {
private:
	enum {
		_EOF=0,
		_ident=1,
		_string=2
	};
	int maxT;

	Token *dummyToken;
	int errDist;
	int minErrDist;

	void SynErr(int n);
	void Get();
	void Expect(int n);
	bool StartOf(int s);
	void ExpectWeak(int n, int follow);
	bool WeakSeparator(int n, int syFol, int repFol);

public:
	Scanner *scanner;
	Errors  *errors;

	Token *t;			// last recognized token
	Token *la;			// lookahead token



	Parser(Scanner *scanner);
	~Parser();
	void SemErr(const wchar_t* msg);

	void Root();
	void Block(ParseTree::Block& B);
	void Stat(ParseTree::Stat*& s, ParseTree::Block& B);
	void Term(ParseTree::BinExpr*& b);
	void Condition(ParseTree::IfElse& conds);
	void Link(ParseTree::Link& link);
	void Goto(ParseTree::Goto& Gt);
	void SinglExpr(ParseTree::SinglExpr& se);
	void Or();
	void And();
	void Not();
	void Word(std::wstring &str);
	void Ident(std::wstring &str);
	void GOTO();
	void SubOp();

	void Parse();

}; // end Parser



#endif


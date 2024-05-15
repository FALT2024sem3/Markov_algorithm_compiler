

#if !defined(COCO_PARSER_H__)
#define COCO_PARSER_H__

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include "AST.h"
#include "Includes.h"


#include "Scanner.h"
#include <locale>
#include <codecvt>
#include <string>



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
	ParseTree::AST* root;

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



    ParseTree::AST* GetASTRoot();
	Parser(Scanner *scanner, ParseTree::AST* a);
	~Parser();
	void SemErr(const wchar_t* msg);

	void Root();
	void Block(ParseTree::Block& B);
	void Stat(Includes::PtrStat& s, ParseTree::Block& B);
	void Term(Includes::PtrBinExpr& b);
	void Condition(Includes::PtrExpr& Cond);
	void Link(ParseTree::Link& link);
	void Goto(ParseTree::Goto& Gt, int& line);
	void expression(Includes::PtrExpr& EXPR);
	void TermOfIf(Includes::PtrExpr& TR);
	void Secondary_expression(Includes::PtrExpr& SE);
	void Primary_expression(Includes::PtrExpr& PE);
	void Unury(Includes::PtrExpr& SE);
	void Word(std::wstring &str);
	void Ident(std::wstring &str, int &line);
	void GOTO();
	void SubOp();

	void Parse();

}; // end Parser



#endif


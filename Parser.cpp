

#include <wchar.h>
#include "Parser.h"
#include "Scanner.h"




void Parser::SynErr(int n) {
	if (errDist >= minErrDist) errors->SynErr(la->line, la->col, n);
	errDist = 0;
}

void Parser::SemErr(const wchar_t* msg) {
	if (errDist >= minErrDist) errors->Error(t->line, t->col, msg);
	errDist = 0;
}

void Parser::Get() {
	for (;;) {
		t = la;
		la = scanner->Scan();
		if (la->kind <= maxT) { ++errDist; break; }

		if (dummyToken != t) {
			dummyToken->kind = t->kind;
			dummyToken->pos = t->pos;
			dummyToken->col = t->col;
			dummyToken->line = t->line;
			dummyToken->next = NULL;
			coco_string_delete(dummyToken->val);
			dummyToken->val = coco_string_create(t->val);
			t = dummyToken;
		}
		la = t;
	}
}

void Parser::Expect(int n) {
	if (la->kind==n) Get(); else { SynErr(n); }
}

void Parser::ExpectWeak(int n, int follow) {
	if (la->kind == n) Get();
	else {
		SynErr(n);
		while (!StartOf(follow)) Get();
	}
}

bool Parser::WeakSeparator(int n, int syFol, int repFol) {
	if (la->kind == n) {Get(); return true;}
	else if (StartOf(repFol)) {return false;}
	else {
		SynErr(n);
		while (!(StartOf(syFol) || StartOf(repFol) || StartOf(0))) {
			Get();
		}
		return StartOf(syFol);
	}
}

void Parser::Root() {
		Expect(3 /* "dafe" */);
		Block(ParseTree::AST::Root);
}

void Parser::Block(ParseTree::Block& B) {
		ParseTree::Stat* s; 
		Expect(4 /* "{" */);
		while (StartOf(1)) {
			Stat(s, B);
		}
		Expect(5 /* "}" */);
}

void Parser::Stat(ParseTree::Stat*& s, ParseTree::Block& B) {
		ParseTree::Stat* ss; 
		ParseTree::BinExpr* b; 
		std::vector<ParseTree::Expr*> se;
		ParseTree::Block* bl = new ParseTree::Block();
		ParseTree::Block* bl2 = new ParseTree::Block(); 
		ParseTree::Expr* ConditionIf;
		ParseTree::Link link;
		ParseTree::Goto Gt;
		
		if (la->kind == 4 /* "{" */) {
			Block(*bl);
			ss = dynamic_cast<ParseTree::Stat*>(bl);
			
		} else if (la->kind == _string) {
			Term(b);
			ss = dynamic_cast<ParseTree::Stat*>(b);
			
		} else if (la->kind == 6 /* "if" */) {
			Get();
			Expect(7 /* "(" */);
			Condition(ConditionIf);
			Expect(8 /* ")" */);
			Block(*bl);
			if (la->kind == 9 /* "else" */) {
				Get();
				Block(*bl2);
			}
			ss = dynamic_cast<ParseTree::Stat*>(new ParseTree::IfElse(ConditionIf, bl, bl2)); 
			
		} else if (la->kind == _ident) {
			Link(link);
			ss = dynamic_cast<ParseTree::Stat*>(new ParseTree::Link(link)); 
			
		} else if (la->kind == 15 /* "goto" */) {
			Goto(Gt);
			ss = dynamic_cast<ParseTree::Stat*>(new ParseTree::Goto(Gt)); 
			
		} else SynErr(18);
		B.add(ss);
		
}

void Parser::Term(ParseTree::BinExpr*& b) {
		std::wstring s1, s2;
		
		Word(s1);
		SubOp();
		Word(s2);
		Expect(14 /* ";" */);
		b = new ParseTree::BinExpr(s1, ParseTree::Operator::SUB , s2); 
		
}

void Parser::Condition(ParseTree::Expr*& Cond) {
		expression(Cond);
}

void Parser::Link(ParseTree::Link& link) {
		std::wstring s; 
		Ident(s);
		Expect(13 /* ":" */);
		link.SetName(s); 
}

void Parser::Goto(ParseTree::Goto& Gt) {
		std::wstring s; 
		GOTO();
		Ident(s);
		Expect(14 /* ";" */);
		Gt.SetLink(s); 
}

void Parser::expression(ParseTree::Expr*& EXPR) {
		ParseTree::Expr* s1; 
		TermOfIf(s1);
		while (la->kind == 10 /* "and" */) {
			ParseTree::Expr* s2; 
			Get();
			TermOfIf(s2);
			s1 = dynamic_cast<ParseTree::Expr*>(new ParseTree::BinLogOp(s1, ParseTree::TypeOfLogicOp::AND, s2));
		}
		EXPR = s1; 
}

void Parser::TermOfIf(ParseTree::Expr*& TR) {
		ParseTree::Expr* s1; 
		Secondary_expression(s1);
		while (la->kind == 11 /* "or" */) {
			ParseTree::Expr* s2; 
			Get();
			Secondary_expression(s2);
			s1 = dynamic_cast<ParseTree::Expr*>(new ParseTree::BinLogOp(s1, ParseTree::TypeOfLogicOp::OR, s2)); 
		}
		TR = s1;  
}

void Parser::Secondary_expression(ParseTree::Expr*& SE) {
		ParseTree::Expr* s; 
		if (la->kind == 12 /* "!" */) {
			Get();
			Primary_expression(s);
			s = dynamic_cast<ParseTree::Expr*>(new ParseTree::SinglLogOp(s, ParseTree::TypeOfLogicOp::NOT)); 
		} else if (la->kind == _string || la->kind == 7 /* "(" */) {
			Primary_expression(s);
		} else SynErr(19);
		SE = s; 
}

void Parser::Primary_expression(ParseTree::Expr*& PE) {
		ParseTree::Expr* s; 
		if (la->kind == 7 /* "(" */) {
			Get();
			expression(s);
			Expect(8 /* ")" */);
		} else if (la->kind == _string) {
			Unury(s);
		} else SynErr(20);
		PE = s; 
}

void Parser::Unury(ParseTree::Expr*& SE) {
		std::wstring str;
		Word(str);
		SE = dynamic_cast<ParseTree::Expr*>(new ParseTree::SinglExpr(str)); 
}

void Parser::Word(std::wstring &str) {
		Expect(_string);
		str=t->val; 
}

void Parser::Ident(std::wstring &str) {
		Expect(_ident);
		str=t->val; 
}

void Parser::GOTO() {
		Expect(15 /* "goto" */);
}

void Parser::SubOp() {
		Expect(16 /* "->" */);
}




// If the user declared a method Init and a mehtod Destroy they should
// be called in the contructur and the destructor respctively.
//
// The following templates are used to recognize if the user declared
// the methods Init and Destroy.

template<typename T>
struct ParserInitExistsRecognizer {
	template<typename U, void (U::*)() = &U::Init>
	struct ExistsIfInitIsDefinedMarker{};

	struct InitIsMissingType {
		char dummy1;
	};
	
	struct InitExistsType {
		char dummy1; char dummy2;
	};

	// exists always
	template<typename U>
	static InitIsMissingType is_here(...);

	// exist only if ExistsIfInitIsDefinedMarker is defined
	template<typename U>
	static InitExistsType is_here(ExistsIfInitIsDefinedMarker<U>*);

	enum { InitExists = (sizeof(is_here<T>(NULL)) == sizeof(InitExistsType)) };
};

template<typename T>
struct ParserDestroyExistsRecognizer {
	template<typename U, void (U::*)() = &U::Destroy>
	struct ExistsIfDestroyIsDefinedMarker{};

	struct DestroyIsMissingType {
		char dummy1;
	};
	
	struct DestroyExistsType {
		char dummy1; char dummy2;
	};

	// exists always
	template<typename U>
	static DestroyIsMissingType is_here(...);

	// exist only if ExistsIfDestroyIsDefinedMarker is defined
	template<typename U>
	static DestroyExistsType is_here(ExistsIfDestroyIsDefinedMarker<U>*);

	enum { DestroyExists = (sizeof(is_here<T>(NULL)) == sizeof(DestroyExistsType)) };
};

// The folloing templates are used to call the Init and Destroy methods if they exist.

// Generic case of the ParserInitCaller, gets used if the Init method is missing
template<typename T, bool = ParserInitExistsRecognizer<T>::InitExists>
struct ParserInitCaller {
	static void CallInit(T *t) {
		// nothing to do
	}
};

// True case of the ParserInitCaller, gets used if the Init method exists
template<typename T>
struct ParserInitCaller<T, true> {
	static void CallInit(T *t) {
		t->Init();
	}
};

// Generic case of the ParserDestroyCaller, gets used if the Destroy method is missing
template<typename T, bool = ParserDestroyExistsRecognizer<T>::DestroyExists>
struct ParserDestroyCaller {
	static void CallDestroy(T *t) {
		// nothing to do
	}
};

// True case of the ParserDestroyCaller, gets used if the Destroy method exists
template<typename T>
struct ParserDestroyCaller<T, true> {
	static void CallDestroy(T *t) {
		t->Destroy();
	}
};

void Parser::Parse() {
	t = NULL;
	la = dummyToken = new Token();
	la->val = coco_string_create(L"Dummy Token");
	Get();
	Root();
	Expect(0);
}

Parser::Parser(Scanner *scanner) {
	maxT = 17;

	ParserInitCaller<Parser>::CallInit(this);
	dummyToken = NULL;
	t = la = NULL;
	minErrDist = 2;
	errDist = minErrDist;
	this->scanner = scanner;
	errors = new Errors();
}

bool Parser::StartOf(int s) {
	const bool T = true;
	const bool x = false;

	static bool set[2][19] = {
		{T,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x},
		{x,T,T,x, T,x,T,x, x,x,x,x, x,x,x,T, x,x,x}
	};



	return set[s][la->kind];
}

Parser::~Parser() {
	ParserDestroyCaller<Parser>::CallDestroy(this);
	delete errors;
	delete dummyToken;
}

Errors::Errors() {
	count = 0;
}

void Errors::SynErr(int line, int col, int n) {
	wchar_t* s;
	switch (n) {
			case 0: s = coco_string_create(L"EOF expected"); break;
			case 1: s = coco_string_create(L"ident expected"); break;
			case 2: s = coco_string_create(L"string expected"); break;
			case 3: s = coco_string_create(L"\"dafe\" expected"); break;
			case 4: s = coco_string_create(L"\"{\" expected"); break;
			case 5: s = coco_string_create(L"\"}\" expected"); break;
			case 6: s = coco_string_create(L"\"if\" expected"); break;
			case 7: s = coco_string_create(L"\"(\" expected"); break;
			case 8: s = coco_string_create(L"\")\" expected"); break;
			case 9: s = coco_string_create(L"\"else\" expected"); break;
			case 10: s = coco_string_create(L"\"and\" expected"); break;
			case 11: s = coco_string_create(L"\"or\" expected"); break;
			case 12: s = coco_string_create(L"\"!\" expected"); break;
			case 13: s = coco_string_create(L"\":\" expected"); break;
			case 14: s = coco_string_create(L"\";\" expected"); break;
			case 15: s = coco_string_create(L"\"goto\" expected"); break;
			case 16: s = coco_string_create(L"\"->\" expected"); break;
			case 17: s = coco_string_create(L"??? expected"); break;
			case 18: s = coco_string_create(L"invalid Stat"); break;
			case 19: s = coco_string_create(L"invalid Secondary_expression"); break;
			case 20: s = coco_string_create(L"invalid Primary_expression"); break;

		default:
		{
			wchar_t format[20];
			coco_swprintf(format, 20, L"error %d", n);
			s = coco_string_create(format);
		}
		break;
	}
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::string narrow = converter.to_bytes(s);
	coco_string_delete(s);
	throw (std::runtime_error(narrow));
	count++;
}

void Errors::Error(int line, int col, const wchar_t *s) {
	wprintf(L"-- line %d col %d: %ls\n", line, col, s);
	count++;
}

void Errors::Warning(int line, int col, const wchar_t *s) {
	wprintf(L"-- line %d col %d: %ls\n", line, col, s);
}

void Errors::Warning(const wchar_t *s) {
	wprintf(L"%ls\n", s);
}

void Errors::Exception(const wchar_t* s) {
	wprintf(L"%ls", s); 
	exit(1);
}





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
		while (la->kind == _string || la->kind == 4 /* "{" */ || la->kind == 6 /* "if" */) {
			Stat(s, B);
		}
		Expect(5 /* "}" */);
		std::cout<<"Block"<<std::endl;
		
		
}

void Parser::Stat(ParseTree::Stat*& s, ParseTree::Block& B) {
		ParseTree::Stat* ss; 
		ParseTree::BinExpr* b; 
		ParseTree::SinglExpr se;
		ParseTree::Block* bl = new ParseTree::Block(); 
		ParseTree::If* IF;
		
		if (la->kind == 4 /* "{" */) {
			Block(*bl);
			ss = dynamic_cast<ParseTree::Stat*>(bl);
			B.add(ss);
		} else if (la->kind == _string) {
			Term(b);
			ss = dynamic_cast<ParseTree::Stat*>(b);
			B.add(ss); 
		} else if (la->kind == 6 /* "if" */) {
			Get();
			Expect(7 /* "(" */);
			SinglExpr(se);
			Expect(8 /* ")" */);
			Block(*bl);
			ss = dynamic_cast<ParseTree::Stat*>( new ParseTree::If(se, bl) );
			B.add(ss); 
		} else SynErr(14);
		
}

void Parser::Term(ParseTree::BinExpr*& b) {
		std::wstring s1, s2; 
		Word(s1);
		Expect(9 /* "->" */);
		Word(s2);
		Expect(10 /* ";" */);
		std::cout<<"BinExpr"<<std::endl;
		b = new ParseTree::BinExpr(s1, ParseTree::Operator::SUB , s2); 
		
}

void Parser::SinglExpr(ParseTree::SinglExpr& se) {
		std::wstring s; ParseTree::Operator op; 
		if (la->kind == 11 /* "?" */) {
			Exist();
			op = ParseTree::Operator::EXIST; 
		} else if (la->kind == 12 /* "!?" */) {
			NotExist();
			op = ParseTree::Operator::NOTEXIST; 
		} else SynErr(15);
		Word(s);
		se = ParseTree::SinglExpr(op, s); 
}

void Parser::Exist() {
		Expect(11 /* "?" */);
}

void Parser::NotExist() {
		Expect(12 /* "!?" */);
}

void Parser::Word(std::wstring &str) {
		Expect(_string);
		str=t->val; 
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
	maxT = 13;

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

	static bool set[1][15] = {
		{T,x,x,x, x,x,x,x, x,x,x,x, x,x,x}
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
			case 9: s = coco_string_create(L"\"->\" expected"); break;
			case 10: s = coco_string_create(L"\";\" expected"); break;
			case 11: s = coco_string_create(L"\"?\" expected"); break;
			case 12: s = coco_string_create(L"\"!?\" expected"); break;
			case 13: s = coco_string_create(L"??? expected"); break;
			case 14: s = coco_string_create(L"invalid Stat"); break;
			case 15: s = coco_string_create(L"invalid SinglExpr"); break;

		default:
		{
			wchar_t format[20];
			coco_swprintf(format, 20, L"error %d", n);
			s = coco_string_create(format);
		}
		break;
	}
	wprintf(L"-- line %d col %d: %ls\n", line, col, s);
	coco_string_delete(s);
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



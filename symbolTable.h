
#ifndef _SYMBOLTABLE_H_
#define _SYMBOLTABLE_H_

#include "Scanner.h"

class Parser;
class Errors;

struct Object {
	wchar_t* name;
	int type;
	Object* next;
	int kind;
	int addr;
	int level;
	Object* locals;
	int nextAddr;
	Object();
	~Object();
};

class SymbolTable {
	const int tInt,tBool, tSet;
	const int var, proc, scope;
	int currentLevel;
	Object* topScope;
	Errors* e;
public:
	SymbolTable(Parser* parser);
	void putError(wchar_t* errMsg);
	void openScope();
	void closeScope();
	Object* newObj(wchar_t* name, int kind, int type);
	Object* findObj(wchar_t* name);
};

#endif

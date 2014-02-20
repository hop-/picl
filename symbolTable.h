
#ifndef _SYMBOLTABLE_H_
#define _SYMBOLTABLE_H_

#include "Parser.h"

class Object {
private:
	wchar_t* name;
	int type;
	Object* next;
	int kind;
	int addr;
	int level;
	Object* locals;
	int nextAddr;
public:
	Object();
	~Object();
};

class SymbolTable {
private:
	const int integer,boolean, set;
	const int var, proc, scope;
	int currentLevel;
	Object* undefObj;
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

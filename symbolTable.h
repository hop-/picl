
#ifndef _SYMBOLTABLE_H_
#define _SYMBOLTABLE_H_

#include "Scanner.h"

#define KIND_VAR 0
#define KIND_PROC 1
#define KIND_SCOPE 2
#define TYPE_BOOL 0
#define TYPE_INT 1
#define TYPE_SET 2
#define TYPE_UNDEF 3

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
	Object* undefObj;
	Object* topScope;
	Errors* e;
public:
	SymbolTable(Parser* parser);
	void putError(int line, int col, wchar_t* errMsg);
	void openScope();
	void closeScope();
	Object* add(int l, int c, wchar_t* name, int kind, int type);
	Object* find(int l, int c, wchar_t* name);
};

#endif

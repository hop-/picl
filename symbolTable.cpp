#include "symbolTable.h"

Object::Object(): name(NULL), type(0), next(NULL), kind(0), addr(0), level(0), locals(NULL), nextAddr(0) {}

Object::~Object(){
	coco_string_delete(name);
}

//-------------------------------------------

SymbolTable::SymbolTable(Parser* parser): integer(1), boolean(0), set(2), var(0), proc(1), scope(2) {}

void SymbolTable::putError(wchar_t* errMsg){}

void SymbolTable::openScope(){}

void SymbolTable::closeScope(){}

Object* SymbolTable::newObj(wchar_t* name, int kind, int type){}

Object* SymbolTable::findObj(wchar_t* name){}

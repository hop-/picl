#include "symbolTable.h"
#include "Parser.h"
#include <iostream>

Object::Object(): name(NULL), type(0), next(NULL), kind(0), addr(0), level(0), locals(NULL), nextAddr(0) {}

Object::~Object(){
	coco_string_delete(name);
}

//-------------------------------------------

SymbolTable::SymbolTable(Parser* parser): 
		tInt(1), tBool(0), tSet(2), var(0), proc(1), scope(2),
		topScope(NULL), e(parser->errors), currentLevel(-1), undefObj(new Object()) {
	undefObj->name = coco_string_create("undef");
	undefObj->type = TYPE_UNDEF;
	undefObj->kind = var;
	undefObj->addr = 0;
	undefObj->level = 0;
	undefObj->next = NULL;
}

void SymbolTable::putError(int line, int col, wchar_t* errMsg){
	e->Error(line, col, errMsg);
}

void SymbolTable::openScope(){
	Object* scop = new Object();
	scop->name = coco_string_create("");
	scop->kind = KIND_SCOPE;
	scop->locals = NULL;
	scop->nextAddr = 0;
	scop->next = topScope;
	topScope = scop;
	currentLevel++;
}

void SymbolTable::closeScope(){
	topScope = topScope->next;
	currentLevel--;
}

Object* SymbolTable::add(int l, int c, wchar_t* name, int kind, int type){
	Object* obj = new Object();
	Object* p = topScope->locals;
	Object* last = NULL;
	
//	wprintf(L"%ls\n", name);
	obj->name = name;
	obj->kind = kind;
	obj->type = type;
	obj->level = currentLevel;
	while(p != NULL){
		if(coco_string_equal(p->name, name)){
			wchar_t str[272];
			coco_swprintf(str, 272, L"%ls declared twice", name);
			putError(l, c, str);
		}
		last = p;
		p = p->next;
	}
	if(last == NULL)
		topScope->locals = obj;
	else
		last->next = obj;
	if(kind = var)
		obj->addr = topScope->nextAddr++;
	return obj;
}

Object* SymbolTable::find(int l, int c, wchar_t* name){
	Object* obj;
	Object* scope = topScope;
	while(scope != NULL){
		obj = scope->locals;
		while(obj != NULL){
			if(coco_string_equal(obj->name, name))
				return obj;
			obj = obj->next;
		}
		scope = scope->next;
	}
	wchar_t str[272];
	coco_swprintf(str, 272, L"%ls is undeclared", name);
	putError(l, c, str);
	return undefObj;
}

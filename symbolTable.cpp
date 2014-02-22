#include "symbolTable.h"
#include "Parser.h"

Object::Object(): name(NULL), type(0), next(NULL), kind(0), addr(0), level(0), locals(NULL), nextAddr(0) {}

Object::~Object(){
	coco_string_delete(name);
}

//-------------------------------------------

SymbolTable::SymbolTable(Parser* parser): tInt(1), tBool(0), tSet(2), var(0), proc(1), scope(2) {
	e = parser->errors;
	topScope = NULL;
	currentLevel = -1;
}

void SymbolTable::putError(wchar_t* errMsg){
	e->Error(0, 0, errMsg);
}

void SymbolTable::openScope(){
	Object* scop = new Object();
	scop->name = coco_string_create("");
	scop->kind = scope;
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

Object* SymbolTable::newObj(wchar_t* name, int kind, int type){
	Object* obj = new Object();
	Object* p = topScope->locals;
	Object* last = NULL;

	obj->name = coco_string_create(name);
	obj->kind = kind;
	obj->type = type;
	obj->level = currentLevel;
	while(p != NULL){
		if(coco_string_equal(obj->name, name)){
			wchar_t str[100];
			coco_swprintf(str, 100, L"%ls name declared twice", name);
			putError(str);
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

Object* SymbolTable::findObj(wchar_t* name){
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
	wchar_t str[100];
	coco_swprintf(str, 100, L"%ls is undeclared", name);
	putError(str);
	return NULL;
}

#include <iostream>

#include "Parser.h"
#include "Scanner.h"
#include "symbolTable.h"

#include <sys/timeb.h>
#include <wchar.h>

int main (int argc, char *argv[]) {
	if (argc == 2) {
		wchar_t *fileName = coco_string_create(argv[1]);
		Scanner *scanner = new Scanner(fileName);
		Parser *parser = new Parser(scanner);
		parser->tab = new SymbolTable(parser);
		parser->Parse();
		coco_string_delete(fileName);
		delete parser;
		delete scanner;
	} else
		std::cout<<"\n"<<"Usage:\n"<<"\t"<<argv[0]<<" <file_name>\n\n";
	return 0;

}

#include <iostream>
#include "scanner.h"

extern int yylex();
extern int yylineno;
extern char* yytext;

char *names[] = {NULL, "db_type", "db_name", "db_table_prefix", "db_port"};

int main(void) {

	int ntoken, vtoken;

	ntoken = yylex();
	while(ntoken) {
		printf("ntoken is: %d\n", ntoken);
		if(yylex() != COLON) {
			printf("Syntax error in line %d, Expected a ':' but found %s\n", yylineno, yytext);
			return 1;
		}
		vtoken = yylex();
		switch (ntoken) {
		case TYPE:
		case NAME:
		case TABLE_PREFIX:
			if(vtoken != IDENTIFIER) {
					printf("Syntax error in line %d, Expected an identifier but found %s\n", yylineno, yytext);
					return 1;
			}
			printf("%s is set to %s\n", names[ntoken], yytext);
			break;
		case PORT:
			if(vtoken != INTEGER) {
				printf("Syntax error in line %d, Expected an integer but found %s the vtoken %d\n", yylineno, yytext, vtoken);
				return 1;
			}
			printf("%s is set to %s\n", names[ntoken], yytext);
			break;
		default:
			printf("Syntax error in line %d with vtoken: %d and text value: [%s]\n",yylineno,vtoken,yytext);
		}
		ntoken = yylex();
	}
	return 0;
}

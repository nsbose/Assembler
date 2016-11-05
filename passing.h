#ifndef PASS_MAIN
#define PASS_MAIN

#include "reg_sym_values.h"


extern int yyparse();
extern void grabToken(char*, int); /*grabs a particular token from the parser*/
void passmain(const char*);
void firstpass(const char*); /*performs the first pass operation*/
void secondpass(); /*performs the second pass operation*/
void createMIF();
extern FILE *yyin;

#endif

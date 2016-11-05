%{
#include <stdio.h>
#include <stdlib.h>
int yyparse(void);
extern int yylex(void);
void yyerror(const char*);
extern FILE *yyin;
#include "passing.h"
#include "reg_sym_values.h"
%}

%token ADD SUB OR AND DIV MULT MFLO MFHI SRL SLL XOR 
%token J JAL JR BEQ BNE ORI ANDI ADDI SUBI LA LUI LW SW LI MOV
%token END
%token R
%token tC tS tLP tRP tCl

%union {
	int num_val;
	char *s;
}
%token <num_val> NUM
%token <s> LABL
%token <s> LABL2


%start program

%%

program
	:	function program
	| 	label program
	|	function
	;

function
	:	label func_text
	|	func_text
	;
	
func_text
	:	rType
	| 	iType
	|	jType
	;
rType
	:	ADD reg tC reg tS
	|	SUB reg tC reg tS
	|	MULT reg tC reg tS
	|	DIV reg tC reg tS
	|	OR reg tC reg tS
	|	AND reg tC reg tS
	|	MFLO reg tS
	|	MFHI reg tS
	|	XOR reg tC reg tS
	|	SLL reg tC reg tC NUM tS
	|	SRL	reg	tC reg tC NUM tS
	;

iType
	:	BEQ reg tC reg tC label tS
	|	BNE reg tC reg tC label tS
	|	LUI reg tC NUM tS
	|	ORI reg tC reg tC NUM tS
	|	ANDI reg tC reg tC NUM tS
	|	SUBI reg tC reg tC NUM tS
	|	ADDI reg tC reg tC NUM tS
	|	LW  reg tC reg tS
	|	SW reg tC reg tS
	|	LA reg tC NUM tS
	|	LI reg tC NUM tS
	|	MOV reg tC reg tS
	;

jType
	:	J label tS
	|	JAL label tS
	|	JR reg tS
	;
reg
	:	R
	;
	
label
	: 	LABL
	|	LABL2
	|	END
	;
%%

void yyerror(const char *message){
	printf(message);
}

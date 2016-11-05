%{
#include <stdio.h>
#include "parser.tab.h"
#include "passing.h"
extern int yylex(void);
%}

%%

"#"[0-9A-Za-z ]+	;
[0-9]+ 		{grabToken(yytext,-3); return NUM;}
[a-zA-Z0-9]+\:	{grabToken(yytext,1); return LABL;}
[a-zA-Z0-9]+\+	{grabToken(yytext,-1); return LABL2;}

"add"		{grabToken(yytext,2); return ADD;}
"sub"		{grabToken(yytext,2); return SUB;}
"or"		{grabToken(yytext,2); return OR;}
"and"		{grabToken(yytext,2); return AND;}
"div"		{grabToken(yytext,2); return DIV;}
"mult"		{grabToken(yytext,2); return MULT;}
"mflo"		{grabToken(yytext,2); return MFLO;}
"mfhi"		{grabToken(yytext,2); return MFHI;}
"srl"		{grabToken(yytext,2); return SRL;}
"sll"		{grabToken(yytext,2); return SLL;}
"xor"		{grabToken(yytext,2); return XOR;}

"jr"		{grabToken(yytext,3); return JR;}
"jal"		{grabToken(yytext,3); return JAL;}
"j"			{grabToken(yytext,3); return J;}

"beq"		{grabToken(yytext,4); return BEQ;}
"bne"		{grabToken(yytext,4); return BNE;}
"ori"		{grabToken(yytext,5); return ORI;}
"andi"		{grabToken(yytext,5); return ANDI;}
"addi"		{grabToken(yytext,5); return ADDI;}
"subi"		{grabToken(yytext,5); return SUBI;}
"la"		{grabToken(yytext,5); return LA;}
"lui"		{grabToken(yytext,5); return LUI;}
"lw"		{grabToken(yytext,5); return LW;}
"sw"		{grabToken(yytext,5); return SW;}
"li"		{grabToken(yytext,5); return LI;}
"mov"		{grabToken(yytext,5); return MOV;}

"$0"		{grabToken(yytext,0); return R;}
"$a0"		{grabToken(yytext,0); return R;}
"$ra"		{grabToken(yytext,0); return R;}
"$t0"		{grabToken(yytext,0); return R;}
"$t1"		{grabToken(yytext,0); return R;}
"$t2"		{grabToken(yytext,0); return R;}
"$t3"		{grabToken(yytext,0); return R;}
"$t4"		{grabToken(yytext,0); return R;}

".end"		{grabToken(yytext,-2); return END;}
[ \t]		;


","			{return tC;}
":"			{return tCl;}
";"			{return tS;}

%%
int yywrap(void)
{
	return 1;
}

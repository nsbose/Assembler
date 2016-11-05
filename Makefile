
all: mipsProj

parser.tab.c parser.tab.h: parser.y
	bison -d parser.y

lex.yy.c: scanner.l parser.tab.h
	flex scanner.l

mipsProj: lex.yy.c parser.tab.c parser.tab.h passing.cpp passing.h reg_sym_values.cpp reg_sym_values.h ps4_new.cpp
	g++  -g -o mipsProj parser.tab.c lex.yy.c passing.cpp reg_sym_values.cpp ps4_new.cpp -lfl


clean:
	rm mipsProj lex.yy.c parser.tab.c parser.tab.h

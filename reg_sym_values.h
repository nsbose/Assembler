#ifndef REG_VALUES
#define REG_VALUES

#include <map>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <utility>


typedef struct {
  unsigned int regAddress;
} register_Values;

typedef struct {
  unsigned int instOp; /*holds the opcode*/
  unsigned int instFunc; /*holds the function code*/
} instr_s ;

typedef struct {
	unsigned int adrsCode;
	std::string labelName;
} sym_tab;

typedef struct{
	unsigned int addressVal; 
	unsigned int instruct_c; //Holds instruction set information
	std::string labelName;
	std::string instName;
	bool jumpval; //if a jump was to occur
	unsigned int j_addrs; /*Address to which the instruction jumps to*/
} machine_block;



typedef std::string name;
typedef std::string sym_label;
typedef int adrsCount;

typedef std::map<name, register_Values> regs_; //For register
typedef std::map<name, instr_s> instruc_; //Instruction sets
typedef std::map<sym_label, sym_tab> syms_; //Symbol Table
typedef std::map<adrsCount, machine_block> machine_code_block;




extern regs_ register_names;
extern instruc_ instructs;
extern syms_ symbol_tabs;
extern machine_code_block mach_tabs;



void initialize(); /*Initializes all the files*/

#endif

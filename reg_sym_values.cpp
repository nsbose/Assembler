#include <iostream>
#include <cstdlib>
#include <utility>
#include <cstdio>
#include <map>
#include <string>
#include "reg_sym_values.h"

using namespace std;

regs_ register_names;
instruc_ instructs;
syms_ symbol_tabs; /*Declares the symbol hashmap*/
machine_code_block mach_tabs; /*Holds machine address locations*/

void initialize(){
  /*The following code will contain the register information*/
  register_names["$0"].regAddress = 0;
  register_names["$a0"].regAddress = 1;
  register_names["$ra"].regAddress = 2;
  register_names["$t0"].regAddress = 3;
  register_names["$t1"].regAddress = 4;
  register_names["$t2"].regAddress = 5;
  register_names["$t3"].regAddress = 6;
  register_names["$t4"].regAddress = 7;
	
  /*R_Type Instructions*/
  instructs["add"].instFunc = 1;
  instructs["sub"].instFunc = 2;
  instructs["or"].instFunc = 3;
  instructs["and"].instFunc = 4;
  instructs["div"].instFunc = 5;
  instructs["mult"].instFunc = 6;
  instructs["mflo"].instFunc = 7;
  instructs["mfhi"].instFunc = 8;
  instructs["srl"].instFunc = 9;
  instructs["sll"].instFunc = 10;
  instructs["xor"].instFunc = 0b1011;

  instructs["add"].instOp = 0;
  instructs["sub"].instOp = 0;
  instructs["or"].instOp = 0;
  instructs["and"].instOp = 0;
  instructs["div"].instOp = 0;
  instructs["mult"].instOp = 0;
  instructs["mflo"].instOp = 0;
  instructs["mfhi"].instOp = 0;
  instructs["srl"].instOp = 0;
  instructs["sll"].instOp = 0;
  instructs["xor"].instOp = 0;

  /*J_Type Instructions*/
  instructs["j"].instOp = 1;
  instructs["jal"].instOp = 2;
  instructs["jr"].instOp = 3;
  
  /*I_Type Instructions*/
  instructs["beq"].instOp = 4;
  instructs["bne"].instOp = 5;
  instructs["ori"].instOp = 6;
  instructs["andi"].instOp = 7;
  instructs["addi"].instOp = 8;
  instructs["subi"].instOp = 9;
  instructs["la"].instOp = 10;
  instructs["lui"].instOp = 11;
  instructs["lw"].instOp = 12;
  instructs["sw"].instOp = 13;
  instructs["li"].instOp = 14;
  instructs["mov"].instOp = 15;

}

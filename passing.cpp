#include <iomanip>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include "passing.h"
#include "parser.tab.h"

#include "reg_sym_values.h"

using namespace std;
void passmain(const char*);
void firstpass(const char*);
void secondpass(const char*);
void grabToken(char*,int);
void createMIF();
static int passStatus;
//aquamentus.com/flex_bison.html#4
unsigned int reg_loc = 0;
int count = 0; /*address space counter*/
bool beginCount = false; /*Turns the switch on for the counter*/
bool switchCount = false;
bool branchCheck = true;
bool jumpCheck = true;



void passmain(const char* FileName)
{
	firstpass(FileName);
	secondpass(FileName);
	createMIF();
}

void firstpass(const char* FileName){
	FILE *infile;
	passStatus = 1; /*set value for first pass*/
	infile = fopen(FileName, "r"); /*opens the file to be read*/
	if (infile == 0){
		cout << "File does not exist and cannot proceed further" << endl;
	}
	else
	{
		yyin = infile; /*Defined yyin to accept the match file pointer*/
		do {
			yyparse();
		} while (!feof(yyin));
		fclose(infile); //closes the file
	}
}
void secondpass(const char* FileName){
	beginCount = false; /*Reset counter switch*/

	FILE *infile;
	passStatus = 2; /*set value for first pass*/
	infile = fopen(FileName, "r"); /*opens the file to be read*/
	if (infile == 0){
		cout << "File does not exist and cannot proceed further" << endl;
	}
	else
	{
		yyin = infile; /*Defined yyin to accept the match file pointer*/
		do {
			yyparse();
		} while (!feof(yyin));
		fclose(infile); //closes the file
	}	
	
}


extern void grabToken(char *tokenName, int instType)
{
  /*The function will get the token values and pass it to Hashmap to check
   *If the instType = 1, then it is an instruction
   *If the instType = 2, then it is a register 
   */
	 //temp variable that holds the binary value
	int offset = 0;
	string tkStr(tokenName); /*Converts from char* to string to be processed*/
	cout << tkStr << " ";
	//Begin hashmap analysis
	if (passStatus == 1)
	{
		//Create a hashmap of all the symbols that appear
		if (tkStr == "start:"){
			count = 0; //sets counter value to 0
			beginCount = true;
		}
		if ((instType == 1) && (!(tkStr == "start:"))){
			count+=1; //update counter for every label that is encountered
			symbol_tabs[tkStr.erase(tkStr.length()-1)].adrsCode = count;
			symbol_tabs[tkStr].labelName = tkStr;
			cout << "LABEL: " << tkStr << " #: " << count << endl;
			beginCount = false; //Sets counter switch to false to prevent double counting
			
		}
		else if ((instType > 1) && (!(beginCount )))
		{
			beginCount = true; //sets switch to true
		}
		else if ((instType > 1) && (beginCount))
		{
			count+=1; //updates counter when it encounters
		}
	}
	if (passStatus == 2)
	{
		if (tkStr == "start:"){
			count = 0; //sets counter value to 0
		}
		if ((instType > 1) && (instType < 6))
		{
			//Only targets instruction types and ignores everything else
			count+=1; //updates counter
			reg_loc = 9; //resets
			
			if (instType == 2) //R-Type registers
			{
				branchCheck = true;
				jumpCheck = true;
				mach_tabs[count].instruct_c = instructs[tkStr].instOp << 12;
				mach_tabs[count].instruct_c = mach_tabs[count].instruct_c | instructs[tkStr].instFunc;
				//cout << tkStr << " " << mach_tabs[count].instruct_c << endl;
				mach_tabs[count].addressVal = count;
			}
			else
			{
				if (instType == 4) 
				{
					branchCheck = false;
				}
				else 
				{
					branchCheck = true; //controls difference between jump and branch
				}
				
				if (instType == 3)
				{
					jumpCheck = false;
				}
				else
				{
					jumpCheck = true;
				}
				mach_tabs[count].instruct_c = instructs[tkStr].instOp << 12;
				cout << "VALUES: " << mach_tabs[count].instruct_c << endl;
				mach_tabs[count].addressVal = count;
			}
		}
		if (instType == 0){
			//Inputs the register values
			mach_tabs[count].instruct_c = mach_tabs[count].instruct_c | (register_names[tkStr].regAddress << reg_loc);
			cout << "REG#: " << reg_loc << endl;
			reg_loc-=3; //shifts the register value to the right
			
			
		}
		/*if ((instType == -1) && (branchCheck)) 
		{
			//loads the target address
			mach_tabs[count].instruct_c = mach_tabs[count].instruct_c | symbol_tabs[tkStr.erase(tkStr.length()-1)].adrsCode;
		}*/
		if ((instType == -1) && (!(branchCheck)))
		{
			//For BEQ or BNE
			offset = symbol_tabs[tkStr.erase(tkStr.length()-1)].adrsCode;
			//offset = symbol_tabs[tkStr].adrsCode;
			cout << "COUNT MATCH: " << offset << endl;
			offset = offset - count; //negative offset
			offset = offset & 0x003F; //bitwise and to remove other values higher bits
			mach_tabs[count].instruct_c = mach_tabs[count].instruct_c | offset;
			
		}
		if ((instType == -1) && (!(jumpCheck)))
		{
			offset = symbol_tabs[tkStr.erase(tkStr.length()-1)].adrsCode;
			cout << "JUMP: " << offset << endl;
			offset = offset & 0x0FFF;
			mach_tabs[count].instruct_c = mach_tabs[count].instruct_c | offset;
		}
		
		if (instType == -3)
		{
			cout << "NUM: " << atoi(tkStr.c_str()) << endl;
			mach_tabs[count].instruct_c = mach_tabs[count].instruct_c | atoi(tkStr.c_str());
		}
	}
	
}


void createMIF()
{	
	FILE *writeFile = fopen("mifOutput.mif", "w");
	
	if (writeFile == NULL){
		printf("File does not exist!\n");
		exit(1); //exit the program 
	}
	const char *text = "This is a sample mif file";
	fprintf(writeFile,"DEPTH = 16384;\n");
	fprintf(writeFile,"WIDTH = 16;\n");
	fprintf(writeFile,"ADDRESS_RADIX = HEX;\n");
	fprintf(writeFile,"DATA_RADIX = HEX;\n");
	fprintf(writeFile,"CONTENT\n");
	fprintf(writeFile,"BEGIN\n");
	
	
		int i,j;
	for (i = 0, j = 0; i < mach_tabs.size();i++, j+=2)
	{
		fprintf(writeFile,"%04X : %04X;\n",i,mach_tabs[i].instruct_c);
	}
	
	
	//cout << "SIZE: " << mach_tabs.size() << endl;
	//int temp =0;
	
	//unsigned int i,j,k,b;
	//unsigned int mask = 0x8000;
	
	/*for (i = 0, j = 0; i < mach_tabs.size();i++, j+=2){
		cout << i << " : " << mach_tabs[j].instruct_c << endl;
	}*/
	/*
	for (i = 0, k = 0; i < mach_tabs.size();i++,k+=2)
	{
		
		b = mach_tabs[k].instruct_c;
		for (j = 0; j < 16; j++){
			if ((b & mask) == 0){
				fputc('0',writeFile);
			}
			else
			{
				fputc('1',writeFile);
			}
			mask >>= 1;	
		}
		fprintf(writeFile,"\n");
		mask = 0x8000;
	}
	
	
	*/
	fprintf(writeFile,"END\n");
	fclose(writeFile);

	//cout << "NEW SIZE: " << temp << endl;
}



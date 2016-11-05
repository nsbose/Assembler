#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <map>
#include <string>
#include "passing.h"
#include "reg_sym_values.h"


/*Resources: http://homepage.cs.uiowa.edu/~rus/Courses/SysSoft/Notes/chap16a2.pdf*/
using namespace std;

//void initialize(); /*Responsible for initializing the opcode and registers*/

int main(){
  string file_name;
  
  initialize();
  /*User enters the filename*/
  cout << "Enter file name: ";
  cin >> file_name;
  file_name = file_name + ".txt"; /*File with extension gets passed to parser*/
  passmain(file_name.c_str()); //we begin the passing to generate the codes

  return 0;
}

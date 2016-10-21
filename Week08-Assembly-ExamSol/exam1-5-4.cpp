/*
 Name: Paul Talaga
 Date: Oct 18, 2016
 Desc: Solution to Midterm exam, problem 5-4
 */

#include <iostream>

using namespace std;

int main(){
  int result = 0;
  
  asm volatile("MOV r0, #5  \n"
	       "MOV r1, #2  \n"
	       "ADD r5, r0, r0 \n"
	       "MUL r5, r5, r1 \n"
	       "MOV r0, r5 \n"
	       "MOV %0, r5"
	       :"=r" (result)
	       :
	       );

  cout << "r5 = " << result << endl;
}

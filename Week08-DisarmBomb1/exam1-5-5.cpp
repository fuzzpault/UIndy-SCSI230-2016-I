/*
 Name: Paul Talaga
 Date: Oct 18, 2016
 Desc: Solution to Midterm exam, problem 5-5
 */

#include <iostream>

using namespace std;

int main(){
  int a[6] = {-1,3,4,5,6,7};
  int result = 0;
  
  asm volatile("MOV r1, #4  \n"
	       "ADD r2, %1, r1 \n"
	       "LDR r0, [r2, r1] \n"
	       "LDR r3, [r2], r1 \n"
	       "ADD r0, r0, r3 \n"
	       "LDR r0, [r2], r1 \n"
	       "LDR r3, [r2], r1 \n"
	       "ADD %0, r0, r3"
	       :"=r" (result)
	       :"r" (a)
	       );

  cout << "r0 = " << result << endl;
}

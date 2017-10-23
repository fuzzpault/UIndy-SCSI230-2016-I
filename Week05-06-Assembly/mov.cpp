/*
  Author: Paul Talaga
    Desc: Example of embedding assembly code in C++

    See: https://gcc.gnu.org/onlinedocs/gcc/Extended-Asm.html
 */

#include <iostream>

using namespace std;

int main(){
  int a = 1;
  int b = 10;
  int dst = 0;

  // Extended Asm uses a template for C to match up actual register locations.
  asm volatile("mov r10, #55\n"
	       "add %0, r10, %1\n"
	       :"=r" (dst)
	       :"r" (a), "r" (b)
      );
  
  cout << "a: " << a << " b: " << b << " dst: " << dst << endl;
}

/*
  Author: Paul Talaga
    Desc: Example of embedding assembly code in C++ to do floating-point math.

    See: https://gcc.gnu.org/onlinedocs/gcc/Extended-Asm.html
 */

#include <iostream>

using namespace std;

int main(){
  double a = 1.5;
  double b = 10.1;
  double dst = 0;

  // Extended Asm uses a template for C to match up actual register locations.
  asm volatile(
         "vldr d1, [%1] \n"
         "vldr d2, [%2] \n"
         "vadd.F64 d3, d1, d2 \n"
	       "vstr d3, [%0] \n" 
	       :
	       :"r" (&dst), "r" (&a), "r" (&b)
      );
  
  cout << "a: " << a << " b: " << b << " dst: " << dst << endl;
}

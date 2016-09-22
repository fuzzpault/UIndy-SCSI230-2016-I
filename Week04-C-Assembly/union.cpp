/* Name: Paul Talaga
   Date: 9/21/16
   Desc: An example of using the union C/C++ keyword to extract and manipulate any typed-thing using another type.
   https://en.wikipedia.org/wiki/Union_type
*/

#include <iostream>

using namespace std;

// The union places all variables IN THE SAME MEMORY SPACE.
union upack_t{
  unsigned long number;
  char b[4];
};
// This acts like a struct, except you can only use one of the variables at a time, or risk 'viewing' it a different type/interpretation.

int main(){
  
  upack_t thing;
  thing.number = 56;

  cout << "num: " << thing.number << endl;

  thing.b[1] = 1; // What byte this corresponds to is processor
                  // specific (bigEndian/littleEndian)
  
  cout << "num: " << thing.number << endl;

  return 0;
}

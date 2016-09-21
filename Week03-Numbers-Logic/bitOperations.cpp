/* Name: Paul Talaga
   Date: 9/12/16
   Desc: Print different #'s after bitwise operations.
         Here is a decent description: http://www.tutorialspoint.com/ansi_c/c_bits_manipulation.htm
*/
#include <iostream>
#include <stdlib.h> // for malloc
#include <string.h> // for memcpy

using namespace std;
  
template <typename myType>
void printBits(myType a){   // Thus any type thing can be printed
  // To get around the type conversion (which we don't want)
  // we copy the data into a char array and operate on it there.
  char* data = (char*)malloc(sizeof(myType));  // Create an array of characters (1 byte) the same size of the incoming thing
  memcpy(data, &a, sizeof(a));            // Copy the data into the array
  
  string ret = "";                        // Since we 'look' at the LSB first, we need to flip the order
  for(unsigned i = 0; i < sizeof(a);i++){
    ret = " " + ret;
    for(unsigned j = 0; j < 8; j++){
      if(data[i] & 1){                    // Is there a 1 in the LSB now?  %2 same
        ret =  "1" + ret;
      }else{
        ret = "0" + ret;
      }
      data[i] = data[i]>>1;               // Bit shift down by 1
    }
  }
  cout << sizeof(myType) << " bytes -> " << ret << endl;
}

int main(){
  int a = 0x000f0f0f0;
  //printBits(a);
  cout << "Inserting an on bit into a variable\n";
  printBits(a);
  printBits(a | 0x01<<10);

  cout << "\nvarious shifts\n";
  printBits(a>>16);
  printBits(a<<16);
  //printBits(a>>0);
  //printBits(a<<0);

  cout << "\n~ operator - ones complement - flips all bits\n";
  int b = 0x45;
  printBits(b);
  printBits(~b);

  cout << "\n^ operator - xor - bits must be different\n";
  printBits(a);
  printBits(b);
  printBits(a ^ b);
  return 0;
}

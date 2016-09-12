/* Name: Paul Talaga
   Date: 9/12/16
   Desc: Print different #'s and types in binary using a templated function.
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
  cout << a << " is " << sizeof(myType) << " bytes -> " << ret << endl;
}

int main(){
  int a = 5;
  printBits(a);
  
  a = -2;
  printBits(a);
  
  short b = 5;
  printBits(b);
  
  int e = b;
  printBits(e);
  
  float c = 2.0;
  printBits(c);
  
  float f = -2.0;
  printBits(f);
  
  double d = 0.5;
  printBits(d);
  
  float g = 0.1;
  printBits(g);
  
  double h = 0.1;
  printBits(h);
}

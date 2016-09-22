/* Name: Paul Talaga
   Date: 9/21/16
   Desc: An example of using the union C/C++ keyword to extract and manipulate any typed-thing using another type.
   https://en.wikipedia.org/wiki/Union_type
*/

#include <iostream>
#include <string.h>
#include <cstdlib>

using namespace std;

union mytype_t{
  char a[4];
  float b;
};

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
  mytype_t d;
  //a.a = 5;
  d.b = 123.1;

  cout << "d.b: " << d.b << endl;
  cout << "d.b: ";
  printBits(d.b);
  
  cout << "d.a: ";
  printBits(d.a[2]);
  cout << endl;

  // Change the 3rd byte from the LSB side (right)
  d.a[2] = 0x0f;

  // Now print out the modified float.
  cout << "d.b: " << d.b << endl;
  cout << "d.b: ";
  printBits(d.b);

  return 0;
}

/* Name: Paul Talaga
   Date: 9/22/16
   Desc: An example of using the memcpy function to change bit values in a larger 'thing'.
*/
#include <iostream>
#include <stdlib.h>
#include <string.h>

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
  unsigned long a = 456789;
  printBits(a);
 
  char b;
  // Copy the MSByte of a into b.
  memcpy(&b, (char*)&a + 3, 1);

  // Change b to be all 1's
  b = 0xff;
  // Copy it back in.
  memcpy( (char*)&a + 3, &b, 1);
  printBits(a);
  
  return 0;
}

/* Name: <fill me in>
   Date: <fill me in>
   Desc: Functions for manipulating data at the bit/byte level.
*/
#include <cstring>
#include <stdlib.h>

using namespace std;

// ASSUME LITTLE-ENDIAN

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


// You may only use &, |, ~, ^, !, >>, << for ALL functions below, unless
// otherwise specified.
float flipSign(float input){
  char c;
  memcpy(&c, (char*)(&input)+3, 1);
  c = c ^ 0x80;
  memcpy((char*)(&input)+3, &c, 1);
  return input;
}


bool isEqual(int a, int b){
  return !(a ^ b);
}

bool isNegative(int a){
  return a>>31;
}

// May use +
int flipInt(int a){
  return ~a + 1;
}

unsigned short flipEndian(unsigned short a){
  return (a<<8) | (a>>8 & 0x00ff);
}


long insert(long data, unsigned short value){
  if(value >= sizeof(long) * 8){
    cout << "Location not valid";
    return 0;
  }
  long mask = 0x1 << value;
  return data | mask;
}

bool contains(long data, unsigned short value){
  if(value >= sizeof(long) * 8){
    cout << "Location not valid";
    return 0;
  }
  long mask = 0x1 << value;
  return data & mask;
}

long remove(long data, unsigned short value){
  if(value >= sizeof(long) * 8){
    cout << "Location not valid";
    return 0;
  }
  long mask = 0x1 << value;
  return data & ~mask;
}

long join(long data1, long data2){  // Should be called union, but that is a keyword
  return data1 | data2;
}

long subtract(long data1, long data2){
  return data1 & ~(data1 & data2);
}

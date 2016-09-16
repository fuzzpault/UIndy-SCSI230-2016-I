/* Name: Paul Talaga
   Date: 9/16/2016
   Desc: Testing program for cbitslib.cpp.
*/

#include <iostream>
#include <cassert>

#include "cbitslib.cpp"

using namespace std;

int main(){
  
  // Flip sign for float
  assert(flipSign(-56.25) == 56.25);
  assert(flipSign(1.0) == -1.0);
  // Flip sign for integers
  assert(flipInt(5) == -5);
  assert(flipInt(-10) == 10);

  // Are two integers the same?
  assert(isEqual(5, 5));
  assert(isEqual(-10, -10));
  assert( !isEqual(5, 6));
  assert( !isEqual(0, -1));

  // Integer is negative?
  assert(isNegative(-5));
  assert(isNegative(-10));
  assert( !isNegative(10));
  assert( !isNegative(0));

  // Flip endian of unsigned short
  assert(flipEndian(flipEndian(20)) == 20);
  assert(flipEndian(0x1234) == 0x3412);
  assert(flipEndian(0xefab) == 0xabef);

  // Bit set checks
  long set = 0x0;
  assert( ! contains(set, 5) );
  set = insert(set, 5);
  assert( contains(set, 5) );
  assert( ! contains(set, 10));
  set = insert(set, 5);
  assert( contains(set, 5) );
  set = insert(set,10);
  set = insert(set, 9);
  assert( contains(set, 9) );
  
  long set2 = 0x0;
  set2 = insert(set2, 9);
  set2 = insert(set2, 2);

  long set3 = join(set, set2);
  assert( contains(set3, 9) );
  assert( contains(set3, 2) );
  set3 = subtract(set, set2);
  assert( !contains(set3, 9) );
  assert( contains(set3, 10) );
  assert( !contains(set3, 2) );

  set = remove(set,10);
  assert( contains(set, 9) );
  assert( !contains(set, 10) );
  set = remove(set, 11);
  assert( !contains(set,11));

  assert( contains(set,30) == 0x0);

  cout << "Success!\n";
  
  return 0;
}

/* Name: Paul Talaga
   Date: 9/12/16
   Desc: Demo of floating point errors.
         Take 0.1 and repeatedly add 0.1 to it.
	 We do this with a float.
	 To know the 'correct' answer, we do the same to an int, but
	 treat it x10, meaning 1 = 0.1
	 We add 0.1 10,000 times and print out the difference between 
	 the float and the int versions.
	 The error is less if you use double rather than float (8 bytes vs 4)
*/
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main(){
  unsigned aint = 1;  // This is x10
  unsigned bint = 1;  // This is x10
  
  float a = 0.1;
  float b = 0.1;
  for(int i = 0; i < 10000; i++){
	a += b;
	aint += bint;
	cout << "float: "  << setw(10) << a;
	cout << " int: " << setw(10) << (float)aint/10;
	cout << " diff: " << fabs(a - (float)aint/10);
	cout << endl;
  }
}

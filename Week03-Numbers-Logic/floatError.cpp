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
/* Name: Paul Talaga
   Date: 9/12/16
   Desc: An example of floating point rouding errors.
         This compares adding 0.1 to a float and an equivalent x100 
	 representation as an unsigned int, 10000 times.
	 Note how adding 0.1 gives non-exact answers while 0.25 is exact.
*/
#include <iomanip>
#include <cmath>

using namespace std;

int main(){
  unsigned aint = 0;  // This is x100
  float a = 0.0;      // Change to double to see the difference

  for(int i = 0; i < 10000; i++){
    // Try adding 0.25 instead, which is 2^(-4).
    a += 0.1;
    aint += 10; // x100
    cout << "float: "  << setw(10) << a;
    cout << " int: " << setw(10) << (float)aint/100;
    cout << " diff: " << fabs(a - (float)aint/100);
    // Comparing 2 floats via == should never be done.
    // Use an epison (range) instead, as seen below.
    if(abs(a - (float)aint/100) < 0.01)cout << "Match!";
    cout << endl;
  }
  return 0;
}

/* Name: Paul Talaga
   Date: 8/29/2016
   Desc: Example of how ints aren't really integers.  Squaring a number
         may lead to a negative number due to wrap-around.
*/

#include <iostream>

using namespace std;

int main(){
  int a = 50000;
  int b = 50000;
  int c = a * b;
  cout  << a << " x " << b << " = " << c << endl;

  return 0;
}

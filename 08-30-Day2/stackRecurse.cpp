/* Name: Paul Talaga
   Date: 8/30/16
   Desc: A infinite recursive call will exhaust the stack

 */
#include <iostream>

using namespace std;

int callMe(unsigned i){
  cout << i << ' ';
  callMe(i + 1);
  return 0;
}

int main(){
  callMe(1);

  return 0;
}

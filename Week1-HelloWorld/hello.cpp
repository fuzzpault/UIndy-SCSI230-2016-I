/* Name: Paul Talaga
   Date: Sept 1, 2016
   Desc: How long to print?

 */

#include <iostream>

using namespace std;

int main(){
  clock_t start = clock();
  cout << "hello world" << endl;
  cout << (clock() - start)/(float)CLOCKS_PER_SEC << endl;
  
  return 0;
}

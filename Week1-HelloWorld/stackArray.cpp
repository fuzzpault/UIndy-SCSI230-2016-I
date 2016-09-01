#include <iostream>

using namespace std;

int main(){
  int a[2000000];
  // Segfaults with 3000000, not with 2000000 
  // 2000000 is 8,000,000 bytes = 7.6 MB
  // 3000000 is 12,000,000 bytes = 11.4 MB
  // So the stack size is between 7.6 and 11.4 MB

  // Note you must do something with a or it will
  // be removed for optimization purposes.

  int* b = new int[30000000]; // No problem with 114 MB on the heap!
  cout << "a address: " << a << endl;
  cout << "b address: " << b << endl;

  delete[] b;// Give it back.
  return 0;
}

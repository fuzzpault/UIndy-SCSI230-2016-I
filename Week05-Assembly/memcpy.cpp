#include <iostream>
#include <cstring>

using namespace std;

int add(int a){
  return a + 1;
}

int main(){
  int a[10] = {1,2,3,4,5,6,7,8,9,10};
  int b[10];

  memcpy(b, a, sizeof(int) * 10);

  return 0;
  
}

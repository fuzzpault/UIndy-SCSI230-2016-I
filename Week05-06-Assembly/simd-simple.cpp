/*


  See: https://gcc.gnu.org/onlinedocs/gcc/Extended-Asm.html
 */

#include <iostream>

using namespace std;

union pack_t{
  unsigned full;
  char p[4];
};

int main(){
  pack_t thing;
  thing.p[0] = 5;
  thing.p[1] = 6;
  thing.p[2] = 7;
  thing.p[3] = 8;

  pack_t out;
  
  asm volatile("UADD8 %0, %1, %1\n"
	       "UADD8 %0, %0, %1"
      :"+r" (out.full)
      :"r" (thing.full) 
      );

  for(int i = 0; i < 4; i++){
    cout << i << ": " << (unsigned)thing.p[i] << endl;
  }
  
  for(int i = 0; i < 4; i++){
    cout << i << ": " << (unsigned)out.p[i] << endl;
  }
}

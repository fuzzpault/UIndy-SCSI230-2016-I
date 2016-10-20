/*
  Name: Paul Talaga
  Date: Oct 5, 2016
  See: https://gcc.gnu.org/onlinedocs/gcc/Extended-Asm.html
  
  Description: This is a demonstration of the UADD8 ARM instruction.
  When run, it will add two arrays as fast as possible using the UADD8 command, plus
  a standard for loop.  To verify correctness, both results are checked against each other.
  
  Clock times are taken for both and printed to the screen.
 */

#include <iostream>

using namespace std;

const long LENGTH = 8000;

union pack_t{
  unsigned full;
  char p[4];
};

// Adds the arrays a and b together element by element into c
// The length is a global constant.
void addSIMD(char* a, char* b, char* c){
  // Assume LENGTH is divisible by 4
  for(unsigned i = 0; i < LENGTH; i = i + 4){
    //cout << "ap: " << (int*)ap << " " << (int*)bp << " " << (int*)cp << endl;
    unsigned* aa = (unsigned*)(a + i);
    unsigned* ab = (unsigned*)(b + i);
    unsigned* ac = (unsigned*)(c + i);
    asm volatile("UADD8 %0, %1, %2"
		 :"+r" (*ac)
		 :"r" (*aa), "r" (*ab)
		 );
 
  }
}

// A slower method of filling registers which still uses UADD8
void addSIMD2(char* a, char* b, char* c){
  // Assume LENGTH is divisible by 4
  for(unsigned i = 0; i < LENGTH; i = i + 4){
    pack_t aa;
    aa.p[0] = a[i];
    aa.p[1] = a[i+1];
    aa.p[2] = a[i+2];
    aa.p[3] = a[i+3];
    pack_t ab;
    ab.p[0] = b[i];
    ab.p[1] = b[i+1];
    ab.p[2] = b[i+2];
    ab.p[3] = b[i+3];
    pack_t ac;
    //cout << "ap: " << (int*)ap << " " << (int*)bp << " " << (int*)cp << endl;
    asm volatile("UADD8 %0, %1, %2"
		 :"+r" (ac.full)
		 :"r" (aa.full), "r" (ab.full)
		 );
    c[i] = ac.p[0];
    c[i+1] = ac.p[1];
    c[i+2] = ac.p[2];
    c[i+3] = ac.p[3];
    
  }
}

void addNormal(char* a, char* b, char* c){
  for(unsigned i =0; i < LENGTH; i++){
    c[i] = a[i] + b[i];
  }
}

int main(){
  char a[LENGTH];
  char b[LENGTH];
  char c[LENGTH];
  char d[LENGTH];

  // Fill a and b
  for(unsigned i = 0; i < LENGTH; i++){
    a[i] = (char)i;
    b[i] = (char)i *2;
  }

  clock_t start_simd = clock();
  addSIMD(a, b, c);
  clock_t stop_simd = clock();
  addNormal(a, b, d);
  clock_t stop_normal = clock();

  cout << "SIMD: " << stop_simd - start_simd << "  normal: " << stop_normal - stop_simd << endl;
  
  bool matches = true;
  for(unsigned i = 0; i < LENGTH; i++){
    if(c[i] != d[i]){
      cout << i << ":" << c[i] << "  " << d[i] << endl;
      matches = false;
    }
  }

  if(matches)cout << "Matches!\n";

  return 0;

  /*
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
  */

  return 0;
}

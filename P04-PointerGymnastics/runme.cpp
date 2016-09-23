/* Name: <fill me in>
   Date: <fill me in>
   Desc: Test file for manip.h and Pointers.h
*/

#include <iostream>
#include <stdlib.h>
#include <assert.h>

#include "Pointers.h"
#include "manip.h"

using namespace std;

void test1(){
  Pointers a;
  manip1(&a);
  assert( *(a.getA()) == 10 );
}
  
void test2(){
  int number = 56;
  Pointers a(number, &number);
  manip2(&a);
  assert( *(a.getB()) == 45 );
}
  
void test3(){
  int number = rand() % 1000;
  int number2 = 4;
  Pointers a(number, &number2);
  manip3(&a);
  assert( *(a.getB()) == number );
}
  
void test4(){
  int number2 = 4;
  Pointers a;
  manip4(&a, &number2);
  assert( a.getB() == &number2 );
}

void test5(){
  int number2 = 4;
  Pointers a(0, &number2);
  manip5(&a, &number2);
  assert( a.getC() == 45 );
}

void test6(){
  int numbers[] = {5,6,7,8};
  Pointers a(0, numbers);
  manip6(&a);
  assert( numbers[2] == 10 );
}
 
void test7(){
  int* number = new int;
  Pointers a(0, number);
  manip7(&a);
  assert( *number == 15 );
  delete number;
}
 
void test8(){
  Pointers a;
  manip8(&a);
  assert( a.getC() == 199 );
}
 
void test9(){
  int* number = new int;
  Pointers* a = new Pointers();
  manip9(a, number);
  assert( a->getB() == number );
  delete number;
  delete a;
}
 
void test10(){
  Pointers* a = new Pointers[10];
  manip10(a);
  assert( a[5].getC() == 199 );
  delete[] a;
}

int main(){
  
  // Run all test functions.  Comment out sto skip any.
  test1();
  test2();
  test3();
  test4();
  test5();
  test6();
  test7();
  test8();
  test9();
  test10();
  
  cout << "Success!" << endl;
  
  return 0;
}

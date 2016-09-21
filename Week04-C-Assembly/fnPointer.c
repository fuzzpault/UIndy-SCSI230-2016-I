/* Name: Paul Talaga
   Date: 9/21/16
   Desc: An example of using function pointers: sending a function as a parameter
         to another function.  This sends the address of the function.

	 Even though we can pass fns as paramters, I would not consider C
	 a 'first-class language' with 'first-class functions' since you can't
	 compose functions, as you can with ints, for example.
	 https://en.wikipedia.org/wiki/First-class_citizen

	 BTW, there is nothing here that MUST be done in C, the same will work in C++,
	 (and then we'd probably use cout, new, and delete).
*/

#include <stdio.h>
#include <stdlib.h>  // For malloc

int addOne(int a){
  return a+1;
}

int subOne(int a){
  return a-1;
}

int print(int a){
  printf("%d ", a);
  return 0;
}

// Calls the given function with the given value
int doIt(int value, int(*fn)(int) ){
  return fn(value);
}

// A more useful function
int* map(int* array, unsigned arr_len, int(*fn)(int) ){
  int* ret = malloc(sizeof(int) * arr_len);
  unsigned i = 0;
  for(i = 0; i < arr_len; i++){
    ret[i] = fn(array[i]);
  }
  return ret;
}

int main(){
  // Send a funtion to a function to be executed
  printf("%d %d\n", doIt(5, addOne), doIt(5, subOne));

  printf("\n");
  
  // Create an array of fn pointers
  int(*functions[5])(int);

  functions[0] = addOne;
  functions[1] = addOne;
  functions[2] = subOne;
  functions[3] = addOne;
  functions[4] = subOne;

  // Run through the array and evaluate each fn with data
  int i = 0;
  for(i = 0; i < 5; i++){
    printf("%d %d\n", i, functions[i](10) );
  }

  // Print out the fn's address
  printf("%#x %#x\n", addOne, subOne);

  // Create an array and generate a new array by applying
  // a function to each element.
  int numbers[] = {1,2,3,10,12,13,10,20,30};

  int* transformed = map(numbers, 9, addOne);
  map(numbers, 9, print);
  printf("\n");
  map(transformed, 9, print);
  printf("\n");
  
  free(transformed);

  // Can you spot the memory leak?
  // Convert this to C++ and use templating to make map universal.
  // If using C++, a vector would be a better choice for memory management.
  
  return 0;
}

/*                                                                                                                     
  Name: Paul Talaga
  Date: Nov 4, 2016
  Desc: Program to print out the length of time to access memory given different array sizes.
        Due to cache sizes, we shold see a slowdown once the cache fills, which on a RPi is about
	512KB for the L2 cache.

	See plotStuff.cpp for instructions on how to plot the result of this program.

	For fast execution, compile this with full optimizations -O3  (thats Oh, not zero)
*/
#include <iostream>
#include <cstdlib>


// http://www.math.utk.edu/~vasili/refs/How-to/gnuplot.print.html
using namespace std;

// Create a 10MB array
const int SIZE = 10 * 1024 * 1024;

int main(){
  char* array = new char[SIZE];    // A char is 1 byte, so calculating the size is easy.
  
  // Fill it with random data so memory can't be compressed easily.
  for(int i = 0; i < SIZE; i++){
    array[i] = rand();
  }
  
  // Rather than create new arrays each time, we just work on different sized parts
  // of a larger array.  Here we go up to 1 MB
  // The 4 in the 1024* 4 is mearly to control the number of points we take between 10 and 1MB.
  // 4 gives a nice # points which executes in a few seconds.
  for(unsigned long arr_size = 10; arr_size < 1024 * 1024 ; arr_size = arr_size + 1024 * 4){
    
    time_t start = clock();
    // The loop below changes array elements within arr_size.  To push the cache hard, we skip around
    // the array.  For good statistics, we must change the same number of elements no matter what the
    // arr_size.  Rather than access the array sequentially (i++), we take jumps to mess with the cache.
    // As long as arr_size is below the full cache size, all changes are fast, but once above, they will
    // start to slow as data is moved in and out.
    for(unsigned long i = 0; i < SIZE * 10 ; i = i + 160){
      array[i % arr_size]++;
    }
    time_t end = clock();

    // arr_size is in bytes
    cout << arr_size << '\t' << end - start << endl;
  }

  // Be a good programer and get into the habit of returning heap memory when you are done.
  delete[] array;
  
  return 0;
}

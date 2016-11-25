/* Name: Paul Talaga
   Date: Aug 29, 2016
   Desc: This program displays the first 100,000 prime numbers, 
   and the time it took to find the in seconds.
*/

#include <iostream>
#include <cmath>

using namespace std;

const unsigned MAX = 5000000; // 100000;

bool isPrime(unsigned n){
  //for(unsigned i = 2; i < n; i++){
  for(unsigned i = 2; i <= sqrt(n); i++){
    if(n % i == 0)return false;
  }
  return true;
}

int main(){
  cout << "Primes under " << MAX << ": " << endl;
  unsigned count = 0;
  clock_t start = clock();
  for(int test = 2; test < MAX; test++){
    if(isPrime(test)){
      //      cout << test << ' ';
      count++;
    }
  }
  cout << "\nThere are " << count << " primes under " << MAX << endl;
  cout << "Took " << (float)(clock()-start) / (float)CLOCKS_PER_SEC << " s" << endl;
  return 0;
}

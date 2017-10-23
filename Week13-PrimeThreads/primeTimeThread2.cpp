/* Name: Paul Talaga
   Date: Nov 10, 2016
   Desc: This program displays the prime numbers <= 5 million, 
   and the time it took to find the in seconds.

   This uses threads to speed up checking.
   This breads up the 5 million possible numbers equally into NUM_THREADS
   groups.
   Uses a faster isPrime function.
*/

#include <iostream>
#include <cmath>
#include <vector>
#include <pthread.h>

using namespace std;

const unsigned MAX = 5000000;
vector<int> primes;
const int NUM_THREADS = 4;
pthread_mutex_t lock;
unsigned long count = 0;

struct thread_data_t{
  int thread_id;
  unsigned long min;
  unsigned long max;
};

// Pointless to check even divisors.
bool isPrime(unsigned n){
  if(n == 0 || n == 1)return false;
  if(n % 2 == 0)return false;
  for(unsigned i = 3; i <= sqrt(n); i+=2){
    if(n % i == 0)return false;
  }
  return true;
}

void* doStuff(void* arg){
  thread_data_t* input;
  input = (thread_data_t*)arg;
  
  int thread_num = input->thread_id;
  unsigned long min = input->min;
  unsigned long max = input->max;
  
  // Rather than have lock contention for every prime #, keep a local vector
  // and prime count.
  int my_count = 0;
  vector<int> my_primes;
  
  for(unsigned long test = min; test <= max; test++){
    if(isPrime(test)){
      //cout << test << ' ';
      my_primes.push_back(test);
      my_count++;
    }
  }
  
  // Now update parent thread
  pthread_mutex_lock(&lock);
  primes.insert(primes.end(), my_primes.begin(), my_primes.end());
  count += my_count;
  pthread_mutex_unlock(&lock);
  
}



int main(){
  clock_t start = clock();
  
  cout << "Primes under " << MAX << ": " << endl;
  count = 1;
  
  primes.push_back(2);
  
  primes.reserve(400000);
  
  thread_data_t passed[NUM_THREADS];
  pthread_t threads[NUM_THREADS];

  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  pthread_mutex_init(&lock, NULL);
  
  unsigned long bsize = MAX / NUM_THREADS;
  
  for(unsigned long b = 0; b < NUM_THREADS; b++){
    passed[b].thread_id = b;
    passed[b].min = b * bsize;
    if(b == NUM_THREADS-1){
      passed[b].max = MAX;
    }else{
      passed[b].max = (b + 1) * bsize - 1;
    }
    pthread_create(&threads[b], &attr, doStuff, (void*)&passed[b]);
  }
  
  
  for(int i = 0; i < NUM_THREADS; i++){
    pthread_join(threads[i], NULL);
    cout << "Thread " << i << " done." << endl;
  }
  pthread_attr_destroy(&attr);
  pthread_mutex_destroy(&lock);
  
  
  for(int i = 0; i < 100; i++){
    cout << primes[i] << ' ';
  }
  cout << " ... ";
  for(int i = primes.size()-100; i < primes.size(); i++){
    cout << primes[i] << ' ';
  }
  cout << "\nThere are " << count << " primes under " << MAX << endl;
  cout << "veclen: " << primes.size() << endl;
  cout << "Took " << (float)(clock()-start) / (float)CLOCKS_PER_SEC << " s" << endl;
  return 0;
}

/* Name: Paul Talaga
   Date: Nov 10, 2016
   Desc: This program displays the prime numbers <= 5 million, 
   and the time it took to find the in seconds.

   This uses threads to speed up checking.
   This breads up the 5 million possible numbers equally into NUM_THREADS
   groups.
   Very few optimizations other than using threads.
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

// Pass a min and max number to each thread to define the min and max # to check.
struct thread_data_t{
  int thread_id;
  unsigned long min;
  unsigned long max;
};

// Simple prime checking function.
bool isPrime(unsigned n){
  if(n == 0 || n == 1)return false;
  for(unsigned i = 2; i <= sqrt(n); i++){
    if(n % i == 0)return false;
  }
  return true;
}

// The function to be called when starting a thread.
void* doStuff(void* arg){
  thread_data_t* input;
  input = (thread_data_t*)arg;
  
  int thread_num = input->thread_id;
  unsigned long min = input->min;
  unsigned long max = input->max;
  
  // Show the start and end values
  pthread_mutex_lock(&lock);
  cout << "Thread " << thread_num << " " << min << " -- " << max << endl;
  pthread_mutex_unlock(&lock);
  
  // Loop through numbers and if prime, add to global vector and increase prime count.
  for(unsigned long test = min; test <= max; test++){
    if(isPrime(test)){
      //cout << test << ' ';
      pthread_mutex_lock(&lock);
      primes.push_back(test);
      count++;
      pthread_mutex_unlock(&lock);
    }
  }  
}



int main(){
  clock_t start = clock();
  
  cout << "Primes under " << MAX << ": " << endl;
  count = 0;
  
  primes.reserve(400000);  // Preallocate a vector to speed push_back later;
  
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
      passed[b].max = (b + 1) * bsize - 1;  // Last block may be odd-sized.
    }
    pthread_create(&threads[b], &attr, doStuff, (void*)&passed[b]);
  }
  
  // Wait till all threads are done.
  for(int i = 0; i < NUM_THREADS; i++){
    pthread_join(threads[i], NULL);
    cout << "Thread " << i << " done." << endl;
  }
  pthread_attr_destroy(&attr);
  pthread_mutex_destroy(&lock);
  
  // Print out the first 100 primes.  This assumes the smallest prime thread finished first.
  for(int i = 0; i < 100; i++){
    cout << primes[i] << ' ';
  }
  cout << " ... ";
  for(int i = primes.size()-100; i < primes.size(); i++){
    cout << primes[i] << ' ';
  }
  cout << "\nThere are " << count << " primes under " << MAX << endl;
  cout << "Took " << (float)(clock()-start) / (float)CLOCKS_PER_SEC << " s" << endl;
  return 0;
}

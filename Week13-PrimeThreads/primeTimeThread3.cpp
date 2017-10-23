/* Name: Paul Talaga
   Date: Aug 29, 2016
   Desc: This program displays the first 5,00,000 prime numbers, 
   and the time it took to find the in seconds.
*/

#include <iostream>
#include <cmath>
#include <vector>
#include <pthread.h>
#include <algorithm>

using namespace std;

const unsigned MAX = 5000000;
vector<int> primes;
const int NUM_THREADS = 4;
pthread_mutex_t lock;
unsigned long num_primes = 0;

struct thread_data_t{
  int thread_id;
};

bool isPrime(unsigned n){
  if(n % 2 == 0)return false;
  unsigned sq = sqrt(n);
  for(unsigned i = 3; i <= sq; i+=2){
    if(n % i == 0)return false;
  }
  return true;
}

void* doStuff(void* arg){
  thread_data_t* input;
  input = (thread_data_t*)arg;
  
  int thread_num = input->thread_id;

  // Keep a local vector and count so not to slow down lock contention.
  int my_count = 0;
  vector<int> my_primes;
  my_primes.reserve(10000);
  // To equalize the load on all threads, each thread goes from 0 to 5 million,
  // but staggered based on the number of threads.
  // Thus all threads should finish at the same time.
  for(unsigned long test = thread_num * 2 + 1; test <=MAX; test+= NUM_THREADS * 2){
    if(isPrime(test)){
      my_primes.push_back(test);
      my_count++;
    }
  }
  
  // Now update parent thread
  pthread_mutex_lock(&lock);
  primes.insert(primes.end(), my_primes.begin(), my_primes.end());
  num_primes += my_count;
  pthread_mutex_unlock(&lock);
  
}



int main(){
  clock_t start = clock();
  
  cout << "Primes under " << MAX << ": " << endl;
  num_primes = 1;
  primes.push_back(2);
  
  primes.reserve(400000);
  
  thread_data_t passed[NUM_THREADS];
  pthread_t threads[NUM_THREADS];

  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  pthread_mutex_init(&lock, NULL);
  
  // See above thread for why min/max are not needed.
  for(int b = 0; b < NUM_THREADS; b++){
    passed[b].thread_id = b;
    pthread_create(&threads[b], &attr, doStuff, (void*)&passed[b]);
  }

  // Wait till all threads are done.
  for(int i = 0; i < NUM_THREADS; i++){
    pthread_join(threads[i], NULL);
    cout << "Thread " << i << " done." << endl;
  }
  
  pthread_attr_destroy(&attr);
  pthread_mutex_destroy(&lock);

  // Since primes could finish out of order, we need to sort teh primes to get
  // first/last 100.
  sort(primes.begin(), primes.end());
  
  for(int i = 0; i < 100; i++){
    cout << primes[i] << ' ';
  }
  cout << " ... ";
  for(int i = primes.size()-100; i < primes.size(); i++){
    cout << primes[i] << ' ';
  }
  cout << "\nThere are " << num_primes << " primes under " << MAX << endl;
  cout << "veclen: " << primes.size() << endl;
  cout << "Took " << (float)(clock()-start) / (float)CLOCKS_PER_SEC << " s total CPU time." << endl;

  return 0;
}

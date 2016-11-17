/*                                                                                                                     
  Name: Paul Talaga
  Date: Nov 1, 2016
  Desc: Program to demonstrate why mutexes/locks are needed.

  To compile this, do: g++ -lpthread thread-bad1.cpp
*/

#include <iostream>
#include <pthread.h>
#include <string>
#include <cstdlib>

using namespace std;

// Put parameters you want to send to the threads in this struct.
struct thread_data_t{
  int thread_id;
};

int temp;  // Single global variable all threads will update.
pthread_mutex_t lock;

void* doStuff(void* arg){
  thread_data_t* input;
  input = (thread_data_t*)arg;
  int a = 0;
  
  int thread_num = input->thread_id;
  // Disable all mutexes/locking and see what occurs.
  //pthread_mutex_lock(&lock);
  
  // This should increment temp by 100
  for(int i = 0; i < 100; i++){
    //pthread_mutex_lock(&lock);
    int v = temp;
    // Do something that will take some time in hopes this thread
    // will be swaped out for another.
    a = rand();
    temp = v + 1;
    //pthread_mutex_unlock(&lock);
  }

  //pthread_mutex_unlock(&lock);
}


const int NUM_THREADS = 50;
int main(){

  temp = 0;
  
  thread_data_t passed[NUM_THREADS];
  pthread_t threads[NUM_THREADS];

  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  pthread_mutex_init(&lock, NULL);

  // Create 50 threads, all incrementing temp by 100 so temp should equal
  // 5000 at the end.
  
  for(int i = 0; i < NUM_THREADS; i++){
    passed[i].thread_id = i;
    pthread_create(&threads[i], &attr, doStuff, (void*)&passed[i]);
  }

  // Wait for all threads to finish.
  for(int i = 0; i < NUM_THREADS; i++){
    pthread_join(threads[i], NULL);
    cout << "Thread " << i << " done." << endl;
  }
  pthread_attr_destroy(&attr);
  pthread_mutex_destroy(&lock);
  
  cout << "Temp should be 5000 but is: " << temp << endl;
  
}

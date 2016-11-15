/*                                                                                                                     
  Name: Paul Talaga
  Date: Nov 1, 2016
  Desc: Program to demonstrate the use of pthreads

  To compile this, do: g++ -lpthread thread1.cpp
*/

#include <iostream>
#include <pthread.h>
#include <string>
#include <cstdlib>

using namespace std;

struct thread_data_t{
  int thread_id;
  int value;
};

int temp;
pthread_mutex_t lock;

void* doStuff(void* arg){
  thread_data_t* input;
  input = (thread_data_t*)arg;
  
  int thread_num = input->thread_id;
  int v = input->value;
  int a;
  //pthread_mutex_lock(&lock);

  //cout << thread_num << " value " << v << " temp " << temp << endl;
  for(int i = 0; i < 100; i++){
    //pthread_mutex_lock(&lock);
    int v = temp;
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
  
  for(int i = 0; i < NUM_THREADS; i++){
    passed[i].thread_id = i;
    passed[i].value = 55;
    pthread_create(&threads[i], &attr, doStuff, (void*)&passed[i]);
  }


  for(int i = 0; i < NUM_THREADS; i++){
    pthread_join(threads[i], NULL);
    cout << "Thread " << i << " done." << endl;
  }
  pthread_attr_destroy(&attr);
  pthread_mutex_destroy(&lock);
  
  cout << "Temp: " << temp << endl;
  
}

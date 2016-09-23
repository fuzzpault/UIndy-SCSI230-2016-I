#ifndef POINTERS_H
#define POINTERS_H

// Author: Paul Talaga
// Source File: Pointers.h
// Description: Implements a convoluted class to exercise pointers, 
// dynamic memory, and reference manipulations.

#include <iostream>

using namespace std;

class Pointers {
public:
 Pointers(){
  a = 5;
  b = NULL;
  c = 10;
 }
 
 Pointers(int a, int* b){
  this->a = a;
  this->b = b;
  c = 0;
 }
 
 int* getA(){
  return &a;
 }
 
 int* getB() const{
  return b;
 }
 
 int getC() const{
  return c;
 }
 
 void setB(int* b){
  this->b = b;
 }
 
 void setC(){
  c = *b;
 }
  
private:
  int a;
  int* b;
  int c;
  
};
#endif

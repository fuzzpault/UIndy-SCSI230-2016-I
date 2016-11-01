/*
  To use, compile this program, and run it.  It should output pairs of numbers
  seperated with a tab character.  Save this to a file via ./a.out > d.csv
  Then start gnuplot, run 'set term dumb', then "plot 'd.csv'" to plot the
  data stored in d.csv.
 */

#include <iostream>

using namespace std;

int main(){
  for(int i = -100; i < 100; i++){
    cout << i << '\t' << i * i * i << endl; 
  }
}

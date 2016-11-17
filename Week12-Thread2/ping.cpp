#include <iostream>
#include <string>
#include <stdio.h>
#include <sstream>

using namespace std;

// Function to ping a host and return true if it is alive, false
// if not.  This is restricted to the 192.168.0.X subnet.
// Timeout is set to 2 seconds.
bool ping(int end){
  FILE* in;
  char buff[512];
  string answer;

  stringstream ss;
  ss << end;

  string command = "ping -c 1 -W 2 192.168.0." + ss.str();
  in = popen(command.c_str(),"r");
  if(!in){
    cout << "popen failed" << endl;
    return false;
  }

  while(fgets(buff, sizeof(buff), in) != NULL){
    answer += buff;
  }

  pclose(in);

  return answer.find(" 1 received") != string::npos;
}

int main(){

  // Make this go faster!
  for(int i = 1; i < 20; i++){
    cout << "192.168.0." << i ;
    if(ping(i)){
      cout << " ALIVE";
    }
    cout << endl;
  }
  
  return 0;
}

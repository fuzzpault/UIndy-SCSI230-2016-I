#include <iostream>
#include <string>
#include <stdio.h>
#include <sstream>

using namespace std;

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
  for(int i = 1; i < 20; i++){
    cout << "192.168.0." << i ;
    if(ping(i)){
      cout << " ALIVE";
    }
    cout << endl;
  }
  //cout << ping(10) << endl;
  
  return 0;
}

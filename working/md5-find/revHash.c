/* Hello World program */

#include<stdio.h>
#include<string.h>
#include <stdbool.h>

#include "md5.h"

bool doesMatch(MD5_CTX * md5, char* to_hash, int h_len, char* to_find, int length){
  MD5_Update(md5, to_hash, h_len);
 
  unsigned char result[16];
  MD5_Final(result, md5);
  int i;
  for(i = 0; i < length; i++){
    if(result[i] != to_find[i])return false; 
  }
  for(i = 0; i < 16; i++){
    printf("%02x",*(result + i));  
  }
  printf("\n");
  return true;
}


void findMatches(char* to_find, int length){
  if(length > 16){
    printf("Hash too long!\n");
    return;
  }
  
  char input[6];
  input[5] = '\0';
  unsigned char result[16];
  char let_1, let_2, let_3, let_4, let_5;
  
  // Setup md5
  MD5_CTX md5;
  MD5_Init(&md5);
  
  for(let_1 = 'a'; let_1 <= 'z'; let_1++){
    for(let_2 = 'a'; let_2 <= 'z'; let_2++){
      for(let_3 = 'a'; let_3 <= 'z'; let_3++){
        for(let_4 = 'a'; let_4 <= 'z'; let_4++){
          for(let_5 = 'a'; let_5 <= 'z'; let_5++){
            input[0] = let_1;
            input[1] = let_2;
            input[2] = let_3;
            input[3] = let_4;
            input[4] = let_5;
            if(doesMatch( &md5, input, 5, to_find, length)){
              printf("%s\n", input);
              
            }
          }
        }
      }
    }
  }

}

main(int argc, char* argv[]){
    if(argc < 2){
      printf("Enter hashed password as command-line parameter.\n\n");
      return 1;
    }
    
    printf("MD5 check for %s\n", argv[1]);
    
    findMatches(argv[1], strlen(argv[1]));
    
    /*
    MD5_CTX md5;
    MD5_Init(&md5);
    char* data = "This is a test.";
    printf("%d\n", sizeof(data) );
    MD5_Update(&md5, data, 15);
    
    // 128-bit?
    unsigned char result[16];
    
    MD5_Final(result, &md5);
    int i;
    for(i = 0; i < 16; i++){
      printf("%02x",*(result + i));  
    }
    */
} 

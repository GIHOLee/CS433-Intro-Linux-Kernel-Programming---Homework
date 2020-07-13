#include <stdio.h>

#define _GNU_SOURCE
#include <sys/syscall.h>
#include <unistd.h>

#define __NR_MY_NAME_CALL 548
#define MY_NAME "Giho Lee"

static long my_name_call(char *name)
{
  return syscall(__NR_MY_NAME_CALL, name);
}

int main(int argc, char **argv)
{
  long ret = my_name_call(MY_NAME);
  printf ("System call returned %ld\n", ret);
  
  return 0;
}

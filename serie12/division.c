#include <stdio.h>

int main(int argc, char* argv[])
{
  int a, b;
  a = 1024;
  b = a*a*a-1;
  a = 2*b;
  b = a+1;
  a = b+1;
  b = 4*b;
  a = 2*a;
  b = b/a;
  printf("%d\n", b);
}
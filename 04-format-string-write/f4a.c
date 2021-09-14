#include <stdio.h>

int main(int argc, char *argv[]) {
  char name[8] = "debin";
  char buf[40] = "\x01\xd4\xff\xff%x%x%x%x%x%x%x%x%x%x%x%56x%hhn";

  printf(buf);
  printf("Name is: %s\n", name);
}

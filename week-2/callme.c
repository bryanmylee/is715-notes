#include <stdio.h>
#include <string.h>

char* callme(char* arg) {
  char buf[10];

  buf[0] = arg[0];
  buf[1] = arg[1];
  buf[2] = arg[2];
}

int main(int argc, char *argv[]) {
  callme(argv[1]);

  printf("%s\n", argv[1]);
}


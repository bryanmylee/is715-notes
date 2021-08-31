#include <stdio.h>

int main(int argc, char *argv[]) {
  char buf[50] = "%x\x7a\xd5\xff\xff %x %x %x %x %x %x %x %x %x %s";

  printf(buf);
}

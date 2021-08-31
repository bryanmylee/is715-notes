#include <stdio.h>
#include <string.h>

int main() {
  char buf[13] = "gaodebin\x38\x56\x4c\x5";

  printf("%s\n", buf);
}

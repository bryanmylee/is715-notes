#include <stdio.h>
#include <string.h>

void copy_name(char* dest) {
  scanf("%s", dest);
}

int main(int argc, char *argv[]) {
  struct {
    char name[8];
    unsigned balance;
    unsigned type;
  } account;

  account.balance = 100;
  account.type = 1;
  copy_name(account.name);

  printf("balance: %u\n", account.balance);
}

#include <stdio.h>
#include <string.h>

void copy_name(char* dest, char* source) {
  int offset = 0;

  while (*(source + offset) != '\0') {
    *(dest + offset) = *(source + offset);
    offset++;
  }

  *(dest + offset) = '\0';
}

int main(int argc, char *argv[]) {
  struct {
    char name[8];
    unsigned balance;
    unsigned type;
  } account;

  account.balance = 100;
  account.type = 1;
  copy_name(account.name, argv[1]);

  printf("balance: %u\n", account.balance);
}

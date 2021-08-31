#include <stdio.h>

void func2(int a, int b) {
}

void func1(int a) {
  int b = 102;
  func2(a, b);
}

int main() {
  int a = 100;
  func1(a);
  a = 101;
}

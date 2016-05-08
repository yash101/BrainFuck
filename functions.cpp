#include "functions.h"
#include "stdio.h"

void output() {
  putchar(*tape);
}

void input() {
  *tape = getchar();
}

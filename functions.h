#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "interp.h"

inline void moveTapeLeft() {
  tape--;
}

inline void moveTapeRight() {
  tape++;
}

inline void cellIncrement() {
  (*tape)++;
}

inline void cellDecrement() {
  (*tape)--;
}

void output();
void input();

#endif

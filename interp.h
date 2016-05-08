#ifndef INTERP_H
#define INTERP_H
extern char** jmpStack;
extern char* tape;

int interp(char* programCode);
#endif

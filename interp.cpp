#include "interp.h"
#include "string.h"
#include "malloc.h"
#include "functions.h"

#ifndef JMP_STACK_SIZE
#define JMP_STACK_SIZE 16384
#endif
#ifndef BF_TAPE_SIZE
#define BF_TAPE_SIZE 30000
#endif

char** jmpStack = (char**) malloc(sizeof(char*) * JMP_STACK_SIZE);
char* tape = (char*) malloc(sizeof(char) * BF_TAPE_SIZE);

int interp(char* programCode)
{
  char* cpos = programCode;

  if(*cpos == '\0') return -1;
  memset(tape, 0, sizeof(char) * BF_TAPE_SIZE);

  do
  {
    if(*cpos == ']') {
      *jmpStack--;
    }

    if(*cpos == '[') {
      *jmpStack = cpos;
      *jmpStack++;
    }

    if(*cpos == '+') cellIncrement();
    if(*cpos == '-') cellDecrement();
    if(*cpos == '>') moveTapeRight();
    if(*cpos == '<') moveTapeLeft();
    if(*cpos == '.') output();
    if(*cpos == ',') input();
  }
  while(*cpos++ != '\0');

  return 0;
}

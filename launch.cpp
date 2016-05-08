#include "launch.h"
#include "interp.h"
#include "stdio.h"
#include "string.h"
#include "malloc.h"

int main(int argc, char** argv)
{
  int type = 0;
  char* data = NULL;

  if(argc <= 1)
    fprintf(stderr, "Error! No arguments provided\n");

  if(argc == 2)
  {
    type = 1;
    data = argv[2];
  }
  else
  {
    for(int i = 1; i < argc; i++)
    {
      if(!strcmp(argv[i], "-f") || !strcmp(argv[i], "--file"))
      {
        type = 1;
        if(i + 1 >= argc)
        {
          fprintf(stderr, "-f/--file used without parameter\n");
          return -1;
        }
        data = argv[i + 1];
        i++;
      }

      if(!strcmp(argv[i], "-r") || !strcmp(argv[i], "--run"))
      {
        type = 2;
        if(i + 1 >= argc)
        {
          fprintf(stderr, "-r/--run used without parameter\n");
          return -1;
        }
        data = argv[i + 1];
        i++;
      }
    }
  }

  if(type == 0 || data == NULL)
  {
    fprintf(stderr, "Error, nothing provided to process!\n");
    return -1;
  }

  char* programCode = (type == 2) ? data : NULL;
  if(type == 1) {
    FILE* file = fopen(data, "r");
    if(file == NULL)
    {
      fprintf(stderr, "Error: Cannot open or read file, \"%s\"\n", data);
      return -1;
    }

    fseek(file, 0L, SEEK_END);
    size_t len = ftell(file);
    programCode = (char*) malloc(sizeof(char) * (len + 1));
    rewind(file);

    memset(programCode, 0, sizeof(char) * (len + 1));

    size_t readlen = fread((void*) programCode, 1, len, file);
    if(readlen < len)
    {
      fprintf(stderr, "Error reading file! Could only read %zi of %zi bytes\n", readlen, len);
      return -1;
    }
  }

  return interp(programCode);
}

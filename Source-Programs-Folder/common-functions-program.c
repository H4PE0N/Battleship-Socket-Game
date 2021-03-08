
#include "common-header-program.h"

void throw_error_message(char message[], int close)
{
  printf("[ERROR]: %s\n",message);if(close)exit(false);
}

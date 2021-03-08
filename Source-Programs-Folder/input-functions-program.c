
#include "common-header-program.h"

int extract_socket_role(char* arguments[], int arg_amount, char* sock_role)
{
  if((arg_amount - 1) < 1) return false;
  char* argument = sentence_index_string(arguments, 1);
  int length = sizeof(arguments[1]);
  sock_role = copy_character_string(argument, sock_role, length);
  return true;
}

/*
char message[] = "SOCKET ROLE NOT INPUTTED";
throw_error_message(message, true);
*/


#include "battleship-output-program.h"

void exit_and_print_message(char* error_message)
{
  printf("[ERROR]: %s\n", error_message); exit(false);
}

int display_server_message(char* server_message)
{
  printf("[SERVER]: %s\n",server_message); return true;
}

int display_client_message(char* client_message)
{
  printf("[CLIENT]: %s\n",client_message); return true;
}

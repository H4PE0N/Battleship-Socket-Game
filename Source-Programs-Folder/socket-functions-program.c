
#include "common-header-program.h"

int setup_socket_information(char sock_role[])
{
  char* address = generate_character_string(STR_SIZE);
  int port = -1; int sock_object = -1;

  int output = input_socket_information(address, &port);
  if(output == false) return sock_object;

  if(character_strings_equal(sock_role, "SERVER", 6))
  {
    sock_object = generate_server_socket(address, port);
  }
  if(character_strings_equal(sock_role, "CLIENT", 6))
  {
    sock_object = generate_client_socket(address, port);
  }
  return sock_object;
}

int input_socket_information(char* address, int* port)
{
  address = copy_character_string("192.168.1.113", address, 13);
  *port = 5555;
  return true;
}


#include "common-header-program.h"
#include <string.h>

int extract_socket_role(char* arguments[],
  char* sock_role)
{
  int length = character_string_length(arguments[1]);
  char* argument = sentence_index_string(arguments, 1);

  sock_role = copy_character_string(argument, sock_role,
    length);
  sock_role = convert_string_upper(sock_role, length);

  char* socket_roles[] = {"SERVER", "CLIENT"};

  int boolean = string_inside_sentence(sock_role, length,
    socket_roles, 2); return boolean;
}

int setup_socket_information(char sock_role[],
  int* sock_object)
{
  char* address = generate_character_string(STR_SIZE);
  int port = INT_NONE;

  int inpt_output = input_socket_information(address,
    &port); if(inpt_output == false) return false;

  int gen_output = generate_socket_variable(address, port,
    sock_role, sock_object); return gen_output;
}

int input_socket_information(char* address, int* port)
{
  char port_message[] = "PORT\t: ";
  char addr_message[] = "ADDRESS\t: ";

  if(!input_character_string(addr_message, address))
    return false;

  int length = character_string_length(address);
  if(character_strings_equal(address, "EXIT", length))
    return false;

  if(!input_integer_variable(port_message, port))
    return false;

  return (length != 0 && port != NULL);
}

int generate_socket_variable(char address[], int port,
  char sock_role[], int* sock_object)
{
  int gen_output = false;
  if(character_strings_equal(sock_role, "SERVER", 6))
  {
    gen_output = generate_server_socket(address, port,
      sock_object);
  }
  if(character_strings_equal(sock_role, "CLIENT", 6))
  {
    gen_output = generate_client_socket(address, port,
      sock_object);
  }
  return gen_output;
}

int generate_server_socket(char address[], int port,
  int* sock_object)
{
  int serv_socket = SOCK_NONE;
  int gen_output = generate_socket_object(AF_INET,
    SOCK_STREAM, 0, &serv_socket);
  if(gen_output == false) return false;

  int bind_output = bind_server_socket(&serv_socket,
    address, port); if(!bind_output) return false;

  int list_output=listen_for_connection(&serv_socket, 5);
  if(list_output == false) return false;

  int acpt_output = accept_connecting_client(&serv_socket,
    address, port, sock_object); return acpt_output;
}

int generate_client_socket(char address[], int port,
  int* sock_object)
{
  int gen_output = generate_socket_object(AF_INET,
    SOCK_STREAM, 0, sock_object);
  if(gen_output == false) return false;

  int cnct_output = connect_server_socket(sock_object,
    address, port); return cnct_output;
}

int generate_socket_object(int domain, int type,
  int protocol, int* sock_object)
{
  *sock_object = socket(domain, type, protocol);
  return (*sock_object != SOCK_NONE);
}

int bind_server_socket(int* serv_socket, char address[],
  int port)
{
  SERVADDR addr_object;
  int addr_output = generate_address_object(AF_INET,
    address, port, &addr_object);
  if(addr_output == false) return false;

  int bind_output = bind(*serv_socket, (SOCKADDR*)
  &addr_object, sizeof(addr_object));
  return (bind_output != BIND_NONE);
}

int listen_for_connection(int* serv_object, int backlog)
{
  int list_output = listen(*serv_object, backlog);
  return (list_output != LIST_NONE);
}

int accept_connecting_client(int* serv_socket,
  char address[], int port, int* sock_object)
{
  SERVADDR addr_object;
  int addr_output = generate_address_object(AF_INET,
    address, port, &addr_object);
  if(addr_output == false) return false;

  int addr_size = sizeof(addr_object);
  *sock_object = accept(*serv_socket, (SOCKADDR*)
  &addr_object, &addr_size);
  return (*sock_object != SOCK_NONE);
}

int connect_server_socket(int* serv_socket, char address[],
  int port)
{
  SERVADDR addr_object;
  int addr_output = generate_address_object(AF_INET,
    address, port, &addr_object);
  if(addr_output == false) return false;

  int cnct_output = connect(*serv_socket, (SOCKADDR*)
  &addr_object, sizeof(addr_object));
  return (cnct_output != CNCT_NONE);
}

int generate_address_object(int domain, char address[],
  int port, SERVADDR* addr_object)
{
  addr_object->sin_family = domain;
  addr_object->sin_port = htons(port);
  int inet_output = inet_pton(domain, address,
    &(addr_object->sin_addr)); return inet_output;
}

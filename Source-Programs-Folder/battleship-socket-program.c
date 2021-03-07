
#include "battleship-main-program.h"
#include "battleship-string-program.h"
#include "battleship-output-program.h"
#include "battleship-socket-program.h"
#include "battleship-ship-program.h"

int listen_for_connection(int server_socket, int backlog)
{
  int list_output = listen(server_socket, backlog);
  if(list_output != -1) return true;
  exit_and_print_message("WHEN LISTENING FOR CONNECTION");
}

int bind_server_socket(int server_socket, char* address, int port)
{
  serv_addr address_object = generate_address_object(AF_INET, address, port);
  int bind_output = bind(server_socket, (sock_addr*) &address_object, sizeof(address_object));
  if(bind_output != -1) return true;
  exit_and_print_message("WHEN BINDING SERVER SOCKET");
}

serv_addr generate_address_object(int sock_domain, char* address, int port)
{
  serv_addr address_object;
  address_object.sin_family = sock_domain;
  address_object.sin_port = htons(port);
  int inet_output = inet_pton(sock_domain, address, &address_object.sin_addr);
  if(inet_output != 0) return address_object;
  exit_and_print_message("ADDRESS OR PORT NOT EXSIST");
}

int generate_server_socket(int sock_domain, int sock_type, int protocol)
{
  int server_socket = socket(sock_domain, sock_type, protocol);
  if(server_socket != -1) return server_socket;
  exit_and_print_message("GENERATING SERVER SOCKET");
}

int connect_server_socket(int server_socket, char* address, int port)
{
  serv_addr address_object = generate_address_object(AF_INET, address, port);
  int conn_output = connect(server_socket, (sock_addr*) &address_object, sizeof(address_object));
  if(conn_output != -1) return true;
  exit_and_print_message("WHEN CONNECTING TO SERVER");
}

int accept_connecting_client(int server_socket, char* address, int port)
{
  serv_addr address_object = generate_address_object(AF_INET, address, port);
  int address_size = sizeof(address_object);

  int client_socket = accept(server_socket, (sock_addr*) &address_object, &address_size);

  if(client_socket != -1) return client_socket;
  exit_and_print_message("WHEN ACCEPTING CLIENT");
}

int socket_address_valid(char* address, int length)
{
  if(length > 0) return true;
  return false;
}

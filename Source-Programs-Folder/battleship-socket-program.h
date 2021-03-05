
#ifndef BATTLESHIP_SOCKET_PROGRAM_H
#define BATTLESHIP_SOCKET_PROGRAM_H

typedef struct sockaddr_in serv_addr;
typedef struct sockaddr sock_addr;

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <stdbool.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <arpa/inet.h>
#include <netinet/in.h>

int listen_for_connection(int, int);
int bind_server_socket(int, char*, int);

serv_addr generate_address_object(int, char*, int);
int generate_server_socket(int, int, int);

int connect_server_socket(int, char*, int);
int accept_connecting_client(int, char*, int);

int socket_address_valid(char*, int);

#endif

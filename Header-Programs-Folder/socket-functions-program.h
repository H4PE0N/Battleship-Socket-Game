
#ifndef SOCKET_FUNCTIONS_PROGRAM_H
#define SOCKET_FUNCTIONS_PROGRAM_H

#include <sys/types.h>
#include <sys/socket.h>

#include <arpa/inet.h>
#include <netinet/in.h>

typedef struct sockaddr_in SERVADDR;

typedef struct sockaddr SOCKADDR;

#define SOCK_NONE -1
#define BIND_NONE -1
#define LIST_NONE -1
#define CNCT_NONE -1

int setup_socket_information(char[], int*);

int generate_server_socket(char[], int, int*);

int generate_client_socket(char[], int, int*);

int bind_server_socket(int*, char[], int);

int listen_for_connection(int*, int);

int accept_connecting_client(int*, char[], int, int*);

int connect_server_socket(int*, char[], int);

int generate_address_object(int, char[], int, SERVADDR*);

int generate_socket_object(int, int, int, int*);

#endif

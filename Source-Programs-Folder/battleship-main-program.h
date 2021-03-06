
#ifndef BATTLESHIP_MAIN_PROGRAM_H
#define BATTLESHIP_MAIN_PROGRAM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

char* extract_socket_role(char*[], int);
void exit_and_print_message(char*);

int*** generate_board_battleships(char***, int);
int setup_socket_information(char*);

int input_socket_information(char*, int*);

int setup_server_socket(char*, int);
int setup_client_socket(char*, int);

int server_battleship_game(int, char***, char***, char*);
int client_battleship_game(int, char***, char***, char*);

void display_game_result(char***, char***, char*);

int*** input_battleship_positions(int***, char***);
int*** input_battleship_position(int***, int);

#endif

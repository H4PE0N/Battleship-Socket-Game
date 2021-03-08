
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

char* server_battleship_game(int, char***, char***, int***);
char* client_battleship_game(int, char***, char***, int***);

void display_game_result(char***, char***, char*);

int*** input_battleship_positions(int***, char***);
int*** input_battleship_position(int***, int);

int attack_opponent_coordinate(int, char***, char*);
int register_opponents_damage(int, char***, int***, char*);

int receive_opponents_coordinate(int, int*);
int send_registerd_damage(int, char*, int**);

char*** register_opponents_coordinate(int*, char***, int***, char*, int**);

int receive_opponents_protocol(int, char*, int**);
int send_attacking_coordinate(int, int*);
char*** register_protocol_coordinates(char*, int**, char***);

int* input_attacking_coordinate();
int generate_damage_protocol(char*, int**, char*);

int allocate_coordinate_protocol(int*, char*);

int defence_board_defeated(char***, int***, int*);
int defence_ship_defeated(int**, char***, int*);
int coordinate_hit_battleship(int*, int**);
#endif

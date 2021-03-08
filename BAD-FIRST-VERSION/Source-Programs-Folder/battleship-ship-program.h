
#ifndef BATTLESHIP_SHIP_PROGRAM_H
#define BATTLESHIP_SHIP_PROGRAM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int*** generate_battleship_array(int);
int*** allocate_battleships_ship(int***, int, int**);

int** generate_battleship_object(int*, int*);
int** allocate_array_coordinate(int**, int, int*);

int** random_vertical_battleship(int);
int** random_horizontal_battleship(int);

int* generate_coordinate_object(int, int);
int** generate_coordinate_objects(int);

int coordinate_index_value(int*, int);
int** battleships_index_ship(int***, int);

int generate_random_integer(int, int);

int generate_inputted_battleship(int***, int, int, char*);
int** generate_random_battleship(int***, int);

int convert_string_coordinate(char*, int, int*);
int convert_string_coordinates(char*, int, int**);

int board_coordinates_inside(int**, int, int);
int board_coordinate_inside(int*, int, int);

int battleship_valid_size(int**, int);
int battleship_position_valid(int***, int**);

int inputted_coordinates_valid(int**, int***, int);
int* array_index_coordinate(int**, int);

int coordinates_array_amount(int**);
int coordinate_variable_exsist(int*);

int battleship_over_battleship(int**, int**);

int* allocate_coordinate_value(int*, int, int);
int* allocate_coordinate_values(int*, int, int);

int** switch_battleship_coordinates(int**);

int** every_battleship_coordinate(int**);

int coordinate_inside_array(int*, int**, int);
int coordinate_objects_equal(int*, int*);

void display_battleship_board(char***, int, int);
void display_battleship_boards(char***, char***, int, int);
void display_board_width(char***, int, int);

#endif

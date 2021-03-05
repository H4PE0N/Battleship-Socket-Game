
#ifndef BATTLESHIP_SHIP_PROGRAM_H
#define BATTLESHIP_SHIP_PROGRAM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int*** generate_battleship_array(int);
int*** allocate_battleships_ship(int***, int, int**);

int** generate_battleship_object(int);
int** allocate_battleship_coordinate(int**, int, int*);

int* generate_coordinate_object(int, int);

#endif

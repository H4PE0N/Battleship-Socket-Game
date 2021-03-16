
#ifndef BATTLESHIP_FUNCTIONS_PROGRAM_H
#define BATTLESHIP_FUNCTIONS_PROGRAM_H

#define SHIP_AMOUNT 5

int generate_battleship_array(int***, int, char***);
char*** mark_battleship_position(char***, int**);
int generate_index_battleship(int***, int);
int input_battleship_position(int***, int, int**);
int convert_string_battleship(char[], int, int**);
int** array_index_battleship(int***, int);
int array_index_integer(int[], int);
int*** allocate_index_battleship(int***, int, int**);
int* generate_coordinate_object(int, int);
int array_coordinates_amount(int**);
int** append_every_coordinate(int**, int*, int*, int);
int** every_battleship_coordinate(int**);
int* array_index_coordinate(int**, int);
int coordinate_index_value(int[], int);
int* allocate_coordinate_value(int[], int, int);

#endif

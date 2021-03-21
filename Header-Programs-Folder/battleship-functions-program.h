
#ifndef BATTLESHIP_FUNCTIONS_PROGRAM_H
#define BATTLESHIP_FUNCTIONS_PROGRAM_H

#define SHIP_AMOUNT 5

static int ship_sizes[] = {2, 3, 3, 4, 5};

int generate_battleship_array(int***, int, char***, char***);
char*** mark_battleship_position(char***, int**);
int generate_index_battleship(int***, int, char***, char***);
int input_battleship_position(int***, int, int**);
int generate_inputted_battleship(char[], int, int**);
int** array_index_battleship(int***, int);
int*** allocate_array_battleship(int***, int, int**);
int* generate_coordinate_object(int, int);
int array_coordinates_amount(int**);
int** append_every_coordinate(int**, int*, int*, int);
int** every_battleship_coordinate(int**);
int* array_index_coordinate(int**, int);
int coordinate_index_value(int[], int);
int* allocate_coordinate_value(int[], int, int);
int convert_string_coordinate(char[], int, int*);
int input_string_battleship(int, char*);
int parse_inputted_battleship(char[], int, char**);
int** allocate_array_coordinate(int**, int, int*);
char*** mark_board_coordinate(char***, int*, char[]);
int coordinate_object_exists(int*);
int** generate_random_battleship(int***, int, int**);
int** copy_battleship_object(int**, int**);
int generate_random_integer(int, int);
int** allocate_ship_coordinates(int**, int*, int*);
int** random_horizontal_battleship(int);
int** random_vertical_battleship(int);
int battleship_object_exists(int**);
int** generate_battleship_object(int*, int*);
int array_battleships_amount(int***);
int battleship_over_battleship(int**, int**);
int integer_variables_equal(int, int);
int coordinate_inside_array(int*, int**, int);
int** battleships_index_ship(int***, int);
int battleship_position_valid(int**, int***);
int coordinate_objects_equal(int*, int*);
int convert_string_coordinates(char[], int, int**);
int** switch_ship_coordinates(int**);
int battleship_order_valid(int*, int*);
int* duplicate_coordinate_object(int*);

#endif

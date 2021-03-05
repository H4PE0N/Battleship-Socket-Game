
#ifndef BATTLESHIP_STRING_PROGRAM_H
#define BATTLESHIP_STRING_PROGRAM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

char string_index_character(char*, int);
char* sentence_index_string(char**, int);

char* allocate_string_character(char*, int, char);
int character_between_integers(char, int, int);

char convert_character_upper(char);
char* convert_string_upper(char*, int);

int character_string_length(char*);
int sentence_string_length(char**, int);

int sentence_string_amount(char**);
char* generate_character_string(int);

int character_variables_equal(char, char);
int character_strings_equal(char*, char*, int);

int string_inside_sentence(char*, int, char**, int);

char** generate_string_sentence(int, int);
char*** generate_string_matrix(int, int);

char*** allocate_matrix_sentence(char***, int, char**);
char** allocate_sentence_string(char**, int, char*);

int character_inside_string(char, char*, int);


#endif

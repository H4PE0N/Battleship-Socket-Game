
#ifndef STRING_FUNCTIONS_PROGRAM_H
#define STRING_FUNCTIONS_PROGRAM_H

int character_string_length(char[]);

char* copy_character_string(char[], char*, int);

char string_index_character(char[], int);

char* allocate_string_character(char*, int, char);

char* sentence_index_string(char**, int);

char* generate_character_string(int);

int character_values_equal(char, char);

int character_strings_equal(char[], char[], int);

char* convert_string_upper(char*, int);

char convert_character_upper(char);

int character_between_integers(char, int, int);

#endif

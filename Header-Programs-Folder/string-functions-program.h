
#ifndef STRING_FUNCTIONS_PROGRAM_H
#define STRING_FUNCTIONS_PROGRAM_H

char* generate_character_string(int);
char* allocate_string_character(char*, int, char);
char* sentence_index_string(char**, int);
char* convert_string_upper(char*, int);
char convert_character_upper(char);
int character_range_between(char, int, int);
int character_smaller_than(char, int);
int character_greater_than(char, int);
char string_index_character(char[], int);
int character_string_length(char[]);
char* copy_character_string(char[], char*, int);
int character_values_equal(char, char);
int character_strings_equal(char[], char[], int);
int string_inside_sentence(char[], int, char*[], int);
int input_character_string(char[], char*);
int input_integer_variable(char[], int*);
char** allocate_sentence_string(char**, int, char[]);

#endif

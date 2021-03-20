
#ifndef CHARACTER_STRING_FUNCTIONS_H
#define CHARACTER_STRING_FUNCTIONS_H

char* generate_character_string(int);
char** generate_character_sentence(int, int);
char*** generate_character_paper(int, int, int);

char* allocate_string_character(char*, int, char);
char** allocate_sentence_character(char**, int, int, char);
char*** allocate_paper_character(char***, int, int, int, char);

char string_index_character(char*, int);
char sentence_index_character(char**, int, int);
char paper_index_character(char***, int, int, int);

char* sentence_index_string(char**, int);
char* paper_index_string(char***, int, int);

char** paper_index_sentence(char***, int);

char** allocate_sentence_string(char**, int, char*);
char*** allocate_paper_string(char***, int, int, char*);

char*** allocate_paper_sentence(char***, int, char**);

#endif

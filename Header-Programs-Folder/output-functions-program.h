
#ifndef OUTPUT_FUNCTIONS_PROGRAM_H
#define OUTPUT_FUNCTIONS_PROGRAM_H

#define MARK_NUM 2
#define CHAR_NONE '\0'

static char board_nums[] = "|  1 2 3 4 5 6 7 8 9 10 |";
static char board_line[] = "+-----------------------+";

char** extract_file_information(char[], int);
char*** extract_board_markers(char[], int);
void display_board_sentence(char***, int, int, char***);
void display_battleship_boards(char***, char***, int, int);
char** split_keyword_marker(char[]);
char*** extract_board_markers(char[], int);
char* markers_index_keyword(char***, int);
char markers_index_marker(char***, int);
char markers_keyword_marker(char***, int, char[]);
char alphabet_index_letter(char[], int);

#endif


#ifndef OUTPUT_FUNCTIONS_PROGRAM_H
#define OUTPUT_FUNCTIONS_PROGRAM_H

#define MARK_NUM 2
#define CHAR_NONE '\0'

char alphabet[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G',
  'H', 'I', CHAR_NONE};

char filename[] = "../markers.txt";

char** extract_file_information(char[], int, int);
char*** extract_board_markers(char[], int);
void display_board_sentence(char***, int, int);
void display_battleship_board(char***, int, int);
void display_battleship_boards(char***, char***, int, int);
char** extract_file_information(char[], int, int);
char** split_keyword_marker(char[]);
char*** extract_board_markers(char[], int);
char* markers_index_keyword(char***, int);
char markers_index_marker(char***, int);
char markers_keyword_marker(char***, int, char[]);
char alphabet_index_letter(char[], int);

#endif

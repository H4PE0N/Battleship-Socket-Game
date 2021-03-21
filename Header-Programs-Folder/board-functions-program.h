
#ifndef BOARD_FUNCTIONS_PROGRAM_H
#define BOARD_FUNCTIONS_PROGRAM_H

#define BOARD_HEIGHT 10
#define BOARD_WIDTH 10

char*** generate_battleship_board(int, int);
char*** generate_index_sentence(char***, int, int);

char*** allocate_board_keyword(char***, int, int, char[]);
char* board_index_keyword(char***, int, int);

#endif

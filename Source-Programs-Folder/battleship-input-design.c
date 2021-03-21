
#include "common-header-program.h"

void display_battleship_input(char*** def_board, char*** off_board, int number, int size)
{
  int height = BOARD_HEIGHT, width = BOARD_WIDTH;
  display_battleship_boards(def_board, off_board, height, width);
  display_ship_information(number, size);
  display_battleship_choices((char*[]) {"A1", "A2"});
}

void display_ship_information(int number, int size)
{
  printf("+-------------------------------+\n");
  printf("| BATTLESHIP NUMBER\t: %d\t|\n", number);
  printf("| BATTLESHIP SIZE\t: %d\t|\n", size);
  printf("+-------------------------------+\n");
}

void display_battleship_choices(char** coordinates)
{
  printf("+-------------------------------+\n");
  char* first = sentence_index_string(coordinates, 0);
  char* second = sentence_index_string(coordinates, 1);
  printf("| BATTLESHIP POSITION\t(%s %s)\t|\n", first, second);
  printf("| RANDOM POSITION\tRANDOM\t|\n");
  printf("+-------------------------------+\n");
}

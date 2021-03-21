
#include "common-header-program.h"

char*** generate_battleship_board(int height, int width)
{
  char*** board = generate_character_paper(height, width, STR_SIZE);
  for(int index = 0; index < height; index = index + 1)
  {
    board = generate_index_sentence(board, index, width);
  }
  return board;
}

char*** generate_index_sentence(char*** board, int height,
  int width)
{
  for(int index = 0; index < width; index = index + 1)
  {
    board = allocate_board_keyword(board, height, index, "EMPTY");
  }
  return board;
}

char*** allocate_board_keyword(char*** board, int height,
  int width, char keyword[])
{
  board = allocate_paper_string(board, height, width, keyword);
  return board;
}

char* board_index_keyword(char*** board, int height,
  int width)
{
  char** sentence = paper_index_sentence(board, height);
  char* keyword = sentence_index_string(sentence, width);
  return keyword;
}

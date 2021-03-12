
#include "common-header-program.h"

char*** generate_battleship_board(int height, int width)
{
  char*** board = malloc(sizeof(char**) * (height + 1));
  for(int index = 0; index < (height + 1); index += 1)
  {
    *(board + index) = malloc(sizeof(char*) * width);
    board = generate_index_sentence(board, index, width);
  }
  return board;
}

char*** generate_index_sentence(char*** board, int height,
  int width)
{
  for(int index = 0; index < width; index = index + 1)
  {
    board = allocate_board_keyword(board, height, index,
      "EMPTY");
  }
  return board;
}

char*** allocate_board_keyword(char*** board, int height,
  int width, char keyword[])
{
  char** sentence = board_index_sentence(board, height);
  *(sentence + width) = keyword; return board;
}

char** board_index_sentence(char*** board, int index)
{
  char** sentence = *(board + index); return sentence;
}

char* board_index_keyword(char*** board, int height,
  int width)
{
  char** sentence = board_index_sentence(board, height);
  char* keyword = sentence_index_string(sentence, width);
  return keyword;
}


#include "battleship-main-program.h"
#include "battleship-string-program.h"
#include "battleship-output-program.h"
#include "battleship-socket-program.h"
#include "battleship-ship-program.h"

char string_index_character(char* string, int index)
{
  char character = *(string + index); return character;
}

char* sentence_index_string(char** sentence, int index)
{
  char* string = *(sentence + index); return string;
}

char* allocate_string_character(char* string, int index, char character)
{
  *(string + index) = character; return string;
}

int character_between_integers(char character, int first, int second)
{
  int boolean = (character >= first && character <= second);
  return boolean;
}

char convert_character_upper(char character)
{
  if(character_between_integers(character, 97, 122))
  {
    return (character - 32);
  }
  return character;
}

char* convert_string_upper(char* string, int length)
{
  for(int index = 0; index < length; index = index + 1)
  {
    char character = string_index_character(string, index);
    character = convert_character_upper(character);
    string = allocate_string_character(string, index, character);
  }
  return string;
}

char escape_chars[] = {'\0', '\n'};

int character_string_length(char* string)
{
  int length = 0;
  while(!character_inside_string(string[length], escape_chars, 3))
  {
    length = (length + 1);
  }
  return length;
}

int character_inside_string(char character, char* string, int length)
{
  for(int index = 0; index < length; index = index + 1)
  {
    char current = string_index_character(string, index);
    if(character_variables_equal(character, current))
    {
      return true;
    }
  }
  return false;
}

int sentence_string_length(char** sentence, int index)
{
  char* string = sentence_index_string(sentence, index);
  int length = character_string_length(string);
  return length;
}

int sentence_string_amount(char** sentence)
{
  int amount = 0;
  while(sentence_string_length(sentence, amount) != 0)
  {
    amount = (amount + 1);
  }
  return amount;
}

char* generate_character_string(int length)
{
  char* string = malloc(sizeof(*string) * length);
  for(int index = 0; index < length; index = index + 1)
  {
    *(string + index) = '\0';
  }
  return string;
}

int character_variables_equal(char first, char second)
{
  int boolean = (first == second); return boolean;
}

int character_strings_equal(char* first, char* second, int length)
{
  for(int index = 0; index < length; index = index + 1)
  {
    char first_char = string_index_character(first, index);
    char second_char = string_index_character(second, index);
    if(!character_variables_equal(first_char, second_char))
    {
      return false;
    }
  }
  return true;
}

int string_inside_sentence(char* string, int length, char** sentence, int height)
{
  for(int index = 0; index < height; index = index + 1)
  {
    char* current = sentence_index_string(sentence, index);
    int current_len = character_string_length(current);

    int comp_length = length;
    if(current_len > length) comp_length = current_len;

    if(character_strings_equal(string, current, comp_length))
    {
      return true;
    }
  }
  return false;
}

char** allocate_sentence_string(char** sentence, int index, char* string)
{
  *(sentence + index) = string; return sentence;
}

char** generate_string_sentence(int height, int width)
{
  char** sentence = malloc(sizeof(char**) * height);
  for(int index = 0; index < height; index = index + 1)
  {
    char* string = generate_character_string(width);
    sentence = allocate_sentence_string(sentence, index, string);
  }
  return sentence;
}

char*** allocate_matrix_sentence(char*** matrix, int index, char** sentence)
{
  *(matrix + index) = sentence; return matrix;
}

char*** generate_string_matrix(int height, int width)
{
  char*** matrix = malloc(sizeof(char**) * height);
  for(int index = 0; index < height; index = index + 1)
  {
    char** sentence = generate_string_sentence(width, 200);
    matrix = allocate_matrix_sentence(matrix, index, sentence);
  }
  return matrix;
}

int string_character_index(char* string, int length, char character)
{
  for(int index = 0; index < length; index = index + 1)
  {
    char current = string_index_character(string, index);
    if(character_variables_equal(current, character))
    {
      return index;
    }
  }
  return -1;
}

char* character_string_section(char* string, int first, int second)
{
  int length = (second - first + 1);
  char* section = generate_character_string(length);
  for(int index = 0; index < length; index = index + 1)
  {
    int curr_index = (index + first);
    char character = string_index_character(string, curr_index);
    section = allocate_string_character(section, index, character);
  }
  return section;
}

int split_character_string(char* string, int length, char character, char** split_string)
{
  if(length <= 2) return false;

  int index = string_character_index(string, length, character);
  if(index == -1) return false;

  char* first = character_string_section(string, 0, index - 1);
  char* second = character_string_section(string, index + 1, length - 1);

  split_string = allocate_sentence_string(split_string, 0, first);
  split_string = allocate_sentence_string(split_string, 1, second);
  return true;
}

int markers_keyword_index(char markers[][2][200], int amount, char* keyword)
{
  int length = character_string_length(keyword);
  for(int index = 0; index < amount; index = index + 1)
  {
    char* current = markers[index][0];
    if(character_strings_equal(current, keyword, length))
    {
      return index;
    }
  }
  return -1;
}

char*** set_coordinate_keyword(char*** board, int* coordinate, char* keyword)
{
  int h_index = coordinate_index_value(coordinate, 0);
  int w_index = coordinate_index_value(coordinate, 1);
  board[h_index][w_index] = keyword;
  return board;
}

char*** set_coordinates_keyword(char*** board, int** coordinates, char* keyword)
{
  int amount = coordinates_array_amount(coordinates);
  for(int index = 0; index < amount; index = index + 1)
  {
    int* coordinate = array_index_coordinate(coordinates, index);
    board = set_coordinate_keyword(board, coordinate, keyword);
  }
  return board;
}

char*** generate_battleship_board(int height, int width)
{
  char*** board = malloc(sizeof(char**) * height);
  for(int h_index = 0; h_index < height; h_index += 1)
  {
    board[h_index] = malloc(sizeof(char*) * width);
    for(int w_index = 0; w_index < width; w_index += 1)
    {
      board[h_index][w_index] = "EMPTY";
    }
  }
  return board;
}

int convert_string_coordinates(char* string, int length, int** coordinates)
{
  char** split_string = generate_string_sentence(length, length);
  int split_output = split_character_string(string, length, ' ', split_string);
  if(split_output == false) return false;

  for(int index = 0; index < 2; index = index + 1)
  {
    char* curr_str = sentence_index_string(split_string, index);
    int string_len = character_string_length(curr_str);

    int cord_output = convert_string_coordinate(curr_str, string_len, coordinates[index]);
    if(cord_output == false) return false;

    coordinates = allocate_array_coordinate(coordinates, index, coordinates[index]);
  }
  return true;
}

char* board_coordinate_keyword(char*** board, int* coordinate)
{
  int h_index = coordinate_index_value(coordinate, 0);
  int w_index = coordinate_index_value(coordinate, 1);
  return board[h_index][w_index];
}

char alphabet[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', '\0'};
char markers[5][2][200] = {{"BATTLESHIP\0", "#"}, {"MISS\0", "+"}, {"HIT\0", "X"}, {"SUNKEN\0", "$"}, {"EMPTY\0", "."}};

char numbers[] = "  1 2 3 4 5 6 7 8 9 10";

void display_board_width(char*** board, int width, int height)
{
  printf("%c ", string_index_character(alphabet, height));
  for(int index = 0; index < width; index = index + 1)
  {
    char* keyword = board[height][index];
    int mark_index = markers_keyword_index(markers, 5, keyword);
    //if(mark_index == -1); marker = ""; 
    char marker = markers[mark_index][1][0];
    printf("%c ", marker);
  }
}

void display_battleship_boards(char*** first, char*** second, int height, int width)
{
  printf("%s\t%s\n", numbers, numbers);
  for(int index = 0; index < height; index = index + 1)
  {
    display_board_width(first, width, index);
    printf("\t");
    display_board_width(second, width, index);
    printf("\n");
  }
  printf("\n");
}

void display_battleship_board(char*** board, int height, int width)
{
  printf("%s\n", numbers);
  for(int index = 0; index < height; index = index + 1)
  {
    display_board_width(board, width, index);
    printf("\n");
  }
  printf("\n");
}

int convert_string_coordinate(char* string, int length, int* coordinate)
{
  char letter = string_index_character(string, 0);
  int number = atoi(character_string_section(string, 1, length - 1));

  int index = string_character_index(alphabet, 10, letter);
  if(index == -1) return false;

  coordinate[0] = index;
  coordinate[1] = (number - 1);
  return true;
}

int convert_coordinate_string(int* coordinate, char* string)
{
  int first = coordinate_index_value(coordinate, 0);
  int second = coordinate_index_value(coordinate, 1);

  int length = character_string_length(alphabet);
  if(first < 0 || first >= length) return false;

  char letter = string_index_character(alphabet, first);
  char number = (second + '1');

  string = allocate_string_character(string, 0, letter);
  string = allocate_string_character(string, 1, number);

  return true;
}


#include "common-header-program.h"

int generate_battleship_array(int*** battleships, int amount, char*** def_board)
{
  int height = BOARD_HEIGHT, width = BOARD_WIDTH;
  for(int index = 0; index < amount; index = index + 1)
  {
    display_battleship_board(def_board, height, width);

    int gnrt_output = generate_index_battleship(battleships, index);
    if(gnrt_output == false) return false;

    int** battleship = array_index_battleship(battleships, index);
    def_board = mark_battleship_position(def_board, battleship);
  }
  return true;
}

int generate_index_battleship(int*** battleships, int index)
{
  int** battleship = array_index_battleship(battleships, index);

  int inpt_output = input_battleship_position(battleships, index, battleship);
  if(inpt_output == false) return false;

  battleships = allocate_index_battleship(battleships, index, battleship);
  return true;
}

int* generate_array_memory(int length)
{
  int* array = malloc(sizeof(int) * (length + 1));
  for(int index = 0; index < (length + 1); index = index + 1)
  {
    array = allocate_array_integer(array, index, INT_NONE);
  }
  return array;
}

int** generate_matrix_memory(int height, int width)
{
  int** matrix = malloc(sizeof(int*) * (height + 1));
  for(int index = 0; index < (height + 1); index = index + 1)
  {
    int* array = generate_array_memory(width);
    matrix = allocate_matrix_array(matrix, index, array);
  }
  return matrix;
}

int*** matrix_array_memory(int amount, int height, int width)
{
  int*** array = malloc(sizeof(int**) * (amount + 1));
  for(int index = 0; index < (amount + 1); index = index + 1)
  {
    int** matrix = generate_matrix_memory(height, width);
    array = allocate_array_matrix(array, index, matrix);
  }
  return array;
}

int input_battleship_position(int*** battleships, int index, int** battleship)
{
  int ship_sizes[] = {2, 3, 3, 4, 5};
  int size = array_index_integer(ship_sizes, index);

  char input_message[STR_SIZE], string[STR_SIZE];
  sprintf(input_message, "BATTLESHIP #%d [SIZE: %d]: ", index + 1, size);
  int inpt_output = input_character_string(input_message, string);

  int length = character_string_length(string);
  if(character_strings_equal(string, "EXIT", length))
    return false;

  int conv_output = convert_string_battleship(string, length, battleship);
  if(conv_output == true) return true;

  return input_battleship_position(battleships, index, battleship);
}

int convert_string_battleship(char string[], int length, int** battleship)
{
  char** strings = generate_string_sentence(2, STR_SIZE);
  int prse_output = sscanf(string, "%s %s", strings[0], strings[1]);
  if(prse_output == false) return false;

  for(int index = 0; index < 2; index = index + 1)
  {
    char* current = sentence_index_string(strings, index);
    int curr_length = character_string_length(current);

    int** battleship = array_index_battleship(battleships, index);
    int conv_output = convert_string_coordinate(current, curr_length, battleship);
    if(conv_output == false) return false;
  }
  return true;
}

int* convert_string_coordinate(char string[], int length)
{
  char letter; int number;
  int prse_output = sscanf(string, "%c%d", &letter, &number);
  if(prse_output == false) return false;

  int index = string_character_index(alphabet, letter);
}

char*** mark_battleship_position(char*** def_board, int** battleship)
{
  int** every_cord = every_battleship_coordinate(battleship);
  int amount = array_coordinates_amount(every_cord);
  for(int index = 0; index < amount; index = index + 1)
  {
    int* coordinate = array_index_coordinate(every_cord, index);
    int height = coordinate_index_value(coordinate, 0);
    int width = coordinate_index_value(coordinate, 1);
    def_board = allocate_board_keyword(def_board, height, width, "BATTLESHIP");
  }
  return def_board;
}

int array_index_integer(int array[], int index)
{
  int integer = *(array + index); return integer;
}

int** array_index_battleship(int***battleships,int index)
{
  int** battleship=battleships[index]; return battleship;
}

int*** allocate_index_battleship(int*** battleships,
  int index, int** battleship)
{
  *(battleships + index) = battleship; return battleships;
}

int** every_battleship_coordinate(int** battleship)
{
  int** every_cord = malloc(sizeof(int*) * 10);
  int* first = array_index_coordinate(battleship, 0);
  int* second = array_index_coordinate(battleship, 1);
  for(int height = first[0]; height <= second[0]; height++)
  {
    every_cord = append_every_coordinate(every_cord, first, second, height);
  }
  return every_cord;
}

int** append_every_coordinate(int** every_cord, int* first, int* second, int height)
{
  for(int width = first[1]; width <= second[1]; width++)
  {
    int* coordinate = generate_coordinate_object(height, width);
    int amount = array_coordinates_amount(every_cord);
    *(every_cord + amount) = coordinate;
  }
  return every_cord;
}

int array_coordinates_amount(int** coordinates)
{
  int amount = 0;
  for(amount; coordinates[amount] != NULL; amount += 1)
  return amount;
}

int* generate_coordinate_object(int first, int second)
{
  int* coordinate = malloc(sizeof(int) * (2 + 1));
  coordinate = allocate_coordinate_value(coordinate, 0, first);
  coordinate = allocate_coordinate_value(coordinate, 1, second);
  return coordinate;
}

int* array_index_coordinate(int** coordinates, int index)
{
  int* coordinate = coordinates[index]; return coordinate;
}

int coordinate_index_value(int coordinate[], int index)
{
  int integer = *(coordinate + index); return integer;
}

int* allocate_coordinate_value(int coordinate[],
  int index, int integer)
{
  *(coordinate + index) = integer; return coordinate;
}


#include "common-header-program.h"

int generate_battleship_array(int*** battleships, int amount, char*** def_board, char*** off_board)
{
  for(int index = 0; index < amount; index = index + 1)
  {
    int gnrt_output = generate_index_battleship(battleships, index, def_board, off_board);
    if(gnrt_output == false) return false;
  }
  return true;
}

int generate_index_battleship(int*** battleships, int index, char*** def_board, char*** off_board)
{
  int** battleship = array_index_battleship(battleships, index);

  int number = index + 1;
  int size = array_index_integer(ship_sizes, index);
  display_battleship_input(def_board, off_board, number, size);

  int inpt_output = input_battleship_position(battleships, index, battleship);
  if(inpt_output == false) return false;

  battleships = allocate_array_battleship(battleships, index, battleship);
  printf("%d-%d %d-%d\n", battleship[0][0], battleship[0][1], battleship[1][0], battleship[1][1]);
  def_board = mark_battleship_position(def_board, battleship);

  return true;
}

int input_battleship_position(int*** battleships, int index, int** battleship)
{
  char* string = generate_character_string(STR_SIZE);
  int inpt_output = input_string_battleship(index, string);
  if(inpt_output == false) return false;

  int length = character_string_length(string);
  if(character_strings_equal(string, "EXIT", length))
    return false;

  if(character_strings_equal(string, "RANDOM", length))
  {
    battleship = generate_random_battleship(battleships, index, battleship);
  }
  else if(!generate_inputted_battleship(string, length, battleship))
  {
    return input_battleship_position(battleships, index, battleship);
  }
  return true;
}

int generate_random_integer(int minimum, int maximum)
{
  int integer = (minimum + (rand() % (maximum - minimum + 1)) );
  return integer;
}

int** generate_random_battleship(int*** battleships, int index, int** battleship)
{
  int size = array_index_integer(ship_sizes, index);
  int** random_ship = random_vertical_battleship(size);
  if(generate_random_integer(false, true) == true)
  {
    random_ship = random_vertical_battleship(size);
  }

  if(battleship_position_valid(random_ship, battleships))
  {
    battleship = copy_battleship_object(random_ship, battleship);
    return battleship;
  }
  return generate_random_battleship(battleships, index, battleship);
}

int** copy_battleship_object(int** copying, int** battleship)
{
  for(int index = 0; index < 2; index = index + 1)
  {
    int* coordinate = array_index_coordinate(copying, index);
    battleship = allocate_array_coordinate(battleship, index, coordinate);
  }
  return battleship;
}

int battleship_position_valid(int** battleship, int*** battleships)
{
  int amount = array_battleships_amount(battleships);
  for(int index = 0; index < 5; index = index + 1) // CHANGE 5 TO AMOUNT
  {
    int** current = battleships_index_ship(battleships, index);

    if(battleship_over_battleship(current, battleship))
    {
      return false;
    }
  }
  return true;
}

int** battleships_index_ship(int*** battleships, int index)
{
  int** battleship = block_index_matrix(battleships, index);
  return battleship;
}

int battleship_over_battleship(int** first, int** second)
{
  int** f_cords = every_battleship_coordinate(first);
  int** s_cords = every_battleship_coordinate(second);

  int f_amount = array_coordinates_amount(f_cords);
  int s_amount = array_coordinates_amount(s_cords);

  for(int index = 0; index < f_amount; index = index + 1)
  {
    int* coordinate = array_index_coordinate(f_cords, index);

    if(coordinate_inside_array(coordinate, s_cords, s_amount))
    {
      return true;
    }
  }
  return false;
}

int coordinate_inside_array(int* coordinate, int** coordinates, int amount)
{
  for(int index = 0; index < amount; index = index + 1)
  {
    int* current = array_index_coordinate(coordinates, index);
    if(coordinate_objects_equal(coordinate, current))
    {
      return true;
    }
  }
  return false;
}

int coordinate_objects_equal(int* first, int* second)
{
  for(int index = 0; index < 2; index = index + 1)
  {
    int f_cord = coordinate_index_value(first, index);
    int s_cord = coordinate_index_value(second, index);

    if(!integer_variables_equal(f_cord, s_cord))
    {
      return false;
    }
  }
  return true;
}

int integer_variables_equal(int first, int second)
{
  int boolean = (first == second); return boolean;
}

int array_battleships_amount(int*** battleships)
{
  for(int amount = 0; true; amount = amount + 1)
  {
    int** battleship = array_index_battleship(battleships, amount);
    if(!battleship_object_exists(battleship))
    {
      return amount;
    }
  }
  return false;
}

int battleship_object_exists(int** battleship)
{
  int amount = array_coordinates_amount(battleship);
  return (amount == 2);
}

int** random_vertical_battleship(int size)
{
  int range = (10 - size - 1);

  int height = generate_random_integer(0, range);
  int width = generate_random_integer(0, 10 - 1);

  int* first = generate_coordinate_object(height, width);
  int* second = generate_coordinate_object(height + size - 1, width);

  return generate_battleship_object(first, second);
}

int** allocate_ship_coordinates(int** battleship, int* first, int* second)
{
  battleship = allocate_array_coordinate(battleship, 0, first);
  battleship = allocate_array_coordinate(battleship, 1, second);
  return battleship;
}

int** random_horizontal_battleship(int size)
{
  int range = (10 - size - 1);

  int height = generate_random_integer(0, 10 - 1);
  int width = generate_random_integer(0, range);

  int* first = generate_coordinate_object(height, width);
  int* second = generate_coordinate_object(height, width + size - 1);

  return generate_battleship_object(first, second);
}

int** generate_battleship_object(int* first, int* second)
{
  int** battleship = generate_integer_matrix(2, 2);
  battleship = allocate_array_coordinate(battleship, 0, first);
  battleship = allocate_array_coordinate(battleship, 1, second);
  return battleship;
}

int input_string_battleship(int index, char* string)
{
  int size = array_index_integer(ship_sizes, index);
  char message[] = "[?] BATTLESHIP POSITION : ";

  int inpt_output = input_character_string(message, string);
  if(inpt_output == false) return false;

  int length = character_string_length(string);
  string = convert_string_upper(string, length);
  return true;
}

int generate_inputted_battleship(char string[], int length, int** battleship)
{
  int** coordinates = generate_integer_matrix(2, 2);
  int conv_output = convert_string_coordinates(string, length, coordinates);
  if(conv_output == false) return false;

  coordinates = switch_ship_coordinates(coordinates);

}

int** switch_ship_coordinates(int** battleship)
{
  int* first = array_index_coordinate(battleship, 0);
  int* second = array_index_coordinate(battleship, 1);
  if(battleship_order_valid(first, second))
    return battleship;

  int* temp_cord = duplicate_coordinate_object(first);
  first = duplicate_coordinate_object(second);
  second = duplicate_coordinate_object(temp_cord);

  return battleship;
}

int* duplicate_coordinate_object(int* coordinate)
{
  int first = coordinate_index_value(coordinate, 0);
  int second = coordinate_index_value(coordinate, 1);
  return generate_coordinate_object(first, second);
}

int battleship_order_valid(int* first, int* second)
{
  for(int index = 0; index < 2; index = index + 1)
  {
    int first_int = coordinate_index_value(first, index);
    int second_int = coordinate_index_value(second, index);
    if(first_int > second_int) return false;
  }
  return true;
}

int convert_string_coordinates(char string[], int length, int** coordinates)
{
  char** sentence = generate_character_sentence(2, STR_SIZE);
  int prse_output = parse_inputted_battleship(string, length, sentence);
  if(prse_output == false) return false;

  for(int index = 0; index < 2; index = index + 1)
  {
    char* current = sentence_index_string(sentence, index);
    int curr_length = character_string_length(current);

    int* coordinate = array_index_coordinate(coordinates, index);

    int conv_output = convert_string_coordinate(current, curr_length, coordinate);
    if(conv_output == false) return false;
  }
  return true;
}

int parse_inputted_battleship(char string[], int length, char** sentence)
{
  char* first = sentence_index_string(sentence, 0);
  char* second = sentence_index_string(sentence, 1);

  int prse_output = sscanf(string, "%s %s", first, second);
  return (prse_output == 2);
}

int convert_string_coordinate(char string[], int length, int* coordinate)
{
  char letter; int number;
  int prse_output = sscanf(string, "%c%d", &letter, &number);
  if(prse_output == false) return false;

  int index = string_character_index(alphabet, 26, letter);
  if(index == INT_NONE) return false;

  coordinate = allocate_coordinate_value(coordinate, 0, index);
  coordinate = allocate_coordinate_value(coordinate, 1, number - 1);
  return true;
}

char*** mark_battleship_position(char*** def_board, int** battleship)
{
  int** every_cord = every_battleship_coordinate(battleship);
  int amount = array_coordinates_amount(every_cord);
  for(int index = 0; index < amount; index = index + 1)
  {
    int* coordinate = array_index_coordinate(every_cord, index);
    def_board = mark_board_coordinate(def_board, coordinate, "BATTLESHIP");
  }
  return def_board;
}

char*** mark_board_coordinate(char*** board, int* coordinate, char keyword[])
{
  int height = coordinate_index_value(coordinate, 0);
  int width = coordinate_index_value(coordinate, 1);
  board = allocate_board_keyword(board, height, width, keyword);
  return board;
}

int** array_index_battleship(int*** battleships, int index)
{
  int** battleship = block_index_matrix(battleships, index);
  return battleship;
}

int*** allocate_array_battleship(int*** battleships,
  int index, int** battleship)
{
  battleships = allocate_block_matrix(battleships, index, battleship);
  return battleships;
}

int** every_battleship_coordinate(int** battleship)
{
  int** every_cord = generate_integer_matrix(10, 2);
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
  for(int amount = 0; true; amount = amount + 1)
  {
    int* coordinate = array_index_coordinate(coordinates, amount);
    if(!coordinate_object_exists(coordinate))
    {
      return amount;
    }
  }
  return false;
}

int coordinate_object_exists(int* coordinate)
{
  int first = coordinate_index_value(coordinate, 0);
  int second = coordinate_index_value(coordinate, 1);
  return (first != INT_NONE && second != INT_NONE);
}

int* generate_coordinate_object(int first, int second)
{
  int* coordinate = generate_integer_array(2);
  coordinate = allocate_coordinate_value(coordinate, 0, first);
  coordinate = allocate_coordinate_value(coordinate, 1, second);
  return coordinate;
}

int* array_index_coordinate(int** coordinates, int index)
{
  int* coordinate = matrix_index_array(coordinates, index);
  return coordinate;
}

int** allocate_array_coordinate(int** coordinates, int index, int* coordinate)
{
  coordinates = allocate_matrix_array(coordinates, index, coordinate);
  return coordinates;
}

int coordinate_index_value(int coordinate[], int index)
{
  int integer = array_index_integer(coordinate, index);
  return integer;
}

int* allocate_coordinate_value(int coordinate[], int index, int integer)
{
  coordinate = allocate_array_integer(coordinate, index, integer);
  return coordinate;
}

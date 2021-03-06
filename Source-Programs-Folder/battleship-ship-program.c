
#include "battleship-ship-program.h"
#include "battleship-string-program.h"

int*** generate_battleship_array(int amount)
{
  int*** battleships = malloc(sizeof(int**) * (amount + 1));
  for(int index = 0; index < (amount + 1); index = index + 1)
  {
    int** battleship = generate_battleship_object(2 + 1);
    battleships = allocate_battleships_ship(battleships, index, battleship);
  }
  return battleships;
}

int*** allocate_battleships_ship(int*** battleships, int index, int** battleship)
{
  *(battleships + index) = battleship; return battleships;
}

int* allocate_coordinate_values(int* coordinate, int first, int second)
{
  coordinate = allocate_coordinate_value(coordinate, 0, first);
  coordinate = allocate_coordinate_value(coordinate, 1, second);
  return coordinate;
}

int** generate_battleship_object(int amount)
{
  int** battleship = generate_coordinate_objects(amount);
  return battleship;
}

int** generate_coordinate_objects(int amount)
{
  int** coordinates = malloc(sizeof(int*) * amount);
  for(int index = 0; index < amount; index = index + 1)
  {
    int* coordinate = generate_coordinate_object(-1, -1);
    coordinates = allocate_array_coordinate(coordinates, index, coordinate);
  }
  return coordinates;
}

int* generate_coordinate_object(int first, int second)
{
  int* coordinate = malloc(sizeof(int) * 2);
  coordinate = allocate_coordinate_values(coordinate, first, second);
  return coordinate;
}

int* duplicate_coordinate_object(int* coordinate)
{
  int first = coordinate_index_value(coordinate, 0);
  int second = coordinate_index_value(coordinate, 1);
  return generate_coordinate_object(first, second);
}

int** allocate_array_coordinate(int** coordinates, int index, int* coordinate)
{
  *(coordinates + index) = coordinate; return coordinates;
}

int coordinate_index_value(int* coordinate, int index)
{
  int value = *(coordinate + index); return value;
}

int* allocate_coordinate_value(int* coordinate, int index, int value)
{
  *(coordinate + index) = value; return coordinate;
}

int** battleships_index_ship(int*** battleships, int index)
{
  int** battleship = *(battleships + index); return battleship;
}

int* array_index_coordinate(int** battleship, int index)
{
  int* coordinate = *(battleship + index); return coordinate;
}

int generate_inputted_battleship(int*** battleships, int index, int size, char* input_string)
{
  int string_len = character_string_length(input_string);
  int** coordinates = generate_coordinate_objects(2);

  int cord_output = convert_string_coordinates(input_string, string_len, coordinates);
  if(cord_output == false) return false;

  coordinates = switch_battleship_coordinates(coordinates);

  if(!inputted_coordinates_valid(coordinates, battleships, size))
  {
    return false;
  }

  battleships = allocate_battleships_ship(battleships, index, coordinates);
  return true;
}

int** switch_battleship_coordinates(int** coordinates)
{
  int height_bool = (coordinates[0][0] > coordinates[1][0]);
  int width_bool = (coordinates[0][1] > coordinates[1][1]);
  if(!height_bool && !width_bool) return coordinates;

  int* temp_cord = duplicate_coordinate_object(coordinates[0]);
  coordinates[0] = duplicate_coordinate_object(coordinates[1]);
  coordinates[1] = duplicate_coordinate_object(temp_cord);

  return coordinates;
}

int inputted_coordinates_valid(int** coordinates, int*** battleships, int size)
{
  int cords_inside = board_coordinates_inside(coordinates, 10, 10);
  if(cords_inside == false) return false;

  int size_valid = battleship_valid_size(coordinates, size);
  if(size_valid == false) return false;
  
  int ship_valid = battleship_position_valid(battleships, coordinates);
  if(ship_valid == false) return false;

  return true;
}

int board_coordinates_inside(int** coordinates, int height, int width)
{
  int first_inside = board_coordinate_inside(coordinates[0], height, width);
  int second_inside = board_coordinate_inside(coordinates[1], height, width);
  return (first_inside && second_inside);
}

int board_coordinate_inside(int* coordinate, int height, int width)
{
  int height_valid = ((coordinate[0] < 10) && (coordinate[0] >= 0));
  int width_valid = ((coordinate[1] < 10) && (coordinate[1] >= 0));
  return (height_valid && width_valid);
}

int battleship_valid_size(int** battleship, int size)
{
  int height_size = (battleship[1][0] - battleship[0][0]);
  int width_size = (battleship[1][1] - battleship[0][1]);
  return ( ((height_size + 1) * (width_size + 1)) == size);
}

int battleship_position_valid(int*** battleships, int** battleship)
{
  for(int index = 0; index < 5; index = index + 1) // CHANGE 5 TO AMOUNT
  {
    int** current_ship = battleships_index_ship(battleships, index);

    if(battleship_over_battleship(current_ship, battleship))
    {
      return false;
    }
  }
  return true;
}

int coordinates_array_amount(int** battleship)
{
  int amount = 0;
  while(coordinate_variable_exsist(battleship[amount]))
  {
    amount = (amount + 1);
  }
  return amount;
}

int coordinate_variable_exsist(int* coordinate)
{
  int first = coordinate_index_value(coordinate, 0);
  int second = coordinate_index_value(coordinate, 1);
  return (first != -1 && second != -1);
}

int battleship_over_battleship(int** first, int** second)
{
  int** first_cords = every_battleship_coordinate(first);
  int** second_cords = every_battleship_coordinate(second);

  int f_amount = coordinates_array_amount(first_cords);
  int s_amount = coordinates_array_amount(second_cords);

  for(int index = 0; index < f_amount; index = index + 1)
  {
    int* coordinate = array_index_coordinate(first_cords, index);

    if(coordinate_inside_array(coordinate, second_cords, s_amount))
    {
      return true;
    }
  }
  return false;
}

int integer_variables_equal(int first, int second)
{
  int boolean = (first == second); return boolean;
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
    int first_cord = coordinate_index_value(first, index);
    int second_cord = coordinate_index_value(second, index);

    if(!integer_variables_equal(first_cord, second_cord))
    {
      return false;
    }
  }
  return true;
}

int generate_random_battleship(int*** battleships, int index, int size)
{

}

int** every_battleship_coordinate(int** battleship)
{
  int* first_cord = array_index_coordinate(battleship, 0);
  int* second_cord = array_index_coordinate(battleship, 1);
  int** coordinates = generate_coordinate_objects(6);
  int index = 0;

  for(int h_index = first_cord[0]; h_index <= second_cord[0]; h_index += 1)
  {
    for(int w_index = first_cord[1]; w_index <= second_cord[1]; w_index += 1)
    {
      int* coordinate = generate_coordinate_object(h_index, w_index);
      coordinates = allocate_array_coordinate(coordinates, index, coordinate);
      index = (index + 1);
    }
  }
  return coordinates;
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

char alphabet[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', '\0'};

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

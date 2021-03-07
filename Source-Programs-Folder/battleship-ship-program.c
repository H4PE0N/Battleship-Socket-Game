
#include "battleship-main-program.h"
#include "battleship-string-program.h"
#include "battleship-output-program.h"
#include "battleship-socket-program.h"
#include "battleship-ship-program.h"

int*** generate_battleship_array(int amount)
{
  int*** battleships = malloc(sizeof(int**) * (amount + 1));
  for(int index = 0; index < (amount + 1); index = index + 1)
  {
    int** battleship = generate_coordinate_objects(2);
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

int** generate_battleship_object(int* first, int* second)
{
  int** battleship = generate_coordinate_objects(2);
  battleship = allocate_array_coordinate(battleship, 0, first);
  battleship = allocate_array_coordinate(battleship, 1, second);
  return battleship;
}

int** generate_coordinate_objects(int amount)
{
  int** coordinates = malloc(sizeof(int*) * (amount + 1));
  for(int index = 0; index < (amount + 1); index = index + 1)
  {
    int* coordinate = generate_coordinate_object(-1, -1);
    coordinates = allocate_array_coordinate(coordinates, index, coordinate);
  }
  return coordinates;
}

int* generate_coordinate_object(int first, int second)
{
  int* coordinate = malloc(sizeof(int) * 3);
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

int generate_random_integer(int minimum, int maximum)
{
  int integer = (minimum + (rand() % (maximum - minimum + 1)) );
  return integer;
}

int** generate_random_battleship(int*** battleships, int ship_size)
{
  int** battleship = random_horizontal_battleship(ship_size);
  if(generate_random_integer(0, 1) == 1) // slingra slant
  {
    battleship = random_vertical_battleship(ship_size);
  }
  if(battleship_position_valid(battleships, battleship))
  {
    return battleship;
  }
  return generate_random_battleship(battleships, ship_size);
}

int** random_vertical_battleship(int ship_size)
{
  int height_range = (10 - ship_size - 1);

  int height = generate_random_integer(0, height_range);
  int width = generate_random_integer(0, 10 - 1);

  int* first = generate_coordinate_object(height, width);
  int* second = generate_coordinate_object(height + ship_size - 1, width);

  return generate_battleship_object(first, second);
}

int** random_horizontal_battleship(int ship_size)
{
  int width_range = (10 - ship_size - 1);

  int height = generate_random_integer(0, 10 - 1);
  int width = generate_random_integer(0, width_range);

  int* first = generate_coordinate_object(height, width);
  int* second = generate_coordinate_object(height, width + ship_size - 1);

  return generate_battleship_object(first, second);
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

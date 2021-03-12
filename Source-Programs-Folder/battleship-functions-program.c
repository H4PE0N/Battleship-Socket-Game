
#include "common-header-program.h"

int generate_battleship_array(int*** battleships,
  int amount, char*** def_board)
{
  battleships = malloc(sizeof(int**) * amount);
  int height = BOARD_HEIGHT, width = BOARD_WIDTH;
  for(int index = 0; index < amount; index = index + 1)
  {
    display_battleship_board(def_board, height, width);
    int gnrt_output=generate_index_battleship(battleships,
      index); if(gnrt_output == false) return false;
    def_board = mark_battleship_position(def_board,
      battleship);
  }
  return true;
}

int generate_index_battleship(int*** battleships, int index)
{
  *(battleships + index) = malloc(sizeof(int*) * 2);
  int** battleship = battleships_index_ship(battleships, index);

  int inpt_output = input_battleship_position(battleships, index, battleship);
  if(inpt_output == false) return false;

  battleships = allocate_battleships_ship(battleships, index, battleship);
  return true;
}

int input_battleship_position(int*** battleships, int index, int** position)
{
  int ship_sizes[] = {2, 3, 3, 4, 5};
  int size = array_index_integer(ship_sizes, index);

  char input_message[] = ("BATTLESHIP #%d [SIZE: %d]: ", index + 1, size);
  char* string = input_character_string(input_message);

  if(character_strings_equal(string, "EXIT", 4))
    return false;

  int conv_output = convert_string_position(position);
  if(conv_output == true) return true;
  return input_battleship_position(battleships, index, position);
}
//
// int array_index_integer(int array[], int index)
// {
//   int integer = *(array + index); return integer;
// }
//
// int** every_battleship_coordinate(int battleship[2][2])
// {
//   int** every_cord = malloc(sizeof(int*) * 10); // 10 is the max coordinates?...
//   int f_cord[2] = array_index_coordinate(battleship, 0);
//   int s_cord[2] = array_index_coordinate(battleship, 1);
//   for(int height=f_cord[0];height<=s_cord[0]; height++)
//   {
//     every_cord = append_every_coordinate(every_cord, f_cord, s_cord, height);
//   }
//   return every_cord;
// }
//
// int** append_every_coordinate(int** every_cord, int* f_cord, int* s_cord, int height);
// {
//   for(int width = f_cord[1]; width<=s_cord[1]; width++)
//   {
//     int coordinate[] = generate_coordinate_object(height, width);
//     int amount = array_coordinates_amount(every_cord);
//     *(every_cord + amount) = coordinate;
//   }
//   return every_cord;
// }
//
// // SHPPNT battleships_index_ship(BTLESHPS battleships, int index)
// // {
// //   BTLESHP battleship = battleships[index]; return battleship;
// // }
// //
// // SHPSPNT allocate_battleships_ship(SHPSPNT battleships, int index, BTLESHP battleship)
// // {
// //   battleships[index] = battleship; return battleships;
// // }
// //
// // SHPPNT allocate_ship_coordinate(SHPPNT battleship, int index, int coordinate[])
// // {
// //   battleship[index] = coordinate; return battleship;
// // }
//
// int* generate_coordinate_object(int first, int second)
// {
//   int coordinate[] = {first, second}; return coordinate;
// }

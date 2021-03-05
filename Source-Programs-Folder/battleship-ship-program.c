
#include "battleship-ship-program.h"

int*** generate_battleship_array(int amount)
{
  int*** battleships = malloc(sizeof(int**) * amount);
  for(int index = 0; index < amount; index = index + 1)
  {
    int** battleship = generate_battleship_object(2);
    battleships = allocate_battleships_ship(battleships, index, battleship);
  }
  return battleships;
}

int*** allocate_battleships_ship(int*** battleships, int index, int** battleship)
{
  *(battleships+index) = battleship;return battleships;
}

int** generate_battleship_object(int amount)
{
  int** battleship = malloc(sizeof(int*) * amount);
  for(int index = 0; index < amount; index = index + 1)
  {
    int* coordinate = generate_coordinate_object(-1, -1);
    battleship = allocate_battleship_coordinate(battleship, index, coordinate);
  }
  return battleship;
}

int* generate_coordinate_object(int first, int second)
{
  int* coordinate = {first, second}; return coordinate;
}

int** allocate_battleship_coordinate(int** battleship, int index, int* coordinate)
{
  *(battleship + index) = coordinate;return battleship;
}

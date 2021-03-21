
#include "common-header-program.h"

int main(int arg_amount, char* arguments[])
{
  srand(time(NULL)); if(arg_amount < 2) return false;

  // char* sock_role = generate_character_string(STR_SIZE);
  // int extr_output = extract_socket_role(arguments,
  //   sock_role); if(extr_output == false) return false;

  // int sock_object = SOCK_NONE;
  // int setup_output = setup_socket_information(sock_role,
  //   &sock_object); if(!setup_output) return false;

  int height = BOARD_HEIGHT, width = BOARD_WIDTH;
  char*** def_board = generate_battleship_board(height, width);
  char*** off_board = generate_battleship_board(height, width);

  int*** battleships = generate_integer_block(SHIP_AMOUNT, 2, 2);
  int shps_output = generate_battleship_array(battleships, SHIP_AMOUNT, def_board);
  if(shps_output == false) return false;

  // char* game_result = generate_character_string(STR_SIZE);
  // if(character_strings_equal(sock_role, "SERVER", 6))
  // {
  //   game_result = server_battleship_game(sock_object, def_board, off_board, battleships);
  // }
  // if(character_strings_equal(sock_role, "CLIENT", 6))
  // {
  //   game_result = client_battleship_game(sock_object, def_board, off_board, battleships);
  // }
  //
  // display_game_result(def_board, off_board, game_result);

  return false;
}

char* server_battleship_game()
{
  /*
  generate game_result variable

  while(game_result is not win or defeated)
    display boards

    attack opponent

    display board

    register opponents damage

  return game result
  */
}

char* client_battleship_game()
{
  /*
  generate game_result variable

  while(game_result is not win or defeated)
    display board

    register opponents damage

    display boards

    attack opponent

  return game result
  */
}

int attack_opponents_coordinate()
{
  /*
  input coordinate

  send coordinate to other socket

  check if coordinate was sent, othervise you have won (they are not playing)

  receive opponents protocol

  check if protocol is DEFEATED, then you have won.
  You have also won if the connection is not working (they are not playing)

  register opponents protocol
  */
}

int register_opponents_damage()
{
  /*
  receive opponents coordinate
  check if connection is lost, if so, you have won  (they are not playing)

  mark opponents coordinate on def_board

  send action and coordinate of damage from opponent back to opponent as a protocol

  if the action was DEFEATED, then you have lost and function returns negative
  */
}

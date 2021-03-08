
#include "common-header-program.h"

int main(int arg_amount, char* arguments[])
{
  srand(time(NULL));

  char* sock_role = generate_character_string(STR_SIZE);
  if(extract_socket_role(arguments, arg_amount, sock_role))
  {
    printf("SOCKET ROLE: %s\n", sock_role);
  }

  int sock_object = setup_socket_information(sock_role);
  if(sock_object != -1) printf("SOCKET: %d\n");

  /*

  setup socket

  generate def_board, off_board and battleships

  start game (either server game or client game)

  display game results

  */
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


#include "battleship-main-program.h"
#include "battleship-string-program.h"
#include "battleship-output-program.h"
#include "battleship-socket-program.h"
#include "battleship-ship-program.h"

#define BOARD_HEIGHT 10
#define BOARD_WIDTH 10

int main(int arg_amount, char* arguments[])
{
  char* socket_role = extract_socket_role(arguments, arg_amount);

  if(character_string_length(socket_role) == 0)
  {
    exit_and_print_message("SOCKET ROLE NOT INPUTTED");
  }

  int socket_obj = setup_socket_information(socket_role);

  char*** def_board = generate_battleship_board(BOARD_HEIGHT, BOARD_WIDTH);
  char*** off_board = generate_battleship_board(BOARD_HEIGHT, BOARD_WIDTH);
  int*** battleships = generate_board_battleships(def_board, 5);
  // char*** def_board = generate_battleship_board(BOARD_HEIGHT, BOARD_WIDTH);
  // char*** off_board = generate_battleship_board(BOARD_HEIGHT, BOARD_WIDTH);
  char* game_result = generate_character_string(200);

  if(character_strings_equal(socket_role, "SERVER", 6))
  {
    int game_output = server_battleship_game(socket_obj, def_board, off_board, game_result);
  }
  if(character_strings_equal(socket_role, "CLIENT", 6))
  {
    int game_output = client_battleship_game(socket_obj, def_board, off_board, game_result);
  }

  display_game_result(def_board, off_board, game_result);

  return false;
}

///////////////////////////////////////////////////////////////////////////////////
int setup_socket_information(char* socket_role)
{
  char* address = generate_character_string(200);
  int port;
  int socket_obj;
  int output = input_socket_information(address, &port);

  printf("ADDRESS: (%s) PORT: (%d)\n", address, port);

  if(character_strings_equal(socket_role, "SERVER", 6))
  {
    int socket_obj = setup_server_socket(address, port);
  }
  if(character_strings_equal(socket_role, "CLIENT", 6))
  {
    int socket_obj = setup_client_socket(address, port);
  }
  if(socket_obj) return socket_obj;
  exit_and_print_message("WHILE SETUP SOCKET INFO");
}

int input_socket_information(char* address, int* port)
{
  // printf("ADDRESS\t:"); scanf("%s", address);
  // printf("PORT\t: "); int port_valid=scanf("%d", port);
  //
  // int length = character_string_length(address);
  // int addr_valid = socket_address_valid(address, length);
  //
  // if(addr_valid && port_valid) return true;
  // exit_and_print_message("ADDRESS OR PORT NOT INPUTTED");

  strcpy(address, "192.168.1.113");
  *port = 5555;
  return true;
}

int setup_server_socket(char* address, int port)
{
  int server_socket = generate_server_socket(AF_INET, SOCK_STREAM, 0);
  display_server_message("GENERATED SERVER SOCKET");

  int bind_output = bind_server_socket(server_socket, address, port);
  display_server_message("SERVER SOCKET IS BUNDEN");

  display_server_message("LISTENING FOR CONNECTION");
  int list_output = listen_for_connection(server_socket, 0);

  int client_socket = accept_connecting_client(server_socket, address, port);
  display_server_message("ACCEPTED CONNECTING CLIENT");

  return client_socket;
}

int setup_client_socket(char* address, int port)
{
  int server_socket = generate_server_socket(AF_INET, SOCK_STREAM, 0);
  display_server_message("GENERATED SERVER SOCKET");

  int conn_output = connect_server_socket(server_socket, address, port);
  display_server_message("CONNECTED TO SERVER SOCKET");

  return server_socket;
}
///////////////////////////////////////////////////////////////////////////////////

int*** generate_board_battleships(char*** def_board, int amount)
{
  int*** battleships = generate_battleship_array(amount);
  battleships = input_battleship_positions(battleships, def_board);
  return battleships;
}

int*** input_battleship_positions(int*** battleships, char*** def_board)
{
  for(int index = 0; index < 5; index = index + 1)
  {
    display_battleship_board(def_board, 10, 10);
    battleships = input_battleship_position(battleships, index);

    int** battleship = battleships_index_ship(battleships, index);
    int** all_cords = every_battleship_coordinate(battleship);
    def_board = board_coordinates_keyword(def_board, all_cords, "BATTLESHIP\0");
  }
  return battleships;
}

int ship_sizes[] = {2, 3, 3, 4, 5};

int*** input_battleship_position(int*** battleships, int index)
{
  int size = ship_sizes[index];
  char* input_string = generate_character_string(200);

  printf("INPUT BATTLESHIP #%d [SIZE: %d]: ", index + 1, size);
  scanf("%[^\n]s", input_string); getchar();

  int length = character_string_length(input_string);
  input_string = convert_string_upper(input_string, length);

  if(character_strings_equal(input_string, "EXIT", 4))
  {
    exit_and_print_message("QUITING GAME / SHIP INPUT");
  }

  if(character_strings_equal(input_string, "RANDOM", 6))
  {
    int** battleship = generate_random_battleship(battleships, size);
    battleships = allocate_battleships_ship(battleships, index, battleship);
  }
  else if(!generate_inputted_battleship(battleships, index, size, input_string))
  {
      return input_battleship_position(battleships, index);
  }
  return battleships;
}

/////////////////////////////////////////////////////////////////////////////////

int server_battleship_game(int socket_obj, char*** def_board, char*** off_board, char* game_result)
{
  display_battleship_boards(def_board, off_board, 10, 10);
  return true;
}

int client_battleship_game(int socket_obj, char*** def_board, char*** off_board, char* game_result)
{
  display_battleship_boards(def_board, off_board, 10, 10);
  return true;
}

void display_game_result(char*** def_board, char*** off_board, char* game_result)
{

}

char* socket_roles[] = {"SERVER", "CLIENT", "\0"};

char* extract_socket_role(char* arguments[], int arg_amount)
{
  char* socket_role = generate_character_string(200);
  if((arg_amount - 1) < 1) return socket_role;

  char* input_role = sentence_index_string(arguments, 1);
  int input_len = character_string_length(input_role);
  input_role = convert_string_upper(input_role, input_len);

  int role_amount = sentence_string_amount(socket_roles);

  if(string_inside_sentence(input_role, input_len, socket_roles, role_amount))
  {
    socket_role = input_role;
  }

  return socket_role;
}

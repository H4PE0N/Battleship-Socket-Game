
#include "battleship-main-program.h"
#include "battleship-string-program.h"
#include "battleship-output-program.h"
#include "battleship-socket-program.h"
#include "battleship-ship-program.h"
#include <errno.h>
#include <time.h>

#define BOARD_HEIGHT 10
#define BOARD_WIDTH 10

int main(int arg_amount, char* arguments[])
{
  srand(time(NULL));

  char* socket_role = extract_socket_role(arguments, arg_amount);

  if(character_string_length(socket_role) == 0)
  {
    exit_and_print_message("SOCKET ROLE NOT INPUTTED");
  }

  int socket_obj = setup_socket_information(socket_role);

  char*** def_board = generate_battleship_board(BOARD_HEIGHT, BOARD_WIDTH);
  char*** off_board = generate_battleship_board(BOARD_HEIGHT, BOARD_WIDTH);
  int*** battleships = generate_board_battleships(def_board, 5);
  char* game_result = generate_character_string(200);

  if(character_strings_equal(socket_role, "SERVER", 6))
  {
    game_result = server_battleship_game(socket_obj, def_board, off_board, battleships);
  }
  if(character_strings_equal(socket_role, "CLIENT", 6))
  {
    game_result = client_battleship_game(socket_obj, def_board, off_board, battleships);
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

  if(character_strings_equal(socket_role, "SERVER", 6))
  {
    socket_obj = setup_server_socket(address, port);
  }
  if(character_strings_equal(socket_role, "CLIENT", 6))
  {
    socket_obj = setup_client_socket(address, port);
  }
  if(socket_obj >= 0) return socket_obj;
  exit_and_print_message("WHILE SETUP SOCKET INFO");
}

int input_socket_information(char* address, int* port)
{
  printf("ADDRESS\t:"); scanf("%s", address);
  printf("PORT\t: "); int port_valid=scanf("%d", port);

  int length = character_string_length(address);
  int addr_valid = socket_address_valid(address, length);

  if(addr_valid && port_valid) return true;
  exit_and_print_message("ADDRESS OR PORT NOT INPUTTED");
  return true;
}

int setup_server_socket(char* address, int port)
{
  int server_socket = generate_server_socket(AF_INET, SOCK_STREAM, 0);
  display_server_message("GENERATED SERVER SOCKET");

  int bind_output = bind_server_socket(server_socket, address, port);
  display_server_message("SERVER SOCKET IS BUNDEN");

  display_server_message("LISTENING FOR CONNECTION");
  int list_output = listen_for_connection(server_socket, 5);

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
    def_board = set_coordinates_keyword(def_board, all_cords, "BATTLESHIP\0");
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

char* server_battleship_game(int socket_obj, char*** def_board, char*** off_board, int*** battleships)
{
  char* game_result = generate_character_string(200);
  while(!character_strings_equal(game_result, "WON\0", 3) && !character_strings_equal(game_result, "DEFEATED\0", 8))
  {
    display_battleship_boards(def_board, off_board, 10, 10);
    if(!attack_opponent_coordinate(socket_obj, off_board, game_result))
    {
      break;
    }
    display_battleship_boards(def_board, off_board, 10, 10);
    register_opponents_damage(socket_obj, def_board, battleships, game_result);
  }
  return game_result;
}

char* client_battleship_game(int socket_obj, char*** def_board, char*** off_board, int*** battleships)
{
  char* game_result = generate_character_string(200);
  while(!character_strings_equal(game_result, "WON\0", 3) && !character_strings_equal(game_result, "DEFEATED\0", 8))
  {
    display_battleship_boards(def_board, off_board, 10, 10);
    if(!register_opponents_damage(socket_obj, def_board, battleships, game_result))
    {
      break;
    }
    display_battleship_boards(def_board, off_board, 10, 10);
    attack_opponent_coordinate(socket_obj, off_board, game_result);
  }
  return game_result;
}

int attack_opponent_coordinate(int socket_obj, char*** off_board, char* game_result)
{
  //printf("attack_opponent_coordinate\n");
  int* coordinate = input_attacking_coordinate();
  int send_output = send_attacking_coordinate(socket_obj, coordinate);
  if(send_output == false)
  {
    strcpy(game_result, "WON");
    return false;
  }
  char* action = generate_character_string(200);
  int** coordinates = generate_coordinate_objects(5);
  int recv_output = receive_opponents_protocol(socket_obj, action, coordinates);

  if(character_strings_equal(action, "DEFEATED", 8))
  {
    strcpy(game_result, "WON");
    return false;
  }

  if(recv_output == false)
  {
    strcpy(game_result, "WON");
    return false;
  }
  off_board = register_protocol_coordinates(action, coordinates, off_board);

  return true;
}

int register_opponents_damage(int socket_obj, char*** def_board, int*** battleships, char* game_result)
{
  //printf("register_opponents_damage\n");
  int* coordinate = generate_coordinate_object(-1, -1);
  int recv_output = receive_opponents_coordinate(socket_obj, coordinate);
  if(recv_output == false)
  {
    strcpy(game_result, "WON");
    return false;
  }

  char* action = generate_character_string(200);
  int** coordinates = generate_coordinate_objects(5);

  def_board = register_opponents_coordinate(coordinate, def_board, battleships, action, coordinates);

  int send_output = send_registerd_damage(socket_obj, action, coordinates);
  if(send_output == false)
  {
  strcpy(game_result, "WON");
    return false;
  }
  if(character_strings_equal(action, "DEFEATED\0", 8))
  {
    strcpy(game_result, "DEFEATED");
    return false;
  }

  return true;
}

/////////////////////////////////////////////////////////////////////////////////
int receive_opponents_coordinate(int socket_obj, int* coordinate)
{
  //printf("receive_opponents_coordinate\n");
  int size = 200;
  char response[size];
  int recv_output = -1;

  while(recv_output == -1)
  {
    recv_output = recv(socket_obj, &response, size, 0);
  }

  if(recv_output == 0) // connection is closed
  {
    return false;
  }

  int length = character_string_length(response);

  int cord_output = convert_string_coordinate(response, length, coordinate);
  if(cord_output == false) return false;

  return true;
}

int send_registerd_damage(int socket_obj, char* action, int** coordinates)
{
  //printf("send_registerd_damage\n");
  char* protocol = generate_character_string(200);
  int gen_output = generate_damage_protocol(action, coordinates, protocol);
  if(gen_output == false)
  {
    exit_and_print_message("WHEN GENERATING PROTOCOL");
  }

  int send_output = send(socket_obj, protocol, 200, 0);
  if(send_output == -1) return false;
  return true;
}

int generate_damage_protocol(char* action, int** coordinates, char* protocol)
{
  //printf("generate_damage_protocol\n");
  strcat(protocol, action); strcat(protocol, "=");
  int amount = coordinates_array_amount(coordinates);
  for(int index = 0; index < (amount - 1); index = index + 1)
  {
    int* coordinate = array_index_coordinate(coordinates, index);
    int all_output = allocate_coordinate_protocol(coordinate, protocol);
    if(all_output == false) return false;
    strcat(protocol, "-");
  }
  int* coordinate = array_index_coordinate(coordinates, amount - 1);
  int all_output = allocate_coordinate_protocol(coordinate, protocol);
  if(all_output == false) return false;
  return true;
}

int allocate_coordinate_protocol(int* coordinate, char* protocol)
{
  // printf("allocate_coordinate_protocol\n");
  char* string = generate_character_string(200);
  int conv_output = convert_coordinate_string(coordinate, string);

  if(conv_output == false) return false;
  strcat(protocol, string); return true;
}

char*** register_opponents_coordinate(int* coordinate, char*** def_board, int*** battleships, char* action, int** coordinates)
{
  // printf("register_opponents_coordinate\n");
  strcpy(action, "MISS");
  coordinates[0] = coordinate;
  coordinates[1] = generate_coordinate_object(-1, -1);

  for(int index = 0; index < 5; index = index + 1)
  {
    int** battleship = battleships_index_ship(battleships, index);
    if(!coordinate_hit_battleship(coordinate, battleship))
    {
      continue;
    }
    strcpy(action, "HIT");

    if(defence_ship_defeated(battleship, def_board, coordinate))
    {
      strcpy(action, "SUNKEN");
      int** all_cords = every_battleship_coordinate(battleship);
      int amount = coordinates_array_amount(all_cords);
      for(int all_ind = 0; all_ind < amount; all_ind++)
      {
        coordinates[all_ind][0] = all_cords[all_ind][0];
        coordinates[all_ind][1] = all_cords[all_ind][1];
      }
    }
    break;
  }
  if(defence_board_defeated(def_board, battleships, coordinate))
  {
    strcpy(action, "DEFEATED");
  }
  def_board = set_coordinates_keyword(def_board, coordinates, action);
  return def_board;
}

int defence_ship_defeated(int** battleship, char*** def_board, int* coordinate)
{
  int** all_cords = every_battleship_coordinate(battleship);
  int amount = coordinates_array_amount(all_cords);
  for(int index = 0; index < amount; index = index + 1)
  {
    int* current = array_index_coordinate(battleship, index);
    if(coordinate_objects_equal(current, coordinate))
    {
      continue;
    }
    char* keyword = board_coordinate_keyword(def_board, current);
    if(strcmp(keyword, "HIT")) return false;
  }
  return true;
}

int defence_board_defeated(char*** def_board, int*** battleships, int* coordinate)
{
  for(int index = 0; index < 5; index = index + 1)
  {
    int** battleship = battleships_index_ship(battleships, index);
    if(!defence_ship_defeated(battleship, def_board, coordinate))
    {
      return false;
    }
  }
  return true;
}

int coordinate_hit_battleship(int* coordinate, int** battleship)
{
  int** all_cords = every_battleship_coordinate(battleship);
  int amount = coordinates_array_amount(all_cords);
  for(int index = 0; index < amount; index = index + 1)
  {
    int* current = array_index_coordinate(all_cords, index);
    if(coordinate_objects_equal(coordinate, current))
    {
      return true;
    }
  }
  return false;
}

/////////////////////////////////////////////////////////////////////////////////
int receive_opponents_protocol(int socket_obj, char* action, int** coordinates)
{
  // printf("receive_opponents_protocol\n");
  char string[200];
  int recv_output = -1;

  while(recv_output == -1)
  {
    recv_output = recv(socket_obj, &string, 200, 0);
  }
  if(recv_output == 0) return false;

  strcpy(action, strtok(string, "="));
  printf("ACTION: (%s)\n", action);

  char* token = strtok(NULL, "-");
  int* coordinate = generate_coordinate_object(-1, -1);

  for(int index = 0; token != NULL; index = index + 1)
  {
    int length = character_string_length(token);
    printf("TOKEN: (%s)\n", token);
    int conv_output = convert_string_coordinate(token, length, coordinate);

    if(conv_output == false) return false;
    coordinates[index][0] = coordinate[0];
    coordinates[index][1] = coordinate[1];

    token = strtok(NULL, "-");
  }

  return true;
}

int send_attacking_coordinate(int socket_obj, int* coordinate)
{
  // printf("send_attacking_coordinate\n");
  int size = 200;
  char* string = generate_character_string(size);

  int conv_output = convert_coordinate_string(coordinate, string);
  if(conv_output == false) return false;

  int send_output = send(socket_obj, string, size, 0);
  if(send_output == -1) return false;

  return true;
}

char*** register_protocol_coordinates(char* action, int** coordinates, char*** off_board)
{
  off_board = set_coordinates_keyword(off_board, coordinates, action);
  return off_board;
}
//////////////////////////////////////////////////////////////////////////////////

int* input_attacking_coordinate()
{
  char* input_string = generate_character_string(200);
  printf("INPUT COORDINATE: ");
  scanf("%[^\n]s", input_string); getchar();

  int length = character_string_length(input_string);
  input_string = convert_string_upper(input_string, length);

  if(character_strings_equal(input_string, "EXIT", 4))
  {
    exit_and_print_message("QUITING GAME / CORD INPUT");
  }

  int* coordinate = generate_coordinate_object(-1, -1);

  if(character_strings_equal(input_string, "RANDOM", 6))
  {

  }
  else if(!convert_string_coordinate(input_string, length, coordinate))
  {
    return input_attacking_coordinate();
  }

  return coordinate;

}

void display_game_result(char*** def_board, char*** off_board, char* game_result)
{
  printf("RESULT: %s\n", game_result);
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

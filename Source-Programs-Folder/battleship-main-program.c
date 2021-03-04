
#include "battleship-main-program.h"
#include "battleship-string-program.h"

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

int main(int arg_amount, char* arguments[])
{
  char* socket_role = extract_socket_role(arguments, arg_amount);

  if(character_string_length(socket_role) == 0)
  {
    printf("SOCKET ROLE NOT INPUTTED\n"); exit(false);
  }

  return false;
}

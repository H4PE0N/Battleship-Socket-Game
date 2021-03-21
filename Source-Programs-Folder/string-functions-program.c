
#include "common-header-program.h"

char* convert_string_upper(char* string, int length)
{
  for(int index = 0; index < length; index = index + 1)
  {
    char character = string_index_character(string,
      index);
    character = convert_character_upper(character);
    string = allocate_string_character(string, index,
      character);
  }
  return string;
}

char convert_character_upper(char character)
{
  if(character_range_between(character, 97, 122))
    return (character - 32); return character;
}

int character_range_between(char character, int minimum,
  int maximum)
{
  int smaller = character_smaller_than(character,
    minimum);
  int greater = character_greater_than(character,
    maximum); return (!smaller && !greater);
}

int character_smaller_than(char character, int integer)
{
  int boolean = (character < integer); return boolean;
}

int character_greater_than(char character, int integer)
{
  int boolean = (character > integer); return boolean;
}

int character_string_length(char string[])
{
  int length = 0;
  for(length; string[length] != CHAR_NONE; length += 1);
  return length;
}

char* copy_character_string(char copying[], char* string,
  int length)
{
  for(int index = 0; index < length; index = index + 1)
  {
    char character = string_index_character(copying,
      index);
    string = allocate_string_character(string, index,
      character);
  }
  return string;
}

// int string_character_valid(char string[] int index)
// {
//   char character = string_index_character(string, index);
//   return (character != CHAR_NONE);
// }
int character_strings_equal(char first[], char second[],
  int length)
{
  for(int index = 0; index < length; index = index + 1)
  {
    char first_char=string_index_character(first,index);
    char second_char = string_index_character(second,
      index);
    if(!character_values_equal(first_char, second_char))
      return false;
  }
  return true;
}

int character_values_equal(char first, char second)
{
  int boolean = (first == second); return boolean;
}

int string_inside_sentence(char string[], int length,
  char* sentence[], int amount)
{
  for(int index = 0; index < amount; index = index + 1)
  {
    char* current = sentence_index_string(sentence,
      index);
    int current_len = character_string_length(current);
    if(character_strings_equal(string, current,
      (current_len > length) ? current_len : length))
      return true;
  }
  return false;
}

int input_character_string(char input_message[],
  char* string)
{
  fflush(stdin);
  printf("%s", input_message);
  char buffer[STR_SIZE];
  fgets(buffer, STR_SIZE, stdin);
  int inpt_output = sscanf(buffer, "%[^\n]", string);
  return (inpt_output == 1);
}

int input_integer_variable(char input_message[],
  int* integer)
{
  fflush(stdin);
  printf("%s", input_message);
  char buffer[STR_SIZE];
  fgets(buffer, STR_SIZE, stdin);
  int inpt_output = sscanf(buffer, "%d", integer);
  return (inpt_output == 1);
}

int string_character_index(char string[], int length,
  char character)
{
  for(int index = length; index >= 0; index = index - 1)
  {
    char current = string_index_character(string, index);
    if(character_values_equal(current, character))
      return index;
  }
  return INT_NONE;
}

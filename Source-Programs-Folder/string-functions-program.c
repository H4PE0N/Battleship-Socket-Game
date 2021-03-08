
#include "common-header-program.h"

char* copy_character_string(char copying[], char* string, int length)
{
  for(int index = 0; index < length; index = index + 1)
  {
    char character = string_index_character(copying, index);
    string = allocate_string_character(string, index, character);
  }
  return string;
}

int character_string_length(char string[])
{
  for(int length = 0; string[length] != '\0'; length++
  return length;
}

char string_index_character(char string[], int index)
{
  char character = *(string + index); return character;
}

char* allocate_string_character(char* string, int index, char character)
{
  *(string + index) = character; return string;
}

char* sentence_index_string(char** sentence, int index)
{
  char* string = *(sentence + index); return string;
}

char* generate_character_string(int length)
{
  char* string = malloc(sizeof(char) * length);
  for(int index = 0; index < length; index = index + 1)
    string = allocate_string_character(string, index, '\0');
  return string;
}

int character_strings_equal(char first[] char second[], int length)
{
  for(int index = 0; index < length; index = index + 1)
  {
    char first_char = string_index_character(first, index);
    char second_char = string_index_character(second, index);
    if(!character_values_equal(first_char, second_char))
      return false;
  }
  return true;
}

int character_values_equal(char first, char second)
{
  int boolean = (first == second); return boolean;
}

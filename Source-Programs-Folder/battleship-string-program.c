
#include "battleship-string-program.h"

char string_index_character(char* string, int index)
{
  char character = *(string + index); return character;
}

char* sentence_index_string(char** sentence, int index)
{
  char* string = *(sentence + index); return string;
}

char* allocate_string_character(char* string, int index, char character)
{
  *(string + index) = character; return string;
}

int character_between_integers(char character, int first, int second)
{
  int boolean = (character >= first && character <= second);
  return boolean;
}

char convert_character_upper(char character)
{
  if(character_between_integers(character, 97, 122))
  {
    return (character - 32);
  }
  return character;
}

char* convert_string_upper(char* string, int length)
{
  for(int index = 0; index < length; index = index + 1)
  {
    char character = string_index_character(string, index);
    character = convert_character_upper(character);
    string = allocate_string_character(string, index, character);
  }
  return string;
}

int character_string_length(char* string)
{
  int length = 0;
  while(string_index_character(string, length) != '\0')
  {
    length = (length + 1);
  }
  return length;
}

int sentence_string_length(char** sentence, int index)
{
  char* string = sentence_index_string(sentence, index);
  int length = character_string_length(string);
  return length;
}

int sentence_string_amount(char** sentence)
{
  int amount = 0;
  while(sentence_string_length(sentence, amount) != 0)
  {
    amount = (amount + 1);
  }
  return amount;
}

char* generate_character_string(int length)
{
  char* string = malloc(sizeof(*string) * length);
  for(int index = 0; index < length; index = index + 1)
  {
    *(string + index) = '\0';
  }
  return string;
}

int character_variables_equal(char first, char second)
{
  int boolean = (first == second); return boolean;
}

int character_strings_equal(char* first, char* second, int length)
{
  for(int index = 0; index < length; index = index + 1)
  {
    char first_char = string_index_character(first, index);
    char second_char = string_index_character(second, index);
    if(!character_variables_equal(first_char, second_char))
    {
      return false;
    }
  }
  return true;
}

int string_inside_sentence(char* string, int length, char** sentence, int height)
{
  for(int index = 0; index < height; index = index + 1)
  {
    char* current = sentence_index_string(sentence, index);
    int current_len = character_string_length(current);

    int comp_length = length;
    if(current_len > length) comp_length = current_len;

    if(character_strings_equal(string, current, comp_length))
    {
      return true;
    }
  }
  return false;
}

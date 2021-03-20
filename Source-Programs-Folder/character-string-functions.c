
#include "common-header-program.h"

char* generate_character_string(int length)
{
  char* string = malloc(sizeof(char) * length);
  for(int index = 0; index < length; index = index + 1)
  {
    string = allocate_string_character(string, index, CHAR_NONE);
  }
  return string;
}

char** generate_character_sentence(int height, int width)
{
  char** sentence = malloc(sizeof(char*) * height);
  for(int index = 0; index < height; index = index + 1)
  {
    char* string = generate_character_string(width);
    sentence = allocate_sentence_string(sentence, index, string);
  }
  return sentence;
}

char*** generate_character_paper(int amount, int height, int width)
{
  char*** paper = malloc(sizeof(char**) * amount);
  for(int index = 0; index < amount; index = index + 1)
  {
    char** sentence = generate_character_sentence(height, width);
    paper = allocate_paper_sentence(paper, index);
  }
  return paper;
}

char* allocate_string_character(char* string, int index, char character)
{
  *(string + index) = character; return string;
}

char** allocate_sentence_character(char** sentence, int height, int width, char character)
{
  char* string = sentence_index_string(sentence, height);
  string = allocate_string_character(string, width, character);
  sentence = allocate_sentence_string(sentence, height, string); // This is not needed!
  return sentence;
}

char*** allocate_paper_character(char*** paper, int index, int height, int width, char character)
{
  char** sentence = paper_index_sentence(paper, index);
  sentence = allocate_sentence_character(sentence, height, width, character);
  paper = allocate_paper_sentence(paper, index, sentence); // This is not needed!
  return paper;
}

char string_index_character(char* string, int index)
{
  char character = *(string + index); return character;
}

char sentence_index_character(char** sentence, int height, int width)
{
  char* string = sentence_index_string(sentence, height);
  char character = string_index_character(string, width);
  return character;
}

char paper_index_character(char*** paper, int index, int height, int width)
{
  char** sentence = paper_index_sentence(paper, index);
  char character = sentence_index_character(sentence, height, width);
  return character;
}

char* sentence_index_string(char** sentence, int index)
{
  char* string = *(sentence + index); return string;
}

char* paper_index_string(char*** paper, int index, int height)
{
  char** sentence = paper_index_string(paper, index);
  char* string = sentence_index_string(sentence, height);
  return string;
}

char** paper_index_sentence(char*** paper, int index)
{
  char** sentence = *(paper + index); return sentence;
}

char** allocate_sentence_string(char** sentence, int index, char* string)
{
  *(sentence + index) = string; return sentence;
}

char*** allocate_paper_string(char*** paper, int index, int height, char* string)
{
  char** sentence = paper_index_sentence(paper, index);
  sentence = allocate_sentence_string(sentence, height, string);
  paper = allocate_paper_sentence(paper, index, sentence); // This is not needed!
  return paper;
}

char*** allocate_paper_sentence(char*** paper, int index, char** sentence)
{
  *(paper + index) = sentence; return paper;
}

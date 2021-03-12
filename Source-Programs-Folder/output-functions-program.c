
#include "common-header-program.h"

char alphabet[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G',
  'H', 'J', 'I', CHAR_NONE};

char filename[] = "markers.txt";

void display_battleship_boards(char*** def_board,
  char*** off_board, int height, int width)
{
  char*** markers = extract_board_markers(filename,
    MARK_NUM);
  for(int index = 0; index < height; index = index + 1)
  {
    display_board_sentence(def_board, width, index,
      markers);
    display_board_sentence(off_board, width, index,
      markers);
  }
}

void display_battleship_board(char*** board, int height,
  int width)
{
  char*** markers = extract_board_markers(filename,
    MARK_NUM);
  printf("  ");
  for(int number = 1; number <= width; number += 1)
    printf("%d ", number); printf("\n");

  for(int index = 0; index < height; index = index + 1)
  {
    display_board_sentence(board, width, index, markers);
    printf("\n");
  }
}

void display_board_sentence(char*** board, int width,
  int height, char*** markers)
{
  char letter = alphabet_index_letter(alphabet, height);
  printf("%c ", letter);
  for(int index = 0; index < width; index = index + 1)
  {
    char* keyword = board_index_keyword(board, height,
      index);
    char marker=markers_keyword_marker(markers, MARK_NUM,
      keyword); printf("%c ", marker);
  }
}

char alphabet_index_letter(char alphabet[], int index)
{
  char letter = *(alphabet + index); return letter;
}

char markers_keyword_marker(char*** markers, int amount,
  char keyword[])
{
  for(int index = 0; index < amount; index = index + 1)
  {
    char* current = markers_index_keyword(markers,index);
    int length = character_string_length(current);
    if(character_strings_equal(keyword, current, length))
      return markers_index_marker(markers, index);
  }
  return CHAR_NONE;
}

char markers_index_marker(char*** markers, int index)
{
  char** marker_pair = *(markers + index);
  char marker = **(marker_pair + 1); return marker;
}

char* markers_index_keyword(char*** markers, int index)
{
  char** marker_pair = *(markers + index);
  char* keyword = *(marker_pair + 0); return keyword;
}

char*** extract_board_markers(char filename[], int amount)
{
  char** file_lines = extract_file_information(filename,
    amount);
  char*** markers = malloc(sizeof(char**) * amount);
  for(int index = 0; index < amount; index = index + 1)
  {
    char* current = sentence_index_string(file_lines,
      index);
    markers[index] = split_keyword_marker(current);
  }
  return markers;
}

char** split_keyword_marker(char current_line[])
{
  char** marker_pair = malloc(sizeof(char*) * (2 + 1));
  char* keyword = generate_character_string(STR_SIZE);
  char* marker = generate_character_string(STR_SIZE);
  sscanf(current_line, "%[A-Z]=%s", keyword, marker);

  marker_pair = allocate_sentence_string(marker_pair, 0,
    keyword);
  marker_pair = allocate_sentence_string(marker_pair, 1,
    marker); return marker_pair;
}

char** extract_file_information(char filename[],int lines)
{
  char** file_lines = malloc(sizeof(char*) * lines);
  FILE* file_pointer = fopen(filename, "r");
  char line_buffer[STR_SIZE];
  for(int index = 0; index < lines; index = index + 1)
  {
    if(!fgets(line_buffer, STR_SIZE, file_pointer))
      break;
    int length = character_string_length(line_buffer) - 1;
    *(file_lines + index) = strncpy(malloc(STR_SIZE),
      line_buffer, length);
  }
  fclose(file_pointer); return file_lines;
}

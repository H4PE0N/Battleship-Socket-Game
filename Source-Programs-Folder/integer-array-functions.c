
#include "common-header-program.h"

int* generate_integer_array(int length)
{
  int* array = malloc(sizeof(int) * (length + 1));
  for(int index = 0; index < (length + 1); index = index + 1)
  {
    array = allocate_array_integer(array, index, INT_NONE);
  }
  return array;
}

int** generate_integer_matrix(int height, int width)
{
  int** matrix = malloc(sizeof(int*) * (height + 1));
  for(int index = 0; index < (height + 1); index = index + 1)
  {
    int* array = generate_integer_array(width);
    matrix = allocate_matrix_array(matrix, index, array);
  }
  return matrix;
}

int*** generate_integer_block(int amount, int height, int width)
{
  int*** block = malloc(sizeof(int**) * (amount + 1));
  for(int index = 0; index < (amount + 1); index = index + 1)
  {
    int** matrix = generate_integer_matrix(height, width);
    block = allocate_block_matrix(block, index, matrix);
  }
  return block;
}

int* allocate_array_integer(int* array, int index, int integer)
{
  *(array + index) = integer; return array;
}

int** allocate_matrix_integer(int** matrix, int height, int width, int integer)
{
  int* array = matrix_index_array(matrix, height);
  array = allocate_array_integer(array, width, integer);
  matrix = allocate_matrix_array(matrix, height, array); // This is not needed!
  return matrix;
}

int*** allocate_block_integer(int*** block, int index, int height, int width, int integer)
{
  int** matrix = block_index_matrix(block, index);
  matrix = allocate_matrix_integer(matrix, height, width, integer);
  block = allocate_block_matrix(block, index, matrix); // This is not needed!
  return block;
}

int array_index_integer(int* array, int index)
{
  int integer = *(array + index); return integer;
}

int matrix_index_integer(int** matrix, int height, int width)
{
  int* array = matrix_index_array(matrix, height);
  int integer = array_index_integer(array, width);
  return integer;
}

int block_index_integer(int*** block, int index, int height, int width)
{
  int** matrix = block_index_matrix(block, index);
  int integer = matrix_index_integer(matrix, height, width);
  return integer;
}

int* matrix_index_array(int** matrix, int index)
{
  int* array = *(matrix + index); return array;
}

int* block_index_array(int*** block, int index, int height)
{
  int** matrix = block_index_matrix(block, index);
  int* array = matrix_index_array(matrix, height);
  return array;
}

int** block_index_matrix(int*** block, int index)
{
  int** matrix = *(block + index); return matrix;
}

int** allocate_matrix_array(int** matrix, int index, int* array)
{
  *(matrix + index) = array; return matrix;
}

int*** allocate_block_array(int*** block, int index, int height, int* array)
{
  int** matrix = block_index_matrix(block, index);
  matrix = allocate_matrix_array(matrix, height, array);
  block = allocate_block_matrix(block, index, matrix); // This is not needed!
  return block;
}

int*** allocate_block_matrix(int*** block, int index, int** matrix)
{
  *(block + index) = matrix; return block;
}

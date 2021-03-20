
#ifndef INTEGER_ARRAY_FUNCTIONS_H
#define INTEGER_ARRAY_FUNCTIONS_H

int* generate_integer_array(int);
int** generate_integer_matrix(int, int);
int*** generate_integer_block(int, int, int);

int* allocate_array_integer(int*, int, int);
int** allocate_matrix_integer(int**, int, int, int);
int*** allocate_block_integer(int***, int, int, int, int);

int array_index_integer(int*, int);
int matrix_index_integer(int**, int, int);
int block_index_integer(int***, int, int, int);

int* matrix_index_array(int**, int);
int* block_index_array(int***, int, int);

int** block_index_matrix(int***, int);

int** allocate_matrix_array(int**, int, int*);
int*** allocate_block_array(int***, int, int, int*);

int*** allocate_block_matrix(int***, int, int**);

#endif

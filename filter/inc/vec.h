
#ifndef TASK1_V70_VECTOR_H
#define TASK1_V70_VECTOR_H

#endif

#include <stdlib.h>
#include <monetary.h>
#define DEFAULT_VECTOR_SIZE 16

typedef struct {
    char** vector;
    ssize_t size;
    ssize_t alloc_size;
} vector;

void vec_init(vector* vec);

//Добавление элемента в вектор
char* vec_push(char* str, vector* vec);

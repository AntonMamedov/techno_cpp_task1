#include "vec.h"

#define EXTEND_SIZE 2

char* vec_push(char *str, vector *vec) {
    if (vec->vector == NULL){
        vec->vector = (char**)malloc(sizeof(char*) * DEFAULT_VECTOR_SIZE);
        vec->vector[vec->size] = str;
        vec->alloc_size = DEFAULT_VECTOR_SIZE;
        vec->size++;
    }
    else{
        if (vec->size == vec->alloc_size) {
            char **temp_vec = (char**)realloc(vec->vector, sizeof(char *) * vec->alloc_size * EXTEND_SIZE);
            if (temp_vec == NULL)
                return NULL;
            else {
                vec->vector = temp_vec;
                vec->vector[vec->size] = str;
                vec->alloc_size *= EXTEND_SIZE;
                vec->size++;
            }
        }
        else{
            vec->vector[vec->size] = str;
            vec->size++;
        }
    }
    return vec->vector[vec->size - 1];
}

void vec_init(vector *vec) {
    vec->vector = NULL;
    vec->size = 0;
    vec->alloc_size = 0;
}
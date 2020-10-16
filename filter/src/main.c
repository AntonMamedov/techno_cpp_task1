#include <stdlib.h>
#include <stdio.h>

#include "str.h"
#include "filter.h"

#define INCORRECT_HTML_LINE_ERR "The line in the HTML file is over 1024 characters, check its correctness"
#define ARG_ERR "For the program to work, you must pass the search pattern. For instance <task1_v70 pattern>"
#define ARG_COUNT 2

#define MAX_LINE_LENGTH 1024
#define MAX_PATTERN_LENGTH 1024

int main(int argc, char** argv){

    if (argc < ARG_COUNT){
        //если отсутствует паттерн поиска, пишем в поток ошибок
        fprintf(stderr, "%s\n", ARG_ERR);
    }
    else{
        /*
         * используем структуру vector, чтоб инкапсулировать в ней размер аллоцированной памяти
         * и фактический размер строки, без данной структуры в функции пришлось бы передавать
         * очень много аргументов
         */
        vector vec;
        vec_init(&vec);
        char sym;
        char buf[MAX_LINE_LENGTH + 1];
        //Читаем из потока ввода пока он не будет закрыт
        for (int len = 0; (sym = fgetc(stdin)) != EOF; len++){
            if (len > MAX_LINE_LENGTH) {
                fprintf(stderr, "%s", INCORRECT_HTML_LINE_ERR);
                return 0;
            }
            if (sym == '\n'){
                buf[len] = '\0';
                char* line = malloc(sizeof(char) * (len + 1));
                str_copy(line, buf);
                vec_push(line, &vec);
                len = -1;
            }
            else
                buf[len] = sym;
        }
        //Структура vector будет выступать в качестве результирующей структуры
        vector result_vec;
        vec_init(&result_vec);
        /*
         * передаем в функцию фильтрации паттерн, массив строк, его размер и указатель на результирующую структуру
         * в соответствии с заданием, но вместо массива строк я бы передал просто результирующую струтуру...
         */
        char pattern[MAX_PATTERN_LENGTH];
        if (argv[1][0] != '"'){
            pattern[0] = '"';
            str_copy(pattern + 1, argv[1]);
            pattern[str_length(argv[1]) + 1] = '"';
            pattern[str_length(argv[1]) + 2] = '\0';
        }
        else{
            str_copy(pattern, argv[1]);
        }
        ssize_t result_vec_size = filter(pattern, vec.vector, vec.size, &result_vec);
        for (size_t i = 0; i < result_vec.size; i++)
            printf("%s\n", result_vec.vector[i]);
        for (size_t i = 0; i < vec.size; i++)
            free(vec.vector[i]);
        free(vec.vector);
        free(result_vec.vector);
    }
    return 0;
}
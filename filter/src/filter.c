#include "filter.h"
#define SRC_LOW "src"
#define SRC_HIGH "SRC"
#define SRC_STR_SIZE 3

/*
 * та функция проверяет, чтоб между src и началом паттерна, т.е ", были только пробелы, табуляции и один знак равно
 */
static int find_the_equal_symbol(char* str){
    size_t count = 0;
    int indicator = -1;
    while (str[count] != '"'){
        if (str[count] == ' ' || str[count] == '\t')
            count++;
        else if (str[count] == '='){
            indicator++;
            count++;
        }
        else{
            return -1;
        }
    }
    if (indicator == 0)
        return 0;
    else
        return -1;
}

size_t filter(char* pattern, char **vec, size_t vec_size, vector *result_vec) {
    for (size_t i = 0; i < vec_size; i++){
        //Проверяем, есть ли в строке подстрока src верхнего или нижнего регистра
        char* src_low_paper = find(SRC_LOW, vec[i], SRC_STR_SIZE, str_length(vec[i])); //ищем нижний регистр
        char* src_high_paper = find(SRC_HIGH, vec[i], SRC_STR_SIZE, str_length(vec[i])); //ищем верхний регистр
        char* src_line = NULL;
        if (src_low_paper != NULL)
            src_line = src_low_paper;
        else
            src_line = src_high_paper;
        //если есть, ищем в строке паттерн
        if (src_line != NULL){
            if (find_the_equal_symbol(src_line + SRC_STR_SIZE) == 0){ // проверка, нет ли в строке лижних символов
                char* pattern_str = find(pattern, src_line, str_length(pattern), str_length(src_line));
                if (pattern_str != NULL) {
                    vec_push(vec[i], result_vec); // если находим, пушим строку в вектор строк
                }
            }
        }
    }
    return result_vec->size;
}
#include "str.h"

#define SYM_TAB_SIZE 128
static char* substr_cmp(const char* substr, char* str, int substr_lastsym_pos, int str_lastsym_pos);

char* str_copy(char* dest, const char* src){
    size_t count = 0;
    for (;src[count] != '\0'; count++)
        dest[count] = src[count];
    dest[count] = '\0';
    return dest;
}

size_t str_length(const char* str){
    size_t count = 0;
    while (str[count] != '\0')
        count++;
    return count;
}

char* find(const char *pattern, char* str, size_t pattern_size, size_t str_size){
    if (pattern == NULL || str == NULL ||
        pattern_size == 0 || str_size == 0 || pattern_size > str_size)
        return NULL;
    else if (pattern_size == 1){
        for (size_t i = 0; i < str_size; i++){
            if (pattern[0] == str[i])
                return str + i;
        }
        return NULL;
    }
    else{
        int sym_table[SYM_TAB_SIZE] = {0};
        for (int i = pattern_size - 2, pos = 1; i >= 0; i--, pos++){
            if (sym_table[pattern[i]] == 0)
                sym_table[pattern[i]] = pos;
        }
        if (sym_table[pattern[pattern_size - 1]] == 0)
            sym_table[pattern[pattern_size - 1]] = pattern_size;
        char* find_res = NULL;
        for (size_t pos = pattern_size - 1; pos < str_size;){
            if (str[pos] != pattern[pattern_size - 1]){
                if (sym_table[str[pos]] == 0)
                    pos+= pattern_size;
                else
                    pos += sym_table[str[pos]];
            }
            else{
                find_res = substr_cmp(pattern, str, pattern_size - 1, pos);
                if (find_res == NULL)
                    pos += pattern_size - 1;
                else
                    break;
            }
        }
        return find_res;
    }
}

/*
 * Проверка на то, является ли подстрока частью строки
 * Проивзодит посимвольное сравнение,итерируясь в обратную сторону,начиная
 * с указанной позиции строки и последнего символа в подстроке
 * Если все символы подстроки входят в строку, возвращает указатель на первый символ подстроки входящий в строку
 */
char* substr_cmp(const char* substr, char* str, int substr_lastsym_pos, int str_lastsym_pos){
    size_t sub_str_len = str_length(substr);
    int str_count = str_lastsym_pos - sub_str_len + 1;
    int sub_str_count = 0;
    if (str_count >= 0){
        for(;str[str_count] == substr[sub_str_count] && sub_str_count != sub_str_len; str_count++)
            sub_str_count++;
        if (sub_str_count != sub_str_len)
            return NULL;
        else
            return str + str_lastsym_pos - sub_str_len + 1;
    }
    else
        return NULL;
}
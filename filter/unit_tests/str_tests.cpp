#include "gtest/gtest.h"

extern "C"{
#include "../inc/str.h"
#include "../src/str.c"
}
TEST(StrFindTest, FindingMissingItem){
    char* src = "223 12 321 111 312 212 312";
    char* result_find = NULL;
    char* pattern = "000";
    EXPECT_EQ(result_find, find(pattern, src, strlen(pattern), strlen(src)));
}

TEST(StrFindTest, FindingSingleItem){
    char* src = "223 12 321 111 312 212 312";
    char* result_find = "12 321 111 312 212 312";
    char* pattern = "1";
    ASSERT_STREQ(result_find,  find(pattern, src, strlen(pattern), strlen(src)));
}

TEST(StrFindTest, FindInMidle){
    char* src = "223 12 321 111 312 212 312";
    char* result_find = "111 312 212 312";
    char* pattern = "111";
    ASSERT_STREQ(result_find, find(pattern, src, strlen(pattern), strlen(src)));
}

TEST(StrFindTest, FindInStart){
    char* src = "223 12 321 111 312 212 312";
    char* result_find = "223 12 321 111 312 212 312";
    char* pattern = "223";
    ASSERT_STREQ(result_find, find(pattern, src, strlen(pattern), strlen(src)));
}

TEST(StrFindTest, FindInEnd){
    char* src = "223 12 321 111 234 212 312";
    char* result_find = "312";
    char* pattern = "312";
    ASSERT_STREQ(result_find, find(pattern, src, strlen(pattern), strlen(src)));
}

//тестирование функции копирования

TEST(StrSopyTest, ThereIsEnoughSpaceInReceiveBuffer){
    char* src = "111";
    char* dest = (char*)malloc(sizeof(char) * strlen(src) + 1);
    str_copy(dest, src);
    ASSERT_STREQ(src, dest);
    free(dest);
}


//тестирование функции вычисления длины строки

TEST(StrLenTest, WithDeterministicZero_DynamicBuffer){
    char* buf = (char*)malloc(sizeof(char) * 3);
    buf[0] = 1;
    buf[1] = 1;
    buf[2] = '\0';
    ASSERT_EQ(2, str_length(buf));
    free(buf);
}


TEST(StrLenTest, StaticBuffer){
    char* buf = "11";
    ASSERT_EQ(2, str_length(buf));
}

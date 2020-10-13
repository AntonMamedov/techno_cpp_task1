#include "gtest/gtest.h"

extern "C"{
#include "../src/vec.c"
}

//Тестирование функции инициаизации вектора
TEST(VectorInitTest, InitTest){
    vector test;
    vec_init(&test);
    ASSERT_EQ(NULL, test.vector);
    ASSERT_EQ(0, test.size);
    ASSERT_EQ(0, test.alloc_size);
}

//Тестирование функции добавление элемента в вектор

TEST(VectorPushTest, NormalPushTest){
    vector test;
    vec_init(&test);
    char* src1 = "111";
    char* src2 = "222";
    vec_push(src1, &test);
    vec_push(src2, &test);
    ASSERT_EQ(2, test.size);
    ASSERT_EQ(DEFAULT_VECTOR_SIZE, test.alloc_size);
    ASSERT_STREQ(test.vector[0], src1);
    ASSERT_STREQ(test.vector[1], src2);
}

TEST(VectorPushTest, ExtendPushTest){
    vector test;
    vec_init(&test);
    char* src = "111";
    size_t count = 0;
    const size_t vec_size = 20;
    for (; count <vec_size; count++)
        vec_push(src, &test);
    ASSERT_EQ(count, test.size);
    ASSERT_EQ(DEFAULT_VECTOR_SIZE * 2, test.alloc_size);
    for (size_t i = 0; i < vec_size; i++)
        ASSERT_STREQ(test.vector[i], src);
    free(test.vector);
}
#include "gtest/gtest.h"
extern "C"{
#include "../src/filter.c"
}

TEST(FilterTest, NormlFIlterTest){
    vector test_src;
    vec_init(&test_src);
    char* pattern = "\"111\"";
    char* src1 = "src = \"111\"";
    char* src2 = "src 111";
    vec_push(src1,&test_src);
    vec_push(src2,&test_src);
    vector test_result;
    vec_init(&test_result);
    size_t res_size = filter(pattern, test_src.vector, test_src.size, &test_result);
    ASSERT_EQ(res_size, 1);
    ASSERT_STREQ(src1, test_result.vector[0]);
    free(test_result.vector);
    free(test_src.vector);
}

TEST(FilterTest, LowHighPaperTest){
    vector test_src;
    vec_init(&test_src);
    char* pattern = "\"111\"";
    char* src1 = "src = \"111\"";
    char* src2 = "SRC = \"111\"";
    vec_push(src1,&test_src);
    vec_push(src2,&test_src);
    vector test_result;
    vec_init(&test_result);
    size_t res_size = filter(pattern, test_src.vector, test_src.size, &test_result);
    ASSERT_EQ(res_size, 2);
    ASSERT_STREQ(src1, test_result.vector[0]);
    ASSERT_STREQ(src2, test_result.vector[1]);
    free(test_result.vector);
    free(test_src.vector);
}
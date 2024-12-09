#include "lib.c"
#include <stdio.h>
// Very small test helpers
int failed = 0;
#define TEST(name) void name()
#define RUN_TEST(name)                     \
    printf("\n\033[1m%s\n\033[0m", #name); \
    name()
#define ASSERT(expr)                                  \
    if (!(expr)) {                                    \
        failed = 1;                                   \
        printf("\033[0;31mFAIL: %s\n\033[0m", #expr); \
    } else {                                          \
        printf("\033[0;32mPASS: %s\n\033[0m", #expr); \
    }
#define ASSERT_EQ_INT(a, b)                                \
    if (!(a == b)) {                                       \
        failed = 1;                                        \
        printf("\033[0;31mFAIL: %d != %d\n\033[0m", a, b); \
    } else {                                               \
        printf("\033[0;32mPASS: %d == %d\n\033[0m", a, b); \
    }
#define ASSERT_STR_EQ(str1, str2)                                \
    if (!(strcmp(str1, str2) == 0)) {                            \
        failed = 1;                                              \
        printf("\033[0;31mFAIL: %s != %s\n\033[0m", str1, str2); \
    } else {                                                     \
        printf("\033[0;32mPASS: %s == %s\n\033[0m", str1, str2); \
    }
// End of test helpers
//
//

TEST(part_two_test)
{
    // ASSERT_EQ_INT(part_two("test.txt"), 2);
    // ASSERT_EQ_INT(part_two("example.txt"), 6);
}
TEST(part_one_test)
{
    // ASSERT_EQ_INT(part_one("example.txt"), 41);
    // ASSERT_EQ_INT(part_one("input.txt"), 4819);
}

int main()
{
    // RUN_TEST(part_one_test);
    // RUN_TEST(part_two_test);

    return failed;
}

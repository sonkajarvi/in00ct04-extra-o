#ifndef TEST_H
#define TEST_H

#include <stdio.h>

#define TEST_SUCCESS 0
#define TEST_FAILURE 1

#define __func(x) __func_##x
#define __name(x) __name_##x

#define __ESC "\033"
#define __RESET __ESC "[0m"
#define __RED __ESC "[31m"
#define __GREEN __ESC "[32m"

#define __run(x) \
    do { \
        const StTestResult r = x.function(); \
        if (r.result == TEST_SUCCESS) { \
            printf("[  " __GREEN "ok" __RESET "  ] %s\n", x.name); \
        } else { \
            printf("[ " __RED "fail" __RESET " ] %s, in '%s:%d', assert '%s'\n", x.name, r.file, r.line, r.expr); \
            return r.result;\
        } \
    } while (0)

#define test_declare(x) \
    do { \
        StTestResult __func(x)(void); \
        StTest __name(x) = { __func(x), #x }; \
        __run(__name(x)); \
    } while (0)

#define test_case(x) \
    StTestResult __func(x)(void)

#define test_assert(expr) \
    if (!(expr)) return (StTestResult){TEST_FAILURE, __LINE__, #expr, __FILE__}

#define test_success() \
    return (StTestResult){TEST_SUCCESS, 0, 0, 0}

typedef struct StTestResult
{
    int result;
    int line;
    const char *expr;
    const char *file;
} StTestResult;

typedef struct StTest
{
    StTestResult (*function)(void);
    const char *name;
} StTest;

#endif // TEST_H

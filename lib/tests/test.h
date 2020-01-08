#pragma once  /* test.h */

#include <stddef.h>

typedef struct {
    const char *name;
    int (*test_fn)();
} Test;

extern const Test TESTS[];

// int string_test(void);
// int vector_test(void);
// int list_test(void);
int result_test(void);

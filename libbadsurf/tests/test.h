#pragma once  /* test.h */

#include <cstddef>

typedef struct {
    const char *name;
    int (*test_fn)();
} Test;

extern const Test TESTS[];

int smart_show_test();
int read_test();

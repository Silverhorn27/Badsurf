#pragma once  /* test.h */

#include <cstddef>

typedef struct {
    const char *name;
    int (*test_fn)();
} Test;

extern const Test TESTS[];

int badsurf_test();

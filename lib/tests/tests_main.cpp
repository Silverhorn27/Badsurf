#include "test.h"

#include <cstdio>
#include <cassert>

#define N_TESTS 1

const Test TESTS[] = {
    // {"string", string_test},
    // {"vector", vector_test},
    // {"list", list_test},
    {"result", result_test},
};

int main(void)
{
    printf("[!] Found %d tests\n", N_TESTS);
    for (int i = 0; i < N_TESTS; i++) {
        printf("\n[*] Running [%d/%d] test: %s"
               "\n===========\n", i+1, N_TESTS, TESTS[i].name);
        if (!TESTS[i].test_fn()) {
            printf("\n[+] %s: test passed\n", TESTS[i].name);
        } else {
            fprintf(stderr, "\n[x] %s: test failed\n", TESTS[i].name);
            return 1;
        }
    }

    return 0;
}

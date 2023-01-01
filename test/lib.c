#include <stdio.h>

__attribute__((constructor))
static void init(void) {
    printf("[%s] initializing\n", __FILE__);
}

__attribute__((destructor))
static void destruct(void) {
    printf("[%s] destructing\n", __FILE__);
}

int adder(int x, int y) {
    return x + y;
}
#include <malloc.h>

void *CRYPTO_malloc(int num, const char *file, int line) {
    return malloc(num);
}

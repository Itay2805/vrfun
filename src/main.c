#include <util/except.h>

int main() {
    err_t err = NO_ERROR;

    TRACE("Hello world!");

cleanup:
    return err;
}

#include <string.h>
#include "except.h"

const char* error_to_str(err_t err) {
    if (err < 0) {
        return strerror(-err);
    } else {
        switch (err) {
            case NO_ERROR: return "No error";
            case ERROR_CHECK_FAILED: return "Check Failed";
            default: return "Unknown error";
        }
    }
}

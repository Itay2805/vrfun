#ifndef __VRFUN_EXCEPT_H__
#define __VRFUN_EXCEPT_H__

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "defs.h"

#define PRINT(fmt, ...) printf(fmt, ## __VA_ARGS__)
#define TRACE(fmt, ...) PRINT("[*] " fmt "\n", ## __VA_ARGS__)
#define ERROR(fmt, ...) PRINT("[-] " fmt "\n", ## __VA_ARGS__)

typedef int err_t;
#define NO_ERROR                0
#define ERROR_CHECK_FAILED      1
#define ERROR_NOT_FOUND         2

const char* error_to_str(err_t err);

#define IS_ERROR(err) (err != NO_ERROR)

#define CHECK_ERROR_LABEL_TRACE(expr, error, label, fmt, ...) \
    do { \
        if (!(expr)) { \
            err = error; \
            ERROR(fmt, ## __VA_ARGS__); \
            ERROR("CHECK failed with error `%s` in function %s (%s:%d)", error_to_str(err), __func__, STR(__FILENAME__), __LINE__); \
            goto label; \
        } \
    } while(0)

#define CHECK_ERROR_TRACE(expr, error, fmt, ...) CHECK_ERROR_LABEL_TRACE(expr, error, cleanup, fmt, ## __VA_ARGS__)
#define CHECK_LABEL_TRACE(expr, label, fmt, ...) CHECK_ERROR_LABEL_TRACE(expr, ERROR_CHECK_FAILED, label, fmt, ## __VA_ARGS__)
#define CHECK_TRACE(expr, fmt, ...) CHECK_ERROR_LABEL_TRACE(expr, ERROR_CHECK_FAILED, cleanup, fmt, ## __VA_ARGS__)

#define CHECK_ERROR_LABEL(expr, error, label) \
    do { \
        if (!(expr)) { \
            err = error; \
            ERROR("CHECK failed with error `%s` in function %s (%s:%d)", error_to_str(err), __func__, STR(__FILENAME__), __LINE__); \
            goto label; \
        } \
    } while(0)

#define CHECK_ERROR(expr, error) CHECK_ERROR_LABEL(expr, error, cleanup)
#define CHECK_LABEL(expr, label) CHECK_ERROR_LABEL(expr, ERROR_CHECK_FAILED, label)
#define CHECK(expr) CHECK_ERROR_LABEL(expr, ERROR_CHECK_FAILED, cleanup)

#define CHECK_FAIL_ERROR_TRACE(error, fmt, ...) CHECK_ERROR_LABEL_TRACE(0, error, cleanup, fmt, ## __VA_ARGS__)
#define CHECK_FAIL_LABEL_TRACE(label, fmt, ...) CHECK_ERROR_LABEL_TRACE(0, ERROR_CHECK_FAILED, label, fmt, ## __VA_ARGS__)
#define CHECK_FAIL_TRACE(fmt, ...) CHECK_ERROR_LABEL_TRACE(0, ERROR_CHECK_FAILED, cleanup, fmt, ## __VA_ARGS__)

#define CHECK_FAIL_ERROR(error) CHECK_ERROR_LABEL(0, error, cleanup)
#define CHECK_FAIL_LABEL(label) CHECK_ERROR_LABEL(0, ERROR_CHECK_FAILED, label)
#define CHECK_FAIL() CHECK_ERROR_LABEL(0, ERROR_CHECK_FAILED, cleanup)

#define CHECK_AND_RETHROW_LABEL(error, label) \
    do { \
        err = error; \
        if (IS_ERROR(err)) { \
            ERROR("\trethrown at %s (%s:%d)", __func__, STR(__FILENAME__), __LINE__); \
            goto label; \
        } \
    } while(0)

#define CHECK_AND_RETHROW(error) CHECK_AND_RETHROW_LABEL(error, cleanup)

#define WARN(expr, fmt, ...) \
    do { \
        if (!(expr)) { \
            PRINT("[!] Warning! " fmt " at %s (%s:%d)\n", ## __VA_ARGS__ , __func__, STR(__FILENAME__), __LINE__); \
        } \
    } while(0)

#define LIBC_CHECK(expr) CHECK_ERROR(expr, -errno)

#endif //__VRFUN_EXCEPT_H__